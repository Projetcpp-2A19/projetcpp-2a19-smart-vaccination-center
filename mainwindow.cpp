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
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QVBoxLayout>
#include <QSqlError>
#include <QTextCharFormat>
#include <QDebug>
#include <QDate>
#include <QTime>
#include <QTableWidgetItem>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow), networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);  // Setup UI from Qt Designer

    connect(ui->exit, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->btnsupp, &QPushButton::clicked, this, &MainWindow::on_btnsupp_clicked);//supp

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
    RendezVous R;
    QSqlQueryModel *model = R.afficher();  // Get the model from RendezVous class

    if (model) {
        ui->tableau6->setModel(model);  // Set the model to the QTableView
        updateTableView();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'affichage des RendezVous");
    }
    envoyerRappelRendezVous();
}



MainWindow::~MainWindow()
{
    delete ui;
    delete networkManager;
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
    QTime heure_rdv = ui->dateEdit_19->time();
    QString priorite_rdv = ui->comboBox_41->currentText();
    QString status = ui->comboBox_37->currentText();
    int id_pat = ui->lineEdit->text().toInt();

    //  Contrôle de saisie**
    if (id_rdv <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("L'ID du rendez-vous doit être un nombre positif."));
        return;
    }

    if (id_pat <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("L'ID du patient doit être un nombre positif."));
        return;
    }

    /* Vérifier que la date du rendez-vous est après la date du système
    if (date_rdv <= QDate::currentDate()) {
        QMessageBox::warning(this, tr("Erreur"), tr("La date du rendez-vous doit être ultérieure à aujourd'hui."));
        return;
    }*/

    // Vérifier que l'heure du rendez-vous est entre 09:00 et 16:00
    if (heure_rdv < QTime(9, 0) || heure_rdv > QTime(23, 0)) {
        QMessageBox::warning(this, tr("Erreur"), tr("L'heure du rendez-vous doit être entre 09:00 et 16:00."));
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
    originalHeure = ui->tableau6->model()->data(ui->tableau6->model()->index(index.row(), 2)).toTime();
    originalPriorite = ui->tableau6->model()->data(ui->tableau6->model()->index(index.row(), 3)).toString();
    originalStatus = ui->tableau6->model()->data(ui->tableau6->model()->index(index.row(), 4)).toString();
    originalIdPat = ui->tableau6->model()->data(ui->tableau6->model()->index(index.row(), 5)).toInt();

    // Remplir les champs de modification
    ui->dateEdit_22->setDate(originalDate);
    ui->dateEdit_19->setTime(originalHeure);
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
    //int currentId = ui->tableau6->;
    QDate newDate = ui->dateEdit_22->date();
    QTime newHeure = ui->dateEdit_19->time();
    QString newPriorite = ui->comboBox_41->currentText();
    QString newStatus = ui->comboBox_37->currentText();
    int newIdPat = ui->lineEdit->text().toInt();

    //  Vérification des champs**
    if (newIdPat <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("L'ID du patient doit être un nombre positif."));
        return;
    }

    //  Vérification de la date**
    if (newDate <= QDate::currentDate()) {
        QMessageBox::warning(this, tr("Erreur"), tr("La date du rendez-vous doit être ultérieure à aujourd'hui."));
        return;
    }

    //  Vérification de l'heure**
    if (newHeure < QTime(9, 0) || newHeure > QTime(16, 0)) {
        QMessageBox::warning(this, tr("Erreur"), tr("L'heure du rendez-vous doit être entre 09:00 et 16:00."));
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


// Exemple de fonction de tri des rendez-vous
void MainWindow::on_comboBox_38_currentIndexChanged(int index) {
    if (index == 0) {
        afficherRendezVous(); // Affichage par défaut
    } else if (index == 1) {
        afficherRendezVousTrieParPriorite(); // Trier par priorité
    } else if (index == 2) {
        afficherRendezVousTrieParDate(); // Trier par date
    }
}

// Fonction qui affiche les rendez-vous sans tri spécifique
void MainWindow::afficherRendezVous() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM RENDEZ_VOUS");
    ui->tableau6->setModel(model);
}

// Fonction qui affiche les rendez-vous triés par priorité (Urgente > Moyenne > Normale)
void MainWindow::afficherRendezVousTrieParPriorite() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM RENDEZ_VOUS ORDER BY "
                    "CASE priorite_rdv "
                    "WHEN 'Urgente' THEN 1 "
                    "WHEN 'Moyenne' THEN 2 "
                    "WHEN 'Normale' THEN 3 "
                    "ELSE 4 END");

    ui->tableau6->setModel(model);
}

// Fonction qui affiche les rendez-vous triés par date
void MainWindow::afficherRendezVousTrieParDate() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM RENDEZ_VOUS ORDER BY date_rdv ASC");
    ui->tableau6->setModel(model);
}


void MainWindow::on_lineEdit_118_textChanged(const QString &searchTerm) {
    RendezVous R;
    QSqlQueryModel* model = nullptr;
    if (searchTerm.trimmed().isEmpty()) {
        // Si la barre de recherche est vide, afficher tous les rendez-vous
        ui->tableau6->setModel(R.afficher());
    } else {
        // Sinon, filtrer les résultats
        ui->tableau6->setModel(R.rechercher(searchTerm));
    }
    ui->lineEdit_118->setPlaceholderText("Recherche par status ou ID patient");  // Ajouter un texte d'aide
    connect(ui->lineEdit_118, &QLineEdit::textChanged, this, &MainWindow::on_lineEdit_118_textChanged);
}


void MainWindow::showStatistiques_rdv() {
    RendezVous R;
    if (!ui->chartContainer_rdv) {
        qDebug() << "❌ ERROR: chartContainer is NULL!";
        return;
    }

    // Ensure chartContainer has a layout
    if (!ui->chartContainer_rdv->layout()) {
        ui->chartContainer_rdv->setLayout(new QVBoxLayout());  // Assign a layout if missing
    }

    // Remove old charts
    QLayoutItem* item;
    while ((item = ui->chartContainer_rdv->layout()->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->chartContainer_rdv->layout());


    // 📊 Pie Chart (Type Distribution)
    QPieSeries *pieSeries = new QPieSeries();
    QMap<QString, int> statsType = R.getStatistiquesParDate();
    if (statsType.isEmpty()) {
        qDebug() << "⚠️ WARNING: No data found for equipment types!";
    }
    for (auto it = statsType.begin(); it != statsType.end(); ++it) {
        pieSeries->append(it.key(), it.value());
    }
    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);
    pieChart->setTitle("Répartition des rendez-vous par date");
    layout->addWidget(new QChartView(pieChart));

    ui->chartContainer_rdv->setLayout(new QVBoxLayout());
    qDebug() << "✅ Statistics updated successfully!";
}





void MainWindow::on_btnrendezv2_clicked(){
    qDebug() << "Button btnequiprmrnt2 clicked!";
    if (!ui->chartContainer_rdv) {                             //ken chartContainer mouch mawjouda
        qDebug() << "ERROR: chartContainer is NULL!";
        return;
    }

    showStatistiques_rdv();

    qDebug() << "Statistics loaded successfully!";
    ui->sqs->setCurrentIndex(15);
}



void MainWindow::chargerRendezVousDansCalendrier() {
    QSqlQuery query("SELECT date_rdv, priorite_rdv FROM RENDEZ_VOUS");

    while (query.next()) {
        QDate date = query.value(0).toDate();
        QString priorite = query.value(1).toString();

        QTextCharFormat format;
        if (priorite == "Urgente") {
            format.setBackground(Qt::red);
        } else if (priorite == "Moyenne") {
            format.setBackground(QColor(255, 165, 0));
        } else { // normal
            format.setBackground(Qt::yellow);
        }
        ui->calendarWidget->setDateTextFormat(date, format);
    }
}
void MainWindow::on_calendarWidget_clicked(const QDate &date) {
    QSqlQuery query;
    query.prepare("SELECT id_rdv, heure_rdv, priorite_rdv, status FROM RENDEZ_VOUS WHERE date_rdv = TO_DATE(:date, 'YYYY-MM-DD')");
    query.bindValue(":date", date.toString("yyyy-MM-dd"));

    if (!query.exec()) {
        qDebug() << "Erreur SQL :" << query.lastError().text();
        return;
    }

    qDebug() << "Requête exécutée avec succès.";

    ui->tableWidget->setRowCount(0); // Effacer l'ancien contenu
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "ID" << "Heure" << "Priorité" << "Status");

    int row = 0;

    while (query.next()) {
        qDebug() << "Données reçues -> ID:" << query.value(0).toInt()
            << ", Heure:" << query.value(1).toString()
            << ", Priorité:" << query.value(2).toString()
            << ", Status:" << query.value(3).toString();

        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // ID
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // Heure
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // Priorité
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString())); // Status
        row++;
    }

    if (row == 0) {
        qDebug() << "Aucun rendez-vous trouvé pour cette date.";
    }
}

void MainWindow::on_btnrendezv3_clicked() {
    chargerRendezVousDansCalendrier();
    ui->sqs->setCurrentIndex(16 );
}

/*void MainWindow::envoyerRappelRendezVous() {
    QSqlQuery query;
    query.prepare("SELECT p.tel, r.date_rdv, r.heure_rdv "
                  "FROM RENDEZ_VOUS r "
                  "JOIN PATIENTS p ON r.id_pat = p.id_pat "
                  );

    if (!query.exec()) {
        QMessageBox::warning(this, "Erreur", "Échec de récupération des rendez-vous : " + query.lastError().text());
        return;
    }

    QString accountSID = "AC76504e48b30a646ff4be149648929856";
    QString authToken = "179d814c8c2028957a73e404e421c333";
    QString twilioNumber = "+16602286692";  // Ajoute le préfixe international ici

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    while (query.next()) {
        QString phoneNumber = query.value(0).toString().trimmed();
        QString dateRdv = query.value(1).toDate().toString("yyyy-MM-dd");
        QString heureRdv = query.value(2).toTime().toString("hh:mm");

        if (phoneNumber.length() != 8) { // Vérifie que c'est bien un numéro tunisien
            qDebug() << "Numéro de téléphone invalide : " << phoneNumber;
            continue;
        }

        QString message = "Rappel : Vous avez un rendez-vous aujourd'hui à " + heureRdv;

        // Construire la requête HTTP pour Twilio
        QNetworkRequest request(QUrl("https://api.twilio.com/2010-04-01/Accounts/" + accountSID + "/Messages.json"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

        QUrlQuery params;
        params.addQueryItem("To", "+216" + phoneNumber); // Ajout du préfixe de la Tunisie
        params.addQueryItem("From", twilioNumber);
        params.addQueryItem("Body", message);

        QByteArray postData = params.query().toUtf8();
        request.setRawHeader("Authorization", "Basic " + QByteArray(QString(accountSID + ":" + authToken).toUtf8()).toBase64());

        // Envoyer la requête POST
        QNetworkReply *reply = manager->post(request, postData);
        connect(reply, &QNetworkReply::finished, [reply]() {
            if (reply->error() == QNetworkReply::NoError) {
                qDebug() << "SMS envoyé avec succès !";
            } else {
                qDebug() << "Erreur d'envoi du SMS :" << reply->errorString();
            }
            reply->deleteLater();
        });
    }
}


void MainWindow::on_pushButton_187_clicked() {
    envoyerRappelRendezVous();
}
*/
void MainWindow::envoyerRappelRendezVous() {
    QSqlQuery query;
    query.prepare("SELECT p.tel, r.date_rdv, r.heure_rdv "
                  "FROM RENDEZ_VOUS r "
                  "JOIN PATIENTS p ON r.id_pat = p.id_pat "
                  "WHERE r.date_rdv = CURRENT_DATE AND r.heure_rdv >= (CURRENT_TIME + INTERVAL '2' HOUR)");

    if (!query.exec()) {
        QMessageBox::warning(this, "Erreur", "Échec de récupération des rendez-vous : " + query.lastError().text());
        return;
    }

    QString accountSID = "AC76504e48b30a646ff4be149648929856";
    QString authToken = "179d814c8c2028957a73e404e421c333";
    QString twilioNumber = "+16602286692";  // Ajoute le préfixe international ici

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    while (query.next()) {
        QString phoneNumber = query.value(0).toString().trimmed();
        QString dateRdv = query.value(1).toDate().toString("yyyy-MM-dd");
        QString heureRdv = query.value(2).toTime().toString("hh:mm");

        if (phoneNumber.length() != 8) { // Vérifie que c'est bien un numéro tunisien
            qDebug() << "Numéro de téléphone invalide : " << phoneNumber;
            continue;
        }

        QString message = "Rappel : Vous avez un rendez-vous aujourd'hui à " + heureRdv;

        // Construire la requête HTTP pour Twilio
        QNetworkRequest request(QUrl("https://api.twilio.com/2010-04-01/Accounts/" + accountSID + "/Messages.json"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

        QUrlQuery params;
        params.addQueryItem("To", "+216" + phoneNumber); // Ajout du préfixe de la Tunisie
        params.addQueryItem("From", twilioNumber);
        params.addQueryItem("Body", message);

        QByteArray postData = params.query().toUtf8();
        request.setRawHeader("Authorization", "Basic " + QByteArray(QString(accountSID + ":" + authToken).toUtf8()).toBase64());

        // Envoyer la requête POST
        QNetworkReply *reply = manager->post(request, postData);
        connect(reply, &QNetworkReply::finished, [reply]() {
            if (reply->error() == QNetworkReply::NoError) {
                qDebug() << "SMS envoyé avec succès !";
            } else {
                qDebug() << "Erreur d'envoi du SMS :" << reply->errorString();
            }
            reply->deleteLater();
        });
    }
}
