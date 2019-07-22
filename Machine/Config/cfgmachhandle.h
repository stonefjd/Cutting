#ifndef CFGMACHHANDLE_H
#define CFGMACHHANDLE_H

#include <QObject>
//#include "cfgmach.h"
//#include "cfghead.h"
//#include "cfglib.h"
#include "cfgmachsettings.h"
#include "cfgknifemanager.h"
class CfgMachHandle : public QObject
{
    Q_OBJECT
public:
    explicit CfgMachHandle(QObject *parent = nullptr);
private:
    CfgMach cfgMach;// = new CfgMach;
    CfgHead cfgHead;// = new CfgHead;
    QList<CfgApron*> cfgApronList;
    CfgLib  lConfig;

    CfgMachSettings *UI_cfgMachSettings;
    CfgKnifeManager *UI_cfgKnifeManager;
public:
    void ShowMachSettings(UserHandle *_userHandle);
    void ShowKnifeManager(UserHandle *_userHandle);

    CfgMachSettings*    GetCfgMachSettings();
    CfgKnifeManager*    GetCfgKnifeManager();

    CfgHead*            GetCfgHead();
    QList<CfgApron*>*   GetCfgArponList();
signals:
    //逻辑原点，逻辑最大切割点，全局最大范围，每毫米脉冲数，实际切割&显示缩放比
    void EnterOprtToolPosCalib(int id);
public slots:
    void SlotUpdateDataHeadPosMax();
    void SlotEnterOprtToolPosCalibRequest(int id);

};

#endif // CFGMACHHANDLE_H
