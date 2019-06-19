#include "cfgmachhandle.h"

CfgMachHandle::CfgMachHandle(QObject *parent) : QObject(parent)
{
    mConfig.GetMachineBaseInfo();
    hConfig.GetHeadInfo(0);
}
void CfgMachHandle::UpdateConfigMaxPluse(double _xPos, double _yPos)
{
//    mConfig.UpdateMachRunMax(static_cast<int>(_xPos),static_cast<int>(_yPos));
    hConfig.UpdateHeadMaxPluse(static_cast<int>(_xPos),static_cast<int>(_yPos),0);
//    hConfig.at(0)->UpdateHeadCutLimit(static_cast<int>(_xPos),static_cast<int>(_yPos),0);
}
