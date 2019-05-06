#include "configmachine.h"
#include "configinfo.h"

ConfigMachine::ConfigMachine(QWidget *parent) : QWidget(parent)
{
    machCfgPath = SETTING_PATH;
}
QString ConfigMachine::GetMachCfgPath()
{
    return machCfgPath;
}
void ConfigMachine::SetMachRunMax(int _axis,double _pos)
{
    machRunMax[_axis-1] = _pos;
}
double ConfigMachine::GetMachRunMax(int _axis)
{
    return machRunMax[_axis-1];
}
bool ConfigMachine::UpdateMachRunMax(int _axis,double _pos)
{
    bool _b=false;
    double _runMax;

    _runMax = _pos/machPulsePerMillimeter[_axis-1];
    if(qAbs(machRunMax[_axis-1]-_runMax)>10)
    {
       machRunMax[_axis-1] = _runMax;
       _b = true;
    }
    return _b;
}

void    ConfigMachine::SetMachPulsePerMillimeter(int _axis,double _pos)
{
    machPulsePerMillimeter[_axis-1] = _pos;
}
double  ConfigMachine::GetMachPulsePerMillimeter(int _axis)
{
    return machPulsePerMillimeter[_axis-1];
}
void ConfigMachine::GetMachineBaseInfo()
{
    QString strConfigPath = machCfgPath;

    QString strSect = ("");
    QString strKey = ("");
    QString strText = ("");
    QString strDefault = ("");
    QString sInfo = "";

    QString *szBuf = new QString;

    //硬件版本号
    strSect = ("HwInfo");
    strKey = ("Version");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        versionHw = *szBuf;
    }

    //软版本号
    strSect = ("SwInfo");
    strKey = ("Version");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        versionSw = *szBuf;
    }

    //毛毡厚度
    strSect = ("DesktopSet");
    strKey = ("FeltThickness");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        feltThickness = (*szBuf).toDouble();
    }

    //机器类型
    strSect = ("MachInfo");
    strKey = ("MachType");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        machType = (*szBuf).toInt();
    }

    //机器子类型
    strKey = ("MachTypeSub");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        machTypeSub = (*szBuf).toInt();
    }

    //机器长宽度
    strKey = ("MachPhysical");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        for(int i=0;i<AXIS_SUM;i++)
            machPhysical[i] = (*szBuf).split(',').at(i).toDouble();
    }

    //机器实际行走长宽度
    strKey = ("MachRunMax");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        for(int i=0;i<AXIS_SUM;i++)
            machRunMax[i] = (*szBuf).split(',').at(i).toDouble();
    }

    //脉冲个数每毫秒X,Y
    strKey = ("MachPulsePerMillimeter");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        for(int i=0;i<AXIS_SUM;i++)
            machPulsePerMillimeter[i] = (*szBuf).split(',').at(i).toDouble();
    }
    //压料时间(s)
    strKey = ("MachTimeSwage");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        machTimeSwage = (*szBuf).toInt();
    }
    //吹气时间(s)
    strKey = ("MachTimeBlow");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        machTimeBlow = (*szBuf).toInt();
    }
    //放料开始提前时间(s)
    strKey = ("MachTimeLoadBefore");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        machTimeLoadBefore = (*szBuf).toInt();
    }
    //放料结束提前时间(s)
    strKey = ("MachTimeLoadAfter");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        machTimeLoadAfter = (*szBuf).toInt();
    }
    //吸气延迟时间(ms)
    strKey = ("MachTimeInhaleDelay");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        machTimeInhaleDelay = (*szBuf).toInt();
    }
    //机头个数
    strKey = ("MachHeadCount");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        machHeadCount = (*szBuf).toInt();
    }
    //机头信息
    for(int _headCnt=0;_headCnt<machHeadCount;_headCnt++)
    {
        ConfigHead *head = new ConfigHead;
        head->GetHeadInfo(_headCnt);
        headConfig.append(head);
    }
}
bool ConfigMachine::WritePrivateProfileString(QString strSect,QString strKey,QString strText,QString strConfigPath)
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
bool ConfigMachine::GetPrivateProfileString(QString strSect,QString strKey,QString *szBuf,QString strConfigPath)
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
