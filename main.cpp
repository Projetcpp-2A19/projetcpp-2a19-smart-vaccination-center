#include <QApplication>
#include <QMessageBox>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QGeoCoordinate>
#include "MarkerModel.h"
#include "connection.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);  // Utiliser QApplication pour intégrer Qt avec QML

    // Connexion à la base de données
    Connection c;
    if (c.createconnect()) {
        QMessageBox::information(nullptr, QObject::tr("Database Open"),
                                 QObject::tr("Connection successful.\nClick OK to continue."), QMessageBox::Ok);

        // Crée et affiche la fenêtre principale
        MainWindow w;


        // Crée le moteur QML xhargment de modelle qml
        QQmlApplicationEngine engine;
        engine.rootContext()->setContextProperty("mainWindow", &w);

        // Instanciation du modèle de marqueurs
        MarkerModel markerModel;
        qmlRegisterType<MarkerModel>("com.example", 1, 0, "MarkerModel"); // Enregistre le type MarkerModel
        markerModel.loadFromJson(); // ✅ charge depuis MarkerModel

        qDebug() << "Nombre de marqueurs après chargement du JSON:" << markerModel.rowCount();


        // Expose les objets C++ à QML
        engine.rootContext()->setContextProperty("markerModel", &markerModel); // Expose le modèle
        engine.rootContext()->setContextProperty("mainWindow", &w); // Expose la fenêtre principale

        // Exemple d'ajout de marqueur
        QGeoCoordinate coord(36.8002, 10.1858);  // Crée une coordonnée
       // markerModel.addMarker(coord);  // Ajoute cette coordonnée au modèle

        // Charge le fichier QML
        engine.load(QUrl(QStringLiteral("qrc:/map.qml")));  // Charge le fichier QML

        // Vérifie si l'application QML a bien été chargée
        if (engine.rootObjects().isEmpty()) {
            return -1;
        }

        // Affiche la fenêtre principale Qt après avoir chargé QML
        w.show();  // Affiche la fenêtre principale qui peut inclure QML




        return app.exec();  // Exécute l'application
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database Not Open"),
                              QObject::tr("Connection failed.\nClick OK to exit."), QMessageBox::Ok);
        return 0;  // Quitter l'application si la connexion échoue
    }
}
