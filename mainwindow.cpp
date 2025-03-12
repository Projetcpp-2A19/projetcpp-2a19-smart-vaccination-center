#include "mainwindow.h"
#include "rendezvous.h"
#include "./ui_mainwindow.h"
#include <QMouseEvent>  // For detecting mouse events
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QPrinter>
#include <QTextDocument>
#include <QSqlQuery>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  // Setup UI from Qt Designer

    connect(ui->exit, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->btnsupp, &QPushButton::clicked, this, &MainWindow::on_btnsupp_clicked);//supp
    RendezVous r;
    ui->tableau6->setModel(r.afficher() );

    // Reference the existing popupWidget from the UI (it should be named popupWidget in the designer)
    popupWidget = ui->popupWidget;

    // Optionally, set the position and size of the popup widget (can be customized)
    popupWidget->setGeometry(200, 100, 200, 100);  // Set position and size of the popup

    // Initially hide the popup
    popupWidget->hide();

    // Connect button click to show or hide the popup
    connect(ui->btnmedecin, &QPushButton::clicked, this, &MainWindow::on_btnmedecin_clicked);

    ui->tableau->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau6->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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

void MainWindow::updateTableView() {
    RendezVous r;
    ui->tableau6->setModel(r.afficher());  // Charger les nouvelles données
    ui->tableau6->viewport()->update();       // Rafraîchir l'affichage
}


void MainWindow::on_pushButton_180_clicked()
{
    QSqlQuery query;

    // Récupération des informations saisies dans les 3 champs
    int id_rdv = ui->lineEditID->text().toInt();
    QDate date_rdv = ui->dateEdit_22->date();
    QDate heure_rdv = ui->dateEdit_19->date();
    QString priorite_rdv = ui->comboBox_41->currentText();
    QString status = ui->comboBox_37->currentText();
    int id_pat = ui->lineEdit->text().toInt();

    // **🛑 Contrôle de saisie**
    if (id_rdv <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("L'ID du rendez-vous doit être un nombre positif."));
        return;
    }

    if (id_pat <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("L'ID du patient doit être un nombre positif."));
        return;
    }

    // Vérifier que la date du rendez-vous est après la date du système
    if (date_rdv <= QDate::currentDate()) {
        QMessageBox::warning(this, tr("Erreur"), tr("La date du rendez-vous doit être ultérieure à aujourd'hui."));
        return;
    }


    // Instancier un objet de la classe rendez vous
    RendezVous R (id_rdv, date_rdv, heure_rdv,priorite_rdv,status,id_pat);

    // Insérer l'objet rendez vous instancié dans la table rendez vous
    // et récupérer la valeur de retour de query.exec()
    bool test = R.ajouter();
    qDebug() << "Requête SQL : " << query.lastQuery();



    if (test) // Si requête exécutée ==> QMessageBox::information
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click Cancel to exit."),
                                 QMessageBox::Cancel);
        updateTableView();
    }
    else // Si requête non exécutée ==> QMessageBox::critical
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
    }

    QSqlQueryModel *model = R.afficher();  // Get the model from RendezVous class

    if (model) {
        ui->tableau6->setModel(model);  // Set the model to the QTableView
        updateTableView();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'affichage des RendezVous");
    }

}

void MainWindow::on_btnsupp_clicked() {
    // Récupérer l'ID sélectionné
    QModelIndex index = ui->tableau6->selectionModel()->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Suppression"), tr("Veuillez sélectionner un élément à supprimer."));
        return;
    }

    int id = ui->tableau6->model()->data(ui->tableau6->model()->index(index.row(), 0)).toInt();  // Supposons que l'ID est en 1ère colonne

    // Confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Suppression"), tr("Voulez-vous vraiment supprimer cet élément ?"),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        RendezVous r;
        if (r.supprimer(id)) {
            QMessageBox::information(this, tr("Suppression"), tr("Suppression réussie."));
            updateTableView();  // Rafraîchir la table après suppression
        } else {
            QMessageBox::critical(this, tr("Erreur"), tr("Échec de la suppression."));
        }
    }
}




void MainWindow::on_btnmodif_clicked() {
    // Récupérer la ligne sélectionnée
    QModelIndex index = ui->tableau6->selectionModel()->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Modification"), tr("Veuillez sélectionner un rendez-vous à modifier."));
        return;
    }

    // Récupérer les valeurs du tableau
    currentId = ui->tableau6->model()->data(ui->tableau6->model()->index(index.row(), 0)).toInt();
    originalDate = ui->tableau6->model()->data(ui->tableau6->model()->index(index.row(), 1)).toDate();
    originalHeure = ui->tableau6->model()->data(ui->tableau6->model()->index(index.row(), 2)).toDate();
    originalPriorite = ui->tableau6->model()->data(ui->tableau6->model()->index(index.row(), 3)).toString();
    originalStatus = ui->tableau6->model()->data(ui->tableau6->model()->index(index.row(), 4)).toString();
    originalIdPat = ui->tableau6->model()->data(ui->tableau6->model()->index(index.row(), 5)).toInt();

    // Remplir les champs de modification
    ui->dateEdit_22->setDate(originalDate);
    ui->dateEdit_19->setDate(originalHeure);
    ui->lineEdit->setText(QString::number(originalIdPat));

    // Définir la priorité dans le comboBox
    if (originalPriorite == "Normal")
        ui->comboBox_41->setCurrentIndex(0);
    else if (originalPriorite == "Moyenne")
        ui->comboBox_41->setCurrentIndex(1);
    else if (originalPriorite == "Urgente")
        ui->comboBox_41->setCurrentIndex(2);
    else
        ui->comboBox_41->setCurrentIndex(3);

    // Définir le statut
    if (originalStatus == "Programmer")
        ui->comboBox_37->setCurrentIndex(0);
    else if (originalStatus == "Annuler")
        ui->comboBox_37->setCurrentIndex(1);
    else
        ui->comboBox_37->setCurrentIndex(2);

    modificationInProgress = true; // Activation du mode modification
}

void MainWindow::on_btncmodif_clicked() {
    // Vérifier si l'utilisateur a sélectionné un rendez-vous à modifier
    if (!modificationInProgress) {
        QMessageBox::warning(this, tr("Erreur"), tr("Veuillez d'abord sélectionner un rendez-vous à modifier."));
        return;
    }

    // Récupérer les nouvelles valeurs
    QDate newDate = ui->dateEdit_22->date();
    QDate newHeure = ui->dateEdit_19->date();
    QString newPriorite = ui->comboBox_41->currentText();
    QString newStatus = ui->comboBox_37->currentText();
    int newIdPat = ui->lineEdit->text().toInt();

    // **🛑 Vérification des champs**
    if (newIdPat <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("L'ID du patient doit être un nombre positif."));
        return;
    }

    // **🛑 Vérification de la date**
    if (newDate <= QDate::currentDate()) {
        QMessageBox::warning(this, tr("Erreur"), tr("La date du rendez-vous doit être ultérieure à aujourd'hui."));
        return;
    }

    // Vérifier si aucune modification n'a été faite
    if (newDate == originalDate && newHeure == originalHeure &&
        newPriorite == originalPriorite && newStatus == originalStatus && newIdPat == originalIdPat) {
        QMessageBox::information(this, tr("Modification"), tr("Aucune modification apportée."));
        return;
    }

    // Créer un objet `RendezVous` mis à jour
    RendezVous rdv(currentId, newDate, newHeure, newPriorite, newStatus, newIdPat);
    if (rdv.modifier(currentId)) {
        QMessageBox::information(this, tr("Modification"), tr("Modification réussie."));
        updateTableView();  // Mettre à jour l'affichage

        modificationInProgress = false; // Réinitialisation du mode modification
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de la modification."));
    }
}



void MainWindow::on_btnrendezv4_clicked()
{
    QModelIndex index = ui->tableau6->selectionModel()->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Suppression"), tr("Veuillez sélectionner un élément à supprimer."));
        return;
    }

    int id = ui->tableau6->model()->data(ui->tableau6->model()->index(index.row(), 0)).toInt();  // Supposons que l'ID est en 1ère colonne


    QSqlQuery query;
    query.prepare("SELECT id_rdv, date_rdv, heure_rdv, priorite_rdv, status, id_pat FROM RENDEZ_VOUS WHERE id_rdv = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la récupération des données du rendez-vous.");
        return;
    }

    if (!query.next()) {
        QMessageBox::warning(this, "Erreur", "Aucun rendez-vous trouvé avec cet ID.");
        return;
    }

    QString date_rdv = query.value("date_rdv").toString();
    QString heure_rdv = query.value("heure_rdv").toString();
    QString priorite_rdv = query.value("priorite_rdv").toString();
    QString status = query.value("status").toString();
    int id_pat = query.value("id_pat").toInt();

    QString filePath = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");
    if (filePath.isEmpty()) {
        return;
    }

    // Création du document HTML pour le PDF
    QTextDocument doc;
    QString html = "<h1 style='text-align:center; color:blue;'>Détails du Rendez-vous</h1>";
    html += "<table border='1' cellspacing='0' cellpadding='5' style='width:100%; border-collapse: collapse;'>";
    html += "<tr><th style='background-color: #f2f2f2;'>Champ</th><th>Valeur</th></tr>";
    html += "<tr><td><b>ID :</b></td><td>" + QString::number(id) + "</td></tr>";
    html += "<tr><td><b>Date :</b></td><td>" + date_rdv + "</td></tr>";
    html += "<tr><td><b>Heure :</b></td><td>" + heure_rdv + "</td></tr>";
    html += "<tr><td><b>Priorité :</b></td><td>" + priorite_rdv + "</td></tr>";
    html += "<tr><td><b>Statut :</b></td><td>" + status + "</td></tr>";
    html += "<tr><td><b>ID Patient :</b></td><td>" + QString::number(id_pat) + "</td></tr>";
    html += "</table>";

    doc.setHtml(html);

    // Création et configuration de l'imprimante PDF
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    printer.setPageMargins(QMarginsF(10, 10, 10, 10));

    // Impression du document dans le fichier PDF
    doc.print(&printer);

    QMessageBox::information(this, "Succès", "Données exportées en PDF avec succès !");
}
