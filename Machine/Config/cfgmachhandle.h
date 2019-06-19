#ifndef CFGMACHHANDLE_H
#define CFGMACHHANDLE_H

#include <QObject>
#include "configmachine.h"
#include "confighead.h"

class CfgMachHandle : public QObject
{
    Q_OBJECT
public:
    explicit CfgMachHandle(QObject *parent = nullptr);

    ConfigMachine   mConfig;
    ConfigHead      hConfig;
signals:

public slots:
    void UpdateConfigMaxPluse(double _xPos, double _yPos);

};

#endif // CFGMACHHANDLE_H
