#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMouseEvent>  // For detecting mouse events
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include "Vaccin.h"
#include <QMessageBox>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  // Setup UI from Qt Designer

    connect(ui->exit, &QPushButton::clicked, this, &MainWindow::close);

    ui->tableau->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau5->setModel(vac.afficher());
}

MainWindow::~MainWindow()
{
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









void MainWindow::on_submit_clicked()
{
    QDate currentDate = QDate::currentDate();
    ui->d2->setDate(QDate::currentDate());

    QString nom = ui->nom->text();
    QString type = ui->type->currentText();
    QString fabricant = ui->fab->text();
    QDate dateFabrication = ui->d1->date();
    QDate dateExpiration = ui->d2->date();
    double temperature = ui->temp->text().toDouble();
    QString paysOrigine = ui->pays->text();
    int stock = ui->stock->text().toInt();


    if (nom.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Le nom ne peut pas être vide !");
    } else if (type.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Le type ne peut pas être vide !");
    } else if (fabricant.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Le fabricant ne peut pas être vide !");
    } else if (dateFabrication > dateExpiration) {
        QMessageBox::critical(this, "Erreur", "La date d'expiration doit être après la date de fabrication !");
    } else if (temperature < -100 || temperature > 100) {
        QMessageBox::critical(this, "Erreur", "Température invalide !");
        ui->temp->clear();
    } else if (paysOrigine.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Le pays d'origine ne peut pas être vide !");
    } else if (stock < 0) {
        QMessageBox::critical(this, "Erreur", "Le stock ne peut pas être négatif !");
        ui->stock->clear();
    } else {
        Vaccin V (0, nom, type, fabricant, dateFabrication, dateExpiration, temperature, paysOrigine, stock);
        bool test = V.ajouter();

        if (test) {
            ui->tableau5->setModel(V.afficher());
            QMessageBox::information(nullptr, QObject::tr("Succès"),
                                     QObject::tr("Ajout effectué.\nClick Cancel pour fermer."), QMessageBox::Cancel);
            ui->nom->clear();
            ui->fab->clear();
            ui->d1->clear();
            ui->d2->clear();
            ui->temp->clear();
            ui->pays->clear();
            ui->stock->clear();
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Échec"),
                                  QObject::tr("Ajout non effectué.\nClick Cancel pour fermer."), QMessageBox::Cancel);
        }
    }


}


void MainWindow::on_del_clicked()
{
    // Récupérer l'ID sélectionné
    QModelIndex index = ui->tableau5->selectionModel()->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Suppression"), tr("Veuillez sélectionner un élément à supprimer."));
        return;
    }

    int id = ui->tableau5->model()->data(ui->tableau5->model()->index(index.row(), 0)).toInt();  // Supposons que l'ID est en 1ère colonne

    // Confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Suppression"), tr("Voulez-vous vraiment supprimer cet élément ?"),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        Vaccin r;
        if (r.supprimer(id)) {
            QMessageBox::information(this, tr("Suppression"), tr("Suppression réussie."));
            ui->tableau5->setModel(vac.afficher());


        } else {
            QMessageBox::critical(this, tr("Erreur"), tr("Échec de la suppression."));
        }
    }

}


void MainWindow::on_pushButton_159_clicked()
{
    if(mod==0){
        // Récupérer l'ID sélectionné
        QModelIndex index = ui->tableau5->selectionModel()->currentIndex();
        if (!index.isValid()) {
            QMessageBox::warning(this, tr("Modifier"), tr("Veuillez sélectionner un élément à Modifier."));
            return;
        }

        int id = ui->tableau5->model()->data(ui->tableau5->model()->index(index.row(), 0)).toInt();  // Supposons que l'ID est en 1ère colonne
        Vaccin v=vac.getVaccinById(id);
        ui->id->setText(QString::number(v.getId()));
        ui->nom->setText(v.getNom());
        ui->type->setCurrentText(v.getType());
        ui->fab->setText(v.getFabricant());
        ui->d1->setDate(v.getDateFabrication());
        ui->d2->setDate(v.getDateExpiration());
        ui->temp->setText(QString::number(v.getTemperature()));
        ui->pays->setText(v.getPaysOrigine());
        ui->stock->setText(QString::number(v.getStock()));
        mod=1;
    }
    else{
        int id = ui->id->text().toInt();
        QString nom = ui->nom->text();
        QString type = ui->type->currentText();
        QString fabricant = ui->fab->text();
        QDate dateFabrication = ui->d1->date();
        QDate dateExpiration = ui->d2->date();
        double temperature = ui->temp->text().toDouble();
        QString paysOrigine = ui->pays->text();
        int stock = ui->stock->text().toInt();
        bool test = vac.modifier(id,nom,type,fabricant,dateFabrication,dateExpiration,temperature,paysOrigine,stock);
        if (test) {
            ui->tableau5->setModel(vac.afficher());
            QMessageBox::information(nullptr, QObject::tr("Succès"),
                                     QObject::tr("Modification effectué.\nClick Cancel pour fermer."), QMessageBox::Cancel);
            ui->nom->clear();
            ui->fab->clear();
            ui->d1->clear();
            ui->d2->clear();
            ui->temp->clear();
            ui->pays->clear();
            ui->stock->clear();
            ui->id->clear();
            mod=0;
        } else {
            mod=0;
            QMessageBox::critical(nullptr, QObject::tr("Échec"),
                                  QObject::tr("Modification non effectué.\nClick Cancel pour fermer."), QMessageBox::Cancel);
        }
    }
}

