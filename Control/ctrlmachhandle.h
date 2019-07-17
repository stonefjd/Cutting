#ifndef CTRLMACHHANDLE_H
#define CTRLMACHHANDLE_H

#include <QObject>

#include "Machine/Config/cfgmachhandle.h"
#include "ctrlmach_ui.h"
class CtrlMachHandle : public QObject
{
    Q_OBJECT
private:
//--系统状态机定时器
    QTimer *ctrlTimer = new QTimer;
//--控制界面和控制对象
    CtrlMach_UI *ctrlMach_UI = new CtrlMach_UI;
    CtrlMach    ctrlMach;
public:
//    explicit CtrlMachHandle(QObject *parent = nullptr);
    CtrlMachHandle(QDockWidget* _ctrlDockWgt);
    void StartCtrlTimer();
    void StopCtrlTimer();

    //获取控制对象的状态
    MainState GetMachState();
    bool GetAxisRunState(int _axis);
signals:
    //更新实时机头坐标
    void UpdateHeadPosRt(QPointF posRT);
private slots:
    void SlotCtrlTask_10ms();
public slots:
    void SlotUpdateDataHead(CfgHead_T _data);
//    void SlotKeyPressed(QKeyEvent event);
//    void SlotKeyReleased(QKeyEvent event);
    void SlotKeyAction(QKeyEvent event);
};

#endif // CTRLMACHHANDLE_H
