﻿#ifndef HARDWAREADAPTOR_H
#define HARDWAREADAPTOR_H

#include <QObject>
#include <QDebug>
#include <QTimer>

class HardwareAdaptor : public QObject
{
    Q_OBJECT
private:

public:
    explicit HardwareAdaptor(QObject *parent = nullptr);

signals:
    void Signal_SetState_FanError();
    void Signal_SetState_FanNoError();
public slots:
    void Slot_Action_CheckHardWareError();

    void Slot_Action_FanStop();
    void Slot_Action_FanWindIn();
    void Slot_Action_FanWindOut();
};

#endif // HARDWAREADAPTOR_H
