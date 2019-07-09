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

//    for(int i=0;i<hConfig.aConfig.count();i++)
//    {
//        int guid    = hConfig.aConfig.at(i)->GetKnifeGuid();
//        short toolId  = GUID2CUTTOOLID(guid);
//        short knifeId = GUID2KNIFEID(guid);
//        CfgKnife *tmpKnife = lConfig.GetCutToolById(toolId)->GetKnifeById(knifeId);
//        hConfig.aConfig.at(i)->SetKnife(tmpKnife);
//    }
}

void CfgMachHandle::ShowMachSettings(UserHandle *_userHandle)
{
    //new UI
    UI_cfgMachSettings = new CfgMachSettings;
    UI_cfgMachSettings->SetCfgUser(_userHandle);
    UI_cfgMachSettings->SetCfgMach(mConfig);
    UI_cfgMachSettings->SetCfgHead(hConfig);
    //load data from param
    UI_cfgMachSettings->LoadData();

    //settings
    UI_cfgMachSettings->setModal(true);
    UI_cfgMachSettings->exec();

    //update data

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

    UI_cfgKnifeManager->LoadData();

    UI_cfgKnifeManager->setModal(true);
    UI_cfgKnifeManager->exec();

    delete UI_cfgKnifeManager;

}
void CfgMachHandle::UpdateConfigMaxPluse(double _xPos, double _yPos)
{
//    mConfig.UpdateMachRunMax(static_cast<int>(_xPos),static_cast<int>(_yPos));
    hConfig->UpdateHeadMaxPluse(static_cast<int>(_xPos),static_cast<int>(_yPos),0);
//    hConfig.at(0)->UpdateHeadCutLimit(static_cast<int>(_xPos),static_cast<int>(_yPos),0);
}
CfgHead* CfgMachHandle::GetHConfig()
{
    return this->hConfig;
}
