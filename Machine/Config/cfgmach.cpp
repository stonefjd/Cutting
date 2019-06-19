#include "cfgmach.h"


CfgMach::CfgMach(QWidget *parent) : QWidget(parent)
{
    machCfgPath = SETTING_PATH;
}
QString CfgMach::GetMachCfgPath()
{
    return machCfgPath;
}
int CfgMach::GetMachHeadCount()
{
    return machHeadCount;
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
//void CfgMach::UpdateMachRunMax(int _xPos,int _yPos)
//{
//    machRunMax[0] = static_cast<double>(_xPos)/machPulsePerMillimeter[0];
//    machRunMax[1] = static_cast<double>(_yPos)/machPulsePerMillimeter[1];
//    WritePrivateProfileString("MachInfo","MachRunMax",QString::number(machRunMax[0])+','+ QString::number(machRunMax[1]),machCfgPath);
//}

//void    CfgMach::SetMachPulsePerMillimeter(int _axis,double _pos)
//{
//    machPulsePerMillimeter[_axis-1] = _pos;
//}
//double  CfgMach::GetMachPulsePerMillimeter(int _axis)
//{
//    return machPulsePerMillimeter[_axis-1];
//}
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
        machHeadCount = (*szBuf).toInt();
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

}
bool CfgMach::WritePrivateProfileString(QString strSect,QString strKey,QString strText,QString strConfigPath)
{
    QFile file(strConfigPath);
    if(!file.exists())
    {
        QMessageBox::information(this,QObject::tr("提示"),QObject::tr("初始化配置文件不存在"),QObject::tr("确定"));//setText(QObject::tr("软件配置文件不存在，以默认文件进行创建"))
        return false;
    }
    else
    {
        QSettings settingsObj(strConfigPath,QSettings::IniFormat);

        settingsObj.beginGroup(strSect);
        settingsObj.setValue(strKey,strText);
        settingsObj.endGroup();
    }
    return true;
}
bool CfgMach::GetPrivateProfileString(QString strSect,QString strKey,QString *szBuf,QString strConfigPath)
{
    QFile file(strConfigPath);
    if(!file.exists())
    {
        QMessageBox::information(this,QObject::tr("提示"),QObject::tr("初始化配置文件不存在"),QObject::tr("确定"));//setText(QObject::tr("软件配置文件不存在，以默认文件进行创建"))
        return false;
    }
    else
    {
        QSettings settingsObj(strConfigPath,QSettings::IniFormat);

        settingsObj.beginGroup(strSect);
        QString tpstr= (settingsObj.value(strKey)).toString();
        if(tpstr == nullptr)
        {
            QStringList tpstrl = (settingsObj.value(strKey)).toStringList();
            tpstr = tpstrl.join(',');
        }
        *szBuf = tpstr;
        settingsObj.endGroup();
    }
    return true;
}
