#include "machine.h"
#include "PhysicalLayer/gts.h"
Machine::Machine(QObject *parent) : QObject(parent)
{
//    this->mFan_1.SetState_FanStop();


//----set the knife of the machine
    sdKnifeConfigLib.ReadConfigFile();
    qDebug()<<sdKnifeConfigLib.GetKnifesCount();

//----InitMachine
    this->MInit();
//------creat the limit State of the machine
    for(short i=0;i<sdKnifeConfigLib.GetKnifesCount()+2;i++)
    {
        LimitSwitch *limit = new LimitSwitch(i+1,nullptr);
        limitList.push_back(limit);
    }
//----


}
void Machine::MInit()
{
    ADP_Connect();
    ADP_Reset();
    ADP_LoadCfgFile("E:\\01.repository\\07.QT\\GTS800.cfg");
    ADP_ClrSts(1,4);
//----check is the knife changed
    {}

//----set the machine limitSwitch
    GT_AxisOn(AXIS_X);
    GT_AxisOn(AXIS_Y);
    GT_ZeroPos(AXIS_X);
    GT_ZeroPos(AXIS_Y);
    GT_SetPrfPos(AXIS_X, 0);
    GT_SetPrfPos(AXIS_Y, 0);
    bool limitStateXPos;
    bool limitStateXNeg;
    bool limitStateYPos;
    bool limitStateYNeg;
    ADP_GetLimitState(AXIS_X,true, &limitStateXPos);
    ADP_GetLimitState(AXIS_X,false,&limitStateXNeg);
    ADP_GetLimitState(AXIS_Y,true, &limitStateYPos);
    ADP_GetLimitState(AXIS_Y,false,&limitStateYNeg);

    qDebug()<<limitStateXPos<<' '<<limitStateXNeg<<' '<<limitStateYPos<<' '<<limitStateYNeg;

    QPoint firstDot(0,0);
    if(limitStateXNeg == true)
    {
        firstDot.setX(2000);
    }

    if(limitStateYNeg == true)
    {
        firstDot.setY(2000);
    }

//    GT_SetDoBit(MC_GPO,1,0);
//    GT_SetDoBit(MC_GPO,2,0);
//    GT_SetDoBit(MC_GPO,3,0);
}
