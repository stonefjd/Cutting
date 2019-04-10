#ifndef FAN_H
#define FAN_H

#include <QObject>
#include "PhysicalLayer/hardwareadaptor.h"

#define FanStop      0x0000
#define FanWindIn    0x0001   //power on test,check everything.
#define FanWindOut   0x0002   //wait for all device OK,if not ok display it.
#define FanError     0x0003


class Fan : public QObject
{
    Q_OBJECT
private:
    uint8_t Fan_stMachine;
public:
    uint8_t Fan_GetState();
    void Fan_SetNormalState(uint8_t _state);
    void Fan_DiagErrorState();
    void Fan_ClrErrorState();
public:
    explicit Fan(QObject *parent = nullptr);

signals:
public slots:

};

#endif // FAN_H
