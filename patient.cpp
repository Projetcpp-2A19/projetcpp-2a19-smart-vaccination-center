#include "patient.h"
#include <QSqlError>
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include "mainwindow.h"
// Constructeurs
Patient::Patient() {}

Patient::Patient(int id, QString nom, QString prenom, QDate dateNaissance,
                 QString email, QString genre, QString adresse, QString groupSanguin,int tel)
    : id(id), nom(nom), prenom(prenom), dateNaissance(dateNaissance),
    email(email), genre(genre), adresse(adresse), groupSanguin(groupSanguin), tel(tel) {}

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
    query.prepare("INSERT INTO PATIENTS (ID_PAT, NOM_PAT, PRENOM_PAT, DATENAIS_PAT, EMAIL, GENRE, ADRESSE, GROUPSANGUIN, TEL) "
                  "VALUES (:id, :nom, :prenom, :dateNaissance, :email, :genre, :adresse, :groupSanguin, :tel)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":dateNaissance", dateNaissance);
    query.bindValue(":email", email);
    query.bindValue(":genre", genre);
    query.bindValue(":adresse", adresse);
    query.bindValue(":groupSanguin", groupSanguin);
    query.bindValue(":tel", tel);

    qDebug() << id << nom << prenom << dateNaissance << email << genre << adresse << groupSanguin << tel;

    if (!query.exec()) {
        qDebug() << "Error:" << query.lastError().text();
        return false;  // Ne pas relancer
    }

    qDebug() << "SQL QUERY:" << query.lastQuery();
    return true;  // Succès
}


// Afficher les patients dans un QTableWidget
void Patient::afficher(QTableWidget* tableWidget)
{
    if (!tableWidget) return;

    tableWidget->clearContents();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(10);
    tableWidget->setHorizontalHeaderLabels({
        "ID", "Nom", "Prénom", "Date Naissance", "Email", "Genre", "Adresse", "Groupe Sanguin", "Téléphone", "Certificat"
    });

    QSqlQuery query;
    if (!query.exec("SELECT ID_PAT, NOM_PAT, PRENOM_PAT, DATENAIS_PAT, EMAIL, GENRE, ADRESSE, GROUPSANGUIN, TEL FROM PATIENTS ORDER BY ID_PAT")) {
        //QMessageBox::critical(nullptr, "Erreur SQL", "Impossible de récupérer les patients !");
        return;
    }

    int row = 0;
    while (query.next()) {
        tableWidget->insertRow(row);
        for (int col = 0; col <= 8; ++col) {
            tableWidget->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
        }

        // Bouton certificat seulement
        QPushButton* btnCertificat = new QPushButton("📩 Certificat");
        btnCertificat->setFixedSize(100, 25);
        btnCertificat->setStyleSheet(R"(
            QPushButton {
                background-color: #2980b9;
                color: white;
                border: 2px solid rgb(173, 216, 230);
                padding: 5px;
                margin: 3px;
                border-radius: 8px;
                font-size: 12px;
                font-weight: bold;
            }
            QPushButton:hover {
                background-color: #1f618d;
                border-color: #5dade2;
            }
            QPushButton:pressed {
                background-color: #154360;
                border-color: #3498db;
            }
        )");

        int patientID = query.value("ID_PAT").toInt();
        btnCertificat->setProperty("id", patientID);

        MainWindow* mainWindow = qobject_cast<MainWindow*>(tableWidget->window());
        if (mainWindow) {
            QObject::connect(btnCertificat, &QPushButton::clicked, mainWindow, [mainWindow, patientID]() {
                mainWindow->envoyerCertificat(patientID);
            });
        }

        tableWidget->setCellWidget(row, 9, btnCertificat);
        row++;
    }

    tableWidget->resizeColumnsToContents();
}


void Patient::afficherSpecifique(QTableWidget* tableWidget, const QString& filtreNom)
{
    if (!tableWidget) return;

    tableWidget->clearContents();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(10);
    tableWidget->setHorizontalHeaderLabels({
        "ID", "Nom", "Prénom", "Date Naissance", "Email", "Genre", "Adresse", "Groupe Sanguin", "Téléphone", "Certificat"
    });

    QSqlQuery query;
    query.prepare("SELECT ID_PAT, NOM_PAT, PRENOM_PAT, DATENAIS_PAT, EMAIL, GENRE, ADRESSE, GROUPSANGUIN, TEL FROM PATIENTS WHERE NOM_PAT LIKE :nom ORDER BY ID_PAT");
    query.bindValue(":nom", "%" + filtreNom + "%");

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL", "Impossible de récupérer les patients recherchés !");
        return;
    }

    int row = 0;
    while (query.next()) {
        tableWidget->insertRow(row);
        for (int col = 0; col <= 8; ++col) {
            tableWidget->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
        }

        // Bouton Certificat uniquement
        QPushButton* btnCertificat = new QPushButton("📩 Certificat");
        btnCertificat->setFixedSize(100, 25);
        btnCertificat->setStyleSheet(R"(
            QPushButton {
                background-color: #2980b9;
                color: white;
                border: 2px solid rgb(173, 216, 230);
                padding: 5px;
                margin: 3px;
                border-radius: 8px;
                font-size: 12px;
                font-weight: bold;
            }
            QPushButton:hover {
                background-color: #1f618d;
                border-color: #5dade2;
            }
            QPushButton:pressed {
                background-color: #154360;
                border-color: #3498db;
            }
        )");

        int patientID = query.value("ID_PAT").toInt();
        btnCertificat->setProperty("id", patientID);

        MainWindow* mainWindow = qobject_cast<MainWindow*>(tableWidget->window());
        if (mainWindow) {
            QObject::connect(btnCertificat, &QPushButton::clicked, mainWindow, [mainWindow, patientID]() {
                mainWindow->envoyerCertificat(patientID);
            });
        }

        tableWidget->setCellWidget(row, 9, btnCertificat);
        row++;
    }

    tableWidget->resizeColumnsToContents();
}



bool Patient::supprimerPatient(int id)
{
    QSqlQuery query;

    // Supprimer les injections liées
    query.prepare("DELETE FROM INJECTIONS WHERE ID_PAT = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Erreur suppression INJECTIONS:" << query.lastError().text();
        return false;
    }

    // Supprimer les rendez-vous liés
    query.prepare("DELETE FROM RENDEZ_VOUS WHERE ID_PAT = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Erreur suppression RENDEZ_VOUS:" << query.lastError().text();
        return false;
    }


    // Enfin, supprimer le patient
    query.prepare("DELETE FROM PATIENTS WHERE ID_PAT = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Erreur suppression PATIENTS:" << query.lastError().text();
        return false;
    }

    qDebug() << "Patient supprimé avec succès.";
    return true;
}
bool Patient::modifierPatient(int id, const QString& nom, const QString& prenom, const QDate& dateNaiss, const QString& email, const QString& genre, const QString& adresse, const QString& groupeSanguin,int tel)
{
    QSqlQuery query;
    query.prepare("UPDATE PATIENTS SET NOM_PAT = :nom, PRENOM_PAT = :prenom, DATENAIS_PAT = :dateNaiss, EMAIL = :email, GENRE = :genre, ADRESSE = :adresse, GROUPSANGUIN = :groupeSanguin, TEL = :tel WHERE ID_PAT = :id");

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":dateNaiss", dateNaiss);
    query.bindValue(":email", email);
    query.bindValue(":genre", genre);
    query.bindValue(":adresse", adresse);
    query.bindValue(":groupeSanguin", groupeSanguin);
    query.bindValue(":tel", tel);
    query.bindValue(":id", id);

    if (query.exec()) {
        return true; // Modification réussie
    } else {
        QMessageBox::critical(nullptr, "Erreur de modification", "Impossible de modifier le patient !");
        return false; // Échec
    }
}

void Patient::afficherTrieParAnneeNaissance(QTableWidget* tableWidget, bool croissant)
{
    if (!tableWidget) return;

    tableWidget->clearContents();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(10); // +1 colonne pour le bouton
    tableWidget->setHorizontalHeaderLabels({
        "ID", "Nom", "Prénom", "Date Naissance", "Email", "Genre", "Adresse", "Groupe Sanguin", "Téléphone", "Certificat"
    });

    QString ordre = croissant ? "ASC" : "DESC";
    QString sqlQuery = "SELECT ID_PAT, NOM_PAT, PRENOM_PAT, DATENAIS_PAT, EMAIL, GENRE, ADRESSE, GROUPSANGUIN, TEL FROM PATIENTS ORDER BY EXTRACT(YEAR FROM DATENAIS_PAT) " + ordre;

    QSqlQuery query;
    if (!query.exec(sqlQuery)) {
        QMessageBox::critical(nullptr, "Erreur SQL", "Impossible de trier les patients !");
        return;
    }

    int row = 0;
    while (query.next()) {
        tableWidget->insertRow(row);
        for (int i = 0; i < 9; ++i)
            tableWidget->setItem(row, i, new QTableWidgetItem(query.value(i).toString()));

        // Bouton Certificat
        QPushButton* btnCertificat = new QPushButton("📩 Certificat");
        btnCertificat->setFixedSize(100, 25);
        btnCertificat->setStyleSheet(R"(
            QPushButton {
                background-color: #2980b9;
                color: white;
                border: 2px solid rgb(173, 216, 230);
                padding: 5px;
                margin: 3px;
                border-radius: 8px;
                font-size: 12px;
                font-weight: bold;
            }
            QPushButton:hover {
                background-color: #1f618d;
                border-color: #5dade2;
            }
            QPushButton:pressed {
                background-color: #154360;
                border-color: #3498db;
            }
        )");

        int patientID = query.value("ID_PAT").toInt();
        btnCertificat->setProperty("id", patientID);

        QObject* parentWidget = tableWidget->window();
        MainWindow* mainWindow = qobject_cast<MainWindow*>(parentWidget);
        if (mainWindow) {
            QObject::connect(btnCertificat, &QPushButton::clicked, mainWindow, [mainWindow, patientID]() {
                mainWindow->envoyerCertificat(patientID);
            });
        }

        tableWidget->setCellWidget(row, 9, btnCertificat);
        row++;
    }

    tableWidget->resizeColumnsToContents();
}
