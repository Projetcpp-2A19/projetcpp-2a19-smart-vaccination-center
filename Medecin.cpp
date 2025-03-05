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


// Constructeur
Medecin::Medecin(int id, const std::string& nom, const std::string& prenom,
                 const std::string& specialite, const std::string& contact)
    : id_med(id), nom_med(nom), prenom_med(prenom), specialite_med(specialite), contact_med(contact) {}

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
{
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM medecins");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("Spécialité"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("Contact"));
            return model;

}


// Méthode pour afficher les informations du médecin
/*void Medecin::afficher() const {
    std::cout << "Docteur " << prenom_med << " " << nom_med
              << ", Spécialité: " << specialite_med
              << ", Contact: " << contact_med << std::endl;
}*/
}
