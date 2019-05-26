#include "confighead.h"
#include "configinfo.h"
ConfigHead::ConfigHead(QWidget *parent) : QWidget(parent)
{
    headCfgPath = SETTING_PATH;
}

void ConfigHead::GetHeadInfo(int _index)
{
    QString strConfigPath = headCfgPath;

    QString strSect = ("");
    QString strKey = ("");
    QString strText = ("");
    QString strDefault = ("");
    QString sInfo = "";

    QString *szBuf = new QString;

    //机头个数
    strSect = ("MachHead"+QString::number(_index));
    strKey = ("MachHeadIndex");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        headIndex = (*szBuf).toInt();
    }

    //原点偏移
    strKey = ("MachHeadXOrigon");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        headOrg.setX((*szBuf).toDouble());
    }
    strKey = ("MachHeadYOrigon");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        headOrg.setY((*szBuf).toDouble());
    }
    //机头当前位置
//    strKey = ("MachHeadXPos");
//    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
//    {
//        headPos.setX((*szBuf).toInt());
//    }
//    strKey = ("MachHeadYPos");
//    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
//    {
//        headPos.setY((*szBuf).toInt());
//    }
    //X方向最大行走脉冲数
    strKey = ("HeadMaxPluseX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        headMaxPluse.setX((*szBuf).toDouble());
    }
    strKey = ("HeadMaxPluseY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        headMaxPluse.setY((*szBuf).toDouble());
    }
    //比例因子：脉冲每毫米
    strKey = ("HeadPluseScaleX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        headPluseScale.setX((*szBuf).toDouble());
    }
    strKey = ("HeadPluseScaleY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        headPluseScale.setY((*szBuf).toDouble());
    }
    //最大长度：毫米
    strKey = ("HeadMaxLengthX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        headMaxLength.setX((*szBuf).toDouble());
    }
    strKey = ("HeadMaxLengthY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        headMaxLength.setY((*szBuf).toDouble());
    }

    //区域限位，人为设定尺寸
    strKey = ("HeadCutLimitX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        headLimit.setX((*szBuf).toDouble());
    }
    strKey = ("HeadCutLimitY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        headLimit.setY((*szBuf).toDouble());
    }
    //送料长度
    strKey = ("FeedLen");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        feedLen = (*szBuf).toInt();
    }
    //送料速度(m/s)
    strKey = ("FeedSpd");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        feedSpd = (*szBuf).toInt();
    }
    //送料加速度(m/s²)
    strKey = ("FeedAcc");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        feedAcc = (*szBuf).toInt();
    }
    //空走速度 (m/s)
    strKey = ("IdleMoveSpd");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        idleMoveSpd = (*szBuf).toInt();
    }
    //空走加速度(G)
    strKey = ("IdleMoveAcc");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        idleMoveAcc = (*szBuf).toInt();
    }
    //获取机座列表
    strKey = ("Aprons");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        apronIndexList = szBuf->split(',');
    }
    for(int _apronCnt=0;_apronCnt<apronIndexList.count();_apronCnt++)
    {
        strKey = ("Apron"+QString::number(_apronCnt));
        QStringList apronParam;
        if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
        {
            apronParam = (szBuf)->split(',');
        }
        configApron *apron = new configApron;
        apron->SetApronIndex(_apronCnt);
        apron->SetKnifeGuid(KNIFETOOLID2GUID(apronParam.at(1).toInt(),apronParam.at(2).toInt()));
        apron->SetXOffset(apronParam.at(3).toDouble());
        apron->SetXOffset(apronParam.at(4).toDouble());
        aConfig.append(apron);
    }
}
QString ConfigHead::GetHeadCfgPath()
{
    return headCfgPath;
}
void ConfigHead::UpdateHeadMaxPluse(int _xPluse,int _yPluse,int _hIndex)
{
    headMaxPluse.setX(_xPluse);
    headMaxPluse.setY(_yPluse);
    headMaxLength.setX(_xPluse/headPluseScale.x());
    headMaxLength.setY(_yPluse/headPluseScale.y());
    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"HeadMaxPluseX",QString::number(_xPluse),headCfgPath);
    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"HeadMaxPluseY",QString::number(_yPluse),headCfgPath);
    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"HeadMaxLengthX",QString::number(_xPluse/headPluseScale.x()),headCfgPath);
    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"HeadMaxLengthY",QString::number(_yPluse/headPluseScale.y()),headCfgPath);
    if(_xPluse <= headLimit.x())
    {
        headLimit.setX(_xPluse);
        WritePrivateProfileString("MachHead"+QString::number(_hIndex),"HeadCutLimitX",QString::number(_xPluse),headCfgPath);
    }
    if(_yPluse <= headLimit.y())
    {
        headLimit.setX(_xPluse);
        WritePrivateProfileString("MachHead"+QString::number(_hIndex),"HeadCutLimitY",QString::number(_yPluse),headCfgPath);
    }
}
void ConfigHead::UpdateHeadCutLimit(int _xPluse,int _yPluse,int _hIndex)
{
    if(_xPluse <= headMaxPluse.x())
    {
        headLimit.setX(_xPluse);
    }
    if(_yPluse <= headMaxPluse.y())
    {
        headLimit.setY(_yPluse);
    }
    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"HeadCutLimitX",QString::number(_xPluse),headCfgPath);
    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"HeadCutLimitY",QString::number(_yPluse),headCfgPath);
}

bool ConfigHead::WritePrivateProfileString(QString strSect,QString strKey,QString strText,QString strConfigPath)
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
bool ConfigHead::GetPrivateProfileString(QString strSect,QString strKey,QString *szBuf,QString strConfigPath)
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
