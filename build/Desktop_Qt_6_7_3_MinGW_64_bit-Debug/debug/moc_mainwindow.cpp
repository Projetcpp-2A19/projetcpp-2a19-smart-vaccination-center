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
    "on_comboBox_currentIndexChanged",
    "index",
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
    "on_btnrendezv2_clicked",
    "on_btnrendezv3_clicked",
    "on_btnequiprmrnt_clicked",
    "on_btnequiprmrnt2_clicked",
    "on_btnequiprmrnt3_clicked",
    "on_btnuser_clicked",
    "on_btnSupprimer_clicked",
    "on_btnModifier_clicked",
    "on_btnConfirmerModifier_clicked",
    "verifierRendezVousDepuisLabel",
    "on_pushButton_115_clicked",
    "onGeoCodeReply",
    "QNetworkReply*",
    "reply",
    "updateTableView",
    "showStatistiques",
    "analyserCommande",
    "updateTableViewchat",
    "QSqlQueryModel*",
    "model",
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
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,  206,    2, 0x06,    1 /* Public */,
       5,    2,  211,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,  216,    2, 0x08,    7 /* Private */,
       8,    0,  219,    2, 0x08,    9 /* Private */,
       9,    0,  220,    2, 0x08,   10 /* Private */,
      10,    0,  221,    2, 0x08,   11 /* Private */,
      11,    0,  222,    2, 0x08,   12 /* Private */,
      12,    0,  223,    2, 0x08,   13 /* Private */,
      13,    0,  224,    2, 0x08,   14 /* Private */,
      14,    0,  225,    2, 0x08,   15 /* Private */,
      15,    0,  226,    2, 0x08,   16 /* Private */,
      16,    0,  227,    2, 0x08,   17 /* Private */,
      17,    0,  228,    2, 0x08,   18 /* Private */,
      18,    0,  229,    2, 0x08,   19 /* Private */,
      19,    0,  230,    2, 0x08,   20 /* Private */,
      20,    0,  231,    2, 0x08,   21 /* Private */,
      21,    0,  232,    2, 0x08,   22 /* Private */,
      22,    0,  233,    2, 0x08,   23 /* Private */,
      23,    0,  234,    2, 0x08,   24 /* Private */,
      24,    0,  235,    2, 0x08,   25 /* Private */,
      25,    0,  236,    2, 0x08,   26 /* Private */,
      26,    0,  237,    2, 0x08,   27 /* Private */,
      27,    0,  238,    2, 0x08,   28 /* Private */,
      28,    0,  239,    2, 0x08,   29 /* Private */,
      29,    0,  240,    2, 0x08,   30 /* Private */,
      30,    1,  241,    2, 0x08,   31 /* Private */,
      33,    0,  244,    2, 0x08,   33 /* Private */,
      34,    0,  245,    2, 0x08,   34 /* Private */,
      35,    0,  246,    2, 0x08,   35 /* Private */,
      36,    1,  247,    2, 0x08,   36 /* Private */,
      36,    0,  250,    2, 0x08,   38 /* Private */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
      39,    1,  251,    2, 0x02,   39 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    3,    4,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
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
    QMetaType::Void, 0x80000000 | 31,   32,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 37,   38,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,   40,

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
        // method 'on_comboBox_currentIndexChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
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
        // method 'on_btnrendezv2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnrendezv3_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnequiprmrnt_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnequiprmrnt2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnequiprmrnt3_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnuser_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnSupprimer_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnModifier_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnConfirmerModifier_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'verifierRendezVousDepuisLabel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_115_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onGeoCodeReply'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QNetworkReply *, std::false_type>,
        // method 'updateTableView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showStatistiques'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'analyserCommande'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateTableViewchat'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QSqlQueryModel *, std::false_type>,
        // method 'updateTableViewchat'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
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
        case 2: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->on_btnmedecin_clicked(); break;
        case 4: _t->on_btnmedecin2_clicked(); break;
        case 5: _t->on_btnpatient_clicked(); break;
        case 6: _t->on_btnpatient2_clicked(); break;
        case 7: _t->on_btnvaccins_clicked(); break;
        case 8: _t->on_btnvaccins2_clicked(); break;
        case 9: _t->on_btnlabo_clicked(); break;
        case 10: _t->on_btnlabo2_clicked(); break;
        case 11: _t->on_btnlabo3_clicked(); break;
        case 12: _t->on_btnlabo4_clicked(); break;
        case 13: _t->on_btnrendezv_clicked(); break;
        case 14: _t->on_btnrendezv2_clicked(); break;
        case 15: _t->on_btnrendezv3_clicked(); break;
        case 16: _t->on_btnequiprmrnt_clicked(); break;
        case 17: _t->on_btnequiprmrnt2_clicked(); break;
        case 18: _t->on_btnequiprmrnt3_clicked(); break;
        case 19: _t->on_btnuser_clicked(); break;
        case 20: _t->on_btnSupprimer_clicked(); break;
        case 21: _t->on_btnModifier_clicked(); break;
        case 22: _t->on_btnConfirmerModifier_clicked(); break;
        case 23: _t->verifierRendezVousDepuisLabel(); break;
        case 24: _t->on_pushButton_115_clicked(); break;
        case 25: _t->onGeoCodeReply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 26: _t->updateTableView(); break;
        case 27: _t->showStatistiques(); break;
        case 28: _t->analyserCommande(); break;
        case 29: _t->updateTableViewchat((*reinterpret_cast< std::add_pointer_t<QSqlQueryModel*>>(_a[1]))); break;
        case 30: _t->updateTableViewchat(); break;
        case 31: _t->searchLocation((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 25:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply* >(); break;
            }
            break;
        case 29:
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
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
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
