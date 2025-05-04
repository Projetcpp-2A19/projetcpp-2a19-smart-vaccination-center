#include "Login.h"
#include "ui_Login.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include "MotDePasseOublie.h"
#include "QFile"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    int ret = A.connect_arduino(); // lancer la connexion à Arduino
    switch(ret){
    case(0): qDebug() << "Arduino is available and connected to : " << A.getarduino_port_name(); break;
    case(1): qDebug() << "Arduino is available but not connected to : " << A.getarduino_port_name(); break;
    case(-1): qDebug() << "Arduino is not available"; break;
    }

    // Connexion signal série à notre slot
    QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(readRFID()));
}

Login::~Login()
{
    delete ui;
}

void Login::readRFID()
{
    static QByteArray fullUID;  // Utilisation d'une variable statique pour accumuler les données

    QByteArray uid_data = A.read_from_arduino();
    qDebug() << "[DEBUG UID brut depuis Arduino]:" << uid_data;

    fullUID.append(uid_data);  // Ajout des nouvelles données à l'UID complet

    // Cherche à savoir si la fin de l'UID est atteinte (fin de ligne typique des messages Arduino)
    if (fullUID.contains("\r\n")) {  // Vérifie la fin de l'UID
        QString uid = QString(fullUID).trimmed().replace(" ", "").toUpper();
        qDebug() << "[DEBUG UID nettoyé]:" << uid;

        if (uid.isEmpty()) {
            qDebug() << "[DEBUG] UID vide, aucun tag scanné.";
            return;
        }

        QSqlQuery query;
        query.prepare("SELECT NOM_MED, PRENOM_MED FROM MEDECINS WHERE RFID_UID = :uid");
        query.bindValue(":uid", uid);

        if (query.exec() && query.next()) {
            QString nom = query.value(0).toString();
            QString prenom = query.value(1).toString();
            QString nom_complet = nom + " " + prenom;

            A.write_to_arduino(nom_complet.toUtf8() + "\n");

            QMessageBox::information(this, "Connexion RFID", "Bonjour " + nom_complet);
            MainWindow *mainWindow = new MainWindow();
            mainWindow->show();
            this->close();
        } else {
            QMessageBox::warning(this, "Erreur RFID", "UID non reconnu.");
            A.write_to_arduino("Acces refuse\n");
        }

        // Réinitialiser pour le prochain UID
        fullUID.clear();
    }
}

void Login::on_pushButton_login_clicked()
{
    qDebug() << "[DEBUG] Bouton Login cliqué.";

    QString login = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();

    QSqlQuery query;

    if (!login.isEmpty() && !password.isEmpty()) {
        query.prepare("SELECT * FROM MEDECINS WHERE ID_MED = :login AND MDP = :password");
        query.bindValue(":login", login);
        query.bindValue(":password", password);

        if (query.exec() && query.next()) {
            MainWindow *mainWindow = new MainWindow();
            mainWindow->show();
            this->close();
        } else {
            QMessageBox::warning(this, "Erreur", "Identifiants incorrects.");
        }
    }
}

void Login::on_pushButton_mdp_oublie_clicked()
{
    MotDePasseOublie *fenetre = new MotDePasseOublie(this);
    fenetre->exec();
}
