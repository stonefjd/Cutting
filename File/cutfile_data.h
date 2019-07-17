#ifndef CUTFILE_DATA_H
#define CUTFILE_DATA_H

#include <QObject>
#include <QDebug>
#include "Base/cutfile.h"
#define HEX_PER_MM 1000.0

class CutFile_Data : public QObject
{
    Q_OBJECT
private:
    QList<CutFile*>* qlcFileList = new QList<CutFile*>;
    QPointF posOrg;            //逻辑切割原点
    double  posToPulseScaleXY;   //每毫米脉冲数
    QPointF posLmt;     //逻辑切割范围
    QPointF posMax;       //全局最大运动边界
    QPointF realToCutScale;    //实际切割缩放比例

    QPointF posRt;  //实时机头位置
    double  *rtAgl;//实时角度
public:
    explicit CutFile_Data(QObject *parent = nullptr);

    QList<CutFile*>* GetFileList();
    void    SetPosOrg(QPointF _pointF);
    QPointF GetPosOrg();
    void    SetPosToPulseScaleXY(double _val);
    double  GetPosToPulseScaleXY();
    void    SetPosLmt(QPointF _pointF);
    QPointF GetPosLmt();
    void    SetPosMax(QPointF _pointF);
    QPointF GetPosMax();
    void    SetRealToCutScale(QPointF _pointF);
    QPointF GetRealToCutScale();
    void    SetPosRt(QPointF _pointF);
    QPointF GetPosRt();
    void    SetRtAgl(double *_agl);
    double  *GetRtAgl();

    void    SetKnifeOffset(QList<int> _guidList, QList<QPointF> _offsetList);
signals:

public slots:
};

#endif // CUTFILE_DATA_H
