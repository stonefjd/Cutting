#include "sdmachine.h"

SDMachine::SDMachine(QObject *parent) : QObject(parent)
{
    m_nMachineType = 0;
    m_nSubMachineType = 0;

    m_dbMachineLen = 2500;
    m_dbMachineHeight = 1800;
}
SDMachine::~SDMachine(void)
{
    Free();
}
SDMachine& SDMachine::operator = (const SDMachine& other)
{
    if (this == &other)
    {
        return *this;
    }


    return *this;
}
SDMachine* SDMachine::Copied()
{
    SDMachine* pMachineInfo = new SDMachine();
    *pMachineInfo = *this;

    return pMachineInfo;
}
bool SDMachine::Copy(SDMachine* pOther)
{
    if (pOther == nullptr)
        return false;

    *this = *pOther;

    return true;
}

void SDMachine::InitMachineHead()
{
    FreeMachineHeads();

    SDMachineHead* pHead = new SDMachineHead();
    pHead->InitApron();
    m_stMachineHeads.push_back(pHead);
}
bool SDMachine::Read(QDataStream *pFile)
{
    Free();

//    int nVersion = 20190302;

//    MS_Readint_Binary(pFile,nVersion);
//    if (nVersion < 20190302 || nVersion > 20300000)
//    {
//        return false;
//    }
//    MS_Readshort_Binary(pFile,m_nMachineType);				//机器类型
//    MS_Readshort_Binary(pFile,m_nSubMachineType);			//机器类型子类型
//    MS_Readdouble_Binary(pFile,m_dbMachineLen);				//机器长度
//    MS_Readdouble_Binary(pFile,m_dbMachineHeight);			//机器宽度

//    int nHeadCount = 0;
//    MS_Readint_Binary(pFile,nHeadCount);
//    if (nHeadCount < -1 || nHeadCount > 100)
//        return false;

//    for(int i = 0; i < nHeadCount; i++)
//    {
//        SDMachineHead* pHead = new SDMachineHead();
//        if (!pHead->Read(pFile,nVersion))
//        {
//            delete pHead;
//            return false;
//        }

//        m_stMachineHeads.push_back(pHead);
//    }

//    //保证至少有一个机头结构
//    if (nHeadCount <= 0)
//    {
//        SDMachineHead* pHead = new SDMachineHead();
//        m_stMachineHeads.push_back(pHead);
//    }

    return true;
}
bool SDMachine::Save(QDataStream *pFile)
{
//    int nVersion = 20190302;

//    MS_Writeint_Binary(pFile,nVersion);

//    MS_Writeshort_Binary(pFile,m_nMachineType);				//机器类型
//    MS_Writeshort_Binary(pFile,m_nSubMachineType);			//机器类型子类型
//    MS_Writedouble_Binary(pFile,m_dbMachineLen);			//机器长度
//    MS_Writedouble_Binary(pFile,m_dbMachineHeight);			//机器宽度

//    int nHeadCount = (int)m_stMachineHeads.size();
//    if (nHeadCount < 0 || nHeadCount > 100)
//    {
//        return false;
//    }

//    MS_Writeint_Binary(pFile,nHeadCount);
//    for(int i = 0; i < nHeadCount; i++)
//    {
//        SDMachineHead* pHead = m_stMachineHeads.at(i);
//        if (!pHead->Save(pFile,nVersion))
//        {
//            return false;
//        }
//    }

    return true;
}

bool SDMachine::ReadApron(QDataStream *pFile)
{
    //int nHeadCount = (int)m_stMachineHeads.size();
    return true;
}
bool SDMachine::SaveApron(QDataStream *pFile)
{
    return true;
}

void SDMachine::Free()
{
    FreeMachineHeads();
}

void SDMachine::GetAllAprons(QList<SDApron*>& vAprons)
{
    for(int i = 0; i < m_stMachineHeads.size(); i++)
    {
        SDMachineHead* pHead = m_stMachineHeads.at(i);

        QList<SDApron*>* pAprons = pHead->GetAprons();
        for(int j = 0; j < pAprons->size(); j++)
        {
            vAprons.push_back(pAprons->at(j));
        }
    }
}


SDApron* SDMachine::GetApron(short nMachineIndex, short nApronIndex)
{
    if (nMachineIndex >= 0 && nMachineIndex < m_stMachineHeads.size())
    {
        SDMachineHead* pHead = m_stMachineHeads.at(nMachineIndex);
        QList<SDApron*>* pAprons = pHead->GetAprons();
        if (nApronIndex >= 0 && nApronIndex < pAprons->size())
        {
            return pAprons->at(nApronIndex);
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        return nullptr;
    }
}

SDApron* SDMachine::GetApron(short nToolApron)
{

    short nSrcMachineIndex = ((nToolApron>>8)&0xff);
    short nSrcApronIndex = nToolApron&0xff;

    return GetApron(nSrcMachineIndex,nSrcApronIndex);
}

void SDMachine::FreeMachineHeads()
{
    for(int i = 0; i < m_stMachineHeads.size(); i++)
    {
        delete m_stMachineHeads.at(i);
    }
    m_stMachineHeads.clear();
}

void SDMachine::ModifyMachineHead(int nHeadCount)
{
    int nOldHeadCount = GetMachineHeadCount();
    if (nOldHeadCount == nHeadCount)
        return;

    if (nOldHeadCount < nHeadCount)
    {
        for(int i = nOldHeadCount; i < nHeadCount; i++)
        {
            NewMachineHead();
        }
    }
    else if (nOldHeadCount > nHeadCount)
    {
        for(int i = nHeadCount; i < nOldHeadCount; i++)
        {
            delete m_stMachineHeads.at(i);
            m_stMachineHeads.erase(m_stMachineHeads.begin()+i);
        }
    }
}

void SDMachine::AddMachineHead(SDMachineHead* pHead)
{
    if (pHead == nullptr)
        return;

    int nMachineIndex = m_stMachineHeads.size();
    pHead->SetMachineHeadIndex(static_cast<short>(nMachineIndex));
    m_stMachineHeads.push_back(pHead);
}

SDMachineHead*  SDMachine::NewMachineHead()
{
    SDMachineHead* pHead = new SDMachineHead();
    AddMachineHead(pHead);

    return pHead;
}
QList<SDMachineHead*>* SDMachine::GetMachineHeads()
{
    return &m_stMachineHeads;
}

int SDMachine::GetMachineHeadCount()
{
    return m_stMachineHeads.size();
}

SDMachineHead*	SDMachine::GetFirstHead()
{
    if (!m_stMachineHeads.empty())
    {
        return m_stMachineHeads.front();
    }

    return nullptr;
}
SDMachineHead* SDMachine::GetSecondHead()
{
    if (m_stMachineHeads.size() > 1)
    {
        return m_stMachineHeads.at(1);
    }
    else
    {
        return nullptr;
    }
}

SDMachineHead* SDMachine::GetMachineHeadByIndex(int nIndex)
{
    if (nIndex >= 0 && nIndex < m_stMachineHeads.size())
    {
        return m_stMachineHeads.at(nIndex);
    }

    return nullptr;
}
int		SDMachine::GetHeadIndexOnBeam(SDMachineHead* pHead)
{
    if (pHead == nullptr)
        return -1;

    int nIndex = 0;
    for(int i = 0; i < m_stMachineHeads.size(); i++)
    {
        SDMachineHead* pSrcHead = m_stMachineHeads.at(i);
        if (pSrcHead->GetMachineBeamIndex() == pHead->GetMachineBeamIndex())
        {
            if (pSrcHead == pHead)
            {
                return nIndex;
            }
            nIndex++;
        }
    }
    return nIndex;
}
QRectF  SDMachine::GetMachineRect()
{
    double lfCuttingTableLen = m_dbMachineLen;//2000*FACTOR_MM;
    double lfCuttingTableHeight = m_dbMachineHeight;//1800*FACTOR_MM;
    if (lfCuttingTableLen <= 0)
        lfCuttingTableLen = 2500;
    if (lfCuttingTableHeight <= 0)
        lfCuttingTableHeight = 1600;

    QRectF rectBed;
    rectBed.setRect(0,lfCuttingTableHeight,lfCuttingTableLen,0);

    return rectBed;
}
