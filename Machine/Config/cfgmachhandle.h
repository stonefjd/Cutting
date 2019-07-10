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
    QList<CfgApron*> aConfig;
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
    void UpdateDataHead(QPointF posOrg,QPointF posLmt,QPointF posMax,QPointF posToPulseScale,QPointF realToCutScale);
    void UpdateDataApron(QList<CfgApron*> _aConfig);
public slots:
    void UpdateConfigMaxPluse(double _xPos, double _yPos);
    void SlotUpdateDataHead();
    void SlotUpdateDataApron();

};

#endif // CFGMACHHANDLE_H
