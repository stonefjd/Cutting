#include "sdknife.h"

SDKnife::SDKnife(QWidget *parent) : QWidget(parent)
{
    Free();
}
SDKnife::SDKnife(short nCutToolId,short nKnifeId)
{
    Free();

    m_nCutToolId = nCutToolId;
    LoadCutToolKey();

    m_nKnifeId = nKnifeId;
    LoadKnifeKey();

    InitKnifeNames();
}
SDKnife::~SDKnife(void)
{
    Free();
}
SDKnife& SDKnife::operator = (const SDKnife& other)
{
    if (this == &other)
    {
        return *this;
    }

    m_nCutInfoId = other.m_nCutInfoId;		//对象id
    m_nCutToolId = other.m_nCutToolId;		//刀具类型
    m_nKnifeId = other.m_nKnifeId;			//刀具子类型
    m_nApronGuid = other.m_nApronGuid;		//刀具所在刀座Guid
    m_nApronCMode = other.m_nApronCMode;    //刀具刀座控制类型
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
SDKnife* SDKnife::Copied()
{
    SDKnife* pKnife = new SDKnife();
    *pKnife = *this;

    return pKnife;
}
bool SDKnife::Copy(SDKnife* pOther)
{
    if (pOther == nullptr)
        return false;

    *this = *pOther;

    return true;
}
bool SDKnife::Read(QDataStream *pFile)
{
    //本结构版本号
    int nVersion = 20190218;
//    MS_Readint_Binary(pFile,nVersion);

//    MS_Readshort_Binary(pFile,m_nCutInfoId);	//对象id
//    MS_Readshort_Binary(pFile,m_nCutToolId);	//刀具类型
//    MS_Readshort_Binary(pFile,m_nKnifeId);		//刀具子类型
//    MS_Readshort_Binary(pFile,m_nApronGuid);	//刀具所在刀座Guid

//    MS_Readshort_Binary(pFile,m_nApronCMode);	//刀具刀座的控制方式

//    MS_Readint_Binary(pFile,m_nGuid);			//Guid值
//    MS_Readint_Binary(pFile,m_nColor);			//颜色
//    MS_Readstring_Binary(pFile,m_sCutToolName);	//刀具大类名
//    MS_Readstring_Binary(pFile,m_sKnifeName);	//刀名
//    MS_Readdouble_Binary(pFile,m_dbDia);		//直径


//    LoadCutToolKey();
//    LoadKnifeKey();
//    CreadApronCMode();


//    MS_Readdouble_Binary(pFile,m_dbXEtc);		//X偏心距
//    MS_Readdouble_Binary(pFile,m_dbYEtc);		//Y偏心距


//    MS_Readdouble_Binary(pFile,m_dbXOffset);//X偏移
//    MS_Readdouble_Binary(pFile,m_dbYOffset);//Y偏移

//    MS_Readdouble_Binary(pFile,m_dbWidth);		//宽度
//    MS_Readdouble_Binary(pFile,m_dbHeight);		//高度
//    MS_Readdouble_Binary(pFile,m_dbAngle);		//角度
//    MS_Readdouble_Binary(pFile,m_dbTenacity);	//韧度


//    MS_Readdouble_Binary(pFile,m_dbPUCstVal);	//抬刀补偿量(过切量)
//    MS_Readdouble_Binary(pFile,m_dbPDCstVal);	//落刀补偿量(过切量)
//    MS_Readdouble_Binary(pFile,m_dbToXAlixAngle);//刀与X轴正向夹角 (度)
//    MS_Readdouble_Binary(pFile,m_dbPUAngle);	//抬刀角度 (度)
//    MS_Readdouble_Binary(pFile,m_dbPUSpeed);	//抬刀速度 (m/s)
//    MS_Readdouble_Binary(pFile,m_dbPDSpeed);	//落刀速度 (m/s)
//    MS_Readdouble_Binary(pFile,m_dbPDAcceleration);//落刀加速度(G)
//    MS_Readdouble_Binary(pFile,m_dbMoveSpeed);	//运动速度(m/s)
//    MS_Readdouble_Binary(pFile,m_dbMoveAcceleration);//运动加速度(g)

//    MS_Readdouble_Binary(pFile,m_dbRotateSpeed);//转刀速度
//    MS_Readdouble_Binary(pFile,m_dbRotateAcceleration);//转刀加速度

//    MS_Readdouble_Binary(pFile,m_dbCornerSpeed);//转角速度

//    MS_Readdouble_Binary(pFile,m_dbMaxPDDepth);	//最大落刀深度(mm)
//    MS_Readdouble_Binary(pFile,m_dbMaxPUDepth);	//最大落刀深度(mm)
//    MS_Readdouble_Binary(pFile,m_dbWaitTimeBeforePD);//落刀前等待时间(ms)
//    MS_Readdouble_Binary(pFile,m_dbWaitTimeAfterPD);//落刀后等待时间(ms)
//    MS_Readdouble_Binary(pFile,m_dbWaitTimeBeforePU);//抬刀前等待时间(ms)
//    MS_Readdouble_Binary(pFile,m_dbWaitTimeAfterPU);//抬刀后等待时间(ms)

//    MS_Readdouble_Binary(pFile,m_dbAlignZ);	//对刀值(mm)
//    MS_Readdouble_Binary(pFile,m_dbAlignZCal);	//对刀偏差(mm)

//    MS_Readdouble_Binary(pFile,m_dbMaxPDDepth45);	//最大落刀深度(mm)


    return true;
}
bool SDKnife::Save(QDataStream *pFile)
{

    int nVersion = 20190218;
//    MS_Writeint_Binary(pFile,m_nVersion);			//本结构版本

//    MS_Writeshort_Binary(pFile,m_nCutInfoId);	//对象id
//    MS_Writeshort_Binary(pFile,m_nCutToolId);	//刀具子类型Id
//    MS_Writeshort_Binary(pFile,m_nKnifeId);		//刀具子类型Id
//    MS_Writeshort_Binary(pFile,m_nApronGuid);	//刀具所在刀座Guid

//    MS_Writeshort_Binary(pFile,m_nApronCMode);	//刀具刀座的控制方式

//    MS_Writeint_Binary(pFile,m_nGuid);			//Guid值
//    MS_Writeint_Binary(pFile,m_nColor);			//颜色
//    MS_Writestring_Binary(pFile,m_sCutToolName);//刀具大类名
//    MS_Writestring_Binary(pFile,m_sKnifeName);	//刀具名
//    MS_Writedouble_Binary(pFile,m_dbDia);		//直径
//    MS_Writedouble_Binary(pFile,m_dbXEtc);		//X偏心距
//    MS_Writedouble_Binary(pFile,m_dbYEtc);		//Y偏心距

//    MS_Writedouble_Binary(pFile,m_dbXOffset);	//X偏移量
//    MS_Writedouble_Binary(pFile,m_dbYOffset);	//Y偏移量

//    MS_Writedouble_Binary(pFile,m_dbWidth);		//宽度
//    MS_Writedouble_Binary(pFile,m_dbHeight);	//高度
//    MS_Writedouble_Binary(pFile,m_dbAngle);		//角度
//    MS_Writedouble_Binary(pFile,m_dbTenacity);	//韧度
//    MS_Writedouble_Binary(pFile,m_dbPUCstVal);	//抬刀补偿量(过切量)
//    MS_Writedouble_Binary(pFile,m_dbPDCstVal);	//落刀补偿量(过切量)
//    MS_Writedouble_Binary(pFile,m_dbToXAlixAngle);//刀与X轴正向夹角 (度)
//    MS_Writedouble_Binary(pFile,m_dbPUAngle);	//抬刀角度 (度)
//    MS_Writedouble_Binary(pFile,m_dbPUSpeed);	//抬刀速度 (m/s)
//    MS_Writedouble_Binary(pFile,m_dbPDSpeed);	//落刀速度 (m/s)
//    MS_Writedouble_Binary(pFile,m_dbPDAcceleration);//落刀加速度(G)
//    MS_Writedouble_Binary(pFile,m_dbMoveSpeed);	//运动速度(m/s)
//    MS_Writedouble_Binary(pFile,m_dbMoveAcceleration);//运动加速度(g)

//    MS_Writedouble_Binary(pFile,m_dbRotateSpeed);	//转动速度(m/s)
//    MS_Writedouble_Binary(pFile,m_dbRotateAcceleration);//转动加速度(g)

//    MS_Writedouble_Binary(pFile,m_dbCornerSpeed);	//转角速度

//    MS_Writedouble_Binary(pFile,m_dbMaxPDDepth);	//最大落刀深度(mm)
//    MS_Writedouble_Binary(pFile,m_dbMaxPUDepth);	//最大落刀深度(mm)
//    MS_Writedouble_Binary(pFile,m_dbWaitTimeBeforePD);//落刀前等待时间(ms)
//    MS_Writedouble_Binary(pFile,m_dbWaitTimeAfterPD);//落刀后等待时间(ms)
//    MS_Writedouble_Binary(pFile,m_dbWaitTimeBeforePU);//抬刀前等待时间(ms)
//    MS_Writedouble_Binary(pFile,m_dbWaitTimeAfterPU);//抬刀后等待时间(ms)

//    MS_Readdouble_Binary(pFile,m_dbAlignZ);	//对刀值(mm)
//    MS_Readdouble_Binary(pFile,m_dbAlignZCal);	//对刀偏差(mm)

//    MS_Writedouble_Binary(pFile,m_dbMaxPDDepth45);	//最大落刀深度(mm)
    return true;
}

bool SDKnife::ReadPro(QDataStream *pFile)
{
    //本结构版本号
    int nVersion = 20190218;
//    MS_Readint_Binary(pFile,nVersion);

//    MS_Readshort_Binary(pFile,m_nCutInfoId);	//对象id
//    MS_Readshort_Binary(pFile,m_nCutToolId);	//刀具类型
//    MS_Readshort_Binary(pFile,m_nKnifeId);		//刀具子类型
//    MS_Readshort_Binary(pFile,m_nApronGuid);     //刀具所在刀座Guid
//    MS_Readint_Binary(pFile,m_nGuid);			//Giud值
//    MS_Readint_Binary(pFile,m_nColor);			//颜色
//    MS_Readstring_Binary(pFile,m_sCutToolName);	//刀具名
//    MS_Readstring_Binary(pFile,m_sKnifeName);		//刀具别名
//    MS_Readdouble_Binary(pFile,m_dbDia);		//直径
//    MS_Readdouble_Binary(pFile,m_dbXEtc);		//偏心距

    return true;
}
bool SDKnife::SavePro(QDataStream *pFile)
{
    int nVersion = 20190218;
//    MS_Writeint_Binary(pFile,m_nVersion);			//本结构版本

//    MS_Writeshort_Binary(pFile,m_nCutInfoId);	//对象id
//    MS_Writeshort_Binary(pFile,m_nCutToolId);	//刀具子类型Id
//    MS_Writeshort_Binary(pFile,m_nKnifeId);		//刀具子类型Id
//    MS_Writeshort_Binary(pFile,m_nApronGuid);	//刀具所在刀座Guid
//    MS_Writeint_Binary(pFile,m_nGuid);			//Guid值
//    MS_Writeint_Binary(pFile,m_nColor);			//颜色
//    MS_Writestring_Binary(pFile,m_sCutToolName);//刀具大类名
//    MS_Writestring_Binary(pFile,m_sKnifeName);	//刀具名
//    MS_Writedouble_Binary(pFile,m_dbDia);		//直径
//    MS_Writedouble_Binary(pFile,m_dbXEtc);		//偏心距


    return true;
}
int SDKnife::GetPrivateProfileString(QString sSect,QString sKey,QString sDefault,QString *szBuf,QString sConfigPath)
{
    QFile file(sConfigPath);
    if(!file.exists())
    {
        QMessageBox::information(this,QObject::tr("提示"),QObject::tr("初始化配置文件不存在"),QObject::tr("确定"));//setText(QObject::tr("软件配置文件不存在，以默认文件进行创建"))
        return false;
    }
    else
    {
        QSettings settingsObj(sConfigPath,QSettings::IniFormat);

        settingsObj.beginGroup(sSect);
        QString tpstr= (settingsObj.value(sKey)).toString();
        if(tpstr == nullptr)
        {
            QStringList tpstrl = (settingsObj.value(sKey)).toStringList();
            tpstr = tpstrl.join(',');
        }
        *szBuf = tpstr;
        settingsObj.endGroup();
    }

    return true;
}
bool SDKnife::ReadEx(QString sConfigPath,QString sSect)
{
//    sSect = "Knife";
//    sSect += QString::number(m_nGuid);

    QString sKey = "";
    QString sInfo = "";
    QString sDefault = "";

    QString *szBuf = new QString;

    int nRet = 0;

    //刀具大类Id
    sKey = "CutToolId";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_nCutToolId = sInfo.toShort();
    }
    else
    {
        return false;
    }

    //刀具子类Id
    sKey = "KnifeId";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_nKnifeId = sInfo.toShort();
    }
    else
    {
        return false;
    }

    //刀具所在刀座Guid
    sKey = "ApronGuid";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_nApronGuid = sInfo.toShort();
    }

    //刀具刀座的控制方式
    sKey = "ApronMode";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_nApronCMode = sInfo.toShort();
    }

    //Guid
    sKey = "KnifeGuid";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_nGuid = sInfo.toInt();
    }

    LoadCutToolKey();
    LoadKnifeKey();

    //颜色
    sKey = "KnifeColor";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_nColor = sInfo.toInt();
    }

    //刀具大类名
    sKey = "CutToolName";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        m_sCutToolName = *szBuf;
    }

    //刀具名
    sKey = "KnifeName";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        m_sKnifeName = *szBuf;
    }

    //直径
    sKey = "Diameter";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbDia = sInfo.toDouble();
    }

    //X偏心距
    sKey = "XEccVal";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbXEtc = sInfo.toDouble();
    }

    //Y偏心距
    sKey = "YEccVal";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbYEtc = sInfo.toDouble();
    }

    //X偏移量
    sKey = "XOffset";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbXOffset = sInfo.toDouble();
    }

    //Y偏移量
    sKey = "YOffset";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbYOffset = sInfo.toDouble();
    }

    //宽度
    sKey = "Width";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbWidth = sInfo.toDouble();
    }

    //高度
    sKey = "Height";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbHeight = sInfo.toDouble();
    }

    //角度
    sKey = "Angle";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbAngle = sInfo.toDouble();
    }
    //韧度
    sKey = "Tenacity";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbTenacity = sInfo.toDouble();
    }

    //抬刀补偿量(过切量)
    sKey = "PUOverCstVal";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbPUCstVal = sInfo.toDouble();
    }

    //落刀补偿量(过切量)
    sKey = "PDOverCstVal";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbPDCstVal = sInfo.toDouble();
    }

    //刀与X轴正向夹角 (度)
    sKey = "ToXAlixAngle";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbToXAlixAngle = sInfo.toDouble();
    }

    //抬刀角度 (度)
    sKey = "PUAngle";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbPUAngle = sInfo.toDouble();
    }

    //抬刀速度 (m/s)
    sKey = "PUSpeed";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbPUSpeed = sInfo.toDouble();
    }

    //落刀速度 (m/s)
    sKey = "PDSpeed";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbPDSpeed = sInfo.toDouble();
    }

    //落刀加速度(G)
    sKey = "PDAcc";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbPDAcceleration = sInfo.toDouble();
    }

    //运动速度(m/s)
    sKey = "MoveSpeed";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbMoveSpeed = sInfo.toDouble();
    }

    //运动加速度(g)
    sKey = "MoveAcc";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbMoveAcceleration = sInfo.toDouble();
    }

    //转动速度(m/s)
    sKey = "RotateSpeed";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbRotateSpeed = sInfo.toDouble();
    }

    //转动加速度(g)
    sKey = "RotateAcc";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbRotateAcceleration = sInfo.toDouble();
    }

    //转角速度
    sKey = "CornerSpeed";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbCornerSpeed = sInfo.toDouble();
    }

    //最大落刀深度(mm)
    sKey = "MaxPDDepth";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbMaxPDDepth = sInfo.toDouble();
    }

    sKey = "MaxPDDepth45";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbMaxPDDepth45 = sInfo.toDouble();
    }

    //最大抬刀深度(mm)
    sKey = "MaxPUDepth";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbMaxPUDepth = sInfo.toDouble();
        if((m_dbMaxPUDepth>m_dbMaxPDDepth)||(m_dbMaxPUDepth<0))
            m_dbMaxPUDepth=m_dbMaxPDDepth;
    }
    else
        m_dbMaxPUDepth=m_dbMaxPDDepth;

    //对刀值(mm)
    sKey = "AlignZ";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbAlignZ = sInfo.toDouble();
    }
    else
        m_dbAlignZ=0;

    //对刀偏差(mm)
    sKey = "AlignZCal";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbAlignZCal = sInfo.toDouble();
    }
    else
        m_dbAlignZCal=0;

    //落刀前等待时间(ms)
    sKey = "WTBeforePD";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbWaitTimeBeforePD = sInfo.toDouble();
    }

    //落刀后等待时间(ms)
    sKey = "WTAfterPD";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbWaitTimeAfterPD = sInfo.toDouble();
    }

    //抬刀前等待时间(ms)
    sKey = "WTBeforePU";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbWaitTimeBeforePU = sInfo.toDouble();
    }

    //抬刀后等待时间(ms)
    sKey = "WTAfterPU";
    nRet = GetPrivateProfileString(sSect, sKey, sDefault, szBuf, sConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        m_dbWaitTimeAfterPU = sInfo.toDouble();
    }


    return true;
}
void SDKnife::WritePrivateProfileString(QString sSect,QString sKey,QString sInfo,QString sConfigPath)
{

}
bool SDKnife::SaveEx(QString sConfigPath,QString sSect)
{
    //string sSect = "Knife";
    //sSect += SDString::intTostring(m_nGuid);

    QString sKey = "";
    QString sInfo = "";

    //刀具大类Id
    sKey = "CutToolId";
    sInfo = QString::number(static_cast<int>(m_nCutToolId));
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
    sInfo = QString::number(static_cast<int>(m_nApronCMode));
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

    return true;
}
void SDKnife::Free()
{
    m_nVersion = 0;
    m_nCutInfoId = 0;						//刀具信息Id
    m_nCutToolId = CUTTINGTOOL_PEN;			//刀具类型
    m_nKnifeId = 0;							//刀具子类型
    m_nApronGuid = 1;						//刀具所在刀座Guid
    m_nApronCMode = 0;						//刀具的控制方式
    m_nGuid = 1;							//Guid值
    m_nColor = 0;							//颜色
    m_sCutToolName = "";					//刀具大类名
    m_sCutToolKey = "PEN";					//刀具大类关键字
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

bool SDKnife::IsSameParam(SDKnife* pOther)
{
    if (pOther == nullptr)
        return false;


    return true;
}

void  SDKnife::SetCutInfoId(short nCutInfoId)
{
    m_nCutInfoId = nCutInfoId;
}
short SDKnife::GetCutInfoId()
{
    return m_nCutInfoId;
}

void   SDKnife::SetCutToolId(short nCutToolId)
{
    m_nCutToolId = nCutToolId;
    LoadCutToolKey();
}
short  SDKnife::GetCutToolId()
{
    return m_nCutToolId;
}

void   SDKnife::SetKnifeId(short nKnifeId)
{
    m_nKnifeId = nKnifeId;
    LoadKnifeKey();
    //m_nGuid = (m_nCutToolId|(m_nKnifeId<<8));// m_nKnifeId<<8 + m_nCutToolId;
}
short  SDKnife::GetKnifeId()
{
    return m_nKnifeId;
}

void   SDKnife::SetApronGuid(short nMachineHead,short nApronIndex)
{
    m_nApronGuid = static_cast<short>(nApronIndex | (nMachineHead<<8));
}
void   SDKnife::SetApronGuid(short nApronGuid)
{
    m_nApronGuid = nApronGuid;
}
short  SDKnife::GetApronGuid()
{
    return m_nApronGuid;
}

short  SDKnife::GetMachinIndex()
{
    short nSrcMachineId = ((m_nApronGuid>>8)&0xff);
    return nSrcMachineId;
}

short  SDKnife::GetApronIndex()
{
    short nApronId = ((m_nApronGuid)&0xff);
    return nApronId;
}

void   SDKnife::SetApronCMode(short nMode)
{
    m_nApronCMode = nMode;
}
short  SDKnife::GetApronCMode()
{
    return m_nApronCMode;
}

void   SDKnife::CreadApronCMode()
{
    switch(m_nCutToolId)
    {
    case CUTTINGTOOL_PEN:
        m_nApronCMode = TOOLAPRON_CMODE_PEN;
        break;
    case CUTTINGTOOL_ROLL:
        m_nApronCMode = TOOLAPRON_CMODE_ROLL;
        break;
    case CUTTINGTOOL_EOT:
        m_nApronCMode = TOOLAPRON_CMODE_EOT;
        break;
    case CUTTINGTOOL_POT:
        m_nApronCMode = TOOLAPRON_CMODE_POT;
        break;
    case CUTTINGTOOL_VPUNCH:
        m_nApronCMode = TOOLAPRON_CMODE_VPUNCH;
        break;
    case CUTTINGTOOL_SPUNCH:
        m_nApronCMode = TOOLAPRON_CMODE_SPUNCH;
        break;
    case CUTTINGTOOL_RPUNCH:
        m_nApronCMode = TOOLAPRON_CMODE_RPUNCH;
        break;
    case CUTTINGTOOL_DRILL:
        m_nApronCMode = TOOLAPRON_CMODE_DRILL;
        break;
    case CUTTINGTOOL_VCUT:
        m_nApronCMode = TOOLAPRON_CMODE_VCUT;
        break;
    case CUTTINGTOOL_SCT:
        m_nApronCMode = TOOLAPRON_CMODE_SCT;
        break;
    case CUTTINGTOOL_KCT:
        m_nApronCMode = TOOLAPRON_CMODE_KCT;
        break;
    case CUTTINGTOOL_CREASE:
        m_nApronCMode = TOOLAPRON_CMODE_CREASE;
        break;
    case CUTTINGTOOL_MILL:
        m_nApronCMode = TOOLAPRON_CMODE_MILL;
        break;
    case CUTTINGTOOL_EVCT:
        m_nApronCMode = TOOLAPRON_CMODE_EVCT;
        break;
    case CUTTINGTOOL_RCT:
        m_nApronCMode = TOOLAPRON_CMODE_RCT;
        break;
    case CUTTINGTOOL_DCT:
        m_nApronCMode = TOOLAPRON_CMODE_DCT;
        break;
    case CUTTINGTOOL_PLOT:
        m_nApronCMode = TOOLAPRON_CMODE_PLOT;
        break;
    case CUTTINGTOOL_REDLIGHT:
        m_nApronCMode = TOOLAPRON_CMODE_REDLIGHT;
        break;
    case CUTTINGTOOL_LASER:
        m_nApronCMode = TOOLAPRON_CMODE_LASER;
        break;
    case CUTTINGTOOL_CAMERA:
        m_nApronCMode = TOOLAPRON_CMODE_CAMERA;
        break;
    case CUTTINGTOOL_NULL:
        m_nApronCMode = TOOLAPRON_CMODE_NULL;
        break;
    default:
        break;
    }
}

void   SDKnife::SetColor(int nClr)
{
    m_nColor = nClr;
}
int    SDKnife::GetColor()
{
    return m_nColor;
}

void   SDKnife::SetCutToolName(QString sToolName)
{
    m_sCutToolName = sToolName;
}
QString SDKnife::GetCutToolName()
{
    return m_sCutToolName;
}

void   SDKnife::SetCutToolKey(QString sKey)
{
    m_sCutToolKey = sKey;
}
QString SDKnife::GetCutToolKey()
{
    return m_sCutToolKey;
}

void   SDKnife::SetKnifeKey(QString sKey)
{
    m_sKnifeKey = sKey;
}

QString   SDKnife::GetKnifeKey()
{
    return m_sKnifeKey;
}

void   SDKnife::LoadKnifeKey()
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

void   SDKnife::LoadCutToolKey()
{
    switch(m_nCutToolId)
    {
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
    case CUTTINGTOOL_NULL:
        m_sCutToolKey = "NULT";
        break;
    default:
        break;
    }
    m_sCutToolName = m_sCutToolKey;
}

void   SDKnife::SetKnifeName(QString sName)
{
    if (!sName.isEmpty())
        m_sKnifeName = sName;
}
QString SDKnife::GetKnifeName()
{
    if (m_sKnifeName.isEmpty())
    {
        InitKnifeNames();
    }

    return m_sKnifeName;
}

void   SDKnife::InitKnifeNames()
{
    m_sKnifeName = m_sCutToolName;
    if(m_nCutToolId != CUTTINGTOOL_PEN)
    {
        m_sKnifeName += QString::number(m_nKnifeId);
    }
}
void   SDKnife::UpdateOffsetFromApron(double x,double y)
{
    if (x>0.001 || y>0.001)
    {
        m_dbXOffset = x;
        m_dbYOffset = y;
    }
}
void   SDKnife::CreateGuid()
{
    m_nGuid = (m_nCutToolId|(m_nKnifeId<<8));// m_nKnifeId<<8 + m_nCutToolId;


    CreadApronCMode();
}
QString SDKnife::GetGuidString()
{
    //string sInfo = SDString::intTostring(m_nGuid);
    QString sInfo = QString::number(m_nCutToolId);
    sInfo += "-";
    sInfo += QString::number(m_nKnifeId);
    return sInfo;
}
void   SDKnife::SetGuid(int nGuid,bool bSetKnifeId)
{
    m_nGuid = nGuid;

    if (bSetKnifeId)
    {
        //重新设置刀片Id
        m_nKnifeId = GUID2KNIFEID(nGuid);//(short)((nGuid>>8)&0xff);

        //重新设置刀具id
        m_nCutToolId = GUID2CUTTOOLID(nGuid);//(short)(nGuid&0xff);
    }
}
int    SDKnife::GetGuid()
{
    return m_nGuid;
}

void   SDKnife::SetDia(double dbValue)
{
    m_dbDia = dbValue;
}
double SDKnife::GetDia()
{
    return m_dbDia;
}


void   SDKnife::SetXEtc(double dbValue)
{
    m_dbXEtc = dbValue;
}
double SDKnife::GetXEtc()
{
    return m_dbXEtc;
}

void   SDKnife::SetYEtc(double dbValue)
{
    m_dbYEtc = dbValue;
}
double SDKnife::GetYEtc()
{
    return m_dbYEtc;
}

void   SDKnife::SetXOffset(double dbValue)
{
    m_dbXOffset = dbValue;
}
double SDKnife::GetXOffset()
{
    return m_dbXOffset;
}

void   SDKnife::SetYOffset(double dbValue)
{
    m_dbYOffset = dbValue;
}
double SDKnife::GetYOffset()
{
    return m_dbYOffset;
}

void   SDKnife::SetWidth(double dbValue)
{
    m_dbWidth = dbValue;
}
double SDKnife::GetWidth()
{
    return m_dbWidth;
}

void   SDKnife::SetHeight(double dbValue)
{
    m_dbHeight = dbValue;
}
double SDKnife::GetHeight()
{
    return m_dbHeight;
}

void   SDKnife::SetAngle(double dbValue)
{
    m_dbAngle = dbValue;
}
double SDKnife::GetAngle()
{
    return m_dbAngle;
}

void   SDKnife::SetTenacity(double dbValue)
{
    m_dbTenacity = dbValue;
}
double SDKnife::GetTenacity()
{
    return m_dbTenacity;
}

double  SDKnife::GetPUCstVal()
{
    return  m_dbPUCstVal;
}
void    SDKnife::SetPUCstVal(double dbValue)
{
    m_dbPUCstVal = dbValue;
}


double  SDKnife::GetPDCstVal()
{
    return m_dbPDCstVal;
}
void    SDKnife::SetPDCstVal(double dbValue)
{
    m_dbPDCstVal = dbValue;
}

double  SDKnife::GetXAlixAngle()
{
    return m_dbToXAlixAngle;
}
void    SDKnife::SetXAlixAngle(double dbValue)
{
    m_dbToXAlixAngle = dbValue;
}


double  SDKnife::GetPUAngle()
{
    return m_dbPUAngle;
}
void    SDKnife::SetPUAngle(double dbValue)
{
    m_dbPUAngle = dbValue;
}


double  SDKnife::GetPUSpeed()
{
    return m_dbPUSpeed;
}
void    SDKnife::SetPUSpeed(double dbValue)
{
    m_dbPUSpeed = dbValue;
}


double  SDKnife::GetPDSpeed()
{
    return m_dbPDSpeed;
}
void    SDKnife::SetPDSpeed(double dbValue)
{
    m_dbPDSpeed = dbValue;
}


double  SDKnife::GetPDAcceleration()
{
    return m_dbPDAcceleration;
}
void    SDKnife::SetPDAcceleration(double dbValue)
{
    m_dbPDAcceleration = dbValue;
}


double  SDKnife::GetMoveSpeed()
{
    return m_dbMoveSpeed;
}
void    SDKnife::SetMoveSpeed(double dbValue)
{
    m_dbMoveSpeed = dbValue;
}


double  SDKnife::GetMoveAcceleration()
{
    return m_dbMoveAcceleration;
}
void    SDKnife::SetMoveAcceleration(double dbValue)
{
    m_dbMoveAcceleration = dbValue;
}

double  SDKnife::GetCornerSpeed()
{
    return m_dbCornerSpeed;
}
void    SDKnife::SetCornerSpeed(double dbValue)
{
    m_dbCornerSpeed = dbValue;
}

double SDKnife::GetRoateSpeed()
{
    return m_dbRotateSpeed;
}
void   SDKnife::SetRoateSpeed(double dbValue)
{
    m_dbRotateSpeed = dbValue;
}

double SDKnife::GetRotateAcceleration()
{
    return m_dbRotateAcceleration;
}
void   SDKnife::SetRotateAcceleration(double dbValue)
{
    m_dbRotateAcceleration = dbValue;
}

double  SDKnife::GetMaxPDDepth()
{
    return m_dbMaxPDDepth;
}
void    SDKnife::SetMaxPDDepth(double dbValue)
{
    m_dbMaxPDDepth = dbValue;
}

double  SDKnife::GetMaxPDDepth45()
{
    return m_dbMaxPDDepth45;
}
void    SDKnife::SetMaxPDDepth45(double dbValue)
{
    m_dbMaxPDDepth45 = dbValue;
}

double  SDKnife::GetMaxPUDepth()
{
    return m_dbMaxPUDepth;
}

void    SDKnife::SetMaxPUDepth(double dbValue)
{
    m_dbMaxPUDepth = dbValue;
}

double  SDKnife::GetAlignZCal()
{
    return m_dbAlignZCal;
}

void    SDKnife::SetAlignZCal(double dbValue)
{
    m_dbAlignZCal=dbValue;
}

double  SDKnife::GetAlignZ()
{
    return m_dbAlignZ;
}

void    SDKnife::SetAlignZ(double dbValue)
{
    m_dbAlignZ=dbValue;
}

double  SDKnife::GetWaitTimeBeforePD()
{
    return m_dbWaitTimeBeforePD;
}
void    SDKnife::SetWaitTimeBeforePD(double dbValue)
{
    m_dbWaitTimeBeforePD = dbValue;
}


double  SDKnife::GetWaitTimeAfterPD()
{
    return m_dbWaitTimeAfterPD;
}
void    SDKnife::SetWaitTimeAfterPD(double dbValue)
{
    m_dbWaitTimeAfterPD = dbValue;
}


double  SDKnife::GetWaitTimeBeforePU()
{
    return m_dbWaitTimeBeforePU;
}
void    SDKnife::SetWaitTimeBeforePU(double dbValue)
{
    m_dbWaitTimeBeforePU = dbValue;
}


double  SDKnife::GetWaitTimeAfterPU()
{
    return m_dbWaitTimeAfterPU;
}
void    SDKnife::SetWaitTimeAfterPU(double dbValue)
{
    m_dbWaitTimeAfterPU = dbValue;
}

void   SDKnife::SetDefaultKnifeInfo(SDKnife* pTestKnife)
{
    if (pTestKnife == nullptr)
        return;
}

bool   SDKnife::IsCutToolType(short nCutToolId)
{
    return (nCutToolId == m_nCutToolId);
}

bool   SDKnife::IsCutToolType_Punch()
{
    if (m_nCutToolId == CUTTINGTOOL_RPUNCH || m_nCutToolId == CUTTINGTOOL_VPUNCH || m_nCutToolId == CUTTINGTOOL_SPUNCH)
        return true;

    return false;
}
bool   SDKnife::IsCutToolType_Plot()
{
    if (m_nCutToolId == CUTTINGTOOL_PLOT)
        return true;

    return false;
}


bool   SDKnife::IsCutToolType_Pen()
{
    if (m_nCutToolId == CUTTINGTOOL_PEN)
        return true;

    return false;
}
