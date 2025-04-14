#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMouseEvent>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include "Medecin.h"
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QVBoxLayout>
#include <QWidget>
#include <QPainter>
#include <QProgressBar>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDate>
#include <QPageSize>
#include <QFont>
#include <QLabel>
#include <QDebug>

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



