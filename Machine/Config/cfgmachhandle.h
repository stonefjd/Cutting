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

    CfgMach *mConfig = new CfgMach;
    CfgHead *hConfig = new CfgHead;
    QList<CfgApron*> aConfigList;
    CfgLib  lConfig;
private:
    CfgMachSettings *UI_cfgMachSettings;
    CfgKnifeManager *UI_cfgKnifeManager;

public:
    void ShowMachSettings(UserHandle *_userHandle);
    void ShowKnifeManager(UserHandle *_userHandle);

    CfgMachSettings* GetCfgMachSettings();
    CfgHead *GetHConfig();

    void InitCommunicate();
signals:
    //逻辑原点，逻辑最大切割点，全局最大范围，每毫米脉冲数，实际切割&显示缩放比
    void UpdateDataHead(CfgHead_T _headData);
    void UpdateDataApron(QList<CfgApron_T> _aConfig);
public slots:
    void UpdateConfigMaxPluse(double _xPos, double _yPos);
    void SlotUpdateDataHeadRequest();
    void SlotUpdateDataApronRequest();

};

#endif // CFGMACHHANDLE_H
