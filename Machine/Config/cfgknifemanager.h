#ifndef CFGKNIFEMANAGER_H
#define CFGKNIFEMANAGER_H

#include <QDialog>
#include <QPushButton>
#include <QButtonGroup>
#include <QGridLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include "cfghead.h"
#include "cfgmach.h"
#include "cfglib.h"
#include "User/userhandle.h"
namespace Ui {
class CfgKnifeManager;
}

class CfgKnifeManager : public QDialog
{
    Q_OBJECT

public:
    explicit CfgKnifeManager(QWidget *parent = nullptr);
    ~CfgKnifeManager();
    void SetCfgHead(CfgHead *_cHead);
    void SetCfgApron(QList<CfgApron*> *_cApron);
    void SetCfgLib(CfgLib *_cLib);

    void SetCfgUser(UserHandle *_userHandle);
    void LoadData();

private:
    Ui::CfgKnifeManager *ui;
    CfgHead *cHead;
    CfgLib  *cLib;
    QList<CfgApron*> *cApron;
    UserHandle *userHandle;
    QList<QComboBox*> cbBoxList;
    QStringList tempKnifeName;

    int tab1Valid = 2;//0:正常 1:未选择刀具 2:无选中
signals:
    void UpdateDataApron();
private slots:
    void SlotBtnGrpClicked(bool _chk);
    void on_btnOK_clicked();
    void on_btnApply_clicked();
    void on_btnCancle_clicked();
};

#endif // CFGKNIFEMANAGER_H
