#ifndef USERHANDLE_H
#define USERHANDLE_H

#include <QObject>
#include "user.h"
#include "userlog.h"
#include "usermanager.h"
class UserHandle : public QObject
{
    Q_OBJECT
public:
    explicit UserHandle(QObject *parent = nullptr);

signals:

public slots:

private:
    UserLog     *UI_userLog;
    UserManager *UI_userManager;
    User        user;
public:

public:
    bool GetUserChecked();
    void ShowManagerMent();
    User* GetUser();
};

#endif // USERHANDLE_H
