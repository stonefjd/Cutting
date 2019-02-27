#include "iniop.h"
#include "ui_iniop.h"
#define SettingPath "Settings\\settingsV1.2.ini"
#define IniFilePath "Settings\\settingsV1.2.ini"

IniOp::IniOp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IniOp)
{
    ui->setupUi(this);
//--judge .ini File existance
    this->iniFilePath = IniFilePath;
    QSettings settingsObj(this->iniFilePath,QSettings::IniFormat);
    QFile file(this->iniFilePath);
    if(!file.exists())
    {
        QMessageBox::information(this,QObject::tr("提示"),QObject::tr("参数配置缺失，\n重新初始化文件设置"),QObject::tr("确定"));//setText(QObject::tr("软件配置文件不存在，以默认文件进行创建"))
    }

//--Init Map for data in .ini file
    this->iniFileKeyList = settingsObj.allKeys();

    for(int i=0;i<iniFileKeyList.count();i++)
    {
        iniFileMap.insert(iniFileKeyList.at(i), settingsObj.value(iniFileKeyList.at(i)).toString());
    }
//--review for all items in this map
    QMapIterator<QString, QString> i(iniFileMap);
    while (i.hasNext()) {
        i.next();
        qDebug() << i.key() << ": " << i.value() << endl;
    }
    qDebug() << settingsObj.value("Head1Set/Knifeilds").toString();
}

IniOp::~IniOp()
{
    delete ui;
}
void IniOp::IniOp_FromIniToMap(QMap<QString, QString> *_qMap,QSettings _qSetting)
{

}
void IniOp::IniOp_FromMapToIni(QMap<QString, QString> _qMap,QSettings *_qSetting)
{

}
void IniOp::IniOp_FromMapToLbl(QMap<QString, QString> _qMap)
{

}
void IniOp::IniOp_FromLblToMap(QMap<QString, QString> *_qMap,QSettings *_qSetting)
{

}
void IniOp::IniOp_ReadFromIniFile(InitItem_T *_obj,QSettings settings)
{
    settings.beginGroup("HwInfo");
    _obj->hwInfo.Version = settings.value("Version").toString();
    settings.endGroup();

    settings.beginGroup("SwInfo");
    _obj->swInfo.Version = settings.value("Version").toString();
    _obj->swInfo.Title = settings.value("Title").toString();
    _obj->swInfo.Language = settings.value("Language").toString();
    settings.endGroup();

    settings.beginGroup("MachInfo");
    _obj->machInfo.MainType = settings.value("MainType").toString();
    _obj->machInfo.SubType = settings.value("SubType").toString();
    _obj->machInfo.Length = settings.value("Length").toDouble();
    _obj->machInfo.Width = settings.value("Width").toDouble();
    _obj->machInfo.BeamCount = settings.value("BeamCount").toInt();
    _obj->machInfo.HeadCount = settings.value("HeadCount").toInt();
    _obj->machInfo.LimitSwitchLevel = settings.value("LimitSwitchLevel").toInt();
    _obj->machInfo.LimitSwitchLength = settings.value("LimitSwitchLength").toInt();
    settings.endGroup();

    settings.beginGroup("MachInfo");
    settings.endGroup();

//

}
void IniOp::IniOp_WriteToIniFile(InitItem_T _obj,QSettings *settings)
{

}
