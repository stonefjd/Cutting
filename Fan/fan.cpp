#include "fan.h"

Fan::Fan(QObject *parent) : QObject(parent)
{
    this->mStateFan = FanStop;
    HardwareAdaptor *hdAdpFan = new HardwareAdaptor;
    connect(this,SIGNAL(Signal_Action_FanStop()),hdAdpFan,SLOT(Slot_Action_FanStop()));
    connect(this,SIGNAL(Signal_Action_FanWindIn()), hdAdpFan,SLOT(Slot_Action_FanWindIn()));
    connect(this,SIGNAL(Signal_Action_FanWindOut()),hdAdpFan,SLOT(Slot_Action_FanWindOut()));
    connect(hdAdpFan,SIGNAL(Signal_SetState_FanError()),this,SLOT(Slot_SetState_FanError()));
    connect(hdAdpFan,SIGNAL(Signal_SetState_FanNoError()),this,SLOT(Slot_SetState_FanNoError()));
}

StateFan_T Fan::GetState_Fan()
{
    return this->mStateFan;
}

void Fan::SetState_FanStop()
{
    if(this->mStateFan != FanError && this->mStateFan != FanStop)
    {
        this->mStateFan = FanStop;
        emit Signal_Action_FanStop();
    }
}
void Fan::SetState_FanWindIn()
{
    if(this->mStateFan != FanError && this->mStateFan != FanWindIn)
    {
        this->mStateFan = FanWindIn;
        emit Signal_Action_FanWindIn();
    }
}
void Fan::SetState_FanWindOut()
{
    if(this->mStateFan != FanError  && this->mStateFan != FanWindOut)
    {
        this->mStateFan = FanWindOut;
        emit Signal_Action_FanWindOut();
    }
}
void Fan::SetState_FanError()
{
    if(this->mStateFan != FanError)
    {
        this->mStateFan = FanError;
        emit Signal_Action_FanStop();
    }
}
void Fan::SetState_FanNoError()
{
    if(this->mStateFan == FanError)
    {
        this->mStateFan = FanStop;
    }
}
void Fan::Slot_SetState_FanError()
{
    this->SetState_FanError();
}
void Fan::Slot_SetState_FanNoError()
{
    this->SetState_FanNoError();
}
