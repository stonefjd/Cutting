#ifndef CUTSAMPLE_H
#define CUTSAMPLE_H

#include <QObject>
#include <QRectF>

#include "cutline.h"
class CutSample : public QObject
{
    Q_OBJECT
public:
    explicit CutSample(QObject *parent = nullptr);

private:
    int m_nSampleId;
    QRectF m_rctAirSquare;
    QList<CutLine*> *m_lNormalLine = new QList<CutLine*>;
    CutLine* m_lPunchLine = new CutLine;
    CutLine* m_lDrillLine = new CutLine;
public:
    int GetSampleId(void);
    void SetSampleId(int _id);

    QRectF GetInhaleSqare();
    void SetInhaleSqare(QRectF _sqare);
    CutLine* GetPunchLine();
    CutLine* GetDrillLine();
    CutLine* GetNormalLine(int _index);
    QList<CutLine*> *GetNormalLineList();
signals:

public slots:
};

#endif // CUTSAMPLE_H
