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
