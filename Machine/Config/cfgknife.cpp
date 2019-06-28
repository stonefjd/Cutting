#include "cfgknife.h"

CfgKnife::CfgKnife(QWidget *parent) : QWidget(parent)
{

}
CfgKnife::CfgKnife(KnifeId nCutToolId,short nKnifeId)
{
    Free();
    //初始化大类
    m_emCutToolId = nCutToolId;
    LoadCutToolKey();
    //初始化子类
    m_nKnifeId = nKnifeId;
    LoadKnifeKey();
    //初始化刀名
    InitKnifeNames();
}
CfgKnife& CfgKnife::operator = (const CfgKnife& other)
{
    if (this == &other)
    {
        return *this;
    }

    m_nCutInfoId = other.m_nCutInfoId;		//对象id
    m_emCutToolId = other.m_emCutToolId;		//刀具类型
    m_nKnifeId = other.m_nKnifeId;			//刀具子类型
    m_nApronGuid = other.m_nApronGuid;		//刀具所在刀座Guid
    m_emApronCMode = other.m_emApronCMode;    //刀具刀座控制类型
    m_nGuid = other.m_nGuid;				//Guid值
    m_nColor = other.m_nColor;				//颜色
    m_sCutToolName = other.m_sCutToolName;	//刀具大类名
    m_sCutToolKey = other.m_sCutToolKey;	//刀具关键字
    m_sKnifeKey = other.m_sKnifeKey;		//刀关键字
    m_sKnifeName = other.m_sKnifeName;		//刀名
    m_dbDia = other.m_dbDia;

    m_dbXEtc = other.m_dbXEtc;				//X偏心距 (eccentricity)
    m_dbYEtc = other.m_dbYEtc;				//Y偏心距 (eccentricity)
    m_dbXOffset = other.m_dbXOffset;		//偏移量
    m_dbYOffset = other.m_dbYOffset;
    m_dbWidth = other.m_dbWidth;
    m_dbHeight = other.m_dbHeight;
    m_dbAngle = other.m_dbAngle;
    m_dbTenacity = other.m_dbTenacity;
    m_dbPUCstVal = other.m_dbPUCstVal;		//抬刀补偿量(过切量)
    m_dbPDCstVal = other.m_dbPDCstVal;		//落刀补偿量(过切量)
    m_dbToXAlixAngle = other.m_dbToXAlixAngle;//刀与X轴正向夹角 (度)
    m_dbPUAngle = other.m_dbPUAngle;		//抬刀角度 (度)
    m_dbPUSpeed = other.m_dbPUSpeed;		//抬刀速度 (m/s)
    m_dbPDSpeed = other.m_dbPDSpeed;		//落刀速度 (m/s)
    m_dbPDAcceleration = other.m_dbPDAcceleration;		//落刀加速度(G)
    m_dbMoveSpeed = other.m_dbMoveSpeed;	//运动速度(m/s)
    m_dbMoveAcceleration = other.m_dbMoveAcceleration;	//运动加速度(g)
    m_dbCornerSpeed = other.m_dbCornerSpeed;//转角速度
    m_dbRotateSpeed = other.m_dbRotateSpeed;//转刀速度(m/s)
    m_dbRotateAcceleration = other.m_dbRotateAcceleration; //转刀加速度(g)
    m_dbMaxPDDepth = other.m_dbMaxPDDepth;	//最大落刀深度(mm)
    m_dbMaxPDDepth45 = other.m_dbMaxPDDepth45;	//最大落刀深度(mm)
    m_dbMaxPUDepth = other.m_dbMaxPUDepth;	//最大抬刀深度(mm)
    m_dbAlignZCal = other.m_dbAlignZCal;//对刀偏差
    m_dbAlignZ = other.m_dbAlignZ;//对刀值

    m_dbWaitTimeBeforePD = other.m_dbWaitTimeBeforePD;//落刀前等待时间(ms)
    m_dbWaitTimeBeforePD = other.m_dbWaitTimeAfterPD;//落刀后等待时间(ms)

    m_dbWaitTimeBeforePU = other.m_dbWaitTimeBeforePU;//抬刀前等待时间(ms)
    m_dbWaitTimeAfterPU = other.m_dbWaitTimeAfterPU;//抬刀后等待时间(ms)

    return *this;
}
void CfgKnife::ReadKnifeInfo(QString sConfigPath,QString sSect)
{
    QString sKey = "";
    QString sInfo = "";
    QString sDefault = "";

    QString *szBuf = new QString;

    //刀具大类Id
    sKey = "CutToolId";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_emCutToolId = static_cast<KnifeId>((*szBuf).toInt());
    }
    //刀具子类Id
    sKey = "KnifeId";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_nKnifeId = (*szBuf).toShort();
    }

    //刀具所在刀座Guid
    sKey = "ApronGuid";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_nApronGuid = (*szBuf).toShort();
    }

    //刀具刀座的控制方式
    sKey = "ApronMode";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_emApronCMode = static_cast<ApronCtrlMode>((*szBuf).toShort());
    }

    //Guid
    sKey = "KnifeGuid";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_nGuid = (*szBuf).toInt();
    }

    LoadCutToolKey();
    LoadKnifeKey();

    //颜色
    sKey = "KnifeColor";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_nColor = (*szBuf).toInt();
    }

    //刀具大类名
    sKey = "CutToolName";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_sCutToolName = *szBuf;
    }
    //刀具名
    sKey = "KnifeName";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_sKnifeName = *szBuf;
    }
    //直径
    sKey = "Diameter";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbDia = (*szBuf).toDouble();
    }
    //X偏心距
    sKey = "XEccVal";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbXEtc = (*szBuf).toDouble();
    }
    //Y偏心距
    sKey = "YEccVal";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbYEtc = (*szBuf).toDouble();
    }
    //X偏移量
    sKey = "XOffset";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbXOffset = (*szBuf).toDouble();
    }
    //Y偏移量
    sKey = "YOffset";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbYOffset = (*szBuf).toDouble();
    }
    //宽度
    sKey = "Width";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbWidth = (*szBuf).toDouble();
    }
    //高度
    sKey = "Height";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbHeight = (*szBuf).toDouble();
    }
    //角度
    sKey = "Angle";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbAngle = (*szBuf).toDouble();
    }
    //韧度
    sKey = "Tenacity";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbTenacity = (*szBuf).toDouble();
    }
    //抬刀补偿量(过切量)
    sKey = "PUOverCstVal";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbPUCstVal = (*szBuf).toDouble();
    }
    //落刀补偿量(过切量)
    sKey = "PDOverCstVal";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbPDCstVal = (*szBuf).toDouble();
    }
    //刀与X轴正向夹角 (度)
    sKey = "ToXAlixAngle";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbToXAlixAngle = (*szBuf).toDouble();
    }
    //抬刀角度 (度)
    sKey = "PUAngle";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbPUAngle = (*szBuf).toDouble();
    }
    //抬刀速度 (m/s)
    sKey = "PUSpeed";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbPUSpeed = (*szBuf).toDouble();
    }
    //落刀速度 (m/s)
    sKey = "PDSpeed";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbPDSpeed = (*szBuf).toDouble();
    }
    //落刀加速度(G)
    sKey = "PDAcc";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbPDAcceleration = (*szBuf).toDouble();
    }
    //运动速度(m/s)
    sKey = "MoveSpeed";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbMoveSpeed = (*szBuf).toDouble();
    }
    //运动加速度(g)
    sKey = "MoveAcc";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbMoveAcceleration = (*szBuf).toDouble();
    }
    //转动速度(m/s)
    sKey = "RotateSpeed";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbRotateSpeed = (*szBuf).toDouble();
    }
    //转动加速度(g)
    sKey = "RotateAcc";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbRotateAcceleration = (*szBuf).toDouble();
    }
    //转角速度
    sKey = "CornerSpeed";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbCornerSpeed = (*szBuf).toDouble();
    }
    //最大落刀深度(mm)
    sKey = "MaxPDDepth";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbMaxPDDepth = (*szBuf).toDouble();
    }
    //45度最大落刀深度(mm)
    sKey = "MaxPDDepth45";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbMaxPDDepth45 = (*szBuf).toDouble();
    }
    //最大抬刀深度(mm)
    sKey = "MaxPUDepth";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbMaxPUDepth = (*szBuf).toDouble();
        if((m_dbMaxPUDepth>m_dbMaxPDDepth)||(m_dbMaxPUDepth<0))
            m_dbMaxPUDepth=m_dbMaxPDDepth;
    }
    else
        m_dbMaxPUDepth=m_dbMaxPDDepth;

    //对刀值(mm)
    sKey = "AlignZ";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbAlignZ = (*szBuf).toDouble();
    }
    else
        m_dbAlignZ=0;

    //对刀偏差(mm)
    sKey = "AlignZCal";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbAlignZCal = (*szBuf).toDouble();
    }
    else
        m_dbAlignZCal=0;

    //落刀前等待时间(ms)
    sKey = "WTBeforePD";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbWaitTimeBeforePD = (*szBuf).toDouble();
    }
    //落刀后等待时间(ms)
    sKey = "WTAfterPD";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbWaitTimeAfterPD = (*szBuf).toDouble();
    }
    //抬刀前等待时间(ms)
    sKey = "WTBeforePU";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbWaitTimeBeforePU = (*szBuf).toDouble();
    }
    //抬刀后等待时间(ms)
    sKey = "WTAfterPU";
    if (GetPrivateProfileString(sSect, sKey, szBuf, sConfigPath))
    {
        m_dbWaitTimeAfterPU = (*szBuf).toDouble();
    }
}
void CfgKnife::WriteKnifeInfo(QString sConfigPath,QString sSect)
{
    QString sKey = "";
    QString sInfo = "";

    //刀具大类Id
    sKey = "CutToolId";
    sInfo = QString::number(static_cast<int>(m_emCutToolId));
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //刀具子类Id
    sKey = "KnifeId";
    sInfo = QString::number(static_cast<int>(m_nKnifeId));
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //刀具所在刀座Guid
    sKey = "ApronGuid";
    sInfo = QString::number(static_cast<int>(m_nApronGuid));
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //刀具刀座的控制方式
    sKey = "ApronMode";
    sInfo = QString::number(static_cast<int>(m_emApronCMode));
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //Guid
    sKey = "KnifeGuid";
    sInfo = QString::number(static_cast<int>(m_nGuid));
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //颜色
    sKey = "KnifeColor";
    sInfo = QString::number(static_cast<int>(m_nColor));
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //刀具大类名
    sKey = "CutToolName";
    sInfo = m_sCutToolName;
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //刀具名
    sKey = "KnifeName";
    sInfo = m_sKnifeName;
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //直径
    sKey = "Diameter";
    sInfo = QString::number(m_dbDia,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //X偏心距
    sKey = "XEccVal";
    sInfo =  QString::number(m_dbXEtc,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //Y偏心距
    sKey = "YEccVal";
    sInfo = QString::number(m_dbYEtc,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //X偏移量
    sKey = "XOffset";
    sInfo = QString::number(m_dbXOffset,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //Y偏移量
    sKey = "YOffset";
    sInfo = QString::number(m_dbYOffset,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //宽度
    sKey = "Width";
    sInfo = QString::number(m_dbWidth,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //高度
    sKey = "Height";
    sInfo = QString::number(m_dbHeight,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //角度
    sKey = "Angle";
    sInfo = QString::number(m_dbAngle,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //韧度
    sKey = "Tenacity";
    sInfo = QString::number(m_dbTenacity,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //抬刀补偿量(过切量)
    sKey = "PUOverCstVal";
    sInfo = QString::number(m_dbPUCstVal,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //落刀补偿量(过切量)
    sKey = "PDOverCstVal";
    sInfo = QString::number(m_dbPDCstVal,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //刀与X轴正向夹角 (度)
    sKey = "ToXAlixAngle";
    sInfo = QString::number(m_dbToXAlixAngle,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //抬刀角度 (度)
    sKey = "PUAngle";
    sInfo = QString::number(m_dbPUAngle,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //抬刀速度 (m/s)
    sKey = "PUSpeed";
    sInfo = QString::number(m_dbPUSpeed,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //落刀速度 (m/s)
    sKey = "PDSpeed";
    sInfo = QString::number(m_dbPDSpeed,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //落刀加速度(G)
    sKey = "PDAcc";
    sInfo = QString::number(m_dbPDAcceleration,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //运动速度(m/s)
    sKey = "MoveSpeed";
    sInfo = QString::number(m_dbMoveSpeed,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //运动加速度(g)
    sKey = "MoveAcc";
    sInfo = QString::number(m_dbMoveAcceleration,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //转动速度(m/s)
    sKey = "RotateSpeed";
    sInfo = QString::number(m_dbRotateSpeed,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //转动加速度(g)
    sKey = "RotateAcc";
    sInfo = QString::number(m_dbRotateAcceleration,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //转角速度
    sKey = "CornerSpeed";
    sInfo = QString::number(m_dbCornerSpeed,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //最大落刀深度(mm)
    sKey = "MaxPDDepth";
    sInfo = QString::number(m_dbMaxPDDepth,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    sKey = "MaxPDDepth45";
    sInfo = QString::number(m_dbMaxPDDepth45,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //最大抬刀深度(mm)
    sKey = "MaxPUDepth";
    sInfo = QString::number(m_dbMaxPUDepth,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //对刀值(mm)
    sKey = "AlignZ";
    sInfo = QString::number(m_dbAlignZ,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //对刀偏差(mm)
    sKey = "AlignZCal";
    sInfo = QString::number(m_dbAlignZCal,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //落刀前等待时间(ms)
    sKey = "WTBeforePD";
    sInfo = QString::number(m_dbWaitTimeBeforePD,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //落刀后等待时间(ms)
    sKey = "WTAfterPD";
    sInfo = QString::number(m_dbWaitTimeAfterPD,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //抬刀前等待时间(ms)
    sKey = "WTBeforePU";
    sInfo = QString::number(m_dbWaitTimeBeforePU,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

    //抬刀后等待时间(ms)
    sKey = "WTAfterPU";
    sInfo = QString::number(m_dbWaitTimeAfterPU,'f',4);
    WritePrivateProfileString(sSect, sKey, sInfo, sConfigPath);

}

void  CfgKnife::SetCutInfoId(short nCutInfoId)
{
    m_nCutInfoId = nCutInfoId;
}
short CfgKnife::GetCutInfoId()
{
    return m_nCutInfoId;
}
void   CfgKnife::SetCutToolId(KnifeId emCutToolId)
{
    m_emCutToolId = emCutToolId;
    LoadCutToolKey();
}
KnifeId  CfgKnife::GetCutToolId()
{
    return m_emCutToolId;
}

void   CfgKnife::SetKnifeId(short nKnifeId)
{
    m_nKnifeId = nKnifeId;
    LoadKnifeKey();
    //m_nGuid = (m_nCutToolId|(m_nKnifeId<<8));// m_nKnifeId<<8 + m_nCutToolId;
}
short  CfgKnife::GetKnifeId()
{
    return m_nKnifeId;
}

void   CfgKnife::SetApronGuid(short nMachineHead,short nApronIndex)
{
    m_nApronGuid = static_cast<short>(nApronIndex | (nMachineHead<<8));
}
void   CfgKnife::SetApronGuid(short nApronGuid)
{
    m_nApronGuid = nApronGuid;
}
short  CfgKnife::GetApronGuid()
{
    return m_nApronGuid;
}

short  CfgKnife::GetMachinIndex()
{
    short nSrcMachineId = ((m_nApronGuid>>8)&0xff);
    return nSrcMachineId;
}

short  CfgKnife::GetApronIndex()
{
    short nApronId = ((m_nApronGuid)&0xff);
    return nApronId;
}

void   CfgKnife::SetApronCMode(ApronCtrlMode emMode)
{
    m_emApronCMode = emMode;
}
short  CfgKnife::GetApronCMode()
{
    return m_emApronCMode;
}
void   CfgKnife::CreadApronCMode()
{
    switch(m_emCutToolId)
    {
    case CUTTINGTOOL_PEN:
        m_emApronCMode = TOOLAPRON_CMODE_PEN;
        break;
    case CUTTINGTOOL_ROLL:
        m_emApronCMode = TOOLAPRON_CMODE_ROLL;
        break;
    case CUTTINGTOOL_EOT:
        m_emApronCMode = TOOLAPRON_CMODE_EOT;
        break;
    case CUTTINGTOOL_POT:
        m_emApronCMode = TOOLAPRON_CMODE_POT;
        break;
    case CUTTINGTOOL_VPUNCH:
        m_emApronCMode = TOOLAPRON_CMODE_VPUNCH;
        break;
    case CUTTINGTOOL_SPUNCH:
        m_emApronCMode = TOOLAPRON_CMODE_SPUNCH;
        break;
    case CUTTINGTOOL_RPUNCH:
        m_emApronCMode = TOOLAPRON_CMODE_RPUNCH;
        break;
    case CUTTINGTOOL_DRILL:
        m_emApronCMode = TOOLAPRON_CMODE_DRILL;
        break;
    case CUTTINGTOOL_VCUT:
        m_emApronCMode = TOOLAPRON_CMODE_VCUT;
        break;
    case CUTTINGTOOL_SCT:
        m_emApronCMode = TOOLAPRON_CMODE_SCT;
        break;
    case CUTTINGTOOL_KCT:
        m_emApronCMode = TOOLAPRON_CMODE_KCT;
        break;
    case CUTTINGTOOL_CREASE:
        m_emApronCMode = TOOLAPRON_CMODE_CREASE;
        break;
    case CUTTINGTOOL_MILL:
        m_emApronCMode = TOOLAPRON_CMODE_MILL;
        break;
    case CUTTINGTOOL_EVCT:
        m_emApronCMode = TOOLAPRON_CMODE_EVCT;
        break;
    case CUTTINGTOOL_RCT:
        m_emApronCMode = TOOLAPRON_CMODE_RCT;
        break;
    case CUTTINGTOOL_DCT:
        m_emApronCMode = TOOLAPRON_CMODE_DCT;
        break;
    case CUTTINGTOOL_PLOT:
        m_emApronCMode = TOOLAPRON_CMODE_PLOT;
        break;
    case CUTTINGTOOL_REDLIGHT:
        m_emApronCMode = TOOLAPRON_CMODE_REDLIGHT;
        break;
    case CUTTINGTOOL_LASER:
        m_emApronCMode = TOOLAPRON_CMODE_LASER;
        break;
    case CUTTINGTOOL_CAMERA:
        m_emApronCMode = TOOLAPRON_CMODE_CAMERA;
        break;
    case CUTTINGTOOL_NULL:
        m_emApronCMode = TOOLAPRON_CMODE_NULL;
        break;
    }
}

void   CfgKnife::SetColor(int nClr)
{
    m_nColor = nClr;
}
int    CfgKnife::GetColor()
{
    return m_nColor;
}

void   CfgKnife::SetCutToolName(QString sToolName)
{
    m_sCutToolName = sToolName;
}
QString CfgKnife::GetCutToolName()
{
    return m_sCutToolName;
}

void   CfgKnife::SetCutToolKey(QString sKey)
{
    m_sCutToolKey = sKey;
}
QString CfgKnife::GetCutToolKey()
{
    return m_sCutToolKey;
}

void   CfgKnife::SetKnifeKey(QString sKey)
{
    m_sKnifeKey = sKey;
}

QString   CfgKnife::GetKnifeKey()
{
    return m_sKnifeKey;
}

void   CfgKnife::SetKnifeName(QString sName)
{
    if (!sName.isEmpty())
        m_sKnifeName = sName;
}
QString CfgKnife::GetKnifeName()
{
    if (m_sKnifeName.isEmpty())
    {
        InitKnifeNames();
    }

    return m_sKnifeName;
}

void   CfgKnife::SetGuid(int nGuid,bool bSetKnifeId)
{
    m_nGuid = nGuid;

    if (bSetKnifeId)
    {
        //重新设置刀片Id
        m_nKnifeId = GUID2KNIFEID(nGuid);//(short)((nGuid>>8)&0xff);

        //重新设置刀具id
        m_emCutToolId = static_cast<KnifeId>(GUID2CUTTOOLID(nGuid));//(short)(nGuid&0xff);
    }
}
int    CfgKnife::GetGuid()
{
    return m_nGuid;
}
void   CfgKnife::CreateGuid()
{
    m_nGuid = KNIFETOOLID2GUID(static_cast<int>(m_emCutToolId),m_nKnifeId);


    CreadApronCMode();
}
QString CfgKnife::GetGuidString()
{
    //string sInfo = SDString::intTostring(m_nGuid);
    QString sInfo = QString::number(m_emCutToolId);
    sInfo += "-";
    sInfo += QString::number(m_nKnifeId);
    return sInfo;
}
void   CfgKnife::SetDia(double dbValue)
{
    m_dbDia = dbValue;
}
double CfgKnife::GetDia()
{
    return m_dbDia;
}


void   CfgKnife::SetXEtc(double dbValue)
{
    m_dbXEtc = dbValue;
}
double CfgKnife::GetXEtc()
{
    return m_dbXEtc;
}

void   CfgKnife::SetYEtc(double dbValue)
{
    m_dbYEtc = dbValue;
}
double CfgKnife::GetYEtc()
{
    return m_dbYEtc;
}
void   CfgKnife::SetXOffset(double dbValue)
{
    m_dbXOffset = dbValue;
}
double CfgKnife::GetXOffset()
{
    return m_dbXOffset;
}

void   CfgKnife::SetYOffset(double dbValue)
{
    m_dbYOffset = dbValue;
}
double CfgKnife::GetYOffset()
{
    return m_dbYOffset;
}

void   CfgKnife::SetWidth(double dbValue)
{
    m_dbWidth = dbValue;
}
double CfgKnife::GetWidth()
{
    return m_dbWidth;
}

void   CfgKnife::SetHeight(double dbValue)
{
    m_dbHeight = dbValue;
}
double CfgKnife::GetHeight()
{
    return m_dbHeight;
}
void   CfgKnife::SetAngle(double dbValue)
{
    m_dbAngle = dbValue;
}
double CfgKnife::GetAngle()
{
    return m_dbAngle;
}

void   CfgKnife::SetTenacity(double dbValue)
{
    m_dbTenacity = dbValue;
}
double CfgKnife::GetTenacity()
{
    return m_dbTenacity;
}

double  CfgKnife::GetPUCstVal()
{
    return  m_dbPUCstVal;
}
void    CfgKnife::SetPUCstVal(double dbValue)
{
    m_dbPUCstVal = dbValue;
}


double  CfgKnife::GetPDCstVal()
{
    return m_dbPDCstVal;
}
void    CfgKnife::SetPDCstVal(double dbValue)
{
    m_dbPDCstVal = dbValue;
}

double  CfgKnife::GetXAlixAngle()
{
    return m_dbToXAlixAngle;
}
void    CfgKnife::SetXAlixAngle(double dbValue)
{
    m_dbToXAlixAngle = dbValue;
}


double  CfgKnife::GetPUAngle()
{
    return m_dbPUAngle;
}
void    CfgKnife::SetPUAngle(double dbValue)
{
    m_dbPUAngle = dbValue;
}


double  CfgKnife::GetPUSpeed()
{
    return m_dbPUSpeed;
}
void    CfgKnife::SetPUSpeed(double dbValue)
{
    m_dbPUSpeed = dbValue;
}


double  CfgKnife::GetPDSpeed()
{
    return m_dbPDSpeed;
}
void    CfgKnife::SetPDSpeed(double dbValue)
{
    m_dbPDSpeed = dbValue;
}


double  CfgKnife::GetPDAcceleration()
{
    return m_dbPDAcceleration;
}
void    CfgKnife::SetPDAcceleration(double dbValue)
{
    m_dbPDAcceleration = dbValue;
}


double  CfgKnife::GetMoveSpeed()
{
    return m_dbMoveSpeed;
}
void    CfgKnife::SetMoveSpeed(double dbValue)
{
    m_dbMoveSpeed = dbValue;
}


double  CfgKnife::GetMoveAcceleration()
{
    return m_dbMoveAcceleration;
}
void    CfgKnife::SetMoveAcceleration(double dbValue)
{
    m_dbMoveAcceleration = dbValue;
}

double  CfgKnife::GetCornerSpeed()
{
    return m_dbCornerSpeed;
}
void    CfgKnife::SetCornerSpeed(double dbValue)
{
    m_dbCornerSpeed = dbValue;
}

double CfgKnife::GetRoateSpeed()
{
    return m_dbRotateSpeed;
}
void   CfgKnife::SetRoateSpeed(double dbValue)
{
    m_dbRotateSpeed = dbValue;
}

double CfgKnife::GetRotateAcceleration()
{
    return m_dbRotateAcceleration;
}
void   CfgKnife::SetRotateAcceleration(double dbValue)
{
    m_dbRotateAcceleration = dbValue;
}

double  CfgKnife::GetMaxPDDepth()
{
    return m_dbMaxPDDepth;
}
void    CfgKnife::SetMaxPDDepth(double dbValue)
{
    m_dbMaxPDDepth = dbValue;
}

double  CfgKnife::GetMaxPDDepth45()
{
    return m_dbMaxPDDepth45;
}
void    CfgKnife::SetMaxPDDepth45(double dbValue)
{
    m_dbMaxPDDepth45 = dbValue;
}

double  CfgKnife::GetMaxPUDepth()
{
    return m_dbMaxPUDepth;
}

void    CfgKnife::SetMaxPUDepth(double dbValue)
{
    m_dbMaxPUDepth = dbValue;
}

double  CfgKnife::GetAlignZCal()
{
    return m_dbAlignZCal;
}

void    CfgKnife::SetAlignZCal(double dbValue)
{
    m_dbAlignZCal=dbValue;
}

double  CfgKnife::GetAlignZ()
{
    return m_dbAlignZ;
}

void    CfgKnife::SetAlignZ(double dbValue)
{
    m_dbAlignZ=dbValue;
}

double  CfgKnife::GetWaitTimeBeforePD()
{
    return m_dbWaitTimeBeforePD;
}
void    CfgKnife::SetWaitTimeBeforePD(double dbValue)
{
    m_dbWaitTimeBeforePD = dbValue;
}


double  CfgKnife::GetWaitTimeAfterPD()
{
    return m_dbWaitTimeAfterPD;
}
void    CfgKnife::SetWaitTimeAfterPD(double dbValue)
{
    m_dbWaitTimeAfterPD = dbValue;
}


double  CfgKnife::GetWaitTimeBeforePU()
{
    return m_dbWaitTimeBeforePU;
}
void    CfgKnife::SetWaitTimeBeforePU(double dbValue)
{
    m_dbWaitTimeBeforePU = dbValue;
}


double  CfgKnife::GetWaitTimeAfterPU()
{
    return m_dbWaitTimeAfterPU;
}
void    CfgKnife::SetWaitTimeAfterPU(double dbValue)
{
    m_dbWaitTimeAfterPU = dbValue;
}


bool   CfgKnife::IsCutToolType(KnifeId emCutToolId)
{
    return (emCutToolId == m_emCutToolId);
}

bool   CfgKnife::IsCutToolType_Punch()
{
    if (m_emCutToolId == CUTTINGTOOL_RPUNCH || m_emCutToolId == CUTTINGTOOL_VPUNCH || m_emCutToolId == CUTTINGTOOL_SPUNCH)
        return true;

    return false;
}
bool   CfgKnife::IsCutToolType_Plot()
{
    if (m_emCutToolId == CUTTINGTOOL_PLOT)
        return true;

    return false;
}


bool   CfgKnife::IsCutToolType_Pen()
{
    if (m_emCutToolId == CUTTINGTOOL_PEN)
        return true;

    return false;
}


void   CfgKnife::UpdateOffsetFromApron(double x,double y)
{
    if (x>0.001 || y>0.001)
    {
        m_dbXOffset = x;
        m_dbYOffset = y;
    }
}

void CfgKnife::InitKnifeNames()
{
    m_sKnifeName = m_sCutToolName;
    if(m_emCutToolId != CUTTINGTOOL_NULL)
    {
        m_sKnifeName += QString::number(m_nKnifeId);
    }
}
void CfgKnife::LoadKnifeKey()
{
    m_sKnifeKey = m_sCutToolKey;
    if (m_nKnifeId <= 1)
    {
        if (m_sKnifeName.isEmpty())
        {
            m_sKnifeName = m_sKnifeKey;
        }
        return;
    }
    m_sKnifeKey += QString::number(m_nKnifeId);
}
void CfgKnife::LoadCutToolKey()
{
    switch(m_emCutToolId)
    {
    case CUTTINGTOOL_NULL:
        m_sCutToolKey = "NULT";
        break;
    case CUTTINGTOOL_PEN:
        m_sCutToolKey = "PEN";
        break;
    case CUTTINGTOOL_ROLL:
        m_sCutToolKey = "WKT";
        break;
    case CUTTINGTOOL_EOT:
        m_sCutToolKey = "EOT";
        break;
    case CUTTINGTOOL_POT:
        m_sCutToolKey = "POT";
        break;
    case CUTTINGTOOL_VPUNCH:
        m_sCutToolKey = "VPT";
        break;
    case CUTTINGTOOL_SPUNCH:
        m_sCutToolKey = "SPT";
        break;
    case CUTTINGTOOL_RPUNCH:
        m_sCutToolKey = "RPT";
        break;
    case CUTTINGTOOL_DRILL:
        m_sCutToolKey = "DPT";
        break;
    case CUTTINGTOOL_VCUT:
        m_sCutToolKey = "VCT";
        break;
    case CUTTINGTOOL_SCT:
        m_sCutToolKey = "SCT";
        break;
    case CUTTINGTOOL_KCT:
        m_sCutToolKey = "KCT";
        break;
    case CUTTINGTOOL_CREASE:
        m_sCutToolKey = "CTT";
        break;
    case CUTTINGTOOL_MILL:
        m_sCutToolKey = "MCT";
        break;
    case CUTTINGTOOL_EVCT:
        m_sCutToolKey = "EVCT";
        break;
    case CUTTINGTOOL_RCT:
        m_sCutToolKey = "RCT";
        break;
    case CUTTINGTOOL_DCT:
        m_sCutToolKey = "DCT";
        break;
    case CUTTINGTOOL_PLOT:
        m_sCutToolKey = "PLOT";
        break;
    case CUTTINGTOOL_REDLIGHT:
        m_sCutToolKey = "RDLT";
        break;
    case CUTTINGTOOL_LASER:
        m_sCutToolKey = "LAST";
        break;
    case CUTTINGTOOL_CAMERA:
        m_sCutToolKey = "CAMT";
        break;
    }
    m_sCutToolName = m_sCutToolKey;
}
void CfgKnife::Free()
{
    m_nVersion = 0;
    m_nCutInfoId = 0;						//刀具信息Id
    m_emCutToolId = CUTTINGTOOL_NULL;		//刀具类型
    m_nKnifeId = 0;							//刀具子类型
    m_nApronGuid = 0;						//刀具所在刀座Guid,0代表未装载
    m_emApronCMode = TOOLAPRON_CMODE_NULL;	//刀具的控制方式
    m_nGuid = 0;							//Guid值
    m_nColor = 0;							//颜色
    m_sCutToolName = "";					//刀具大类名
    m_sCutToolKey = "NULT";					//刀具大类关键字
    m_sKnifeKey = "";						//刀关键字
    m_sKnifeName = "";						//刀名
    m_dbDia = 0;							//直径
    m_dbXEtc = 0;			//X偏心距 (eccentricity)
    m_dbYEtc = 0;			//Y偏心距 (eccentricity)
    m_dbXOffset = 0;		//X偏移量
    m_dbYOffset = 0;		//Y偏移量
    m_dbWidth = 0;			//宽度
    m_dbHeight = 0;			//高度
    m_dbAngle = 0;			//角度
    m_dbTenacity = 0;		//韧度
    m_dbPUCstVal = 0;		//抬刀补偿量(过切量)
    m_dbPDCstVal = 0;		//落刀补偿量(过切量)
    m_dbToXAlixAngle = 0;   //刀与X轴正向夹角 (度)
    m_dbPUAngle = 30;		//抬刀角度 (度)
    m_dbPUSpeed = 10;		//抬刀速度 (m/s)
    m_dbPDSpeed = 10;		//落刀速度 (m/s)
    m_dbPDAcceleration = 1;	//落刀加速度(G)
    m_dbMoveSpeed = 10;     //运动速度(m/s)
    m_dbMoveAcceleration = 1;//运动加速度(g)
    m_dbRotateSpeed = 10;	//转刀速度
    m_dbRotateAcceleration = 1;//转刀加速度
    m_dbCornerSpeed = 10;	//转角速度
    m_dbMaxPDDepth = 1;		//最大落刀深度(mm)
    m_dbMaxPDDepth45 = 1;	//最大落刀深度(mm)
    m_dbMaxPUDepth = 1;		//最大抬刀深度(mm)
    m_dbAlignZ=0;			//对刀值
    m_dbAlignZCal=0;		//对刀偏差
    m_dbWaitTimeBeforePD = 0;	//落刀前等待时间(ms)
    m_dbWaitTimeAfterPD = 0;	//落刀后等待时间(ms)
    m_dbWaitTimeBeforePU = 0;	//抬刀前等待时间(ms)
    m_dbWaitTimeAfterPU = 0;	//抬刀后等待时间(ms)
}


bool CfgKnife::WritePrivateProfileString(QString strSect,QString strKey,QString strText,QString strConfigPath)
{
    QFile file(strConfigPath);
    if(!file.exists())
    {
        QMessageBox::information(this,QObject::tr("提示"),QObject::tr("初始化配置文件不存在"),QObject::tr("确定"));//setText(QObject::tr("软件配置文件不存在，以默认文件进行创建"))
        return false;
    }
    else
    {
        QSettings settingsObj(strConfigPath,QSettings::IniFormat);

        settingsObj.beginGroup(strSect);
        settingsObj.setValue(strKey,strText);
        settingsObj.endGroup();
    }
    return true;
}
bool CfgKnife::GetPrivateProfileString(QString strSect,QString strKey,QString *szBuf,QString strConfigPath)
{
    QFile file(strConfigPath);
    if(!file.exists())
    {
        QMessageBox::information(this,QObject::tr("提示"),QObject::tr("初始化配置文件不存在"),QObject::tr("确定"));//setText(QObject::tr("软件配置文件不存在，以默认文件进行创建"))
        return false;
    }
    else
    {
        QSettings settingsObj(strConfigPath,QSettings::IniFormat);

        settingsObj.beginGroup(strSect);
        QString tpstr= (settingsObj.value(strKey)).toString();
        if(tpstr == nullptr)
        {
            QStringList tpstrl = (settingsObj.value(strKey)).toStringList();
            tpstr = tpstrl.join(',');
        }
        *szBuf = tpstr;
        settingsObj.endGroup();
    }
    return true;
}
