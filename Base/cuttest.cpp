#include "cuttest.h"

CutTest::CutTest(QObject *parent) : QObject(parent)
{
    sample = new CutSample;
//    sample->GetNormalLine()[0].AddPoint(QPointF(0,0),100.1);

    CutSample *sample2 = sample;
//    sample2->GetNormalLine()[0].AddPoint(QPointF(1,1),100.2);
}
