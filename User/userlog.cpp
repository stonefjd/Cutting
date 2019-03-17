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
    QValidator* validator = new QIntValidator(0,99999,this);
    ui->lineEditSN->setValidator(validator);

    this->userIsIdentified = false;

    this->setModal(true);
    int ret = this->exec();

    if(ret)
    {
        this->userSN = ui->lineEditSN->text().toInt();
        this->userPSW_org = ui->lineEditPsw->text();
        this->userPSW_md5 = QCryptographicHash::hash(this->userPSW_org.toLatin1(),
                                                 QCryptographicHash::Md5).toHex();
        qDebug()<<"ORG:"+ this->userPSW_org;
        qDebug()<<"MD5:"+ this->userPSW_md5;
        if(userCheckCollection(this->userSN,this->userPSW_md5))
        {
            this->userIsIdentified = true;
        }
        else
        {
            this->userIsIdentified = false;
        }
    }
}
bool UserLog::userIsChecked()
{
    return this->userIsIdentified;
}
bool UserLog::userCheckCollection(int _sn,QString _pswd)
{
    bool ret = false;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("PGM");
    db.setDatabaseName("MyDataBase.db");
    db.setUserName("STONE");
    db.setPassword("12345678");
    db.open();
    qDebug()<<db.tables();

    QSqlQuery query;
    query.prepare( "SELECT * FROM userTable WHERE userSN = " + QString::number(_sn));
    if(!query.exec())
        qDebug() << query.lastError();
    else
    {
        query.first();
        qDebug()<<query.value(USER_PSW_C).toString();
        if(query.value(USER_PSW_C).toString() == _pswd)
        {
            ret = true;
            qDebug()<<"identified";
        }
        else
            qDebug()<<"passwordWrong";
    }
    db.close();
    return ret;
}

UserLog::~UserLog()
{
    delete ui;
}
