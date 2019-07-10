#include "cfgmachhandle.h"

CfgMachHandle::CfgMachHandle(QObject *parent) : QObject(parent)
{
    mConfig->GetMachineBaseInfo();
    hConfig->GetHeadInfo();
    lConfig.ReadCutToolLib();
    for(int i=0;i<MAX_TOOLAPRON;i++)
    {
        CfgApron *tempApron = new CfgApron;
        tempApron->GetApronInfo(i);

        CfgKnife *tmpKnife = lConfig.GetKnifeByGuid(tempApron->GetKnifeGuid());
        tempApron->SetKnife(tmpKnife);
        aConfig.append(tempApron);
    }
    //add knife paramater in lib by GUID
}

void CfgMachHandle::ShowMachSettings(UserHandle *_userHandle)
{
    //new UI
    UI_cfgMachSettings = new CfgMachSettings;

    UI_cfgMachSettings->SetCfgUser(_userHandle);
    UI_cfgMachSettings->SetCfgMach(mConfig);
    UI_cfgMachSettings->SetCfgHead(hConfig);
    //connect signal for the data out
    connect(UI_cfgMachSettings,SIGNAL(UpdateDataHead()),this,SLOT(SlotUpdateDataHead()));
    //load data from param
    UI_cfgMachSettings->LoadData();
    //settings
    UI_cfgMachSettings->setModal(true);
    UI_cfgMachSettings->exec();
    //disconnect signal to updata data
    disconnect(UI_cfgMachSettings,SIGNAL(UpdateDataHead()),this,SLOT(SlotUpdateDataHead()));
    //delete UI
    delete UI_cfgMachSettings;
}
void CfgMachHandle::ShowKnifeManager(UserHandle *_userHandle)
{
    UI_cfgKnifeManager = new CfgKnifeManager;
    UI_cfgKnifeManager->SetCfgHead(hConfig);
    UI_cfgKnifeManager->SetCfgLib(&lConfig);
    UI_cfgKnifeManager->SetCfgApron(&aConfig);
    UI_cfgKnifeManager->SetCfgUser(_userHandle);

    //connect signal for the data out
    connect(UI_cfgKnifeManager,SIGNAL(UpdateDataApron()),this,SLOT(SlotUpdateDataApron()));
    //load data from param
    UI_cfgKnifeManager->LoadData();
    //settings
    UI_cfgKnifeManager->setModal(true);
    UI_cfgKnifeManager->exec();
    //disconnect signal to updata data
    disconnect(UI_cfgKnifeManager,SIGNAL(UpdateDataApron()),this,SLOT(SlotUpdateDataApron()));
    //delete UI
    delete UI_cfgKnifeManager;
}
CfgMachSettings* CfgMachHandle::GetCfgMachSettings()
{
    return this->UI_cfgMachSettings;
}

CfgHead* CfgMachHandle::GetHConfig()
{
    return this->hConfig;
}
void CfgMachHandle::InitCommunicate()
{
    //机头参数发出
    emit UpdateDataHead(hConfig->GetPosOrg(),hConfig->GetPosLmt(),hConfig->GetPosMax(),hConfig->GetPosToPulseScale(),hConfig->GetRealToCutScale());
    //机座参数发出
    emit UpdateDataApron(aConfig);
}
void CfgMachHandle::UpdateConfigMaxPluse(double _xPos, double _yPos)
{
    //从机器数据中更新到配置数据中
    hConfig->UpdateHeadMaxPluse(static_cast<int>(_xPos),static_cast<int>(_yPos),0);
    //从配置数据中更新到显示数据中
    emit UpdateDataHead(hConfig->GetPosOrg(),hConfig->GetPosLmt(),hConfig->GetPosMax(),hConfig->GetPosToPulseScale(),hConfig->GetRealToCutScale());
}
void CfgMachHandle::SlotUpdateDataHead()
{
    emit UpdateDataHead(hConfig->GetPosOrg(),hConfig->GetPosLmt(),hConfig->GetPosMax(),hConfig->GetPosToPulseScale(),hConfig->GetRealToCutScale());
}
void CfgMachHandle::SlotUpdateDataApron()
{
    emit UpdateDataApron(aConfig);
}
