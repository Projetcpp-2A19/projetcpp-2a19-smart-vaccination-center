#include "mainwindow.h"
#include "patient.h"
#include "./ui_mainwindow.h"
#include <QMouseEvent>  // For detecting mouse events
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <cstdlib>  // Pour rand() et srand()
#include <ctime>    // Pour time()
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <ctime>
#include <QPainter>
#include <QPdfWriter>
#include <QSqlQuery>
#include <QSqlError>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QChart>
#include <QLineSeries>
#include <QPieSeries>
#include <QChartView>

#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

#include <QTemporaryFile>
#include <QBuffer>
#include <QDebug>
#include <QImage>
#include <QSslSocket>

#include "qrcode/qrcodegen.hpp"
using qrcodegen::QrCode;
using qrcodegen::QrSegment;
#include "mailing/smtpclient.h"
#include "mailing/emailaddress.h"
#include "mailing/mimehtml.h"
#include "mailing/mimeinlinefile.h"

#include <QBuffer>
#include <QImage>
#include <QFile>
#include <QDebug>
#include "mailing/mimemessage.h"
#include "mailing/mimehtml.h"
#include "mailing/mimeinlinefile.h"
#include "mailing/emailaddress.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  // Setup UI from Qt Designer
    connect(ui->tri, &QPushButton::clicked, this, &MainWindow::on_btn_tri_clicked);
    connect(ui->listpatient, &QPushButton::clicked, this, &MainWindow::on_listpatient_clicked);

    connect(ui->exit, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->recherche, &QPushButton::clicked, this, &MainWindow::on_btn_recherche_clicked);

    // Reference the existing popupWidget from the UI (it should be named popupWidget in the designer)
    popupWidget = ui->popupWidget;

    // Optionally, set the position and size of the popup widget (can be customized)
    popupWidget->setGeometry(200, 100, 200, 100);  // Set position and size of the popup

    // Initially hide the popup
    popupWidget->hide();

    // Connect button click to show or hide the popup
    connect(ui->btnmedecin, &QPushButton::clicked, this, &MainWindow::on_btnmedecin_clicked);
    // Initialisation de la table
    ui->tableau3_2->setColumnCount(8);
    ui->tableau3_2->setHorizontalHeaderLabels({"ID", "Nom", "Prénom", "Date Naissance", "Email", "Genre", "Adresse", "Groupe Sanguin"});
    ui->tableau3_2->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Charger les patients existants
    Patient p;
    p.afficher(ui->tableau3_2);
    /*ui->tableau->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau6->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);*/
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    ui->listpatient->setGraphicsEffect(effect);

    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(1000);      // 1 seconde
    animation->setStartValue(0.0);     // Transparent
    animation->setEndValue(1.0);       // Opaque
    animation->start(QAbstractAnimation::DeleteWhenStopped);

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnajouterpatient_clicked()
{
    // Génération d'un ID aléatoire
    std::srand(std::time(0));
    int min = 1, max = 100;
    int id = min + std::rand() % (max - min + 1);

    QString nom = ui->lineEdit_45->text().trimmed();
    QString prenom = ui->lineEdit_46->text().trimmed();
    QDate dateNaiss = ui->dateEdit_7->date();
    QString email = ui->lineEdit_47->text().trimmed();
    QString genre = ui->comboBox_9->currentText();
    QString adresse = ui->lineEdit_48->text().trimmed();
    QString groupeSanguin =ui->comboBox_6->currentText();


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

    QRegularExpression regexEmail("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.com$");
    if (!regexEmail.match(email).hasMatch()) {
        QMessageBox::warning(this, "Email invalide", "L'email doit être sous la forme exemple@domaine.com !");
        return;
    }

    Patient patient(id,nom,prenom,dateNaiss,email,genre,adresse,groupeSanguin);

    if (currentPatientId == -1) {
        if (patient.ajouter()) {
            QMessageBox::information(this, "Succès", "Patient ajouté avec succès !");
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de l'ajout du patient.");
        }
    } else {
        // 🔹 Modification d'un patient existant
        if (patient.modifierPatient(currentPatientId, nom, prenom, dateNaiss, email, genre, adresse, groupeSanguin)) {
            QMessageBox::information(this, "Succès", "Patient modifié avec succès !");
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la modification du patient.");
        }

        // Réinitialisation après modification
        currentPatientId = -1;
        ui->btnajouterpatient->setText("Ajouter");
        ui->btnajouterpatient->setStyleSheet("QPushButton {background-color: rgb(173, 216, 230); color: #ffffff;border: 2px solid rgb(173, 216, 230);padding: 10px;margin: 6px; border-radius: 12px;font-size: 15px;font-weight: bold;transition: all 0.3s ease-in-out;}QPushButton:hover {background-color: #606060;border-color: #777777;}QPushButton:pressed { background-color: #787878;border-color: #909090;}QPushButton:disabled {background-color: #353535;color: #ffffff;border-color: #444444;}");
    }

    patient.afficher(ui->tableau3_2); // Rafraîchir la liste des patients
    ui->rapportettable->setCurrentWidget(ui->page_5);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    // Detect if the click happens outside the popupWidget
    if (!popupWidget->geometry().contains(event->pos())) {
        popupWidget->hide();  // Hide the popup if clicked outside
    }
}
void MainWindow::supprimerPatient(int id)
{
    Patient p;
    if (p.supprimerPatient(id)) {
        QMessageBox::information(this, "Suppression réussie", "Le patient a été supprimé avec succès."+ QString::number(id));
        p.afficher(ui->tableau3_2); // Rafraîchir la liste
    }
}
void MainWindow::modifierPatient(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM PATIENTS WHERE ID_PAT = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        // Stocker l'ID du patient en modification
        currentPatientId = id;

        // Remplir le formulaire avec les données du patient sélectionné
        ui->lineEdit_45->setText(query.value("NOM_PAT").toString());
        ui->lineEdit_46->setText(query.value("PRENOM_PAT").toString());
        ui->dateEdit_7->setDate(query.value("DATENAIS_PAT").toDate());
        ui->lineEdit_47->setText(query.value("EMAIL").toString());
        ui->comboBox_9->setCurrentText(query.value("GENRE").toString());
        ui->lineEdit_48->setText(query.value("ADRESSE").toString());
        ui->comboBox_6->setCurrentText(query.value("GROUPSANGUIN").toString());

        // Changer le texte du bouton "Ajouter" en "Modifier"
        ui->btnajouterpatient->setText("Modifier");
        ui->btnajouterpatient->setStyleSheet("background-color: green; color: white; font-weight: bold; border-radius: 10px; padding: 8px;");
    } else {
        QMessageBox::critical(this, "Erreur","Impossible de récupérer les informations du patient." + QString::number(currentPatientId));
    }
}
void MainWindow::on_btn_recherche_clicked()
{
    QString rechercheNom = ui->lineEdit_50->text().trimmed();  // Supprime les espaces inutiles

    Patient patient;
    patient.afficherSpecifique(ui->tableau3_2, rechercheNom);  // Appel de la nouvelle fonction
}
void MainWindow::on_btn_tri_clicked()
{
    Patient patient;
    patient.afficherTrieParAnneeNaissance(ui->tableau3_2);  // Appelle la nouvelle fonction
}
void MainWindow::genererRapportPDF()
{
    QString filePath = QDir::homePath() + "/Desktop/c++/vaxnestv2/rapport_patient.pdf";
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
void MainWindow::on_btnpatient3_2_clicked()
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
    ui->page_6->setLayout(layout);
}

// Code du bouton pour afficher les statistiques
void MainWindow::on_btnpatient2_2_clicked()
{
    afficherStatistiques();
    ui->rapportettable->setCurrentWidget(ui->page_6);
}
void MainWindow::on_listpatient_clicked()
{
    Patient p;
    p.afficher(ui->tableau3_2);  // Charge les patients dans le tableau
    ui->rapportettable->setCurrentWidget(ui->page_5);
}
void MainWindow::genererCertificatImage(const Patient &patient)
{
    QPixmap certificatPixmap(900, 600);
    certificatPixmap.fill(Qt::white);

    QPainter painter(&certificatPixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    // Header banner
    QRect headerRect(0, 0, certificatPixmap.width(), 80);
    painter.fillRect(headerRect, QColor("#0d6efd")); // Blue banner
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 22, QFont::Bold));
    painter.drawText(headerRect, Qt::AlignCenter, "Certificat de Fin de Vaccination");

    // Draw a border
    painter.setPen(QPen(Qt::gray, 2));
    painter.drawRect(10, 10, certificatPixmap.width() - 20, certificatPixmap.height() - 20);

    // Add logo (if available)
    QPixmap logo(":/img/logo.png");  // Change to your actual resource/logo path
    if (!logo.isNull())
        painter.drawPixmap(30, 100, 100, 100, logo);

    // Info section
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 14));
    int leftMargin = 160;
    int top = 120;
    int lineSpacing = 40;

    painter.drawText(leftMargin, top, QString("Nom : %1").arg(patient.getNom()));
    painter.drawText(leftMargin, top + lineSpacing, QString("Prénom : %1").arg(patient.getPrenom()));
    painter.drawText(leftMargin, top + 2 * lineSpacing, QString("Date de naissance : %1").arg(patient.getDateNaissance().toString("dd/MM/yyyy")));
    painter.drawText(leftMargin, top + 3 * lineSpacing, QString("Vaccin complété le : %1").arg(QDate::currentDate().toString("dd/MM/yyyy")));

    // Signature area
    QFont font("Arial", 12, -1, true); // true pour italique
    painter.setFont(font);
    painter.drawText(certificatPixmap.width() - 300, certificatPixmap.height() - 100, "Signature du médecin");
    painter.drawLine(certificatPixmap.width() - 300, certificatPixmap.height() - 95, certificatPixmap.width() - 100, certificatPixmap.height() - 95);

    // Save image
    QString filePath = "C:/Users/justmalek/Desktop/c++/vaxnestv2/certificat.jpg";
    if (!certificatPixmap.save(filePath, "JPG")) {
        qDebug() << "❌ Failed to save certificate image at:" << filePath;
    } else {
        qDebug() << "✅ Certificate image saved at:" << filePath;
    }
}

bool MainWindow::ajouterCertificatImageDansBDD(int patientID)
{
    QString imagePath = "C:/Users/justmalek/Desktop/c++/vaxnestv2/certificat.jpg";

    QFile file(imagePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "❌ Impossible d’ouvrir le fichier certificat.jpg";
        return false;
    }

    QByteArray imageData = file.readAll(); // Lire l’image
    file.close();

    QSqlQuery query;
    query.prepare("UPDATE PATIENTS SET CERTIFICAT = :image WHERE ID_PAT = :id");
    query.bindValue(":image", imageData);
    query.bindValue(":id", patientID);

    if (!query.exec()) {
        qDebug() << "❌ Échec de l'enregistrement du certificat dans la base:" << query.lastError().text();
        return false;
    }

    qDebug() << "✅ Certificat image enregistré dans la base pour le patient ID" << patientID;
    return true;
}

QImage MainWindow::genererQRCodeAvecLienDrive()
{
    // Lien Google Drive transformé
    QString lienImage = "https://drive.google.com/uc?export=view&id=1HfaF1eGw_ZD8LK2qdx8fxhxuYCKZmW8y";

    using qrcodegen::QrCode;
    QrCode qr = QrCode::encodeText(lienImage.toUtf8().constData(), QrCode::Ecc::LOW);

    const int size = qr.getSize();
    QImage qrImage(size, size, QImage::Format_RGB32);
    qrImage.fill(Qt::white);

    for (int y = 0; y < size; ++y)
        for (int x = 0; x < size; ++x)
            if (qr.getModule(x, y))
                qrImage.setPixel(x, y, qRgb(0, 0, 0));

    return qrImage.scaled(200, 200);
}


void MainWindow::envoyerCertificatParEmail(const QString &emailDestinataire, const QImage &qrImage)
{
    // Setup SMTP client (Gmail with App Password)
    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);
    smtp.setUser("melekbenrejeb1919@gmail.com");
    smtp.setPassword("btlkydkksieygnww");  // ✅ App Password

    // Debug socket errors
    QObject::connect(smtp.getSocket(), &QSslSocket::errorOccurred, [](QAbstractSocket::SocketError err){
        qDebug() << "Socket error:" << err;
    });

    // Build the email message
    MimeMessage message;
    EmailAddress from("melekbenrejeb1919@gmail.com", "malekbenrejeb");
    EmailAddress to(emailDestinataire, "Destinataire");

    message.setSender(from);
    message.addRecipient(to);
    message.setSubject("Votre certificat de fin de vaccination");

    // HTML body
    MimeHtml *html = new MimeHtml;
    html->setHtml(R"(
        <html>
        <body style="font-family: Arial, sans-serif; background-color: #f5f5f5; padding: 20px;">
            <h2 style="color: #0d6efd;">🎉 Félicitations !</h2>
            <p>Vous avez complété votre vaccination. Veuillez trouver ci-dessous votre certificat.</p>
            <p>📎 Scannez ce QR Code pour télécharger votre certificat :</p>
            <img src="cid:qrimage" width="200" height="200" alt="QR code">
            <p style="margin-top: 20px;">Merci de votre confiance.</p>
        </body>
        </html>
    )");

    // 1. Save QR image as "certificat.png"
    QString qrPath = "C:/Users/justmalek/Desktop/c++/vaxnestv2/certificat.png";

    // Save QR to file
    QFile *qrFile = new QFile(qrPath);
    if (!qrFile->open(QIODevice::WriteOnly)) {
        qDebug() << "❌ Failed to write QR image to:" << qrPath;
        return;
    }
    qrImage.save(qrFile, "PNG");
    qrFile->close();

    // Reopen for reading to embed in email
    if (!qrFile->open(QIODevice::ReadOnly)) {
        qDebug() << "❌ Failed to reopen QR image for reading!";
        return;
    }

    // 2. Attach QR image as inline file
    MimeInlineFile *qrAttachment = new MimeInlineFile(qrFile);
    qrAttachment->setContentType("image/png");
    qrAttachment->setContentId("qrimage"); // must match <img src="cid:qrimage">
    qrAttachment->setEncoding(MimePart::Base64);

    // 3. Add parts to the message
    message.addPart(html);
    message.addPart(qrAttachment);

    // 4. SMTP send process
    smtp.connectToHost();
    if (!smtp.waitForReadyConnected()) {
        qDebug() << "❌ Failed to connect to host!";
        return;
    }

    smtp.login("melekbenrejeb1919@gmail.com","btlkydkksieygnww");
    if (!smtp.waitForAuthenticated()) {
        qDebug() << "❌ Login failed! Check app password.";
        return;
    }

    smtp.sendMail(message);
    if (!smtp.waitForMailSent()) {
        qDebug() << "❌ Failed to send email!";
    } else {
        qDebug() << "✅ Email sent successfully to:" << emailDestinataire;
    }

    smtp.quit();
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

        return Patient(id, nom, prenom, dateNaissance, email, genre, adresse, groupeSanguin);
    } else {
        qDebug() << "Erreur : patient non trouvé ou erreur SQL :" << query.lastError().text();
        return Patient(); // patient vide
    }
}

void MainWindow::envoyerCertificat(int patientID)
{
    qDebug() << "declaratient patient" ;
    Patient patient = getPatientById(patientID); // récupérez l'objet Patient
    qDebug() << "generation certificat";
    genererCertificatImage(patient);
    qDebug() << "Qrcode"  ;
    ajouterCertificatImageDansBDD(patient.getId());
    QImage qrCode = genererQRCodeAvecLienDrive();
    qDebug() << "1:";
    envoyerCertificatParEmail(patient.getEmail().trimmed(), qrCode);
    qDebug() << "mail envoyer!:" << patientID;
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





