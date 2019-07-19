#include "cutfile_data.h"

CutFile_Data::CutFile_Data(QObject *parent) : QObject(parent)
{

}
QList<CutFile*>* CutFile_Data::GetFileList()
{
    return this->qlcFileList;
}
QPointF*    CutFile_Data::GetPosOrg()
{
    return this->posOrg;
}
double*     CutFile_Data::GetPosToPulseScaleXY()
{
    return this->posToPulseScaleXY;
}
QPointF*    CutFile_Data::GetPosLmt()
{
    return this->posLmt;
}
QPointF*    CutFile_Data::GetPosMax()
{
    return this->posMax;
}
QPointF*    CutFile_Data::GetRealToCutScale()
{
    return this->realToCutScale;
}
QPointF*    CutFile_Data::GetPosRt()
{
    return this->posRt;
}
double*     CutFile_Data::GetRtAgl()
{
    return this->rtAgl;
}

void    CutFile_Data::SetPosOrg(QPointF* _pointF)
{
    this->posOrg = _pointF;
}
void    CutFile_Data::SetPosToPulseScaleXY(double* _val)
{
    this->posToPulseScaleXY = _val;
}
void    CutFile_Data::SetPosLmt(QPointF* _pointF)
{
    this->posLmt = _pointF;
}
void    CutFile_Data::SetPosMax(QPointF* _pointF)
{
    this->posMax = _pointF;
}
void    CutFile_Data::SetRealToCutScale(QPointF* _pointF)
{
    this->realToCutScale = _pointF;
}
void    CutFile_Data::SetPosRt(QPointF* _pointF)
{
    this->posRt = _pointF;
}
void    CutFile_Data::SetRtAgl(double *_agl)
{
    this->rtAgl = _agl;
}
//void    CutFile_Data::SetListCfgApron(QList<CfgApron*>* _list)
//{
//    this->cfgApronList = _list;
//}

//void CutFile_Data::SetKnifeOffset()
//{
//    //通过机座数据更新裁切列表中的相关偏移数据
//    QList<int> tempGuidList;
//    QList<QPointF> tempOffsetList;
//    for(int i=0;i<cfgApronList->count();i++)
//    {
//        tempGuidList.append(cfgApronList->at(i)->GetKnifeGuid());
//        tempOffsetList.append(QPointF(cfgApronList->at(i)->GetXOffset(),cfgApronList->at(i)->GetYOffset()));
//    }

//    if(tempGuidList.count() != tempOffsetList.count())
//        qDebug()<<"SetKnifeOffset fault";
//    for(int i=0;i<qlcFileList->count();i++)
//    {
//        CutFile *_file = qlcFileList->at(i);
//        for(int j= 0;j<_file->GetPageList()->count();j++)
//        {
//            CutPage *_page = _file->GetPage(j);
//            for(int k = 0;k<_page->GetSampleList()->count();k++)
//            {
//                CutSample *_sample = _page->GetSample(k);
//                for(int l = 0;l<_sample->GetNormalLineList()->count();l++)
//                {
//                    CutLine *_line = _sample->GetNormalLine(l);
//                    for(int m = 0;m<tempGuidList.count();m++)
//                    {
//                        if(_line->GetKnifeGuid() == tempGuidList.at(m))
//                        {
//                            _line->SetKnifeOffset(tempOffsetList.at(m));
//                            break;
//                        }
//                    }
//                }
//            }
//        }
//    }
//}
