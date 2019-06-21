#include "user.h"
#include <QDebug>
User::User(QObject *parent) : QObject(parent)
{
    this->userIsChecked = false;
    this->userSN        = 0;
    this->userPSW_org   = nullptr;
    this->userPSW_md5   = nullptr;
}
User::~User()
{
//    delete this;
}
//---get and set code
bool User::GetUserIsChecked()
{
    return userIsChecked;
}
void User::SetUserIsChecked(bool _checked)
{
    userIsChecked = _checked;
}
int User::GetUserSN()
{
    return userSN;
}
void User::SetUserSN(int _sn)
{
    userSN = _sn;
}
QString User::GetUserName()
{
    return userName;
}
void User::SetUserName(QString _name)
{
    userName = _name;
}
QString User::GetUserPSW_org()
{
    return userPSW_org;
}
void User::SetUserPSW_org(QString _psw)
{
    userPSW_org = _psw;
}
QString User::GetUserPSW_MD5()
{
    return userPSW_md5;
}
void User::SetUserPSW_MD5(QString _psw)
{
    userPSW_md5 = _psw;
}
int User::GetUserLevel()
{
    return userLevel;
}
void User::SetUserLevel(int _level)
{
    userLevel = _level;
}

QString User::GetUserRoleName()
{
    return userRoleName;
}
void User::SetUserRoleName(QString _name)
{
    userRoleName = _name;
}
bool User::GetUserPrimWrite()
{
    return userPrimWrite;
}
void User::SetUserPrimWrite(bool _prim)
{
    userPrimWrite = _prim;
}
bool User::GetUserPrimRead()
{
    return userPrimRead;
}
void User::SetUserPrimRead(bool _prim)
{
    userPrimRead = _prim;
}
bool User::GetUserPrimAdd()
{
    return userPrimAdd;
}
void User::SetUserPrimAdd(bool _prim)
{
    userPrimAdd = _prim;
}
bool User::GetUserPrimDelete()
{
    return userPrimDelete;
}
void User::SetUserPrimDelete(bool _prim)
{
    userPrimDelete = _prim;
}




QMap<QString, int> User::GetUserPrimRoleMap()
{
    return this->userPrimRoleMap;
}
//----function code



//----private code


