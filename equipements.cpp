#include "equipements.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

// Constructeurs
Equipement::Equipement() {}
//description_eqp description
Equipement::Equipement(int id, QString nom, QString type, QString statut, QDate date_maintenance, QString description)
    : id_eqp(id), nom_eqp(nom), type_eqp(type), statut_eqp(statut), date_maintenance_eqp(date_maintenance), description_eqp(description) {}

// Ajouter un équipement
bool Equipement::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO EQUIPEMENTS (id_eqp, nom_eqp, type_eqp, statut_eqp, date_maintenance_eqp, description_eqp) "
                  "VALUES (:id, :nom, :type, :statut, TO_DATE(:date_maintenance, 'YYYY-MM-DD'), :description)");

    query.bindValue(":id", id_eqp);
    query.bindValue(":nom", nom_eqp);
    query.bindValue(":type", type_eqp);
    query.bindValue(":statut", statut_eqp);
    query.bindValue(":date_maintenance", date_maintenance_eqp.toString("yyyy-MM-dd"));
    query.bindValue(":description", description_eqp);


    return query.exec();
}

// Afficher tous les équipements
QSqlQueryModel* Equipement::afficher(){
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery(R"(
        SELECT
            id_eqp,
            nom_eqp,
            type_eqp,
            statut_eqp,
            date_maintenance_eqp,
            description_eqp
        FROM EQUIPEMENTS
        ORDER BY id_eqp ASC
    )");


    // Set headers for better readability
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date Maintenance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Description"));

    return model;
}

// Modifier un équipement
bool Equipement::modifier(int id) {
    QSqlQuery query;
    query.prepare("UPDATE EQUIPEMENTS SET nom_eqp=:nom, type_eqp=:type, statut_eqp=:statut, date_maintenance_eqp=:date_maintenance, description_eqp=:description WHERE id_eqp=:id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom_eqp);
    query.bindValue(":type", type_eqp);
    query.bindValue(":statut", statut_eqp);
    // If the QDate is valid, bind it directly. Otherwise, bind a null QVariant.
    if (date_maintenance_eqp.isValid()) {
        query.bindValue(":date_maintenance", date_maintenance_eqp);
    } else {
        query.bindValue(":date_maintenance", QVariant());
    }
    query.bindValue(":description", description_eqp);

    return query.exec();
}

// Supprimer un équipement
bool Equipement::supprimer(int id) {
    QSqlQuery query;

    // Step 1: Delete the equipment with the given ID
    query.prepare("DELETE FROM EQUIPEMENTS WHERE id_eqp = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Erreur SQL lors de la suppression :" << query.lastError().text();
        return false;
    }

    // Step 2: Reorder the remaining IDs to be sequential
    query.prepare("UPDATE EQUIPEMENTS SET id_eqp = id_eqp - 1 WHERE id_eqp > :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Erreur SQL lors de la mise à jour des IDs :" << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQueryModel* Equipement::rechercher(QString searchTerm) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Convert search term to lowercase
    searchTerm = searchTerm.toLower();

    query.prepare("SELECT id_eqp, nom_eqp, type_eqp, statut_eqp, date_maintenance_eqp, description_eqp "
                  "FROM EQUIPEMENTS "
                  "WHERE LOWER(nom_eqp) LIKE LOWER(:searchTerm) OR LOWER(type_eqp) LIKE LOWER(:searchTerm) "
                  "ORDER BY id_eqp ASC");

    query.bindValue(":searchTerm", "%" + searchTerm + "%");  // Enable partial matches
    query.exec();
    model->setQuery(query);

    return model;
}

QString Equipement::getEquipementsAsHTML() {
    QString html = "<h1 style='text-align: center;'>Liste des Équipements</h1>";
    html += "<table border='1' cellspacing='0' cellpadding='5' width='100%'>";
    html += "<tr><th>ID</th><th>Nom</th><th>Type</th><th>Statut</th><th>Date Maintenance</th><th>Description</th></tr>";

    QSqlQuery query("SELECT id_eqp, nom_eqp, type_eqp, statut_eqp, date_maintenance_eqp, description_eqp FROM EQUIPEMENTS");
    while (query.next()) {
        html += "<tr>";
        html += "<td>" + query.value("id_eqp").toString() + "</td>";
        html += "<td>" + query.value("nom_eqp").toString() + "</td>";
        html += "<td>" + query.value("type_eqp").toString() + "</td>";
        html += "<td>" + query.value("statut_eqp").toString() + "</td>";
        html += "<td>" + query.value("date_maintenance_eqp").toString() + "</td>";
        html += "<td>" + query.value("description_eqp").toString() + "</td>";
        html += "</tr>";
    }
    html += "</table>";

    return html;
}

QMap<QString, int> Equipement::getStatistiquesParType() {
    QMap<QString, int> stats;
    QSqlQuery query("SELECT type_eqp, COUNT(*) FROM EQUIPEMENTS GROUP BY type_eqp");

    while (query.next()) {
        QString type = query.value(0).toString();
        int count = query.value(1).toInt();
        stats[type] = count;
    }

    return stats;
}

bool Equipement::setEnPanne(const QString &idEquipement) {
    QSqlQuery query;
    query.prepare("UPDATE EQUIPEMENTS SET statut_eqp = 'En panne' WHERE id_eqp = :id");
    query.bindValue(":id", idEquipement);

    if (!query.exec()) {
        qDebug() << "ERROR: Failed to update status to 'En panne' for ID:" << idEquipement;
        return false;
    }
    return true;
}

// Getters et Setters
int Equipement::getId() const { return id_eqp; }
void Equipement::setId(int id) { id_eqp = id; }
QString Equipement::getNom() const { return nom_eqp; }
void Equipement::setNom(const QString &nom) { nom_eqp = nom; }
QString Equipement::getType() const { return type_eqp; }
void Equipement::setType(const QString &type) { type_eqp = type; }
QString Equipement::getStatut() const { return statut_eqp; }
void Equipement::setStatut(const QString &statut) { statut_eqp = statut; }
QDate Equipement::getDateMaintenance() const { return date_maintenance_eqp; }
void Equipement::setDateMaintenance(const QDate &date) { date_maintenance_eqp = date; }
QString Equipement::getDescription() const { return description_eqp; };
void Equipement::setDescription(const QString &description) { description_eqp = description; }
