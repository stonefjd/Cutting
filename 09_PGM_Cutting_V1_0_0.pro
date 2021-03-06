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
    User/userlog.cpp \
    User/usermanager.cpp \
    User/user.cpp \
    User/userhandle.cpp \
    Machine/Config/cfgmachsettings.cpp \
    Machine/Config/cfgmachhandle.cpp \
    Machine/Config/cfgmach.cpp \
    Machine/Config/cfghead.cpp \
    Machine/Config/cfgknife.cpp \
    Machine/Config/cfgbasedefine.cpp \
    Machine/Config/cfglib.cpp \
    Machine/Config/cfgcuttool.cpp \
    Machine/Config/cfgknifemanager.cpp \
    Machine/Config/cfgapron.cpp \
    Base/cutsample.cpp \
    Base/cutline.cpp \
    Base/cutfile.cpp \
    Base/cutpage.cpp \
    File/cutfilehandle.cpp \
    File/cutfile_ui.cpp \
    File/cutfile_data.cpp \
    Control/u_ctrltoolposcalib.cpp \
    Control/u_ctrlbtndir.cpp \
    Control/u_ctrlrngrst.cpp \
    Control/h_ctrlmach.cpp \
    Control/d_ctrlmach.cpp

HEADERS += \
    windowcutting.h \
    PhysicalLayer/hardwareadaptor.h \
    PhysicalLayer/gts.h \
    Machine/machine.h \
    Machine/Fan/fan.h \
    User/userlog.h \
    User/usermanager.h \
    User/user.h \
    User/userhandle.h \
    Machine/Config/cfgmachsettings.h \
    Machine/Config/cfgmachhandle.h \
    Machine/Config/cfgmach.h \
    Machine/Config/cfghead.h \
    Machine/Config/cfgknife.h \
    Machine/Config/cfgbasedefine.h \
    Machine/Config/cfglib.h \
    Machine/Config/cfgcuttool.h \
    Machine/Config/cfgknifemanager.h \
    Machine/Config/cfgapron.h \
    Base/cutsample.h \
    Base/cutline.h \
    Base/cutfile.h \
    Base/cutpage.h \
    File/cutfilehandle.h \
    File/cutfile_ui.h \
    File/cutfile_data.h \
    Control/u_ctrltoolposcalib.h \
    Control/u_ctrlbtndir.h \
    Control/u_ctrlrngrst.h \
    Control/h_ctrlmach.h \
    Control/d_ctrlmach.h

FORMS += \
        windowcutting.ui \
    File/Settings/settings.ui \
    User/userlog.ui \
    User/usermanager.ui \
    Machine/Config/cfgmachsettings.ui \
    Machine/Config/cfgknifemanager.ui \
    Control/u_ctrltoolposcalib.ui \
    Control/u_ctrlrngrst.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/PhysicalLayer/ -lgts
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/PhysicalLayer/ -lgts
else:unix: LIBS += -L$$PWD/PhysicalLayer/ -lgts

INCLUDEPATH += $$PWD/PhysicalLayer
DEPENDPATH += $$PWD/PhysicalLayer
