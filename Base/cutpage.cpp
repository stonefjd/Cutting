#include "cutpage.h"

CutPage::CutPage(QObject *parent) : QObject(parent)
{
    this->m_qlcPage->clear();
}

CutSample* CutPage::GetSample(int _index)
{
    return this->m_qlcPage->at(_index);
}

QList<CutSample*>* CutPage::GetSampleList()
{
    return this->m_qlcPage;
}

float CutPage::GetPageLength(void)
{
    return this->m_qlnPageLength;
}
void CutPage:: SetPageLength(float _len)
{
    this->m_qlnPageLength = _len;
}
