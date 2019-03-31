#ifndef HARDWAREADAPTOR_H
#define HARDWAREADAPTOR_H

#include <QObject>
#include <QDebug>
#include <QTimer>

#define GTSLIB 1

#ifdef GTSLIB
    #include <PhysicalLayer/gts.h>
#endif

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

private:

};

short ADP_GetLimit(short _index,long *_pPos,long *_pNeg);

void ADP_Connect();
void ADP_Reset();
void ADP_ClrSts(short axis, short count);
void ADP_LoadCfgFile(QString _path);
void ADP_Disconnect();
void ADP_GetLimitState(short _axis,bool _polar,bool *_state);
#endif // HARDWAREADAPTOR_H
