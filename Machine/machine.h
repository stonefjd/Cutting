#ifndef MACHINE_H
#define MACHINE_H

#include <QObject>

#include "Fan/fan.h"
#include "Limit/limitswitch.h"
#include "Machine/Knife/sdknifeconfig.h"

#define X_AXIS 0
#define Y_AXIS 1

#define X_Limit 0
#define Y_Limit 1
#define Z_Limit 2
#define A_Limit 3

enum MStateMain_T {
    MPowerOn    = 0x0000,
    MSelfTest   = 0x0001,   //power on test,check everything.
    MWait       = 0x0002,   //wait for all device OK,if not ok display it.
    MInitial    = 0x0003,   //run to the Mechanical limit zero point for the all axes correction.
    MOperate    = 0x0004,   //moving the tool in 2 axis.
    MStop       = 0x0005,   //
    MRunning    = 0x0006,
    MPause      = 0x0007,
    MErrorOccur = 0x0008,
};

class Machine : public QObject
{
    Q_OBJECT
public:
    explicit Machine(QObject *parent = nullptr);
    Fan mFan_1;
    SDKnifeConfig       sdKnifeConfigLib;

    QList<LimitSwitch*> limitList ;//= new LimitSwitch(X_Limit);
signals:

public slots:
private:
    bool mPowerState;
};

#endif // MACHINE_H
