#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("malek");
    db.setPassword("malek1111");

    if (db.open())
        test=true;





    return  test;
}
void Connection::closeconnect(){db.close();}
