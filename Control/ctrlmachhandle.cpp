#include "ctrlmachhandle.h"

//CtrlMachHandle::CtrlMachHandle(QObject *parent) : QObject(parent)
//{
//    ctrlMach_UI->SetCtrlMachObj(&this->ctrlMach);
//}
CtrlMachHandle::CtrlMachHandle(QDockWidget* _ctrlDockWgt)
{
    ctrlMach_UI->SetCtrlMachObj(&this->ctrlMach);
    ctrlMach_UI->InitialModel(_ctrlDockWgt);

    ctrlTimer=new QTimer(this);
    connect(ctrlTimer,SIGNAL(timeout()),this,SLOT(SlotCtrlTask_10ms()));
}
void CtrlMachHandle::StartCtrlTimer()
{
    //默认10ms
    ctrlTimer->start(10);
}
void CtrlMachHandle::StopCtrlTimer()
{
    ctrlTimer->stop();
}
MainState CtrlMachHandle::GetMachState()
{
    return this->ctrlMach.GetMainState();
}
bool CtrlMachHandle::GetAxisRunState(int _axis)
{
    return this->ctrlMach.GetAxisRunState(_axis);
}

void CtrlMachHandle::SlotCtrlTask_10ms()
{
//    qDebug()<<"10ms";
    ctrlMach.StateMachScheduleMain();
    ctrlMach.GetRunningData();
    emit UpdateHeadPosRt(ctrlMach.GetPosRT());
}
void CtrlMachHandle::SlotUpdateDataHead(CfgHead_T _data)
{
//    qDebug()<<"ctrl upadte data head In";
    ctrlMach.SetPosOrg(_data.posOrg);
    ctrlMach.SetPosLmt(_data.posLmt);
    ctrlMach.SetPosMax(_data.posMax);
    ctrlMach.SetPosToPulseScaleXY(_data.posToPulseScaleXY);
    ctrlMach.SetIdleMoveSpd(_data.idleMoveSpd);
    ctrlMach.SetIdleMoveAcc(_data.idleMoveAcc);
}
//void CtrlMachHandle::SlotKeyPressed(QKeyEvent event)
//{
//    ctrlMach.SetKeyState(event);
//}
//void CtrlMachHandle::SlotKeyReleased(QKeyEvent event)
//{
//    ctrlMach.SetKeyState(event);
//}
void CtrlMachHandle::SlotKeyAction(QKeyEvent event)
{
    ctrlMach.KeyActionEvent(event);
}
