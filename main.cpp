#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    MainWindow w;
    Login l;





    bool test=c.createconnect();
    if(test)
    {l.show();
        QSqlQueryModel * afficherEquipements();
        w.updateTableViewEquipement();
        /*QMessageBox::information(nullptr, QObject::tr("database is open"),
                                 QObject::tr("connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);*/

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);



    a.setStyleSheet(R"(
        QMessageBox {
            background-color: #1e1e2f;
            color: #ecf0f1;
            font-family: 'Segoe UI';
            font-size: 16px;
            border: 2px solid #34495e;
            border-radius: 12px;
            padding: 12px;
        }

        QMessageBox QLabel {
            color: #ecf0f1;
            font-size: 16px;
            padding: 10px;
        }

        QPushButton {
            background-color: qlineargradient(
                spread:pad,
                x1:0, y1:0, x2:1, y2:1,
                stop:0 #3498db,
                stop:1 #2980b9
            );
            color: white;
            font-weight: bold;
            border: none;
            border-radius: 10px;
            padding: 8px 18px;
            min-width: 80px;
            margin: 6px;
            box-shadow: 2px 2px 8px rgba(0, 0, 0, 0.4);
        }

        QPushButton:hover {
            background-color: #1abc9c;
        }

        QPushButton:pressed {
            background-color: #16a085;
        }
    )");


    return a.exec();
}
