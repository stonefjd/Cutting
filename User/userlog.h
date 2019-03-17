#ifndef USERLOG_H
#define USERLOG_H

#include <QDialog>
#include <QtSql>

#define USER_ID_C   0
#define USER_SN_C   1
#define USER_PSW_C  2
#define USER_RLV_C  3

namespace Ui {
class UserLog;
}

class UserLog : public QDialog
{
    Q_OBJECT

public:
    explicit UserLog(QWidget *parent = nullptr);
    bool userIsChecked();
    ~UserLog();

private:
    Ui::UserLog *ui;

    QSqlDatabase db;
    bool userIsIdentified;
    int userSN;
    QString userPSW_org;
    QString userPSW_md5;

    void userOpenDataBase();
    bool userCheckCollection(int _sn,QString _pswd);

};

#endif // USERLOG_H
