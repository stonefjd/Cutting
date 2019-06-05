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
enum MainState
{
    stMain_Stop,
    stMain_Init,
    stMain_Wait,
    stMain_Operate,
    stMain_Cut,
    stMain_Err,
};
enum SubState_Init
{
    stSubInit_NotIn,
    stSubInit_In,
    stSubInit_MOrg,
    stSubInit_LOrg,
    stSubInit_Finish,
    stSubInit_Fail,
};

enum SubState_Operate
{
    stSubOperate_NotIn,
    stSubOperate_Key,
    stSubOperate_BtnL,
    stSubOperate_BtnR,
    stSubOperate_BtnU,
    stSubOperate_BtnD,
    stSubOperate_BtnO,
    stSubOperate_Finish,
    stSubOperate_Fail,
    stSubOperate_SizeCalibration_step1,
    stSubOperate_SizeCalibration_step2,
    stSubOperate_SizeCalibration_step3,
    stSubOperate_EdgeScane_step1,
};

enum SubState_Cut
{
    stSubCut_NotIn,
    stSubCut_FirstIn,
    stSubCut_Run,
    stSubCut_Pause,
    stSubCut_Continue,
    stSubCut_Stop,
    stSubCut_Finish,
};

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
    MainState machine_stMainState;

    SubState_Init       machine_stSubState_Init;
    SubState_Operate    machine_stSubState_Operate;
    SubState_Cut        machine_stSubState_Cut;

    uint8_t machine_stSubState_Stop;
    uint8_t machine_stSubState_Wait;
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
    double  *head0_IdleMoveSpd;
    double  *head0_IdleMoveAcc;
public:
    QPointF head0_Pos;
    double  head0_MoveAngel;
    QPointF head0_PosLast;
public:
    void Mach_SetHead0Org(QPointF *_head0_Org);
    void Mach_SetHead0PulsePerMillimeter(QPointF *_head0_PulsePerMillimeter);
    void Mach_SetHead0Limit(QPointF *_head0_Limit);
    void Mach_SetCutContent(QList<fileData_t> *_fileContent);
    void Mach_SetHead0IdleMoveSpd(double *_movSpd);
    void Mach_SetHead0IdleMoveAcc(double *_movAcc);

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
