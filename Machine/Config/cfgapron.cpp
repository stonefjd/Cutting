#include "cfgapron.h"

CfgApron::CfgApron()
{
    cfgApronData.apronIndex = -1; 		//刀座序号
    cfgApronData.apronUsed  = 0;         //是否使用
    cfgApronData.apronCtrlMode = -1;     //控制模式
    cfgApronData.apronKnifeGuid = -1;		//刀具Guid
    cfgApronData.apronOffsetX = 0;		//刀座偏移量X
    cfgApronData.apronOffsetY = 0;		//刀座偏移量Y
    cfgApronData.knifeInApron = nullptr;

    cfgApronData.cfgPath = SETTING_PATH;
}
void CfgApron::GetApronInfo(int index)
{
    cfgApronData.apronIndex = index;

    QString strSect = ("");
    QString strKey = ("");
    QString strText = ("");
    QString strDefault = ("");
    QString sInfo = "";

    QString *szBuf = new QString;

    //
    strSect = ("MachHead0");
    strKey = ("Apron"+QString::number(index));
    QStringList _apronInfo;
    if (GetPrivateProfileString(strSect, strKey, szBuf, cfgApronData.cfgPath))
    {
        _apronInfo = (*szBuf).split(',');
    }
    cfgApronData.apronUsed       = _apronInfo.at(0).toInt();
    cfgApronData.apronCtrlMode   = _apronInfo.at(1).toInt();
    cfgApronData.apronKnifeGuid  = _apronInfo.at(2).toInt();
    cfgApronData.apronOffsetX    = _apronInfo.at(3).toDouble();
    cfgApronData.apronOffsetY    = _apronInfo.at(4).toDouble();
}
CfgApron_T CfgApron::GetCfgAprondData()
{
    return this->cfgApronData;
}
void CfgApron::SetApronIndex(int nApronIndex)
{
    cfgApronData.apronIndex = nApronIndex;
}

int CfgApron::GetApronIndex()
{
    return cfgApronData.apronIndex;
}
void  CfgApron::SetApronUse(int _use)
{
    cfgApronData.apronUsed = _use;
}

int   CfgApron::GetApronUse(void)
{
    return cfgApronData.apronUsed;
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
    cfgApronData.apronKnifeGuid = nGuid;
}
int CfgApron::GetKnifeGuid()
{
    return cfgApronData.apronKnifeGuid;
}
void CfgApron::SetKnife(CfgKnife *_knife)
{
    cfgApronData.knifeInApron = _knife;
}
CfgKnife *CfgApron::GetKnife()
{
    return cfgApronData.knifeInApron;
}
void CfgApron::SetXOffset(double dbValue)
{
    cfgApronData.apronOffsetX = dbValue;
}
double CfgApron::GetXOffset()
{
    return cfgApronData.apronOffsetX;
}
void CfgApron::SetYOffset(double dbValue)
{
    cfgApronData.apronOffsetY = dbValue;
}
double CfgApron::GetYOffset()
{
    return cfgApronData.apronOffsetY;
}
