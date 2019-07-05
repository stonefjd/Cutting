#include "cutline.h"
CutLine::CutLine(QObject *parent) : QObject(parent)
{
    m_pgLine.clear();
    m_ldAngle.clear();
    m_dDepth = 0;
    m_nKnifeGuid = 0;
}

void    CutLine::AddPoint(QPointF _point,double _angle)
{
    m_pgLine.append(_point);
    m_ldAngle.append(_angle);
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
    this->m_strLable = _lineLable;
}

QString CutLine::GetLineLable(void)
{
    return this->m_strLable;
}
