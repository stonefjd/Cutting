#-------------------------------------------------
#
# Project created by QtCreator 2018-12-15T11:55:35
#
#-------------------------------------------------

QT       += core gui xml sql 3dinput

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
    windowcutting.cpp \
    PhysicalLayer/hardwareadaptor.cpp \
    Machine/machine.cpp \
    Machine/Fan/fan.cpp \
    File/CutFileListOp/cutfilelistop.cpp \
    File/IniOp/iniop.cpp \
    User/userlog.cpp \
    Machine/Knife/sdknife.cpp \
    Machine/Knife/sdknifeconfig.cpp \
    Machine/Knife/sdapron.cpp \
    Machine/Knife/sdmachinehead.cpp \
    Machine/Knife/sdmachine.cpp \
    Machine/Knife/sdcuttoollib.cpp \
    Machine/Config/confighead.cpp \
    Machine/Config/configknife.cpp \
    Machine/Config/configmachine.cpp \
    Machine/Config/configknifelib.cpp \
    Machine/Config/configapron.cpp \
    File/cutfiledraw.cpp \
    Machine/Config/configwhole.cpp \
    User/usermanager.cpp \
    User/user.cpp

HEADERS += \
    windowcutting.h \
    PhysicalLayer/hardwareadaptor.h \
    PhysicalLayer/gts.h \
    Machine/machine.h \
    Machine/Fan/fan.h \
    File/CutFileListOp/cutfilelistop.h \
    File/IniOp/iniop.h \
    User/userlog.h \
    Machine/Knife/Symbol.h \
    Machine/Knife/sdknife.h \
    Machine/Knife/sdknifeconfig.h \
    Machine/Knife/sdapron.h \
    Machine/Knife/sdmachinehead.h \
    Machine/Knife/sdmachine.h \
    Machine/Knife/sdcuttoollib.h \
    Machine/Config/confighead.h \
    Machine/Config/configknife.h \
    Machine/Config/configmachine.h \
    Machine/Config/configknifelib.h \
    Machine/Config/configapron.h \
    Machine/Config/configinfo.h \
    File/cutfiledraw.h \
    File/cutfileformat.h \
    Machine/Config/configwhole.h \
    User/usermanager.h \
    User/user.h

FORMS += \
        windowcutting.ui \
    File/Settings/settings.ui \
    File/IniOp/iniop.ui \
    User/userlog.ui \
    User/usermanager.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/PhysicalLayer/ -lgts
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/PhysicalLayer/ -lgts
else:unix: LIBS += -L$$PWD/PhysicalLayer/ -lgts

INCLUDEPATH += $$PWD/PhysicalLayer
DEPENDPATH += $$PWD/PhysicalLayer
