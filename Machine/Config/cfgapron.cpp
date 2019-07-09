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

    //
    strSect = ("MachHead0");
    strKey = ("Apron"+QString::number(index));
    QStringList _apronInfo;
    if (GetPrivateProfileString(strSect, strKey, szBuf, apronCfgPath))
    {
        _apronInfo = (*szBuf).split(',');
    }
    apronUsed       = _apronInfo.at(0).toInt();
    apronCtrlMode   = _apronInfo.at(1).toInt();
    apronKnifeGuid  = _apronInfo.at(2).toInt();
    apronOffsetX    = _apronInfo.at(3).toDouble();
    apronOffsetY    = _apronInfo.at(4).toDouble();
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
