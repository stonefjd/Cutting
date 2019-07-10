#include "cutfile_data.h"

CutFile_Data::CutFile_Data(QObject *parent) : QObject(parent)
{

}
QList<CutFile*>* CutFile_Data::GetFileList()
{
    return this->qlcFileList;
}

void    CutFile_Data::SetPosOrg(QPointF _pointF)
{
    this->posOrg = _pointF;
}
QPointF CutFile_Data::GetPosOrg()
{
    return this->posOrg;
}

void    CutFile_Data::SetPosToPulseScale(QPointF _pointF)
{
    this->posToPulseScale = _pointF;
}

QPointF CutFile_Data::GetPosToPulseScale()
{
    return this->posToPulseScale;
}

void    CutFile_Data::SetPosLmt(QPointF _pointF)
{
    this->posLimit = _pointF;
}

QPointF CutFile_Data::GetPosLmt()
{
    return this->posLimit;
}

void    CutFile_Data::SetPosMax(QPointF _pointF)
{
    this->posMax = _pointF;
}

QPointF CutFile_Data::GetPosMax()
{
    return this->posMax;
}

void    CutFile_Data::SetRealToCutScale(QPointF _pointF)
{
    this->realToCutScale = _pointF;
}

QPointF CutFile_Data::GetRealToCutScale()
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
void CutFile_Data::SetKnifeOffset(QList<int> _guidList, QList<QPointF> _offsetList)
{
    if(_guidList.count() != _offsetList.count())
        qDebug()<<"SetKnifeOffset fault";
    for(int i=0;i<qlcFileList->count();i++)
    {
        CutFile *_file = qlcFileList->at(i);
        for(int j= 0;j<_file->GetPageList()->count();j++)
        {
            CutPage *_page = _file->GetPage(j);
            for(int k = 0;k<_page->GetSampleList()->count();k++)
            {
                CutSample *_sample = _page->GetSample(k);
                for(int l = 0;l<_sample->GetNormalLineList()->count();l++)
                {
                    CutLine *_line = _sample->GetNormalLine(l);
                    for(int m = 0;m<_guidList.count();m++)
                    {
                        if(_line->GetKnifeGuid() == _guidList.at(m))
                        {
                            _line->SetKnifeOffset(_offsetList.at(m));
                            break;
                        }
                    }
                }
            }
        }
    }
}
