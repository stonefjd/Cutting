#include "cutfile.h"

CutFile::CutFile(QObject *parent) : QObject(parent)
{
    this->m_qlcFile->clear();
    this->m_nTimes = 0;
}

void CutFile::AddCutPage(CutPage *page,int _len)
{
    page->SetPageLength(_len);
    this->m_qlcFile->append(page);
//    this->m_qlcFile->last()->
}

void    CutFile::SetFilePath(QString _path)
{
    this->m_qstrFilePath = _path;
}
QString CutFile::GetFilePath(void)
{
    return this->m_qstrFilePath;
}
void    CutFile::SetFileName(QString _name)
{
    this->m_qstrFileName = _name;
}
QString CutFile::GetFileName(void)
{
    return this->m_qstrFileName;
}
void    CutFile::SetCutTimes(int _times)
{
    this->m_nTimes = _times;
}
int     CutFile::GetCutTimes(void)
{
    return this->m_nTimes;
}

CutPage* CutFile::GetPage(int _index)
{
    return this->m_qlcFile->at(_index);
}
QList<CutPage*>* CutFile::GetPageList()
{
    return this->m_qlcFile;
}
bool CutFile::ReduceCutTimes()
{
    if(m_nTimes>1)
    {
        m_nTimes--;
        return true;
    }
    else
    {
        m_nTimes = 0;
        return false;
    }
}
void CutFile::ResetFileState()
{
    if(this->m_qlcFile->isEmpty()!=true)
    {
        for(int i=0;i<m_qlcFile->count();i++)
        {
            CutPage *tempPage = m_qlcFile->at(i);
            for(int j=0;j<tempPage->GetSampleList()->count();j++)
            {
                tempPage->GetSample(j)->SetCutFinished(false);
            }
        }
    }
}
