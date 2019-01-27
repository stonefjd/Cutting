#-------------------------------------------------
#
# Project created by QtCreator 2018-12-15T11:55:35
#
#-------------------------------------------------

QT       += core gui\
            xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 09_PGM_Cutting_V1_0_0
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
TRANSLATIONS += trans.ts
SOURCES += \
    main.cpp \
    statemachine.cpp \
    windowcutting.cpp \
    PhysicalLayer/hardwareadaptor.cpp \
    Machine/machine.cpp \
    Machine/Fan/fan.cpp \
    Machine/KnifeTool/knifetool.cpp \
    Machine/Desktop/desktop.cpp \
    File/Settings/settings.cpp \
    File/Route/route.cpp

HEADERS += \
    statemachine.h \
    windowcutting.h \
    PhysicalLayer/hardwareadaptor.h \
    PhysicalLayer/gts.h \
    Machine/machine.h \
    Machine/Fan/fan.h \
    Machine/KnifeTool/knifetool.h \
    Machine/Desktop/desktop.h \
    File/Settings/settings.h \
    File/Route/route.h

FORMS += \
        windowcutting.ui \
    File/Settings/settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/PhysicalLayer/ -lgts
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/PhysicalLayer/ -lgtsd
else:unix: LIBS += -L$$PWD/PhysicalLayer/ -lgts

INCLUDEPATH += $$PWD/PhysicalLayer
DEPENDPATH += $$PWD/PhysicalLayer
