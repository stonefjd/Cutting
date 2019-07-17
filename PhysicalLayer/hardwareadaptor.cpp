#include "hardwareadaptor.h"

HardwareAdaptor::HardwareAdaptor(QObject *parent) : QObject(parent)
{
//    QTimer *hardwareIOTimer = new QTimer;
//    connect(hardwareIOTimer,SIGNAL(timeout()),SLOT(Slot_Action_CheckHardWareError()));
//    hardwareIOTimer->start(1000);
}

#ifdef GOOGOL_PLUSE_4AXIS
    //--转速模式结构体，插补模式结构体
    static  TJogPrm Jog;
    static  TCrdPrm crdPrm;
#endif
short ADP_GetLimit(short _index,long *_pPos,long *_pNeg)
{
#ifdef GOOGOL_PLUSE_4AXIS
    return GT_GetSoftLimit(_index,_pPos,_pNeg);
#elif
    return 0;
#endif
}

void ADP_Connect()
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_Open();
#endif
}
void ADP_Disconnect()
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_Close();
#endif
}
void ADP_Reset()
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_Reset();
#endif
}
void ADP_AxisOn(short _axis)
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_AxisOn(_axis);
#endif
}
void ADP_ZeroPos(short _axis)
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_ZeroPos(_axis);
#endif
}
void ADP_ClrSts(short axis, short count)
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_ClrSts(axis, count);
#endif
}
void ADP_GetSts(short axis, long *pSts)
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_GetSts(axis, pSts);
#endif
}
void ADP_LoadCfgFile(QString _path)
{
#ifdef GOOGOL_PLUSE_4AXIS
    QByteArray qByteArray= _path.toUtf8();
    char *cStr = qByteArray.data();
    GT_LoadConfig(cStr);
#endif
}

bool ADP_GetAxisMotorEnState(short _axis)
{
#ifdef GOOGOL_PLUSE_4AXIS
    long *pSts = new long;
    GT_GetSts(_axis,pSts);
    if( (*pSts&0x0200) != 0)
        return true;
    else
        return false;
#else
    return false;
#endif
}
bool ADP_GetAxisPlanRunState(short _axis)
{
#ifdef GOOGOL_PLUSE_4AXIS
    long *pSts = new long;
    GT_GetSts(_axis,pSts);
    if( (*pSts&0x0400) != 0)
        return true;
    else
        return false;
#else
    return false;
#endif
}
void ADP_Update(short _axis)
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_Update(static_cast<long>(1<<(_axis-1)));
#endif
}
void ADP_GetLimitState(short _axis,bool _polar,bool *_state)
{
#ifdef GOOGOL_PLUSE_4AXIS
    long *pSts = new long;
    GT_GetSts(_axis,pSts);
    if(_polar == true)
    {
        if((*pSts&0x20) !=0)
            *_state = true;
        else
            *_state = false;
    }
    else if(_polar == false)
    {
        if((*pSts&0x40) !=0)
            *_state = true;
        else
            *_state = false;
    }
#endif
}
void ADP_PrfJog(short _profile)
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_PrfJog(_profile);
#endif
}
void ADP_SetJogPrm(short _profile,TJogPrm *_pPrm)
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_SetJogPrm(_profile,_pPrm);
#endif
}
void ADP_SetVel(short _profile,double _vel)
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_SetVel(_profile,_vel);
#endif
}
void ADP_SetPrfPos(short _profile,long _prfPos)
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_SetPrfPos(_profile,_prfPos);
#endif
}
void ADP_SetCrdPrm(short _crd,TCrdPrm *_pCrdPrm)
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_SetCrdPrm(_crd,_pCrdPrm);
#endif
}
void ADP_CrdClear(short _crd,short _fifo)
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_CrdClear(_crd,_fifo);
#endif
}
void ADP_LnXY(short crd,long x,long y,double synVel,double synAcc,double velEnd,short fifo)
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_LnXY( crd, x, y, synVel, synAcc, velEnd, fifo);
#endif
}
void ADP_CrdStart(short _mask,short _option)
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_CrdStart(_mask,_option);
#endif
}
void ADP_Stop(long _mask,long _option)
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_Stop(_mask,_option);
#endif
}
void ADP_GetAxisPrfPos(short _axis,double *_pValue)
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_GetAxisPrfPos( _axis, _pValue);
#endif
}
//void ADP_
//{
//#ifdef GOOGOL_PLUSE_4AXIS
//#endif
//}

//板子初始化，主要包括轴卡连接，复位以及读取配置文件
void ADP_InitData()
{
#ifdef GOOGOL_PLUSE_4AXIS
    memset(&crdPrm, 0, sizeof(crdPrm));
    crdPrm.dimension=2;   // 坐标系为二维坐标系
    crdPrm.synVelMax=500;  // 最大合成速度：500pulse/ms
    crdPrm.synAccMax=1;   // 最大加速度：1pulse/ms^2，约为10m/s^2
    crdPrm.evenTime = 50;   // 最小匀速时间：50ms
    crdPrm.profile[0] = 1;   // 规划器1对应到X轴
    crdPrm.profile[1] = 2;   // 规划器2对应到Y轴
    crdPrm.setOriginFlag = 1;  // 表示需要指定坐标系的原点坐标的规划位置
    crdPrm.originPos[0] = 00000;  // 坐标系的原点坐标的规划位置为（100, 100）
    crdPrm.originPos[1] = 00000;

    Jog.acc = 0;
    Jog.dec = 0;
    Jog.smooth = 0.5;
#endif
}
void ADP_InitBoard(QString _path)
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_Close();
    GT_Open();
    GT_Reset();
    ADP_LoadCfgFile(_path);
#endif
}
//使能所有轴号
void ADP_EnableAllAxis()
{
#ifdef GOOGOL_PLUSE_4AXIS
    ADP_ClrSts(AXIS_FIRST,AXIS_MAX);
    ADP_AxisOn(AXIS_X);
    ADP_AxisOn(AXIS_Y);
    ADP_AxisOn(AXIS_Z1);
    ADP_AxisOn(AXIS_A1);
#endif
}
//禁止所有轴号
void ADP_DisableALLAxis()
{
#ifdef GOOGOL_PLUSE_4AXIS
    ADP_ClrSts(AXIS_FIRST,AXIS_MAX);
    GT_AxisOff(AXIS_X);
    GT_AxisOff(AXIS_Y);
    GT_AxisOff(AXIS_Z1);
    GT_AxisOff(AXIS_A1);
#endif
}
//清除所有轴的规划位置和实际位置
void ADP_ZeroPosALl()
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_ZeroPos(AXIS_X);
    GT_ZeroPos(AXIS_Y);
    GT_ZeroPos(AXIS_Z1);
    GT_ZeroPos(AXIS_A1);
#endif
}
void ADP_GetGpi(long *_diValue)
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_GetDi(MC_GPI,_diValue);
#endif
}
void ADP_SetGpo(long _doValue)
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_SetDo(MC_GPO,_doValue);
#endif
}
void ADP_StartHome()
{
#ifdef GOOGOL_PLUSE_4AXIS
    for(short i=0;i<AXIS_MAX;i++)
        GT_SetDoBit(MC_GPO,i+1,0);
#endif
}
void ADP_StopHome()
{
#ifdef GOOGOL_PLUSE_4AXIS
    for(short i=0;i<AXIS_MAX;i++)
        GT_SetDoBit(MC_GPO,i+1,1);
#endif
}
void ADP_StartMovePoint(short _crd,short _fifo,long _xPos,long _yPos,double spd,double acc)
{
#ifdef GOOGOL_PLUSE_4AXIS
    ADP_SetCrdPrm(_crd, &crdPrm);
    ADP_CrdClear(_crd, _fifo);
     // 该插补段的坐标系是坐标系1 //xy点// 该插补段的目标速度：3pulse/ms // 插补段的加速度：0.1pulse/ms^2// 终点速度为0 // 向坐标系1的FIFO0缓存区传递该直线插补数据
    ADP_LnXY(1,_xPos,_yPos,spd,acc,0,_fifo);
    ADP_CrdStart(_crd, 0);
#endif
}
void ADP_GetRunStateAndSegment(short _crd, short *_pRun, long *_pSegment, short _fifo)
{
#ifdef GOOGOL_PLUSE_4AXIS
    GT_CrdStatus(_crd,_pRun,_pSegment,_fifo);
#endif
}
//从控制器中读取当前的位置
void ADP_GetHeadPosRt(QPointF *_posRt,double _ppm)
{
#ifdef GOOGOL_PLUSE_4AXIS
    double xPluse,yPluse;
    ADP_GetAxisPrfPos(AXIS_X,&xPluse);
    ADP_GetAxisPrfPos(AXIS_Y,&yPluse);
    if(_ppm != 0.0)
    {
        _posRt->setX(xPluse/_ppm);
        _posRt->setY(yPluse/_ppm);
    }
    else
    {
        _posRt->setX(xPluse);
        _posRt->setY(yPluse);
    }
#endif
}
bool ADP_GetAxisRunState(short _axis)
{
#ifdef GOOGOL_PLUSE_4AXIS
    bool val = false;
    long state = 0;
    GT_GetSts(_axis, &state);
    if((state&0x0400) != 0)
        val = true;
    else
        val = false;
    return val;
#elif
    return false;
#endif
}
void ADP_SetJogMode(short _axis,double _spd,double _acc)
{
#ifdef GOOGOL_PLUSE_4AXIS    

    Jog.acc = _acc;
    Jog.dec = _acc;
    Jog.smooth = 0.5;
    GT_PrfJog(_axis);
    GT_SetJogPrm (_axis,&Jog);
    GT_SetVel(_axis, _spd);
    long mask = static_cast<long>(1<<(_axis-1));
    GT_Update(mask);

//    ADP_PrfJog(_axis);
//    ADP_SetJogPrm (_axis,&Jog);
//    ADP_SetVel(_axis, _spd);
//    ADP_Update(_axis);
#endif
}

void ADP_SetFanStop()
{
#ifdef GOOGOL_PLUSE_4AXIS
#endif
}
void ADP_SetFanWindIn()
{
#ifdef GOOGOL_PLUSE_4AXIS
#endif
}
void ADP_SetFanWindOut()
{
#ifdef GOOGOL_PLUSE_4AXIS
#endif
}
bool ADP_GetFanErrorState()
{
#ifdef GOOGOL_PLUSE_4AXIS
    return false;
#else
    return false;
#endif
}
