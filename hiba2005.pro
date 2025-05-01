QT       += core gui network charts serialport printsupport
QT += charts

QT += location positioning location positioning quickwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += src

SOURCES += \
    Login.cpp \
    MarkerModel.cpp \
    Medecin.cpp \
    MotDePasseOublie.cpp \
    arduino.cpp \
    connection.cpp \
    lab.cpp \
    main.cpp \
    mainwindow.cpp \
    Vaccin.cpp \
    rendezvous.cpp \
    sms1.cpp \
    src/emailaddress.cpp \
    src/mimeattachment.cpp \
    src/mimebase64encoder.cpp \
    src/mimebase64formatter.cpp \
    src/mimebytearrayattachment.cpp \
    src/mimecontentencoder.cpp \
    src/mimecontentformatter.cpp \
    src/mimefile.cpp \
    src/mimehtml.cpp \
    src/mimeinlinefile.cpp \
    src/mimemessage.cpp \
    src/mimemultipart.cpp \
    src/mimepart.cpp \
    src/mimeqpencoder.cpp \
    src/mimeqpformatter.cpp \
    src/mimetext.cpp \
    src/quotedprintable.cpp \
    src/sms.cpp \
    src/smtpclient.cpp

HEADERS += \
    Login.h \
    MarkerModel.h \
    Medecin.h \
    MotDePasseOublie.h \
    arduino.h \
    connection.h \
    lab.h \
    mainwindow.h \
    Vaccin.h \
    rendezvous.h \
    sms1.h \
    src/emailaddress.h \
    src/mimeattachment.h \
    src/mimebase64encoder.h \
    src/mimebase64formatter.h \
    src/mimebytearrayattachment.h \
    src/mimecontentencoder.h \
    src/mimecontentformatter.h \
    src/mimefile.h \
    src/mimehtml.h \
    src/mimeinlinefile.h \
    src/mimemessage.h \
    src/mimemultipart.h \
    src/mimepart.h \
    src/mimeqpencoder.h \
    src/mimeqpformatter.h \
    src/mimetext.h \
    src/quotedprintable.h \
    src/sms.h \
    src/smtpclient.h \
    src/smtpmime_global.h

FORMS += \
    Login.ui \
    MotDePasseOublie.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QT+=sql

RESOURCES += \
    resources.qrc

DISTFILES += \
    map.qml
