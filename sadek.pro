QT += core gui sql printsupport charts multimedia serialport

QMAKE_POST_LINK += echo Ensure Python is installed and models are downloaded

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Vaccin.cpp \
    arduino.cpp \
    connection.cpp \
    equipements.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    FridgeMonitor.h \
    Vaccin.h \
    arduino.h \
    connection.h \
    equipements.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT+=sql

RESOURCES += \
    resources.qrc
