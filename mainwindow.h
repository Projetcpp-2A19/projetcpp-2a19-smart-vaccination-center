
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>  // For the popup widget
#include <QPushButton>  // For the button
#include <QLabel>  // For the label inside the popup widget

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
    void supprimerPatient(int id);
    void modifierPatient(int id);
    int currentPatientId = -1;

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
    void on_btnajouterpatient_clicked();
    void on_btn_recherche_clicked();
    void on_btn_tri_clicked();
    void genererRapportPDF();
    void on_btnpatient3_2_clicked();
    void afficherStatistiques();
    void on_btnpatient2_2_clicked();
    void on_listpatient_clicked();
private:

    Ui::MainWindow *ui;
    QWidget *popupWidget;  // The popup widget
protected:
    void mousePressEvent(QMouseEvent *event) override;  // Detect clicks outside the popup
};

#endif // MAINWINDOW_H
