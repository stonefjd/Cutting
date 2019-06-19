#include "cfgmachsettings.h"
#include "ui_cfgmachsettings.h"

cfgMachSettings::cfgMachSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cfgMachSettings)
{
    ui->setupUi(this);
}

cfgMachSettings::~cfgMachSettings()
{
    delete ui;
}
