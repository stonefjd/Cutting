#include "cutfile.h"

CutFile::CutFile(QObject *parent) : QObject(parent)
{

}

void CutFile:: SetPageLength(int _pageLength)
{
    this->m_nPageLenth = _pageLength;
}

int CutFile::GetPageLength()
{
    return this->m_nPageLenth;
}
QList<CutSample*>* CutFile::GetSampleList()
{
    return this->m_lSampleList;
}
CutSample* CutFile::GetSample(int _index)
{
    return this->m_lSampleList->at(_index);
}
