#include "settings.h"
#include "ui_settings.h"

#define TABNUM_A 5
#define TABNUM_B 4

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    emit ui->listWidget->itemClicked(ui->listWidget->item(0));
    ui->tabWidgetSize->setCurrentIndex(0);
    ui->tabWidgetSpeed->setCurrentIndex(0);
}

Settings::~Settings()
{
    delete ui;
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
    //    item->operator=()
}


