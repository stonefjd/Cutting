#include "cutfile_data.h"

CutFile_Data::CutFile_Data(QObject *parent) : QObject(parent)
{

}
QList<CutFile*>* CutFile_Data::GetFileList()
{
    return this->qlcFileList;
}

void    CutFile_Data::SetPosOrg(QPointF *_pointF)
{
    this->posOrg = _pointF;
}
QPointF* CutFile_Data::GetPosOrg()
{
    return this->posOrg;
}

void    CutFile_Data::SetPosToPulseScale(QPointF *_pointF)
{
    this->posToPulseScale = _pointF;
}

QPointF* CutFile_Data::GetPosToPulseScale()
{
    return this->posToPulseScale;
}

void    CutFile_Data::SetPosLmt(QPointF *_pointF)
{
    this->posLimit = _pointF;
}

QPointF* CutFile_Data::GetPosLmt()
{
    return this->posLimit;
}

void    CutFile_Data::SetPosMax(QPointF *_pointF)
{
    this->posMax = _pointF;
}

QPointF* CutFile_Data::GetPosMax()
{
    return this->posMax;
}

void    CutFile_Data::SetRealToCutScale(QPointF *_pointF)
{
    this->realToCutScale = _pointF;
}

QPointF* CutFile_Data::GetRealToCutScale()
{
    return this->realToCutScale;
}

void    CutFile_Data::SetPosRt(QPointF _pointF)
{
    this->posRt = _pointF;
}

QPointF CutFile_Data::GetPosRt()
{
    return this->posRt;
}

void    CutFile_Data::SetRtAgl(double *_agl)
{
    this->rtAgl = _agl;
}

double *CutFile_Data::GetRtAgl()
{
    return this->rtAgl;
}
