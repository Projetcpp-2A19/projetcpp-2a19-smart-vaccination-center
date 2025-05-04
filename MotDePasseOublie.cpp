#include "MotDePasseOublie.h"
#include "ui_MotDePasseOublie.h"
#include <QMessageBox>
#include <QSqlQuery>

MotDePasseOublie::MotDePasseOublie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MotDePasseOublie)
{
    ui->setupUi(this);
}

MotDePasseOublie::~MotDePasseOublie()
{
    delete ui;
}

void MotDePasseOublie::on_pushButton_valider_clicked()
{
    QString login = ui->lineEdit_login->text();
    QString reponse = ui->lineEdit_reponse->text();
    QString newPassword = ui->lineEdit_newPassword->text();

    QSqlQuery query;
    query.prepare("SELECT * FROM MEDECINS WHERE ID_MED = :login AND REPONSE = :reponse");
    query.bindValue(":login", login);
    query.bindValue(":reponse", reponse);

    if (query.exec() && query.next()) {
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE MEDECINS SET MDP = :newPassword WHERE ID_MED = :login");
        updateQuery.bindValue(":newPassword", newPassword);
        updateQuery.bindValue(":login", login);

        if (updateQuery.exec()) {
            this->close();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de mise à jour du mot de passe.");
        }
    } else {
        QMessageBox::warning(this, "Erreur", "Identifiants ou réponse incorrecte.");
    }
}
