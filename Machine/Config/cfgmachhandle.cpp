#include "cfgmachhandle.h"

CfgMachHandle::CfgMachHandle(QObject *parent) : QObject(parent)
{
    cfgMach.GetMachineBaseInfo();
    cfgHead.GetHeadInfo();
    lConfig.ReadCutToolLib();
    for(int i=0;i<MAX_TOOLAPRON;i++)
    {
        CfgApron *tempApron = new CfgApron;
        tempApron->GetApronInfo(i);

        CfgKnife *tmpKnife = lConfig.GetKnifeByGuid(tempApron->GetKnifeGuid());
        tempApron->SetKnife(tmpKnife);
        cfgApronList.append(tempApron);
    }
    //add knife paramater in lib by GUID
}

void CfgMachHandle::ShowMachSettings(UserHandle *_userHandle)
{
    //new UI
    UI_cfgMachSettings = new CfgMachSettings;

    UI_cfgMachSettings->SetCfgUser(_userHandle);
    UI_cfgMachSettings->SetCfgMach(&cfgMach);
    UI_cfgMachSettings->SetCfgHead(&cfgHead);
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
    UI_cfgKnifeManager->SetCfgHead(&cfgHead);
    UI_cfgKnifeManager->SetCfgLib(&lConfig);
    UI_cfgKnifeManager->SetCfgApron(&cfgApronList);
    UI_cfgKnifeManager->SetCfgUser(_userHandle);

    //connect signal for the data out
    connect(UI_cfgKnifeManager,SIGNAL(UpdateDataApronRequest()),            this,SLOT(SlotUpdateDataApronRequest()));
    connect(UI_cfgKnifeManager,SIGNAL(EnterOprtToolPosCalibRequest(int,double)),   this,SLOT(SlotEnterOprtToolPosCalibRequest(int,double)));
    //load data from param
    UI_cfgKnifeManager->LoadData();
    //settings
    UI_cfgKnifeManager->setModal(true);
    UI_cfgKnifeManager->exec();
    //disconnect signal to updata data
    disconnect(UI_cfgKnifeManager,SIGNAL(UpdateDataApronRequest()),         this,SLOT(SlotUpdateDataApronRequest()));
    disconnect(UI_cfgKnifeManager,SIGNAL(EnterOprtToolPosCalibRequest(int,double)),this,SLOT(SlotEnterOprtToolPosCalibRequest(int,double)));
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

CfgHead* CfgMachHandle::GetCfgHead()
{
    return &this->cfgHead;
}
QList<CfgApron*>*   CfgMachHandle::GetCfgArponList()
{
    return &this->cfgApronList;
}
//void CfgMachHandle::InitCommunicate()
//{
//    //机头参数发出
////    emit UpdateDataHead(cfgHead->GetCfgHeadData());
//    //机座参数发出
//    QList<CfgApron_T> aCfgDataList;
//    for(int i=0;i<cfgApronList.count();i++)
//    {
//        aCfgDataList.append(cfgApronList.at(i)->GetCfgAprondData());
//    }
//    emit UpdateDataApron(aCfgDataList);
//}
void CfgMachHandle::SlotUpdateDataHeadPosMax(QPointF _point)
{
    qDebug()<<"update";
    cfgHead.UpdateDataPosMax(_point,0);
//    emit UpdateDataHead(cfgHead->GetCfgHeadData());
}
void CfgMachHandle::SlotUpdateDataHeadRequest()
{
//    emit UpdateDataHead(cfgHead->GetCfgHeadData());
}
void CfgMachHandle::SlotUpdateDataApronRequest()
{
    //机座参数发出
//    QList<CfgApron_T> aCfgDataList;
//    for(int i=0;i<cfgApronList.count();i++)
//    {
//        aCfgDataList.append(cfgApronList.at(i)->GetCfgAprondData());
//    }
//    emit UpdateDataApron(aCfgDataList);
}
void CfgMachHandle::SlotUpdateDataHeadPosRt(QPointF posRT)
{
//    cfgHead->SetPosRt(posRT);
}
void CfgMachHandle::SlotEnterOprtToolPosCalibRequest(int id, double deep)
{
    emit EnterOprtToolPosCalib(id,deep);
}
