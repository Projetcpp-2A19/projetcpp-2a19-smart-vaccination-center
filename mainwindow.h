#ifndef MAINWINDOW_H
#define MAINWINDOW_H
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
#include <QNetworkReply>          // Pour gérer les réponses des requêtes

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
    void on_btnrendezv2_clicked();
    void on_btnrendezv3_clicked();
    void on_btnequiprmrnt_clicked();
    void on_btnequiprmrnt2_clicked();
    void on_btnequiprmrnt3_clicked();
    void on_pushButton_180_clicked();

    void on_btnuser_clicked();
    void on_btnsupp_clicked(); //btn supp

    void on_btnmodif_clicked();
    void on_btncmodif_clicked();
    void on_btnrendezv4_clicked();
    void on_comboBox_38_currentIndexChanged(int index);
    void on_lineEdit_118_textChanged(const QString &searchTerm);
    void showStatistiques_rdv();
    void chargerRendezVousDansCalendrier();
    void on_calendarWidget_clicked(const QDate &date);
    //void afficherRdv();
    void envoyerRappelRendezVous();
    //void on_pushButton_187_clicked();
private:
    int currentId;       // ID du rendez-vous sélectionné
    QDate originalDate;  // Date du rendez-vous avant modification
    QTime originalHeure; // Heure du rendez-vous avant modification
    QString originalPriorite; // Priorité du rendez-vous avant modification
    QString originalStatus;   // Statut du rendez-vous avant modification
    int originalIdPat;   // ID du patient lié au rendez-vous

    bool modificationInProgress = false; // Indicateur de modification en cours

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager; // Gestionnaire de requêtes HTTP
    QWidget *popupWidget;  // The popup widget
    void updateTableView();
    void afficherRendezVous();              // Affichage par défaut
    void afficherRendezVousTrieParPriorite(); // Affichage trié par priorité
    void afficherRendezVousTrieParDate();    // Affichage trié par date
protected:
    void mousePressEvent(QMouseEvent *event) override;  // Detect clicks outside the popup
};


#endif // MAINWINDOW_H
