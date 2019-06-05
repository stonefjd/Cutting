#include "userlog.h"
#include "ui_userlog.h"

#include <QIntValidator>
#include <QDebug>
#include <QCryptographicHash>

UserLog::UserLog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserLog)
{
    ui->setupUi(this);
    //limit the ID only for 0-99999
    QValidator* validator = new QIntValidator(0,99999,this);
    ui->lineEditSN->setValidator(validator);
}
QString UserLog::GetLineEditSN(void)
{
    return ui->lineEditSN->text();
}
QString UserLog::GetLineEditPSW(void)
{
    return  ui->lineEditPsw->text();
}

UserLog::~UserLog()
{
    delete ui;
}
