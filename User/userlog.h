#ifndef USERLOG_H
#define USERLOG_H

#include <QDialog>
#include <QtSql>
#include "user.h"


namespace Ui {
class UserLog;
}

class UserLog : public QDialog
{
    Q_OBJECT

public:
    explicit UserLog(QWidget *parent = nullptr);
    ~UserLog();
private:
    Ui::UserLog *ui;

    User *user;
//    QSqlDatabase db;

public:
    void SetUser(User *_user);

private slots:
    void on_buttonBox_accepted();
};

#endif // USERLOG_H
