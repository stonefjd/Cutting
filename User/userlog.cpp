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

    //set up database
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setHostName("PGM");
    db.setDatabaseName("Settings\\MyDataBase.db");
//    db.setUserName("STONE");
//    db.setPassword("12345678");
    db.open();

    this->setWindowTitle(tr("请输入员工工号密码"));
    //limit the ID only for 0-99999
    QValidator* validator = new QIntValidator(0,99999,this);
    ui->lineEditSN->setValidator(validator);
    //query the history user list
    QStringList strList = GetHistoryUserList("");
    completer = new QCompleter(strList, this);
    ui->lineEditSN->setCompleter(completer);
}

void UserLog::SetUser(User *_user)
{
    //create user
    this->user = _user;
}

UserLog::~UserLog()
{
    delete ui;
}

void UserLog::on_buttonBox_accepted()
{
    user->SetUserSN(ui->lineEditSN->text().toInt());
    user->SetUserPSW_org(ui->lineEditPsw->text());
    CheckUserMatching();
}

//----------private
void UserLog::CheckUserMatching(void)
{
    user->SetUserPSW_MD5(QCryptographicHash::hash(user->GetUserPSW_org().toLatin1(),QCryptographicHash::Md5).toHex());
    QString _value = QueryItemInTableByKey("userPasswordMD5","userTable","userSN",QString::number(user->GetUserSN()));
    if(_value == user->GetUserPSW_MD5())
    {
        qDebug()<<"identified";
        user->SetUserName(QueryItemInTableByKey("userName",         "userTable","userSN",QString::number(user->GetUserSN())));
        user->SetUserLevel(QueryItemInTableByKey("userLevel",        "userTable","userSN",QString::number(user->GetUserSN())).toInt());
        user->SetUserRoleName(QueryItemInTableByKey("roleName",         "roleDefTable","roleLevel",QString::number(user->GetUserLevel())));
        user->SetUserPrimWrite(QueryItemInTableByKey("rolePrim_write",   "roleDefTable","roleLevel",QString::number(user->GetUserLevel())).toInt());
        user->SetUserPrimRead(QueryItemInTableByKey("rolePrim_read",    "roleDefTable","roleLevel",QString::number(user->GetUserLevel())).toInt());
        user->SetUserPrimAdd(QueryItemInTableByKey("rolePrim_add",     "roleDefTable","roleLevel",QString::number(user->GetUserLevel())).toInt());
        user->SetUserPrimDelete(QueryItemInTableByKey("rolePrim_delete",  "roleDefTable","roleLevel",QString::number(user->GetUserLevel())).toInt());
        user->SetUserIsChecked(true);
        QSqlQuery query;
        query.prepare("SELECT roleLevel,roleName FROM roleDefTable WHERE roleLevel > " +QString::number(user->GetUserLevel()));
        if(!query.exec())
        {
            qDebug() << query.lastError();
        }
        while(query.next())
        {
            int roleLevel = query.value("roleLevel").toInt();
            QString roleName = query.value("roleName").toString();
            user->userPrimRoleMap.insert(roleName, roleLevel);
        }
        QDateTime time = QDateTime::currentDateTime();
        QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");

        query.prepare("INSERT INTO historyTable VALUES ("+QString::number(user->GetUserSN())+",'"+user->GetUserName()+"','"+str+"','')");
        if(!query.exec())
        {
            qDebug()<<query.lastError();
        }
    }
    else
    {
        user->SetUserIsChecked(false);
    }
}
QStringList UserLog::GetHistoryUserList(QString _arg)//get history from query match
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
QString UserLog::QueryItemInTableByKey(QString _item,QString _table,QString _key,QString _value)
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
