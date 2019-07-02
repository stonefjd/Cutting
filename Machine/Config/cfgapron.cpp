#include "cfgapron.h"

CfgApron::CfgApron()
{
    apronIndex = -1; 		//刀座序号
    apronUsed  = 0;         //是否使用
//    apronHeadIndex = -1;     //机头序号
    apronKnifeGuid = -1;		//刀具Guid
    apronOffsetX = 0;		//刀座偏移量X
    apronOffsetY = 0;		//刀座偏移量Y
    knifeInApron = nullptr;

    apronCfgPath = SETTING_PATH;
}
void CfgApron::GetApronInfo(int index)
{
    apronIndex = index;


    QString strSect = ("");
    QString strKey = ("");
    QString strText = ("");
    QString strDefault = ("");
    QString sInfo = "";

    QString *szBuf = new QString;

    //机头个数
    strSect = ("Apron"+QString::number(index));
    strKey = ("Used");
    if (GetPrivateProfileString(strSect, strKey, szBuf, apronCfgPath))
    {
        apronUsed = (*szBuf).toInt();
    }

    strKey = ("AddedKnifeGuid");
    if (GetPrivateProfileString(strSect, strKey, szBuf, apronCfgPath))
    {
        apronKnifeGuid = (*szBuf).toInt();
    }

    strKey = ("OffsetX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, apronCfgPath))
    {
        apronOffsetX = (*szBuf).toInt();
    }

    strKey = ("OffsetY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, apronCfgPath))
    {
        apronOffsetY = (*szBuf).toDouble();
    }
}

void CfgApron::SetApronIndex(int nApronIndex)
{
    apronIndex = nApronIndex;
}

int CfgApron::GetApronIndex()
{
    return apronIndex;
}
void  CfgApron::SetApronUse(int _use)
{
    this->apronUsed = _use;
}

int   CfgApron::GetApronUse(void)
{
    return this->apronUsed;
}

//void CfgApron::SetApronHeadIndex(short nMachinexIndex)
//{
//    apronHeadIndex = nMachinexIndex;
//}
//short CfgApron::GetApronHeadeIndex()
//{
//    return apronHeadIndex;
//}
//short configApron::GetApronGuid()
//{
//    return static_cast<short>(m_nApronIndex | (m_nMachineIndex<<8));
//}

void CfgApron::SetKnifeGuid(int nGuid)
{
    apronKnifeGuid = nGuid;
}
int CfgApron::GetKnifeGuid()
{
    return apronKnifeGuid;
}
void CfgApron::SetKnife(CfgKnife *_knife)
{
    this->knifeInApron = _knife;
}
CfgKnife *CfgApron::GetKnife()
{
    return this->knifeInApron;
}
void CfgApron::SetXOffset(double dbValue)
{
    apronOffsetX = dbValue;
}
double CfgApron::GetXOffset()
{
    return apronOffsetX;
}


void CfgApron::SetYOffset(double dbValue)
{
    apronOffsetY = dbValue;
}
double CfgApron::GetYOffset()
{
    return apronOffsetY;
}
