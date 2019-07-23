#ifndef D_CTRLMACH_H
#define D_CTRLMACH_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QPointF>
#include <QKeyEvent>


#include "PhysicalLayer/hardwareadaptor.h"
#include "Machine/Config/cfgmachhandle.h"
#include "File/cutfilehandle.h"

struct DirBit
{
    int  pos;
    int  neg;
};

const int DIR_W = 0;
const int DIR_S = 1;
const int DIR_A = 2;
const int DIR_D = 3;
const int DIR_SUM = 4;
enum CtrlMode
{
    ctrlModeFF,//Z进给，A进给
    ctrlModePF,//Z冲，A进给
    ctrlModeFS,//Z进给，A旋转
    ctrlModePS,//Z冲，A旋转
};
enum MainState
{
    stMain_Stop,
    stMain_Init,
    stMain_Wait,
    stMain_Oprt,
    stMain_Cut,
    stMain_Err,
};
enum SubStateInit
{
    stInit_NotIn,
    stInit_BoardInit,
    stInit_BackMachOrg,
    stInit_BackLogicOrg,
};

enum SubStateOprt
{
    stOprt_NotIn,
    stOprt_BtnO,
    stOprt_BndrRsz,
    stOprt_RngScan,
    stOprt_RngRst,
    stOprt_ToolDeepCalib,
    stOprt_ToolPosCalib,
    stOprt_Fnsh,


    stOprt_Fail,
    stOprt_SizeCalibration_step1,
    stOprt_SizeCalibration_step2,
    stOprt_SizeCalibration_step3,
    stOprt_EdgeScane_step1,
};

enum SubStateCut
{
    stCut_NotIn,
    stCut_FirstIn,
    stCut_Run,
    stCut_Pause,
    stCut_Wait,
    stCut_Continue,
    stCut_Stop,
    stCut_Finish,
};
enum StepCnt
{
    stStepNotIn,
    stStep1,
    stStep2,
    stStep3,
    stStep4,
    stStep5,
    stStepLast,
};

/*     控制系统中预定义的内容：1.轴默认顺序为X,Y,Z1,A1,Z2,A2.四轴卡只有前面四个，六/八轴卡为6个轴
 *     回原点的方式在轴卡中固定设置为自动回原点，回到原点后发出IO信号。每个驱动器都会在轴卡上有一个DI信号对应。
 * 由于回原点后不同的驱动器的响应情况不同（汇川翻转电平，禾川脉冲电平持续2s），因此默认只要出现由高至低的跳变即可。
 * 关于机器匹配的问题，在驱动额定转速3000r/min的伺服电机时，需要给所有的伺服驱动器的设置为10000pluse/r的驱动精度，并且脉冲最大频率设置为500K。
 * 因此脉冲折算为尺寸的精度可以直接放入配置文件,目前区分了X和Y轴，实际上XY应保持一致，默认采用X轴。
 */

class D_CtrlMach : public QObject
{
    Q_OBJECT
private:

//--系统状态变量与子状态变量
    MainState       m_stMainThis = stMain_Init;
    MainState       m_stMainLast = stMain_Stop;

    SubStateInit    m_stSubInit = stInit_NotIn;
    SubStateOprt    m_stSubOprt = stOprt_NotIn;
    SubStateCut     m_stSubCut  = stCut_NotIn;
//--机头传入参数
    QPointF*    posOrg;             //逻辑切割原点
    QPointF*    posLmt;             //逻辑切割范围
    QPointF*    posMax;             //全局最大运动边界
    double*     posToPulseScaleXY;    //每毫米脉冲数
    double*     idleMoveSpd;         //空走速度 (m/s)
    double*     idleMoveAcc;         //空走加速度(G)
    QList<CfgApron*> *cfgApronList;
//--切割文件传入原始数据
    CutFile_Data *cutFile_Data;
//--传出参数
    QPointF posRT;
    double  pluseRT[2];
//--跳转辅助变量
    bool    m_cdInitMachOrg[AXIS_MAX] = {false};            //初始化回零状态位;value:0-Not OK,1-OK
    uint8_t m_cdDirCmd = 0;                                 //KeyBoard与Push Button方向按键记录bit0-W,bit1-S,bit2-A,bit3-D;value:0:released;1:pressed
    DirBit  m_dirBitMove[2];                                //存储按键变量移位的位数,与m_cdDirCmd相对应,初始化存储位
    StepCnt m_cdOprtStepBndrRsz         = stStepNotIn;      //存储操作状态下，边缘校准的步骤
    StepCnt m_cdOprtStepRngRst          = stStepNotIn;      //存储操作状态下，重设范围的步骤
    StepCnt m_cdOprtStepToolPosCalib    = stStepNotIn;      //存储操作状态下，刀位校准的步骤
    StepCnt m_cdCutStepCountine         = stStepNotIn;
//--轴控制变量
    short       m_nCtrlAxisZ = AXIS_NULL;       //默认Z轴
    short       m_nCtrlAxisA = AXIS_NULL;       //默认A轴
    CtrlMode    m_emCtrlMode = ctrlModeFF;      //默认轴控制方式
    double      m_nKnifeMaxDeep = 0;            //默认深度
//--轴运行结构体变量
    TJogPrm m_tJogPrm;
    TCrdPrm m_tCrdPrm;
//--状态变量
    bool    m_stAxisRunState[AXIS_MAX];         //轴运行状态
    double  m_nPlusePause[2];                      //切割状态下暂停点
    bool    m_cdCutSim = false;                 //模拟裁切标志位：0：模拟裁切;1：实际裁切
    int     m_ctCutSampleNow = 0;
//--相关常量参数
    const double mc_crossLen = 15.0;//画十字的长度15mm
private:
    void StateMachScheduleSubInit();
    void StateMachScheduleSubWait();
    void StateMachScheduleSubOprt();
    void StateMachScheduleSubCut();

//--辅助函数,根据按键和button状态匀速运行轴
    void JoggingForAxis(short _axis,double _lowSpdScale = 1);
public:
    explicit D_CtrlMach(QObject *parent = nullptr);

//--状态运行
    void GetRunningData();
    void StateMachScheduleMain();

//--外部事件触发状态跳转
    void EventOprtSubEnter(int _id);
    void EventOprtSubEnterToolPosCalib();
    void EventOprtSubExitToolPosCalib();
    void EventRunSubEnterRunPuase(bool _clicked);
    void EventRunSubEnterStop();
    void EventActionKey(QKeyEvent event);
//--系统状态读
    MainState GetMainState();
//--跳转状态读
    StepCnt GetCdtOprtStepToolPosCalib();
//--轴控制量写
    void    SetCtrlAxisGroup(int _idApron);
//--轴状态读
    bool    GetAxisRunState(short _axis);
//--传入参数读写
    void    SetPosOrg(QPointF* _pointF);
    void    SetPosLmt(QPointF* _pointF);
    void    SetPosMax(QPointF* _pointF);
    void    SetPosToPulseScaleXY(double* _val);
    void    SetIdleMoveSpd(double* _val);
    void    SetIdleMoveAcc(double* _val);
    void    SetCfgApronList(QList<CfgApron*> *_list);

    void    SetCutFileData(CutFile_Data *_cutFile_Data);

    QPointF* GetPosOrg();
    QPointF* GetPosLmt();
    QPointF* GetPosMax();
    double*  GetPosToPulseScaleXY();
    double*  GetIdleMoveSpd();
    double*  GetIdleMoveAcc();
    QList<CfgApron*>* GetCfgApronList();

//--传出参数读
    QPointF* GetPosRT();
signals:
    void UpdateDataHeadPosMax();
public slots:
    void SlotBtnPressed(int _id);
    void SlotBtnReleased(int _id);
};

#endif // D_CTRLMACH_H
