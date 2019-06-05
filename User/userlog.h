#ifndef USERLOG_H
#define USERLOG_H

#include <QDialog>
#include <QtSql>

#define USER_ID_C   0
#define USER_SN_C   1
#define USER_PSW_C  2
#define USER_PLV_C  3

#define PLV_CHG     0x1
#define PLV_ADD     0x2
#define PLV_DEL     0x4

#define PLV_STURFF  PLV_CHG
#define PLV_CAPTAIN PLV_CHG|PLV_ADD
#define PLV_MANAGER PLV_CHG|PLV_ADD|PLV_DEL


namespace Ui {
class UserLog;
}

class UserLog : public QDialog
{
    Q_OBJECT

public:
    explicit UserLog(QWidget *parent = nullptr);
    ~UserLog();
    QString GetLineEditSN(void);
    QString GetLineEditPSW(void);
private:
    Ui::UserLog *ui;

    QSqlDatabase db;




};

#endif // USERLOG_H
