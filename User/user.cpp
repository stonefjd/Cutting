#include "user.h"
#include <QDebug>
User::User(QObject *parent) : QObject(parent)
{
    UI_userManager = new UserManager;
    UI_userLog = new UserLog;

    this->userIsChecked = false;
    this->userSN        = 0;
    this->userPSW_org   = nullptr;
    this->userPSW_md5   = nullptr;
    this->userPrimLevel = 0;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("PGM");
    db.setDatabaseName("MyDataBase.db");
    db.setUserName("STONE");
    db.setPassword("12345678");

    //when new the user,display the UI for user to write
    UI_userLog->setModal(true);
    int ret = UI_userLog->exec();
    if(ret)
    {
        this->userSN = UI_userLog->GetLineEditSN().toInt();
        this->userPSW_org = UI_userLog->GetLineEditPSW();
        qDebug()<<userSN<<' '<<userPSW_org;
        this->userPSW_md5 = QCryptographicHash::hash(this->userPSW_org.toLatin1(),
                                                     QCryptographicHash::Md5).toHex();
        db.open();
        qDebug()<<db.tables();
        if(UserMaching(this->userSN,this->userPSW_md5))
        {
            this->userIsChecked = true;

        }
        else
        {
            this->userIsChecked = false;
        }
        db.close();
    }
}
bool User::UserIsChecked()
{
    return this->userIsChecked;
}

bool User::UserMaching(int _sn,QString _pswd)
{
    bool ret = false;
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
            this->userPrimLevel = query.value(USER_PLV_C).toInt();
        }
        else
            qDebug()<<"passwordWrong";
    }
    return ret;
}
