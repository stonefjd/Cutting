#include "hardwareadaptor.h"

HardwareAdaptor::HardwareAdaptor(QObject *parent) : QObject(parent)
{
//    QTimer *hardwareIOTimer = new QTimer;
//    connect(hardwareIOTimer,SIGNAL(timeout()),SLOT(Slot_Action_CheckHardWareError()));
//    hardwareIOTimer->start(1000);
}
void HardwareAdaptor::Slot_Action_CheckHardWareError()
{
    qDebug()<<"1000ms timer";
    if(1)
    {
        emit Signal_SetState_FanNoError();
    }
    else
    {
        emit Signal_SetState_FanError();
    }
}
void HardwareAdaptor::Slot_Action_FanStop()
{
    qDebug()<<"action FanStop";
}
void HardwareAdaptor::Slot_Action_FanWindIn()
{
    qDebug()<<"action FanWindIn";
}
void HardwareAdaptor::Slot_Action_FanWindOut()
{
    qDebug()<<"action FanWindOut";
}

short ADP_GetLimit(short _index,long *_pPos,long *_pNeg)
{
#ifdef GTSLIB
    return GT_GetSoftLimit(_index,_pPos,_pNeg);
#endif
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
void ADP_ClrSts(short axis, short count)
{
#ifdef GTSLIB
    GT_ClrSts(axis, count);
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
