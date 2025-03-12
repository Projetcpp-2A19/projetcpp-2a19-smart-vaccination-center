#include "Medecin.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QString>
#include "Medecin.h"
#include <QList>
#include <qsqlerror.h>
#include <iostream>
#include <QMessageBox>
#include <QRegularExpression>
#include <regex>

// Constructeur
Medecin::Medecin(int id, const std::string& nom, const std::string& prenom,
                 const std::string& specialite, const std::string& contact)
    : id_med(id), nom_med(nom), prenom_med(prenom), specialite_med(specialite), contact_med(contact) {}

Medecin::Medecin() {
    id_med = 0;
    nom_med = "";
    prenom_med = "";
    specialite_med = "";
    contact_med = "";
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
    query.prepare("INSERT INTO medecins (id_med, nom_med, prenom_med, specialite_med, contact_med) "
                  "VALUES (:id, :nom, :prenom, :specialite, :contact)");

    query.bindValue(":id", id_med);
    query.bindValue(":nom", QString::fromStdString(nom_med));
    query.bindValue(":prenom", QString::fromStdString(prenom_med));
    query.bindValue(":specialite", QString::fromStdString(specialite_med));
    query.bindValue(":contact", QString::fromStdString(contact_med));

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
    // Vérifier que l'ID est positif
    if (id <= 0) {
        return false;
    }

    // Vérifier que nom, prenom et specialite contiennent uniquement des lettres
    std::regex regexNomPrenom("^[A-Za-zÀ-ÖØ-öø-ÿ ]+$");
    if (!std::regex_match(nom, regexNomPrenom) ||
        !std::regex_match(prenom, regexNomPrenom) ||
        !std::regex_match(specialite, regexNomPrenom)) {
        return false;
    }

    // Vérifier que le contact contient exactement 8 chiffres
    std::regex regexContact("^[0-9]{8}$");
    if (!std::regex_match(contact, regexContact)) {
        return false;
    }

    return true;
}



