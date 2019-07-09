#include "cfgmach.h"


CfgMach::CfgMach()
{
    machCfgPath = SETTING_PATH;

    versionHw   = "1";
    versionSw   = "1";
    machType    = 0;
//    double  machTypeSub;

    sizeX       = 2500;
    sizeY       = 1600;
    feltThick   = 3;

    effctLvLimit = 0;
    effctLvSwage = 0;
    effctLvPuase = 0;
    effctLvPump  = 0;

    enFanZone   = 0;
    enInhal     = 0;
    enBlow      = 0;
    freqInhale  = 5000;
    freqBlow    = 5000;

    timeSwage   = 200;			//压料时间(s)
    timeBlow    = 200;          //吹气时间(s)
    timeLoadBefore  = 200;		//放料开始提前时间(s)
    timeLoadAfter   = 200;		//放料结束提前时间(s)
    timeInhaleDelay = 200;		//吸气延迟时间(ms)

    alignEn     = 0;
    alignMaxZ   = 10;
    alignStartZ = 10;
    alignAbsX   = 100;
    alignAbsY   = 100;

    headCount   = 100;
}
QString CfgMach::GetMachCfgPath()
{
    return machCfgPath;
}
int CfgMach::GetHeadCount()
{
    return headCount;
}
QString CfgMach::GetVersionHw()
{
    return versionHw;
}
QString CfgMach::GetVersionSw()
{
    return versionSw;
}
double  CfgMach::GetType()
{
    return machType;
}
double  CfgMach::GetSizeX()
{
    return sizeX;
}
double  CfgMach::GetSizeY()
{
    return sizeY;
}
double  CfgMach::GetFeltThick()
{
    return feltThick;
}
bool CfgMach::GetEffctLvLimit()
{
    return effctLvLimit;
}
bool CfgMach::GetEffctLvSwage()
{
    return effctLvSwage;
}
bool CfgMach::GetEffctLvPuase()
{
    return effctLvPuase;
}
bool CfgMach::GetEffctLvPump()
{
    return effctLvPump;
}
bool CfgMach::GetEnFanZone()
{
    return enFanZone;
}
bool CfgMach::GetEnInhal()
{
    return enInhal;
}
bool CfgMach::GetEnBlow()
{
    return enBlow;
}
int CfgMach::GetFreqInhale()
{
    return freqInhale;
}
int CfgMach::GetFreqBlow()
{
    return freqBlow;
}
int CfgMach::GetTimeSwage()
{
    return timeSwage;
}
int CfgMach::GetTimeBlow()
{
    return timeBlow;
}
int CfgMach::GetTimeLoadBefore()
{
    return timeLoadBefore;
}
int CfgMach::GetTimeLoadAfter()
{
    return timeLoadAfter;
}
int CfgMach::GetTimeInhaleDelay()
{
    return timeInhaleDelay;
}
bool CfgMach::GetAlignEn()
{
    return alignEn;
}
double CfgMach::GetAlignMaxZ()
{
    return alignMaxZ;
}
double CfgMach::GetAlignStartZ()
{
    return alignStartZ;
}
double CfgMach::GetAlignAbsX()
{
    return alignAbsX;
}
double CfgMach::GetAlignAbsY()
{
    return alignAbsY;
}
void CfgMach::GetMachineBaseInfo()
{
    QString strConfigPath = machCfgPath;

    QString strSect = ("");
    QString strKey = ("");
    QString strText = ("");
    QString strDefault = ("");
    QString sInfo = "";

    QString *szBuf = new QString;
//------------------机械信息
    //硬件版本号
    strSect = ("MachInfo");
    strKey = ("HwVersion");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        versionHw = *szBuf;
    }
    //软版本号
    strKey = ("SwVersion");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        versionSw = *szBuf;
    }
    //机器类型
    strKey = ("Type");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        machType = (*szBuf).toInt();
    }
    //机器长宽度
    strKey = ("SizeX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        sizeX = (*szBuf).toDouble();
    }
    strKey = ("SizeY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        sizeY = (*szBuf).toDouble();
    }
    //毛毡厚度
    strKey = ("FeltThick");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        feltThick = (*szBuf).toDouble();
    }
//--------------------------机械配置
    //机头个数
    strSect = ("MachSet");
    strKey = ("HeadCount");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        headCount = (*szBuf).toInt();
    }
    strKey = ("EffctLvLimit");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        effctLvLimit = (*szBuf).toInt();
    }
    strKey = ("EffctLvSwage");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        effctLvSwage = (*szBuf).toInt();
    }
    strKey = ("EffctLvPuase");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        effctLvPuase = (*szBuf).toInt();
    }
    strKey = ("EffctLvPump");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        effctLvPump = (*szBuf).toInt();
    }
    strKey = ("EnFanZone");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        enFanZone = (*szBuf).toInt();
    }
    strKey = ("EnInhale");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        enInhal = (*szBuf).toInt();
    }
    strKey = ("EnBlow");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        enBlow = (*szBuf).toInt();
    }
    strKey = ("FreqInhale");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        freqInhale = (*szBuf).toInt();
    }
    strKey = ("FreqBlow");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        freqBlow = (*szBuf).toInt();
    }
  //----------------------风机
    //压料时间
    strKey = ("TimeSwage");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        timeSwage = (*szBuf).toInt();
    }
    //吹气时间(s)
    strKey = ("TimeBlow");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        timeBlow = (*szBuf).toInt();
    }
    //放料开始提前时间(s)
    strKey = ("TimeLoadBefore");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        timeLoadBefore = (*szBuf).toInt();
    }
    //放料结束提前时间(s)
    strKey = ("TimeLoadAfter");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        timeLoadAfter = (*szBuf).toInt();
    }
    //吸气延迟时间(ms)
    strKey = ("TimeInhaleDelay");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        timeInhaleDelay = (*szBuf).toInt();
    }
  //----------------------对刀
    strKey = ("AlignEn");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        alignEn = (*szBuf).toInt();
    }
    strKey = ("AlignMaxZ");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        alignMaxZ = (*szBuf).toDouble();
    }
    strKey = ("AlignStartZ");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        alignStartZ = (*szBuf).toDouble();
    }
    strKey = ("AlignAbsX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        alignAbsX = (*szBuf).toDouble();
    }
    strKey = ("AlignAbsY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        alignAbsY = (*szBuf).toDouble();
    }
}
