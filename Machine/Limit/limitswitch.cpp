#include "limitswitch.h"

LimitSwitch::LimitSwitch(short _index,QObject *parent) : QObject(parent),axisIndex(_index)
{

}

short LimitSwitch:: GetLimit(long *_pPos,long *_pNeg)
{
    return GT_GetSoftLimit(axisIndex,_pPos,_pNeg);
}
int  LimitSwitch::GetIndex()
{
    return axisIndex;
}
//void LimitSwitch::SetIndex(int _index)
//{

//}
