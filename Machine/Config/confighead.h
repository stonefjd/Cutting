#ifndef CONFIGHEAD_H
#define CONFIGHEAD_H

#include <QWidget>
#include <QSettings>
#include <QFile>
#include <QMessageBox>
#include "configapron.h"
class ConfigHead : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigHead(QWidget *parent = nullptr);

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

    double idleMoveSpd;		//空走速度 (m/s)
    double idleMoveAcc;     //空走加速度(G)
    QStringList apronIndexList;

public:
    QPointF headOrg;//红色激光点
    QPointF headPos;//当前位置
    QPointF headPluseScale;//脉冲每毫米
    QPointF headMaxPluse;//行走的最大脉冲数,取决于限位开关,目前等价于机械极限尺寸
    QPointF headMaxLength;//最大实际长度，毫米
    QPointF headLimit;  //区域限位，人为设定尺寸
    QPointF headCutScale;
    QList<configApron*> aConfig;


public slots:
};

#endif // CONFIGHEAD_H
