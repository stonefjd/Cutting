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

    User *user;
    QCompleter *completer;
//    QListWidget* listHistory;
//    QSqlDatabase db;
private:
    void DisplayHistoryUser(QStringList _userList);

public:
    void SetUser(User *_user);

private slots:
    void on_buttonBox_accepted();
    void on_lineEditSN_textEdited(const QString &arg1);
};

#endif // USERLOG_H
