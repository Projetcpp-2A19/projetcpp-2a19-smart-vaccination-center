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
    if (!tableWidget) return;

    tableWidget->clearContents();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(10);
    tableWidget->setHorizontalHeaderLabels({"ID", "Nom", "Prénom", "Date Naissance", "Email", "Genre", "Adresse", "Groupe Sanguin", "Actions", "Certificat"});

    QSqlQuery query;
    if (!query.exec("SELECT * FROM PATIENTS ORDER BY ID_PAT")) {
        QMessageBox::critical(nullptr, "Erreur SQL", "Impossible de récupérer les patients !");
        return;
    }

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

        // ---------- BOUTONS MODIFIER & SUPPRIMER ----------
        QWidget* widget = new QWidget();
        QPushButton* btnModifier = new QPushButton("✏ Modifier");
        QPushButton* btnSupprimer = new QPushButton("🗑 Supprimer");

        btnModifier->setFixedSize(80, 25);
        btnSupprimer->setFixedSize(80, 25);

        QString buttonStyle = R"(
            QPushButton {
                background-color: green;
                color: #ffffff;
                border: 2px solid rgb(173, 216, 230);
                padding: 5px;
                margin: 3px;
                border-radius: 8px;
                font-size: 12px;
                font-weight: bold;
            }
            QPushButton:hover {
                background-color: #606060;
                border-color: #777777;
            }
            QPushButton:pressed {
                background-color: #787878;
                border-color: #909090;
            }
        )";
        QString buttonStyle2 = buttonStyle;
        buttonStyle2.replace("green", "red");

        btnModifier->setStyleSheet(buttonStyle);
        btnSupprimer->setStyleSheet(buttonStyle2);

        int patientID = query.value("ID_PAT").toInt();
        btnModifier->setProperty("id", patientID);
        btnSupprimer->setProperty("id", patientID);

        QObject* parentWidget = tableWidget->window();
        MainWindow* mainWindow = qobject_cast<MainWindow*>(parentWidget);
        if (mainWindow) {
            QObject::connect(btnModifier, &QPushButton::clicked, mainWindow, [mainWindow, patientID]() {
                mainWindow->modifierPatient(patientID);
            });

            QObject::connect(btnSupprimer, &QPushButton::clicked, mainWindow, [mainWindow, patientID]() {
                mainWindow->supprimerPatient(patientID);
            });
        }

        QHBoxLayout* layout = new QHBoxLayout();
        layout->addWidget(btnModifier);
        layout->addWidget(btnSupprimer);
        layout->setContentsMargins(3, 1, 3, 1);
        layout->setAlignment(Qt::AlignCenter);
        widget->setLayout(layout);
        tableWidget->setCellWidget(row, 8, widget);

        // ---------- BOUTON CERTIFICAT ----------
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
        btnCertificat->setProperty("id", patientID);

        if (mainWindow) {
            QObject::connect(btnCertificat, &QPushButton::clicked, mainWindow, [mainWindow, patientID]() {
                mainWindow->envoyerCertificat(patientID);  // Crée cette fonction
            });
        }

        tableWidget->setCellWidget(row, 9, btnCertificat); // Nouvelle colonne "Certificat"
        row++;
    }

    tableWidget->resizeColumnsToContents();
}

void Patient::afficherSpecifique(QTableWidget* tableWidget, const QString& filtreNom)
{
    if (!tableWidget) return;

    tableWidget->clearContents();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(9);
    tableWidget->setHorizontalHeaderLabels({"ID", "Nom", "Prénom", "Date Naissance", "Email", "Genre", "Adresse", "Groupe Sanguin", "Actions"});

    QSqlQuery query;
    query.prepare("SELECT * FROM PATIENTS WHERE NOM_PAT LIKE :nom ORDER BY ID_PAT");
    query.bindValue(":nom", "%" + filtreNom + "%");  // Recherche partielle sur le nom

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL", "Impossible de récupérer les patients recherchés !");
        return;
    }

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

        // 🔹 Création des boutons Modifier / Supprimer
        QWidget* widget = new QWidget();
        QPushButton* btnModifier = new QPushButton("✏ Modifier");
        QPushButton* btnSupprimer = new QPushButton("🗑 Supprimer");

        // 🔹 Réduire la taille des boutons
        btnModifier->setFixedSize(80, 25);
        btnSupprimer->setFixedSize(80, 25);

        // 🔹 Appliquer un style
        btnModifier->setStyleSheet("background-color: green; color: white; font-weight: bold;");
        btnSupprimer->setStyleSheet("background-color: red; color: white; font-weight: bold;");

        // 🔹 Récupérer l'ID du patient
        int patientID = query.value("ID_PAT").toInt();
        btnModifier->setProperty("id", patientID);
        btnSupprimer->setProperty("id", patientID);

        // 🔹 Récupérer la fenêtre principale (MainWindow)
        QObject* parentWidget = tableWidget->window();
        MainWindow* mainWindow = qobject_cast<MainWindow*>(parentWidget);
        if (mainWindow) {
            // Connexion du bouton Modifier
            QObject::connect(btnModifier, &QPushButton::clicked, mainWindow, [mainWindow, patientID]() {
                mainWindow->modifierPatient(patientID);
            });

            // Connexion du bouton Supprimer
            QObject::connect(btnSupprimer, &QPushButton::clicked, mainWindow, [mainWindow, patientID]() {
                mainWindow->supprimerPatient(patientID);
            });
        }

        // 🔹 Mise en page des boutons
        QHBoxLayout* layout = new QHBoxLayout();
        layout->addWidget(btnModifier);
        layout->addWidget(btnSupprimer);
        layout->setContentsMargins(3, 1, 3, 1);
        layout->setAlignment(Qt::AlignCenter);
        widget->setLayout(layout);

        tableWidget->setCellWidget(row, 8, widget);
        row++;
    }

    tableWidget->resizeColumnsToContents();
}


bool Patient::supprimerPatient(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM PATIENTS WHERE ID_PAT = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        return true; // Suppression réussie
    } else {
        QMessageBox::critical(nullptr, "Erreur de suppression", "Impossible de supprimer le patient !");
        return false; // Échec
    }
}
bool Patient::modifierPatient(int id, const QString& nom, const QString& prenom, const QDate& dateNaiss, const QString& email, const QString& genre, const QString& adresse, const QString& groupeSanguin)
{
    QSqlQuery query;
    query.prepare("UPDATE PATIENTS SET NOM_PAT = :nom, PRENOM_PAT = :prenom, DATENAIS_PAT = :dateNaiss, EMAIL = :email, GENRE = :genre, ADRESSE = :adresse, GROUPSANGUIN = :groupeSanguin WHERE ID_PAT = :id");

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":dateNaiss", dateNaiss);
    query.bindValue(":email", email);
    query.bindValue(":genre", genre);
    query.bindValue(":adresse", adresse);
    query.bindValue(":groupeSanguin", groupeSanguin);
    query.bindValue(":id", id);

    if (query.exec()) {
        return true; // Modification réussie
    } else {
        QMessageBox::critical(nullptr, "Erreur de modification", "Impossible de modifier le patient !");
        return false; // Échec
    }
}

void Patient::afficherTrieParAnneeNaissance(QTableWidget* tableWidget)
{
    if (!tableWidget) return;

    tableWidget->clearContents();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(9);
    tableWidget->setHorizontalHeaderLabels({"ID", "Nom", "Prénom", "Date Naissance", "Email", "Genre", "Adresse", "Groupe Sanguin", "Actions"});

    QString sqlQuery = "SELECT * FROM PATIENTS ORDER BY EXTRACT(YEAR FROM DATENAIS_PAT) ASC";
    QSqlQuery query;
    if (!query.exec(sqlQuery)) {
        QMessageBox::critical(nullptr, "Erreur SQL", "Impossible de trier les patients !");
        return;
    }

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

        // 🔹 Création des boutons Modifier / Supprimer
        QWidget* widget = new QWidget();
        QPushButton* btnModifier = new QPushButton("✏ Modifier");
        QPushButton* btnSupprimer = new QPushButton("🗑 Supprimer");

        // 🔹 Réduire la taille des boutons
        btnModifier->setFixedSize(80, 25);
        btnSupprimer->setFixedSize(80, 25);

        // 🔹 Appliquer un style
        btnModifier->setStyleSheet("background-color: green; color: white; font-weight: bold;");
        btnSupprimer->setStyleSheet("background-color: red; color: white; font-weight: bold;");

        // 🔹 Récupérer l'ID du patient
        int patientID = query.value("ID_PAT").toInt();
        btnModifier->setProperty("id", patientID);
        btnSupprimer->setProperty("id", patientID);

        // 🔹 Récupérer la fenêtre principale (MainWindow)
        QObject* parentWidget = tableWidget->window();
        MainWindow* mainWindow = qobject_cast<MainWindow*>(parentWidget);
        if (mainWindow) {
            // Connexion du bouton Modifier
            QObject::connect(btnModifier, &QPushButton::clicked, mainWindow, [mainWindow, patientID]() {
                mainWindow->modifierPatient(patientID);
            });

            // Connexion du bouton Supprimer
            QObject::connect(btnSupprimer, &QPushButton::clicked, mainWindow, [mainWindow, patientID]() {
                mainWindow->supprimerPatient(patientID);
            });
        }

        // 🔹 Mise en page des boutons
        QHBoxLayout* layout = new QHBoxLayout();
        layout->addWidget(btnModifier);
        layout->addWidget(btnSupprimer);
        layout->setContentsMargins(3, 1, 3, 1);
        layout->setAlignment(Qt::AlignCenter);
        widget->setLayout(layout);

        tableWidget->setCellWidget(row, 8, widget);
        row++;
    }

    tableWidget->resizeColumnsToContents();
}

