#include "connection.h"
#include <QSqlError>
#include <QDebug>

Connection::Connection(){}

bool Connection::createconnection(){
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("Source_Projet2A");//inserer le nom de la source de données
    db.setUserName("dhia");//inserer nom de l'utilisateur
    db.setPassword("esprit2004");//inserer mot de passe de cet utilisateur

    if (db.open()){
        test=true;
    }
    return  test;
}

void Connection::closeConnection(){
    db.close();
    //qDebug() << " Database connection closed!";
}
