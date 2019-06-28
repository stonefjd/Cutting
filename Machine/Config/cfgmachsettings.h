#ifndef CFGMACHSETTINGS_H
#define CFGMACHSETTINGS_H

#include <QDialog>
#include <QFont>
#include <QtSql>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include "cfgmach.h"
#include "cfghead.h"
#include "User/userhandle.h"
namespace Ui {
class CfgMachSettings;
}

class CfgMachSettings : public QDialog
{
    Q_OBJECT

public:
    explicit CfgMachSettings(QWidget *parent = nullptr);
    ~CfgMachSettings();

private:
    Ui::CfgMachSettings *ui;

private:
    CfgMach *cMach;
    CfgHead *cHead;
    QString cPath;
    QSqlDatabase db;
    UserHandle *userHandle;
    bool WritePrivateProfileString(QString strSect,QString strKey,QString strText,QString strConfigPath);
    bool GetPrivateProfileString(QString strSect,QString strKey,QString *szBuf,QString strConfigPath);

public:
    void SetCfgMach(CfgMach *_cMach);
    void SetCfgHead(CfgHead *_cHead);
    void SetMachUser(UserHandle *_userHandle);
    void LoadData();
private slots:
    void SlotLineEditTextChanged(const QString &text);
    void SlotComboBoxCurrentIndexChanged(int index);
    void SlotBtnOkClicked();
    void SlotBtnApplyClicked();
    void SlotBtnCancleClicked();
};

#endif // CFGMACHSETTINGS_H
