#ifndef MACHINE_H
#define MACHINE_H

#include <QObject>
#include <QKeyEvent>
#include "Fan/fan.h"
#include "PhysicalLayer/hardwareadaptor.h"
#include "Machine/Knife/sdknifeconfig.h"
#include "Machine/Config/configmachine.h"
#include "Machine/Config/confighead.h"



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

#define stSubOperate_NotIn  0
#define stSubOperate_Key   1
#define stSubOperate_BtnL   5
#define stSubOperate_BtnR   6
#define stSubOperate_BtnU   7
#define stSubOperate_BtnD   8
#define stSubOperate_BtnO   9
#define stSubOperate_Finish 10
#define stSubOperate_Fail   11
#define stSubOperate_EdgeScane_step1   12
#define stSubOperate_EdgeScane_step2   13
#define stSubOperate_EdgeScane_step3   14
#define stSubOperate_EdgeScane_step4   15

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

    uint8_t machine_stSubState_Stop;
    uint8_t machine_stSubState_Init;
    uint8_t machine_stSubState_Wait;
    uint8_t machine_stSubState_Operate;
    uint8_t machine_stSubState_Cut;
    uint8_t machine_stSubState_Pause;
    uint8_t machine_stSubState_Err;

private:
    TJogPrm Jog;
    TCrdPrm crdPrm;
public:
    explicit Machine(QObject *parent = nullptr);
public: // sub class obj
    uint8_t machine_stMainState;
    uint8_t machine_ctSubState_Operate_Key;
    Fan mFan_1;
    SDKnifeConfig sdKnifeConfigLib;
    ConfigMachine   mConfig;
public:
    void MInit();
    void MainStateRun();
    void SubStateRunInitial();
    void SubStateRunWait();
    void SubStateRunOperate();
    void SubStateRunCut();

signals:
public slots:
    void Task_10ms();
    void SubStateOpBtnPress(int id);
    void SubStateOpBtnRelease(int id);
    void SubStateOpKeyPress(QKeyEvent event);
    void SubStateOpKeyRelease(QKeyEvent event);
    void SubStateOpBtnSizeCalibration();

};

#endif // MACHINE_H
