#ifndef FAN_H
#define FAN_H

#include <QObject>
#include "PhysicalLayer/hardwareadaptor.h"
enum StateFan_T {
    FanStop     = 0x0000,
    FanWindIn   = 0x0001,   //power on test,check everything.
    FanWindOut  = 0x0002,   //wait for all device OK,if not ok display it.
    FanError = 0x0003,
};
struct FanSpeed_T
{
    double windPos;
    double windNeg;
};

class Fan : public QObject
{
    Q_OBJECT
private:
    StateFan_T mStateFan;
    void SetState_FanError();
    void SetState_FanNoError();
public:
    explicit Fan(QObject *parent = nullptr);

    StateFan_T GetState_Fan();
    void SetState_FanStop();
    void SetState_FanWindIn();
    void SetState_FanWindOut();


signals:
    void Signal_Action_FanStop();
    void Signal_Action_FanWindIn();
    void Signal_Action_FanWindOut();
public slots:
    void Slot_SetState_FanError();
    void Slot_SetState_FanNoError();
};

#endif // FAN_H
