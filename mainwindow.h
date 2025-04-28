#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>  // For the popup widget
#include <QPushButton>  // For the button
#include <QLabel>  // For the label inside the popup widget
#include <QtCharts>
#include "equipements.h"
#include "arduino.h"
#include "Vaccin.h"

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
    void on_btnuser_clicked();
    void on_btnvoice_clicked();

public:
    void updateTableView();

private:
    //Ui::MainWindow *ui;
    QWidget *popupWidget;  // The popup widget

private slots:
    void update_fridge_status();

private:
    QByteArray data;
    Arduino A;

private:
    bool modificationInProgress = false; // Track if modification has started
    int mod=0;

private slots:
    void on_btnequipementAjouter_clicked();  // Slot for adding equipment
    void afficherEquipements();  // Function to display data in the table
    void on_btnSupprimer_clicked(); //btn supp
    void on_btnModifier_clicked();
    void on_btnConfirmerModifier_clicked();
    void on_lineEdit_54_textChanged(const QString &searchTerm);
    void on_btnequiprmrnt4_clicked();
    void showStatistiques();
    void on_panneButton_clicked();  // Handle "Panne" button click
    void showPanneNotification(const QString &equipementNom); // Display scrolling notification

    void on_submit_clicked();
    void on_del_clicked();
    void on_pushButton_159_clicked();

private:
    int currentId;              // id of the currently selected equipment
    QString originalNom;        // original name loaded from table
    QString originalType;       // original type loaded from table
    QString originalStatut;     // original status loaded from table
    QString originalDescription;
    QDate originalDate;

    QSortFilterProxyModel *proxyModel;

private:
    Ui::MainWindow *ui;
    Equipement equipement;  // Equipement object
    Vaccin vac;

};

#endif // MAINWINDOW_H
