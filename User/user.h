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
signals:
public slots:

private:
    bool    userIsChecked;
    int     userSN;
    QString userPSW_org;
    QString userPSW_md5;
    int     userLevel;
    int     userPrimAct;//允许动作
    int     userPrimItem;//可查看栏目
    int     userPrimLevel;//可查看对象

    QSqlDatabase db;
    QString userPrimItemStr;
private:
    bool    UserMaching(int _sn,QString _pswd);
public:
    bool    GetUserIsChecked();
    void    SetUserIsChecked(bool _checked);
    void    SetUserSN(int _sn);
    void    SetUserPSW(QString _psw);
    QString GetUserPrimItemStr();
    QString GetUserPrimLevelStr();
    void    SetHistoryUser(int _sn);
    int     GetHistoryUser();
public:
    void    CheckUserMatching();
};

#endif // USER_H
