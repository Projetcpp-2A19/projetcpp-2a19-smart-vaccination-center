#include "MarkerModel.h"
#include <QGeoServiceProvider>
#include <QGeoCodingManager>
#include <QGeoCodeReply>
#include <QSqlQuery>
#include <QSqlError>
#include <QGeoLocation>
#include <QGeoLocation>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCoreApplication>



MarkerModel::MarkerModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int MarkerModel::rowCount(const QModelIndex &parent) const //nbr totale de coordonner
{
    Q_UNUSED(parent);
    return m_coordinates.count();
}

QVariant MarkerModel::data(const QModelIndex &index, int role) const//Fournit les données d’une coordonnée spécifique à QM
{
    if (!index.isValid() || index.row() >= m_coordinates.count())
        return QVariant();
// Récupération des données (QML)
    const QGeoCoordinate &coord = m_coordinates.at(index.row());

    switch (role) {
    case CoordinateRole:
        return QVariant::fromValue(coord);
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> MarkerModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CoordinateRole] = "coordinate";
    return roles;
}

void MarkerModel::addMarker(const QGeoCoordinate &coord)
{
    if (!coord.isValid()) {
        qWarning() << "Coordonnée invalide ignorée.";
        return;
    }

    qDebug() << "Ajout d'un marqueur — Latitude:" << coord.latitude()
             << ", Longitude:" << coord.longitude();

    beginInsertRows(QModelIndex(), m_coordinates.size(), m_coordinates.size());
    m_coordinates.append(coord);
    endInsertRows();

    qDebug() << "Nombre total de marqueurs après ajout:" << m_coordinates.count();
}
void MarkerModel::loadFromJson()
{
    QString filePath = QCoreApplication::applicationDirPath() + "/coordinates.json";
    QFile file(filePath);

    if (!file.exists()) {
        qWarning() << "❌ Le fichier coordinates.json n'existe pas :" << filePath;
        return;
    }

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "❌ Impossible d'ouvrir coordinates.json en lecture :" << file.errorString();
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "❌ Erreur lors du parsing JSON :" << parseError.errorString();
        return;
    }

    if (!doc.isArray()) {
        qWarning() << "❌ Le contenu JSON n'est pas un tableau.";
        return;
    }

    QJsonArray array = doc.array();

    beginResetModel();
    m_coordinates.clear();

    for (const QJsonValue &val : array) {
        if (!val.isObject())
            continue;

        QJsonObject obj = val.toObject();
        double lat = obj["latitude"].toDouble();
        double lon = obj["longitude"].toDouble();

        if (!qFuzzyIsNull(lat) && !qFuzzyIsNull(lon)) {
            QGeoCoordinate coord(lat, lon);
            qDebug() << "📍 Chargé depuis JSON :" << coord;
            m_coordinates.append(coord);
        } else {
            qWarning() << "⚠️ Coordonnée invalide ignorée :" << obj;
        }
    }

    endResetModel();
    qDebug() << "✅ Modèle rechargé depuis le fichier JSON.";
}


void MarkerModel::addLocation(const QString &localisation, double lat, double lon)
{
    QFile file(QCoreApplication::applicationDirPath() + "/coordinates.json");
    QJsonArray array;

    // Lire le fichier existant
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        array = doc.array();
        file.close();
    }

    // Éviter les doublons
    for (const QJsonValue &val : array) {
        if (val.toObject()["localisation"].toString().compare(localisation, Qt::CaseInsensitive) == 0)
            return;
    }

    // Ajouter le nouvel objet
    QJsonObject obj;
    obj["localisation"] = localisation;
    obj["latitude"] = lat;
    obj["longitude"] = lon;
    array.append(obj);

    // Écrire dans le fichier
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        file.write(QJsonDocument(array).toJson());
        file.close();
    }

    // Ajouter visuellement sur la carte
    addMarker(QGeoCoordinate(lat, lon));
}

void MarkerModel::removeLocation(const QString &localisation)
{
    QFile file(QCoreApplication::applicationDirPath() + "/coordinates.json");

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "❌ Impossible d'ouvrir coordinates.json pour lecture";
        return;
    }

    if (localisation.trimmed().isEmpty()) {
        qWarning() << "❌ Nom de localisation vide ou invalide reçu.";
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonArray array = doc.array();
    file.close();

    QJsonArray updatedArray;
    QList<QGeoCoordinate> coordsASupprimer;

    // Comparaison avec une tolérance
    for (const QJsonValue &val : array) {
        QJsonObject obj = val.toObject();
        QString loc = obj["localisation"].toString();
        if (loc.compare(localisation, Qt::CaseInsensitive) != 0) {
            updatedArray.append(obj);
        } else {
            double lat = obj["latitude"].toDouble();
            double lon = obj["longitude"].toDouble();
            if (!qIsNaN(lat) && !qIsNaN(lon)) {
                coordsASupprimer.append(QGeoCoordinate(lat, lon));
                qDebug() << "🗑️ Supprimer : " << lat << lon;
            }
        }
    }

    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        file.write(QJsonDocument(updatedArray).toJson());
        file.close();
    }

    // Supprimer les coordonnées du modèle avec une tolérance sur les coordonnées
    bool removed = false;
    for (const QGeoCoordinate &coord : coordsASupprimer) {
        for (int i = 0; i < m_coordinates.size(); ++i) {
            if (qFuzzyCompare(m_coordinates[i].latitude(), coord.latitude()) &&
                qFuzzyCompare(m_coordinates[i].longitude(), coord.longitude())) {
                m_coordinates.removeAt(i);
                removed = true;
                break;
            }
        }
    }

    if (removed) {
        beginResetModel();
        endResetModel();
    } else {
        qWarning() << "⚠️ Aucune coordonnée correspondante trouvée dans le modèle.";
    }
}
