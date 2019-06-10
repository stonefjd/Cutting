#include "user.h"
#include <QDebug>
User::User(QObject *parent) : QObject(parent)
{
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
    db.open();
}
//---get and set code
bool User::GetUserIsChecked()
{
    return this->userIsChecked;
}
void User::SetUserIsChecked(bool _checked)
{
    this->userIsChecked = _checked;
}

void User::SetUserSN(int _sn)
{
    this->userSN = _sn;
}
void User::SetUserPSW(QString _psw)
{
    this->userPSW_org = _psw;
}
QString User::GetUserPrimItemStr()
{
    QString temp = nullptr;
    (userPrimItem & 0x1<<0) !=0?temp.append("userSN,"):temp.append("");
    (userPrimItem & 0x1<<1) !=0?temp.append("userName,"):temp.append("");
    (userPrimItem & 0x1<<2) !=0?temp.append("userPasswordMD5,"):temp.append("");
    (userPrimItem & 0x1<<3) !=0?temp.append("userLevel,"):temp.append("");
    (userPrimItem & 0x1<<4) !=0?temp.append("userPrimAct,"):temp.append("");
    (userPrimItem & 0x1<<5) !=0?temp.append("userPrimItem,"):temp.append("");
    (userPrimItem & 0x1<<6) !=0?temp.append("userPrimLevel,"):temp.append("");
    if(*(temp.end()-1) == ',')
    {
        temp = temp.remove(temp.length()-1,1);
    }
    return temp;
}
QString User::GetUserPrimLevelStr()
{
    QString temp = nullptr;
    (userPrimLevel & 0x1<<0) !=0?temp.append(" userSN ='"    +QString::number(userSN)    +"' OR"):temp.append("");
    (userPrimLevel & 0x1<<1) !=0?temp.append(" userLevel >" +QString::number(userLevel) +" OR"):temp.append("");
    if(temp != nullptr)
    {
        temp = "WHERE" + temp;
        temp = temp.remove(temp.length()-3,3);
    }
    return temp;
}
//----function code
void User::CheckUserMatching(void)
{
    this->userPSW_md5 = QCryptographicHash::hash(this->userPSW_org.toLatin1(),QCryptographicHash::Md5).toHex();

    qDebug()<<db.tables();
    if(PasswordMaching(this->userSN,this->userPSW_md5))
    {
        this->userIsChecked = true;
        SetHistoryUser(userSN);
    }
    else
    {
        this->userIsChecked = false;
    }
//    db.close();
}
void User::SetHistoryUser(int _sn)
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    QSqlQuery query;
    query.prepare("INSERT INTO historyTable VALUES ("+QString::number(_sn)+",'"+str+"','')");
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
}
QStringList User::GetHistoryUser(QString _arg)//get history from query match
{
    QStringList _userList;

    QSqlQuery query;
//    query.prepare("INSERT INTO historyTable VALUES ("+QString::number(100)+",'"+"ABC"+"','')");
    query.prepare( "SELECT * FROM historyTable WHERE userSN LIKE '"+_arg+"%'");
    if(!query.exec())
    {
        qDebug() << query.lastError();
    }
    query.first();
    while(!query.value(0).isNull())
    {
        QString str = query.value(0).toString();
        bool isRepeat = false;
        for(int i=0;i<_userList.count();i++)
        {
            if(_userList.at(i)==str)
                isRepeat = true;
        }
        if(isRepeat == false)
            _userList.append(str);
        query.next();
    }
//    _userList.append()
    qDebug()<<_userList;
    return _userList;
}
//----private code
bool User::PasswordMaching(int _sn,QString _pswd)
{
    bool ret = false;
    QSqlQuery query;
    query.prepare( "SELECT * FROM userTable WHERE userSN = '" + QString::number(_sn)+"'");
    if(!query.exec())
    {
        qDebug() << query.lastError();
    }
    else
    {
        query.first();
        qDebug()<<query.value(USER_PSW).toString();
        if(query.value(USER_PSW).toString() == _pswd)
        {
            ret = true;
            qDebug()<<"identified";
            this->userLevel     = query.value(USER_LV).toInt();
            this->userPrimAct   = query.value(USER_PACT).toInt();
            this->userPrimItem  = query.value(USER_PITEM).toInt();
            this->userPrimLevel = query.value(USER_PLEVEL).toInt();
        }
        else
            qDebug()<<"passwordWrong";
    }
    return ret;
}