#include "Login.h"
#include "ui_Login.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include "MotDePasseOublie.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_login_clicked()
{
    QString login = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();

    QSqlQuery query;
    query.prepare("SELECT * FROM MEDECINS WHERE ID_MED = :login AND MDP = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        QMessageBox::information(this, "Connexion", "Connexion réussie !");

        MainWindow *mainWindow = new MainWindow();
        mainWindow->show();
        this->close();  // Ferme la fenêtre Login
    } else {
        QMessageBox::warning(this, "Erreur", "Identifiants incorrects.");
    }
}
void Login::on_pushButton_mdp_oublie_clicked()
{
    MotDePasseOublie *fenetre = new MotDePasseOublie(this);
    fenetre->exec();
}
