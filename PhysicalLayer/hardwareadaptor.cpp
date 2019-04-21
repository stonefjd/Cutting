#include "hardwareadaptor.h"

HardwareAdaptor::HardwareAdaptor(QObject *parent) : QObject(parent)
{
//    QTimer *hardwareIOTimer = new QTimer;
//    connect(hardwareIOTimer,SIGNAL(timeout()),SLOT(Slot_Action_CheckHardWareError()));
//    hardwareIOTimer->start(1000);
}


short ADP_GetLimit(short _index,long *_pPos,long *_pNeg)
{
#ifdef GTSLIB
    return GT_GetSoftLimit(_index,_pPos,_pNeg);
#endif
    return 0 ;
}

void ADP_Connect()
{
#ifdef GTSLIB
    GT_Open();
#endif
}
void ADP_Reset()
{
#ifdef GTSLIB
    GT_Reset();
#endif
}
void ADP_AxisOn(short _axis)
{
#ifdef GTSLIB
    GT_AxisOn(_axis);
#endif
}
void ADP_ZeroPos(short _axis)
{
#ifdef GTSLIB
    GT_ZeroPos(_axis);
#endif
}
void ADP_ClrSts(short axis, short count)
{
#ifdef GTSLIB
    GT_ClrSts(axis, count);
#endif
}
void ADP_GetSts(short axis, long *pSts)
{
#ifdef GTSLIB
    GT_GetSts(axis, pSts);
#endif
}
void ADP_LoadCfgFile(QString _path)
{
#ifdef GTSLIB
    QByteArray qByteArray= _path.toUtf8();
    char *cStr = qByteArray.data();
    GT_LoadConfig(cStr);
#endif
}
void ADP_Disconnect()
{
#ifdef GTSLIB
    GT_Close();
#endif
}

bool ADP_GetAxisMotorEnState(short _axis)
{
#ifdef GTSLIB
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
#ifdef GTSLIB
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
#ifdef GTSLIB
    GT_Update(static_cast<long>(1<<(_axis-1)));
#endif
}
void ADP_GetLimitState(short _axis,bool _polar,bool *_state)
{
#ifdef GTSLIB
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
#ifdef GTSLIB
    GT_PrfJog(_profile);
#endif
}
void ADP_SetJogPrm(short _profile,TJogPrm *_pPrm)
{
#ifdef GTSLIB
    GT_SetJogPrm(_profile,_pPrm);
#endif
}
void ADP_SetVel(short _profile,double _vel)
{
#ifdef GTSLIB
    GT_SetVel(_profile,_vel);
#endif
}
void ADP_SetPrfPos(short _profile,long _prfPos)
{
#ifdef GTSLIB
    GT_SetPrfPos(_profile,_prfPos);
#endif
}
void ADP_SetCrdPrm(short _crd,TCrdPrm *_pCrdPrm)
{
#ifdef GTSLIB
    GT_SetCrdPrm(_crd,_pCrdPrm);
#endif
}
void ADP_CrdClear(short _crd,short _fifo)
{
#ifdef GTSLIB
    GT_CrdClear(_crd,_fifo);
#endif
}
void ADP_LnXY(short crd,long x,long y,double synVel,double synAcc,double velEnd,short fifo)
{
#ifdef GTSLIB
    GT_LnXY( crd, x, y, synVel, synAcc, velEnd, fifo);
#endif
}
void ADP_CrdStart(short _mask,short _option)
{
#ifdef GTSLIB
    GT_CrdStart(_mask,_option);
#endif
}
void ADP_Stop(long _mask,long _option)
{
#ifdef GTSLIB
    GT_Stop(_mask,_option);
#endif
}
void ADP_GetAxisPrfPos(short _axis,double *_pValue)
{
#ifdef GTSLIB
    GT_GetAxisPrfPos( _axis, _pValue);
#endif
}
//void ADP_
//{
//#ifdef GTSLIB
//#endif
//}
void ADP_SetFanStop()
{
#ifdef GTSLIB
#endif
}
void ADP_SetFanWindIn()
{
#ifdef GTSLIB
#endif
}
void ADP_SetFanWindOut()
{
#ifdef GTSLIB
#endif
}
bool ADP_GetFanErrorState()
{
#ifdef GTSLIB
    return false;
#else
    return false;
#endif
}
