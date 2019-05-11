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
    void CutFileDraw_SetPageRange(QRect *_rectPageRange);
    void CutFileDraw_SetPaintFactor(QPointF *_factorPulsePerMillimeter);
    void CutFileDraw_SetPosFWheel(QPointF _posFMouse);
    void CutFileDraw_SetPosFMousePressed(QPointF _posFMouse);
    void CutFileDraw_SetPosFMouseMoveDelta(QPointF _posFMouse);

    void CutFileDraw_SetFactor(int _dir,bool _divEn);
private:
    QFrame *paintFrame;
    QList<fileData_t> *fileContent;
    QRect   *rectPageRange;
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
