#ifndef MACHINE_H
#define MACHINE_H

#include <QObject>

#include "Fan/fan.h"
#include "Limit/limitswitch.h"
#include "PhysicalLayer/hardwareadaptor.h"
#include "Machine/Knife/sdknifeconfig.h"

#define AXIS_X 1
#define AXIS_Y 2

#define X_Limit 1
#define Y_Limit 2
#define Z_Limit 3
#define A_Limit 4

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
private:
    bool mPowerState;
public:
    explicit Machine(QObject *parent = nullptr);
public: // sub class obj
    Fan mFan_1;
    SDKnifeConfig sdKnifeConfigLib;

    QList<LimitSwitch*> limitList ;//= new LimitSwitch(X_Limit);
public:
    void MInit();
signals:
public slots:

};

#endif // MACHINE_H
