#include "fan.h"

Fan::Fan(QObject *parent) : QObject(parent)
{
    Fan_stMachine = FanStop;
}
uint8_t Fan::Fan_GetState(void)
{
    return Fan_stMachine;
}
void Fan::Fan_SetNormalState(uint8_t _state)
{
    if(Fan_stMachine!= FanError)
    {
        switch(_state)
        {
            case FanStop:
            {
                if(Fan_stMachine != FanStop)
                {
                    Fan_stMachine = FanStop;
                    ADP_SetFanStop();
                }
                break;
            }
            case FanWindIn:
            {
                if(Fan_stMachine != FanWindIn)
                {
                    Fan_stMachine = FanWindIn;
                    ADP_SetFanWindIn();
                }
                break;
            }
            case FanWindOut:
            {
                if(Fan_stMachine != FanWindOut)
                {
                    Fan_stMachine = FanWindOut;
                    ADP_SetFanWindOut();
                }
                break;
            }
        }
    }
}
void Fan::Fan_DiagErrorState()
{
    if(ADP_GetFanErrorState() != false)
        Fan_stMachine = FanError;
}
void Fan::Fan_ClrErrorState()
{
    if(ADP_GetFanErrorState() != true)
        Fan_stMachine = FanStop;
}
//StateFan_T Fan::GetState_Fan()
//{
//    return this->mStateFan;
//}

//void Fan::SetState_FanStop()
//{
//    if(this->mStateFan != FanError && this->mStateFan != FanStop)
//    {
//        this->mStateFan = FanStop;
//        emit Signal_Action_FanStop();
//    }
//}
//void Fan::SetState_FanWindIn()
//{
//    if(this->mStateFan != FanError && this->mStateFan != FanWindIn)
//    {
//        this->mStateFan = FanWindIn;
//        emit Signal_Action_FanWindIn();
//    }
//}
//void Fan::SetState_FanWindOut()
//{
//    if(this->mStateFan != FanError  && this->mStateFan != FanWindOut)
//    {
//        this->mStateFan = FanWindOut;
//        emit Signal_Action_FanWindOut();
//    }
//}
//void Fan::SetState_FanError()
//{
//    if(this->mStateFan != FanError)
//    {
//        this->mStateFan = FanError;
//        emit Signal_Action_FanStop();
//    }
//}
//void Fan::SetState_FanNoError()
//{
//    if(this->mStateFan == FanError)
//    {
//        this->mStateFan = FanStop;
//    }
//}
//void Fan::Slot_SetState_FanError()
//{
//    this->SetState_FanError();
//}
//void Fan::Slot_SetState_FanNoError()
//{
//    this->SetState_FanNoError();
//}
