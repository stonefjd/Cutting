#include "cfghead.h"
CfgHead::CfgHead()
{
    cfgHeadData.cfgPath = SETTING_PATH;
}

void CfgHead::GetHeadInfo()
{
    QString strConfigPath = cfgHeadData.cfgPath;

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
        cfgHeadData.headIndex = (*szBuf).toInt();
    }
    //原点偏移
    strKey = ("PosOrgX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgHeadData.posOrg.setX((*szBuf).toDouble());
    }
    strKey = ("PosOrgY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgHeadData.posOrg.setY((*szBuf).toDouble());
    }
    //最大长度：毫米
    strKey = ("PosMaxX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgHeadData.posMax.setX((*szBuf).toDouble());
    }
    strKey = ("PosMaxY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgHeadData.posMax.setY((*szBuf).toDouble());
    }
    //区域限位，人为设定尺寸
    strKey = ("PosLimitX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgHeadData.posLmt.setX((*szBuf).toDouble());
        if(cfgHeadData.posLmt.x()>cfgHeadData.posMax.x())
        {
            cfgHeadData.posLmt.setX(cfgHeadData.posMax.x());
            WritePrivateProfileString(strSect,strKey,QString::number(cfgHeadData.posLmt.x()),strConfigPath);
        }
    }
    strKey = ("PosLimitY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgHeadData.posLmt.setY((*szBuf).toDouble());
        if(cfgHeadData.posLmt.y()>cfgHeadData.posMax.y())
        {
            cfgHeadData.posLmt.setY(cfgHeadData.posMax.y());
            WritePrivateProfileString(strSect,strKey,QString::number(cfgHeadData.posLmt.y()),strConfigPath);
        }
    }
    //比例因子：脉冲每毫米
    strKey = ("PosToPulseScaleX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgHeadData.posToPulseScale.setX((*szBuf).toDouble());
    }
    strKey = ("PosToPulseScaleY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgHeadData.posToPulseScale.setY((*szBuf).toDouble());
    }
    strKey = ("PosToPulseScaleXY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgHeadData.posToPulseScaleXY = ((*szBuf).toDouble());
    }
    //X方向最大行走脉冲数
    strKey = ("PulseMaxX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgHeadData.pulseMax.setX((*szBuf).toDouble());
    }
    strKey = ("PulseMaxY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgHeadData.pulseMax.setY((*szBuf).toDouble());
    }
    //比例因子：设计尺寸到切割尺寸
    strKey = ("RealToCutScaleX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgHeadData.realToCutScale.setX((*szBuf).toDouble());
    }
    strKey = ("RealToCutScaleY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgHeadData.realToCutScale.setY((*szBuf).toDouble());
    }

    //送料长度
    strKey = ("FeedLen");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgHeadData.feedLen = (*szBuf).toDouble();
    }
    //送料速度(m/s)
    strKey = ("FeedSpd");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgHeadData.feedSpd = (*szBuf).toDouble();
    }
    //送料加速度(m/s²)
    strKey = ("FeedAcc");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgHeadData.feedAcc = (*szBuf).toDouble();
    }
    //空走速度 (m/s)
    strKey = ("IdleMoveSpd");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgHeadData.idleMoveSpd = (*szBuf).toDouble();
    }
    //空走加速度(G)
    strKey = ("IdleMoveAcc");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        cfgHeadData.idleMoveAcc = (*szBuf).toDouble();
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
CfgHead_T CfgHead::GetCfgHeadData()
{
    return this->cfgHeadData;
}
QPointF CfgHead::GetPosOrg()
{
    return cfgHeadData.posOrg;
}
QPointF CfgHead::GetPosLmt()
{
    return cfgHeadData.posLmt;
}
QPointF CfgHead::GetPosMax()
{
    return cfgHeadData.posMax;
}
QPointF CfgHead::GetPosToPulseScale()
{
    return cfgHeadData.posToPulseScale;
}
double  CfgHead::GetPosToPulseScaleXY()
{
    return cfgHeadData.posToPulseScaleXY;
}
QPointF CfgHead::GetPulseMax()
{
    return cfgHeadData.pulseMax;
}
QPointF CfgHead::GetRealToCutScale()
{
    return cfgHeadData.realToCutScale;
}
double  CfgHead::GetIdleMoveSpd()
{
    return cfgHeadData.idleMoveSpd;
}
double  CfgHead::GetIdleMoveAcc()
{
    return cfgHeadData.idleMoveAcc;
}
double  CfgHead::GetFeedLen()
{
    return cfgHeadData.feedLen;
}
double  CfgHead::GetFeedSpd()
{
    return cfgHeadData.feedSpd;
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
    return cfgHeadData.feedAcc;
}

QString CfgHead::GetHeadCfgPath()
{
    return cfgHeadData.cfgPath;
}
void CfgHead::UpdateDataPosMax(QPointF _pos,int _hIndex)
{
    cfgHeadData.posMax.setX(_pos.x());
    cfgHeadData.posMax.setY(_pos.y());
    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"PosMaxX",QString::number(_pos.x()),cfgHeadData.cfgPath);
    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"PosMaxY",QString::number(_pos.y()),cfgHeadData.cfgPath);
    if(_pos.x() <= cfgHeadData.posLmt.x())
    {
        cfgHeadData.posLmt.setX(_pos.x());
        WritePrivateProfileString("MachHead"+QString::number(_hIndex),"PosLimitX",QString::number(_pos.x()),cfgHeadData.cfgPath);
    }
    if(_pos.y() <= cfgHeadData.posLmt.y())
    {
        cfgHeadData.posLmt.setY(_pos.y());
        WritePrivateProfileString("MachHead"+QString::number(_hIndex),"PosLimitY",QString::number(_pos.y()),cfgHeadData.cfgPath);
    }
}
//void CfgHead::UpdateHeadMaxPluse(int _xPluse,int _yPluse,int _hIndex)
//{
//    cfgHeadData.pulseMax.setX(_xPluse);
//    cfgHeadData.pulseMax.setY(_yPluse);
//    cfgHeadData.posMax.setX(_xPluse/cfgHeadData.posToPulseScale.x());
//    cfgHeadData.posMax.setY(_yPluse/cfgHeadData.posToPulseScale.y());
//    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"PulseMaxX",QString::number(_xPluse),cfgHeadData.cfgPath);
//    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"PulseMaxY",QString::number(_yPluse),cfgHeadData.cfgPath);
//    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"PosMaxX",QString::number(_xPluse/cfgHeadData.posToPulseScale.x()),cfgHeadData.cfgPath);
//    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"PosMaxY",QString::number(_yPluse/cfgHeadData.posToPulseScale.y()),cfgHeadData.cfgPath);

//}
//void CfgHead::UpdateHeadCutLimit(int _xPluse,int _yPluse,int _hIndex)
//{
//    if(_xPluse <= pulseMax.x())
//    {
//        posLimit.setX(_xPluse);
//    }
//    if(_yPluse <= pulseMax.y())
//    {
//        posLimit.setY(_yPluse);
//    }
//    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"HeadCutLimitX",QString::number(_xPluse),headCfgPath);
//    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"HeadCutLimitY",QString::number(_yPluse),headCfgPath);
//}
