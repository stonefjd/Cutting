#include "settings.h"
#include "ui_settings.h"

//#pragma execution_character_set("utf-8")

#define SettingPath "Settings\\settings.ini"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
//--Init Ui
    emit ui->listWidget->itemClicked(ui->listWidget->item(0));
    ui->tabWidgetSize->setCurrentIndex(0);
    ui->tabWidgetSpeed->setCurrentIndex(0);
//--Set lineEdit limit
    ui->lineEditLazerAbsX->setValidator(new QDoubleValidator(0, 1000.0, 2,this));
//--Init Settings File
    this->pathSettingFile = SettingPath;
    QSettings settingsObj(this->pathSettingFile,QSettings::IniFormat);
    QFile file(this->pathSettingFile);

    if(!file.exists())
    {
        //remind for init files
        QMessageBox::information(this,QObject::tr("提示"),QObject::tr("参数配置缺失，\n重新初始化文件设置"),QObject::tr("确定"));//setText(QObject::tr("软件配置文件不存在，以默认文件进行创建"))

        SettingsCfg_SetDefault(&settingsCfg_Default);
        SettingsCfg_Set(&settingsObj,&settingsCfg_Default);
    }
    SettingsCfg_GetInit(&settingsObj,&settingsCfg);

//--First Dislpay
    SettingsCfg_DisplayNum(&settingsCfg);
//--Display Ui

}
Settings::~Settings()
{
    delete ui;
}
void Settings::SettingsCfg_DisplayNum(SettingsCfg_T *cfg)
{
    ui->lineEditLazerAbsX->setText(QString::number(cfg->laserAbs.x));
    ui->lineEditLazerAbsY->setText(QString::number(cfg->laserAbs.y));

    ui->lineEditSeatX_1->setText(QString::number(cfg->toolSeat[0].x));
    ui->lineEditSeatY_1->setText(QString::number(cfg->toolSeat[0].y));
    ui->lineEditSeatH_1->setText(QString::number(cfg->toolSeat[0].h));

    ui->lineEditSeatX_2->setText(QString::number(cfg->toolSeat[1].x));
    ui->lineEditSeatY_2->setText(QString::number(cfg->toolSeat[1].y));
    ui->lineEditSeatH_2->setText(QString::number(cfg->toolSeat[1].h));

    ui->lineEditSeatX_3->setText(QString::number(cfg->toolSeat[2].x));
    ui->lineEditSeatY_3->setText(QString::number(cfg->toolSeat[2].y));
    ui->lineEditSeatH_3->setText(QString::number(cfg->toolSeat[2].h));

    ui->lineEditSeatX_4->setText(QString::number(cfg->toolSeat[3].x));
    ui->lineEditSeatY_4->setText(QString::number(cfg->toolSeat[3].y));
    ui->lineEditSeatH_4->setText(QString::number(cfg->toolSeat[3].h));

    ui->lineEditSeatX_5->setText(QString::number(cfg->toolSeat[4].x));
    ui->lineEditSeatY_5->setText(QString::number(cfg->toolSeat[4].y));
    ui->lineEditSeatH_5->setText(QString::number(cfg->toolSeat[4].h));

    ui->lineEditCuttingX->setText(QString::number(cfg->desktopSizeCut.x));
    ui->lineEditCuttingY->setText(QString::number(cfg->desktopSizeCut.y));

    ui->lineEditDesktopH->setText(QString::number(cfg->desktopH.h));

    ui->lineEditMovingSpd->setText(QString::number(cfg->toolSpeed.movingSpd));
    ui->lineEditMovingAcc->setText(QString::number(cfg->toolSpeed.movingAcc));
    ui->lineEditCuttingSpd->setText(QString::number(cfg->toolSpeed.cuttingSpd));
    ui->lineEditCuttingAcc->setText(QString::number(cfg->toolSpeed.cuttingAcc));
    ui->lineEditToolDown->setText(QString::number(cfg->toolSpeed.toolDown));
    ui->lineEditDesktopSpd->setText(QString::number(cfg->toolSpeed.desktopSpd));

    ui->hSliderWindPos->setSliderPosition(int(cfg->fanSpeed.windPos));
    ui->hSliderWindNeg->setSliderPosition(int(cfg->fanSpeed.windNeg));
}
void Settings::SettingsCfg_Set(QSettings *settings,SettingsCfg_T *cfg)
{
    settings->beginGroup("LaserAbs");
    settings->setValue("X",cfg->laserAbs.x);
    settings->setValue("Y",cfg->laserAbs.y);
    settings->endGroup();

    settings->beginGroup("desktopH");
    settings->setValue("H",cfg->desktopH.h);
    settings->endGroup();

    settings->beginGroup("desktopSizeCut");
    settings->setValue("X",cfg->desktopSizeCut.x);
    settings->setValue("Y",cfg->desktopSizeCut.y);
    settings->endGroup();

    settings->beginGroup("fanSpeed");
    settings->setValue("POS",cfg->fanSpeed.windPos);
    settings->setValue("NEG",cfg->fanSpeed.windNeg);
    settings->endGroup();

    settings->beginGroup("toolSpeed");
    settings->setValue("cuttingSpd",cfg->toolSpeed.cuttingSpd);
    settings->setValue("cuttingAcc",cfg->toolSpeed.cuttingAcc);
    settings->setValue("desktopSpd",cfg->toolSpeed.desktopSpd);
    settings->setValue("movingSpd",cfg->toolSpeed.movingSpd);
    settings->setValue("movingAcc",cfg->toolSpeed.movingAcc);
    settings->setValue("toolDown",cfg->toolSpeed.toolDown);
    settings->endGroup();

    for(int i = 0;i < TOOLNUM;i++)
    {
        settings->beginGroup("toolSeat" + QString::number(i));
        settings->setValue("X",cfg->toolSeat[i].x);
        settings->setValue("Y",cfg->toolSeat[i].y);
        settings->setValue("Z",cfg->toolSeat[i].h);
        settings->endGroup();
    }
}
bool Settings::SettingsCfg_GetEditLine(SettingsCfg_T *cfg)
{
    cfg->laserAbs.x = ui->lineEditLazerAbsX->text().toDouble();
    cfg->laserAbs.y = ui->lineEditLazerAbsY->text().toDouble();

    cfg->desktopH.h = ui->lineEditDesktopH->text().toDouble();

    cfg->desktopSizeCut.x = ui->lineEditCuttingX->text().toDouble();
    cfg->desktopSizeCut.y = ui->lineEditCuttingY->text().toDouble();

    cfg->fanSpeed.windPos = double(ui->hSliderWindPos->sliderPosition());
    cfg->fanSpeed.windNeg = double(ui->hSliderWindNeg->sliderPosition());

    cfg->toolSpeed.cuttingSpd   = ui->lineEditCuttingSpd->text().toDouble();
    cfg->toolSpeed.cuttingAcc   = ui->lineEditCuttingAcc->text().toDouble();
    cfg->toolSpeed.desktopSpd   = ui->lineEditDesktopSpd->text().toDouble();
    cfg->toolSpeed.movingSpd    = ui->lineEditMovingSpd->text().toDouble();
    cfg->toolSpeed.movingAcc    = ui->lineEditMovingAcc->text().toDouble();
    cfg->toolSpeed.toolDown     = ui->lineEditToolDown->text().toDouble();

    cfg->toolSeat[0].x   = ui->lineEditSeatX_1->text().toDouble();
    cfg->toolSeat[0].y   = ui->lineEditSeatY_1->text().toDouble();
    cfg->toolSeat[0].h   = ui->lineEditSeatH_1->text().toDouble();

    cfg->toolSeat[1].x   = ui->lineEditSeatX_2->text().toDouble();
    cfg->toolSeat[1].y   = ui->lineEditSeatY_2->text().toDouble();
    cfg->toolSeat[1].h   = ui->lineEditSeatH_2->text().toDouble();

    cfg->toolSeat[2].x   = ui->lineEditSeatX_3->text().toDouble();
    cfg->toolSeat[2].y   = ui->lineEditSeatY_3->text().toDouble();
    cfg->toolSeat[2].h   = ui->lineEditSeatH_3->text().toDouble();

    cfg->toolSeat[3].x   = ui->lineEditSeatX_4->text().toDouble();
    cfg->toolSeat[3].y   = ui->lineEditSeatY_4->text().toDouble();
    cfg->toolSeat[3].h   = ui->lineEditSeatH_4->text().toDouble();

    cfg->toolSeat[4].x   = ui->lineEditSeatX_5->text().toDouble();
    cfg->toolSeat[4].y   = ui->lineEditSeatY_5->text().toDouble();
    cfg->toolSeat[4].h   = ui->lineEditSeatH_5->text().toDouble();

    return true;
}
bool Settings::SettingsCfg_GetInit(QSettings *settings,SettingsCfg_T *cfg)
{
    settings->beginGroup("laserAbs");
    cfg->laserAbs.x = settings->value("X").toDouble();
    cfg->laserAbs.y = settings->value("Y").toDouble();
    settings->endGroup();

    settings->beginGroup("desktopH");
    cfg->desktopH.h = settings->value("H").toDouble();
    settings->endGroup();

    settings->beginGroup("desktopSizeCut");
    cfg->desktopSizeCut.x = settings->value("X").toDouble();
    cfg->desktopSizeCut.y = settings->value("Y").toDouble();
    settings->endGroup();

    settings->beginGroup("fanSpeed");
    cfg->fanSpeed.windPos = settings->value("POS").toDouble();
    cfg->fanSpeed.windNeg = settings->value("NEG").toDouble();
    settings->endGroup();

    settings->beginGroup("toolSpeed");
    cfg->toolSpeed.cuttingSpd   = settings->value("cuttingSpd").toDouble();
    cfg->toolSpeed.cuttingAcc   = settings->value("cuttingAcc").toDouble();
    cfg->toolSpeed.desktopSpd   = settings->value("desktopSpd").toDouble();
    cfg->toolSpeed.movingSpd    = settings->value("movingSpd").toDouble();
    cfg->toolSpeed.movingAcc    = settings->value("movingAcc").toDouble();
    cfg->toolSpeed.toolDown     = settings->value("toolDown").toDouble();
    settings->endGroup();

    for(int i = 0;i < TOOLNUM;i++)
    {
        settings->beginGroup("toolSeat" + QString::number(i));
        cfg->toolSeat[i].x   = settings->value("X").toDouble();
        cfg->toolSeat[i].y   = settings->value("Y").toDouble();
        cfg->toolSeat[i].h   = settings->value("Z").toDouble();
        settings->endGroup();
    }
    return true;
}
void Settings::SettingsCfg_SetDefault(SettingsCfg_T *cfg)
{
    cfg->desktopH.h              = 0.2;
    cfg->desktopSizeCut.x        = 2.4;
    cfg->desktopSizeCut.y        = 1.2;
    cfg->fanSpeed.windNeg        = 10;
    cfg->fanSpeed.windPos        = 20;
    cfg->laserAbs.x              = 20.2;
    cfg->laserAbs.y              = 20.2;
    cfg->toolSpeed.cuttingAcc    = 1;
    cfg->toolSpeed.cuttingSpd    = 1.2;
    cfg->toolSpeed.desktopSpd    = 0.5;
    cfg->toolSpeed.movingAcc     = 1;
    cfg->toolSpeed.movingSpd     = 1.2;
    cfg->toolSpeed.toolDown      = 0.2;
    for(int i = 0;i < TOOLNUM;i++)
    {
        cfg->toolSeat[i].x       = 10;
        cfg->toolSeat[i].y       = 10+i*10;
        cfg->toolSeat[i].h       = 10;
    }
}
void Settings::on_listWidget_itemClicked(QListWidgetItem *item)
{
    if(item == ui->listWidget->item(0))
    {
        qDebug()<<"0";
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if (item == ui->listWidget->item(1))
    {
        qDebug()<<"1";
        ui->stackedWidget->setCurrentIndex(1);
    }
}



void Settings::on_pushButtonOk_clicked()
{
    SettingsCfg_GetEditLine(&settingsCfg);
    QSettings settingsObj(this->pathSettingFile,QSettings::IniFormat);
    SettingsCfg_Set(&settingsObj,&settingsCfg);
    this->close();
}

void Settings::on_pushButtonApply_clicked()
{
    SettingsCfg_GetEditLine(&settingsCfg);
    QSettings settingsObj(this->pathSettingFile,QSettings::IniFormat);
    SettingsCfg_Set(&settingsObj,&settingsCfg);
}

void Settings::on_pushButtonCancel_clicked()
{
    SettingsCfg_DisplayNum(&settingsCfg);
    this->close();
}
void Settings::resetSettingsData()
{
    QSettings settingsObj(this->pathSettingFile,QSettings::IniFormat);
    SettingsCfg_SetDefault(&settingsCfg_Default);
    SettingsCfg_Set(&settingsObj,&settingsCfg_Default);
    SettingsCfg_GetInit(&settingsObj,&settingsCfg);
    SettingsCfg_DisplayNum(&settingsCfg);
}
