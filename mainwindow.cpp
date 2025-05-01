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
    popupWidget = ui->popupWidget;

    // Optionally, set the position and size of the popup widget (can be customized)
    popupWidget->setGeometry(200, 100, 200, 100);  // Set position and size of the popup

    // Initially hide the popup
    popupWidget->hide();

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
    showStockPieChart();
    //ui->sqs->setCurrentIndex(14);
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
