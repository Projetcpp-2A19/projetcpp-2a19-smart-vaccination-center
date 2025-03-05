#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMouseEvent>  // For detecting mouse events
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  // Setup UI from Qt Designer
    connect(ui->exit, &QPushButton::clicked, this, &MainWindow::close);

    ui->tableau->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableauEquipements->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau6->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow(){
    delete ui;
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

void MainWindow::updateTableView() //aff
{
    ui->tableauEquipements->setModel(equipement.afficher());
}

void MainWindow::on_btnequipementAjouter_clicked(){
    // Générer un ID unique (MAX(id_eqp) + 1)
    QSqlQuery query;
    query.prepare("SELECT MAX(id_eqp) FROM EQUIPEMENTS");
    query.exec();

    int id = 1;  // Valeur par défaut si la table est vide
    if (query.next()) {
        id = query.value(0).toInt() + 1;  // Incrémentation du dernier ID
    }

    // Récupérer les valeurs de l'UI
    QString nom = ui->lineEdit_51->text();
    QString type = ui->comboBox_11->currentText();
    QString statut = ui->comboBox_13->currentText();

    // Obtenir la date actuelle (type QDate)
    QDate dateMaintenance = QDate::currentDate();

    // Check if 'nom' is empty
    if (nom.isEmpty()) {
        // Show an error message if empty
        QMessageBox::warning(this, "Erreur", "Le nom ne peut pas être vide !");
    }
    else{
        // Créer l'objet Equipement
        Equipement equip(id, nom, type, statut, dateMaintenance);

        // Ajouter dans la base de données
        if (equip.ajouter()) {
            QMessageBox::information(this, "Succès", "Equipement ajouté avec succès !");
            afficherEquipements();  // Refresh table after adding
        } else {
            QMessageBox::critical(this, "Erreur", "L'ajout de l'équipement a échoué !");
        }
    }
    /*if (!query.exec()) {
        qDebug() << "Database Error: " << query.lastError().text();
        QMessageBox::critical(nullptr, "Database Error", "Error: " + query.lastError().text());
    }*/
}

void MainWindow::afficherEquipements(){
    QSqlQueryModel* model = equipement.afficher();
    ui->tableauEquipements->setModel(model);  // Assign model to QTableView
}

