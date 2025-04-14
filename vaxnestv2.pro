QT       += core gui network
QT +=sql
QT += widgets charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    connection.cpp \
    mainwindow.cpp \
    patient.cpp \
    mailing/emailaddress.cpp \
    mailing/mimebase64encoder.cpp \
    mailing/mimebytearrayattachment.cpp \
    mailing/mimecontentformatter.cpp \
    mailing/mimehtml.cpp \
    mailing/mimemessage.cpp \
    mailing/mimepart.cpp \
    mailing/mimeqpformatter.cpp \
    mailing/quotedprintable.cpp \
    mailing/smtpclient.cpp \
    mailing/mimeattachment.cpp \
    mailing/mimebase64formatter.cpp \
    mailing/mimecontentencoder.cpp \
    mailing/mimefile.cpp \
    mailing/mimeinlinefile.cpp \
    mailing/mimemultipart.cpp \
    mailing/mimeqpencoder.cpp \
    mailing/mimetext.cpp \
    qrcode/qrcodegen.cpp

HEADERS += \
    connection.h \
    mainwindow.h \
    patient.h \
    mailing/emailaddress.h \
    mailing/mimebase64encoder.h \
    mailing/mimebytearrayattachment.h \
    mailing/mimecontentformatter.h \
    mailing/mimehtml.h \
    mailing/mimemessage.h \
    mailing/mimepart.h \
    mailing/mimeqpformatter.h \
    mailing/quotedprintable.h \
    mailing/smtpclient.h \
    mailing/mimeattachment.h \
    mailing/mimebase64formatter.h \
    mailing/mimecontentencoder.h \
    mailing/mimefile.h \
    mailing/mimeinlinefile.h \
    mailing/mimemultipart.h \
    mailing/mimeqpencoder.h \
    mailing/mimetext.h \
    mailing/smtpmime_global.h



FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc


INCLUDEPATH += $$PWD/qrcode

