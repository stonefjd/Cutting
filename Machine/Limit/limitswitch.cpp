#include "limitswitch.h"

LimitSwitch::LimitSwitch(short _index,QObject *parent) : QObject(parent),axisIndex(_index)
{

}

short LimitSwitch:: GetLimitState(short _axis,bool _polar,bool *_state)
{
    ADP_GetLimitState( _axis, _polar, _state);
    return 0;//ADP_GetLimit(axisIndex,_pPos,_pNeg);
}
int  LimitSwitch::GetIndex()
{
    return axisIndex;
}
//void LimitSwitch::SetIndex(int _index)
//{

//}
