#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMouseEvent>  // For detecting mouse events
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include "lab.h"
#include <QString>
#include <QMessageBox>
#include <QSqlError>
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



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  // Charge l'interface

    // Initialisation du gestionnaire de réseau
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

    // Configuration d'autres éléments de l'interface
    connect(ui->btnRechercher, &QPushButton::clicked, this, &MainWindow::rechercher);
    connect(ui->btnlabo5, &QPushButton::clicked, this, &MainWindow::on_btnlabo5_clicked);
    connect(ui->chatbot, &QPushButton::clicked, this, &MainWindow::analyserCommande);
    connect(ui->btnSupprimer, &QPushButton::clicked, this, &MainWindow::on_btnSupprimer_clicked);

    Lab Etmp;
    ui->tableau->setModel(Etmp.afficher());


    // Dans le main.cpp ou autre fichier où tu charges QML
    QQmlApplicationEngine engine;
    MarkerModel markerModel;  // Instancie ton modèle

    // Expose le modèle à QML
    engine.rootContext()->setContextProperty("markerModel", &markerModel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));  // Charge le fichier QML


    // Ajustement automatique des colonnes dans les tableaux
    ui->tableau->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableau6->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
    qDebug() << "Button btnequiprmrnt2 clicked!";
    if (!ui->chartContainer) {                             //ken chartContainer mouch mawjouda
        qDebug() << "ERROR: chartContainer is NULL!";
        return;
    }

    showStatistiques();

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
    ui->tableau->setModel(labo.afficher());  // Charger les nouvelles données
    ui->tableau->viewport()->update();       // Rafraîchir l'affichage
}

void MainWindow::on_comboBox_currentIndexChanged(int)
{
    trierParId();
}



void MainWindow::on_pushButton_115_clicked() {
    // Récupération des données depuis l'interface utilisateur
    int id = ui->lineEdit_18->text().toInt();
    QString nom = ui->lineEdit_19->text();
    QString localisation = ui->lineEdit_20->text();
    QString status = ui->comboBox_2->currentText();
    QString contact = ui->lineEdit_22->text();

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
    bool test = labo.ajouter();

    // Vérification du succès de l'ajout
    if (test) {
        QMessageBox::information(this, tr("Succès"), tr("Ajout effectué avec succès."));

        // Mise à jour de la table après ajout
        updateTableView();
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Ajout non effectué."));
    }
    m_markerModel.addMarker(QGeoCoordinate(latitude, longitude));


}





void MainWindow::on_btnSupprimer_clicked() {
    // Récupérer l'ID sélectionné
    QModelIndex index = ui->tableau->selectionModel()->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Suppression"), tr("Veuillez sélectionner un élément à supprimer."));
        return;
    }

    int id = ui->tableau->model()->data(ui->tableau->model()->index(index.row(), 0)).toInt();  // Supposons que l'ID est en 1ère colonne

    // Confirmation
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Suppression"), tr("Voulez-vous vraiment supprimer cet élément ?"),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        Lab labo;
        if (labo.supprimer(id)) {
            QMessageBox::information(this, tr("Suppression"), tr("Suppression réussie."));
            updateTableView();  // Rafraîchir la table après suppression
        } else {
            QMessageBox::critical(this, tr("Erreur"), tr("Échec de la suppression."));
        }
    }
}






void MainWindow::on_btnModifier_clicked() {
    // Récupérer la ligne sélectionnée
    QModelIndex index = ui->tableau->selectionModel()->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, tr("Modification"), tr("Veuillez sélectionner un laboratoire à modifier."));
        return;
    }

    // Récupérer les données du tableau
    currentId = ui->tableau->model()->data(ui->tableau->model()->index(index.row(), 0)).toInt();
    originalNom = ui->tableau->model()->data(ui->tableau->model()->index(index.row(), 1)).toString();
    originalLocalisation = ui->tableau->model()->data(ui->tableau->model()->index(index.row(), 2)).toString();
    originalStatut = ui->tableau->model()->data(ui->tableau->model()->index(index.row(), 3)).toString();
    originalContact = ui->tableau->model()->data(ui->tableau->model()->index(index.row(), 4)).toString();

    // Remplir les champs du formulaire de modification
    ui->lineEdit_18->setText(QString::number(currentId));
    ui->lineEdit_19->setText(originalNom);
    ui->lineEdit_20->setText(originalLocalisation);
    ui->lineEdit_22->setText(originalContact);



    modificationInProgress = true; // Indiquer qu'une modification est en cours
}

// Fonction pour rafraîchir l'affichage





void MainWindow::on_btnConfirmerModifier_clicked() {
    // Vérifier si une modification est en cours
    if (!modificationInProgress) {
        QMessageBox::warning(this, tr("Erreur"), tr("Veuillez d'abord sélectionner un laboratoire à modifier en cliquant sur 'Modifier'."));
        return;
    }

    // Récupérer les nouvelles valeurs depuis les champs de saisie
    QString newNom = ui->lineEdit_19->text();
    QString newLocalisation = ui->lineEdit_20->text();
    QString newStatut = ui->comboBox_2->currentText();
    QString newContact = ui->lineEdit_22->text();

    // Vérifier si aucun changement n'a été effectué
    if (newNom == originalNom && newLocalisation == originalLocalisation &&
        newStatut == originalStatut && newContact == originalContact) {
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
    if (newNom != originalNom) {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM LABORATOIRES WHERE  NOM_LAB = :nom");
        query.bindValue(":nom", newNom);
        if (query.exec() && query.next() && query.value(0).toInt() > 0) {
            QMessageBox::warning(this, tr("Erreur"), tr("Un laboratoire avec ce nom existe déjà !"));
            return;
        }
    }

    // Mise à jour des informations du laboratoire
    Lab labo(currentId, newNom, newLocalisation, newStatut, newContact);
    if (labo.modifier(currentId)) {
        QMessageBox::information(this, tr("Modification"), tr("Modification réussie."));
        updateTableView();  // Rafraîchir la table après modification

        modificationInProgress = false; // Réinitialiser le flag
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de la modification."));
    }
}






// Déclare le modèle au niveau de la classe pour le réutiliser
QSqlQueryModel *model = new QSqlQueryModel();

void MainWindow::trierParId() {
    QString triOption = ui->comboBox->currentText();
    QSqlQuery query;

    // Vérification de l'option sélectionnée
    if (triOption == "ID") {
        query.prepare("SELECT * FROM LABORATOIRES ORDER BY ID_LAB ASC");
    } else {
        query.prepare("SELECT * FROM LABORATOIRES");  // Tri par défaut
    }

    // Exécuter la requête et vérifier les erreurs
    if (!query.exec()) {
        qDebug() << "Erreur lors du tri :" << query.lastError().text();
        return;
    }

    // Appliquer le modèle à la table
    model->setQuery(std::move(query));
    ui->tableau->setModel(model);
    ui->tableau->resizeColumnsToContents();
}



void MainWindow::rechercher() {

    QString recherche = ui->lineEdit_24->text().trimmed();

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

















#include <QPdfWriter>
#include <QPainter>
#include <QSqlQuery>
#include <QMessageBox>
#include <QFileDialog>

void MainWindow::on_btnlabo5_clicked() {//PDF
    QString fileName = QFileDialog::getSaveFileName(this, tr("Enregistrer le rapport"), "", tr("Fichiers PDF (*.pdf)"));
    if (fileName.isEmpty()) {
        return;
    }

    QPdfWriter writer(fileName);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(300);

    QPainter painter;
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
void MainWindow::showStatistiques() {
    if (!ui->chartContainer) {
        qDebug() << "❌ ERROR: chartContainer is NULL!";
        return;
    }

    // Ensure chartContainer has a layout
    if (!ui->chartContainer->layout()) {
        ui->chartContainer->setLayout(new QVBoxLayout());  // Assign a layout if missing
    }

    // Remove old charts
    QLayoutItem* item;
    while ((item = ui->chartContainer->layout()->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->chartContainer->layout());


    // 📊 Pie Chart (Type Distribution)
    QPieSeries *pieSeries = new QPieSeries();
    QMap<QString, int> statsType = labo.getStatistiquesParstatus();
    if (statsType.isEmpty()) {
        qDebug() << "⚠️ WARNING: No data found for equipment types!";
    }
    for (auto it = statsType.begin(); it != statsType.end(); ++it) {
        pieSeries->append(it.key(), it.value());
    }
    QChart *pieChart = new QChart();
    pieChart->addSeries(pieSeries);
    pieChart->setTitle("Répartition des laboratoires par status");
    layout->addWidget(new QChartView(pieChart));

    ui->chartContainer->setLayout(new QVBoxLayout());
    qDebug() << "✅ Statistics updated successfully!";
}

//chatbot




void MainWindow::analyserCommande()
{
    QString commande = ui->lineEditchat->text();  // Récupérer la commande entrée par l'utilisateur

    if (!commande.isEmpty()) {
        // Analyser la commande via l'objet Lab
        labo.analyserCommande(commande);

        // Mettre à jour l'affichage du tableau après la commande
        updateTableViewchat();
    } else {
        // Afficher un message d'erreur si la commande est vide
        QMessageBox::warning(this, "Commande vide", "Veuillez entrer une commande valide.");
    }
}

void MainWindow::updateTableViewchat()
{
    // Créer un modèle pour afficher les laboratoires
    QSqlQueryModel *model = labo.afficher();

    if (model != nullptr) {
        ui->tableViewchatbot->setModel(model);  // Mettre à jour l'affichage du QTableView
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de charger les données du chatbot.");
    }
}

//*********************maps


// Fonction pour traiter la réponse de géocodage
void MainWindow::onGeoCodeReply(QNetworkReply* reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Erreur de géocodage : " << reply->errorString();
        return;
    }

    // Parse la réponse JSON
    QByteArray response = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(response);
    QJsonArray jsonArray = doc.array();

    // Vérifie si la réponse contient des résultats
    if (!jsonArray.isEmpty()) {
        // Récupère les coordonnées de la première entrée
        QJsonObject firstResult = jsonArray.first().toObject();
        double latitude = firstResult["lat"].toString().toDouble();
        double longitude = firstResult["lon"].toString().toDouble();

        // Vérification des coordonnées avant de les émettre
        if (std::isnan(latitude) || std::isnan(longitude) || latitude == 0 || longitude == 0) {
            qDebug() << "Coordonnées invalides reçues : " << latitude << ", " << longitude;
        } else {
            // Affiche les coordonnées
            qDebug() << "Latitude : " << latitude << ", Longitude : " << longitude;

            // Émet le signal pour ajouter un marqueur sur la carte
            emit ajouterLaboratoireEPINGLE(latitude, longitude);
        }
    } else {
        qDebug() << "Aucune coordonnée trouvée pour l'adresse.";
    }

    reply->deleteLater();
}
