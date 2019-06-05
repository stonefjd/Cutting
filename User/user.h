#ifndef USER_H
#define USER_H

#include <QObject>
#include <User/userlog.h>
#include <User/usermanager.h>
#include <QtSql>
class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);

signals:

public slots:
private:
    UserLog     *UI_userLog;
    UserManager *UI_userManager;
private:
    QSqlDatabase db;

    bool    userIsChecked;
    int     userSN;
    QString userPSW_org;
    QString userPSW_md5;
    int     userPrimLevel;
public:
    bool    UserIsChecked();
    bool    UserMaching(int _sn,QString _pswd);

};

#endif // USER_H
