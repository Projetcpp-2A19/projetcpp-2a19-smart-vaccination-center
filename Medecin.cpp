#include "Medecin.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QString>
#include <QList>
#include <qsqlerror.h>
#include <iostream>
#include <QMessageBox>
#include <QRegularExpression>
#include <regex>


// Constructeur
Medecin::Medecin(int id, const std::string& nom, const std::string& prenom,
                 const std::string& specialite, const std::string& contact, const std::string& mdp,
                 const std::string& question, const std::string& reponse)
    : id_med(id), nom_med(nom), prenom_med(prenom), specialite_med(specialite), contact_med(contact),
    mdp(mdp), question(question), reponse(reponse) {}

Medecin::Medecin() {
    id_med = 0;
    nom_med = "";
    prenom_med = "";
    specialite_med = "";
    contact_med = "";
    mdp = "";
    question = "";
    reponse = "";
}

// Getters
int Medecin::getId() const {
    return id_med;
}

std::string Medecin::getNom() const {
    return nom_med;
}

std::string Medecin::getPrenom() const {
    return prenom_med;
}

std::string Medecin::getSpecialite() const {
    return specialite_med;
}

std::string Medecin::getContact() const {
    return contact_med;
}

// Setters
void Medecin::setId(int id) {
    id_med = id;
}

void Medecin::setNom(const std::string& nom) {
    nom_med = nom;
}

void Medecin::setPrenom(const std::string& prenom) {
    prenom_med = prenom;
}

void Medecin::setSpecialite(const std::string& specialite) {
    specialite_med = specialite;
}

void Medecin::setContact(const std::string& contact) {
    contact_med = contact;
}
bool Medecin::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO medecins (id_med, nom_med, prenom_med, specialite_med, contact_med,mdp, question, reponse) "
                  "VALUES (:id, :nom, :prenom, :specialite, :contact, :mdp, :question, :reponse)");

    query.bindValue(":id", id_med);
    query.bindValue(":nom", QString::fromStdString(nom_med));
    query.bindValue(":prenom", QString::fromStdString(prenom_med));
    query.bindValue(":specialite", QString::fromStdString(specialite_med));
    query.bindValue(":contact", QString::fromStdString(contact_med));
    query.bindValue(":mdp", QString::fromStdString(mdp));
    query.bindValue(":question", QString::fromStdString(question));
    query.bindValue(":reponse", QString::fromStdString(reponse));

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout du médecin: " << query.lastError();
        return false;
    }
    return true;
}

QSqlQueryModel* Medecin::afficher() {

        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM medecins");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("Spécialité"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("Contact"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("MDP"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("question"));
            model->setHeaderData(7, Qt::Horizontal, QObject::tr("reponse"));

    return model;

}

bool Medecin::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM medecins WHERE id_med = :id");
    query.bindValue(":id", id);
    return query.exec();
}


bool Medecin::modifier() {
    QSqlQuery query;
    query.prepare("UPDATE medecins SET nom_med= :nom, prenom_med= :prenom, specialite_med= :specialite, contact_med= :contact WHERE id_med= :id");

    query.bindValue(":id", id_med);
    query.bindValue(":nom", QString::fromStdString(nom_med));
    query.bindValue(":prenom", QString::fromStdString(prenom_med));
    query.bindValue(":specialite", QString::fromStdString(specialite_med));
    query.bindValue(":contact", QString::fromStdString(contact_med));

    return query.exec();
}
bool Medecin::verifierChamps(int id, const std::string& nom, const std::string& prenom,
                             const std::string& specialite, const std::string& contact) {

    if (id <= 0) {
        return false;
    }


    std::regex regexNomPrenom("^[A-Za-zÀ-ÖØ-öø-ÿ ]+$");
    if (!std::regex_match(nom, regexNomPrenom) ||
        !std::regex_match(prenom, regexNomPrenom) ||
        !std::regex_match(specialite, regexNomPrenom)) {
        return false;
    }


    std::regex regexContact("^[0-9]{8}$");
    if (!std::regex_match(contact, regexContact)) {
        return false;
    }

    return true;
}

QSqlQueryModel * Medecin::tri_id()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM medecins ORDER BY id_med ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Spécialité"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Contact"));

    return model;
}




QSqlQueryModel * Medecin::tri_nom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM medecins ORDER BY nom_med ASC");


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_med"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom_med"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("specialite_med"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("contact_med"));



    return model;


}

QSqlQueryModel * Medecin::tri_prenom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM medecins ORDER BY prenom_med ASC");


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_med"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom_med"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("specialite_med"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("contact_med"));



    return model;


}

QSqlQueryModel* Medecin::chercher(int id_chercher)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM medecins WHERE id_med = :id");
    query.bindValue(":id", id_chercher);
    query.exec();

    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Spécialité"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Contact"));

    return model;
}

/*std::map<std::string, int> Medecin::statistiquesParSpecialite() {
    std::map<std::string, int> stats;
    QSqlQuery query("SELECT specialite_med, COUNT(*) FROM medecins GROUP BY specialite_med");

    while (query.next()) {
        std::string specialite = query.value(0).toString().toStdString();
        int count = query.value(1).toInt();
        stats[specialite] = count;
    }

    return stats;
}
*/
/*std::map<std::string, int> Medecin::statistiquesParSpecialite() {
    std::map<std::string, int> stats;
    QSqlQuery query;

    if (!query.exec("SELECT specialite_med, COUNT(*) FROM medecins GROUP BY specialite_med")) {
        qDebug() << "Erreur SQL :" << query.lastError().text();
        return stats;
    }

    while (query.next()) {
        std::string specialite = query.value(0).toString().toStdString();
        int count = query.value(1).toInt();
        stats[specialite] = count;
    }

    return stats;
}*/
std::map<std::string, int> Medecin::statistiquesParSpecialite() {
    std::map<std::string, int> stats;
    QSqlQuery query;
    query.prepare("SELECT SPECIALITE_MED, COUNT(*) FROM MEDECINS GROUP BY SPECIALITE_MED");

    if (query.exec()) {
        while (query.next()) {
            QString specialite = query.value(0).toString();
            int count = query.value(1).toInt();
            stats[specialite.toStdString()] = count;
        }
        qDebug() << "Nombre de spécialités récupérées :" << stats.size();
    } else {
        qDebug() << "Erreur SQL :" << query.lastError().text();
    }

    return stats;
}
