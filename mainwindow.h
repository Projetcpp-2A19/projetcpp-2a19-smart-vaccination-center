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
    void on_comboBox_38_currentIndexChanged(int index);
    void on_lineEdit_134_textChanged(const QString &searchTerm);
    void showStatistiques_rdv();
    void chargerRendezVousDansCalendrier();
    void on_calendarWidget_clicked(const QDate &date);
    void on_pushButton_194_clicked();

private:
    Ui::MainWindow *ui;
    QWidget *popupWidget;  // The popup widget
    QNetworkAccessManager *networkManager;
    Vaccin vac;
    int mod=0;

    Arduino A;
    QTimer *timer;
    QString dernierTexteLabel;
    QTimer* labelWatchTimer;

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

    bool modificationInProgress = false; // Indicateur de modification en cours

};

#endif // MAINWINDOW_H
