#include "sdmachinehead.h"

SDMachineHead::SDMachineHead(QObject *parent) : QObject(parent)
{
    Free();
}

SDMachineHead::~SDMachineHead(void)
{
    Free();
    FreeAprons();
}
SDMachineHead& SDMachineHead::operator = (const SDMachineHead& other)
{
    if (this == &other)
    {
        return *this;
    }
    m_nMachineBeamIndex = other.m_nMachineBeamIndex;		//横梁序号
    m_nMachineHeadIndex = other.m_nMachineHeadIndex;		//机头序号
    m_dbHeadXOrigin = other.m_dbHeadXOrigin;				//机头原点X
    m_dbHeadYOrigin = other.m_dbHeadYOrigin;				//机头原点Y

    m_dbHeadXPos = other.m_dbHeadXPos;						//机头位置X
    m_dbHeadYPos = other.m_dbHeadYPos;						//机头位置Y

    m_dbActualLen = other.m_dbActualLen;					//实测长度
    m_dbExpectLen = other.m_dbExpectLen;					//预测长度
    m_dbActualWidth = other.m_dbActualWidth;				//实测宽度
    m_dbExpectWidth = other.m_dbExpectWidth;				//预测宽度
    m_dbXScale = other.m_dbXScale;
    m_dbYScale = other.m_dbYScale;

    m_dbPlotActualLen = other.m_dbPlotActualLen;			//实测长度
    m_dbPlotExpectLen = other.m_dbPlotExpectLen;			//预测长度
    m_dbPlotActualWidth = other.m_dbPlotActualWidth;		//实测宽度
    m_dbPlotExpectWidth = other.m_dbPlotExpectWidth;		//预测宽度
    m_dbPlotXScale = other.m_dbPlotXScale;
    m_dbPlotYScale = other.m_dbPlotYScale;

    m_dbCuttingLen = other.m_dbCuttingLen;				//切割范围(长度)
    m_dbCuttingHeight = other.m_dbCuttingHeight;		//切割范围(宽度)

    m_dbPenOffsetX = other.m_dbPenOffsetX;				//笔偏移X
    m_dbPenOffsetY = other.m_dbPenOffsetY;				//笔偏移Y

    m_dbGlowOffsetX = other.m_dbGlowOffsetX;			//红光定位 X偏移
    m_dbGlowOffsetY = other.m_dbGlowOffsetY;			//红光定位 Y偏移

    m_dbCameraOffsetX = other.m_dbCameraOffsetX;		//摄像头 X偏移
    m_dbCameraOffsetY = other.m_dbCameraOffsetY;		//摄像头 Y偏移
    m_dbCameraHeight = other.m_dbCameraHeight;			//摄像头 高度

    m_nCuttingMode = other.m_nCuttingMode;				//切割模式
    m_nDecoupleMode = other.m_nDecoupleMode;			//减震模式

    m_dbFeedLen = other.m_dbFeedLen;					//送料长度
    m_dbFeedSpeed = other.m_dbFeedSpeed;				//送料速度(m/s)
    m_dbSwagingTime = other.m_dbSwagingTime;			//压料时间(s)
    m_dbSwagingTime1 = other.m_dbSwagingTime1;			//压料时间(s)
    m_dbSwagingTime2 = other.m_dbSwagingTime2;
    m_dbSwagingTime3 = other.m_dbSwagingTime3;

    m_dbIdleMoveSpeed = other.m_dbIdleMoveSpeed;		//空走速度 (m/s)
    m_dbIdleMoveAcceleration = other.m_dbIdleMoveAcceleration;//空走加速度(G)


    m_dbReducerEdge = other.m_dbReducerEdge;			//减速边界

    m_dbInhaleDelayTime = other.m_dbInhaleDelayTime;	//吸气延迟时间(ms)
    m_nLastCutLineId = other.m_nLastCutLineId;			//最后一条切割的直线段id
    m_nLastPLotLineId = other.m_nLastPLotLineId;		//最后一条打印的直线段id
    m_nLastPlotFlag=other.m_nLastPlotFlag;				//打印标记

    m_dbScanLen=other.m_dbScanLen;						//扫描长度
    m_dbScanSpeed=other.m_dbScanSpeed;					//扫描速度(m/s)
    m_dbScanAcceleration=other.m_dbScanAcceleration;	//扫描加速度(G)

    m_bEnablePlot = other.m_bEnablePlot;
    m_bValid = other.m_bValid;

    return *this;
}
SDMachineHead* SDMachineHead::Copied()
{
    SDMachineHead* pMachineHead = new SDMachineHead();
    *pMachineHead = *this;

    return pMachineHead;
}
bool SDMachineHead::Copy(SDMachineHead* pOther)
{
    if (pOther == nullptr)
        return false;

    *this = *pOther;

    return true;
}

void SDMachineHead::InitApron()
{
    FreeAprons();

    AddApronIndex(0,TOOLAPRON_CMODE_ROLL);
    AddApronIndex(1,TOOLAPRON_CMODE_RPUNCH);
    AddApronIndex(2,TOOLAPRON_CMODE_VPUNCH);
    AddApronIndex(3,TOOLAPRON_CMODE_PLOT);

}
bool SDMachineHead::Read(QDataStream *pFile,int nVer)
{


    return true;
}
bool SDMachineHead::Save(QDataStream *pFile,int nVer)
{


    return true;
}


void SDMachineHead::Free()
{
    m_nMachineBeamIndex = 0;
    m_nMachineHeadIndex = 0;		//机头序号
    m_dbHeadXOrigin = 0;			//机头原点X
    m_dbHeadYOrigin = 0;			//机头原点Y

    m_dbHeadXPos = 0;				//机头位置X
    m_dbHeadYPos = 0;				//机头位置Y

    m_dbActualLen = 1000;			//实测长度
    m_dbExpectLen = 1000;			//预测长度
    m_dbActualWidth = 1000;			//实测宽度
    m_dbExpectWidth = 1000;			//预测宽度
    m_dbXScale = 1;
    m_dbYScale = 1;

    m_dbPlotActualLen = 1000;		//实测长度
    m_dbPlotExpectLen = 1000;		//预测长度
    m_dbPlotActualWidth = 1000;		//实测宽度
    m_dbPlotExpectWidth = 1000;		//预测宽度
    m_dbPlotXScale = 1;
    m_dbPlotYScale = 1;

    m_dbCuttingLen = 0;				//切割范围(长度)
    m_dbCuttingHeight = 0;			//切割范围(宽度)

    m_dbPenOffsetX = 0;				//笔偏移X
    m_dbPenOffsetY = 0;				//笔偏移Y

    m_dbGlowOffsetX = 0;			//红光定位 X偏移
    m_dbGlowOffsetY = 0;			//红光定位 Y偏移

    m_dbCameraOffsetX = 0;			//摄像头 X偏移
    m_dbCameraOffsetY = 0;			//摄像头 Y偏移
    m_dbCameraHeight = 0;			//摄像头 高度

    m_nCuttingMode = 0;				//切割模式
    m_nDecoupleMode = 0;			//减震模式

    m_dbFeedLen = 0;				//送料长度
    m_dbFeedSpeed = 50;				//送料速度(m/s)
    m_dbSwagingTime = 1000;			//压料时间(s)
    m_dbSwagingTime1 = 1000;		//压料时间(s)
    m_dbSwagingTime2 = 0;
    m_dbSwagingTime3 = 0;
    m_dbFeedJ = 1;					//送料速度(m/s)

    m_dbIdleMoveSpeed = 200;		//空走速度 (m/s)
    m_dbIdleMoveAcceleration = 12;	//空走加速度(G)

    m_dbReducerEdge = 0;			//减速边界

    m_dbInhaleDelayTime = 2000;		//吸气延迟时间(ms)
    m_nLastCutLineId = -1;			//最后一条切割的直线段id
    m_nLastPLotLineId = -1;			//最后一条打印的直线段id
    m_nLastPlotFlag=0;				//打印标记

    m_dbScanLen=1000;				//扫描长度
    m_dbScanSpeed=15;				//扫描速度(m/s)
    m_dbScanAcceleration=8;			//扫描加速度(G)

    m_bEnablePlot = true;
    m_bValid = true;

    m_dbHeadFactXOffset = 0;
    m_dbHeadFactYOffset = 0;
}

QList<SDApron*>* SDMachineHead::GetAprons()
{
    return &m_vstAprons;
}

int  SDMachineHead::GetApronsCount()
{
    return m_vstAprons.size();
}
void SDMachineHead::FreeAprons()
{
    for(int i = 0; i < m_vstAprons.size(); i++)
    {
        delete m_vstAprons.at(i);
    }
    m_vstAprons.clear();
}

void SDMachineHead::AddApron(SDApron* pApron)
{
    if (pApron == nullptr)
        return;

    pApron->SetMachineIndex(m_nMachineHeadIndex);
    m_vstAprons.push_back(pApron);
}

SDApron* SDMachineHead::AddApronIndex(int nApronIndex)
{
    SDApron* pApron = GetApronByApronIndex(nApronIndex);
    if (pApron == nullptr)
    {
        pApron = new SDApron();
        pApron->SetApronIndex(static_cast<short>(nApronIndex));
        pApron->SetMachineIndex(m_nMachineHeadIndex);

        m_vstAprons.push_back(pApron);
        return pApron;
    }
    else
    {
        return pApron;
    }
}

SDApron* SDMachineHead::AddApronIndex(int nApronIndex,short nApronCMode)
{
    SDApron* pApron = GetApronByApronIndex(nApronIndex);

    if (pApron == nullptr)
    {
        pApron = new SDApron();
        pApron->SetApronIndex(static_cast<short>(nApronIndex));
        pApron->SetMachineIndex(m_nMachineHeadIndex);
        pApron->SetApronCMode(nApronCMode);
        m_vstAprons.push_back(pApron);
        return pApron;
    }
    else
    {
        pApron->SetApronCMode(nApronCMode);
        return pApron;
    }
}

SDApron*	SDMachineHead::GetApronByApronIndex(int nApronIndex)
{
    for(int i = 0; i < m_vstAprons.size(); i++)
    {
        SDApron* pApron = m_vstAprons.at(i);
        int nApron = pApron->GetApronIndex();
        if (nApron == nApronIndex)
            return pApron;
    }
    return nullptr;
}

int	SDMachineHead::FindApron(int nApronIndex)
{
    for(int i = 0; i < m_vstAprons.size(); i++)
    {
        SDApron* pApron = m_vstAprons.at(i);
        int nApron = pApron->GetApronIndex();
        if (nApron == nApronIndex)
            return i;
    }
    return -1;
}

void SDMachineHead::UpdateOnlineAprons(QList<SDApron*> &vAprons)
{
    int nOldApronSize = m_vstAprons.size();
    int nNewApronSize = vAprons.size();
    for(int i = 0; i < nOldApronSize; i++)
    {
        if (i >= nNewApronSize)
            break;

        SDApron* pOldApron = m_vstAprons.at(i);
        SDApron* pNewApron = vAprons.at(i);

        //控制方式相同，就把原有的刀具信息保存到新的刀座上
        if (pOldApron->GetApronCMode() == pNewApron->GetApronCMode())
        {
            pNewApron->SetKnifeGuid(pOldApron->GetKnifeGuid());
        }
    }

    //释放旧的刀座结构
    FreeAprons();

    //添加新的刀座结构
    for(int j = 0; j < nNewApronSize; j++)
    {
        SDApron* pNewApron = vAprons.at(j);
        this->AddApron(pNewApron);
    }

}
void SDMachineHead::CheckAprons()
{
    if (m_vstAprons.empty())
    {
        InitApron();
    }
}
