#ifndef CFGHEAD_H
#define CFGHEAD_H

#include <QWidget>
#include <QSettings>
#include <QFile>
#include <QMessageBox>
#include "configapron.h"
class CfgHead : public QWidget
{
    Q_OBJECT
public:
    explicit CfgHead(QWidget *parent = nullptr);

signals:
public:
    void GetHeadInfo(int _index);
    QString GetHeadCfgPath();

    void UpdateHeadMaxPluse(int _xPluse,int _yPluse,int _hIndex);
    void UpdateHeadCutLimit(int _xPluse,int _yPluse,int _hIndex);
    bool GetPrivateProfileString(QString strSect,QString strKey,QString *szBuf,QString strConfigPath);
    bool WritePrivateProfileString(QString strSect,QString strKey,QString strText,QString strConfigPath);

private:
    QString headCfgPath;
    int headIndex;

    double feedLen;     //送料长度
    double feedSpd;     //送料速度(m/s)
    double feedAcc;     //送料加速度(m/s²)
    QStringList apronIndexList;

public:
    QPointF posOrg;//红色激光点
    QPointF posLimit;  //区域限位，人为设定尺寸
    QPointF posMax;//最大实际长度，毫米
    QPointF posToPulseScale;//脉冲每毫米
    QPointF pulseMax;//行走的最大脉冲数,取决于限位开关,目前等价于机械极限尺寸
    QPointF realToCutScale;
    QList<configApron*> aConfig;
    double idleMoveSpd;		//空走速度 (m/s)
    double idleMoveAcc;     //空走加速度(G)
public:
    QPointF GetPosOrg();
    QPointF GetPosLimit();
    QPointF GetPosMax();
    QPointF GetPosToPulseScale();
    QPointF GetPulseMax();
    QPointF GetRealToCutScale();
    double  GetIdleMoveSpd();
    double  GetIdleMoveAcc();
    double  GetFeedLen();
    double  GetFeedSpd();
    double  GetFeedAcc();

    void SetPosOrg(QPointF);
    void SetPosLimit(QPointF);
    void SetPosMax(QPointF);
    void SetPosToPulseScale(QPointF);
    void SetPulseMax(QPointF);
    void SetRealToCutScale(QPointF);
    void SetIdleMoveSpd(double);
    void SetIdleMoveAcc(double);
    void SetFeedLen(double);
    void SetFeedSpd(double);
    void SetFeedAcc(double);

public slots:
};

#endif // CFGHEAD_H
