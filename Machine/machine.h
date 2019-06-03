#ifndef MACHINE_H
#define MACHINE_H

#include <QObject>
#include <QKeyEvent>
#include <QThread>
#include "Fan/fan.h"
#include "PhysicalLayer/hardwareadaptor.h"
//#include "Machine/Knife/sdknifeconfig.h"
#include "Machine/Config/configmachine.h"
#include "Machine/Config/confighead.h"
#include "File/cutfileformat.h"


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
#define stSubOperate_SizeCalibration_step1   12
#define stSubOperate_SizeCalibration_step2   13
#define stSubOperate_SizeCalibration_step3   14
#define stSubOperate_EdgeScane_step1   15

#define stSubCut_NotIn      0
#define stSubCut_FirstIn    1
#define stSubCut_Run        2
#define stSubCut_Pause      3
#define stSubCut_Continue   4
#define stSubCut_Stop       5
#define stSubCut_Finish     6
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
    bool mStatePower;
    bool mStateMotorRunningX;
    bool mStateMotorRunningY;
public:
    bool GetStateMotorRunningX();
    bool GetStateMotorRunningY();
    uint8_t GetMachineMainState();
private:
    QTimer *mTimer;
    uint8_t machine_stMainState;

    uint8_t machine_stSubState_Stop;
    uint8_t machine_stSubState_Init;
    uint8_t machine_stSubState_Wait;
    uint8_t machine_stSubState_Operate;
    uint8_t machine_stSubState_Cut;
    uint8_t machine_stSubState_Pause;
    uint8_t machine_stSubState_Err;

    uint8_t machine_ctSubState_Operate_Key;
    int     machine_ctSubState_Cut_SampleFinished;
    int     machine_ctSubState_Cut_WindowFinished;
    int     machine_ctSubState_Cut_FileFinished;
private:
    TJogPrm Jog;
    TCrdPrm crdPrm;
public:
    explicit Machine(QObject *parent = nullptr);
public: // sub class obj
    Fan mFan_1;
//    SDKnifeConfig sdKnifeConfigLib;
private:
    QPointF *head0_Org;
    QPointF *head0_Limit;
    QPointF *head0_PulsePerMillimeter;
    QList<fileData_t> *fileContent;
public:
    QPointF head0_Pos;
    double  head0_MoveAngel;
    QPointF head0_PosLast;
public:
    void Mach_SetHead0Org(QPointF *_head0_Org);
    void Mach_SetHead0PulsePerMillimeter(QPointF *_head0_PulsePerMillimeter);
    void Mach_SetHead0Limit(QPointF *_head0_Limit);
    void Mach_SetCutContent(QList<fileData_t> *_fileContent);
public:
    void MInit();
    void MainStateRun();
    void SubStateRunInitial();
    void SubStateRunWait();
    void SubStateRunOperate();
    void SubStateRunCut();

    void GetRunningData();
signals:
    void UpdateMachineMaxPluse(double _xPos, double _yPos);
public slots:
    void Task_10ms();
    void SubStateOpBtnPress(int id);
    void SubStateOpBtnRelease(int id);
    void SubStateOpKeyPress(QKeyEvent event);
    void SubStateOpKeyRelease(QKeyEvent event);
    void SubStateOpBtnReSize();
    void SubStateOpBtnEdgeScan();
    void SubStateCutRunOrPause(bool _pressed);
    void SubStateCutStop();
};

#endif // MACHINE_H
