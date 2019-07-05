#include "cuttest.h"

CutTest::CutTest(QObject *parent) : QObject(parent)
{
    sample = new CutSample;
//    CutLine *a = new CutLine;
    sample->GetPunchLine()->AddPoint(QPointF(1,1),100);
   CutSample* sample2 = sample;
   sample2->GetPunchLine()->AddPoint(QPointF(2,2),200);
   CutLine line;
   line.AddPoint(QPointF(3,3),100);
   sample2->GetNormalLine()->append(&line);
   sample2->GetNormalLine()->append(&line);

}
