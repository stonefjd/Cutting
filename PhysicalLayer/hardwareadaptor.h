#ifndef HARDWAREADAPTOR_H
#define HARDWAREADAPTOR_H

#include <QObject>
#include <QDebug>
#include <QTimer>

#define GTSLIB 0

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

public slots:


private:

};

short ADP_GetLimit(short _index,long *_pPos,long *_pNeg);

void ADP_Connect();
void ADP_Reset();
void ADP_ClrSts(short axis, short count);
void ADP_LoadCfgFile(QString _path);
void ADP_Disconnect();
void ADP_GetLimitState(short _axis,bool _polar,bool *_state);

void ADP_SetFanStop();
void ADP_SetFanWindIn();
void ADP_SetFanWindOut();
bool ADP_GetFanErrorState();//0 no error, 1 error
#endif // HARDWAREADAPTOR_H
