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
public:
    explicit CutFileDraw(QWidget *parent = nullptr);
    void CutFileDraw_DisplayFileData();

    void CutFileDraw_SetPaintFrame(QFrame *_paintFrame);
    void CutFileDraw_SetPaintContent(QList<fileData_t> *_fileContent);
    void CutFileDraw_SetPaintFactor(QPointF *_factorPulsePerMillimeter);
    void CutFileDraw_SetPaintOrgLogic(QPoint *_org);
    void CutFileDraw_SetRangePage(QPoint *_rectRangePage);
    void CutFileDraw_SetRangeMax(QPoint *_rectRangeMax);
    void CutFileDraw_SetPosFWheel(QPointF _posFMouse);
    void CutFileDraw_SetPosFMousePressed(QPointF _posFMouse);
    void CutFileDraw_SetPosFMouseMoveDelta(QPointF _posFMouse);

    void CutFileDraw_SetFactor(int _dir,bool _divEn);
private:
    QFrame *paintFrame;
    QList<fileData_t> *fileContent;
    QPoint  *posRangeLimit;
    QPoint  *posRangeMax;
    QPoint  *posOrgLogic;
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
