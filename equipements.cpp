#include "equipements.h"
#include <QDebug>
#include <QSqlError>

// Constructeurs
Equipement::Equipement() {}

Equipement::Equipement(int id, QString nom, QString type, QString statut, QDate date_maintenance)
    : id_eqp(id), nom_eqp(nom), type_eqp(type), statut_eqp(statut), date_maintenance_eqp(date_maintenance) {}

// Ajouter un équipement
bool Equipement::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO EQUIPEMENTS (id_eqp, nom_eqp, type_eqp, statut_eqp, date_maintenance_eqp) "
                  "VALUES (:id, :nom, :type, :statut, TO_DATE(:date_maintenance, 'YYYY-MM-DD'))");

    query.bindValue(":id", id_eqp);
    query.bindValue(":nom", nom_eqp);
    query.bindValue(":type", type_eqp);
    query.bindValue(":statut", statut_eqp);
    query.bindValue(":date_maintenance", date_maintenance_eqp.toString("yyyy-MM-dd"));


    return query.exec();
}

// Afficher tous les équipements
QSqlQueryModel* Equipement::afficher(){
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT nom_eqp, type_eqp, statut_eqp, date_maintenance_eqp FROM EQUIPEMENTS");

    // Set headers for better readability
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date Maintenance"));

    return model;
}

// Modifier un équipement
bool Equipement::modifier(int id) {
    QSqlQuery query;
    query.prepare("UPDATE EQUIPEMENTS SET nom_eqp=:nom, type_eqp=:type, statut_eqp=:statut, date_maintenance_eqp=:date_maintenance WHERE id_eqp=:id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom_eqp);
    query.bindValue(":type", type_eqp);
    query.bindValue(":statut", statut_eqp);
    query.bindValue(":date_maintenance", date_maintenance_eqp);

    return query.exec();
}

// Supprimer un équipement
bool Equipement::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM EQUIPEMENTS WHERE id_eqp = :id");
    query.bindValue(":id", id);
    return query.exec();
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
