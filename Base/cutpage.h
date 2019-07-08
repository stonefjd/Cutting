#ifndef CUTPAGE_H
#define CUTPAGE_H

#include <QObject>

#include "cutsample.h"
class CutPage : public QObject
{
    Q_OBJECT
private:
    QList<CutSample*>* m_qlcPage = new QList<CutSample*>;
    float m_qlnPageLength;
public:
    explicit CutPage(QObject *parent = nullptr);

    CutSample* GetSample(int _index);
    QList<CutSample*>* GetSampleList();

    float  GetPageLength(void);
    void SetPageLength(float _len);
signals:

public slots:
};

#endif // CUTPAGE_H
