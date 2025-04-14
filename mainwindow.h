#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>  // For the popup widget
#include <QPushButton>  // For the button
#include <QLabel>  // For the label inside the popup widget
#include "lab.h"
#include <QtCharts>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include "MarkerModel.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    // Le slot qui sera appelé lorsque l'utilisateur change la sélection dans le comboBox
    void on_comboBox_currentIndexChanged(int index); //TRI

private:
    // La fonction qui effectuera le tri par ID
    void trierParId();









public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void rechercher(); ///recherche
    void on_btnlabo5_clicked();//pdf
    //void afficherStatistiques();//stat
    // Fonction pour récupérer les coordonnées via géocodage
    void getCoordinatesFromAddress(const QString &address);
  // Q_INVOKABLE void geocodeAndAddLocation(const QString &location);
    //void updateMapMarkers() ;
   Q_INVOKABLE void searchLocation(const QString &address);


signals:
         //void addPinToMapSignal(double latitude, double longitude);
    Q_INVOKABLE void ajouterLaboratoireEPINGLE(double latitude, double longitude);

    void positionTrouvee(double latitude, double longitude);





private slots:

    void on_btnmedecin_clicked();  // Slot to handle btnmedecin click
    void on_btnmedecin2_clicked();
    void on_btnpatient_clicked();
    void on_btnpatient2_clicked();
    void on_btnvaccins_clicked();
    void on_btnvaccins2_clicked();
    void on_btnlabo_clicked();
    void on_btnlabo2_clicked();
    void on_btnlabo3_clicked();
    void on_btnlabo4_clicked();
    void on_btnrendezv_clicked();
    void on_btnrendezv2_clicked();
    void on_btnrendezv3_clicked();
    void on_btnequiprmrnt_clicked();
    void on_btnequiprmrnt2_clicked();
    void on_btnequiprmrnt3_clicked();
    void on_btnuser_clicked();
    void on_btnSupprimer_clicked(); //btn supp

    void on_btnModifier_clicked();
    void on_btnConfirmerModifier_clicked();







private:
    //Ui::MainWindow *ui;
    QWidget *popupWidget;  // The popup widget
    MarkerModel m_markerModel; //maps
private:
    int currentId;  // Stocke l'ID de l'élément en cours de modification
    QString originalNom;
    QString originalLocalisation;
    QString originalStatut;
    QString originalContact;
    bool modificationInProgress = false; // Indique si une modification est en cours


    // Detect clicks outside the popup
private slots:
    void on_pushButton_115_clicked();
    void onGeoCodeReply(QNetworkReply* reply);//MAP
    void updateTableView();
    void showStatistiques();
    void analyserCommande(); //chatbot
    void updateTableViewchat(QSqlQueryModel *model);//chatbot
    void updateTableViewchat();




private:
    Ui::MainWindow *ui;
    Lab labo;  // LABORATOIRE object
private://maps
    QNetworkAccessManager *networkManager;  // Gestionnaire de requêtes réseau
    double latitude = 0.0;
    double longitude = 0.0;




};

#endif // MAINWINDOW_H
