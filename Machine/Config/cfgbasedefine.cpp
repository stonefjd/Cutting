#include "cfgbasedefine.h"

CfgBaseDefine::CfgBaseDefine()
{

}
bool WritePrivateProfileString(QString strSect,QString strKey,QString strText,QString strConfigPath)
{
    QFile file(strConfigPath);
    if(!file.exists())
    {
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("初始化配置文件内容缺失"));
        msgBox.exec();
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
bool GetPrivateProfileString(QString strSect,QString strKey,QString *szBuf,QString strConfigPath)
{
    QFile file(strConfigPath);
    if(!file.exists())
    {
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("初始化配置文件内容缺失"));
        msgBox.exec();
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
