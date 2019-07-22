#ifndef H_CTRLMACH_H
#define H_CTRLMACH_H

#include <QObject>

#include "u_ctrlbtndir.h"
#include "u_ctrlrngrst.h"
#include "u_ctrltoolposcalib.h"
class H_CtrlMach : public QObject
{
    Q_OBJECT
private:
//--系统状态机定时器
    QTimer *ctrlTimer = new QTimer;
//--控制界面和控制对象
    D_CtrlMach          d_ctrlMach;
    U_CtrlBtnDir        *u_ctrlBtnDir = new U_CtrlBtnDir;
    U_CtrlRngRst        *u_ctrlRngRst;
    U_CtrlToolPosCalib  *u_ctrlToolPosCalib;
public:
//    explicit H_CtrlMach(QObject *parent = nullptr);
    H_CtrlMach(QDockWidget* _ctrlDockWgt);

    D_CtrlMach* GetCtrlMach();
    void StartCtrlTimer();
    void StopCtrlTimer();

    //获取控制对象的状态
    MainState GetMachState();
    bool GetAxisRunState(short _axis);
signals:
    //更新实时机头坐标
//    void UpdateDataHeadPosRt(QPointF posRT);
//    void UpdateDataHeadPosMax(QPointF posRT);
private slots:
    void SlotCtrlTask_10ms();
public slots:
    void SlotEnterOprtToolPosCalib(int _id);
    void SlotActionKeyBoard(QKeyEvent event);
    void SlotActionOprt();
//    void SlotUpdateDataHeadPosMaxRequest();
};

#endif // H_CTRLMACH_H
