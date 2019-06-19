#include "iniop.h"
#include "ui_iniop.h"

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
    else
    {
        IniOp_ReadFromIniFile(&initItem,&settingsObj);
    }
    /* //use the map file as the structure for the control
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
    */
}

IniOp::~IniOp()
{
    delete ui;
}
void IniOp::IniOp_FromIniToMap(QMap<QString, QString> *_qMap,QSettings *_qSetting)
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
void IniOp::IniOp_ReadFromIniFile(InitItem_T *_obj,QSettings *settings)
{
    settings->beginGroup("HwInfo");
    _obj->hwInfo.Version = settings->value("Version").toString();
    settings->endGroup();

    settings->beginGroup("SwInfo");
    _obj->swInfo.Version = settings->value("Version").toString();
    _obj->swInfo.Title = settings->value("Title").toString();
    _obj->swInfo.Language = settings->value("Language").toString();
    settings->endGroup();

    settings->beginGroup("MachInfo");
    _obj->machInfo.MainType = settings->value("MainType").toString();
    _obj->machInfo.SubType = settings->value("SubType").toString();
    _obj->machInfo.Length = settings->value("Length").toDouble();
    _obj->machInfo.Width = settings->value("Width").toDouble();
    _obj->machInfo.BeamCount = settings->value("BeamCount").toInt();
    _obj->machInfo.HeadCount = settings->value("HeadCount").toInt();
    _obj->machInfo.LimitSwitchLevel = settings->value("LimitSwitchLevel").toBool();
    _obj->machInfo.LimitSwitchLength = settings->value("LimitSwitchLength").toInt();
    settings->endGroup();

    settings->beginGroup("MachSet");
    _obj->machSet.CutLength = settings->value("CutLength").toDouble();
    _obj->machSet.FeedLength = settings->value("FeedLength").toDouble();
    _obj->machSet.feltThick = settings->value("feltThick").toDouble();
    settings->endGroup();

    settings->beginGroup("FanSet");
    _obj->fanSet.ZoneEn = settings->value("ZoneEn").toBool();
    _obj->fanSet.FreqChgEn = settings->value("FreqChgEn").toBool();
    _obj->fanSet.InhaleEn= settings->value("InhaleEn").toBool();
    _obj->fanSet.BlowEn = settings->value("BlowEn").toBool();
    _obj->fanSet.InhaleFreq = settings->value("InhaleFreq").toInt();
    _obj->fanSet.BlowFreq = settings->value("BlowFreq").toInt();
    settings->endGroup();

    settings->beginGroup("SpeedSet");
    _obj->speedSet.CutSpd = settings->value("CutSpd").toDouble();
    _obj->speedSet.CutAcc = settings->value("CutAcc").toDouble();
    _obj->speedSet.MoveSpd = settings->value("MoveSpd").toDouble();
    _obj->speedSet.MoveAcc = settings->value("MoveAcc").toDouble();
    _obj->speedSet.FeltMovSpd = settings->value("FeltMovSpd").toDouble();
    _obj->speedSet.ToolDownSpd = settings->value("ToolDownSpd").toDouble();
    _obj->speedSet.FeedSpd = settings->value("FeedSpd").toDouble();
    settings->endGroup();

    settings->beginGroup("TimeSet");
    _obj->timeSet.SwagingTime = settings->value("SwagingTime").toInt();
    _obj->timeSet.BlowTime = settings->value("BlowTime").toInt();
    _obj->timeSet.InhaleDelayTime = settings->value("InhaleDelayTime").toInt();
    settings->endGroup();

    settings->beginGroup("AlignToolSet");
    _obj->alignToolSet.AlignEn = settings->value("AlignEn").toBool();
    _obj->alignToolSet.AlignZ = settings->value("AlignZ").toDouble();
    _obj->alignToolSet.AlignAbsX = settings->value("AlignAbsX").toDouble();
    _obj->alignToolSet.AlignAbsY = settings->value("AlignAbsY").toDouble();
    _obj->alignToolSet.AlignMaxZ = settings->value("AlignMaxZ").toDouble();
    _obj->alignToolSet.AlignZCalib = settings->value("AlignZCalib").toDouble();
    settings->endGroup();

    settings->beginGroup("Head1Set");
    _obj->head1Set.Index = settings->value("Index").toBool();
    _obj->head1Set.SeatNum = settings->value("SeatNum").toInt();
    _obj->head1Set.Knifeilds = settings->value("Knifeilds").toStringList();
    _obj->head1Set.SeatOffsetX = settings->value("SeatOffsetX").toStringList();
    _obj->head1Set.SeatOffsetY = settings->value("SeatOffsetY").toStringList();
    _obj->head1Set.SeatOffsetZ = settings->value("SeatOffsetZ").toStringList();
    qDebug()<<settings->value("SeatOffsetZ").toStringList();
    _obj->head1Set.AbsX = settings->value("AbsX").toDouble();
    _obj->head1Set.AbsY = settings->value("AbsY").toDouble();
    _obj->head1Set.LaserOffsetX = settings->value("LaserOffsetX").toDouble();
    _obj->head1Set.LaserOffsetY = settings->value("LaserOffsetY").toDouble();
    _obj->head1Set.FctLenX = settings->value("FctLenX").toDouble();
    _obj->head1Set.FctLenY = settings->value("FctLenY").toDouble();
    _obj->head1Set.StdLenX = settings->value("StdLenX").toDouble();
    _obj->head1Set.StdLenY = settings->value("StdLenY").toDouble();
    _obj->head1Set.ScaleX = settings->value("ScaleX").toDouble();
    _obj->head1Set.ScaleY = settings->value("ScaleY").toDouble();
    settings->endGroup();

    settings->beginGroup("RecordDetail");
    _obj->recordDetail.LastPlotFlag = settings->value("LastPlotFlag").toBool();
    _obj->recordDetail.LastCutLineId = settings->value("LastCutLineId").toInt();
    _obj->recordDetail.LastPlotLineId = settings->value("LastPlotLineId").toInt();
    _obj->recordDetail.LastFilePathList = settings->value("LastFilePathList").toString();
    settings->endGroup();

//

}
void IniOp::IniOp_WriteToIniFile(InitItem_T _obj,QSettings *settings)
{

}
