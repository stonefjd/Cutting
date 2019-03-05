#include "statemachine.h"

#define TIMEOUT 10

StateMachine::StateMachine(QObject *parent) : QObject(parent)
{
    this->mStateMain = MPowerOn;
    this->timeId = this->startTimer(TIMEOUT);
}
void StateMachine::MainStateRunning()
{
    //--------MselfTest
    if(this->mStateMain == MPowerOn)//source state
    {
        if(1)
        {
            this->mStateMain = MWait;//dirction state
            LeaveStateCallBack_MPowerOn();
        }
    }
}


void StateMachine::LeaveStateCallBack_MPowerOn()
{

}
void StateMachine::timerEvent(QTimerEvent *event)
{
    if(this->timeId == event->timerId())
    {
        MainStateRunning();
        qDebug()<<event->timerId();
    }
}
