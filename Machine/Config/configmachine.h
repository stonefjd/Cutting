#ifndef CONFIGMACHINE_H
#define CONFIGMACHINE_H

#include <QWidget>
#include <QFile>
#include <QMessageBox>
#include <QSettings>
#include <QDebug>
#include "configinfo.h"

class ConfigMachine : public QWidget
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

    int     timeSwage;			//压料时间(s)
    int     timeBlow;            //吹气时间(s)
    int     timeLoadBefore;		//放料开始提前时间(s)
    int     timeLoadAfter;		//放料结束提前时间(s)
    int     timeInhaleDelay;		//吸气延迟时间(ms)

    int     machHeadCount;
public:

private:
public:
    explicit ConfigMachine(QWidget *parent = nullptr);
    void GetMachineBaseInfo();

    QString GetMachCfgPath();
//    void    SetMachRunMax(int _axis,double _pos);
//    double  GetMachRunMax(int _axis);
    int     GetMachHeadCount();
//    void    UpdateMachRunMax(int _xPos, int _yPos);

//    void    SetMachPulsePerMillimeter(int _axis,double _pos);
//    double  GetMachPulsePerMillimeter(int _axis);

    bool GetPrivateProfileString(QString strSect,QString strKey,QString *szBuf,QString strConfigPath);
    bool WritePrivateProfileString(QString strSect,QString strKey,QString strText,QString strConfigPath);

signals:

public slots:
};

#endif // CONFIGMACHINE_H
