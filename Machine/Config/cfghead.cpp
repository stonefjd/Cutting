#include "cfghead.h"
CfgHead::CfgHead()
{
    cfgPath = SETTING_PATH;
}

void CfgHead::GetHeadInfo()
{
    QString strConfigPath = cfgPath;

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
        posOrg.setX((*szBuf).toDouble());
    }
    strKey = ("PosOrgY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        posOrg.setY((*szBuf).toDouble());
    }
    //最大长度：毫米
    strKey = ("PosMaxX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        posMax.setX((*szBuf).toDouble());
    }
    strKey = ("PosMaxY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        posMax.setY((*szBuf).toDouble());
    }
    //区域限位，人为设定尺寸
    strKey = ("PosLimitX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        posLmt.setX((*szBuf).toDouble());
        if(posLmt.x()>posMax.x())
        {
            posLmt.setX(posMax.x());
            WritePrivateProfileString(strSect,strKey,QString::number(posLmt.x()),strConfigPath);
        }
    }
    strKey = ("PosLimitY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        posLmt.setY((*szBuf).toDouble());
        if(posLmt.y()>posMax.y())
        {
            posLmt.setY(posMax.y());
            WritePrivateProfileString(strSect,strKey,QString::number(posLmt.y()),strConfigPath);
        }
    }
    //比例因子：脉冲每毫米
    strKey = ("PosToPulseScaleXY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        posToPulseScaleXY = ((*szBuf).toDouble());
    }
    //比例因子：设计尺寸到切割尺寸
    strKey = ("RealToCutScaleX");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        realToCutScale.setX((*szBuf).toDouble());
    }
    strKey = ("RealToCutScaleY");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        realToCutScale.setY((*szBuf).toDouble());
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
        idleMoveSpd = (*szBuf).toDouble();
    }
    //空走加速度(G)
    strKey = ("IdleMoveAcc");
    if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath))
    {
        idleMoveAcc = (*szBuf).toDouble();
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
    return &posOrg;
}
QPointF* CfgHead::GetPosLmt()
{
    return &posLmt;
}
QPointF* CfgHead::GetPosMax()
{
    return &posMax;
}
double*  CfgHead::GetPosToPulseScaleXY()
{
    return &posToPulseScaleXY;
}
QPointF* CfgHead::GetRealToCutScale()
{
    return &realToCutScale;
}
double*  CfgHead::GetIdleMoveSpd()
{
    return &idleMoveSpd;
}
double*  CfgHead::GetIdleMoveAcc()
{
    return &idleMoveAcc;
}
double*  CfgHead::GetFeedLen()
{
    return &feedLen;
}
double*  CfgHead::GetFeedSpd()
{
    return &feedSpd;
}
double*  CfgHead::GetFeedAcc()
{
    return &feedAcc;
}
void CfgHead::SetPosRt(QPointF *_point)
{
    this->posRt = _point;
}
QString CfgHead::GetHeadCfgPath()
{
    return cfgPath;
}
void CfgHead::UpdateDataPosMax(int _hIndex)
{
//    posMax.setX(_pos.x());
//    posMax.setY(_pos.y());
    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"PosMaxX",QString::number(posMax.x()),cfgPath);
    WritePrivateProfileString("MachHead"+QString::number(_hIndex),"PosMaxY",QString::number(posMax.y()),cfgPath);
    if(posMax.x() <= posLmt.x())
    {
        posLmt.setX(posMax.x());
        WritePrivateProfileString("MachHead"+QString::number(_hIndex),"PosLimitX",QString::number(posMax.x()),cfgPath);
    }
    if(posMax.y() <= posLmt.y())
    {
        posLmt.setY(posMax.y());
        WritePrivateProfileString("MachHead"+QString::number(_hIndex),"PosLimitY",QString::number(posMax.y()),cfgPath);
    }
}

