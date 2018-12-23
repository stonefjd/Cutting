#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <QObject>
#include <QTimerEvent>
#include <QDebug>

enum MStateMain_T {
    MPowerOn    = 0x0000,
    MSelfTest   = 0x0001,   //power on test,check everything.
    MWait       = 0x0002,   //wait for all device OK,if not ok display it.
    MInitial    = 0x0003,   //run to the Mechanical limit zero point for the all axes correction.
    MOperate    = 0x0004,   //moving the tool in 2 axis.
    MStop       = 0x0005,   //
    MRunning    = 0x0006,
    MPause      = 0x0007,
    MErrorOccur = 0x0008,
};
class StateMachine : public QObject
{
    Q_OBJECT
private:
    MStateMain_T mStateMain;
    int timeId;
public:
    explicit StateMachine(QObject *parent = nullptr);

    //override functions
    void timerEvent(QTimerEvent *event);

    //own functions
    void MainStateRunning();
    void LeaveStateCallBack_MPowerOn();
    void LeaveStateCallBack_MSelfTest();
    void LeaveStateCallBack_MWait();
signals:
    void LeaveStateCallBack_MPowerOnToMainWindow();

public slots:


};

#endif // STATEMACHINE_H
