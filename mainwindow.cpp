#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMouseEvent>  // For detecting mouse events
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QDate>
#include <QStandardPaths>
#include <QDesktopServices>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QVBoxLayout>
#include <QPainter>
#include <QProgressBar>
#include <QPdfWriter>
#include <QFileDialog>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QPageSize>
#include <QFont>
#include <QLabel>
#include <QDebug>
#include <QTableWidgetItem>
#include <QMouseEvent>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QSignalBlocker>
#include <QTextDocument>
#include <QFileDialog>
#include <QPrinter>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>
#include <QProcess>
#include <QDate>
#include "Vaccin.h"
#include "Medecin.h"
#include "arduino.h"



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
#include "rendezvous.h"
#include "sms1.h"



//SI CHAHD
#include <QMouseEvent>  // For detecting mouse events
#include <QHBoxLayout>
#include <QWidget>
#include "lab.h"
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QVBoxLayout>
#include <QQmlContext>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QQmlApplicationEngine>
#include <QPdfWriter>
#include <QPainter>
#include <QSqlQuery>
#include <QMessageBox>
#include <QFileDialog>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>


#include "markermodel.h"

#include <cstdlib>  // Pour rand() et srand()
#include <ctime>    // Pour time()
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QChart>
#include "connection.h"
#include <QGraphicsOpacityEffect>
#include <QTemporaryFile>
#include <QBuffer>
#include <QImage>
#include <QFile>
#include <QSslSocket>
#include "patient.h"
#include "qrcode/qrcodegen.hpp"
#include "qrcode/qrcodegen.cpp"
using qrcodegen::QrCode;
using qrcodegen::QrSegment;



void logToFile(const QString &event, const QString &details) {
    QFile file("app_log.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString timestamp = QDateTime::currentDateTime().toString("[yyyy-MM-dd HH:mm:ss] ");
        out << timestamp << event << ": " << details << "\n";
        file.close();
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  // Setup UI from Qt Designer

    connect(ui->btnmedecin3_3, &QPushButton::clicked, this, &MainWindow::afficherStat);
    connect(ui->btnmedecin3, &QPushButton::clicked, this, &MainWindow::exporterPDF);

    ui->comboBox_question->addItems({
        "Quel est le nom de votre premier animal ?",
        "Quel est votre plat préféré ?",
        "Quel est le prénom de votre meilleur ami d'enfance ?",
        "Quel est le nom de votre première école ?"
    });

    ui->comboSpecialite->addItems({
        "Biologie Médicale",
        "Microbiologie",
        "Hématologie",
        "Immunologie",
        "Biochimie",
        "Toxicologie",
        "Parasitologie",
        "Virologie",
        "Génétique Médicale",
        "Anatomopathologie"
    });
    connect(ui->exit, &QPushButton::clicked, this, &MainWindow::close);


    //popupWidget = ui->popupWidget;

    // Optionally, set the position and size of the popup widget (can be customized)
    //popupWidget->setGeometry(200, 100, 200, 100);  // Set position and size of the popup

    // Initially hide the popup
    //popupWidget->hide();

    // Connect button click to show or hide the popup
    connect(ui->btnmedecin, &QPushButton::clicked, this, &MainWindow::on_btnmedecin_clicked);

    ui->tableau->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tableau4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableauEquipements->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tableau6_2_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //partie vaccin
    ui->tableau5->setModel(vac.afficher());
    connect(ui->exit, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::applyFilter);
    connect(ui->sortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onSortChanged);
    //end partie vaccin

    /*connect(ui->pdfButton, &QPushButton::clicked, this, &MainWindow::on_pdfButton_clicked);
 /*   Medecin M ;
    QSqlQueryModel *model = M.afficher();  // Get the model from RendezVous class

    if (model) {
        ui->tabmedecins->setModel(model);  // Set the model to the QTableView
        updateTableView();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'affichage des RendezVous");
    }*/

        connect(ui->pushButton_116, &QPushButton::clicked, this, &MainWindow::ajouterMedecin);
    afficherMedecins();
    /*int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
    case(-1):qDebug() << "arduino is not available";
    }*/






    ui->dateEdit_24->setDate(QDate::currentDate());

    //connect(ui->exit, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->btnsupp_2, &QPushButton::clicked, this, &MainWindow::on_btnsupp_2_clicked);//supp

    // Reference the existing popupWidget from the UI (it should be named popupWidget in the designer)
    //popupWidget = ui->popupWidget;

    // Optionally, set the position and size of the popup widget (can be customized)
    //popupWidget->setGeometry(200, 100, 200, 100);  // Set position and size of the popup

    // Initially hide the popup
    //popupWidget->hide();

    // Connect button click to show or hide the popup
    connect(ui->btnmedecin, &QPushButton::clicked, this, &MainWindow::on_btnmedecin_clicked);


    ui->tableau6_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    RendezVous R;
    QSqlQueryModel *model = R.afficher();  // Get the model from RendezVous class

    if (model) {
        ui->tableau6_2->setModel(model);  // Set the model to the QTableView
        updateTableViewRV();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'affichage des RendezVous");
    }
    //envoyerRappelRendezVous();
    A.connect_arduino();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::verifierIDDepuisArduino);
    timer->start(200);

//*******************************************************************************
    //*****************************************************************
    //***********************chahd


    // Initialisation du gestionnaire de réseau conexion a gecodage
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onGeoCodeReply);

    // Appeler la fonction de géocodage avec l'adresse "Tunis"
    getCoordinatesFromAddress("Tunis");  // Demander les coordonnées de Tunis

    // Connexion du modèle de marqueurs à QML
    qRegisterMetaType<QGeoCoordinate>("QGeoCoordinate");
    QQuickWidget *quickWidget = ui->maps;
    quickWidget->rootContext()->setContextProperty("mainWindow", this);
    quickWidget->rootContext()->setContextProperty("markerModel", &m_markerModel);
    quickWidget->setSource(QUrl("qrc:/map.qml"));
    quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

    // Connecter le signal d'erreur pour le débogage
    connect(quickWidget, &QQuickWidget::statusChanged, this, [quickWidget]() {
        if (quickWidget->status() == QQuickWidget::Error) {
            qWarning() << "Erreur lors du chargement du QML :";
            for (const auto &error : quickWidget->errors()) {
                qWarning() << error.toString();
            }
        }
    });
    quickWidget->rootContext()->setContextProperty("markerModel", &m_markerModel);


    // Configuration d'autres éléments de l'interface
    connect(ui->btnRechercher_labo, &QPushButton::clicked, this, &MainWindow::rechercher_labo);
    connect(ui->btnlabo5, &QPushButton::clicked, this, &MainWindow::on_btnlabo5_clicked);
    connect(ui->chatbot, &QPushButton::clicked, this, &MainWindow::analyserCommande);
    connect(ui->btnSupprimer_labo, &QPushButton::clicked, this, &MainWindow::on_btnSupprimer_labo_clicked);

    Lab Etmp;
    ui->tableau->setModel(Etmp.afficher_chahd());






    //----------------------------------------------------------------------------------------------------------------------------sadek
    ui->lineEdit_54->setPlaceholderText("Recherche");  // Set search hint
    connect(ui->lineEdit_54, &QLineEdit::textChanged, this, &MainWindow::on_lineEdit_54_textChanged);
    ui->tableauEquipements->setModel(equipement.afficher()); // or trier("Par défaut")
    ui->tableauEquipements->setSortingEnabled(true);
    ui->tableauEquipements->sortByColumn(0, Qt::AscendingOrder); // optional default sort

    updateTableViewEquipement();

    ui->dateEdit_11->clear();             // Clear the date field (remains empty)
    ui->dateEdit_11->setEnabled(false);     // Disable user interaction
    ui->dateEdit_11->setVisible(false);
    ui->label_2009->setVisible(false);
    //connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(update_fridge_status()));

    //malek
    connect(ui->tri, &QPushButton::clicked, this, &MainWindow::on_tri_clicked);
    connect(ui->listpatient, &QPushButton::clicked, this, &MainWindow::on_listpatient_clicked);
    connect(ui->recherche, &QPushButton::clicked, this, &MainWindow::on_recherche_clicked);
    ui->tableau3_4->setColumnCount(8);
    ui->tableau3_4->setHorizontalHeaderLabels({"ID", "Nom", "Prénom", "Date Naissance", "Email", "Genre", "Adresse", "Groupe Sanguin"});
    ui->tableau3_4->setSelectionBehavior(QAbstractItemView::SelectRows);

    /*Connection c;
    c.createconnect();
    int ret = A.connect_arduino();
    switch (ret) {
    case 0: qDebug() << "Arduino connecté sur :" << A.getarduino_port_name(); break;
    case 1: qDebug() << "Arduino détecté mais non connecté !"; break;
    case -1: qDebug() << "Arduino non disponible !"; break;
    }

    update_fridge_status();*/
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
    qDebug() << "Button btnequiprmrnt2 clicked!";
    if (!ui->chartContainer_labo) {                             //ken chartContainer mouch mawjouda
        qDebug() << "ERROR: chartContainer is NULL!";
        return;
    }

    showStatistiques_labo();

    qDebug() << "Statistics loaded successfully!";
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
    showStatistiques();
    ui->sqs->setCurrentIndex(12);
}

void MainWindow::on_btnequiprmrnt3_clicked()
{
    ui->sqs->setCurrentIndex(13);
}

void MainWindow::on_btnvaccins2_clicked()
{
    showStockPieChart();
    //ui->sqs->setCurrentIndex(14);
}
void MainWindow::updateTableView_labo() {
    ui->tableau->setModel(labo.afficher_chahd());  // Charger les nouvelles données
    ui->tableau->viewport()->update();       // Rafraîchir l'affichage
}

void MainWindow::on_comboBox_labo6_currentIndexChanged(int)
{
    trierParId_labo();
}



void MainWindow::updateTableView() {
    Medecin med;
    ui->tabmedecins->setModel(med.afficher());  // Charger les nouvelles données       // Rafraîchir l'affichage
    ui->tabmedecins->viewport()->update();       // Rafraîchir l'affichage
}



void MainWindow::ajouterMedecin()
{
    int id = ui->lineEdit_id->text().toInt();
    std::string nom = ui->lineEdit_21->text().toStdString();
    std::string prenom = ui->lineEdit_23->text().toStdString();
    std::string specialite = ui->comboSpecialite->currentText().toStdString();
    std::string contact = ui->lineEdit_27->text().toStdString();
    std::string mdp = ui->lineEdit_mdp->text().toStdString();
    std::string question = ui->comboBox_question->currentText().toStdString();
    std::string reponse = ui->lineEdit_reponse->text().toStdString();


    if (!Medecin::verifierChamps(id, nom, prenom, specialite, contact)) {
        QMessageBox::warning(this, "Erreur de saisie", "Veuillez entrer des informations valides !");
        return;
    }
    Medecin med(id, nom, prenom, specialite, contact,mdp, question, reponse );
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
    std::string specialite = ui->comboSpecialite->currentText().toStdString();
    std::string contact = ui->lineEdit_27->text().toStdString();
    std::string mdp = ui->lineEdit_mdp->text().toStdString();
    std::string question = ui->comboBox_question->currentText().toStdString();
    std::string reponse = ui->lineEdit_reponse->text().toStdString();


    Medecin med(id, nom, prenom, specialite, contact, mdp, question, reponse);
    bool test = med.modifier();
    if (test) {
        ui->tabmedecins->setModel(med.afficher());
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not Ok"), QObject::tr("Modification échouée.\n"
                                                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
    }
}



void MainWindow::on_comboBoxtri_currentIndexChanged(int index)
{
    Medecin M;

    switch (index) {
    case 0:
        /*QMessageBox::information(nullptr, QObject::tr("Ok"), QObject::tr("Tri par ID effectué.\n""Click Cancel to exit."), QMessageBox::Cancel);*/
        ui->tabmedecins->setModel(M.tri_id());
        break;
    case 1:
        /* QMessageBox::information(nullptr, QObject::tr("Ok"), QObject::tr("Tri par nom effectué.\n""Click Cancel to exit."), QMessageBox::Cancel);*/
        ui->tabmedecins->setModel(M.tri_nom());
        break;
    case 2:
        /*QMessageBox::information(nullptr, QObject::tr("Ok"), QObject::tr("Tri par prénom effectué.\n""Click Cancel to exit."), QMessageBox::Cancel);*/
        ui->tabmedecins->setModel(M.tri_prenom());
        break;
    }
}

void MainWindow::on_b_chercher_clicked()
{
    int id_chercher = ui->id_chercher->text().toInt();

    Medecin M;
    QSqlQueryModel* result = M.chercher(id_chercher);

    ui->tabmedecins->setModel(result);
}



/*
void MainWindow::afficherStatsSansChart() {
    qDebug() << "afficherStatsSansChart() appelée";

    std::map<std::string, int> stats = Medecin::statistiquesParSpecialite();
    qDebug() << "Nombre de spécialités récupérées :" << stats.size();
    for (const auto& pair : stats) {
        qDebug() << QString::fromStdString(pair.first) << ":" << pair.second;
    }

    QWidget *statsWindow = new QWidget();
    statsWindow->setWindowTitle("Statistiques des Médecins par Spécialité");

    QVBoxLayout *layout = new QVBoxLayout(statsWindow);

    for (const auto &entry : stats) {
        QLabel *label = new QLabel(QString::fromStdString(entry.first) + " (" + QString::number(entry.second) + ")");
        QProgressBar *progressBar = new QProgressBar();
        progressBar->setRange(0, 100);
        progressBar->setValue(entry.second * 10);  // Adapte selon le max
        layout->addWidget(label);
        layout->addWidget(progressBar);
    }

    statsWindow->setLayout(layout);
    statsWindow->resize(400, 300);
    statsWindow->show();
}
*/

void MainWindow::afficherStat()
{
    qDebug() << "afficherStatsSansChart() appelée";
    std::map<std::string, int> stats = Medecin::statistiquesParSpecialite();

    if (stats.empty()) {
        QMessageBox::information(this, "Statistiques", "Aucune donnée disponible.");
        return;
    }

    // Calculer le total pour les pourcentages
    int total = 0;
    for (const auto &entry : stats) {
        total += entry.second;
    }

    // Créer une fenêtre personnalisée
    QWidget *window = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(window);

    QLabel *title = new QLabel("Répartition des médecins par spécialité");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 20px; font-weight: bold; padding: 10px;");
    layout->addWidget(title);

    for (const auto &entry : stats) {
        QString specialite = QString::fromStdString(entry.first);
        int count = entry.second;
        int percentage = (total > 0) ? (count * 100 / total) : 0;

        // Conteneur horizontal
        QHBoxLayout *rowLayout = new QHBoxLayout();

        QLabel *label = new QLabel(specialite);
        label->setFixedWidth(150);
        label->setStyleSheet("font-weight: bold; font-size: 14px;");

        QProgressBar *progress = new QProgressBar();
        progress->setRange(0, 100);
        progress->setValue(percentage);
        progress->setTextVisible(true);
        progress->setFormat(QString("%1 (%2%)").arg(count).arg(percentage));
        progress->setStyleSheet(R"(
            QProgressBar {
                border: 1px solid #bbb;
                border-radius: 8px;
                background: #eee;
                height: 20px;
                font-size: 12px;
            }
            QProgressBar::chunk {
                background-color: #5AA897;
                border-radius: 8px;
            }
        )");

        rowLayout->addWidget(label);
        rowLayout->addWidget(progress);
        layout->addLayout(rowLayout);
    }

    layout->addStretch();
    window->setLayout(layout);
    window->resize(600, 400);
    window->setWindowTitle("Statistiques Médecins");
    window->show();
}

void MainWindow::exporterPDF() {
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty())
        return;

    QPdfWriter pdf(fileName);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setResolution(300);

    QPainter painter(&pdf);

    // Police et style
    QFont titleFont("Arial", 22, QFont::Bold);
    QFont headerFont("Arial", 12, QFont::Bold);
    QFont textFont("Arial", 11);

    // Titre
    painter.setFont(titleFont);
    painter.drawText(QRect(0, 0, pdf.width(), 100), Qt::AlignCenter, "🩺 Liste des Médecins");

    int topMargin = 130;
    int leftMargin = 50;
    int rowHeight = 40;
    int columnWidth = (pdf.width() - 2 * leftMargin) / 5;

    // En-têtes du tableau
    QStringList headers = {"ID", "Nom", "Prénom", "Spécialité"};
    painter.setFont(headerFont);
    painter.setBrush(QColor(220, 230, 250));  // Bleu clair
    painter.setPen(Qt::black);

    for (int i = 0; i < headers.size(); ++i) {
        painter.drawRect(leftMargin + i * columnWidth, topMargin, columnWidth, rowHeight);
        painter.drawText(leftMargin + i * columnWidth, topMargin, columnWidth, rowHeight, Qt::AlignCenter, headers[i]);
    }

    // Données depuis la base
    QSqlQuery query("SELECT id_med, nom_med, prenom_med, specialite_med FROM MEDECINS");
    int row = 1;

    painter.setFont(textFont);
    while (query.next()) {
        for (int col = 0; col < headers.size(); ++col) {
            QRect cellRect(leftMargin + col * columnWidth, topMargin + row * rowHeight, columnWidth, rowHeight);
            painter.drawRect(cellRect);
            painter.drawText(cellRect, Qt::AlignCenter, query.value(col).toString());
        }
        row++;
    }

    painter.end();

    QMessageBox::information(this, "Export PDF", "Le fichier a été exporté avec succès !");
}


//partie Vaccin
void MainWindow::on_submit_clicked()
{
    /*QDate currentDate = QDate::currentDate();
    ui->d2->setDate(QDate::currentDate());*/

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
            logToFile("Vaccine added", nom + ", " + type + ", " + paysOrigine);
            checkLowStockAndNotify(); // 🚨 Add this line
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
        Vaccin vacToDelete = vac.getVaccinById(id);
        Vaccin r;
        if (r.supprimer(id)) {
            logToFile("Vaccine deleted", vacToDelete.getNom() + ", " + vacToDelete.getType() + ", " + vacToDelete.getPaysOrigine()); // 📝 Log it
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
            bool test = vac.modifier(id,nom,type,fabricant,dateFabrication,dateExpiration,temperature,paysOrigine,stock);
            if (test) {
                ui->tableau5->setModel(vac.afficher());
                logToFile("Vaccine modified", nom + ", " + type + ", " + paysOrigine);
                checkLowStockAndNotify(); // 🚨 Add this line
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
}
void MainWindow::applyFilter(const QString &text)
{
    // Call the searchByName method from Vaccin class and update the model
    ui->sortComboBox->setCurrentIndex(0);
    ui->tableau5->setModel(vac.searchByName(text));
}
void MainWindow::onSortChanged(int index)
{
    ui->searchLineEdit->clear();

    QString orderBy;

    // Check the current index of the combo box and set the sorting column accordingly
    if (index == 0) {
        // "Default" selected - order by id_vac
        orderBy = "id_vac";
    } else if (index == 1) {
        // "Date de fabrication" selected - order by date_fabrication
        ui->sortComboBox->setCurrentIndex(1);
        orderBy = "date_fabrication";
    }

    // Update the model with the appropriate sorted query
    ui->tableau5->setModel(vac.afficher(orderBy));  // Call afficher with the orderBy column
}
void MainWindow::on_pdfButton_clicked()
{
    // Open save dialog
    QString filePath = QFileDialog::getSaveFileName(
        this,
        tr("Save PDF"),
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/vaccins.pdf",
        tr("PDF Files (*.pdf)")
        );
    if (filePath.isEmpty()) {
        return;
    }

    // Create PDF writer
    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize::A4);
    writer.setResolution(300);
    writer.setTitle(tr("Vaccin Report"));
    writer.setCreator("VAX Nest");

    QPainter painter(&writer);
    if (!painter.isActive()) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to create PDF."));
        return;
    }

    // Set fonts
    QFont headerFont = painter.font();
    headerFont.setBold(true);
    headerFont.setPointSize(10);

    QFont dataFont = painter.font();
    dataFont.setPointSize(9);

    // Layout parameters
    const int margin = 40;
    int yPos = margin;
    const int baseRowHeight = 50; // Minimum row height
    const int lineHeight = 20;
    const int cellPadding = 5;

    // Column widths (adjust according to your data)
    QVector<int> columnWidths = {120, 300, 300, 300, 300, 300, 300, 300, 300}; // ID, Name, Type, etc.

    // Get model data
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableau5->model());
    if (!model) {
        QMessageBox::critical(this, tr("Error"), tr("No data to export."));
        return;
    }

    // Draw title
    painter.setFont(headerFont);
    painter.drawText(margin, yPos, tr("Vaccination Report"));
    yPos += lineHeight * 2;

    // Draw current date
    painter.drawText(margin, yPos, tr("Generated on: ") + QDate::currentDate().toString(Qt::ISODate));
    yPos += lineHeight * 2;

    // Calculate total table width
    int tableWidth = std::accumulate(columnWidths.begin(), columnWidths.end(), 0);

    // Draw headers with background
    painter.setFont(headerFont);
    painter.setBrush(QBrush(Qt::lightGray));
    painter.setPen(Qt::NoPen);
    painter.drawRect(margin, yPos, tableWidth, baseRowHeight);

    painter.setPen(Qt::black);
    int xPos = margin;
    for (int col = 0; col < model->columnCount(); ++col) {
        QString header = model->headerData(col, Qt::Horizontal).toString();
        painter.drawText(QRect(xPos, yPos, columnWidths[col], baseRowHeight),
                         Qt::AlignCenter, header);
        xPos += columnWidths[col];
    }
    yPos += baseRowHeight;

    // Draw data rows with dynamic height
    painter.setFont(dataFont);
    for (int row = 0; row < model->rowCount(); ++row) {
        // First pass: calculate required row height
        int requiredRowHeight = baseRowHeight;

        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->data(model->index(row, col)).toString();

            // Special formatting for dates
            if (col == 4 || col == 5) { // Date columns
                QDate date = QDate::fromString(data, Qt::ISODate);
                if (date.isValid()) {
                    data = date.toString("dd/MM/yyyy");
                }
            }

            QRect textRect(0, 0, columnWidths[col] - 2*cellPadding, 0);
            QFontMetrics fm(dataFont);
            QRect boundingRect = fm.boundingRect(textRect, Qt::TextWordWrap, data);

            // Calculate how many lines we need
            int linesNeeded = ceil((double)boundingRect.height() / lineHeight);
            int cellHeight = linesNeeded * lineHeight;

            if (cellHeight > requiredRowHeight) {
                requiredRowHeight = cellHeight;
            }
        }

        // Check for page break before drawing row
        if (yPos + requiredRowHeight > writer.height() - margin) {
            writer.newPage();
            yPos = margin;

            // Redraw headers on new page
            painter.setFont(headerFont);
            painter.setBrush(QBrush(Qt::lightGray));
            painter.setPen(Qt::NoPen);
            painter.drawRect(margin, yPos, tableWidth, baseRowHeight);

            painter.setPen(Qt::black);
            xPos = margin;
            for (int col = 0; col < model->columnCount(); ++col) {
                QString header = model->headerData(col, Qt::Horizontal).toString();
                painter.drawText(QRect(xPos, yPos, columnWidths[col], baseRowHeight),
                                 Qt::AlignCenter, header);
                xPos += columnWidths[col];
            }
            yPos += baseRowHeight;

            painter.setFont(dataFont);
        }

        // Draw row background (alternating colors)
        painter.setBrush(QBrush(row % 2 ? Qt::white : QColor(240, 240, 240)));
        painter.setPen(Qt::NoPen);
        painter.drawRect(margin, yPos, tableWidth, requiredRowHeight);
        painter.setPen(Qt::black);

        // Draw cell contents with text wrapping
        xPos = margin;
        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->data(model->index(row, col)).toString();

            // Format dates
            if (col == 4 || col == 5) { // Date columns
                QDate date = QDate::fromString(data, Qt::ISODate);
                if (date.isValid()) {
                    data = date.toString("dd/MM/yyyy");
                }
            }

            QRect cellRect(xPos + cellPadding, yPos + cellPadding,
                           columnWidths[col] - 2*cellPadding, requiredRowHeight - 2*cellPadding);

            painter.drawText(cellRect, Qt::TextWordWrap | Qt::AlignVCenter, data);
            xPos += columnWidths[col];
        }

        yPos += requiredRowHeight;
    }

    painter.end();


    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}

void MainWindow::on_emailButton_clicked()
{

    SmtpClient smtp("smtp.gmail.com", 587, SmtpClient::TlsConnection);


    smtp.connectToHost();
    if (smtp.waitForReadyConnected()) {
        qDebug() << "Connected to the SMTP server!";


        smtp.login("3abedelsmadGathafi@gmail.com", "qbap zjeo obxj ixse", SmtpClient::AuthLogin);

        if (smtp.waitForAuthenticated()) {
            qDebug() << "Logged in successfully!";


            MimeMessage message;
            EmailAddress sender("3abedelsmadGathafi@gmail.com", "VAX NEST");
            message.setSender(sender);

            EmailAddress recipient("allanimohammed73@gmail.com", "Mohamed");
            message.addRecipient(recipient);

            message.setSubject("Stock Alert: Low Levels");

            MimeText *text = new MimeText();
            text->setText("Dear Admin,\n\nSome stock levels are getting low. Please review.\n\nBest regards,\nYour Application");
            message.addPart(text);


            smtp.sendMail(message);


            if (smtp.waitForMailSent()) {
                QMessageBox::information(this, "Email Sent", "Stock alert email has been sent successfully.");
            } else {
                QMessageBox::critical(this, "Mail Sending Error", "Failed to send the email.");
            }


            smtp.quit();
        } else {
            qDebug() << "Failed to log in to the SMTP server.";
            QMessageBox::critical(this, "Login Error", "Failed to log in to the SMTP server.");
        }
    } else {
        qDebug() << "Failed to connect to the SMTP server.";
        QMessageBox::critical(this, "Connection Error", "Failed to connect to the email server.");
    }
}



void MainWindow::on_sms_clicked()
{
    SmsSender sender("b7e5a19e50227693c9f5a908a1382769-dbfcdd8b-0e1d-4392-bd72-7c50d3600a4f", "447491163443");
    sender.sendSms("+21646598646", "Hello from Qt!");
    QMessageBox::critical(this, "Connection Error", "hi");

}


void MainWindow::sendStockAlertEmail(const QString &nom, const QString &type, const QString &pays, int stock) {
    SmtpClient smtp("smtp.gmail.com", 587, SmtpClient::TlsConnection);
    smtp.connectToHost();
    if (smtp.waitForReadyConnected()) {
        smtp.login("3abedelsmadGathafi@gmail.com", "qbap zjeo obxj ixse", SmtpClient::AuthLogin);
        if (smtp.waitForAuthenticated()) {
            MimeMessage message;
            EmailAddress sender("3abedelsmadGathafi@gmail.com", "AUTO VAX NEST");
            message.setSender(sender);

            EmailAddress recipient("allanimohammed73@gmail.com", "Mohamed");
            message.addRecipient(recipient);

            message.setSubject("Low Vaccine Stock Alert");

            QString content = QString("Dear Admin,\n\nStock for vaccine %1 (%2 - %3) is low.\nCurrent stock: %4 units.\n\nPlease restock soon.")
                                  .arg(nom, type, pays).arg(stock);

            MimeText *text = new MimeText();
            text->setText(content);
            message.addPart(text);

            qDebug() << "📤 Trying to send email...";
            smtp.sendMail(message);
            qDebug() << "✅ sendMail() called.";

            if (smtp.waitForMailSent()) {
                qDebug() << "📬 Email successfully sent.";
            } else {
                qDebug() << "❌ Failed to send email after calling sendMail.";
            }

            smtp.quit();
        } else {
            qDebug() << "❌ Failed to authenticate.";
        }
    } else {
        qDebug() << "❌ Failed to connect.";
    }
}



void MainWindow::checkLowStockAndNotify() {
    QSqlQuery query;
    query.prepare("SELECT nom_vac, type_vac, pays_origin, stock FROM vaccins WHERE stock <= 10");

    if (query.exec()) {
        while (query.next()) {
            QString nom = query.value(0).toString();
            QString type = query.value(1).toString();
            QString pays = query.value(2).toString();
            int stock = query.value(3).toInt();

            // Compose message
            QString details = QString("Vaccine %1 (%2 - %3) stock is low: %4 units left.")
                                  .arg(nom, type, pays).arg(stock);

            // Log and send
            logToFile("Stock alert", details);
            sendStockAlertEmail(nom, type, pays, stock);
        }
    }
}

void MainWindow::showStockPieChart() {
    QPieSeries *series = new QPieSeries();

    QSqlQuery query;
    query.prepare("SELECT type_vac, SUM(stock) FROM vaccins GROUP BY type_vac");
    if (query.exec()) {
        while (query.next()) {
            QString type = query.value(0).toString();
            int stock = query.value(1).toInt();
            series->append(type, stock);
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Stock Distribution by Vaccine Type");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Statistics - Pie Chart");
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(chartView);
    dialog->setLayout(layout);
    dialog->resize(600, 400);
    dialog->exec();
}



/*---------------------
 * --------------------
 * --------------------
 * --------------------
 * --------------------
 * SI DHIA-------------
---------------------
 * --------------------
 * --------------------
 * --------------------
 * --------------------*/


void MainWindow::verifierIDDepuisArduino()
{
    QByteArray data = A.read_from_arduino();

    if (!data.isEmpty()) {
        QString id_recu = QString(data).trimmed();

        // Affiche l'ID reçu dans la zone de débogage
        qDebug() << "ID Patient reçu :" << id_recu;

        // Vérifie dans la base de données si l'ID existe
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM Patients WHERE id_pat = :id");
        query.bindValue(":id", id_recu);

        if (query.exec() && query.next()) {
            int count = query.value(0).toInt();
            if (count > 0) {
                qDebug() << "ID Patient valide. Vérification du rendez-vous en cours...";

                // Si l'ID est valide, vérifie s'il a un rendez-vous
                verifierRendezVousEtCommanderServo(id_recu);
            } else {
                qDebug() << "ID Patient invalide !";
            }
        } else {
            qDebug() << "Erreur SQL : " << query.lastError().text();
        }
    }
}

void MainWindow::verifierRendezVousEtCommanderServo(QString id) {
    QDate date_auj = QDate::currentDate();
    QString dateStr = date_auj.toString("yyyy-MM-dd");

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Rendez_Vous WHERE id_pat = :id AND TRUNC(date_rdv) = TO_DATE(:date, 'YYYY-MM-DD')");
    query.bindValue(":id", id);
    query.bindValue(":date", dateStr);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        if (count > 0) {
            qDebug() << "Rendez-vous trouvé aujourd'hui pour ID:" << id << " -> Activation du servo.";
            A.write_to_arduino("1");
        } else {
            qDebug() << "Aucun rendez-vous pour aujourd'hui pour ID:" << id;
            A.write_to_arduino("0");
        }
    } else {
        qDebug() << "Erreur requête rendez-vous :" << query.lastError().text();
    }
}




void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event); // Appel à la classe de base
    updateTableViewRV();             // Mise à jour du tableau après affichage
}





void MainWindow::updateTableViewRV() {
    RendezVous r;
    ui->tableau6_2->setModel(r.afficher());  // Charger les nouvelles données
    ui->tableau6_2->viewport()->update();       // Rafraîchir l'affichage
}


void MainWindow::on_pushButton_193_clicked()
{
    QSqlQuery query;

    // Récupération des informations saisies dans les 3 champs
    int id_rdv = ui->lineEditID_2->text().toInt();
    QDate date_rdv = ui->dateEdit_24->date();
    QTime heure_rdv = ui->dateEdit_25->time();
    QString priorite_rdv = ui->comboBox_44->currentText();
    QString status = ui->comboBox_45->currentText();
    int id_pat = ui->lineEdit_2->text().toInt();

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
        updateTableViewRV();
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
        ui->tableau6_2->setModel(model);  // Set the model to the QTableView
        updateTableViewRV();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'affichage des RendezVous");
    }
}

void MainWindow::on_btnsupp_2_clicked() {
    // Récupérer l'ID sélectionné
    QModelIndex index = ui->tableau6_2->selectionModel()->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Suppression"), tr("Veuillez sélectionner un élément à supprimer."));
        return;
    }

    int id = ui->tableau6_2->model()->data(ui->tableau6_2->model()->index(index.row(), 0)).toInt();  // Supposons que l'ID est en 1ère colonne

    // Confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Suppression"), tr("Voulez-vous vraiment supprimer cet élément ?"),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        RendezVous r;
        if (r.supprimer(id)) {
            QMessageBox::information(this, tr("Suppression"), tr("Suppression réussie."));
            updateTableViewRV();  // Rafraîchir la table après suppression
        } else {
            QMessageBox::critical(this, tr("Erreur"), tr("Échec de la suppression."));
        }
    }
}




void MainWindow::on_btnmodif_2_clicked() {
    // Récupérer la ligne sélectionnée
    QModelIndex index = ui->tableau6_2->selectionModel()->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Modification"), tr("Veuillez sélectionner un rendez-vous à modifier."));
        return;
    }

    // Récupérer les valeurs du tableau
    currentId = ui->tableau6_2->model()->data(ui->tableau6_2->model()->index(index.row(), 0)).toInt();
    originalDate = ui->tableau6_2->model()->data(ui->tableau6_2->model()->index(index.row(), 1)).toDate();
    originalHeure = ui->tableau6_2->model()->data(ui->tableau6_2->model()->index(index.row(), 2)).toTime();
    originalPriorite = ui->tableau6_2->model()->data(ui->tableau6_2->model()->index(index.row(), 3)).toString();
    originalStatus = ui->tableau6_2->model()->data(ui->tableau6_2->model()->index(index.row(), 4)).toString();
    originalIdPat = ui->tableau6_2->model()->data(ui->tableau6_2->model()->index(index.row(), 5)).toInt();

    // Remplir les champs de modification
    ui->dateEdit_24->setDate(originalDate);
    ui->dateEdit_25->setTime(originalHeure);
    ui->lineEdit_2->setText(QString::number(originalIdPat));

    // Définir la priorité dans le comboBox
    if (originalPriorite == "Normal")
        ui->comboBox_44->setCurrentIndex(0);
    else if (originalPriorite == "Moyenne")
        ui->comboBox_44->setCurrentIndex(1);
    else if (originalPriorite == "Urgente")
        ui->comboBox_44->setCurrentIndex(2);
    else
        ui->comboBox_44->setCurrentIndex(3);

    // Définir le statut
    if (originalStatus == "Programmer")
        ui->comboBox_45->setCurrentIndex(0);
    else if (originalStatus == "Annuler")
        ui->comboBox_45->setCurrentIndex(1);
    else
        ui->comboBox_45->setCurrentIndex(2);

    modificationInProgress = true; // Activation du mode modification
}

void MainWindow::on_btncmodif_2_clicked() {
    // Vérifier si l'utilisateur a sélectionné un rendez-vous à modifier
    if (!modificationInProgress) {
        QMessageBox::warning(this, tr("Erreur"), tr("Veuillez d'abord sélectionner un rendez-vous à modifier."));
        return;
    }

    // Récupérer les nouvelles valeurs
    //int currentId = ui->tableau6_2->;
    QDate newDate = ui->dateEdit_24->date();
    QTime newHeure = ui->dateEdit_25->time();
    QString newPriorite = ui->comboBox_44->currentText();
    QString newStatus = ui->comboBox_45->currentText();
    int newIdPat = ui->lineEdit_2->text().toInt();

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
        updateTableViewRV();  // Mettre à jour l'affichage

        modificationInProgress = false; // Réinitialisation du mode modification
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de la modification."));
    }
}


void MainWindow::on_btnrendezv4_2_clicked()
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
void MainWindow::on_comboBox_46_currentIndexChanged(int index) {
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
    ui->tableau6_2->setModel(model);
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
    ui->tableau6_2->setModel(model);
}

// Fonction qui affiche les rendez-vous triés par date
void MainWindow::afficherRendezVousTrieParDate(const QString &ordre) {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM RENDEZ_VOUS ORDER BY date_rdv " + ordre);
    ui->tableau6_2->setModel(model);
}



void MainWindow::on_lineEdit_134_textChanged(const QString &searchTerm) {
    RendezVous R;
    QSqlQueryModel* model = nullptr;
    if (searchTerm.trimmed().isEmpty()) {
        // Si la barre de recherche est vide, afficher tous les rendez-vous
        ui->tableau6_2->setModel(R.afficher());
    } else {
        // Sinon, filtrer les résultats
        ui->tableau6_2->setModel(R.rechercher(searchTerm));
    }
    ui->lineEdit_134->setPlaceholderText("Recherche par ID patient");  // Ajouter un texte d'aide
    connect(ui->lineEdit_134, &QLineEdit::textChanged, this, &MainWindow::on_lineEdit_134_textChanged);
}

/*
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
*/void MainWindow::showStatistiques_rdv() {
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



void MainWindow::on_btnrendezv2_2_clicked(){
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

void MainWindow::on_btnrendezv3_2_clicked() {
    chargerRendezVousDansCalendrier();
    ui->sqs->setCurrentIndex(16 );
}


void MainWindow::on_pushButton_194_clicked()
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

        sms1  s;
        s.sendSMS(internationalNumber, message);

        qDebug() << "SMS envoyé à :" << tel << "Message:" << message;
    }

    if (!found) {
        qDebug() << "Aucun rendez-vous trouvé dans la base de données.";
    }
}
/* chahd ......................................
 * ...................................................
 * ...........
 * .........................
 * .................*/

void MainWindow::on_pushButton_labo7_clicked() {
    // Récupération des données depuis l'interface utilisateur
    int id = ui->lineEdit_labo1->text().toInt();
    QString nom = ui->lineEdit_labo2->text();
    QString localisation = ui->lineEdit_labo3->text();
    QString status = ui->comboBox_labo4->currentText();
    QString contact = ui->lineEdit_labo5->text();

    // Contrôle de saisie-----------------------------------------------
    if (nom.isEmpty() || localisation.isEmpty() || contact.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Tous les champs doivent être remplis !"));
        return;
    }

    if (nom.length() > 20) {
        QMessageBox::warning(this, tr("Erreur"), tr("Le nom ne doit pas dépasser 20 caractères !"));
        return;
    }



    // Vérification de l'ID
    if (id <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("L'ID doit être un entier positif."));
        return;
    }


    // Vérification du format du contact (doit être un numéro à 8 chiffres)
    QRegularExpression regex("^\\d{8}$");  // Exige un numéro à 8 chiffres
    if (!regex.match(contact).hasMatch()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Le contact doit être un numéro à 8 chiffres."));
        return;
    }

    // Appel pour obtenir les coordonnées en fonction de la localisation
    getCoordinatesFromAddress(localisation);// **************map2
    // Création d'un objet Lab et ajout dans la BD
    Lab labo(id, nom, localisation, status, contact);
    bool test = labo.ajouter_chahd();

    // Vérification du succès de l'ajout
    if (test) {
        QMessageBox::information(this, tr("Succès"), tr("Ajout effectué avec succès."));

        // Mise à jour de la table après ajout
        updateTableView_labo();


        //addLocationToJson(localisation, latitude, longitude);
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Ajout non effectué."));
    }
    m_markerModel.addLocation(localisation, latitude, longitude);


    //  m_markerModel.geocodeAndAddLocation(localisation);  // ✅
    getCoordinatesFromAddress(localisation); // -> Lancement d'une requête asynchrone

    // Puis immédiatement :
    // m_markerModel.addLocation(localisation, latitude, longitude); // ❌ Mauvais : latitude/longitude = 0

    // m_markerModel.geocodeAndAddLocation(lieu); // 🛠️ utilise le bon objet



}





void MainWindow::on_btnSupprimer_labo_clicked() {
    // Vérifie la sélection dans le tableau
    QModelIndex index = ui->tableau->selectionModel()->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Suppression"), tr("Veuillez sélectionner un élément à supprimer."));
        return;
    }

    // Récupère l'ID (colonne 0) et la localisation (colonne 1 ou autre selon ta table)
    int row = index.row();
    int id = ui->tableau->model()->data(ui->tableau->model()->index(row, 0)).toInt();
    QString localisationASupprimer = ui->tableau->model()->data(ui->tableau->model()->index(row, 2)).toString(); // colonne localisation

    // Confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Suppression"),
                                  tr("Voulez-vous vraiment supprimer cet élément ?"),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        Lab labo;
        if (labo.supprimer_chahd(id)) {
            QMessageBox::information(this, tr("Suppression"), tr("Suppression réussie."));
            updateTableView_labo();  // Rafraîchir la table

            // Supprime du fichier JSON et met à jour la carte
            m_markerModel.removeLocation(localisationASupprimer);  // Suppression du marqueur sur la carte et du fichier JSON

            // Met à jour la carte après suppression
            // updateMapMarkers();  // Cette fonction devrait actualiser la carte avec les marqueurs restants
        } else {
            QMessageBox::critical(this, tr("Erreur"), tr("Échec de la suppression."));
        }
    }
}



void MainWindow::on_btnModifier_labo_clicked() {
    // Récupérer la ligne sélectionnée
    QModelIndex index = ui->tableau->selectionModel()->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Modification"), tr("Veuillez sélectionner un laboratoire à modifier."));
        return;
    }

    // Récupérer les données du tableau
    currentIdL = ui->tableau->model()->data(ui->tableau->model()->index(index.row(), 0)).toInt();
    originalNomL = ui->tableau->model()->data(ui->tableau->model()->index(index.row(), 1)).toString();
    originalLocalisationL = ui->tableau->model()->data(ui->tableau->model()->index(index.row(), 2)).toString();
    originalStatutL = ui->tableau->model()->data(ui->tableau->model()->index(index.row(), 3)).toString();
    originalContactL = ui->tableau->model()->data(ui->tableau->model()->index(index.row(), 4)).toString();

    // Remplir les champs du formulaire de modification
    ui->lineEdit_labo1->setText(QString::number(currentIdL));
    ui->lineEdit_labo2->setText(originalNomL);
    ui->lineEdit_labo3->setText(originalLocalisationL);
    ui->lineEdit_labo5->setText(originalContactL);



    modificationInProgressL = true; // Indiquer qu'une modification est en cours
}

// Fonction pour rafraîchir l'affichage





void MainWindow::on_btnConfirmerModifier_labo8_clicked() {
    // Vérifier si une modification est en cours
    if (!modificationInProgressL) {
        QMessageBox::warning(this, tr("Erreur"), tr("Veuillez d'abord sélectionner un laboratoire à modifier en cliquant sur 'Modifier'."));
        return;
    }

    // Récupérer les nouvelles valeurs depuis les champs de saisie
    QString newNom = ui->lineEdit_labo2->text();
    QString newLocalisation = ui->lineEdit_labo3->text();
    QString newStatut = ui->comboBox_labo4->currentText();
    QString newContact = ui->lineEdit_labo5->text();

    // Vérifier si aucun changement n'a été effectué
    if (newNom == originalNomL && newLocalisation == originalLocalisationL &&
        newStatut == originalStatutL && newContact == originalContactL) {
        QMessageBox::information(this, tr("Modification"), tr("Aucune modification apportée."));
        return;
    }

    // Contrôle de saisie---------------------------------

    // Vérification du format du contact (doit être un numéro à 8 chiffres)
    QRegularExpression regex("^\\d{8}$");  // Exige un numéro à 8 chiffres
    if (!regex.match(newContact).hasMatch()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Le contact doit être un numéro à 8 chiffres."));
        return;
    }


    if (newNom.isEmpty() || newLocalisation.isEmpty() || newContact.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Tous les champs doivent être remplis !"));
        return;
    }

    if (newNom.length() > 20) {
        QMessageBox::warning(this, tr("Erreur"), tr("Le nom ne doit pas dépasser 20 caractères !"));
        return;
    }

    // Vérifier si le nouveau nom existe déjà (éviter les doublons)
    if (newNom != originalNomL) {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM LABORATOIRES WHERE  NOM_LAB = :nom");
        query.bindValue(":nom", newNom);
        if (query.exec() && query.next() && query.value(0).toInt() > 0) {
            QMessageBox::warning(this, tr("Erreur"), tr("Un laboratoire avec ce nom existe déjà !"));
            return;
        }
    }

    // Mise à jour des informations du laboratoire
    Lab labo(currentIdL, newNom, newLocalisation, newStatut, newContact);
    if (labo.modifier_chahd(currentIdL)) {
        QMessageBox::information(this, tr("Modification"), tr("Modification réussie."));
        updateTableView_labo();  // Rafraîchir la table après modification

        modificationInProgressL = false; // Réinitialiser le flag
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de la modification."));
    }
}






// Déclare le modèle au niveau de la classe pour le réutiliser
QSqlQueryModel *model = new QSqlQueryModel();

void MainWindow::trierParId_labo() {
    QString triOption = ui->comboBox_labo6->currentText();
    QSqlQuery query;

    if (triOption == "⬆️ ID") {
        query.prepare("SELECT * FROM LABORATOIRES ORDER BY ID_LAB ASC");
    } else if (triOption == "⬇️ ID") {
        query.prepare("SELECT * FROM LABORATOIRES ORDER BY ID_LAB DESC");
    } else {
        query.prepare("SELECT * FROM LABORATOIRES");  // Aucun tri spécifique
    }

    if (!query.exec()) {
        qDebug() << "❌ Erreur lors du tri :" << query.lastError().text();
        return;
    }

    model->setQuery(std::move(query));
    ui->tableau->setModel(model);
    ui->tableau->resizeColumnsToContents();
}



void MainWindow::rechercher_labo() {

    QString recherche = ui->lineEdit_24_labo->text().trimmed();

    if (recherche.isEmpty()) {
        QMessageBox::warning(this, tr("Recherche"), tr("Veuillez entrer un statut (Actif ou Inactif) ou un nom de laboratoire."));
        return;
    }

    QSqlQuery query;
    QString queryString = "SELECT * FROM LABORATOIRES WHERE";

    QString rechercheUpper = recherche.toUpper();

    if (rechercheUpper == "ACTIF" || rechercheUpper == "INACTIF") {
        queryString += " UPPER(STATUS) = :statut";
        query.prepare(queryString);
        query.bindValue(":statut", rechercheUpper);
    } else {
        queryString += " UPPER(NOM_LAB) LIKE :nomLab";
        query.prepare(queryString);
        query.bindValue(":nomLab", "%" + rechercheUpper + "%");
    }

    if (!query.exec()) {
        qDebug() << "Erreur lors de la recherche :" << query.lastError().text();
        return;
    }

    model->setQuery(query);
    qDebug() << "Nombre de résultats : " << model->rowCount();

    ui->tableau->setModel(model);
    ui->tableau->resizeColumnsToContents();
    ui->tableau->resizeRowsToContents();
}


void MainWindow::updateTableViewchat(QSqlQueryModel *model)
{
    if (model != nullptr) {
        ui->tableViewchatbot->setModel(model);
    } else {
        QMessageBox::warning(this, "Erreur", "Erreur d'affichage du laboratoire.");
    }
}
















void MainWindow::on_btnlabo5_clicked() {//PDF
    QString fileName = QFileDialog::getSaveFileName(this, tr("Enregistrer le rapport"), "", tr("Fichiers PDF (*.pdf)"));
    if (fileName.isEmpty()) {
        return;
    }

    QPdfWriter writer(fileName);//Initialise l’objet PDF
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(300);

    QPainter painter;//desgner de pfd
    if (!painter.begin(&writer)) {
        QMessageBox::warning(this, tr("Erreur"), tr("Impossible de créer le fichier PDF."));
        return;
    }

    // Définition des dimensions adaptées
    int margin = 120;  // Marge à gauche
    int colWidths[] = {240, 440, 520, 280, 380}; // Largeurs des colonnes ajustées
    int rowHeight = 100; // Hauteur des lignes
    int yPosition = 120; // Position initiale après le titre

    // Dessiner le titre
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.drawText(200, 50, "Rapport des Laboratoires");

    // Dessiner l'en-tête du tableau
    painter.setFont(QFont("Arial", 11, QFont::Bold));
    int x = margin;
    QStringList headers = {"ID_LAB", "Nom_Lab", "Localisation", "Statut", "Contact"};

    for (int i = 0; i < headers.size(); i++) {
        painter.drawRect(x, yPosition, colWidths[i], rowHeight); // Dessiner la cellule
        painter.drawText(QRect(x + 5, yPosition + 10, colWidths[i] - 10, rowHeight), Qt::AlignLeft | Qt::AlignVCenter, headers[i]); // Texte ajusté
        x += colWidths[i];
    }

    yPosition += rowHeight;

    // Récupérer les données
    QSqlQuery query("SELECT * FROM LABORATOIRES");
    painter.setFont(QFont("Arial", 10)); // Police plus grande

    while (query.next()) {
        x = margin;

        // Récupérer les valeurs
        QString idLab = query.value("ID_LAB").toString();
        QString nomLab = query.value("NOM_LAB").toString().left(25);
        QString localisationLab = query.value("LOCALISATION_LAB").toString().left(30);
        QString statut = query.value("STATUS").toString();
        QString contact = query.value("CONTACT").toString().left(15);

        QStringList rowData = {idLab, nomLab, localisationLab, statut, contact};

        for (int i = 0; i < rowData.size(); i++) {
            painter.drawRect(x, yPosition, colWidths[i], rowHeight); // Dessiner la cellule
            painter.drawText(QRect(x + 5, yPosition + 10, colWidths[i] - 10, rowHeight), Qt::TextWordWrap | Qt::AlignLeft | Qt::AlignVCenter, rowData[i]); // Texte ajusté
            x += colWidths[i];
        }

        yPosition += rowHeight;

        // Vérifier si une nouvelle page est nécessaire
        if (yPosition > 750) {
            writer.newPage();
            yPosition = 120; // Réinitialiser la position pour la nouvelle page
        }
    }

    painter.end();
    QMessageBox::information(this, tr("Succès"), tr("Le rapport PDF a été généré avec succès."));
}
void MainWindow::showStatistiques_labo() {
    if (!ui->chartContainer_labo) {
        qDebug() << "❌ ERROR: chartContainer is NULL!";
        return;
    }

    // Étape 1 : Vérifier ou créer un layout
    if (!ui->chartContainer_labo->layout()) {
        ui->chartContainer_labo->setLayout(new QVBoxLayout());
    }

    // Étape 2 : Nettoyer les anciens graphiques
    QLayoutItem* item;
    while ((item = ui->chartContainer_labo->layout()->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->chartContainer_labo->layout());

    // Étape 3 : Créer la série de données avec les stats. (QPieSeries)
    QPieSeries *pieSeries = new QPieSeries();
    QMap<QString, int> statsType = labo.getStatistiquesParstatus_chahd();

    if (statsType.isEmpty()) {
        qDebug() << "⚠️ WARNING: No data found for status statistics!";
    }

    // Étape 4 : Calculer le total pour les pourcentages
    int total = 0;
    for (auto it = statsType.begin(); it != statsType.end(); ++it) {
        total += it.value();
    }

    // Étape 5 : Ajouter les tranches avec pourcentage dans le label
    for (auto it = statsType.begin(); it != statsType.end(); ++it) {
        qreal value = it.value();
        QString label = QString("%1 (%2%)")
                            .arg(it.key())
                            .arg(QString::number((value / (double)total) * 100.0, 'f', 1));
        QPieSlice *slice = pieSeries->append(label, value);
    }

    pieSeries->setLabelsVisible(true);  // Étape 6 : Afficher les labels

    // Étape 7 : Créer le graphique et l’ajouter au layout
    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);
    pieChart->setTitle("Répartition des laboratoires par statut");

    QChartView *chartView = new QChartView(pieChart);
    chartView->setRenderHint(QPainter::Antialiasing);

    layout->addWidget(chartView);

    qDebug() << "✅ Statistiques mises à jour avec succès !";
}

//chatbot




void MainWindow::analyserCommande()
{
    QString commande = ui->lineEditchat->text().trimmed();

    if (commande.isEmpty()) {
        QMessageBox::warning(this, "Commande vide", "Veuillez entrer une commande valide.");
        return;
    }

    QSqlQueryModel* model = labo.analyserCommande(commande);  // On récupère le modèle en retour
    if (model) {
        updateTableViewchat(model);
    } else {
        updateTableViewchat();  // Afficher tous par défaut
    }
}



void MainWindow::updateTableViewchat()
{
    QSqlQueryModel *model = labo.afficher_chahd();

    if (model != nullptr) {
        ui->tableViewchatbot->setModel(model);
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de charger les laboratoires.");
    }
}





//*********************maps


// Fonction pour traiter la réponse de géocodage
void MainWindow::onGeoCodeReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonDocument json = QJsonDocument::fromJson(responseData);
        QJsonArray results = json.array();

        if (!results.isEmpty()) {
            QJsonObject firstResult = results.first().toObject();
            double lat = firstResult["lat"].toString().toDouble();
            double lon = firstResult["lon"].toString().toDouble();
            QString localisation = QUrlQuery(reply->url()).queryItemValue("q");

            qDebug() << "🌍 Coordonnées reçues pour" << localisation << ":" << lat << lon;

            // 1. Ajoute au modèle (et fichier JSON)
            m_markerModel.addLocation(localisation, lat, lon);

            // 2. (Optionnel) Mets à jour les coordonnées globales
            latitude = lat;
            longitude = lon;
            emit positionTrouvee(lat, lon);

        } else {
            qWarning() << "❌ Aucun résultat pour l'adresse.";
        }
    } else {
        qWarning() << "❌ Erreur de la requête :" << reply->errorString();
    }

    reply->deleteLater();
}
void MainWindow::searchLocation(const QString &address) {
    if (address.trimmed().isEmpty()) {
        qDebug() << "Adresse vide, aucune recherche.";
        return;
    }

    QUrl url("https://nominatim.openstreetmap.org/search");
    QUrlQuery query;
    query.addQueryItem("q", address);
    query.addQueryItem("format", "json");
    query.addQueryItem("addressdetails", "1");
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, "MyApp/1.0");  // Important pour Nominatim

    networkManager->get(request);

}
// Fonction pour envoyer la requête de géocodage et obtenir les coordonnées
void MainWindow::getCoordinatesFromAddress(const QString &address) {
    QUrl url("https://nominatim.openstreetmap.org/search");
    QUrlQuery query;
    query.addQueryItem("q", address);  // Adresse (par exemple "Tunis")
    query.addQueryItem("format", "json");  // Format de réponse JSON
    url.setQuery(query);

    // Envoie la requête de géocodage
    networkManager->get(QNetworkRequest(url));
}








































































//------------------------------------------------------------------------------------------------------------------Sadek



//------------------------------------------------------------------------------------------------------------------CRUD

void MainWindow::updateTableViewEquipement() {
    QSqlQueryModel* model = equipement.afficher();

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    ui->tableauEquipements->setModel(proxyModel);
    ui->tableauEquipements->setSortingEnabled(true);
    ui->tableauEquipements->sortByColumn(0, Qt::AscendingOrder);  // Optional: Default sort by ID
}

void MainWindow::on_btnequipementAjouter_4_clicked() {
    QSqlQuery query;
    query.prepare("SELECT MAX(id_eqp) FROM EQUIPEMENTS");  // Get max ID
    query.exec();

    int id = 1;  // Default ID if the table is empty

    if (query.next() && !query.value(0).isNull()) {
        id = query.value(0).toInt() + 1;  // Assign max ID + 1
    }

    // Récupérer les valeurs de l'UI
    QString nom = ui->lineEdit_67->text();
    QString type = ui->comboBox_20->currentText();
    QString statut = ui->comboBox_21->currentText();
    QString description = ui->inputvoice_4->text();

    // Obtenir la date actuelle
    QDate dateMaintenance ;

    // Vérifier si le nom est vide
    if (nom.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le nom ne peut pas être vide !");
        return;
    }

    if (nom.length() > 30) {
        QMessageBox::warning(this, "Erreur", "Le nom ne doit pas dépasser 30 caractères !");
        return;
    }

    if (description.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "La description ne peut pas être vide !");
        return;
    }

    if (description.length() > 100) {
        QMessageBox::warning(this, "Erreur", "La description ne doit pas dépasser 100 caractères !");
        return;
    }

    // Vérifier si le nom existe déjà
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM EQUIPEMENTS WHERE nom_eqp = :nom");
    checkQuery.bindValue(":nom", nom);
    checkQuery.exec();

    if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Erreur", "Un équipement avec ce nom existe déjà !");
        return;
    }

    // Créer l'objet Equipement avec le bon ID
    Equipement equip(id, nom, type, statut, dateMaintenance, description);

    // Ajouter dans la base de données
    if (equip.ajouter()) {
        QMessageBox::information(this, "Succès", "Équipement ajouté avec succès !");
        afficherEquipements();  // Refresh table after adding
    } else {
        QMessageBox::critical(this, "Erreur", "L'ajout de l'équipement a échoué !");
    }
}

void MainWindow::afficherEquipements(){
    QSqlQueryModel* model = equipement.afficher();
    ui->tableauEquipements->setModel(model);  // Assign model to QTableView
}

void MainWindow::on_btnSupprimer_clicked() {
    QModelIndex index = ui->tableauEquipements->selectionModel()->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Suppression"), tr("Veuillez sélectionner un élément à supprimer."));
        return;
    }

    int id = ui->tableauEquipements->model()->data(ui->tableauEquipements->model()->index(index.row(), 0)).toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Suppression"), tr("Voulez-vous vraiment supprimer cet élément ?"),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        Equipement equip;
        if (equip.supprimer(id)) {
            QMessageBox::information(this, tr("Suppression"), tr("Suppression réussie."));
            updateTableViewEquipement();
        } else {
            QMessageBox::critical(this, tr("Erreur"), tr("Échec de la suppression."));
        }
    }
}

void MainWindow::on_btnModifier_clicked() {

    ui->dateEdit_11->setEnabled(true);
    ui->dateEdit_11->setVisible(true);
    ui->label_2009->setVisible(true);

    // Retrieve the selected row
    QModelIndex index = ui->tableauEquipements->selectionModel()->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Modification"), tr("Veuillez sélectionner un élément à modifier."));
        return;
    }

    // Get the record values from the table.
    currentId = ui->tableauEquipements->model()->data(ui->tableauEquipements->model()->index(index.row(), 0)).toInt();
    originalNom = ui->tableauEquipements->model()->data(ui->tableauEquipements->model()->index(index.row(), 1)).toString();
    originalType = ui->tableauEquipements->model()->data(ui->tableauEquipements->model()->index(index.row(), 2)).toString();
    originalStatut = ui->tableauEquipements->model()->data(ui->tableauEquipements->model()->index(index.row(), 3)).toString();
    originalDescription = ui->tableauEquipements->model()->data(ui->tableauEquipements->model()->index(index.row(), 5)).toString();

    QString dateStr = ui->tableauEquipements->model()->data(ui->tableauEquipements->model()->index(index.row(), 4)).toString();

    QDate maintenanceDate = QDate::fromString(dateStr, "dd-MM-yyyy");
    originalDate = maintenanceDate;

    if (maintenanceDate.isValid()) {
        ui->dateEdit_11->setDate(maintenanceDate);
        ui->dateEdit_11->setDisplayFormat("dd/MM/yyyy");
    } else {
        ui->dateEdit_11->clear();  // fallback if parsing fails
    }

    // Populate the other fields
    ui->lineEdit_67->setText(originalNom);

    // Set comboBox_20 (Type)
    if (originalType == "Machine")
        ui->comboBox_20->setCurrentIndex(0);
    else if (originalType == "Outil")
        ui->comboBox_20->setCurrentIndex(1);
    else if (originalType == "Stockage")
        ui->comboBox_20->setCurrentIndex(0);
    else
        ui->comboBox_20->setCurrentIndex(3);

    // Set comboBox_21 (Statut)
    if (originalStatut == "Inactif")
        ui->comboBox_21->setCurrentIndex(1);
    else
        ui->comboBox_21->setCurrentIndex(0);

    ui->inputvoice_4->setText(originalDescription);

    modificationInProgress = true; // Set the flag when modification starts
}

void MainWindow::on_btnConfirmerModifier_4_clicked() {
    // Ensure user clicked "Modifier" before confirming
    if (!modificationInProgress) {
        QMessageBox::warning(this, tr("Erreur"), tr("Veuillez d'abord sélectionner un équipement à modifier en cliquant sur 'Modifier'."));
        return;
    }

    // Retrieve new values from groupbox fields
    QString newNom = ui->lineEdit_67->text();
    QString newType = ui->comboBox_20->currentText();
    QString newStatut = ui->comboBox_21->currentText();
    QString newDescription = ui->inputvoice_4->text();

    // Here, we use the text of the dateEdit_11:
    QString dateText = ui->dateEdit_11->text().trimmed();
    QDate newDate;
    if (dateText.isEmpty()) {
        // If the field is empty, set newDate to an invalid date
        newDate = QDate();
    } else {
        newDate = ui->dateEdit_11->date();
    }

    // Check if no change was made
    if (newNom == originalNom && newType == originalType && newStatut == originalStatut && newDescription == originalDescription && newDate == originalDate) {
        QMessageBox::information(this, tr("Modification"), tr("Aucune modification apportée."));
        return;
    }

    // Validate the new name
    if (newNom.isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"), tr("Le nom ne peut pas être vide !"));
        return;
    }
    if (newNom.length() > 30) {
        QMessageBox::warning(this, tr("Erreur"), tr("Le nom ne doit pas dépasser 30 caractères !"));
        return;
    }

    // Check if the new name already exists in the database
    if (newNom != originalNom) {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM EQUIPEMENTS WHERE nom_eqp = :nom");
        query.bindValue(":nom", newNom);
        if(query.exec() && query.next() && query.value(0).toInt() > 0) {
            QMessageBox::warning(this, tr("Erreur"), tr("Un équipement avec ce nom existe déjà !"));
            return;
        }
    }

    if (newDescription.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "La description ne peut pas être vide !");
        return;
    }

    if (newDescription.length() > 100) {
        QMessageBox::warning(this, "Erreur", "La description ne doit pas dépasser 100 caractères !");
        return;
    }

    Equipement equip(currentId, newNom, newType, newStatut, newDate, newDescription);
    if (equip.modifier(currentId)) {
        QMessageBox::information(this, tr("Modification"), tr("Modification réussie."));
        updateTableViewEquipement();  // Refresh the table

        modificationInProgress = false; // Reset the flag after modification
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de la modification."));
    }

    ui->dateEdit_11->clear();             // Clear the date field (remains empty)
    ui->dateEdit_11->setEnabled(false);     // Disable user interaction
    ui->dateEdit_11->setVisible(false);
    ui->label_2009->setVisible(false);
    ui->comboBox_20->setCurrentIndex(0);
    ui->comboBox_21->setCurrentIndex(0);
    ui->inputvoice_4->clear();
    ui->lineEdit_67->clear();
}



//------------------------------------------------------------------------------------------------------------------RECHERCHER

void MainWindow::on_lineEdit_54_textChanged(const QString &searchTerm) {
    if (searchTerm.trimmed().isEmpty()) {
        // If the search field is empty, show all equipment
        ui->tableauEquipements->setModel(equipement.afficher());
    } else {
        // Otherwise, filter based on search input
        ui->tableauEquipements->setModel(equipement.rechercher(searchTerm));
    }
}

//------------------------------------------------------------------------------------------------------------------PDF

void MainWindow::on_btnequiprmrnt4_clicked() {
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer PDF", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) {
        return;
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(equipement.getEquipementsAsHTML()); // Call the function from Equipement class
    doc.print(&printer);

    QMessageBox::information(this, "Succès", "PDF généré avec succès !");
}

//------------------------------------------------------------------------------------------------------------------STAT

void MainWindow::showStatistiques() {
    // Clear existing layout content
    if (ui->chartContainerType->layout()) {
        QLayout *layout = ui->chartContainerType->layout();
        while (QLayoutItem *item = layout->takeAt(0)) {
            if (QWidget *widget = item->widget()) {
                widget->deleteLater();
            }
            delete item;
        }
    } else {
        ui->chartContainerType->setLayout(new QVBoxLayout());
    }

    // 📊 Pie Chart (Type Distribution)
    QPieSeries *pieSeries = new QPieSeries();
    QMap<QString, int> statsType = equipement.getStatistiquesParType();

    int total = 0;
    for (auto it = statsType.begin(); it != statsType.end(); ++it) {
        total += it.value();  // Calculate total count of all equipment
    }

    if (statsType.isEmpty()) {
        qDebug() << "⚠️ WARNING: No data found for equipment types!";
    } else {
        for (auto it = statsType.begin(); it != statsType.end(); ++it) {
            double percentage = (total > 0) ? (it.value() * 100.0 / total) : 0;  // Calculate percentage

            QPieSlice *slice = pieSeries->append(it.key(), it.value());

            // Set label format to show percentage
            slice->setLabel(QString("%1: %2%").arg(it.key()).arg(percentage, 0, 'f', 1));

            slice->setLabelVisible(true);  // Ensure label is visible

            // Add hover effect
            connect(slice, &QPieSlice::hovered, [slice](bool hovered) {
                slice->setExploded(hovered);
                slice->setLabelFont(QFont("Arial", hovered ? 12 : 10, hovered ? QFont::Bold : QFont::Normal));
            });
        }
    }

    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);

    // Set Background Color 🎨
    pieChart->setBackgroundBrush(QBrush(QColor(234, 251, 255)));

    QChartView *chartView = new QChartView(pieChart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->chartContainerType->layout()->addWidget(chartView);
}



//------------------------------------------------------------------------------------------------------------------Alert

void MainWindow::on_panneButton_clicked() {
    // Get the selected row from QTableView
    QModelIndex index = ui->tableauEquipements->selectionModel()->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Aucune sélection"), tr("Veuillez sélectionner un équipement."));
        return;
    }

    // Get the model to extract data from the selected row
    QAbstractItemModel *model = ui->tableauEquipements->model();
    int row = index.row();

    // Get the equipment ID and name
    QString equipementID = model->data(model->index(row, 0)).toString();  // Column 1 = id_eqp
    QString equipementNom = model->data(model->index(row, 1)).toString(); // Column 2 = nom_eqp

    // Call the function to update the database
    Equipement equip;
    if (equip.setEnPanne(equipementID)) {
        QMessageBox::information(this, tr("Mise en panne"), tr("L'équipement a été marqué en panne."));
        updateTableViewEquipement();  // Refresh the table from the database
        showPanneNotification(equipementNom);  // Show scrolling alert message
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de modifier le statut en panne."));
    }
}

void MainWindow::showPanneNotification(const QString &equipementNom) {
    QString alertText = equipementNom + " est en panne. 🚨";

    // Set text style (red text only)
    ui->labelAlert_6->setStyleSheet("color: red; font-size: 18px; font-weight: bold;");
    ui->labelAlert_6->setAlignment(Qt::AlignVCenter);
    ui->labelAlert_6->setText(alertText);

    // Setup media player with audio output
    QMediaPlayer *player = new QMediaPlayer(this);
    QAudioOutput *audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl::fromLocalFile("C:/Users/sadekk/Documents/sadek/siren.wav"));
    audioOutput->setVolume(50); // 50% volume
    player->setLoops(QMediaPlayer::Infinite);

    // Faster animation (3 seconds per cycle)
    int animationDuration = 6000;
    int totalDuration = 15000;

    QPropertyAnimation *animation = new QPropertyAnimation(ui->labelAlert_6, "pos", this);
    animation->setDuration(animationDuration);
    animation->setStartValue(QPoint(-ui->labelAlert_6->width(), ui->labelAlert_6->y()));
    animation->setEndValue(QPoint(width(), ui->labelAlert_6->y()));
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setLoopCount(totalDuration / animationDuration);

    // Start both sound and animation
    player->play();
    animation->start();

    // Cleanup after 15 seconds
    QTimer::singleShot(totalDuration, [=]() {
        player->stop();
        animation->stop();
        ui->labelAlert_6->clear();
        player->deleteLater();
        audioOutput->deleteLater();
        animation->deleteLater();
    });
}

//------------------------------------------------------------------------------------------------------------------Voice to chat

void MainWindow::on_btnvoice_4_clicked() {
    QProcess process;
    QString pythonPath = "python";  // Or the full path if needed
    QString scriptPath = "C:/Users/sadekk/Documents/sadek/voice_module/run_transcription.py";

    // Start the Python process
    process.start(pythonPath, QStringList() << scriptPath);
    process.waitForFinished(-1);  // Wait for the script to finish

    // 🔹 Capture standard output (transcribed text)
    QString output = QString::fromUtf8(process.readAllStandardOutput()).trimmed();
    ui->inputvoice_4->setText(output);

    // 🔹 Capture and print standard error (for debugging)
    QString errors = QString::fromUtf8(process.readAllStandardError());
}

//------------------------------------------------------------------------------------------------------------------Arduino

void MainWindow::update_fridge_status() {
    static QByteArray buffer;
    buffer += A.read_from_arduino();
    int endIndex;

    while ((endIndex = buffer.indexOf('\n')) != -1) {
        QByteArray line = buffer.left(endIndex).trimmed();
        buffer.remove(0, endIndex + 1);
        QString text = QString::fromUtf8(line);

        QString id;
        float currentTemp = 0.0;
        bool ok = false;

        QRegularExpression re(R"(ID(\d+):TEMP:([\d.]+))");
        QRegularExpressionMatch match = re.match(text);

        if (match.hasMatch()) {
            id = match.captured(1);               // "1" or "2"
            currentTemp = match.captured(2).toFloat(&ok);

            if (ok) {
                QSqlQuery tempQuery;
                tempQuery.prepare("SELECT temperature_conservation FROM VACCINS WHERE id_vac = :id");
                tempQuery.bindValue(":id", id.toInt());
                float conservationTemp = 0.0;

                if (tempQuery.exec() && tempQuery.next()) {
                    conservationTemp = tempQuery.value(0).toFloat(&ok);
                }

                if (id == "1") {
                    ui->label_temperaturearduino->setText(QString::number(currentTemp) + " °C");
                    ui->label_temperaturebase->setText(QString::number(conservationTemp) + " °C");
                } else if (id == "2") {
                    ui->label_temperaturearduino2->setText(QString::number(currentTemp) + " °C");
                    ui->label_temperaturearduino2_2->setText(QString::number(conservationTemp) + " °C");
                }

                // Alert check
                if (qAbs(currentTemp - conservationTemp) > 0.5) {

                    QSqlQuery update;
                    update.prepare("UPDATE EQUIPEMENTS SET statut_eqp = 'En panne' WHERE id_eqp = :id");
                    update.bindValue(":id", id.toInt());
                    if (!update.exec()) {
                        qDebug() << "Update failed:" << update.lastError().text();
                    }

                    A.write_to_arduino("ALERTE\n");
                    updateTableViewEquipement();
                }
            }
        }
    }
}






















//pat
void MainWindow::modifierPatient(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM PATIENTS WHERE ID_PAT = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        // Stocker l'ID du patient en modification
        currentPatientId = id;

        // Remplir le formulaire avec les données du patient sélectionné
        ui->lineEdit_57->setText(query.value("NOM_PAT").toString());
        ui->lineEdit_58->setText(query.value("PRENOM_PAT").toString());
        ui->dateEdit_9->setDate(query.value("DATENAIS_PAT").toDate());
        ui->lineEdit_59->setText(query.value("EMAIL").toString());
        ui->comboBox_12->setCurrentText(query.value("GENRE").toString());
        ui->lineEdit_60->setText(query.value("ADRESSE").toString());
        ui->comboBox_7->setCurrentText(query.value("GROUPSANGUIN").toString());
        ui->lineEdit_61->setText(query.value("TEL").toString());
        // Changer le texte du bouton "Ajouter" en "Modifier"
        ui->btnajouterpatient_2->setText("Modifier");
        ui->btnajouterpatient_2->setStyleSheet("background-color: green; color: white; font-weight: bold; border-radius: 10px; padding: 8px;");
    } else {
        QMessageBox::critical(this, "Erreur","Impossible de récupérer les informations du patient." + QString::number(currentPatientId));
    }
}
void MainWindow::supprimerPatient(int id)
{
    Patient p;
    if (p.supprimerPatient(id)) {
        QMessageBox::information(this, "Suppression réussie", "Le patient a été supprimé avec succès."+ QString::number(id));
        p.afficher(ui->tableau3_4); // Rafraîchir la liste
    }
}
void MainWindow::on_btnajouterpatient_2_clicked()
{
    // Génération d'un ID aléatoire
    std::srand(std::time(0));
    int min = 1, max = 100;
    int id = min + std::rand() % (max - min + 1);

    QString nom = ui->lineEdit_57->text().trimmed();
    QString prenom = ui->lineEdit_58->text().trimmed();
    QDate dateNaiss = ui->dateEdit_9->date();
    QString email = ui->lineEdit_59->text().trimmed();
    QString genre = ui->comboBox_12->currentText();
    QString adresse = ui->lineEdit_60->text().trimmed();
    QString groupeSanguin =ui->comboBox_7->currentText();
    bool ok;
    int tel = ui->lineEdit_61->text().trimmed().toInt(&ok);
    qDebug() << tel;
    if (!ok) {
        QMessageBox::warning(this, "Entrée invalide", "Le numéro de téléphone doit être un entier valide.");
        return;  // Or handle it accordingly
    }



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

    QRegularExpression regexEmail("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.(com|tn)$");

    if (!regexEmail.match(email).hasMatch()) {
        QMessageBox::warning(this, "Email invalide", "L'email doit être sous la forme exemple@domaine.com !");
        return;
    }
    qDebug() << tel;
    Patient patient(id,nom,prenom,dateNaiss,email,genre,adresse,groupeSanguin,tel);

    if (currentPatientId == -1) {
        if (patient.ajouter()) {
            QMessageBox::information(this, "Succès", "Patient ajouté avec succès !");
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de l'ajout du patient.");
        }
    } else {
        // 🔹 Modification d'un patient existant
        if (patient.modifierPatient(currentPatientId, nom, prenom, dateNaiss, email, genre, adresse, groupeSanguin,tel)) {
            QMessageBox::information(this, "Succès", "Patient modifié avec succès !");
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la modification du patient.");
        }

        // Réinitialisation après modification
        currentPatientId = -1;
        ui->btnajouterpatient_2->setText("Ajouter");
        ui->btnajouterpatient_2->setStyleSheet("QPushButton {background-color: rgb(173, 216, 230); color: #ffffff;border: 2px solid rgb(173, 216, 230);padding: 10px;margin: 6px; border-radius: 12px;font-size: 15px;font-weight: bold;transition: all 0.3s ease-in-out;}QPushButton:hover {background-color: #606060;border-color: #777777;}QPushButton:pressed { background-color: #787878;border-color: #909090;}QPushButton:disabled {background-color: #353535;color: #ffffff;border-color: #444444;}");
    }

    patient.afficher(ui->tableau3_4); // Rafraîchir la liste des patients
    ui->rapportettable->setCurrentWidget(ui->page_7);
}
void MainWindow::on_recherche_clicked()
{
    QString rechercheNom = ui->lineEdit_62->text().trimmed();

    Patient patient;
    patient.afficherSpecifique(ui->tableau3_4, rechercheNom);
}
void MainWindow::on_tri_clicked()
{
    Patient patient;
    patient.afficherTrieParAnneeNaissance(ui->tableau3_4);
}
void MainWindow::genererRapportPDF()
{
    QString filePath = QDir::homePath() + "/Desktop/c++/integ2/rapport_patient.pdf";
    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);
    QPainter painter(&pdfWriter);

    // Marges
    const int marginLeft = 40;
    const int marginTop = 50;
    const int pageWidth = pdfWriter.width() - 2 * marginLeft;

    // Logo et titre
    QPixmap logo("/mnt/data/44298757-c475-4d62-8415-e4d92b1b761b-removebg-preview.png");
    painter.drawPixmap(marginLeft, marginTop, 80, 80, logo);
    painter.setFont(QFont("Arial", 20, QFont::Bold));
    painter.setPen(Qt::darkBlue);
    painter.drawText(marginLeft + 100, marginTop + 40, "VaxNest - Rapport des Patients");

    // Ligne séparatrice
    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(marginLeft, marginTop + 100, marginLeft + pageWidth, marginTop + 100);

    // Titre tableau
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.drawText(marginLeft, marginTop + 130, "Liste des Patients");

    // Coordonnées du tableau
    int y = marginTop + 160;
    int rowHeight = 45;

    // Largeur totale à diviser
    QVector<int> columnWidths = {
        int(pageWidth * 0.08),  // ID
        int(pageWidth * 0.20),  // Nom
        int(pageWidth * 0.20),  // Prénom
        int(pageWidth * 0.20),  // Date naissance
        int(pageWidth * 0.32)   // Email
    };

    QStringList headers = {"ID", "Nom", "Prénom", "Date Naissance", "Email"};

    // En-tête stylée
    painter.setFont(QFont("Arial", 11, QFont::Bold));
    painter.setPen(Qt::white);
    painter.setBrush(QColor("#2E86C1"));  // Bleu foncé
    int x = marginLeft;
    for (int i = 0; i < headers.size(); ++i) {
        painter.drawRect(x, y, columnWidths[i], rowHeight);
        painter.drawText(x + 10, y + 30, headers[i]);
        x += columnWidths[i];
    }
    y += rowHeight;

    // Récupération des patients
    QSqlQuery query;
    if (!query.exec("SELECT ID_PAT, NOM_PAT, PRENOM_PAT, TO_CHAR(DATENAIS_PAT, 'YYYY-MM-DD'), EMAIL FROM PATIENTS ORDER BY ID_PAT")) {
        QMessageBox::critical(this, "Erreur SQL", "Impossible de récupérer les patients: " + query.lastError().text());
        return;
    }

    // Dessiner les lignes
    painter.setFont(QFont("Arial", 10));
    bool isAlternate = false;
    while (query.next()) {
        x = marginLeft;
        painter.setPen(Qt::black);
        painter.setBrush(isAlternate ? QColor("#f5f6fa") : Qt::white);  // Gris clair
        isAlternate = !isAlternate;

        for (int i = 0; i < headers.size(); ++i) {
            painter.drawRect(x, y, columnWidths[i], rowHeight);
            painter.drawText(x + 10, y + 28, query.value(i).toString());
            x += columnWidths[i];
        }

        y += rowHeight;

        // Saut de page si dépassement
        if (y > pdfWriter.height() - 100) {
            pdfWriter.newPage();
            y = marginTop;
        }
    }

    painter.end();
    QMessageBox::information(this, "Succès", "Le rapport PDF a été généré avec succès !");
}


// Code du bouton pour générer le rapport
void MainWindow::on_btnpatient3_3_clicked()
{
    genererRapportPDF();
}
void MainWindow::afficherStatistiques()
{
    // Récupérer les données d'âge des patients
    QSqlQuery queryAge;
    if (!queryAge.exec("SELECT DATENAIS_PAT FROM PATIENTS")) {
        QMessageBox::critical(this, "Erreur SQL", "Impossible de récupérer les âges: " + queryAge.lastError().text());
        return;
    }

    QLineSeries *ageSeries = new QLineSeries();
    QDate currentDate = QDate::currentDate();
    int index = 0;
    while (queryAge.next()) {
        QDate birthDate = queryAge.value(0).toDate();
        int age = birthDate.daysTo(currentDate) / 365; // Calcul de l'âge
        ageSeries->append(index++, age);
    }

    QChart *ageChart = new QChart();
    ageChart->addSeries(ageSeries);
    ageChart->setTitle("Courbe d'âge des patients");
    ageChart->createDefaultAxes();
    QChartView *ageChartView = new QChartView(ageChart);
    ageChartView->setRenderHint(QPainter::Antialiasing);

    // Récupérer les données des groupes sanguins
    QSqlQuery queryBlood;
    if (!queryBlood.exec("SELECT GROUPSANGUIN, COUNT(*) FROM PATIENTS GROUP BY GROUPSANGUIN")) {
        QMessageBox::critical(this, "Erreur SQL", "Impossible de récupérer les groupes sanguins: " + queryBlood.lastError().text());
        return;
    }

    QPieSeries *bloodSeries = new QPieSeries();
    while (queryBlood.next()) {
        bloodSeries->append(queryBlood.value(0).toString(), queryBlood.value(1).toInt());
    }

    QChart *bloodChart = new QChart();
    bloodChart->addSeries(bloodSeries);
    bloodChart->setTitle("Répartition des groupes sanguins");
    QChartView *bloodChartView = new QChartView(bloodChart);
    bloodChartView->setRenderHint(QPainter::Antialiasing);

    // Ajouter les graphiques à la page_6 du stackedWidget
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(ageChartView);
    layout->addWidget(bloodChartView);
    ui->page_8->setLayout(layout);
}

// Code du bouton pour afficher les statistiques
void MainWindow::on_btnpatient2_3_clicked()
{
    afficherStatistiques();
    ui->rapportettable->setCurrentWidget(ui->page_8);
}
void MainWindow::on_listpatient_clicked()
{
    Patient p;
    p.afficher(ui->tableau3_4);
    ui->rapportettable->setCurrentWidget(ui->page_7);
}
QString MainWindow::recupererVaccinsPatient(int patientID)
{
    QSqlQuery query;
    query.prepare(R"(
    SELECT VAC.NOM_VAC
    FROM VACCINS VAC
    JOIN INJECTIONS INJ ON VAC.ID_VAC = INJ.ID_VAC
    WHERE INJ.ID_PAT = :id
)");
    query.bindValue(":id",patientID);

    QStringList vaccins;
    if (query.exec()) {
        while (query.next()) {
            vaccins << query.value(0).toString();
        }
    } else {
        qDebug() << "❌ Erreur récupération vaccins : " << query.lastError().text();
    }

    return "Vaccins reçus : " + (vaccins.isEmpty() ? "Aucun" : vaccins.join(", "));
}
bool MainWindow::ajouterCertificatImageDansBDD(int patientID)
{
    // Chemin absolu vers le certificat généré
    QString imagePath = "C:/Users/justmalek/Desktop/c++/integ2/certificat.jpg";

    QFile file(imagePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "❌ Impossible d’ouvrir le fichier certificat.jpg pour lecture.";
        return false;
    }

    QByteArray imageData = file.readAll();
    file.close();

    QSqlQuery query;
    query.prepare("UPDATE PATIENTS SET CERTIFICAT = :image WHERE ID_PAT = :id");
    query.bindValue(":image", imageData);         // BLOB (image en binaire)
    query.bindValue(":id", patientID);

    if (!query.exec()) {
        qDebug() << "❌ Erreur SQL lors de l'insertion du certificat :" << query.lastError().text();
        return false;
    }

    qDebug() << "✅ Certificat enregistré avec succès pour le patient ID" << patientID;
    return true;
}
void MainWindow::genererCertificatImage(const Patient &patient)
{
    int patientID = patient.getId();  // Ajoute un getter getId() si nécessaire
    QString vaccinsText = recupererVaccinsPatient(patientID);

    // Générer le QR code avec ce texte
    using qrcodegen::QrCode;
    QrCode qr = QrCode::encodeText(vaccinsText.toUtf8().constData(), QrCode::Ecc::LOW);

    const int size = qr.getSize();
    QImage qrImage(size, size, QImage::Format_RGB32);
    qrImage.fill(Qt::white);
    for (int y = 0; y < size; ++y)
        for (int x = 0; x < size; ++x)
            if (qr.getModule(x, y))
                qrImage.setPixel(x, y, qRgb(0, 0, 0));
    QPixmap qrPixmap = QPixmap::fromImage(qrImage.scaled(130, 130)); // QR redimensionné

    // Création du certificat
    QPixmap certificatPixmap(900, 600);
    certificatPixmap.fill(Qt::white);

    QPainter painter(&certificatPixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    // En-tête
    QRect headerRect(0, 0, certificatPixmap.width(), 80);
    painter.fillRect(headerRect, QColor("#0d6efd"));
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 22, QFont::Bold));
    painter.drawText(headerRect, Qt::AlignCenter, "Certificat de Fin de Vaccination");

    // Bordure
    painter.setPen(QPen(Qt::gray, 2));
    painter.drawRect(10, 10, certificatPixmap.width() - 20, certificatPixmap.height() - 20);

    // Logo
    QPixmap logo("C:/Users/justmalek/Desktop/c++/vaxnestv2/icons/chahed_bhima-removebg-preview.png");
    if (!logo.isNull())
        painter.drawPixmap(30, 100, 100, 100, logo);

    // Infos
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 14));
    int leftMargin = 160;
    int top = 120;
    int lineSpacing = 40;

    painter.drawText(leftMargin, top, QString("Nom : %1").arg(patient.getNom()));
    painter.drawText(leftMargin, top + lineSpacing, QString("Prénom : %1").arg(patient.getPrenom()));
    painter.drawText(leftMargin, top + 2 * lineSpacing, QString("Date de naissance : %1").arg(patient.getDateNaissance().toString("dd/MM/yyyy")));
    painter.drawText(leftMargin, top + 3 * lineSpacing, QString("Vaccin complété le : %1").arg(QDate::currentDate().toString("dd/MM/yyyy")));

    // Texte vaccins visible
    painter.drawText(leftMargin, top + 5 * lineSpacing, vaccinsText);

    // Signature
    QFont font("Arial", 12, -1, true);
    painter.setFont(font);
    painter.drawText(certificatPixmap.width() - 300, certificatPixmap.height() - 100, "Signature du médecin");
    painter.drawLine(certificatPixmap.width() - 300, certificatPixmap.height() - 95, certificatPixmap.width() - 100, certificatPixmap.height() - 95);

    // QR code (en bas à gauche par exemple)
    painter.drawPixmap(30, certificatPixmap.height() - 180, qrPixmap);

    painter.end();

    QString filePath = "C:/Users/justmalek/Desktop/c++/integ2/certificat.jpg";
    if (!certificatPixmap.save(filePath, "JPG")) {
        qDebug() << "❌ Échec de sauvegarde du certificat.";
    } else {
        qDebug() << "✅ Certificat sauvegardé avec succès.";
    }
}
Patient MainWindow::getPatientById(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM PATIENTS WHERE ID_PAT = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        int id = query.value("ID_PAT").toInt();
        QString nom = query.value("NOM_PAT").toString();
        QString prenom = query.value("PRENOM_PAT").toString();
        QDate dateNaissance = query.value("DATENAIS_PAT").toDate();
        QString email = query.value("EMAIL").toString();
        QString genre = query.value("GENRE").toString();
        QString adresse = query.value("ADRESSE").toString();
        QString groupeSanguin = query.value("GROUPSANGUIN").toString();
        int tel = query.value("TEL").toInt();
        return Patient(id, nom, prenom, dateNaissance, email, genre, adresse, groupeSanguin,tel);
    } else {
        qDebug() << "Erreur : patient non trouvé ou erreur SQL :" << query.lastError().text();
        return Patient(); // patient vide
    }
}
void MainWindow::afficherCertificatDepuisBDD(int patientID)
{
    QSqlQuery query;
    query.prepare("SELECT CERTIFICAT FROM PATIENTS WHERE ID_PAT = :id");
    query.bindValue(":id", patientID);

    if (query.exec() && query.next()) {
        QByteArray imageData = query.value(0).toByteArray();

        if (imageData.isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Aucune image de certificat trouvée !");
            return;
        }

        QPixmap pixmap;
        pixmap.loadFromData(imageData);

        QLabel *label = ui->labelCertificat;  // Assure-toi qu'il existe dans page_5
        label->setPixmap(pixmap.scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    } else {
        QMessageBox::critical(this, "Erreur", "Impossible de charger le certificat depuis la base !");
    }
}

void MainWindow::envoyerCertificat(int patientID)
{
    qDebug() << "declaratient patient" ;
    Patient patient = getPatientById(patientID); // récupérez l'objet Patient
    qDebug() << "generation certificat";
    genererCertificatImage(patient);
    qDebug() << "Qrcode"  ;
    /*uploadCertificatViaPython();*/
    ajouterCertificatImageDansBDD(patient.getId());
    //affichege de certificat
    afficherCertificatDepuisBDD(patientID);
    ui->rapportettable->setCurrentWidget(ui->page_5);
}
#include "login.h"

void MainWindow::on_btnrendezv_2_clicked()
{
    this->close();

    Login *mainWindow = new Login();
    mainWindow->show();

}

