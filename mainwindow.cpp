#include "mainwindow.h"
#include "patient.h"
#include "./ui_mainwindow.h"
#include <QMouseEvent>  // For detecting mouse events
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <cstdlib>  // Pour rand() et srand()
#include <ctime>    // Pour time()
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <ctime>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  // Setup UI from Qt Designer

    connect(ui->exit, &QPushButton::clicked, this, &MainWindow::close);

    // Reference the existing popupWidget from the UI (it should be named popupWidget in the designer)
    popupWidget = ui->popupWidget;

    // Optionally, set the position and size of the popup widget (can be customized)
    popupWidget->setGeometry(200, 100, 200, 100);  // Set position and size of the popup

    // Initially hide the popup
    popupWidget->hide();

    // Connect button click to show or hide the popup
    connect(ui->btnmedecin, &QPushButton::clicked, this, &MainWindow::on_btnmedecin_clicked);
    // Initialisation de la table
    ui->tableau3_2->setColumnCount(8);
    ui->tableau3_2->setHorizontalHeaderLabels({"ID", "Nom", "Prénom", "Date Naissance", "Email", "Genre", "Adresse", "Groupe Sanguin"});
    ui->tableau3_2->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Charger les patients existants
    Patient p;
    p.afficher(ui->tableau3_2);
    /*ui->tableau->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau6->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);*/

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnajouterpatient_clicked()
{
    // Génération d'un ID aléatoire
    std::srand(std::time(0));
    int min = 1, max = 100;
    int id = min + std::rand() % (max - min + 1);

    QString nom = ui->lineEdit_45->text().trimmed();
    QString prenom = ui->lineEdit_46->text().trimmed();
    QDate dateNaiss = ui->dateEdit_7->date();
    QString email = ui->lineEdit_47->text().trimmed();
    QString genre = ui->comboBox_9->currentText();
    QString adresse = ui->lineEdit_48->text().trimmed();
    QString groupeSanguin = ui->lineEdit_49->text().trimmed();

    // 🔹 Vérification : Champs vides
    if (nom.isEmpty() || prenom.isEmpty() || email.isEmpty() || adresse.isEmpty() || groupeSanguin.isEmpty()) {
        QMessageBox::warning(this, "Champ vide", "Tous les champs doivent être remplis !");
        return;
    }

    // 🔹 Vérification : Nom & Prénom (doivent contenir uniquement des lettres)
    QRegularExpression regexAlpha("^[A-Za-zÀ-ÿ]+$");
    if (!regexAlpha.match(nom).hasMatch() || !regexAlpha.match(prenom).hasMatch()) {
        QMessageBox::warning(this, "Format invalide", "Le nom et le prénom doivent contenir uniquement des lettres !");
        return;
    }

    // 🔹 Vérification : Email (format `*@*.com`)
    QRegularExpression regexEmail("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.com$");
    if (!regexEmail.match(email).hasMatch()) {
        QMessageBox::warning(this, "Email invalide", "L'email doit être sous la forme exemple@domaine.com !");
        return;
    }

    Patient patient;

    if (currentPatientId == -1) {
        // 🔹 Ajout d'un nouveau patient
        if (patient.ajouter()) {
            QMessageBox::information(this, "Succès", "Patient ajouté avec succès !");
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de l'ajout du patient.");
        }
    } else {
        // 🔹 Modification d'un patient existant
        if (patient.modifierPatient(currentPatientId, nom, prenom, dateNaiss, email, genre, adresse, groupeSanguin)) {
            QMessageBox::information(this, "Succès", "Patient modifié avec succès !");
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la modification du patient.");
        }

        // Réinitialisation après modification
        currentPatientId = -1;
        ui->btnajouterpatient->setText("Ajouter");
        ui->btnajouterpatient->setStyleSheet("background-color: blue; color: white; font-weight: bold; border-radius: 10px; padding: 8px;");
    }

    patient.afficher(ui->tableau3_2); // Rafraîchir la liste des patients
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    // Detect if the click happens outside the popupWidget
    if (!popupWidget->geometry().contains(event->pos())) {
        popupWidget->hide();  // Hide the popup if clicked outside
    }
}
void MainWindow::supprimerPatient(int id)
{
    Patient p;
    if (p.supprimerPatient(id)) {
        QMessageBox::information(this, "Suppression réussie", "Le patient a été supprimé avec succès."+ QString::number(id));
        p.afficher(ui->tableau3_2); // Rafraîchir la liste
    }
}
void MainWindow::modifierPatient(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM PATIENTS WHERE ID_PAT = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        // Stocker l'ID du patient en modification
        currentPatientId = id;

        // Remplir le formulaire avec les données du patient sélectionné
        ui->lineEdit_45->setText(query.value("NOM_PAT").toString());
        ui->lineEdit_46->setText(query.value("PRENOM_PAT").toString());
        ui->dateEdit_7->setDate(query.value("DATENAIS_PAT").toDate());
        ui->lineEdit_47->setText(query.value("EMAIL").toString());
        ui->comboBox_9->setCurrentText(query.value("GENRE").toString());
        ui->lineEdit_48->setText(query.value("ADRESSE").toString());
        ui->lineEdit_49->setText(query.value("GROUPSANGUIN").toString());

        // Changer le texte du bouton "Ajouter" en "Modifier"
        ui->btnajouterpatient->setText("Modifier");
        ui->btnajouterpatient->setStyleSheet("background-color: green; color: white; font-weight: bold; border-radius: 10px; padding: 8px;");
    } else {
        QMessageBox::critical(this, "Erreur","Impossible de récupérer les informations du patient." + QString::number(currentPatientId));
    }
}
void MainWindow::on_btnmedecin_clicked()
{
    ui->sqs->setCurrentIndex(0);
}

void MainWindow::on_btnpatient_clicked()
{
    ui->sqs->setCurrentIndex(1);
}

void MainWindow::on_btnlabo_clicked()
{
    ui->sqs->setCurrentIndex(2);
}

void MainWindow::on_btnequiprmrnt_clicked()
{
    ui->sqs->setCurrentIndex(3);
}

void MainWindow::on_btnvaccins_clicked()
{
    ui->sqs->setCurrentIndex(4);
}

void MainWindow::on_btnrendezv_clicked()
{
    ui->sqs->setCurrentIndex(5);
}

void MainWindow::on_btnuser_clicked()
{
    ui->sqs->setCurrentIndex(6);
}

void MainWindow::on_btnlabo2_clicked()
{
    ui->sqs->setCurrentIndex(7);
}

void MainWindow::on_btnlabo3_clicked()
{
    ui->sqs->setCurrentIndex(8);
}

void MainWindow::on_btnlabo4_clicked()
{
    ui->sqs->setCurrentIndex(9);
}

void MainWindow::on_btnmedecin2_clicked()
{
    ui->sqs->setCurrentIndex(10);
}

void MainWindow::on_btnpatient2_clicked()
{
    ui->sqs->setCurrentIndex(11);
}

void MainWindow::on_btnequiprmrnt2_clicked()
{
    ui->sqs->setCurrentIndex(12);
}

void MainWindow::on_btnequiprmrnt3_clicked()
{
    ui->sqs->setCurrentIndex(13);
}

void MainWindow::on_btnvaccins2_clicked()
{
    ui->sqs->setCurrentIndex(14);
}

void MainWindow::on_btnrendezv2_clicked()
{
    ui->sqs->setCurrentIndex(15);
}

void MainWindow::on_btnrendezv3_clicked()
{
    ui->sqs->setCurrentIndex(16);
}





