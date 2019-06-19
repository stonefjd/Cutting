#ifndef CFGMACH_H
#define CFGMACH_H

#include <QWidget>
#include <QFile>
#include <QMessageBox>
#include <QSettings>
#include <QDebug>
#include "configinfo.h"

class CfgMach : public QWidget
{
    Q_OBJECT
private:
    QString machCfgPath;

    QString versionHw;
    QString versionSw;
    double  machType;
//    double  machTypeSub;
    double  sizeX;
    double  sizeY;
    double  feltThick;

    bool effctLvLimit;
    bool effctLvSwage;
    bool effctLvPuase;
    bool effctLvPump;

    bool enFanZone;
    bool enInhal;
    bool enBlow;
    int freqInhale;
    int freqBlow;

    int timeSwage;			//压料时间(s)
    int timeBlow;            //吹气时间(s)
    int timeLoadBefore;		//放料开始提前时间(s)
    int timeLoadAfter;		//放料结束提前时间(s)
    int timeInhaleDelay;		//吸气延迟时间(ms)

    int machHeadCount;
public:

private:
public:
    explicit CfgMach(QWidget *parent = nullptr);
    void GetMachineBaseInfo();

    QString GetMachCfgPath();
    int     GetMachHeadCount();

    QString GetVersionHw();
    QString GetVersionSw();
    double  GetType();
    double  GetSizeX();
    double  GetSizeY();
    double  GetFeltThick();

    void SetVersionHw(QString);
    void SetVersionSw(QString);
    void SetType(double);
    void SetSizeX(double);
    void SetSizeY(double);
    void SetFeltThick(double);


    bool GetPrivateProfileString(QString strSect,QString strKey,QString *szBuf,QString strConfigPath);
    bool WritePrivateProfileString(QString strSect,QString strKey,QString strText,QString strConfigPath);

signals:

public slots:
};

#endif // CFGMACH_H
