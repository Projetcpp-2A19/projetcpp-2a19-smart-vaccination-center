#include "mainwindow.h"
#include "rendezvous.h"
#include "./ui_mainwindow.h"
#include <QMouseEvent>  // For detecting mouse events
#include <QShowEvent>
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
#include "sms.h"
#include "arduino.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow), networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);  // Setup UI from Qt Designer

    ui->dateEdit_22->setDate(QDate::currentDate());

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
    //envoyerRappelRendezVous();
    int ret=    A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
    case(-1):qDebug() << "arduino is not available";
    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
    //le slot update_label suite à la reception du signal readyRe
}



MainWindow::~MainWindow()
{
    delete ui;
    delete networkManager;
}
void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event); // Appel à la classe de base
    updateTableView();             // Mise à jour du tableau après affichage
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

    /* Vérifier que la date du rendez-vous est après la date du système*/
    if (date_rdv < QDate::currentDate()) {
        QMessageBox::warning(this, tr("Erreur"), tr("La date du rendez-vous doit être ultérieure à aujourd'hui."));
        return;
    }

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
    if (newDate < QDate::currentDate()) {
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
    QDate dateAuj = QDate::currentDate();
    QString dateStr = dateAuj.toString("yyyy-MM-dd");

    QSqlQuery query;
    query.prepare("SELECT id_rdv, date_rdv, TO_CHAR(heure_rdv, 'HH24:MI') AS heure_rdv, priorite_rdv, status, id_pat FROM RENDEZ_VOUS WHERE TRUNC(date_rdv) = TO_DATE(:date, 'YYYY-MM-DD')");
    query.bindValue(":date", dateStr);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la récupération des rendez-vous du jour.");
        return;
    }

    if (!query.next()) {
        QMessageBox::information(this, "Aucun rendez-vous", "Aucun rendez-vous trouvé pour aujourd'hui.");
        return;
    }

    // Revenir au début du résultat pour tout parcourir
    query.first();

    QString filePath = QFileDialog::getSaveFileName(this, "Exporter les RDV du jour en PDF", "", "Fichiers PDF (*.pdf)");
    if (filePath.isEmpty()) return;

    QTextDocument doc;
    QString html = "<h1 style='text-align:center; color:darkblue;'>Liste des Rendez-vous - " + dateAuj.toString("dd/MM/yyyy") + "</h1>";
    html += "<table border='1' cellspacing='0' cellpadding='5' style='width:100%; border-collapse: collapse;'>";
    html += "<tr style='background-color:#f2f2f2;'>";
    html += "<th>ID</th><th>Heure</th><th>Priorité</th><th>Statut</th><th>ID Patient</th></tr>";

    do {
        int id = query.value("id_rdv").toInt();
        QString heure = query.value("heure_rdv").toString();
        QString priorite = query.value("priorite_rdv").toString();
        QString statut = query.value("status").toString();
        int id_pat = query.value("id_pat").toInt();

        html += "<tr>";
        html += "<td>" + QString::number(id) + "</td>";
        html += "<td>" + heure + "</td>";
        html += "<td>" + priorite + "</td>";
        html += "<td>" + statut + "</td>";
        html += "<td>" + QString::number(id_pat) + "</td>";
        html += "</tr>";
    } while (query.next());

    html += "</table>";
    doc.setHtml(html);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    printer.setPageMargins(QMarginsF(10, 10, 10, 10));

    doc.print(&printer);

    QMessageBox::information(this, "Succès", "La liste des rendez-vous du jour a été exportée avec succès !");
}



// Exemple de fonction de tri des rendez-vous
void MainWindow::on_comboBox_38_currentIndexChanged(int index) {
    switch(index) {
    case 0:
        afficherRendezVous();  // Sans tri
        break;
    case 1:
        afficherRendezVousTrieParPriorite("ASC");
        break;
    case 2:
        afficherRendezVousTrieParPriorite("DESC");
        break;
    case 3:
        afficherRendezVousTrieParDate("ASC");
        break;
    case 4:
        afficherRendezVousTrieParDate("DESC");
        break;
    default:
        afficherRendezVous();  // fallback
        break;
    }
}

// Fonction qui affiche les rendez-vous sans tri spécifique
void MainWindow::afficherRendezVous() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM RENDEZ_VOUS");
    ui->tableau6->setModel(model);
}

// Fonction qui affiche les rendez-vous triés par priorité (Urgente > Moyenne > Normale)
void MainWindow::afficherRendezVousTrieParPriorite(const QString &ordre) {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM RENDEZ_VOUS ORDER BY "
                    "CASE priorite_rdv "
                    "WHEN 'Urgente' THEN 1 "
                    "WHEN 'Moyenne' THEN 2 "
                    "WHEN 'Normale' THEN 3 "
                    "ELSE 4 END " + ordre);
    ui->tableau6->setModel(model);
}

// Fonction qui affiche les rendez-vous triés par date
void MainWindow::afficherRendezVousTrieParDate(const QString &ordre) {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM RENDEZ_VOUS ORDER BY date_rdv " + ordre);
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
    ui->lineEdit_118->setPlaceholderText("Recherche par ID patient");  // Ajouter un texte d'aide
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
        qDebug() << "⚠️ WARNING: No data found for rendez-vous!";
    }

    int total = 0;
    for (auto val : statsType.values()) {
        total += val;
    }

    for (auto it = statsType.begin(); it != statsType.end(); ++it) {
        QPieSlice *slice = pieSeries->append(it.key(), it.value());
        double percentage = (double(it.value()) / total) * 100.0;
        slice->setLabel(QString("%1 - %2 (%3%)")
                            .arg(it.key())
                            .arg(it.value())
                            .arg(QString::number(percentage, 'f', 1)));
        slice->setLabelVisible(true);
    }

    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);
    pieChart->setTitle("📊 Répartition des rendez-vous par date");
    pieChart->legend()->setVisible(true);
    pieChart->legend()->setAlignment(Qt::AlignBottom);

    layout->addWidget(new QChartView(pieChart));

    qDebug() << "✅ Statistics updated successfully!";
}
/*void MainWindow::showStatistiques_rdv() {
    RendezVous R;
    if (!ui->chartContainer_rdv) {
        qDebug() << "❌ ERROR: chartContainer is NULL!";
        return;
    }

    // Mettre un layout horizontal (gauche: camembert, droite: courbe)
    if (!ui->chartContainer_rdv->layout()) {
        ui->chartContainer_rdv->setLayout(new QHBoxLayout());
    }

    // Nettoyer les anciens graphiques
    QLayoutItem* item;
    while ((item = ui->chartContainer_rdv->layout()->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    QHBoxLayout *layout = qobject_cast<QHBoxLayout*>(ui->chartContainer_rdv->layout());

    // ====================== 🍕 Graphique en camembert ======================
    QPieSeries *pieSeries = new QPieSeries();
    QMap<QString, int> statsType = R.getStatistiquesParDate();

    if (statsType.isEmpty()) {
        qDebug() << "⚠️ WARNING: No data found for rendez-vous!";
    }

    int total = 0;
    for (auto val : statsType.values()) {
        total += val;
    }

    for (auto it = statsType.begin(); it != statsType.end(); ++it) {
        QPieSlice *slice = pieSeries->append(it.key(), it.value());
        double percentage = (double(it.value()) / total) * 100.0;
        slice->setLabel(QString("%1 - %2 (%3%)")
                            .arg(it.key())
                            .arg(it.value())
                            .arg(QString::number(percentage, 'f', 1)));
        slice->setLabelVisible(true);
    }

    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);
    pieChart->setTitle("📊 Répartition des rendez-vous par date");
    pieChart->legend()->setVisible(true);
    pieChart->legend()->setAlignment(Qt::AlignBottom);

    layout->addWidget(new QChartView(pieChart));

    // ====================== 📈 Graphique en courbe ======================
    QLineSeries *lineSeries = new QLineSeries();
    QChart *lineChart = new QChart();

    int i = 0;
    QStringList categories;
    for (auto it = statsType.begin(); it != statsType.end(); ++it) {
        lineSeries->append(i, it.value());
        categories << it.key();
        ++i;
    }

    lineChart->addSeries(lineSeries);
    lineChart->setTitle("📈 Évolution des rendez-vous");

    QCategoryAxis *axisX = new QCategoryAxis();
    for (int j = 0; j < categories.size(); ++j) {
        axisX->append(categories[j], j);
    }
    axisX->setLabelsAngle(-45);
    axisX->setTitleText("Date");

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Nombre");

    lineChart->addAxis(axisX, Qt::AlignBottom);
    lineChart->addAxis(axisY, Qt::AlignLeft);
    lineSeries->attachAxis(axisX);
    lineSeries->attachAxis(axisY);

    layout->addWidget(new QChartView(lineChart));

    qDebug() << "✅ Camembert + Courbe générés avec succès !";
}
*/


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
    query.prepare("SELECT id_rdv, TO_CHAR(heure_rdv, 'HH24:MI') AS heure_rdv, priorite_rdv, status, id_pat FROM RENDEZ_VOUS WHERE date_rdv = TO_DATE(:date, 'YYYY-MM-DD')");
    query.bindValue(":date", date.toString("yyyy-MM-dd"));

    if (!query.exec()) {
        qDebug() << "Erreur SQL :" << query.lastError().text();
        return;
    }

    qDebug() << "Requête exécutée avec succès.";

    ui->tableWidget->setRowCount(0); // Effacer l'ancien contenu
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "ID" << "Heure" << "Priorité" << "Status" << "ID patient");

    int row = 0;

    while (query.next()) {
        qDebug() << "Données reçues -> ID:" << query.value(0).toInt()
            << ", Heure:" << query.value(1).toString()
            << ", Priorité:" << query.value(2).toString()
            << ", Status:" << query.value(3).toString()
            << ", ID patient:" << query.value(4).toString();

        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // ID
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // Heure
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // Priorité
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(query.value(3).toString())); // Status
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(query.value(4).toString())); // id_pat
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


void MainWindow::on_pushButton_187_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT p.tel, r.date_rdv, r.heure_rdv "
                  "FROM RENDEZ_VOUS r "
                  "JOIN PATIENTS p ON r.id_pat = p.id_pat");

    if (!query.exec()) {
        qDebug() << "Erreur SQL :" << query.lastError().text();
        return;
    }

    bool found = false;

    while (query.next()) {
        found = true;
        QString tel = query.value(0).toString();
        QString internationalNumber = "+216" + tel;  // Ajout du préfixe
        QDate date = query.value(1).toDate();
        QTime heure = query.value(2).toTime();

        QString message = QString("Bonjour, ceci est un rappel de votre rendez-vous prévu le %1 à %2.")
                              .arg(date.toString("dd/MM/yyyy"))
                              .arg(heure.toString("HH:mm"));

        sms s;
        s.sendSMS(internationalNumber, message);

        qDebug() << "SMS envoyé à :" << tel << "Message:" << message;
    }

    if (!found) {
        qDebug() << "Aucun rendez-vous trouvé dans la base de données.";
    }
}
