#include "sdcuttoollib.h"

SDCutTool::SDCutTool(void)
{
    m_nCutToolId = CUTTINGTOOL_PEN;
    m_sCutToolKey = "PEN";
    m_sCutToolName = "PEN";
    m_nMaxKnifeId = 1;   //1-20
    m_nMaxKnifeId1 = 21; //21--40
    m_nMaxKnifeId2 = 41; //41-60
}
SDCutTool::SDCutTool(short nCutToolId)
{
    m_nCutToolId = nCutToolId;
    LoadCutToolKey();
    m_nMaxKnifeId = 1;
    m_nMaxKnifeId1 = 21;
    m_nMaxKnifeId2 = 41;
}

SDCutTool::~SDCutTool(void)
{
    FreeKnifes();
}

SDCutTool& SDCutTool::operator = (const SDCutTool& other)
{
    if (this == &other)
    {
        return *this;
    }

    FreeKnifes();

    m_nCutToolId = other.m_nCutToolId;
    m_sCutToolKey = other.m_sCutToolKey;
    m_sCutToolName = other.m_sCutToolName;
    m_nMaxKnifeId = other.m_nMaxKnifeId;
    m_nMaxKnifeId1 = other.m_nMaxKnifeId1;
    m_nMaxKnifeId2 = other.m_nMaxKnifeId2;
    for(int i = 0; i < other.m_stvKnifes.size(); i++)
    {
        SDKnife* pSrcKnife = other.m_stvKnifes.at(i);
        SDKnife* pDesKnife = pSrcKnife->Copied();

        m_stvKnifes.push_back(pDesKnife);
    }

    return *this;
}
void SDCutTool::FreeKnifes()
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        delete m_stvKnifes.at(i);
    }
    m_stvKnifes.clear();
}
QList<SDKnife*>*	SDCutTool::GetSubKnifes()
{
    return &m_stvKnifes;
}

bool SDCutTool::AddKnife(SDKnife* pKnife,int nIdType)
{
    if (pKnife == nullptr)
        return false;

    pKnife->SetCutToolId(m_nCutToolId);

    int nMaxKnifeId = GetMaxKnifeId(nIdType);
    pKnife->SetKnifeId(static_cast<short>(nMaxKnifeId++));
    SetMaxKnifeId(static_cast<short>(nMaxKnifeId),nIdType);

    pKnife->CreateGuid();

    m_stvKnifes.push_back(pKnife);

    return true;
}

bool SDCutTool::AddKnifePro(SDKnife* pKnife)
{
    if (pKnife == nullptr)
        return false;

    m_stvKnifes.push_back(pKnife);

    return true;
}

SDKnife* SDCutTool::NewKnife(int nIdType)
{
    SDKnife* pKnife = new SDKnife();
    pKnife->SetCutToolId(m_nCutToolId);


    int nMaxKnifeId = GetMaxKnifeId(nIdType);
    pKnife->SetKnifeId(static_cast<short>(nMaxKnifeId++));
    SetMaxKnifeId(static_cast<short>(nMaxKnifeId),nIdType);


    pKnife->CreateGuid();

    m_stvKnifes.push_back(pKnife);

    return pKnife;
}

SDKnife* SDCutTool::NewKnife(int nApronCMode,int nClr,double dbDia,double dbAngle,int nIdType)
{
    SDKnife* pKnife = new SDKnife();
    pKnife->SetCutToolId(m_nCutToolId);
    pKnife->SetApronCMode(static_cast<short>(nApronCMode));

    int nMaxKnifeId = GetMaxKnifeId(nIdType);
    pKnife->SetKnifeId(static_cast<short>(nMaxKnifeId++));
    SetMaxKnifeId(static_cast<short>(nMaxKnifeId),nIdType);


    pKnife->SetColor(nClr);
    pKnife->SetDia(dbDia);
    pKnife->SetAngle(dbAngle);

    pKnife->CreateGuid();

    pKnife->LoadCutToolKey();
    pKnife->LoadKnifeKey();
    pKnife->InitKnifeNames();

    m_stvKnifes.push_back(pKnife);

    return pKnife;
}

SDKnife* SDCutTool::GetKnifeById(short nKnifeId)
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        SDKnife* pKnife = m_stvKnifes.at(i);
        if (pKnife->GetKnifeId() == nKnifeId)
            return pKnife;
    }

    return nullptr;
}

SDKnife* SDCutTool::GetKnifeByIndex(int nIndex)
{
    if (nIndex < m_stvKnifes.size() && nIndex >= 0)
    {
        return m_stvKnifes.at(nIndex);
    }

    return nullptr;
}

SDKnife* SDCutTool::GetKnifeByKey(QString sKey)
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        SDKnife* pKnife = m_stvKnifes.at(i);
        if (pKnife->GetKnifeKey() == sKey)
            return pKnife;
    }

    return nullptr;
}

bool     SDCutTool::DelKnifeById(short nKnifeId)
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        SDKnife* pKnife = m_stvKnifes.at(i);
        if (pKnife->GetKnifeId() == nKnifeId)
        {
            delete pKnife;
            m_stvKnifes.erase(m_stvKnifes.begin()+i);
            return true;
        }
    }

    return false;
}
bool     SDCutTool::DelKnife(SDKnife* pTestKnife)
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        SDKnife* pKnife = m_stvKnifes.at(i);
        if (pKnife == pTestKnife)
        {
            delete pKnife;
            m_stvKnifes.erase(m_stvKnifes.begin()+i);
            return true;
        }
    }

    return false;
}
bool     SDCutTool::DelKnifeByKey(QString sKey)
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        SDKnife* pKnife = m_stvKnifes.at(i);
        if (pKnife->GetKnifeKey() == sKey)
        {
            delete pKnife;
            m_stvKnifes.erase(m_stvKnifes.begin()+i);
            return true;
        }
    }

    return false;
}
void    SDCutTool::SetMaxKnifeId(short nMaxKnifeId,int nIdType)
{
    switch(nIdType)
    {
    case 0:
        m_nMaxKnifeId = nMaxKnifeId;
        break;
    case 1:
        m_nMaxKnifeId1 = nMaxKnifeId;
        break;
    case 2:
        m_nMaxKnifeId2 = nMaxKnifeId;
        break;
    default:
        m_nMaxKnifeId = nMaxKnifeId;
        break;
    }

}
short  SDCutTool::GetMaxKnifeId(int nIdType)
{
    switch(nIdType)
    {
    case 0:
        return m_nMaxKnifeId;
    case 1:
        return m_nMaxKnifeId1;
    case 2:
        return m_nMaxKnifeId2;
    default:
        return m_nMaxKnifeId;
    }
}

void   SDCutTool::SetCutToolId(short nCutToolId)
{
    m_nCutToolId = nCutToolId;
}
short  SDCutTool::GetCutToolId()
{
    return m_nCutToolId;
}

void   SDCutTool::SetCutToolKey(QString sKey)
{
    m_sCutToolKey = sKey;
}
QString SDCutTool::GetCutToolKey()
{
    return m_sCutToolKey;
}

void   SDCutTool::SetCutToolName(QString sName)
{
    m_sCutToolName = sName;
}
QString SDCutTool::GetCutToolName()
{
    return m_sCutToolName;
}

void   SDCutTool::LoadCutToolKey()
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

bool SDCutTool::Read(QDataStream *pFile)
{
    if (pFile == nullptr)
        return false;

//    FreeKnifes();

//    MS_Readshort_Binary(pFile,m_nCutToolId);
//    MS_Readshort_Binary(pFile,m_nMaxKnifeId);
//    LoadCutToolKey();

//    int nKnifeCount = 0;
//    MS_Readint_Binary(pFile,nKnifeCount);
//    if (nKnifeCount < -1 || nKnifeCount > 100)
//        return false;

//    for(int i = 0; i < nKnifeCount; i++)
//    {
//        SDKnife* pKnife = new SDKnife();
//        if (!pKnife->Read(pFile))
//        {
//            delete pKnife;
//            return false;
//        }

//        m_stvKnifes.push_back(pKnife);
//    }

    return true;
}
bool SDCutTool::Save(QDataStream *pFile)
{
    if (pFile == nullptr)
        return false;

//    MS_Writeshort_Binary(pFile,m_nCutToolId);
//    MS_Writeshort_Binary(pFile,m_nMaxKnifeId);

//    int nKnifeCount = (int)m_stvKnifes.size();
//    MS_Writeint_Binary(pFile,nKnifeCount);

//    for(int i = 0; i < nKnifeCount; i++)
//    {
//        SDKnife* pKnife = m_stvKnifes.at(i);
//        if (!pKnife->Save(pFile))
//        {
//            return false;
//        }
//    }

    return true;
}

SDCutToolLib::SDCutToolLib(QWidget *parent) : QWidget(parent)
{

}
SDCutToolLib::~SDCutToolLib(void)
{
    FreeCutTools();
}

SDCutToolLib& SDCutToolLib::operator = (const SDCutToolLib& other)
{
    if (this == &other)
    {
        return *this;
    }

    FreeCutTools();

    //m_strConfigDir = other.m_strConfigDir;
    for(int i = 0; i < other.m_stvCutTools.size(); i++)
    {
        SDCutTool* pSrcCutTool = other.m_stvCutTools.at(i);
        SDCutTool* pDesCutTool = new SDCutTool();
        *pDesCutTool = *pSrcCutTool;
        m_stvCutTools.push_back(pDesCutTool);
    }

    return *this;
}

void SDCutToolLib::FreeCutTools()
{
    for(int i = 0; i < m_stvCutTools.size(); i++)
    {
        delete m_stvCutTools.at(i);
    }
    m_stvCutTools.clear();
}
QList<SDCutTool*>*	SDCutToolLib::GetCutTools()
{
    return &m_stvCutTools;
}

void SDCutToolLib::GetAllKnifes(QList<SDKnife*> &vKnifes)
{
    for(int i = 0; i < m_stvCutTools.size(); i++)
    {
        SDCutTool* pCutTool = m_stvCutTools.at(i);

        QList<SDKnife*>* pKnifes = pCutTool->GetSubKnifes();
        for(int j = 0; j < pKnifes->size(); j++)
        {
            SDKnife* pKnife = pKnifes->at(j);
            vKnifes.push_back(pKnife);
        }
    }
}

void SDCutToolLib::GetAllKnifeNames(QList<QString> &vNames)
{
    for(int i = 0; i < m_stvCutTools.size(); i++)
    {
        SDCutTool* pCutTool = m_stvCutTools.at(i);

        QList<SDKnife*>* pKnifes = pCutTool->GetSubKnifes();
        for(int j = 0; j < pKnifes->size(); j++)
        {
            SDKnife* pKnife = pKnifes->at(j);

            vNames.push_back(pKnife->GetKnifeName());
        }
    }
}


void SDCutToolLib::GetAllKnifeKeys(QList<QString> &vKeys)
{
    for(int i = 0; i < m_stvCutTools.size(); i++)
    {
        SDCutTool* pCutTool = m_stvCutTools.at(i);

        QList<SDKnife*>* pKnifes = pCutTool->GetSubKnifes();
        for(int j = 0; j < pKnifes->size(); j++)
        {
            SDKnife* pKnife = pKnifes->at(j);

            vKeys.push_back(pKnife->GetKnifeKey());
        }
    }
}

bool SDCutToolLib::AddCutTool(SDCutTool* pCutTool)
{
    if (pCutTool == nullptr)
        return false;

    m_stvCutTools.push_back(pCutTool);

    return true;
}
SDCutTool* SDCutToolLib::GetCutToolById(short nCutToolId)
{
    for(int i = 0; i < m_stvCutTools.size(); i++)
    {
        SDCutTool* pCutTool = m_stvCutTools.at(i);
        if (pCutTool->GetCutToolId() == nCutToolId)
            return pCutTool;
    }

    return nullptr;
}

SDCutTool* SDCutToolLib::GetCutToolByIndex(int nIndex)
{
    if (nIndex < m_stvCutTools.size() && nIndex >= 0)
    {
        return m_stvCutTools.at(nIndex);
    }

    return nullptr;
}

SDCutTool* SDCutToolLib::GetCutToolByKey(QString sKey)
{
    for(int i = 0; i < m_stvCutTools.size(); i++)
    {
        SDCutTool* pCutTool = m_stvCutTools.at(i);
        if (pCutTool->GetCutToolKey() == sKey)
            return pCutTool;
    }

    return nullptr;
}

SDKnife*   SDCutToolLib::GetKnifeById(short nCutToolId, short nKnifeId)
{
    SDCutTool* pCutTool = GetCutToolById(nCutToolId);
    if (pCutTool != nullptr)
    {
        SDKnife* pKnife = pCutTool->GetKnifeById(nKnifeId);
        return pKnife;
    }
    return nullptr;
}

SDKnife*   SDCutToolLib::GetKnifeByGuid(int nGuid)
{
    short nCutToolId = static_cast<short>(nGuid&0xff);
    short nKnifeId = static_cast<short>((nGuid>>8)&0xff);

    return GetKnifeById(nCutToolId,nKnifeId);
}

SDKnife*   SDCutToolLib::GetFirstCModeKnife(short nCModeId)
{
    for(int k = 0; k < m_stvCutTools.size(); k++)
    {
        SDCutTool* pCutTool = m_stvCutTools.at(k);

        SDKnife* pKnife = pCutTool->GetKnifeByIndex(0);
        if (pKnife != nullptr && pKnife->GetApronCMode() == nCModeId)
        {
            return pKnife;
        }
    }
    return nullptr;
}

void SDCutToolLib::GetAllKnifesOnCMode(short nCModeId,QList<SDKnife*> &vKnifes)
{
    for(int k = 0; k < m_stvCutTools.size(); k++)
    {
        SDCutTool* pCutTool = m_stvCutTools.at(k);

        QList<SDKnife*> *pKnifes = pCutTool->GetSubKnifes();
        for(int j = 0; j < pKnifes->size(); j++)
        {
            SDKnife* pKnife = pKnifes->at(j);
            if (pKnife->GetApronCMode() == nCModeId)
            {
                vKnifes.push_back(pKnife);
            }
        }
    }
}
void       SDCutToolLib::UpdateKnifeInfo(SDKnife* pKinfe)
{
    if (pKinfe == nullptr)
        return;

    SDKnife* pDesKnife = this->GetKnifeById(pKinfe->GetCutToolId(),pKinfe->GetKnifeId());
    if (pDesKnife != nullptr)
    {
        pDesKnife->Copy(pKinfe);
    }
}
void       SDCutToolLib::UpdateKnifeInfo(QList<SDKnife*> *pKnifes)
{
    for(int i = 0; i < pKnifes->size(); i++)
    {
        UpdateKnifeInfo(pKnifes->at(i));
    }
}

void SDCutToolLib::InitDefaultCutToolLib()
{
    //测试
    int nClr = 0xFFFFFF;

    SDCutTool* pCutTool = new SDCutTool;
    SDKnife* pKnife = new SDKnife;

    //PEN
    pCutTool = new SDCutTool(CUTTINGTOOL_PEN);
        nClr = 0xFFFFFF;
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_PEN,nClr,2,0,0);
    this->AddCutTool(pCutTool);

    //ROLL
    pCutTool = new SDCutTool(CUTTINGTOOL_ROLL);

        nClr = 0xFF00FF;
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_ROLL,nClr,2,0,0);

    this->AddCutTool(pCutTool);

    //EOT
    pCutTool = new SDCutTool(CUTTINGTOOL_EOT);

        nClr = 0xFF0000;
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_EOT,nClr,2,30,0);

        //nClr = RGB(255,0,0);
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_EOT,nClr,2,45,0);

    this->AddCutTool(pCutTool);



    //Drill
    pCutTool = new SDCutTool(CUTTINGTOOL_DRILL);
        nClr = 0x00FF40;
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_DRILL,nClr,3,0,0);
    this->AddCutTool(pCutTool);



    //VPUNCH
    pCutTool = new SDCutTool(CUTTINGTOOL_VPUNCH);

        nClr = 0xFFFF00;
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_VPUNCH,nClr,5,45,0);

        //V型刀下的一字冲刀 在此处设置是为了实现安装两个一字冲孔刀
        nClr = 0xFFFF80;
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_VPUNCH,nClr,3,0,1);

        nClr = 0xFFFF80;
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_VPUNCH,nClr,5,0,1);

        //V型刀下的圆型冲孔刀 在此处设置是为了实现安装两个圆型冲孔刀
        nClr = 0xFFFF80;
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_VPUNCH,nClr,2,0,2);

        nClr = 0xFFFF80;
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_VPUNCH,nClr,3,0,2);


        nClr = 0xFFFF80;
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_VPUNCH,nClr,5,0,2);

    this->AddCutTool(pCutTool);

    //FPUNCH
    pCutTool = new SDCutTool(CUTTINGTOOL_SPUNCH);

        nClr = 0xFFFF80;
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_SPUNCH,nClr,3,0,0);

        nClr = 0xFFFF80;
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_SPUNCH,nClr,5,0,0);

    this->AddCutTool(pCutTool);

    //RPUNCH
    pCutTool = new SDCutTool(CUTTINGTOOL_RPUNCH);

        nClr = 0xFFC080;
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_RPUNCH,nClr,2,0,0);

        nClr = 0xFFC080;
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_RPUNCH,nClr,3,0,0);

        nClr = 0xFFC080;
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_RPUNCH,nClr,5,0,0);

    this->AddCutTool(pCutTool);



    //VCUT
    pCutTool = new SDCutTool(CUTTINGTOOL_VCUT);
        nClr = 0x00FFFF;
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_VCUT,nClr,5,30,0);

        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_VCUT,nClr,5,45,0);

    this->AddCutTool(pCutTool);

    //MILL
    pCutTool = new SDCutTool(CUTTINGTOOL_MILL);

        nClr = 0x00FF00;
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_MILL,nClr,3,0,0);
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_MILL,nClr,4,0,0);
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_MILL,nClr,5,0,0);
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_MILL,nClr,6,0,0);

    this->AddCutTool(pCutTool);

    //PLOTTING
    pCutTool = new SDCutTool(CUTTINGTOOL_PLOT);
        nClr = 0xFFC080;
        pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_PLOT,nClr,5,0,0);
    this->AddCutTool(pCutTool);

    //增加一个空的刀具
    if (GetCutToolById(CUTTINGTOOL_NULL) == nullptr)
    {
        pCutTool = new SDCutTool(CUTTINGTOOL_NULL);
            nClr = 0xFFC080;
            pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_NULL,nClr,5,0,0);
        this->AddCutTool(pCutTool);
    }
}
int SDCutToolLib::GetPrivateProfileString(QString strSect,QString strKey,QString strDefault,QString *szBuf,QString strConfigPath)
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
//checked OK by Stone
bool SDCutToolLib::ReadCutToolLib(QString sLocalDir)
{
    //释放内存
    FreeCutTools();

    //方案2 ini格式
    QString strConfigPath = sLocalDir;
    strConfigPath += ("Settings\\KnifeToolLib.ini");//KnifeToolLib.ini

    QString strSect = ("");
    QString strKey = ("");
    QString strText = ("");
    QString strDefault = ("");
    QString sInfo = "";

    QString *szBuf = new QString;

    //刀具大类信息
    QList<QString> vCutToolIdArray;
    strSect = ("CuttingToolId");
    strKey = ("CuttingToolIds");

    int nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        vCutToolIdArray = sInfo.split(',');
    }
    else
    {
        //return false;
    }

    QString strTemp = ("");
    //读取刀具大类
    for(int i = 0; i < vCutToolIdArray.size(); i++)
    {
        SDCutTool* pCutTool = new SDCutTool();

        short nCutToolId = vCutToolIdArray[i].toShort();

        strSect = ("CuttingTool");
        strTemp = QString::number(nCutToolId);
        strSect += strTemp;

        //刀具Id
        strKey = ("CuttingToolId");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            short nValue = sInfo.toShort();
            pCutTool->SetCutToolId(nValue);
        }

        //刀具名
        strKey = ("CuttingToolName");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            pCutTool->SetCutToolName(sInfo);
        }

        //子刀具最大Id
        strKey = ("MaxKnifeId");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            short nValue = sInfo.toShort();
            pCutTool->SetMaxKnifeId(nValue);
        }

        //子刀具最大Id
        strKey = ("MaxKnifeId1");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            short nValue = sInfo.toShort();
            pCutTool->SetMaxKnifeId(nValue,1);
        }


        //子刀具最大Id
        strKey = ("MaxKnifeId2");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            short nValue = sInfo.toShort();
            pCutTool->SetMaxKnifeId(nValue,2);
        }

        //加载刀具名关键字
        pCutTool->LoadCutToolKey();

        //刀具Guid队列信息
        QList<QString> vKnifeSpArray;
        strKey = ("KnifeGuids");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            vKnifeSpArray = sInfo.split(',');
        }

        QString sConfigPath = strConfigPath;
        for(int j = 0; j < vKnifeSpArray.size(); j++)
        {
            SDKnife* pKnife = new SDKnife();

            pKnife->SetCutToolKey(pCutTool->GetCutToolKey());
            pKnife->SetCutToolName(pCutTool->GetCutToolName());
            pKnife->SetGuid(vKnifeSpArray.at(j).toInt());

            QString sKnifeSect = "Knife";
            sKnifeSect += pKnife->GetGuidString();


            pKnife->ReadEx(sConfigPath,sKnifeSect);//待修改确认

            pCutTool->AddKnifePro(pKnife);
        }

        m_stvCutTools.push_back(pCutTool);
    }

    if (m_stvCutTools.empty())
    {
        InitDefaultCutToolLib();
    }

    //增加一个空的刀具
    if (GetCutToolById(CUTTINGTOOL_NULL) == nullptr)
    {
        SDCutTool* pNullCutTool = new SDCutTool(CUTTINGTOOL_NULL);

        int nClr = 255;
        SDKnife* pNullKnife = pNullCutTool->NewKnife(TOOLAPRON_CMODE_NULL,nClr,5,30,0);
        this->AddCutTool(pNullCutTool);
    }

    //test 新增一个刀具大类 ->
    //if (GetCutToolById(CUTTINGTOOL_VCUT) == NULL)
    //{
    //	SDCutTool* pCutTool = new SDCutTool(CUTTINGTOOL_VCUT);
    //		int nClr = RGB(255,255,255);
    //		SDKnife* pKnife = pCutTool->NewKnife(TOOLAPRON_CMODE_VCUT,nClr,5,30,0);
    //	this->AddCutTool(pCutTool);
    //}

    return true;
}
void SDCutToolLib::WritePrivateProfileString(QString strSect,QString strKey,QString strText,QString strConfigPath)
{

}
bool SDCutToolLib::SaveCutToolLib(QString sLocalDir)
{
    //方案2 ini格式
    QString strConfigPath = sLocalDir;
    strConfigPath += ("\\ToolSet\\KnifeToolLib.ini");//KnifeToolLib.ini


    QString strSect = ("");
    QString strKey = ("");
    QString strText = ("");

    strSect = ("CuttingToolId");

    //配置刀具大类信息
    int nCutToolCount = m_stvCutTools.size();
    QString strTemp = ("");
    strText = ("");
    int i = 0;
    for(i = 0; i < nCutToolCount; i++)
    {
        SDCutTool* pCutTool = m_stvCutTools.at(i);

        //strTemp.Format(("%hd"),pCutTool->GetCutToolId());
        strTemp = QString::number(pCutTool->GetCutToolId());
        strText += strTemp;
        if (i < (nCutToolCount-1))
        {
            strText += (",");
        }
    }
    strKey = ("CuttingToolIds");
    WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

    //保存刀具大类
    for(i = 0; i < nCutToolCount; i++)
    {
        SDCutTool* pCutTool = m_stvCutTools.at(i);

        strSect = ("CuttingTool");
        //strTemp.Format(("%hd"),pCutTool->GetCutToolId());
        strTemp = QString::number(pCutTool->GetCutToolId());
        strSect += strTemp;

        //刀具Id
        strKey = ("CuttingToolId");
        //strText.Format(("%hd"),pCutTool->GetCutToolId());
        strText = QString::number(pCutTool->GetCutToolId());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //刀具名
        strKey = ("CuttingToolName");
        //strText = SDConvert::stringToCString(pCutTool->GetCutToolName());
        strText = pCutTool->GetCutToolName();
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //子刀具最大Id【第一梯段】
        strKey = ("MaxKnifeId");
        //strText.Format(_T("%hd"),pCutTool->GetMaxKnifeId(0));
        strText = QString::number(pCutTool->GetMaxKnifeId(0));
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //子刀具最大Id【第二梯段】
        strKey = ("MaxKnifeId1");
        //strText.Format(("%hd"),pCutTool->GetMaxKnifeId(1));
        strText = QString::number(pCutTool->GetMaxKnifeId(1));
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //子刀具最大Id【第三梯段】
        strKey = ("MaxKnifeId2");
        //strText.Format(("%hd"),pCutTool->GetMaxKnifeId(2));
        strText = QString::number(pCutTool->GetMaxKnifeId(2));
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //子刀具SP值队列
        QList<SDKnife*> *pSubKnifes = pCutTool->GetSubKnifes();
        int nKnifeCount = pSubKnifes->size();
        int j = 0;
        strText = ("");
        for(j = 0; j < nKnifeCount; j++)
        {
            SDKnife* pKnife = pSubKnifes->at(j);

            //strTemp.Format(("%d"),pKnife->GetGuid());
            strTemp = QString::number(pKnife->GetGuid());
            strText += strTemp;
            if (j < (nKnifeCount-1))
            {
                strText += (",");
            }
        }
        strKey = ("KnifeGuids");
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //保存子刀具
        QString sConfigPath = (strConfigPath);
        for(j = 0; j < nKnifeCount; j++)
        {
            SDKnife* pKnife = pSubKnifes->at(j);

            QString sSect = "Knife";
            sSect += pKnife->GetGuidString();


            pKnife->SaveEx(sConfigPath,sSect);
        }
    }

    return true;
}
bool SDCutToolLib::ImportSysCutToolLib(QString sLocalDir,bool bConver)
{
    if (bConver)
    {
        return ReadCutToolLib(sLocalDir);
    }

    //1 备份
    QList<SDCutTool*> vSrcCutTools;
    //vSrcCutTools.assign(m_stvCutTools.begin(),m_stvCutTools.end());
    vSrcCutTools = m_stvCutTools;
    m_stvCutTools.clear();

    //2 读入新数据
    if (!ReadCutToolLib(sLocalDir))
    {
        FreeCutTools();
        //m_stvCutTools.assign(vSrcCutTools.begin(),vSrcCutTools.end());
        m_stvCutTools = vSrcCutTools;
    }

    for(int i = 0; i < vSrcCutTools.size(); i++)
    {
        SDCutTool* pSrcCutTool = vSrcCutTools.at(i);

        SDCutTool* pDesCutTool = this->GetCutToolById(pSrcCutTool->GetCutToolId());
        if (pDesCutTool != nullptr)
        {
            QList<SDKnife*>* pSrcKnifes = pSrcCutTool->GetSubKnifes();
            for(int j = 0; j < pSrcKnifes->size(); j++)
            {
                SDKnife* pSrcKnife = pSrcKnifes->at(j);

                SDKnife* pDesKnife = pDesCutTool->GetKnifeById(pSrcKnife->GetKnifeId());
                if (pDesKnife != nullptr)
                {
                    pDesKnife->Copy(pSrcKnife);
                }
            }
        }

        delete pSrcCutTool;
    }
    vSrcCutTools.clear();

    return true;
}
