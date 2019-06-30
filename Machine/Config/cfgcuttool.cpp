#include "cfgcuttool.h"

CfgCutTool::CfgCutTool()
{
    m_emCutToolId = CUTTINGTOOL_NULL;
    m_sCutToolKey = "NULL";
    m_sCutToolName = "NUll";
    m_nMaxKnifeId = 1;   //1-20
    m_nMaxKnifeId1 = 21; //21--40
    m_nMaxKnifeId2 = 41; //41-60
}
CfgCutTool::CfgCutTool(short nCutToolId)
{
    m_emCutToolId = static_cast<KnifeId>(nCutToolId);
    LoadCutToolKey();
    m_nMaxKnifeId = 1;
    m_nMaxKnifeId1 = 21;
    m_nMaxKnifeId2 = 41;
}
CfgCutTool::~CfgCutTool(void)
{
    FreeKnifes();
}
CfgCutTool& CfgCutTool::operator = (const CfgCutTool& other)
{
    if (this == &other)
    {
        return *this;
    }

    FreeKnifes();

    m_emCutToolId = other.m_emCutToolId;
    m_sCutToolKey = other.m_sCutToolKey;
    m_sCutToolName = other.m_sCutToolName;
    m_nMaxKnifeId = other.m_nMaxKnifeId;
    m_nMaxKnifeId1 = other.m_nMaxKnifeId1;
    m_nMaxKnifeId2 = other.m_nMaxKnifeId2;
    for(int i = 0; i < other.m_stvKnifes.size(); i++)
    {
        CfgKnife* pSrcKnife = other.m_stvKnifes.at(i);
        CfgKnife* pDesKnife = pSrcKnife->Copied();

        m_stvKnifes.push_back(pDesKnife);
    }

    return *this;
}
void CfgCutTool::FreeKnifes()
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        delete m_stvKnifes.at(i);
    }
    m_stvKnifes.clear();
}
QList<CfgKnife*>*CfgCutTool::GetSubKnifes()
{
    return &m_stvKnifes;
}
bool CfgCutTool::AddKnife(CfgKnife* pKnife,int nIdType)
{
    if (pKnife == nullptr)
        return false;

    pKnife->SetCutToolId(m_emCutToolId);

    int nMaxKnifeId = GetMaxKnifeId(nIdType);
    pKnife->SetKnifeId(static_cast<short>(nMaxKnifeId++));
    SetMaxKnifeId(static_cast<short>(nMaxKnifeId),nIdType);

    pKnife->CreateGuid();

    m_stvKnifes.push_back(pKnife);

    return true;
}

bool CfgCutTool::AddKnifePro(CfgKnife* pKnife)
{
    if (pKnife == nullptr)
        return false;

    m_stvKnifes.push_back(pKnife);

    return true;
}

CfgKnife* CfgCutTool::NewKnife(int nIdType)
{
    CfgKnife* pKnife = new CfgKnife();
    pKnife->SetCutToolId(m_emCutToolId);


    int nMaxKnifeId = GetMaxKnifeId(nIdType);
    pKnife->SetKnifeId(static_cast<short>(nMaxKnifeId++));
    SetMaxKnifeId(static_cast<short>(nMaxKnifeId),nIdType);


    pKnife->CreateGuid();

    m_stvKnifes.push_back(pKnife);

    return pKnife;
}

CfgKnife* CfgCutTool::NewKnife(int nApronCMode,int nClr,double dbDia,double dbAngle,int nIdType)
{
    CfgKnife* pKnife = new CfgKnife();
    pKnife->SetCutToolId(m_emCutToolId);
    pKnife->SetApronCMode(static_cast<ApronCtrlMode>(nApronCMode));

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

CfgKnife* CfgCutTool::GetKnifeById(short nKnifeId)
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        CfgKnife* pKnife = m_stvKnifes.at(i);
        if (pKnife->GetKnifeId() == nKnifeId)
            return pKnife;
    }

    return nullptr;
}

CfgKnife* CfgCutTool::GetKnifeByIndex(int nIndex)
{
    if (nIndex < m_stvKnifes.size() && nIndex >= 0)
    {
        return m_stvKnifes.at(nIndex);
    }

    return nullptr;
}

CfgKnife* CfgCutTool::GetKnifeByKey(QString sKey)
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        CfgKnife* pKnife = m_stvKnifes.at(i);
        if (pKnife->GetKnifeKey() == sKey)
            return pKnife;
    }

    return nullptr;
}

bool     CfgCutTool::DelKnifeById(short nKnifeId)
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        CfgKnife* pKnife = m_stvKnifes.at(i);
        if (pKnife->GetKnifeId() == nKnifeId)
        {
            delete pKnife;
            m_stvKnifes.erase(m_stvKnifes.begin()+i);
            return true;
        }
    }

    return false;
}
bool     CfgCutTool::DelKnife(CfgKnife* pTestKnife)
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        CfgKnife* pKnife = m_stvKnifes.at(i);
        if (pKnife == pTestKnife)
        {
            delete pKnife;
            m_stvKnifes.erase(m_stvKnifes.begin()+i);
            return true;
        }
    }

    return false;
}
bool     CfgCutTool::DelKnifeByKey(QString sKey)
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        CfgKnife* pKnife = m_stvKnifes.at(i);
        if (pKnife->GetKnifeKey() == sKey)
        {
            delete pKnife;
            m_stvKnifes.erase(m_stvKnifes.begin()+i);
            return true;
        }
    }

    return false;
}
void    CfgCutTool::SetMaxKnifeId(short nMaxKnifeId,int nIdType)
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
short  CfgCutTool::GetMaxKnifeId(int nIdType)
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

void   CfgCutTool::SetCutToolId(KnifeId nCutToolId)
{
    m_emCutToolId = nCutToolId;
}
KnifeId  CfgCutTool::GetCutToolId()
{
    return m_emCutToolId;
}

void   CfgCutTool::SetCutToolKey(QString sKey)
{
    m_sCutToolKey = sKey;
}
QString CfgCutTool::GetCutToolKey()
{
    return m_sCutToolKey;
}

void   CfgCutTool::SetCutToolName(QString sName)
{
    m_sCutToolName = sName;
}
QString CfgCutTool::GetCutToolName()
{
    return m_sCutToolName;
}

void   CfgCutTool::LoadCutToolKey()
{
    switch(m_emCutToolId)
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
    }
    m_sCutToolName = m_sCutToolKey;
}
