/********************************************************************************
** Form generated from reading UI file 'Login.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QStackedWidget *stackedWidget_2;
    QWidget *medecin_2;
    QLabel *label_13;
    QWidget *Patient_2;
    QLabel *label_14;
    QWidget *Labo_2;
    QLineEdit *lineEdit_login;
    QLineEdit *lineEdit_password;
    QPushButton *pushButton_login;
    QLabel *label;
    QLabel *label_2;
    QWidget *widget_4;
    QPushButton *btnuser;
    QWidget *widget_2;
    QPushButton *pushButton_14;
    QLabel *label_4;
    QLabel *label_9;
    QPushButton *pushButton_mdp_oublie;
    QWidget *equibment_2;
    QLabel *label_17;
    QWidget *Vacc_2;
    QLabel *label_18;
    QWidget *RendezVous_2;
    QLabel *label_19;
    QWidget *user_2;
    QLabel *label_20;
    QWidget *statlabo_2;
    QLabel *label_21;
    QWidget *chatbotlabo_2;
    QLabel *label_23;
    QWidget *journallabo_2;
    QLabel *label_24;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(1303, 859);
        stackedWidget_2 = new QStackedWidget(Login);
        stackedWidget_2->setObjectName("stackedWidget_2");
        stackedWidget_2->setGeometry(QRect(-30, 20, 1311, 801));
        stackedWidget_2->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 251, 255);\n"
""));
        medecin_2 = new QWidget();
        medecin_2->setObjectName("medecin_2");
        label_13 = new QLabel(medecin_2);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(560, 80, 171, 61));
        label_13->setStyleSheet(QString::fromUtf8("color : black;"));
        stackedWidget_2->addWidget(medecin_2);
        Patient_2 = new QWidget();
        Patient_2->setObjectName("Patient_2");
        Patient_2->setStyleSheet(QString::fromUtf8("color : black;"));
        label_14 = new QLabel(Patient_2);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(410, 60, 171, 61));
        stackedWidget_2->addWidget(Patient_2);
        Labo_2 = new QWidget();
        Labo_2->setObjectName("Labo_2");
        Labo_2->setStyleSheet(QString::fromUtf8("color : black;"));
        lineEdit_login = new QLineEdit(Labo_2);
        lineEdit_login->setObjectName("lineEdit_login");
        lineEdit_login->setGeometry(QRect(630, 200, 291, 51));
        lineEdit_login->setStyleSheet(QString::fromUtf8("border: 2px solid #2a2a2a ; /* Blue border */\n"
"        border-radius: 6px;\n"
"        padding: 5px 8px;\n"
"         color: #2a2a2a;\n"
"    padding: 10px;\n"
"    margin: 6px;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"        selection-background-color: #cce5ff; /* Light blue selection */\n"
"\n"
""));
        lineEdit_password = new QLineEdit(Labo_2);
        lineEdit_password->setObjectName("lineEdit_password");
        lineEdit_password->setGeometry(QRect(630, 310, 291, 51));
        lineEdit_password->setStyleSheet(QString::fromUtf8("border: 2px solid #2a2a2a ; /* Blue border */\n"
"        border-radius: 6px;\n"
"        padding: 5px 8px;\n"
"         color: #2a2a2a;\n"
"    padding: 10px;\n"
"    margin: 6px;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"        selection-background-color: #cce5ff; /* Light blue selection */\n"
"\n"
""));
        lineEdit_password->setEchoMode(QLineEdit::EchoMode::Password);
        pushButton_login = new QPushButton(Labo_2);
        pushButton_login->setObjectName("pushButton_login");
        pushButton_login->setGeometry(QRect(720, 420, 241, 51));
        pushButton_login->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(173, 216, 230);\n"
"    color: #ffffff;\n"
"    border: 2px solid rgb(173, 216, 230);\n"
"    padding: 10px;\n"
"    margin: 6px;\n"
"    border-radius: 12px;\n"
"    font-size: 15px;\n"
"    font-weight: bold;\n"
"    transition: all 0.3s ease-in-out;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #606060;\n"
"    border-color: #777777;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #787878;\n"
"    border-color: #909090;\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: #353535;\n"
"    color: #ffffff;\n"
"    border-color: #444444;\n"
"}\n"
""));
        label = new QLabel(Labo_2);
        label->setObjectName("label");
        label->setGeometry(QRect(510, 220, 63, 20));
        label->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"        font-weight: bold;\n"
"        color: #333; /* Dark gray text */\n"
"        background: transparent;"));
        label_2 = new QLabel(Labo_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(510, 330, 111, 20));
        label_2->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"        font-weight: bold;\n"
"        color: #333; /* Dark gray text */\n"
"        background: transparent;"));
        widget_4 = new QWidget(Labo_2);
        widget_4->setObjectName("widget_4");
        widget_4->setGeometry(QRect(210, 0, 1121, 71));
        widget_4->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: #2a2a2a;\n"
"    border-right: 2px solid #3a3a3a;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #3a3a3a;\n"
"    color: #ffffff;\n"
"    border: none;\n"
"    padding: 10px;\n"
"    margin: 5px;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #4a4a4a;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #666666;\n"
"}\n"
"\n"
"QListWidget {\n"
"    background-color: #2a2a2a;\n"
"    color: #ffffff;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QListWidget::item {\n"
"    padding: 8px;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QListWidget::item:selected {\n"
"    background-color: #4a4a4a;\n"
"}\n"
"\n"
"QScrollBar:vertical {\n"
"    border: none;\n"
"    background: #2a2a2a;\n"
"    width: 8px;\n"
"    margin: 0px 0px 0px 0px;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: #555555;\n"
"    border-radius: 10px;\n"
"}\n"
""
                        "\n"
"QScrollBar::handle:vertical:hover {\n"
"    background: #777777;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {\n"
"    border: none;\n"
"    background: none;\n"
"}\n"
""));
        btnuser = new QPushButton(widget_4);
        btnuser->setObjectName("btnuser");
        btnuser->setGeometry(QRect(950, 0, 151, 61));
        btnuser->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2a2a2a;\n"
"    color: #ffffff;\n"
"    border: 2px solid #2a2a2a;\n"
"    padding: 10px;\n"
"    margin: 6px;\n"
"    border-radius: 12px;\n"
"    font-size: 15px;\n"
"    font-weight: bold;\n"
"    transition: all 0.3s ease-in-out;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #606060;\n"
"    border-color: #777777;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #787878;\n"
"    border-color: #909090;\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: #353535;\n"
"    color: #ffffff;\n"
"    border-color: #444444;\n"
"}\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/icons/microscope_4131002.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnuser->setIcon(icon);
        btnuser->setCheckable(true);
        btnuser->setAutoExclusive(true);
        widget_2 = new QWidget(Labo_2);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(40, 0, 191, 781));
        widget_2->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: #2a2a2a;\n"
"    border-right: 2px solid #2a2a2a;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #3a3a3a;\n"
"    color: #ffffff;\n"
"    border: none;\n"
"    padding: 10px;\n"
"    margin: 5px;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #4a4a4a;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #666666;\n"
"}\n"
"\n"
"QListWidget {\n"
"    background-color: #2a2a2a;\n"
"    color: #ffffff;\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QListWidget::item {\n"
"    padding: 8px;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QListWidget::item:selected {\n"
"    background-color: #4a4a4a;\n"
"}\n"
"\n"
"QScrollBar:vertical {\n"
"    border: none;\n"
"    background: #2a2a2a;\n"
"    width: 8px;\n"
"    margin: 0px 0px 0px 0px;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: #555555;\n"
"    border-radius: 10px;\n"
"}\n"
"\n"
"QScrollBar::handle:ver"
                        "tical:hover {\n"
"    background: #777777;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {\n"
"    border: none;\n"
"    background: none;\n"
"}\n"
""));
        pushButton_14 = new QPushButton(widget_2);
        pushButton_14->setObjectName("pushButton_14");
        pushButton_14->setGeometry(QRect(30, 740, 101, 41));
        pushButton_14->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2a2a2a;\n"
"    color: #ffffff;\n"
"    border: 2px solid #2a2a2a;\n"
"    padding: 10px;\n"
"    margin: 6px;\n"
"    border-radius: 12px;\n"
"    font-size: 15px;\n"
"    font-weight: bold;\n"
"    text-transform: uppercase;\n"
"    transition: all 0.3s ease-in-out;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #606060;\n"
"    border-color: #777777;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #787878;\n"
"    border-color: #909090;\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: #353535;\n"
"    color: #ffffff;\n"
"    border-color: #444444;\n"
"}\n"
""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/prefix1/icons/close_4942745.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_14->setIcon(icon1);
        pushButton_14->setCheckable(true);
        pushButton_14->setAutoExclusive(true);
        label_4 = new QLabel(widget_2);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 0, 81, 71));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/icons/chahed_bhima-removebg-preview.png")));
        label_4->setScaledContents(true);
        label_9 = new QLabel(widget_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(80, 20, 111, 41));
        label_9->setPixmap(QPixmap(QString::fromUtf8(":/icons/44298757-c475-4d62-8415-e4d92b1b761b-removebg-preview.png")));
        label_9->setScaledContents(true);
        pushButton_mdp_oublie = new QPushButton(Labo_2);
        pushButton_mdp_oublie->setObjectName("pushButton_mdp_oublie");
        pushButton_mdp_oublie->setGeometry(QRect(720, 480, 241, 51));
        pushButton_mdp_oublie->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgb(173, 216, 230);\n"
"    color: #ffffff;\n"
"    border: 2px solid rgb(173, 216, 230);\n"
"    padding: 10px;\n"
"    margin: 6px;\n"
"    border-radius: 12px;\n"
"    font-size: 15px;\n"
"    font-weight: bold;\n"
"    transition: all 0.3s ease-in-out;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #606060;\n"
"    border-color: #777777;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #787878;\n"
"    border-color: #909090;\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: #353535;\n"
"    color: #ffffff;\n"
"    border-color: #444444;\n"
"}\n"
""));
        stackedWidget_2->addWidget(Labo_2);
        equibment_2 = new QWidget();
        equibment_2->setObjectName("equibment_2");
        label_17 = new QLabel(equibment_2);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(440, 50, 171, 61));
        label_17->setStyleSheet(QString::fromUtf8("color : black;"));
        stackedWidget_2->addWidget(equibment_2);
        Vacc_2 = new QWidget();
        Vacc_2->setObjectName("Vacc_2");
        label_18 = new QLabel(Vacc_2);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(430, 70, 171, 61));
        label_18->setStyleSheet(QString::fromUtf8("color : black;"));
        stackedWidget_2->addWidget(Vacc_2);
        RendezVous_2 = new QWidget();
        RendezVous_2->setObjectName("RendezVous_2");
        label_19 = new QLabel(RendezVous_2);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(410, 60, 171, 61));
        label_19->setStyleSheet(QString::fromUtf8("color : black;"));
        stackedWidget_2->addWidget(RendezVous_2);
        user_2 = new QWidget();
        user_2->setObjectName("user_2");
        label_20 = new QLabel(user_2);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(750, 170, 171, 61));
        label_20->setStyleSheet(QString::fromUtf8("color : black;"));
        stackedWidget_2->addWidget(user_2);
        statlabo_2 = new QWidget();
        statlabo_2->setObjectName("statlabo_2");
        label_21 = new QLabel(statlabo_2);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(0, 0, 461, 71));
        label_21->setStyleSheet(QString::fromUtf8(" color: rgb(220, 78, 78);\n"
"    padding: 10px;\n"
"    margin: 6px;\n"
"    font-size: 30px;\n"
"    font-weight: bold;\n"
"background-color: rgb(234, 251, 255); \n"
"\n"
""));
        stackedWidget_2->addWidget(statlabo_2);
        chatbotlabo_2 = new QWidget();
        chatbotlabo_2->setObjectName("chatbotlabo_2");
        label_23 = new QLabel(chatbotlabo_2);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(0, 0, 461, 71));
        label_23->setStyleSheet(QString::fromUtf8(" color: rgb(220, 78, 78);\n"
"    padding: 10px;\n"
"    margin: 6px;\n"
"    font-size: 30px;\n"
"    font-weight: bold;\n"
"background-color: rgb(234, 251, 255); \n"
"\n"
""));
        stackedWidget_2->addWidget(chatbotlabo_2);
        journallabo_2 = new QWidget();
        journallabo_2->setObjectName("journallabo_2");
        label_24 = new QLabel(journallabo_2);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(0, 0, 461, 71));
        label_24->setStyleSheet(QString::fromUtf8(" color: rgb(220, 78, 78);\n"
"    padding: 10px;\n"
"    margin: 6px;\n"
"    font-size: 30px;\n"
"    font-weight: bold;\n"
"background-color: rgb(234, 251, 255); \n"
"\n"
""));
        stackedWidget_2->addWidget(journallabo_2);

        retranslateUi(Login);

        stackedWidget_2->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Connexion", nullptr));
        label_13->setText(QCoreApplication::translate("Login", "medecin", nullptr));
        label_14->setText(QCoreApplication::translate("Login", "patient", nullptr));
        pushButton_login->setText(QCoreApplication::translate("Login", "Valider", nullptr));
        label->setText(QCoreApplication::translate("Login", "ID:", nullptr));
        label_2->setText(QCoreApplication::translate("Login", "Mot de passe:", nullptr));
        btnuser->setText(QCoreApplication::translate("Login", "\360\237\221\250\360\237\217\273\342\200\215\360\237\222\273   Utilisateur", nullptr));
        pushButton_14->setText(QString());
        label_4->setText(QString());
        label_9->setText(QString());
        pushButton_mdp_oublie->setText(QCoreApplication::translate("Login", "Mdp oubli\303\251", nullptr));
        label_17->setText(QCoreApplication::translate("Login", "equibment", nullptr));
        label_18->setText(QCoreApplication::translate("Login", "VACCINS", nullptr));
        label_19->setText(QCoreApplication::translate("Login", "rendez vous", nullptr));
        label_20->setText(QCoreApplication::translate("Login", "user", nullptr));
        label_21->setText(QCoreApplication::translate("Login", "Statistique :    (laboratoire)", nullptr));
        label_23->setText(QCoreApplication::translate("Login", "Chatbot :    (laboratoire)", nullptr));
        label_24->setText(QCoreApplication::translate("Login", "Journal :    (laboratoire)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
