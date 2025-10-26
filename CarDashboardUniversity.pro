QT += core gui svg qml quick quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fuelmeter.cpp \
    geardisplay.cpp \
    infodisplay.cpp \
    main.cpp \
    cardashboard.cpp \
    navdisplay.cpp \
    speedometer.cpp

HEADERS += \
    cardashboard.h \
    fuelmeter.h \
    geardisplay.h \
    infodisplay.h \
    navdisplay.h \
    speedometer.h

FORMS += \
    cardashboard.ui

RESOURCES += \
    resources.qrc

TRANSLATIONS += \
    CarDashboardUniversity_en_GB.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
