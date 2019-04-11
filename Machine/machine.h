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

#define stMainStop      0
#define stMainInitial   1
#define stMainWait      2
#define stMainOperate   3
#define stMainCut       4
#define stMainPause     5
#define stMainErr       6

#define stSubNotIn      0
#define stSubData       1
#define stSubMotorRun   2
#define stSubTimeDelay  3
#define stSubWait       4

class Machine : public QObject
{
    Q_OBJECT
private:
    bool mPowerState;
    QTimer *mTimer;

    uint8_t machine_stMainState;
    uint8_t machine_stSubState_Stop;
    uint8_t machine_stSubState_Initial;
    uint8_t machine_stSubState_Wait;
    uint8_t machine_stSubState_Operate;
    uint8_t machine_stSubState_Cut;
    uint8_t machine_stSubState_Pause;
    uint8_t machine_stSubState_Err;

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
    void Task_10ms_stateMachine();
};

#endif // MACHINE_H
