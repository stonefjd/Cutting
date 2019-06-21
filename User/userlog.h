#ifndef USERLOG_H
#define USERLOG_H

#include <QDialog>
#include <QtSql>
#include <QListWidget>
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
    QSqlDatabase db;
    User *user;
    QCompleter *completer;
public:
    void SetUser(User *_user);
private:
    QStringList GetHistoryUserList(QString _arg);
    QString     QueryItemInTableByKey(QString _item,QString _table,QString _key,QString _value);
    void        CheckUserMatching(void);

private slots:
    void on_buttonBox_accepted();
};

#endif // USERLOG_H
