#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_login_clicked();
    void on_pushButton_mdp_oublie_clicked();
    void readRFID(); // Slot appelé automatiquement à chaque nouvelle lecture Arduino
private:
    Ui::Login *ui;
    Arduino A;
    bool hasProcessed = false;
};

#endif // LOGIN_H
