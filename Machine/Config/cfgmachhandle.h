#ifndef CFGMACHHANDLE_H
#define CFGMACHHANDLE_H

#include <QObject>
#include "cfgmach.h"
#include "cfghead.h"
#include "cfgmachsettings.h"
class CfgMachHandle : public QObject
{
    Q_OBJECT
public:
    explicit CfgMachHandle(QObject *parent = nullptr);

    CfgMach mConfig;
    CfgHead hConfig;
    CfgMachSettings *UI_cfgMachSetting;

public:
    void ShowSettings();
signals:

public slots:
    void UpdateConfigMaxPluse(double _xPos, double _yPos);

};

#endif // CFGMACHHANDLE_H
