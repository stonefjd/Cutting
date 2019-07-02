#ifndef CFGMACHHANDLE_H
#define CFGMACHHANDLE_H

#include <QObject>
//#include "cfgmach.h"
//#include "cfghead.h"
//#include "cfglib.h"
#include "cfgmachsettings.h"
#include "cfgknifemanager.h"
class CfgMachHandle : public QObject
{
    Q_OBJECT
public:
    explicit CfgMachHandle(QObject *parent = nullptr);

    CfgMach mConfig;
    CfgHead hConfig;
    QList<CfgApron*> aConfig;
    CfgLib  lConfig;
    CfgMachSettings *UI_cfgMachSettings;
    CfgKnifeManager *UI_cfgKnifeManager;

public:
    void ShowMachSettings(UserHandle *_userHandle);
    void ShowKnifeManager(UserHandle *_userHandle);


signals:

public slots:
    void UpdateConfigMaxPluse(double _xPos, double _yPos);

};

#endif // CFGMACHHANDLE_H
