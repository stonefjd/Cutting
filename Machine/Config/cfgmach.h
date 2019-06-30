#ifndef CFGMACH_H
#define CFGMACH_H

#include "cfgbasedefine.h"

class CfgMach
{
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

    bool   alignEn;
    double alignMaxZ;
    double alignStartZ;
    double alignAbsX;
    double alignAbsY;

    int headCount;
public:


public:
    CfgMach();
    void GetMachineBaseInfo();

    QString GetMachCfgPath();
    int     GetHeadCount();
//--------mach parm
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
//--------mach settings param
    bool GetEffctLvLimit();
    bool GetEffctLvSwage();
    bool GetEffctLvPuase();
    bool GetEffctLvPump();
    bool GetEnFanZone();
    bool GetEnInhal();
    bool GetEnBlow();
    int GetFreqInhale();
    int GetFreqBlow();
    int GetTimeSwage();
    int GetTimeBlow();
    int GetTimeLoadBefore();
    int GetTimeLoadAfter();
    int GetTimeInhaleDelay();

    void SetEffctLvLimit(bool);
    void SetEffctLvSwage(bool);
    void SetEffctLvPuase(bool);
    void SetEffctLvPump(bool);
    void SetEnFanZone(bool);
    void SetEnInhal(bool);
    void SetEnBlow(bool);
    void SetFreqInhale(int);
    void SetFreqBlow(int);
    void SetTimeSwage(int);
    void SetTimeBlow(int);
    void SetTimeLoadBefore(int);
    void SetTimeLoadAfter(int);
    void SetTimeInhaleDelay(int);
//----align
    bool   GetAlignEn();
    double GetAlignMaxZ();
    double GetAlignStartZ();
    double GetAlignAbsX();
    double GetAlignAbsY();

    void SetAlignEn(bool);
    void SetAlignMaxZ(double);
    void SetAlignStartZ(double);
    void SetAlignAbsX(double);
    void SetAlignAbsY(double);
};

#endif // CFGMACH_H
