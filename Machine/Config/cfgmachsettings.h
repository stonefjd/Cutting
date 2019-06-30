#ifndef CFGMACHSETTINGS_H
#define CFGMACHSETTINGS_H

#include <QDialog>
#include <QFont>
#include <QtSql>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include "cfgbasedefine.h"
#include "cfgmach.h"
#include "cfghead.h"
#include "cfglib.h"
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
    CfgLib  *cLib;
    QString cPath;
    QSqlDatabase db;
    UserHandle *userHandle;

public:
    void SetCfgMach(CfgMach *_cMach);
    void SetCfgHead(CfgHead *_cHead);
    void SetCfgUser(UserHandle *_userHandle);
    void LoadData();
private slots:
    void SlotLineEditTextChanged(const QString &text);
    void SlotComboBoxCurrentIndexChanged(int index);
    void SlotBtnOkClicked();
    void SlotBtnApplyClicked();
    void SlotBtnCancleClicked();
};

#endif // CFGMACHSETTINGS_H
