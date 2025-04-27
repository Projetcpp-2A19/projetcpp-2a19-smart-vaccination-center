#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql network charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
INCLUDEPATH += src


SOURCES += \
    Vaccin.cpp \
    src/emailaddress.cpp \
    main.cpp \
    mainwindow.cpp \
    connection.cpp \
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
    Vaccin.h \
    mainwindow.h \
    connection.h \
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
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QT+= sql

RESOURCES += \
    icons.qrc
