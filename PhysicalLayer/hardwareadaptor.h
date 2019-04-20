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
void ADP_AxisOn(short _axis);
void ADP_ZeroPos(short _axis);
void ADP_ClrSts(short axis, short count);
void ADP_GetSts(short axis, long *pSts);
void ADP_LoadCfgFile(QString _path);
void ADP_Disconnect();
bool ADP_GetAxisMotorEnState(short _axis);
bool ADP_GetAxisPlanRunState(short _axis);
void ADP_Update(short _axis);
void ADP_GetLimitState(short _axis,bool _polar,bool *_state);
void ADP_PrfJog(short _profile);
void ADP_SetJogPrm(short _profile,TJogPrm *_pPrm);
void ADP_SetVel(short _profile,double _vel);
void ADP_SetPrfPos(short _profile,long _prfPos);
void ADP_SetCrdPrm(short _crd,TCrdPrm *_pCrdPrm);
void ADP_CrdClear(short _crd,short _fifo);
void ADP_LnXY(short crd,long x,long y,double synVel,double synAcc,double velEnd,short fifo);
void ADP_CrdStart(short _mask,short _option);
void ADP_Stop(long _mask,long _option);

void ADP_SetFanStop();
void ADP_SetFanWindIn();
void ADP_SetFanWindOut();
bool ADP_GetFanErrorState();//0 no error, 1 error
#endif // HARDWAREADAPTOR_H
