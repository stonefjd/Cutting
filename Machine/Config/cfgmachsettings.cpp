#include "cfgmachsettings.h"
#include "ui_cfgmachsettings.h"

CfgMachSettings::CfgMachSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CfgMachSettings)
{
    ui->setupUi(this);
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
    ui->lEdtHwVersion->setText(cMach->GetVersionHw());
    ui->lEdtSwVersion->setText(cMach->GetVersionSw());
    ui->lEdtType->setText(QString::number(cMach->GetType()));
    ui->lEdtSizeX->setText(QString::number(cMach->GetSizeX()));
    ui->lEdtSizeY->setText(QString::number(cMach->GetSizeY()));
    ui->lEdtFeltThick->setText(QString::number(cMach->GetFeltThick()));
    ui->gridLayout->setSizeConstraint(QLayout::SetFixedSize);
    ui->tabWidget->setTabEnabled(0,false);
    ui->tabWidget->setStyleSheet("QTabBar::tab:disabled {width: 0; color: transparent;}");
}
