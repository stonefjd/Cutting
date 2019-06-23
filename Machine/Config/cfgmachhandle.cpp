#include "cfgmachhandle.h"

CfgMachHandle::CfgMachHandle(QObject *parent) : QObject(parent)
{
    mConfig.GetMachineBaseInfo();
    hConfig.GetHeadInfo(0);


}

void CfgMachHandle::ShowSettings(UserHandle *_userHandle)
{
    //new UI
    UI_cfgMachSetting = new CfgMachSettings;
    UI_cfgMachSetting->SetCfgMach(&mConfig);
    UI_cfgMachSetting->SetCfgHead(&hConfig);
    UI_cfgMachSetting->SetMachUser(_userHandle);
    //load data from param
    UI_cfgMachSetting->LoadData();

    //settings
    UI_cfgMachSetting->setModal(true);
    UI_cfgMachSetting->exec();

    //update data

    //delete UI
    delete UI_cfgMachSetting;
}
void CfgMachHandle::UpdateConfigMaxPluse(double _xPos, double _yPos)
{
//    mConfig.UpdateMachRunMax(static_cast<int>(_xPos),static_cast<int>(_yPos));
    hConfig.UpdateHeadMaxPluse(static_cast<int>(_xPos),static_cast<int>(_yPos),0);
//    hConfig.at(0)->UpdateHeadCutLimit(static_cast<int>(_xPos),static_cast<int>(_yPos),0);
}
