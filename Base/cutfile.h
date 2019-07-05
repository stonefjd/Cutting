#ifndef CUTFILE_H
#define CUTFILE_H

#include <QObject>
#include "cutsample.h"
class CutFile : public QObject
{
    Q_OBJECT
private:
    QList<CutSample*> *m_lSampleList;
    int m_nPageLenth;
public:
    explicit CutFile(QObject *parent = nullptr);
    void SetPageLength(int _pageLength);
    int GetPageLength();

    QList<CutSample*>* GetSampleList();
    CutSample* GetSample(int _index);
signals:

public slots:
};

#endif // CUTFILE_H
