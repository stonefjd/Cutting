#ifndef CONFIGMACHINEHANDLE_H
#define CONFIGMACHINEHANDLE_H

#include <QObject>
#include "configmachine.h"
#include "confighead.h"

class ConfigMachineHandle : public QObject
{
    Q_OBJECT
public:
    explicit ConfigMachineHandle(QObject *parent = nullptr);

    ConfigMachine   mConfig;
    ConfigHead      hConfig;
signals:

public slots:
    void UpdateConfigMaxPluse(double _xPos, double _yPos);

};

#endif // CONFIGMACHINEHANDLE_H
