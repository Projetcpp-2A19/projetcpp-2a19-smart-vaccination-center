#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>  // For the popup widget
#include <QPushButton>  // For the button
#include <QLabel>  // For the label inside the popup widget
#include <QSqlQueryModel>  // Pour afficher les données dans tableau2
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QSqlQuery>
#include <QSqlError>
#include <QVBoxLayout>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDesktopServices>
#include <QDate>
#include <QMainWindow>
#include <QWidget>  // For the popup widget
#include <QPushButton>  // For the button
#include <QLabel>  // For the label inside the popup widget
#include <QtCharts>
#include <QCalendarWidget>
#include <QTableWidget>
#include <QTextCharFormat>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QNetworkAccessManager>  // Ajout pour les requêtes HTTP
#include <QNetworkReply>
#include "Vaccin.h"
#include "Medecin.h"
#include "smtpclient.h"
#include "mimemessage.h"
#include "mimepart.h"
#include "mimetext.h"
#include "sms.h"
#include "arduino.h"
#include "MarkerModel.h"
#include"lab.h"


//using namespace QtCharts;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void rechercher_labo(); ///recherche
    void on_btnlabo5_clicked();//pdf

    // Fonction pour récupérer les coordonnées via géocodage
    void getCoordinatesFromAddress(const QString &address);

    Q_INVOKABLE void searchLocation(const QString &address);
    void traiterDemandeAcces();
    void update_label();
signals:
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
    void on_btnrendezv2_2_clicked();
    void on_btnrendezv3_2_clicked();
    void on_btnequiprmrnt_clicked();
    void on_btnequiprmrnt2_clicked();
    void on_btnequiprmrnt3_clicked();
    void updateTableView();
    void updateTableViewRV();

    void on_btnuser_clicked();
    void ajouterMedecin(); // Slot pour gérer l'ajout d'un médecin
    void afficherMedecins(); // Fonction pour afficher les médecins dans tableau2
    void on_pushButton_mod_clicked();
    void on_b_supp_clicked();
    void on_comboBoxtri_currentIndexChanged(int);
    void on_b_chercher_clicked();
    void afficherStat();
    void exporterPDF();

    void on_submit_clicked();
    void on_del_clicked();
    void on_pushButton_159_clicked();
    void applyFilter(const QString &text);  // Added filter method
    void onSortChanged(int index);  // Slot to handle QComboBox selection change
    void on_pdfButton_clicked();
    void on_emailButton_clicked();
    void on_sms_clicked();
    void checkLowStockAndNotify();
    void sendStockAlertEmail(const QString &nom, const QString &type, const QString &pays, int stock);
    void showStockPieChart();
    void mousePressEvent(QMouseEvent *event);


    void on_pushButton_193_clicked();

    //void on_btnuser_clicked();
    void on_btnsupp_2_clicked(); //btn supp

    void on_btnmodif_2_clicked();
    void on_btncmodif_2_clicked();
    void on_btnrendezv4_2_clicked();
    void on_comboBox_46_currentIndexChanged(int index);
    void on_lineEdit_134_textChanged(const QString &searchTerm);
    void showStatistiques_rdv();
    void chargerRendezVousDansCalendrier();
    void on_calendarWidget_clicked(const QDate &date);
    void on_pushButton_194_clicked();



    void on_btnSupprimer_labo_clicked(); //btn supp
    void on_btnModifier_labo_clicked();
    void on_btnConfirmerModifier_labo8_clicked();



private:
    Ui::MainWindow *ui;
    QWidget *popupWidget;  // The popup widget
    QNetworkAccessManager *networkManager;
     Lab labo;  // LABORATOIRE object
    Vaccin vac;
    int mod=0;

    Arduino A;
    QTimer *timer;
    QString dernierTexteLabel;
    QTimer* labelWatchTimer;
    MarkerModel m_markerModel; //maps

    void afficherRendezVous();              // Affichage par défaut
    void afficherRendezVousTrieParPriorite(const QString &ordre);   // Affichage trié par priorité
    void afficherRendezVousTrieParDate(const QString &ordre);    // Affichage trié par date
    void verifierIDDepuisArduino();
    //void verifierRendezVousDepuisLabel();
    void verifierRendezVousEtCommanderServo(QString id);



protected:
    void showEvent(QShowEvent *event) override;


private:
    int currentId;       // ID du rendez-vous sélectionné
    QDate originalDate;  // Date du rendez-vous avant modification
    QTime originalHeure; // Heure du rendez-vous avant modification
    QString originalPriorite; // Priorité du rendez-vous avant modification
    QString originalStatus;   // Statut du rendez-vous avant modification
    int originalIdPat;   // ID du patient lié au rendez-vous
 void trierParId_labo();
    bool modificationInProgress = false; // Indicateur de modification en cours

    int currentIdL;  // Stocke l'ID de l'élément en cours de modification
    QString originalNomL;
    QString originalLocalisationL;
    QString originalStatutL;
    QString originalContactL;
    bool modificationInProgressL = false; // Indique si une modification est en cours
private slots:
    void on_pushButton_labo7_clicked();
    void onGeoCodeReply(QNetworkReply* reply);//MAP
    void updateTableView_labo();
    void showStatistiques_labo();
    void analyserCommande(); //chatbot
    void updateTableViewchat(QSqlQueryModel *model);//chatbot
    void updateTableViewchat();
    void on_comboBox_labo6_currentIndexChanged(int index); //TRI
private://maps
    //QNetworkAccessManager *networkManager;  // Gestionnaire de requêtes réseau
    double latitude = 0.0;
    double longitude = 0.0;

};

#endif // MAINWINDOW_H
