#include "rendezvous.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

// Constructeur par défaut
RendezVous::RendezVous() : id_rdv(0), date_rdv(QDate::currentDate()), heure_rdv(QTime::currentTime()), priorite_rdv(""), status("En attente"), id_pat(0) {}

// Constructeur paramétré
RendezVous::RendezVous(int id, QDate date, QTime heure, QString priorite, QString stat, int idp)
    : id_rdv(id), date_rdv(date), heure_rdv(heure), priorite_rdv(priorite), status(stat), id_pat(idp) {}

// Getters
int RendezVous::getIdRdv() const { return id_rdv; }
QDate RendezVous::getDateRdv() const { return date_rdv; }
QTime RendezVous::getHeureRdv() const { return heure_rdv; }
QString RendezVous::getPrioriteRdv() const { return priorite_rdv; }
QString RendezVous::getStatus() const { return status; }
int RendezVous::getIdpat() const { return id_pat; }

// Setters
void RendezVous::setIdRdv(int id) { id_rdv = id; }
void RendezVous::setDateRdv(QDate date) { date_rdv = date; }
void RendezVous::setHeureRdv(QTime heure) { heure_rdv = heure; }
void RendezVous::setPrioriteRdv(QString priorite) { priorite_rdv = priorite; }
void RendezVous::setStatus(QString stat) { status = stat; }
void RendezVous::setIdpat(int idp) { id_pat = idp; }

// CRUD

// Méthode pour ajouter un rendez-vous dans la base de données
bool RendezVous::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO RENDEZ_VOUS (id_rdv, date_rdv, heure_rdv, priorite_rdv, status ,id_pat) "
                  "VALUES (:id, TO_DATE(:date, 'YYYY-MM-DD'), TO_TIMESTAMP(:heure, 'HH24:MI:SS'), :priorite, :status, :id_pat)");
    query.bindValue(":id", id_rdv);
    query.bindValue(":date", date_rdv.toString("yyyy-MM-dd"));
    query.bindValue(":heure", heure_rdv.toString("HH:mm:ss"));
    query.bindValue(":priorite", priorite_rdv);
    query.bindValue(":status", status);
    query.bindValue(":id_pat", id_pat);
    return query.exec();
}


QSqlQueryModel* RendezVous::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM RENDEZ_VOUS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_rdv"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("date_rdv"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("heure_rdv"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("priorite_rdv"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("status"));
    return model;
}

// Méthode pour supprimer un rendez-vous en fonction de son ID
bool RendezVous::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM RENDEZ_VOUS WHERE id_rdv = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur SQL lors de la suppression :" << query.lastError().text();
        return false;
    }

    return true;
}


// Modifier un rendez vous
bool RendezVous::modifier(int id) {
    QSqlQuery query;
    query.prepare("UPDATE RENDEZ_VOUS SET id_rdv=:id, date_rdv=TO_DATE(:date, 'YYYY-MM-DD'), heure_rdv=TO_TIMESTAMP(:heure, 'HH24:MI:SS'), priorite_rdv=:priorite, status=:status, id_pat=:id_pat  WHERE id_rdv=:id");
    query.bindValue(":id", id_rdv);
    query.bindValue(":date", date_rdv.toString("yyyy-MM-dd"));
    query.bindValue(":heure", heure_rdv.toString("HH:mm:ss"));
    query.bindValue(":priorite", priorite_rdv);
    query.bindValue(":status", status);
    query.bindValue(":id_pat", id_pat);

    return query.exec();
}

//MERIERS

QSqlQueryModel* RendezVous::rechercher(QString searchTerm) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Convertir le terme de recherche en minuscules
    searchTerm = searchTerm.toLower();

    query.prepare("SELECT id_rdv, date_rdv, heure_rdv, priorite_rdv, status, id_pat "
                  "FROM RENDEZ_VOUS "
                  "WHERE TO_CHAR(id_pat) LIKE LOWER(:searchTerm)"
                  "ORDER BY id_rdv");

    query.bindValue(":searchTerm", "%" + searchTerm + "%");  // Recherche partielle
    query.exec();
    model->setQuery(query);

    return model;
}

QMap<QString, int> RendezVous::getStatistiquesParDate() {
    QMap<QString, int> stats;
    QSqlQuery query("SELECT TO_CHAR(date_rdv, 'YYYY-MM-DD'), COUNT(*) FROM RENDEZ_VOUS GROUP BY TO_CHAR(date_rdv, 'YYYY-MM-DD') ORDER BY TO_CHAR(date_rdv, 'YYYY-MM-DD')");

    while (query.next()) {
        QString type = query.value(0).toString();
        int count = query.value(1).toInt();
        stats[type] = count;
    }

    return stats;
}
