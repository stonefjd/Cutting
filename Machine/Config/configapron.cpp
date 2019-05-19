#include "configapron.h"

configApron::configApron(QWidget *parent) : QWidget(parent)
{
    apronIndex = -1; 		//刀座序号
    apronHeadIndex = -1;     //机头序号
    apronKnifeGuid = -1;		//刀具Guid
    apronXOffset = 0;		//刀座偏移量X。增加此变量的目的是为了更换刀具后保留刀座的偏移量，
    apronYOffset = 0;		//刀座偏移量Y。
}
void  configApron::SetApronIndex(int nApronIndex)
{
    apronIndex = nApronIndex;
}

int configApron::GetApronIndex()
{
    return apronIndex;
}
void  configApron::SetApronHeadIndex(short nMachinexIndex)
{
    apronHeadIndex = nMachinexIndex;
}
short configApron::GetApronHeadeIndex()
{
    return apronHeadIndex;
}

//short configApron::GetApronGuid()
//{
//    return static_cast<short>(m_nApronIndex | (m_nMachineIndex<<8));
//}

void  configApron::SetKnifeGuid(int nGuid)
{
    apronKnifeGuid = nGuid;
}
int   configApron::GetKnifeGuid()
{
    return apronKnifeGuid;
}
void   configApron::SetXOffset(double dbValue)
{
    apronXOffset = dbValue;
}
double configApron::GetXOffset()
{
    return apronXOffset;
}


void   configApron::SetYOffset(double dbValue)
{
    apronYOffset = dbValue;
}
double configApron::GetYOffset()
{
    return apronYOffset;
}
