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
        aConfigList.append(tempApron);
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
    connect(UI_cfgMachSettings,SIGNAL(UpdateDataHeadRequest()),this,SLOT(SlotUpdateDataHeadRequest()));
    //load data from param
    UI_cfgMachSettings->LoadData();
    //settings
    UI_cfgMachSettings->setModal(true);
    UI_cfgMachSettings->exec();
    //disconnect signal to updata data
    disconnect(UI_cfgMachSettings,SIGNAL(UpdateDataHeadRequest()),this,SLOT(SlotUpdateDataHeadRequest()));
    //delete UI
    delete UI_cfgMachSettings;
}
void CfgMachHandle::ShowKnifeManager(UserHandle *_userHandle)
{
    UI_cfgKnifeManager = new CfgKnifeManager;
    UI_cfgKnifeManager->SetCfgHead(hConfig);
    UI_cfgKnifeManager->SetCfgLib(&lConfig);
    UI_cfgKnifeManager->SetCfgApron(&aConfigList);
    UI_cfgKnifeManager->SetCfgUser(_userHandle);

    //connect signal for the data out
    connect(UI_cfgKnifeManager,SIGNAL(UpdateDataApronRequest()),this,SLOT(SlotUpdateDataApronRequest()));
    //load data from param
    UI_cfgKnifeManager->LoadData();
    //settings
    UI_cfgKnifeManager->setModal(true);
    UI_cfgKnifeManager->exec();
    //disconnect signal to updata data
    disconnect(UI_cfgKnifeManager,SIGNAL(UpdateDataApronRequest()),this,SLOT(SlotUpdateDataApronRequest()));
    //delete UI
    delete UI_cfgKnifeManager;
}
CfgMachSettings* CfgMachHandle::GetCfgMachSettings()
{
    return this->UI_cfgMachSettings;
}
CfgKnifeManager* CfgMachHandle::GetCfgKnifeManager()
{
    return this->UI_cfgKnifeManager;
}

CfgHead* CfgMachHandle::GetHConfig()
{
    return this->hConfig;
}
void CfgMachHandle::InitCommunicate()
{
    //机头参数发出
    emit UpdateDataHead(hConfig->GetCfgHeadData());
    //机座参数发出
    QList<CfgApron_T> aCfgDataList;
    for(int i=0;i<aConfigList.count();i++)
    {
        aCfgDataList.append(aConfigList.at(i)->GetCfgAprondData());
    }
    emit UpdateDataApron(aCfgDataList);
}
//void CfgMachHandle::UpdateConfigMaxPluse(double _xPos, double _yPos)
//{
//    //从机器数据中更新到配置数据中
//    hConfig->UpdateHeadMaxPluse(static_cast<int>(_xPos),static_cast<int>(_yPos),0);

//    //从配置数据中更新到显示数据中
//    emit UpdateDataHead(hConfig->GetCfgHeadData());
//}
void CfgMachHandle::SlotUpdateDataHeadPosMax(QPointF _point)
{
    qDebug()<<"update";
    hConfig->UpdateDataPosMax(_point,0);
    emit UpdateDataHead(hConfig->GetCfgHeadData());
}
void CfgMachHandle::SlotUpdateDataHeadRequest()
{
    emit UpdateDataHead(hConfig->GetCfgHeadData());
}
void CfgMachHandle::SlotUpdateDataApronRequest()
{
    //机座参数发出
    QList<CfgApron_T> aCfgDataList;
    for(int i=0;i<aConfigList.count();i++)
    {
        aCfgDataList.append(aConfigList.at(i)->GetCfgAprondData());
    }
    emit UpdateDataApron(aCfgDataList);
}
