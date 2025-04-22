#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>  // For the popup widget
#include <QPushButton>  // For the button
#include <QLabel>  // For the label inside the popup widget
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include "Vaccin.h"
#include "smtpclient.h"
#include "mimemessage.h"
#include "mimepart.h"
#include "mimetext.h"
#include "sms.h"

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

    void on_btnuser_clicked();


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

private:
    Ui::MainWindow *ui;
    QWidget *popupWidget;  // The popup widget
    Vaccin vac;
    int mod=0;
};

#endif // MAINWINDOW_H
