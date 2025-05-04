/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qabstractbarseries.h>
#include <QtCharts/qvbarmodelmapper.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCharts/qcandlestickseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qxyseries.h>
#include <QtCharts/qxyseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qxyseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtNetwork/QSslError>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "ajouterLaboratoireEPINGLE",
    "",
    "latitude",
    "longitude",
    "positionTrouvee",
    "on_btnmedecin_clicked",
    "on_btnmedecin2_clicked",
    "on_btnpatient_clicked",
    "on_btnpatient2_clicked",
    "on_btnvaccins_clicked",
    "on_btnvaccins2_clicked",
    "on_btnlabo_clicked",
    "on_btnlabo2_clicked",
    "on_btnlabo3_clicked",
    "on_btnlabo4_clicked",
    "on_btnrendezv_clicked",
    "on_btnrendezv2_2_clicked",
    "on_btnrendezv3_2_clicked",
    "on_btnequiprmrnt_clicked",
    "on_btnequiprmrnt2_clicked",
    "on_btnequiprmrnt3_clicked",
    "updateTableView",
    "updateTableViewRV",
    "on_btnuser_clicked",
    "ajouterMedecin",
    "afficherMedecins",
    "on_pushButton_mod_clicked",
    "on_b_supp_clicked",
    "on_comboBoxtri_currentIndexChanged",
    "on_b_chercher_clicked",
    "afficherStat",
    "exporterPDF",
    "on_submit_clicked",
    "on_del_clicked",
    "on_pushButton_159_clicked",
    "applyFilter",
    "text",
    "onSortChanged",
    "index",
    "on_pdfButton_clicked",
    "on_emailButton_clicked",
    "on_sms_clicked",
    "checkLowStockAndNotify",
    "sendStockAlertEmail",
    "nom",
    "type",
    "pays",
    "stock",
    "showStockPieChart",
    "mousePressEvent",
    "QMouseEvent*",
    "event",
    "on_pushButton_193_clicked",
    "on_btnsupp_2_clicked",
    "on_btnmodif_2_clicked",
    "on_btncmodif_2_clicked",
    "on_btnrendezv4_2_clicked",
    "on_comboBox_46_currentIndexChanged",
    "on_lineEdit_134_textChanged",
    "searchTerm",
    "showStatistiques_rdv",
    "chargerRendezVousDansCalendrier",
    "on_calendarWidget_clicked",
    "date",
    "on_pushButton_194_clicked",
    "on_btnSupprimer_labo_clicked",
    "on_btnModifier_labo_clicked",
    "on_btnConfirmerModifier_labo8_clicked",
    "on_btnequipementAjouter_4_clicked",
    "afficherEquipements",
    "on_btnSupprimer_clicked",
    "on_btnModifier_clicked",
    "on_btnConfirmerModifier_4_clicked",
    "on_lineEdit_54_textChanged",
    "on_btnequiprmrnt4_clicked",
    "showStatistiques",
    "on_panneButton_clicked",
    "showPanneNotification",
    "equipementNom",
    "on_btnvoice_4_clicked",
    "update_fridge_status",
    "on_btnajouterpatient_2_clicked",
    "on_recherche_clicked",
    "on_tri_clicked",
    "genererRapportPDF",
    "on_btnpatient3_3_clicked",
    "afficherStatistiques",
    "on_btnpatient2_3_clicked",
    "on_listpatient_clicked",
    "recupererVaccinsPatient",
    "patientID",
    "ajouterCertificatImageDansBDD",
    "genererCertificatImage",
    "Patient",
    "patient",
    "getPatientById",
    "id",
    "afficherCertificatDepuisBDD",
    "on_pushButton_labo7_clicked",
    "onGeoCodeReply",
    "QNetworkReply*",
    "reply",
    "updateTableView_labo",
    "showStatistiques_labo",
    "analyserCommande",
    "updateTableViewchat",
    "QSqlQueryModel*",
    "model",
    "on_comboBox_labo6_currentIndexChanged",
    "searchLocation",
    "address"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      89,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,  548,    2, 0x06,    1 /* Public */,
       5,    2,  553,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,  558,    2, 0x08,    7 /* Private */,
       7,    0,  559,    2, 0x08,    8 /* Private */,
       8,    0,  560,    2, 0x08,    9 /* Private */,
       9,    0,  561,    2, 0x08,   10 /* Private */,
      10,    0,  562,    2, 0x08,   11 /* Private */,
      11,    0,  563,    2, 0x08,   12 /* Private */,
      12,    0,  564,    2, 0x08,   13 /* Private */,
      13,    0,  565,    2, 0x08,   14 /* Private */,
      14,    0,  566,    2, 0x08,   15 /* Private */,
      15,    0,  567,    2, 0x08,   16 /* Private */,
      16,    0,  568,    2, 0x08,   17 /* Private */,
      17,    0,  569,    2, 0x08,   18 /* Private */,
      18,    0,  570,    2, 0x08,   19 /* Private */,
      19,    0,  571,    2, 0x08,   20 /* Private */,
      20,    0,  572,    2, 0x08,   21 /* Private */,
      21,    0,  573,    2, 0x08,   22 /* Private */,
      22,    0,  574,    2, 0x08,   23 /* Private */,
      23,    0,  575,    2, 0x08,   24 /* Private */,
      24,    0,  576,    2, 0x08,   25 /* Private */,
      25,    0,  577,    2, 0x08,   26 /* Private */,
      26,    0,  578,    2, 0x08,   27 /* Private */,
      27,    0,  579,    2, 0x08,   28 /* Private */,
      28,    0,  580,    2, 0x08,   29 /* Private */,
      29,    1,  581,    2, 0x08,   30 /* Private */,
      30,    0,  584,    2, 0x08,   32 /* Private */,
      31,    0,  585,    2, 0x08,   33 /* Private */,
      32,    0,  586,    2, 0x08,   34 /* Private */,
      33,    0,  587,    2, 0x08,   35 /* Private */,
      34,    0,  588,    2, 0x08,   36 /* Private */,
      35,    0,  589,    2, 0x08,   37 /* Private */,
      36,    1,  590,    2, 0x08,   38 /* Private */,
      38,    1,  593,    2, 0x08,   40 /* Private */,
      40,    0,  596,    2, 0x08,   42 /* Private */,
      41,    0,  597,    2, 0x08,   43 /* Private */,
      42,    0,  598,    2, 0x08,   44 /* Private */,
      43,    0,  599,    2, 0x08,   45 /* Private */,
      44,    4,  600,    2, 0x08,   46 /* Private */,
      49,    0,  609,    2, 0x08,   51 /* Private */,
      50,    1,  610,    2, 0x08,   52 /* Private */,
      53,    0,  613,    2, 0x08,   54 /* Private */,
      54,    0,  614,    2, 0x08,   55 /* Private */,
      55,    0,  615,    2, 0x08,   56 /* Private */,
      56,    0,  616,    2, 0x08,   57 /* Private */,
      57,    0,  617,    2, 0x08,   58 /* Private */,
      58,    1,  618,    2, 0x08,   59 /* Private */,
      59,    1,  621,    2, 0x08,   61 /* Private */,
      61,    0,  624,    2, 0x08,   63 /* Private */,
      62,    0,  625,    2, 0x08,   64 /* Private */,
      63,    1,  626,    2, 0x08,   65 /* Private */,
      65,    0,  629,    2, 0x08,   67 /* Private */,
      66,    0,  630,    2, 0x08,   68 /* Private */,
      67,    0,  631,    2, 0x08,   69 /* Private */,
      68,    0,  632,    2, 0x08,   70 /* Private */,
      69,    0,  633,    2, 0x08,   71 /* Private */,
      70,    0,  634,    2, 0x08,   72 /* Private */,
      71,    0,  635,    2, 0x08,   73 /* Private */,
      72,    0,  636,    2, 0x08,   74 /* Private */,
      73,    0,  637,    2, 0x08,   75 /* Private */,
      74,    1,  638,    2, 0x08,   76 /* Private */,
      75,    0,  641,    2, 0x08,   78 /* Private */,
      76,    0,  642,    2, 0x08,   79 /* Private */,
      77,    0,  643,    2, 0x08,   80 /* Private */,
      78,    1,  644,    2, 0x08,   81 /* Private */,
      80,    0,  647,    2, 0x08,   83 /* Private */,
      81,    0,  648,    2, 0x08,   84 /* Private */,
      82,    0,  649,    2, 0x08,   85 /* Private */,
      83,    0,  650,    2, 0x08,   86 /* Private */,
      84,    0,  651,    2, 0x08,   87 /* Private */,
      85,    0,  652,    2, 0x08,   88 /* Private */,
      86,    0,  653,    2, 0x08,   89 /* Private */,
      87,    0,  654,    2, 0x08,   90 /* Private */,
      88,    0,  655,    2, 0x08,   91 /* Private */,
      89,    0,  656,    2, 0x08,   92 /* Private */,
      90,    1,  657,    2, 0x08,   93 /* Private */,
      92,    1,  660,    2, 0x08,   95 /* Private */,
      93,    1,  663,    2, 0x08,   97 /* Private */,
      96,    1,  666,    2, 0x08,   99 /* Private */,
      98,    1,  669,    2, 0x08,  101 /* Private */,
      99,    0,  672,    2, 0x08,  103 /* Private */,
     100,    1,  673,    2, 0x08,  104 /* Private */,
     103,    0,  676,    2, 0x08,  106 /* Private */,
     104,    0,  677,    2, 0x08,  107 /* Private */,
     105,    0,  678,    2, 0x08,  108 /* Private */,
     106,    1,  679,    2, 0x08,  109 /* Private */,
     106,    0,  682,    2, 0x08,  111 /* Private */,
     109,    1,  683,    2, 0x08,  112 /* Private */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
     110,    1,  686,    2, 0x02,  114 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    3,    4,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   37,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,   45,   46,   47,   48,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 51,   52,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void, QMetaType::QString,   60,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,   64,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   60,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   79,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,   91,
    QMetaType::Bool, QMetaType::Int,   91,
    QMetaType::Void, 0x80000000 | 94,   95,
    0x80000000 | 94, QMetaType::Int,   97,
    QMetaType::Void, QMetaType::Int,   91,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 101,  102,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 107,  108,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   39,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,  111,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'ajouterLaboratoireEPINGLE'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'positionTrouvee'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'on_btnmedecin_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnmedecin2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnpatient_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnpatient2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnvaccins_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnvaccins2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnlabo_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnlabo2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnlabo3_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnlabo4_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnrendezv_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnrendezv2_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnrendezv3_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnequiprmrnt_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnequiprmrnt2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnequiprmrnt3_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateTableView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateTableViewRV'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnuser_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ajouterMedecin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'afficherMedecins'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_mod_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_b_supp_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_comboBoxtri_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_b_chercher_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'afficherStat'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'exporterPDF'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_submit_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_del_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_159_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'applyFilter'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onSortChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_pdfButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_emailButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_sms_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'checkLowStockAndNotify'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendStockAlertEmail'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'showStockPieChart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'mousePressEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'on_pushButton_193_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnsupp_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnmodif_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btncmodif_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnrendezv4_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_comboBox_46_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_lineEdit_134_textChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'showStatistiques_rdv'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'chargerRendezVousDansCalendrier'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_calendarWidget_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QDate &, std::false_type>,
        // method 'on_pushButton_194_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnSupprimer_labo_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnModifier_labo_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnConfirmerModifier_labo8_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnequipementAjouter_4_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'afficherEquipements'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnSupprimer_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnModifier_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnConfirmerModifier_4_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_lineEdit_54_textChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_btnequiprmrnt4_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showStatistiques'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_panneButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showPanneNotification'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_btnvoice_4_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'update_fridge_status'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnajouterpatient_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_recherche_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_tri_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'genererRapportPDF'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnpatient3_3_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'afficherStatistiques'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnpatient2_3_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_listpatient_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'recupererVaccinsPatient'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'ajouterCertificatImageDansBDD'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'genererCertificatImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const Patient &, std::false_type>,
        // method 'getPatientById'
        QtPrivate::TypeAndForceComplete<Patient, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'afficherCertificatDepuisBDD'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_pushButton_labo7_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onGeoCodeReply'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QNetworkReply *, std::false_type>,
        // method 'updateTableView_labo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showStatistiques_labo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'analyserCommande'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateTableViewchat'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QSqlQueryModel *, std::false_type>,
        // method 'updateTableViewchat'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_comboBox_labo6_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'searchLocation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ajouterLaboratoireEPINGLE((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2]))); break;
        case 1: _t->positionTrouvee((*reinterpret_cast< std::add_pointer_t<double>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<double>>(_a[2]))); break;
        case 2: _t->on_btnmedecin_clicked(); break;
        case 3: _t->on_btnmedecin2_clicked(); break;
        case 4: _t->on_btnpatient_clicked(); break;
        case 5: _t->on_btnpatient2_clicked(); break;
        case 6: _t->on_btnvaccins_clicked(); break;
        case 7: _t->on_btnvaccins2_clicked(); break;
        case 8: _t->on_btnlabo_clicked(); break;
        case 9: _t->on_btnlabo2_clicked(); break;
        case 10: _t->on_btnlabo3_clicked(); break;
        case 11: _t->on_btnlabo4_clicked(); break;
        case 12: _t->on_btnrendezv_clicked(); break;
        case 13: _t->on_btnrendezv2_2_clicked(); break;
        case 14: _t->on_btnrendezv3_2_clicked(); break;
        case 15: _t->on_btnequiprmrnt_clicked(); break;
        case 16: _t->on_btnequiprmrnt2_clicked(); break;
        case 17: _t->on_btnequiprmrnt3_clicked(); break;
        case 18: _t->updateTableView(); break;
        case 19: _t->updateTableViewRV(); break;
        case 20: _t->on_btnuser_clicked(); break;
        case 21: _t->ajouterMedecin(); break;
        case 22: _t->afficherMedecins(); break;
        case 23: _t->on_pushButton_mod_clicked(); break;
        case 24: _t->on_b_supp_clicked(); break;
        case 25: _t->on_comboBoxtri_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 26: _t->on_b_chercher_clicked(); break;
        case 27: _t->afficherStat(); break;
        case 28: _t->exporterPDF(); break;
        case 29: _t->on_submit_clicked(); break;
        case 30: _t->on_del_clicked(); break;
        case 31: _t->on_pushButton_159_clicked(); break;
        case 32: _t->applyFilter((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 33: _t->onSortChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 34: _t->on_pdfButton_clicked(); break;
        case 35: _t->on_emailButton_clicked(); break;
        case 36: _t->on_sms_clicked(); break;
        case 37: _t->checkLowStockAndNotify(); break;
        case 38: _t->sendStockAlertEmail((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4]))); break;
        case 39: _t->showStockPieChart(); break;
        case 40: _t->mousePressEvent((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 41: _t->on_pushButton_193_clicked(); break;
        case 42: _t->on_btnsupp_2_clicked(); break;
        case 43: _t->on_btnmodif_2_clicked(); break;
        case 44: _t->on_btncmodif_2_clicked(); break;
        case 45: _t->on_btnrendezv4_2_clicked(); break;
        case 46: _t->on_comboBox_46_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 47: _t->on_lineEdit_134_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 48: _t->showStatistiques_rdv(); break;
        case 49: _t->chargerRendezVousDansCalendrier(); break;
        case 50: _t->on_calendarWidget_clicked((*reinterpret_cast< std::add_pointer_t<QDate>>(_a[1]))); break;
        case 51: _t->on_pushButton_194_clicked(); break;
        case 52: _t->on_btnSupprimer_labo_clicked(); break;
        case 53: _t->on_btnModifier_labo_clicked(); break;
        case 54: _t->on_btnConfirmerModifier_labo8_clicked(); break;
        case 55: _t->on_btnequipementAjouter_4_clicked(); break;
        case 56: _t->afficherEquipements(); break;
        case 57: _t->on_btnSupprimer_clicked(); break;
        case 58: _t->on_btnModifier_clicked(); break;
        case 59: _t->on_btnConfirmerModifier_4_clicked(); break;
        case 60: _t->on_lineEdit_54_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 61: _t->on_btnequiprmrnt4_clicked(); break;
        case 62: _t->showStatistiques(); break;
        case 63: _t->on_panneButton_clicked(); break;
        case 64: _t->showPanneNotification((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 65: _t->on_btnvoice_4_clicked(); break;
        case 66: _t->update_fridge_status(); break;
        case 67: _t->on_btnajouterpatient_2_clicked(); break;
        case 68: _t->on_recherche_clicked(); break;
        case 69: _t->on_tri_clicked(); break;
        case 70: _t->genererRapportPDF(); break;
        case 71: _t->on_btnpatient3_3_clicked(); break;
        case 72: _t->afficherStatistiques(); break;
        case 73: _t->on_btnpatient2_3_clicked(); break;
        case 74: _t->on_listpatient_clicked(); break;
        case 75: { QString _r = _t->recupererVaccinsPatient((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 76: { bool _r = _t->ajouterCertificatImageDansBDD((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 77: _t->genererCertificatImage((*reinterpret_cast< std::add_pointer_t<Patient>>(_a[1]))); break;
        case 78: { Patient _r = _t->getPatientById((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< Patient*>(_a[0]) = std::move(_r); }  break;
        case 79: _t->afficherCertificatDepuisBDD((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 80: _t->on_pushButton_labo7_clicked(); break;
        case 81: _t->onGeoCodeReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 82: _t->updateTableView_labo(); break;
        case 83: _t->showStatistiques_labo(); break;
        case 84: _t->analyserCommande(); break;
        case 85: _t->updateTableViewchat((*reinterpret_cast< std::add_pointer_t<QSqlQueryModel*>>(_a[1]))); break;
        case 86: _t->updateTableViewchat(); break;
        case 87: _t->on_comboBox_labo6_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 88: _t->searchLocation((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 81:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply* >(); break;
            }
            break;
        case 85:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QSqlQueryModel* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(double , double );
            if (_t _q_method = &MainWindow::ajouterLaboratoireEPINGLE; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(double , double );
            if (_t _q_method = &MainWindow::positionTrouvee; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 89)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 89;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 89)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 89;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::ajouterLaboratoireEPINGLE(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::positionTrouvee(double _t1, double _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
