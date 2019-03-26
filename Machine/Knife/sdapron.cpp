#include "sdapron.h"

SDApron::SDApron(QObject *parent) : QObject(parent)
{
    m_nMachineIndex = 0;
    m_nApronIndex = -1;
    m_nApronCMode = -1;
    m_nKnifeGuid = -1;
    m_dbXOffset = 0;
    m_dbYOffset = 0;
}
SDApron::~SDApron(void)
{
    Free();
}
SDApron& SDApron::operator = (const SDApron& other)
{
    if (this == &other)
    {
        return *this;
    }

    m_nApronIndex = other.m_nApronIndex;
    m_nApronCMode = other.m_nApronCMode;
    m_nKnifeGuid = other.m_nKnifeGuid;
    m_nMachineIndex = other.m_nMachineIndex;
    m_dbXOffset = other.m_dbXOffset;
    m_dbYOffset = other.m_dbYOffset;
    return *this;
}
SDApron* SDApron::Copied()
{
    SDApron* pApron = new SDApron();
    *pApron = *this;

    return pApron;
}
bool SDApron::Copy(SDApron* pOther)
{
    if (pOther == nullptr)
        return false;

    *this = *pOther;

    return true;
}


bool SDApron::Read(QDataStream *pFile,int nVer)
{
    Free();
//	MS_Readshort_Binary(pFile,m_nApronIndex);           //刀座序号
//	MS_Readshort_Binary(pFile,m_nApronCMode);		    //刀座控制方式

//	MS_Readint_Binary(pFile,m_nKnifeGuid);				//刀座上的刀具Guid

    return true;
}
bool SDApron::Save(QDataStream *pFile,int nVer)
{
//	MS_Writeshort_Binary(pFile,m_nApronIndex);            //刀座序号
//	MS_Writeshort_Binary(pFile,m_nApronCMode);			  //刀座控制方式

//	MS_Writeint_Binary(pFile,m_nKnifeGuid);				  //刀座上的刀具Guid


    return true;
}


void SDApron::Free()
{
    m_nMachineIndex = 0;
    m_nApronIndex = -1;
    m_nApronCMode = -1;
    m_nKnifeGuid = -1;
}

void  SDApron::SetApronIndex(short nApronIndex)
{
    m_nApronIndex = nApronIndex;
}

short SDApron::GetApronIndex()
{
    return m_nApronIndex;
}

void  SDApron::SetApronCMode(short nCMode)
{
    m_nApronCMode = nCMode;
}
short SDApron::GetApronCMode()
{
    return m_nApronCMode;
}


void  SDApron::SetMachineIndex(short nMachinexIndex)
{
    m_nMachineIndex = nMachinexIndex;
}
short SDApron::GetMachineIndex()
{
    return m_nMachineIndex;
}

short SDApron::GetApronGuid()
{
    return static_cast<short>(m_nApronIndex | (m_nMachineIndex<<8));
}

void  SDApron::SetKnifeGuid(int nGuid)
{
    m_nKnifeGuid = nGuid;
}
int   SDApron::GetKnifeGuid()
{
    return m_nKnifeGuid;
}
void   SDApron::SetXOffset(double dbValue)
{
    m_dbXOffset = dbValue;
}
double SDApron::GetXOffset()
{
    return m_dbXOffset;
}


void   SDApron::SetYOffset(double dbValue)
{
    m_dbYOffset = dbValue;
}
double SDApron::GetYOffset()
{
    return m_dbYOffset;
}
