#include "cfgmach.h"


CfgMach::CfgMach()
{
    cfgMachData.cfgPath = SETTING_PATH;

    cfgMachData.versionHw   = "1";
    cfgMachData.versionSw   = "1";
    cfgMachData.machType    = 0;
//    double  machTypeSub;

    cfgMachData.sizeX       = 2500;
    cfgMachData.sizeY       = 1600;
    cfgMachData.feltThick   = 3;

    cfgMachData.effctLvLimit = 0;
    cfgMachData.effctLvSwage = 0;
    cfgMachData.effctLvPuase = 0;
    cfgMachData.effctLvPump  = 0;

    cfgMachData.enFanZone   = 0;
    cfgMachData.enInhal     = 0;
    cfgMachData.enBlow      = 0;
    cfgMachData.freqInhale  = 5000;
    cfgMachData.freqBlow    = 5000;

    cfgMachData.timeSwage   = 200;			//压料时间(s)
    cfgMachData.timeBlow    = 200;          //吹气时间(s)
    cfgMachData.timeLoadBefore  = 200;		//放料开始提前时间(s)
    cfgMachData.timeLoadAfter   = 200;		//放料结束提前时间(s)
    cfgMachData.timeInhaleDelay = 200;		//吸气延迟时间(ms)

    cfgMachData.alignEn     = 0;
    cfgMachData.alignMaxZ   = 10;
    cfgMachData.alignStartZ = 10;
    cfgMachData.alignAbsX   = 100;
    cfgMachData.alignAbsY   = 100;

    cfgMachData.headCount   = 100;
}
QString CfgMach::GetMachCfgPath()
{
    return cfgMachData.cfgPath;
}
int CfgMach::GetHeadCount()
{
    return cfgMachData.headCount;
}
QString CfgMach::GetVersionHw()
{
    return cfgMachData.versionHw;
}
QString CfgMach::GetVersionSw()
{
    return cfgMachData.versionSw;
}
double  CfgMach::GetType()
{
    return cfgMachData.machType;
}
double  CfgMach::GetSizeX()
{
    return cfgMachData.sizeX;
}
double  CfgMach::GetSizeY()
{
    return cfgMachData.sizeY;
}
double  CfgMach::GetFeltThick()
{
    return cfgMachData.feltThick;
}
bool CfgMach::GetEffctLvLimit()
{
    return cfgMachData.effctLvLimit;
}
bool CfgMach::GetEffctLvSwage()
{
    return cfgMachData.effctLvSwage;
}
bool CfgMach::GetEffctLvPuase()
{
    return cfgMachData.effctLvPuase;
}
bool CfgMach::GetEffctLvPump()
{
    return cfgMachData.effctLvPump;
}
bool CfgMach::GetEnFanZone()
{
    return cfgMachData.enFanZone;
}
bool CfgMach::GetEnInhal()
{
    return cfgMachData.enInhal;
}
bool CfgMach::GetEnBlow()
{
    return cfgMachData.enBlow;
}
int CfgMach::GetFreqInhale()
{
    return cfgMachData.freqInhale;
}
int CfgMach::GetFreqBlow()
{
    return cfgMachData.freqBlow;
}
int CfgMach::GetTimeSwage()
{
    return cfgMachData.timeSwage;
}
int CfgMach::GetTimeBlow()
{
    return cfgMachData.timeBlow;
}
int CfgMach::GetTimeLoadBefore()
{
    return cfgMachData.timeLoadBefore;
}
int CfgMach::GetTimeLoadAfter()
{
    return cfgMachData.timeLoadAfter;
}
int CfgMach::GetTimeInhaleDelay()
{
    return cfgMachData.timeInhaleDelay;
}
bool CfgMach::GetAlignEn()
{
    return cfgMachData.alignEn;
}
double CfgMach::GetAlignMaxZ()
{
    return cfgMachData.alignMaxZ;
}
double CfgMach::GetAlignStartZ()
{
    return cfgMachData.alignStartZ;
}
double CfgMach::GetAlignAbsX()
{
    return cfgMachData.alignAbsX;
}
double CfgMach::GetAlignAbsY()
{
    return cfgMachData.alignAbsY;
}
void CfgMach::GetMachineBaseInfo()
{
    QString strConfigPath = cfgMachData.cfgPath;

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
        cfgMachData.versionHw = *szBuf;
    }
    //软版本号
    strKey = ("SwVersion");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.versionSw = *szBuf;
    }
    //机器类型
    strKey = ("Type");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.machType = (*szBuf).toInt();
    }
    //机器长宽度
    strKey = ("SizeX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.sizeX = (*szBuf).toDouble();
    }
    strKey = ("SizeY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.sizeY = (*szBuf).toDouble();
    }
    //毛毡厚度
    strKey = ("FeltThick");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.feltThick = (*szBuf).toDouble();
    }
//--------------------------机械配置
    //机头个数
    strSect = ("MachSet");
    strKey = ("HeadCount");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.headCount = (*szBuf).toInt();
    }
    strKey = ("EffctLvLimit");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.effctLvLimit = (*szBuf).toInt();
    }
    strKey = ("EffctLvSwage");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.effctLvSwage = (*szBuf).toInt();
    }
    strKey = ("EffctLvPuase");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.effctLvPuase = (*szBuf).toInt();
    }
    strKey = ("EffctLvPump");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.effctLvPump = (*szBuf).toInt();
    }
    strKey = ("EnFanZone");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.enFanZone = (*szBuf).toInt();
    }
    strKey = ("EnInhale");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.enInhal = (*szBuf).toInt();
    }
    strKey = ("EnBlow");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.enBlow = (*szBuf).toInt();
    }
    strKey = ("FreqInhale");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.freqInhale = (*szBuf).toInt();
    }
    strKey = ("FreqBlow");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.freqBlow = (*szBuf).toInt();
    }
  //----------------------风机
    //压料时间
    strKey = ("TimeSwage");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.timeSwage = (*szBuf).toInt();
    }
    //吹气时间(s)
    strKey = ("TimeBlow");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.timeBlow = (*szBuf).toInt();
    }
    //放料开始提前时间(s)
    strKey = ("TimeLoadBefore");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.timeLoadBefore = (*szBuf).toInt();
    }
    //放料结束提前时间(s)
    strKey = ("TimeLoadAfter");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.timeLoadAfter = (*szBuf).toInt();
    }
    //吸气延迟时间(ms)
    strKey = ("TimeInhaleDelay");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.timeInhaleDelay = (*szBuf).toInt();
    }
  //----------------------对刀
    strKey = ("AlignEn");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.alignEn = (*szBuf).toInt();
    }
    strKey = ("AlignMaxZ");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.alignMaxZ = (*szBuf).toDouble();
    }
    strKey = ("AlignStartZ");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.alignStartZ = (*szBuf).toDouble();
    }
    strKey = ("AlignAbsX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.alignAbsX = (*szBuf).toDouble();
    }
    strKey = ("AlignAbsY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgMachData.alignAbsY = (*szBuf).toDouble();
    }
}
