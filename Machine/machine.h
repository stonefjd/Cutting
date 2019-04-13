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

#define stMain_Stop         0
#define stMain_Init         1
#define stMain_Wait         2
#define stMain_Operate      3
#define stMain_Cut          4
#define stMain_Pause        5
#define stMain_Err          6

#define stSubInit_NotIn  0
#define stSubInit_In     1
#define stSubInit_MOrg   2
#define stSubInit_LOrg   3
#define stSubInit_Finish 4
#define stSubInit_Fail   5


//#define stSubNotIn      0
//#define stSubData       1
//#define stSubMotorRun   2
//#define stSubTimeDelay  3
//#define stSubWait       4
//#define stSubFinish     5
//#define stSubFail       6
class Machine : public QObject
{
    Q_OBJECT
private:
    bool mPowerState;
    QTimer *mTimer;

    uint8_t machine_stMainState;
    uint8_t machine_stSubState_Stop;
    uint8_t machine_stSubState_Init;
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
    void MainStateRun();
    void SubStateRunInitial();
signals:
public slots:
    void Task_10ms();
};

#endif // MACHINE_H
