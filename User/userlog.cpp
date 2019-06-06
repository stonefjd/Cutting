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

void UserLog::SetUser(User *_user)
{
    this->user = _user;
}

UserLog::~UserLog()
{
    delete ui;
}

void UserLog::on_buttonBox_accepted()
{
    user->SetUserSN(ui->lineEditSN->text().toInt());
    user->SetUserPSW(ui->lineEditPsw->text());
    user->CheckUserMatching();
}
