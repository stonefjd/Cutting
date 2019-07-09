#include "cfghead.h"
CfgHead::CfgHead()
{
    headCfgPath = SETTING_PATH;
}

void CfgHead::GetHeadInfo()
{
    QString strConfigPath = headCfgPath;

    QString strSect = ("");
    QString strKey = ("");
    QString strText = ("");
    QString strDefault = ("");
    QString sInfo = "";

    QString *szBuf = new QString;

    //机头个数
    strSect = ("MachHead0");
    strKey = ("HeadIndex");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        headIndex = (*szBuf).toInt();
    }
    //原点偏移
    strKey = ("PosOrgX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        posOrg->setX((*szBuf).toDouble());
    }
    strKey = ("PosOrgY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        posOrg->setY((*szBuf).toDouble());
    }
    //最大长度：毫米
    strKey = ("PosMaxX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        posMax->setX((*szBuf).toDouble());
    }
    strKey = ("PosMaxY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        posMax->setY((*szBuf).toDouble());
    }
    //区域限位，人为设定尺寸
    strKey = ("PosLimitX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        posLimit->setX((*szBuf).toDouble());
        if(posLimit->x()>posMax->x())
        {
            posLimit->setX(posMax->x());
            WritePrivateProfileString(strSect,strKey,QString::number(posLimit->x()),strConfigPath);
        }
    }
    strKey = ("PosLimitY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        posLimit->setY((*szBuf).toDouble());
        if(posLimit->y()>posMax->y())
        {
            posLimit->setY(posMax->y());
            WritePrivateProfileString(strSect,strKey,QString::number(posLimit->y()),strConfigPath);
        }
    }
    //比例因子：脉冲每毫米
    strKey = ("PosToPulseScaleX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        posToPulseScale->setX((*szBuf).toDouble());
    }
    strKey = ("PosToPulseScaleY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        posToPulseScale->setY((*szBuf).toDouble());
    }
    //X方向最大行走脉冲数
    strKey = ("PulseMaxX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        pulseMax->setX((*szBuf).toDouble());
    }
    strKey = ("PulseMaxY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        pulseMax->setY((*szBuf).toDouble());
    }
    //比例因子：设计尺寸到切割尺寸
    strKey = ("RealToCutScaleX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        realToCutScale->setX((*szBuf).toDouble());
    }
    strKey = ("RealToCutScaleY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        realToCutScale->setY((*szBuf).toDouble());
    }

    //送料长度
    strKey = ("FeedLen");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        feedLen = (*szBuf).toDouble();
    }
    //送料速度(m/s)
    strKey = ("FeedSpd");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        feedSpd = (*szBuf).toDouble();
    }
    //送料加速度(m/s²)
    strKey = ("FeedAcc");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        feedAcc = (*szBuf).toDouble();
    }
    //空走速度 (m/s)
    strKey = ("IdleMoveSpd");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        *idleMoveSpd = (*szBuf).toDouble();
    }
    //空走加速度(G)
    strKey = ("IdleMoveAcc");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        *idleMoveAcc = (*szBuf).toDouble();
    }
//    //获取机座列表
//    strKey = ("Aprons");
//    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
//    {
//        apronIndexList = szBuf->split(',');
//    }
//    for(int _apronCnt=0;_apronCnt<apronIndexList.count();_apronCnt++)
//    {
//        strKey = ("Apron"+QString::number(_apronCnt));
//        QStringList apronParam;
//        if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
//        {
//            apronParam = (szBuf)->split(',');
//        }
//        CfgApron *apron = new CfgApron;
//        apron->SetApronIndex(_apronCnt);
//        apron->SetKnifeGuid(KNIFETOOLID2GUID(apronParam.at(1).toInt(),apronParam.at(2).toInt()));
//        apron->SetXOffset(apronParam.at(3).toDouble());
//        apron->SetXOffset(apronParam.at(4).toDouble());
//        aConfig.append(apron);
//    }
}
QPointF* CfgHead::GetPosOrg()
{
    return posOrg;
}
QPointF* CfgHead::GetPosLmt()
{
    return posLimit;
}
QPointF* CfgHead::GetPosMax()
{
    return posMax;
}
QPointF* CfgHead::GetPosToPulseScale()
{
    return posToPulseScale;
}
QPointF* CfgHead::GetPulseMax()
{
    return pulseMax;
}
QPointF* CfgHead::GetRealToCutScale()
{
    return realToCutScale;
}
double*  CfgHead::GetIdleMoveSpd()
{
    return idleMoveSpd;
}
double*  CfgHead::GetIdleMoveAcc()
{
    return idleMoveAcc;
}
double  CfgHead::GetFeedLen()
{
    return feedLen;
}
double  CfgHead::GetFeedSpd()
{
    return feedSpd;
}
//void CfgHead::SetApronIndexList(QStringList _list)
//{
//    this->apronIndexList = _list;
//}
//QStringList CfgHead::GetApronIndexList(void)
//{
//    return this->apronIndexList;
//}
double  CfgHead::GetFeedAcc()
{
    return feedAcc;
}

QString CfgHead::GetHeadCfgPath()
{
    return headCfgPath;
}
void CfgHead::UpdateHeadMaxPluse(int _xPluse,int _yPluse,int _hIndex)
{
    pulseMax->setX(_xPluse);
    pulseMax->setY(_yPluse);
    posMax->setX(_xPluse/posToPulseScale->x());
    posMax->setY(_yPluse/posToPulseScale->y());
    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"PulseMaxX",QString::number(_xPluse),headCfgPath);
    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"PulseMaxY",QString::number(_yPluse),headCfgPath);
    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"PosMaxX",QString::number(_xPluse/posToPulseScale->x()),headCfgPath);
    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"PosMaxY",QString::number(_yPluse/posToPulseScale->y()),headCfgPath);
    if(_xPluse <= posLimit->x())
    {
        posLimit->setX(_xPluse);
        WritePrivateProfileString("MachHead"+QString::number(_hIndex),"HeadCutLimitX",QString::number(_xPluse),headCfgPath);
    }
    if(_yPluse <= posLimit->y())
    {
        posLimit->setX(_xPluse);
        WritePrivateProfileString("MachHead"+QString::number(_hIndex),"HeadCutLimitY",QString::number(_yPluse),headCfgPath);
    }
}
void CfgHead::UpdateHeadCutLimit(int _xPluse,int _yPluse,int _hIndex)
{
    if(_xPluse <= pulseMax->x())
    {
        posLimit->setX(_xPluse);
    }
    if(_yPluse <= pulseMax->y())
    {
        posLimit->setY(_yPluse);
    }
    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"HeadCutLimitX",QString::number(_xPluse),headCfgPath);
    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"HeadCutLimitY",QString::number(_yPluse),headCfgPath);
}
