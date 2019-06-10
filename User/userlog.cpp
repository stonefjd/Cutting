#include "userlog.h"
#include "ui_userlog.h"

#include <QIntValidator>
#include <QDebug>
#include <QCryptographicHash>
#include <QCompleter>
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
    //create user
    this->user = _user;
    //query the history user list
    QStringList strList = user->GetHistoryUser("");
    completer = new QCompleter(strList, this);
    ui->lineEditSN->setCompleter(completer);
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

void UserLog::on_lineEditSN_textEdited(const QString &arg1)
{
//    QStringList userList;
//    if(arg1.isEmpty())
//    {
//        qDebug()<<"y";
//    }
//    else
//        userList = user->GetHistoryUser(arg1);
//    DisplayHistoryUser(userList);
}
void UserLog::DisplayHistoryUser(QStringList _userList)
{
//    QCompleter *completer = new QCompleter(wordList, this);
//    completer->setCaseSensitivity(Qt::CaseInsensitive);
//    lineEdit->setCompleter(completer);
}

