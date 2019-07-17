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
/* 该类主要实现对.ini文件的无差别配置，针对单一定义的key/value类型的配置变量进行列表与配置
 * KEY从database中获取，key的属性显示属性也在database中体现，key对应的value从.ini文件中获取。
 * 定义的值在配置类中无特殊含义。
 * 更新完之后，重新让机器类以及机头类从.ini文件中加载数据。
 */
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
signals:
    void UpdateDataHeadRequest();

};

#endif // CFGMACHSETTINGS_H
