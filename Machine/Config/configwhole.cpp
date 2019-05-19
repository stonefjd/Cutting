#include "configwhole.h"

ConfigWhole::ConfigWhole(QWidget *parent) : QWidget(parent)
{
    mConfig.GetMachineBaseInfo();
//    headConfig.Get
    for(int _headCnt=0;_headCnt<mConfig.GetMachHeadCount();_headCnt++)
    {
        ConfigHead *head = new ConfigHead;
        head->GetHeadInfo(_headCnt);
        hConfig.append(head);
    }
}

void ConfigWhole::UpdateConfigMaxPluse(double _xPos, double _yPos)
{
//    mConfig.UpdateMachRunMax(static_cast<int>(_xPos),static_cast<int>(_yPos));
    hConfig.at(0)->UpdateHeadMaxPluse(static_cast<int>(_xPos),static_cast<int>(_yPos),0);
//    hConfig.at(0)->UpdateHeadCutLimit(static_cast<int>(_xPos),static_cast<int>(_yPos),0);
}
