#ifndef USER_H
#define USER_H

#include <QObject>
#include <QtSql>

#define USER_SN     0
#define USER_NAME   1
#define USER_PSW    2
#define USER_LV     3
#define USER_PACT   4
#define USER_PITEM  5
#define USER_PLEVEL 6

#define PLV_CHG     0x1
#define PLV_ADD     0x2
#define PLV_DEL     0x4

#define PLV_STURFF  PLV_CHG
#define PLV_CAPTAIN PLV_CHG|PLV_ADD
#define PLV_MANAGER PLV_CHG|PLV_ADD|PLV_DEL

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    ~User();
signals:
public slots:

private:
    bool    userIsChecked;
    int     userSN;
    QString userName;
    QString userPSW_org;
    QString userPSW_md5;
    int     userLevel;
    bool    userPrimWrite;
    bool    userPrimRead;
    bool    userPrimAdd;
    bool    userPrimDelete;
    QString userRoleName;
//    int     userPrimAct;//允许动作
//    int     userPrimItem;//可查看栏目
//    int     userPrimLevel;//可查看对象
//    QString userPrimItemStr;
private:
    QString QueryItemInTableByKey(QString _item,QString _table,QString _key,QString _value);

public:
    QMap<QString, int> userPrimRoleMap;

    bool    GetUserIsChecked();
    void    SetUserIsChecked(bool _checked);
    int     GetUserSN(void);
    void    SetUserSN(int _sn);
    QString GetUserName();
    void    SetUserName(QString _name);
    QString GetUserPSW_org();
    void    SetUserPSW_org(QString _psw);
    QString GetUserPSW_MD5();
    void    SetUserPSW_MD5(QString _psw);
    int     GetUserLevel();
    void    SetUserLevel(int _level);
    QString GetUserRoleName();
    bool    GetUserPrimWrite();
    bool    GetUserPrimRead();
    bool    GetUserPrimAdd();
    bool    GetUserPrimDelete();

    void    SetUserRoleName(QString _name);
    void    SetUserPrimWrite(bool _prim);
    void    SetUserPrimRead(bool _prim);
    void    SetUserPrimAdd(bool _prim);
    void    SetUserPrimDelete(bool _prim);

    QMap<QString, int> GetUserPrimRoleMap();
//    QString GetUserPrimItemStr();
//    QString GetUserPrimLevelStr();
public:
    void    CheckUserMatching();
};

#endif // USER_H
