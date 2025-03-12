#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMouseEvent>  // For detecting mouse events
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include "Medecin.h"
#include <QMessageBox>

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

    ui->tableau->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau6->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        connect(ui->pushButton_116, &QPushButton::clicked, this, &MainWindow::ajouterMedecin);


}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::mousePressEvent(QMouseEvent *event) {
    // Detect if the click happens outside the popupWidget
    if (!popupWidget->geometry().contains(event->pos())) {
        popupWidget->hide();  // Hide the popup if clicked outside
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


void MainWindow::ajouterMedecin()
{
    int id = ui->lineEdit_id->text().toInt();
    std::string nom = ui->lineEdit_21->text().toStdString();
    std::string prenom = ui->lineEdit_23->text().toStdString();
    std::string specialite = ui->lineEdit_25->text().toStdString();
    std::string contact = ui->lineEdit_27->text().toStdString();

    if (!Medecin::verifierChamps(id, nom, prenom, specialite, contact)) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez entrer des informations valides !");
        return;
    }

    Medecin med(id, nom, prenom, specialite, contact);
    if (med.ajouter()) {
        QMessageBox::information(this, "Succès", "Médecin ajouté avec succès");
        afficherMedecins();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du médecin");
    }

    ui->tabmedecins->setModel(med.afficher());

}

void MainWindow::afficherMedecins()
{
    QSqlQueryModel *model = Medecin::afficher();  // Get the model from Medecin class

    if (model) {
        ui->tabmedecins->setModel(model);  // Set the model to the QTableView
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'affichage des médecins");
    }
}


void MainWindow::on_b_supp_clicked()
{

    Medecin med;
    (med.setId(ui->suppID->text().toUInt()));
    bool test = med.supprimer(med.getId());
    QMessageBox msgBox;
    if(test){
        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Suppression effectuée \n"),
                                 QMessageBox::Cancel); ui->tabmedecins->setModel(med.afficher());


    }
    else{ QMessageBox::critical(nullptr , QObject::tr("Not Ok "),QObject::tr("Suppression non effectuée\n"),
                              QMessageBox::Cancel);


    }
}



void MainWindow::on_pushButton_mod_clicked()
{
    int id = ui->lineEdit_id->text().toUInt();
    std::string nom = ui->lineEdit_21->text().toStdString();
    std::string prenom = ui->lineEdit_23->text().toStdString();
    std::string specialite = ui->lineEdit_25->text().toStdString(); // Conversion correcte
    std::string contact = ui->lineEdit_27->text().toStdString();

    Medecin med(id, nom, prenom, specialite, contact);

    bool test = med.modifier();
    if (test) {
        ui->tabmedecins->setModel(med.afficher());
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not Ok"), QObject::tr("Modification échouée.\n"
                                                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
    }
}

