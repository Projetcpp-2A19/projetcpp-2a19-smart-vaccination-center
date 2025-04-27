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
#include "Vaccin.h"
#include "Medecin.h"
#include "arduino.h"


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
    ui->tableau6->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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

