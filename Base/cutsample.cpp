#include "cutsample.h"

CutSample::CutSample(QObject *parent) : QObject(parent)
{
    m_nSampleId=0;
    m_rctAirSquare.setTopLeft(QPointF(0,0));
    m_rctAirSquare.setBottomRight(QPointF(0,0));
}
int CutSample::GetSampleId(void)
{
    return m_nSampleId;
}
void CutSample::SetSampleId(int _id)
{
    m_nSampleId = _id;
}
QList<CutLine *>* CutSample::GetNormalLineList()
{
    return m_lNormalLine;
}
CutLine* CutSample::GetNormalLine(int _index)
{
    return this->m_lNormalLine->at(_index);
}
QRectF CutSample::GetInhaleSqare()
{
    return this->m_rctAirSquare;
}
void CutSample::SetInhaleSqare(QRectF _sqare)
{
    this->m_rctAirSquare = _sqare;
}
CutLine* CutSample::GetPunchLine()
{
    return m_lPunchLine;
}

CutLine*  CutSample::GetDrillLine()
{
    return m_lDrillLine;
}
