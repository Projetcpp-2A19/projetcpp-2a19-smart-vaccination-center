/****************************************************************************
** Meta object code from reading C++ file 'smtpclient.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mailing/smtpclient.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'smtpclient.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSSmtpClientENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSSmtpClientENDCLASS = QtMocHelpers::stringData(
    "SmtpClient",
    "error",
    "",
    "SmtpClient::SmtpError",
    "e",
    "stateChanged",
    "SmtpClient::ClientState",
    "s",
    "connected",
    "readyConnected",
    "authenticated",
    "mailSent",
    "mailReset",
    "disconnected",
    "socketStateChanged",
    "QAbstractSocket::SocketState",
    "state",
    "socketError",
    "QAbstractSocket::SocketError",
    "socketReadyRead",
    "socketEncrypted",
    "AuthMethod",
    "AuthPlain",
    "AuthLogin",
    "SmtpError",
    "ConnectionTimeoutError",
    "ResponseTimeoutError",
    "AuthenticationError",
    "MailSendingError",
    "ServerError",
    "ClientError",
    "SocketError",
    "ConnectionType",
    "TcpConnection",
    "SslConnection",
    "TlsConnection",
    "ClientState",
    "UnconnectedState",
    "ConnectingState",
    "ConnectedState",
    "ReadyState",
    "AuthenticatingState",
    "MailSendingState",
    "DisconnectingState",
    "ResetState",
    "_EHLO_State",
    "_TLS_State",
    "_READY_Connected",
    "_READY_Authenticated",
    "_READY_MailSent",
    "_READY_Encrypted",
    "_QUITTING_State",
    "_TLS_0_STARTTLS",
    "_TLS_1_ENCRYPT",
    "_TLS_2_EHLO",
    "_AUTH_PLAIN_0",
    "_AUTH_LOGIN_0",
    "_AUTH_LOGIN_1_USER",
    "_AUTH_LOGIN_2_PASS",
    "_MAIL_0_FROM",
    "_MAIL_1_RCPT_INIT",
    "_MAIL_2_RCPT",
    "_MAIL_3_DATA",
    "_MAIL_4_SEND_DATA"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSSmtpClientENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       4,  106, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   86,    2, 0x06,    5 /* Public */,
       5,    1,   89,    2, 0x06,    7 /* Public */,
       8,    0,   92,    2, 0x06,    9 /* Public */,
       9,    0,   93,    2, 0x06,   10 /* Public */,
      10,    0,   94,    2, 0x06,   11 /* Public */,
      11,    0,   95,    2, 0x06,   12 /* Public */,
      12,    0,   96,    2, 0x06,   13 /* Public */,
      13,    0,   97,    2, 0x06,   14 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      14,    1,   98,    2, 0x09,   15 /* Protected */,
      17,    1,  101,    2, 0x09,   17 /* Protected */,
      19,    0,  104,    2, 0x09,   19 /* Protected */,
      20,    0,  105,    2, 0x09,   20 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 18,    1,
    QMetaType::Void,
    QMetaType::Void,

 // enums: name, alias, flags, count, data
      21,   21, 0x0,    2,  126,
      24,   24, 0x0,    7,  130,
      32,   32, 0x0,    3,  144,
      36,   36, 0x0,   27,  150,

 // enum data: key, value
      22, uint(SmtpClient::AuthPlain),
      23, uint(SmtpClient::AuthLogin),
      25, uint(SmtpClient::ConnectionTimeoutError),
      26, uint(SmtpClient::ResponseTimeoutError),
      27, uint(SmtpClient::AuthenticationError),
      28, uint(SmtpClient::MailSendingError),
      29, uint(SmtpClient::ServerError),
      30, uint(SmtpClient::ClientError),
      31, uint(SmtpClient::SocketError),
      33, uint(SmtpClient::TcpConnection),
      34, uint(SmtpClient::SslConnection),
      35, uint(SmtpClient::TlsConnection),
      37, uint(SmtpClient::UnconnectedState),
      38, uint(SmtpClient::ConnectingState),
      39, uint(SmtpClient::ConnectedState),
      40, uint(SmtpClient::ReadyState),
      41, uint(SmtpClient::AuthenticatingState),
      42, uint(SmtpClient::MailSendingState),
      43, uint(SmtpClient::DisconnectingState),
      44, uint(SmtpClient::ResetState),
      45, uint(SmtpClient::_EHLO_State),
      46, uint(SmtpClient::_TLS_State),
      47, uint(SmtpClient::_READY_Connected),
      48, uint(SmtpClient::_READY_Authenticated),
      49, uint(SmtpClient::_READY_MailSent),
      50, uint(SmtpClient::_READY_Encrypted),
      51, uint(SmtpClient::_QUITTING_State),
      52, uint(SmtpClient::_TLS_0_STARTTLS),
      53, uint(SmtpClient::_TLS_1_ENCRYPT),
      54, uint(SmtpClient::_TLS_2_EHLO),
      55, uint(SmtpClient::_AUTH_PLAIN_0),
      56, uint(SmtpClient::_AUTH_LOGIN_0),
      57, uint(SmtpClient::_AUTH_LOGIN_1_USER),
      58, uint(SmtpClient::_AUTH_LOGIN_2_PASS),
      59, uint(SmtpClient::_MAIL_0_FROM),
      60, uint(SmtpClient::_MAIL_1_RCPT_INIT),
      61, uint(SmtpClient::_MAIL_2_RCPT),
      62, uint(SmtpClient::_MAIL_3_DATA),
      63, uint(SmtpClient::_MAIL_4_SEND_DATA),

       0        // eod
};

Q_CONSTINIT const QMetaObject SmtpClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSSmtpClientENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSSmtpClientENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSSmtpClientENDCLASS_t,
        // enum 'AuthMethod'
        QtPrivate::TypeAndForceComplete<SmtpClient::AuthMethod, std::true_type>,
        // enum 'SmtpError'
        QtPrivate::TypeAndForceComplete<SmtpClient::SmtpError, std::true_type>,
        // enum 'ConnectionType'
        QtPrivate::TypeAndForceComplete<SmtpClient::ConnectionType, std::true_type>,
        // enum 'ClientState'
        QtPrivate::TypeAndForceComplete<SmtpClient::ClientState, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SmtpClient, std::true_type>,
        // method 'error'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<SmtpClient::SmtpError, std::false_type>,
        // method 'stateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<SmtpClient::ClientState, std::false_type>,
        // method 'connected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'readyConnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'authenticated'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'mailSent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'mailReset'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'socketStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketState, std::false_type>,
        // method 'socketError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>,
        // method 'socketReadyRead'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'socketEncrypted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void SmtpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SmtpClient *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< std::add_pointer_t<SmtpClient::SmtpError>>(_a[1]))); break;
        case 1: _t->stateChanged((*reinterpret_cast< std::add_pointer_t<SmtpClient::ClientState>>(_a[1]))); break;
        case 2: _t->connected(); break;
        case 3: _t->readyConnected(); break;
        case 4: _t->authenticated(); break;
        case 5: _t->mailSent(); break;
        case 6: _t->mailReset(); break;
        case 7: _t->disconnected(); break;
        case 8: _t->socketStateChanged((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketState>>(_a[1]))); break;
        case 9: _t->socketError((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        case 10: _t->socketReadyRead(); break;
        case 11: _t->socketEncrypted(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketState >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SmtpClient::*)(SmtpClient::SmtpError );
            if (_t _q_method = &SmtpClient::error; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SmtpClient::*)(SmtpClient::ClientState );
            if (_t _q_method = &SmtpClient::stateChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SmtpClient::*)();
            if (_t _q_method = &SmtpClient::connected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SmtpClient::*)();
            if (_t _q_method = &SmtpClient::readyConnected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SmtpClient::*)();
            if (_t _q_method = &SmtpClient::authenticated; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SmtpClient::*)();
            if (_t _q_method = &SmtpClient::mailSent; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SmtpClient::*)();
            if (_t _q_method = &SmtpClient::mailReset; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SmtpClient::*)();
            if (_t _q_method = &SmtpClient::disconnected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject *SmtpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SmtpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSSmtpClientENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SmtpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void SmtpClient::error(SmtpClient::SmtpError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SmtpClient::stateChanged(SmtpClient::ClientState _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SmtpClient::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SmtpClient::readyConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SmtpClient::authenticated()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void SmtpClient::mailSent()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void SmtpClient::mailReset()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void SmtpClient::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
