#include "machine.h"

Machine::Machine(QObject *parent) : QObject(parent)
{
//    this->mFan_1.SetState_FanStop();
    //get the num of knife

//----set the knife of the machine
    sdKnifeConfigLib.ReadConfigFile();
    qDebug()<<sdKnifeConfigLib.GetKnifesCount();

//----set the limit State of the machine
    for(short i=0;i<sdKnifeConfigLib.GetKnifesCount()+2;i++)
    {
        long pos,neg;
        LimitSwitch *limit = new LimitSwitch(i,nullptr);
        limit->GetLimit(&pos,&neg);
        qDebug()<<pos<<' '<<neg;
        limitList.push_back(limit);
    }


//    free(limit);
//    *limit = new LimitSwitch(Y_AXIS,nullptr);
}
