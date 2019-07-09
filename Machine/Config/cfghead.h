﻿#ifndef CFGHEAD_H
#define CFGHEAD_H

#include <QObject>

#include "cfgapron.h"
#include "cfgbasedefine.h"
class CfgHead
{
public:
     CfgHead();

public:
    void GetHeadInfo();
    QString GetHeadCfgPath();

    void UpdateHeadMaxPluse(int _xPluse,int _yPluse,int _hIndex);
    void UpdateHeadCutLimit(int _xPluse,int _yPluse,int _hIndex);

private:
    QString headCfgPath;
    int headIndex;

    double feedLen;     //送料长度
    double feedSpd;     //送料速度(m/s)
    double feedAcc;     //送料加速度(m/s²)
//    QStringList apronIndexList;


public:
    QPointF *posOrg     = new QPointF;      //红色激光点
    QPointF *posLimit   = new QPointF;      //区域限位，人为设定尺寸
    QPointF *posMax     = new QPointF;      //最大实际长度，毫米
    QPointF *pulseMax   = new QPointF;      //行走的最大脉冲数,取决于限位开关,目前等价于机械极限尺寸
    QPointF *posToPulseScale    = new QPointF; //脉冲每毫米
    QPointF *realToCutScale     = new QPointF;  //实际尺寸与切割尺寸的比值
//    QList<CfgApron*> aConfig;
    double *idleMoveSpd = new double;		//空走速度 (m/s)
    double *idleMoveAcc = new double;     //空走加速度(G)
public:
    QPointF *GetPosOrg();
    QPointF *GetPosLmt();
    QPointF *GetPosMax();
    QPointF *GetPosToPulseScale();
    QPointF *GetPulseMax();
    QPointF *GetRealToCutScale();
    double  *GetIdleMoveSpd();
    double  *GetIdleMoveAcc();
    double  GetFeedLen();
    double  GetFeedSpd();
    double  GetFeedAcc();

    void SetPosOrg(QPointF);
    void SetPosLmt(QPointF);
    void SetPosMax(QPointF);
    void SetPosToPulseScale(QPointF);
    void SetPulseMax(QPointF);
    void SetRealToCutScale(QPointF);
    void SetIdleMoveSpd(double);
    void SetIdleMoveAcc(double);
    void SetFeedLen(double);
    void SetFeedSpd(double);
    void SetFeedAcc(double);

//    void SetApronIndexList(QStringList _list);
//    QStringList GetApronIndexList(void);
};

#endif // CFGHEAD_H
