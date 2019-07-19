#ifndef HARDWAREADAPTOR_H
#define HARDWAREADAPTOR_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QPointF>
#define GOOGOL_PLUSE_4AXIS
#ifdef GOOGOL_PLUSE_4AXIS
    #include <PhysicalLayer/gts.h>
    const int AXIS_NULL  = 0;
    const int AXIS_FIRST = 1;
    const int AXIS_MAX   = 4;
    const int AXIS_X=1;
    const int AXIS_Y=2;
    const int AXIS_Z1=3;
    const int AXIS_A1=4;
#endif

#ifdef GOOGOL_PLUSE_8AXIS
    const int AXIS_X=1;
    const int AXIS_Y=2;
    const int AXIS_Z1=3;
    const int AXIS_A1=4;
    const int AXIS_Z2=5;
    const int AXIS_A2=6;
#endif

#ifdef  LEADSHINE
#endif

#ifdef  ADLINK_ETH
#endif

#ifdef INOVANCE_ETH
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
void ADP_ClrSts(short axis, short count = 1);
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
void ADP_LnXY(short crd,long x,long y,double synVel,double synAcc,double velEnd,short fifo = 0);
void ADP_BufMove(short crd,short moveAxis,long pos,double vel,double acc,short modal,short fifo=0);
void ADP_CrdStart(short _mask,short _option);
void ADP_Stop(long _mask,long _option);
void ADP_GetAxisPrfPos(short _axis,double *_pValue);

void ADP_InitData();
void ADP_InitBoard(QString _path);
void ADP_EnableAllAxis();
void ADP_DisableALLAxis();
void ADP_ZeroPosALl();
void ADP_GetGpi(long *_diValue);
void ADP_SetGpo(long _doValue);
void ADP_StartHome();
void ADP_StopHome();
void ADP_StartHomeAxis(short _axis);
void ADP_StopHomeAxis(short _axis);
void ADP_StartMovePoint(short _crd, short _fifo, long _xPos, long _yPos, double spd, double acc, TCrdPrm crdPrm);
void ADP_GetRunStateAndSegment(short _crd,short *_pRun,long *_pSegment,short _fifo=0);
void ADP_GetHeadPosRt(QPointF *_posRt,double _ppm);
bool ADP_GetAxisRunState(short _axis);
void ADP_SetJogMode(short _axis,double _spd,double _acc,double _smooth);


void ADP_SetFanStop();
void ADP_SetFanWindIn();
void ADP_SetFanWindOut();
bool ADP_GetFanErrorState();//0 no error, 1 error
#endif // HARDWAREADAPTOR_H
