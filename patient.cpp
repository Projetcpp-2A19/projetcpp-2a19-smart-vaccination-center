#include "patient.h"
#include <QSqlError>
#include <QDebug>

// Constructeurs
Patient::Patient() {}

Patient::Patient(int id, QString nom, QString prenom, QDate dateNaissance,
                 QString email, QString genre, QString adresse, QString groupSanguin)
    : id(id), nom(nom), prenom(prenom), dateNaissance(dateNaissance),
    email(email), genre(genre), adresse(adresse), groupSanguin(groupSanguin) {}

// Getters et Setters
int Patient::getId() const { return id; }
void Patient::setId(int id) { this->id = id; }
QString Patient::getNom() const { return nom; }
void Patient::setNom(const QString &nom) { this->nom = nom; }
QString Patient::getPrenom() const { return prenom; }
void Patient::setPrenom(const QString &prenom) { this->prenom = prenom; }
QDate Patient::getDateNaissance() const { return dateNaissance; }
void Patient::setDateNaissance(const QDate &dateNaissance) { this->dateNaissance = dateNaissance; }
QString Patient::getEmail() const { return email; }
void Patient::setEmail(const QString &email) { this->email = email; }
QString Patient::getGenre() const { return genre; }
void Patient::setGenre(const QString &genre) { this->genre = genre; }
QString Patient::getAdresse() const { return adresse; }
void Patient::setAdresse(const QString &adresse) { this->adresse = adresse; }
QString Patient::getGroupSanguin() const { return groupSanguin; }
void Patient::setGroupSanguin(const QString &groupSanguin) { this->groupSanguin = groupSanguin; }

// Ajouter un patient à la base de données
bool Patient::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO PATIENTS (ID_PAT, NOM_PAT, PRENOM_PAT, DATENAIS_PAT, EMAIL, GENRE, ADRESSE, GROUPSANGUIN) "
                  "VALUES (:id, :nom, :prenom, :dateNaissance, :email, :genre, :adresse, :groupSanguin)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":dateNaissance", dateNaissance);
    query.bindValue(":email", email);
    query.bindValue(":genre", genre);
    query.bindValue(":adresse", adresse);
    query.bindValue(":groupSanguin", groupSanguin);

    return query.exec();
}

// Afficher les patients dans un QTableWidget
void Patient::afficher(QTableWidget* tableWidget)
{
    tableWidget->setRowCount(0); // Vider le tableau avant de le remplir
    QSqlQuery query("SELECT * FROM PATIENTS ORDER BY ID_PAT");

    int row = 0;
    while (query.next()) {
        tableWidget->insertRow(row);
        tableWidget->setItem(row, 0, new QTableWidgetItem(query.value("ID_PAT").toString()));
        tableWidget->setItem(row, 1, new QTableWidgetItem(query.value("NOM_PAT").toString()));
        tableWidget->setItem(row, 2, new QTableWidgetItem(query.value("PRENOM_PAT").toString()));
        tableWidget->setItem(row, 3, new QTableWidgetItem(query.value("DATENAIS_PAT").toString()));
        tableWidget->setItem(row, 4, new QTableWidgetItem(query.value("EMAIL").toString()));
        tableWidget->setItem(row, 5, new QTableWidgetItem(query.value("GENRE").toString()));
        tableWidget->setItem(row, 6, new QTableWidgetItem(query.value("ADRESSE").toString()));
        tableWidget->setItem(row, 7, new QTableWidgetItem(query.value("GROUPSANGUIN").toString()));
        row++;
    }
}
