#include "cutline.h"
CutLine::CutLine(QObject *parent) : QObject(parent)
{
    m_qpgLine.clear();
    m_qldAngle.clear();
    m_dDepth = 0;
    m_nKnifeGuid = 0;
    m_qstrLable = "NoLine";
    m_qpOffset = QPointF(0,0);
}

void    CutLine::AddCutPoint(QPointF _point,double _angle)
{
    m_qpgLine.append(_point);
    m_qldAngle.append(_angle);
}

void    CutLine::SetDepth(double _depth)
{
    this->m_dDepth = _depth;
}

double  CutLine::GetDepth(void)
{
    return this->m_dDepth;
}

void    CutLine::SetKnifeGuid(int _guid)
{
    this->m_nKnifeGuid = _guid;
}

int     CutLine::GetKnifeGuid(void)
{
    return this->m_nKnifeGuid;
}

void    CutLine::SetLineLable(QString _lineLable)
{
    this->m_qstrLable = _lineLable;
}

QString CutLine::GetLineLable(void)
{
    return this->m_qstrLable;
}
