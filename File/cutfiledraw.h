#ifndef CUTFILEDRAW_H
#define CUTFILEDRAW_H

#include <QWidget>
#include <QDebug>
#include <QFrame>
#include <QPainter>
#include <QRect>
#include "cutfileformat.h"
class CutFileDraw : public QWidget
{
    Q_OBJECT
private:
    void CutFileDraw_DrawLine(QPointF q1,QPointF q2,QPointF fact,QPointF offset);
public:
    explicit CutFileDraw(QWidget *parent = nullptr);
    void CutFileDraw_DisplayFileData();

    void CutFileDraw_SetPaintFrame(QFrame *_paintFrame);
    void CutFileDraw_SetPaintContent(QList<fileData_t> *_fileContent);
    void CutFileDraw_SetPaintFactorPulsePerMillimeter(QPointF *_factorPulsePerMillimeter);
    void CutFileDraw_SetPaintLogicOrg(QPointF *_org);
    void CutFileDraw_SetPaintLogicRealTime(QPointF *_pos);

    void CutFileDraw_SetRangePage(QPointF *_rectRangePage);
    void CutFileDraw_SetRangeMax(QPointF *_rectRangeMax);
    void CutFileDraw_SetPosFWheel(QPointF _posFMouse);
    void CutFileDraw_SetPosFMousePressed(QPointF _posFMouse);
    void CutFileDraw_SetPosFMouseReleased();
    void CutFileDraw_SetPosFMouseMoveDelta(QPointF _posFMouse);
    void CutFileDraw_SetSizeFixed();

    void CutFileDraw_SetFactor(int _dir,bool _divEn);
private:
    QFrame *paintFrame;
    QList<fileData_t> *fileContent;
    QPointF  *posRangeLimit;
    QPointF  *posRangeMax;
    QPointF  *posLogicOrg;
    QPointF  *posLogicRealTime;
    QPointF *factorPulsePerMillimeter;
    QPointF posFWheel;
    QPointF posFMousePressed;
    QPointF posFMouseMoved;

    QTransform transPosToLogic;
    QPointF posLogic;
    double  paintFactor;

signals:

public slots:
};

#endif // CUTFILEDRAW_H
