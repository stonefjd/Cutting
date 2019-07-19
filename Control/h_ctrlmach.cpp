#include "h_ctrlmach.h"

//H_CtrlMach::H_CtrlMach(QObject *parent) : QObject(parent)
//{

//}
H_CtrlMach::H_CtrlMach(QDockWidget* _ctrlDockWgt)
{
    u_ctrlBtnDir->SetCtrlMachObj(&this->d_ctrlMach);
    u_ctrlBtnDir->InitialModel(_ctrlDockWgt);

    ctrlTimer=new QTimer(this);
    connect(ctrlTimer,SIGNAL(timeout()),this,SLOT(SlotCtrlTask_10ms()));
    connect(&d_ctrlMach,SIGNAL(UpdateDataHeadPosMaxRequest()),this,SLOT(SlotUpdateDataHeadPosMaxRequest()));
}
void H_CtrlMach::StartCtrlTimer()
{
    //默认10ms
    ctrlTimer->start(10);
}
void H_CtrlMach::StopCtrlTimer()
{
    ctrlTimer->stop();
}
MainState H_CtrlMach::GetMachState()
{
    return this->d_ctrlMach.GetMainState();
}
bool H_CtrlMach::GetAxisRunState(int _axis)
{
    return this->d_ctrlMach.GetAxisRunState(_axis);
}

void H_CtrlMach::SlotCtrlTask_10ms()
{
//    qDebug()<<"10ms";
    d_ctrlMach.StateMachScheduleMain();
    d_ctrlMach.GetRunningData();
    emit UpdateDataHeadPosRt(d_ctrlMach.GetPosRT());
}
void H_CtrlMach::SlotUpdateDataHead(CfgHead_T _data)
{
//    qDebug()<<"ctrl upadte data head In";
    d_ctrlMach.SetPosOrg(_data.posOrg);
    d_ctrlMach.SetPosLmt(_data.posLmt);
    d_ctrlMach.SetPosMax(_data.posMax);
    d_ctrlMach.SetPosToPulseScaleXY(_data.posToPulseScaleXY);
    d_ctrlMach.SetIdleMoveSpd(_data.idleMoveSpd);
    d_ctrlMach.SetIdleMoveAcc(_data.idleMoveAcc);
}
//void CtrlMachHandle::SlotKeyPressed(QKeyEvent event)
//{
//    ctrlMach.SetKeyState(event);
//}
//void CtrlMachHandle::SlotKeyReleased(QKeyEvent event)
//{
//    ctrlMach.SetKeyState(event);
//}
void H_CtrlMach::SlotActionKeyBoard(QKeyEvent event)
{
    d_ctrlMach.EventActionKey(event);
}
void H_CtrlMach::SlotActionOprt()
{
    int id;
    QObject *act = qobject_cast<QObject*>(sender());
    id = act->property("id").toInt();
    qDebug()<<id;
    d_ctrlMach.EventActionButton(id);
    if(id == 2)
    {
        u_ctrlRngRst = new U_CtrlRngRst;
        u_ctrlRngRst->SetCtrlMachObj(&this->d_ctrlMach);
        connect(u_ctrlRngRst,  SIGNAL(keyPressed(QKeyEvent)),  this, SLOT(SlotActionKeyBoard(QKeyEvent)));
        connect(u_ctrlRngRst,  SIGNAL(keyReleased(QKeyEvent)), this, SLOT(SlotActionKeyBoard(QKeyEvent)));//----Machine Init

        u_ctrlRngRst->setModal(true);
        u_ctrlRngRst->exec();
    }
}
void H_CtrlMach::SlotUpdateDataHeadPosMaxRequest()
{
    emit UpdateDataHeadPosMax(d_ctrlMach.GetPosMax());
}
