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
D_CtrlMach* H_CtrlMach::GetCtrlMach()
{
    return &this->d_ctrlMach;
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
bool H_CtrlMach::GetAxisRunState(short _axis)
{
    return this->d_ctrlMach.GetAxisRunState(_axis);
}

void H_CtrlMach::SlotCtrlTask_10ms()
{
//    qDebug()<<"10ms";
    d_ctrlMach.StateMachScheduleMain();
    d_ctrlMach.GetRunningData();
//    emit UpdateDataHeadPosRt(*d_ctrlMach.GetPosRT());
}
//void H_CtrlMach::SlotUpdateDataHead(CfgHead_T _data)
//{
////    qDebug()<<"ctrl upadte data head In";
//    d_ctrlMach.SetPosOrg(_data.posOrg);
//    d_ctrlMach.SetPosLmt(_data.posLmt);
//    d_ctrlMach.SetPosMax(_data.posMax);
//    d_ctrlMach.SetPosToPulseScaleXY(_data.posToPulseScaleXY);
//    d_ctrlMach.SetIdleMoveSpd(_data.idleMoveSpd);
//    d_ctrlMach.SetIdleMoveAcc(_data.idleMoveAcc);
//}
void H_CtrlMach::SlotEnterOprtToolPosCalib(int _id, double _deep)
{
    //创建提示对象
    u_ctrlToolPosCalib = new U_CtrlToolPosCalib;
    //设置数据对象
    u_ctrlToolPosCalib->SetCtrlMachObj(&d_ctrlMach);
    //连接界面发出信号
    connect(u_ctrlToolPosCalib,  SIGNAL(keyPressed(QKeyEvent)),  this, SLOT(SlotActionKeyBoard(QKeyEvent)));
    connect(u_ctrlToolPosCalib,  SIGNAL(keyReleased(QKeyEvent)), this, SLOT(SlotActionKeyBoard(QKeyEvent)));
    //设置显示属性
    u_ctrlToolPosCalib->setModal(true);
    //初始化界面内容 并确定是否显示
    if(u_ctrlToolPosCalib->InitialModel(_id,_deep))
        u_ctrlToolPosCalib->exec();
    //显示
    delete u_ctrlToolPosCalib;
}
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
    d_ctrlMach.EventOprtSubEnter(id);
    if(id == 2)
    {
        u_ctrlRngRst = new U_CtrlRngRst;
        u_ctrlRngRst->SetCtrlMachObj(&this->d_ctrlMach);
        connect(u_ctrlRngRst,  SIGNAL(keyPressed(QKeyEvent)),  this, SLOT(SlotActionKeyBoard(QKeyEvent)));
        connect(u_ctrlRngRst,  SIGNAL(keyReleased(QKeyEvent)), this, SLOT(SlotActionKeyBoard(QKeyEvent)));

        u_ctrlRngRst->setModal(true);
        u_ctrlRngRst->exec();
    }
}
void H_CtrlMach::SlotUpdateDataHeadPosMaxRequest()
{
    emit UpdateDataHeadPosMax(*d_ctrlMach.GetPosMax());
}
