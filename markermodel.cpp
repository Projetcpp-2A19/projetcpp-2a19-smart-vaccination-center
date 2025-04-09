#include "MarkerModel.h"

MarkerModel::MarkerModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int MarkerModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_coordinates.count();
}

QVariant MarkerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_coordinates.count())
        return QVariant();

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
