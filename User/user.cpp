#include "user.h"
#include <QDebug>
User::User(QObject *parent) : QObject(parent)
{
    this->userIsChecked = false;
    this->userSN        = 0;
    this->userPSW_org   = nullptr;
    this->userPSW_md5   = nullptr;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("PGM");
    db.setDatabaseName("MyDataBase.db");
    db.setUserName("STONE");
    db.setPassword("12345678");
    db.open();
}
User::~User()
{
//    delete this;
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
int User::GetUserSN()
{
    return this->userSN;
}
QString User::GetUserName()
{
    return this->userName;
}
void User::SetUserPSW(QString _psw)
{
    this->userPSW_org = _psw;
}
int User::GetUserLevel()
{
    return this->userLevel;
}
QString User::GetUserRoleName()
{
    return this->userRoleName;
}
bool User::GetUserPrimWrite()
{
    return this->userPrimWrite;
}
bool User::GetUserPrimRead()
{
    return this->userPrimRead;
}
bool User::GetUserPrimAdd()
{
    return this->userPrimAdd;
}
bool User::GetUserPrimDelete()
{
    return this->userPrimDelete;
}
QMap<QString, int> User::GetUserPrimRoleMap()
{
    return this->userPrimRoleMap;
}
//QString User::GetUserPrimItemStr()
//{
//    QString temp = nullptr;
//    (userPrimItem & 0x1<<0) !=0?temp.append("userSN,"):temp.append("");
//    (userPrimItem & 0x1<<1) !=0?temp.append("userName,"):temp.append("");
//    (userPrimItem & 0x1<<2) !=0?temp.append("userPasswordMD5,"):temp.append("");
//    (userPrimItem & 0x1<<3) !=0?temp.append("userLevel,"):temp.append("");
//    (userPrimItem & 0x1<<4) !=0?temp.append("userPrimAct,"):temp.append("");
//    (userPrimItem & 0x1<<5) !=0?temp.append("userPrimItem,"):temp.append("");
//    (userPrimItem & 0x1<<6) !=0?temp.append("userPrimLevel,"):temp.append("");
//    if(*(temp.end()-1) == ',')
//    {
//        temp = temp.remove(temp.length()-1,1);
//    }
//    return temp;
//}
//QString User::GetUserPrimLevelStr()
//{
//    QString temp = nullptr;
//    (userPrimLevel & 0x1<<0) !=0?temp.append(" userSN ='"    +QString::number(userSN)    +"' OR"):temp.append("");
//    (userPrimLevel & 0x1<<1) !=0?temp.append(" userLevel >" +QString::number(userLevel) +" OR"):temp.append("");
//    if(temp != nullptr)
//    {
//        temp = "WHERE" + temp;
//        temp = temp.remove(temp.length()-3,3);
//    }
//    return temp;
//}
//----function code
void User::CheckUserMatching(void)
{
    this->userPSW_md5 = QCryptographicHash::hash(this->userPSW_org.toLatin1(),QCryptographicHash::Md5).toHex();
    if(PasswordMaching(this->userSN,this->userPSW_md5))
    {
        this->userIsChecked = true;
        SetHistoryUser();
    }
    else
    {
        this->userIsChecked = false;
    }
//    db.close();
}
void User::SetHistoryUser()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    QSqlQuery query;
    query.prepare("INSERT INTO historyTable VALUES ("+QString::number(this->userSN)+",'"+this->userName+"','"+str+"','')");
    if(!query.exec())
    {
        qDebug()<<query.lastError();
    }
}
QStringList User::GetHistoryUserList(QString _arg)//get history from query match
{
    QStringList _userList;

    QSqlQuery query;
//    query.prepare("INSERT INTO historyTable VALUES ("+QString::number(100)+",'"+"ABC"+"','')");
    query.prepare( "SELECT * FROM historyTable WHERE userSN LIKE '"+_arg+"%'");
    if(!query.exec())
    {
        qDebug() << query.lastError();
    }
//    query.first();
    while(query.next())
    {
        QString str = query.value("userSN").toString();
        bool isRepeat = false;
        for(int i=0;i<_userList.count();i++)
        {
            if(_userList.at(i)==str)
                isRepeat = true;
        }
        if(isRepeat == false)
            _userList.append(str);
    }
    qDebug()<<_userList;
    return _userList;
}
//----private code
bool User::PasswordMaching(int _sn,QString _pswd)
{
    bool ret = false;
    QString _value;
    _value = QueryItemInTableByKey("userPasswordMD5","userTable","userSN",QString::number(_sn));
    if(_value == _pswd)
    {
        ret = true;
        qDebug()<<"identified";
        this->userName      = QueryItemInTableByKey("userName",         "userTable","userSN",QString::number(_sn));
        this->userLevel     = QueryItemInTableByKey("userLevel",        "userTable","userSN",QString::number(_sn)).toInt();
        this->userRoleName  = QueryItemInTableByKey("roleName",         "roleDefTable","roleLevel",QString::number(this->userLevel));
        this->userPrimWrite = QueryItemInTableByKey("rolePrim_write",   "roleDefTable","roleLevel",QString::number(this->userLevel)).toInt();
        this->userPrimRead  = QueryItemInTableByKey("rolePrim_read",    "roleDefTable","roleLevel",QString::number(this->userLevel)).toInt();
        this->userPrimAdd   = QueryItemInTableByKey("rolePrim_add",     "roleDefTable","roleLevel",QString::number(this->userLevel)).toInt();
        this->userPrimDelete= QueryItemInTableByKey("rolePrim_delete",  "roleDefTable","roleLevel",QString::number(this->userLevel)).toInt();
//        this->
        QSqlQuery query;
        query.prepare("SELECT roleLevel,roleName FROM roleDefTable WHERE roleLevel > " +QString::number(this->userLevel));
        if(!query.exec())
        {
            qDebug() << query.lastError();
        }
        while(query.next())
        {
            int roleLevel = query.value("roleLevel").toInt();
            QString roleName = query.value("roleName").toString();
            this->userPrimRoleMap.insert(roleName, roleLevel);
        }
    }
    return ret;
}
QString User::QueryItemInTableByKey(QString _item,QString _table,QString _key,QString _value)
{
    QString _itemValue;
    QSqlQuery query;
    query.prepare("SELECT "+_item+" FROM "+_table+" WHERE "+_key+" = '" +_value+"'");
    if(!query.exec())
    {
        qDebug() << query.lastError();
    }
    else
    {
        query.first();
        _itemValue = query.value(0).toString();
    }
    return _itemValue;
}
