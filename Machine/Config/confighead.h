#ifndef CONFIGHEAD_H
#define CONFIGHEAD_H

#include <QWidget>
#include <QSettings>
#include <QFile>
#include <QMessageBox>

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
    void UpdateHeadCutRange();
    bool GetPrivateProfileString(QString strSect,QString strKey,QString *szBuf,QString strConfigPath);
    bool WritePrivateProfileString(QString strSect,QString strKey,QString strText,QString strConfigPath);

private:
    QString headCfgPath;
    int headIndex;

    double  headMaxLengthX;
    double  headMaxLengthY;

    double cameraOffsetX;		//摄像头 X偏移
    double cameraOffsetY;		//摄像头 Y偏移
    double cameraHeight;		//摄像头 高度

    double feedLen;     //送料长度
    double feedSpd;     //送料速度(m/s)
    double feedAcc;     //送料加速度(m/s²)

    double moveSpd;		//空走速度 (m/s)
    double moveAcc;     //空走加速度(G)
public:
    QPoint  headOrg;//红色激光点
    QPoint  headPos;//当前位置
    QPointF headPluseScale;//脉冲每毫米
    QPoint  headMaxPluse;//行走的最大脉冲数,取决于限位开关,目前等价于机械极限尺寸
    QPoint  headCutLimit;  //区域限位，人为设定尺寸
    QRect   headCutRect;




public slots:
};

#endif // CONFIGHEAD_H
