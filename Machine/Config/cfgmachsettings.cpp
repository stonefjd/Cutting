#include "cfgmachsettings.h"
#include "ui_cfgmachsettings.h"

CfgMachSettings::CfgMachSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CfgMachSettings)
{
    ui->setupUi(this);
//    db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setHostName("PGM");
//    db.setDatabaseName("MyDataBase.db");
//    db.setUserName("STONE");
//    db.setPassword("12345678");
//    db.open();
}

CfgMachSettings::~CfgMachSettings()
{
    delete ui;
}
void CfgMachSettings::SetCfgMach(CfgMach *_cMach)
{
    this->cMach = _cMach;
}
void CfgMachSettings::SetCfgHead(CfgHead *_cHead)
{
    this->cHead = _cHead;
}
void CfgMachSettings::LoadData()
{
    //机械固化参数
    ui->lEdtHwVersion->setText(cMach->GetVersionHw());
    ui->lEdtSwVersion->setText(cMach->GetVersionSw());
    ui->lEdtType->setText(QString::number(cMach->GetType()));
    ui->lEdtSizeX->setText(QString::number(cMach->GetSizeX()));
    ui->lEdtSizeY->setText(QString::number(cMach->GetSizeY()));
    ui->lEdtFeltThick->setText(QString::number(cMach->GetFeltThick()));
    ui->lEdtHeadCount->setText(QString::number(cMach->GetHeadCount()));
    ui->gridLayout->setSizeConstraint(QLayout::SetFixedSize);
    //ui->tabWidget->setTabEnabled(0,false);
    ui->tabWidget->setStyleSheet("QTabBar::tab:disabled {width: 0; color: transparent;}");

    //机械配置参数
    ui->cbEffctLvLimit->setCurrentIndex(cMach->GetEffctLvLimit()?0:1);
    ui->cbEffctLvSwage->setCurrentIndex(cMach->GetEffctLvSwage()?0:1);
    ui->cbEffctLvPuase->setCurrentIndex(cMach->GetEffctLvPuase()?0:1);
    ui->cbEffctLvPump ->setCurrentIndex(cMach->GetEffctLvPump ()?0:1);

    ui->cbEnFanZone   ->setCurrentIndex(cMach->GetEnFanZone()?0:1);
    ui->cbEnBlow      ->setCurrentIndex(cMach->GetEnBlow()?0:1);
    ui->cbEnInhale    ->setCurrentIndex(cMach->GetEnInhal()?0:1);

    ui->lEdtFreqBlow  ->setValidator(new QIntValidator(0,5000,this));
    ui->lEdtFreqInhale->setValidator(new QIntValidator(0,5000,this));
    ui->lEdtFreqBlow  ->setText(QString::number(cMach->GetFreqBlow()));
    ui->lEdtFreqInhale->setText(QString::number(cMach->GetFreqInhale()));

    ui->lEdtTimeSwage      ->setValidator(new QIntValidator(0,500,this));
    ui->lEdtTimeBlow       ->setValidator(new QIntValidator(0,500,this));
    ui->lEdtTimeLoadBefore ->setValidator(new QIntValidator(0,500,this));
    ui->lEdtTimeLoadAfter  ->setValidator(new QIntValidator(0,500,this));
    ui->lEdtTimeInhaleDelay->setValidator(new QIntValidator(0,500,this));
    ui->lEdtTimeSwage      ->setText(QString::number(cMach->GetTimeSwage()));
    ui->lEdtTimeBlow       ->setText(QString::number(cMach->GetTimeBlow()));
    ui->lEdtTimeLoadBefore ->setText(QString::number(cMach->GetTimeLoadBefore()));
    ui->lEdtTimeLoadAfter  ->setText(QString::number(cMach->GetTimeLoadAfter()));
    ui->lEdtTimeInhaleDelay->setText(QString::number(cMach->GetTimeInhaleDelay()));

    ui->cbAlignEn      ->setCurrentIndex(cMach->GetAlignEn()?0:1);
    ui->lEdtAlignMaxZ  ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
    ui->lEdtAlignStartZ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
    ui->lEdtAlignAbsX  ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
    ui->lEdtAlignAbsY  ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
    ui->lEdtAlignMaxZ  ->setText(QString::number(cMach->GetAlignMaxZ()));
    ui->lEdtAlignStartZ->setText(QString::number(cMach->GetAlignStartZ()));
    ui->lEdtAlignAbsX  ->setText(QString::number(cMach->GetAlignAbsX()));
    ui->lEdtAlignAbsY  ->setText(QString::number(cMach->GetAlignAbsY()));

    //机头配置参数
    ui->lEdtPosOrgX         ->setText(QString::number(cHead->GetPosOrg().x()));
    ui->lEdtPosOrgY         ->setText(QString::number(cHead->GetPosOrg().y()));
    ui->lEdtPosLimitX       ->setText(QString::number(cHead->GetPosLimit().x()));
    ui->lEdtPosLimitY       ->setText(QString::number(cHead->GetPosLimit().y()));
    ui->lEdtPosMaxX         ->setText(QString::number(cHead->GetPosMax().x()));
    ui->lEdtPosMaxY         ->setText(QString::number(cHead->GetPosMax().y()));
    ui->lEdtPosToPulseScaleX->setText(QString::number(cHead->GetPosToPulseScale().x()));
    ui->lEdtPosToPulseScaleY->setText(QString::number(cHead->GetPosToPulseScale().y()));
    ui->lEdtPulseMaxX       ->setText(QString::number(cHead->GetPulseMax().x()));
    ui->lEdtPulseMaxY       ->setText(QString::number(cHead->GetPulseMax().y()));
    ui->lEdtRealToCutScaleX ->setText(QString::number(cHead->GetRealToCutScale().x()));
    ui->lEdtRealToCutScaleY ->setText(QString::number(cHead->GetRealToCutScale().y()));
    ui->lEdtPosOrgX         ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
    ui->lEdtPosOrgY         ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
    ui->lEdtPosLimitX       ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
    ui->lEdtPosLimitY       ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
    ui->lEdtPosMaxX         ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
    ui->lEdtPosMaxY         ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
    ui->lEdtPosToPulseScaleX->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
    ui->lEdtPosToPulseScaleY->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
    ui->lEdtRealToCutScaleX ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
    ui->lEdtRealToCutScaleY ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000

    ui->lEdtFeedLen    ->setText(QString::number(cHead->GetFeedLen()));
    ui->lEdtFeedSpd    ->setText(QString::number(cHead->GetFeedSpd()));
    ui->lEdtFeedAcc    ->setText(QString::number(cHead->GetFeedAcc()));
    ui->lEdtIdleMoveSpd->setText(QString::number(cHead->GetIdleMoveSpd()));
    ui->lEdtIdleMoveAcc->setText(QString::number(cHead->GetIdleMoveAcc()));
    ui->lEdtFeedLen    ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
    ui->lEdtFeedSpd    ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
    ui->lEdtFeedAcc    ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
    ui->lEdtIdleMoveSpd->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
    ui->lEdtIdleMoveAcc->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000

    QList<QLineEdit*> lEditList;
    lEditList.append(ui->tab->findChildren<QLineEdit*>());

    qDebug()<<lEditList;
}






void CfgMachSettings::on_lEdtFeedLen_editingFinished()
{
    QLineEdit *lEdt = qobject_cast<QLineEdit*>(sender());

    QFont font = lEdt->font();
    font.setBold(true);
    lEdt->setFont(font);
}
