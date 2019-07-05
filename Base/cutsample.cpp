#include "cutsample.h"

CutSample::CutSample(QObject *parent) : QObject(parent)
{
    m_nSampleId=0;
    m_rctAirSquare.setTopLeft(QPointF(0,0));
    m_rctAirSquare.setBottomRight(QPointF(0,0));
//    m_lNormalLine->clear();
    m_lPunchLine;
    m_lDrillLine;

}
int CutSample::GetSampleId(void)
{
    return m_nSampleId;
}

void CutSample::SetSampleId(int _id)
{
    m_nSampleId = _id;
}

QList<CutLine *>* CutSample::GetNormalLine()
{
//    return m_lNormalLine;
}
