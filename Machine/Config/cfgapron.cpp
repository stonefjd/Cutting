#include "cfgapron.h"

CfgApron::CfgApron()
{
    apronIndex = -1; 		//刀座序号
    apronUsed  = 0;         //是否使用
    apronCtrlMode = -1;     //控制模式
    apronKnifeGuid = -1;		//刀具Guid
    apronOffsetX = 0;		//刀座偏移量X
    apronOffsetY = 0;		//刀座偏移量Y
    knifeInApron = nullptr;

    cfgPath = SETTING_PATH;
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

    //
    strSect = ("Head0-Apron"+QString::number(index));
    strKey = ("Used");
    if (GetPrivateProfileString(strSect, strKey, szBuf, cfgPath))
    {
        apronUsed = (*szBuf).toInt();
    }
    strKey = ("CtrlMode");
    if (GetPrivateProfileString(strSect, strKey, szBuf, cfgPath))
    {
        apronCtrlMode = (*szBuf).toInt();
    }
    strKey = ("KnifeGuid");
    if (GetPrivateProfileString(strSect, strKey, szBuf, cfgPath))
    {
        apronKnifeGuid = (*szBuf).toInt();
    }
    strKey = ("OffsetX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, cfgPath))
    {
        apronOffsetX = (*szBuf).toDouble();
    }
    strKey = ("OffsetY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, cfgPath))
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
    apronUsed = _use;
}

int   CfgApron::GetApronUse(void)
{
    return apronUsed;
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
    knifeInApron = _knife;
}
CfgKnife *CfgApron::GetKnife()
{
    return knifeInApron;
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
