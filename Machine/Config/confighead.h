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
    void GetMachineInfo();

    bool GetPrivateProfileString(QString strSect,QString strKey,QString *szBuf,QString strConfigPath);
    bool WritePrivateProfileString(QString strSect,QString strKey,QString strText,QString strConfigPath);

private:
    QString headCfgPath;
    int headIndex;
    double headOrgX;//红色激光点
    double headOrgY;

    double headPosX;//当前位置
    double headPosY;

    double headMaxPluseX;//行走的最大脉冲数,取决于限位开关,目前等价于机械极限尺寸
    double headMaxPluseY;

    double headPluseScaleX;//脉冲每毫米
    double headPluseScaleY;

    double headMaxLengthX;
    double headMaxLengthY;

    double headCutLimitX;//区域限位，人为设定尺寸
    double headCutLimitY;

    double penOffsetX;//笔偏移
    double penOffsetY;

    double glowOffsetX;//灼烧激光偏移
    double glowOffsetY;

    double cameraOffsetX;		//摄像头 X偏移
    double cameraOffsetY;		//摄像头 Y偏移

    short  cuttingMode;			//切割模式
    short  decoupleMode;		//减震模式

    double feedLen;				//送料长度
    double feedSpeed;			//送料速度(m/s)
    double swagingTime;			//压料时间(s)
    double swagingTime1;		//吹气时间(s)
    double swagingTime2;		//放料开始提前时间(s)
    double swagingTime3;		//放料结束提前时间(s)
    double m_dbInhaleDelayTime;		//吸气延迟时间(ms)
    double m_dbReducerEdge;			//减速边界

    double m_dbScanLen;				//扫描长度
    double m_dbScanSpeed;			//扫描速度(m/s)
    double m_dbScanAcceleration;	//扫描加速度(G)

    double m_dbIdleMoveSpeed;		//空走速度 (m/s)
    double m_dbIdleMoveAcceleration;//空走加速度(G)
public slots:
};

#endif // CONFIGHEAD_H
