#ifndef CUTFILE_DATA_H
#define CUTFILE_DATA_H

#include <QObject>
#include <QDebug>
#include "Base/cutfile.h"
//#include "Machine/Config/cfgmachhandle.h"

#define HEX_PER_MM 1000.0

class CutFile_Data : public QObject
{
    Q_OBJECT
private:
    //待传出变量，因为数据量大，因此开辟于堆内存中
    QList<CutFile*>* qlcFileList = new QList<CutFile*>;
    //待传入机头变量
    QPointF* posOrg;            //逻辑切割原点
    double*  posToPulseScaleXY; //每毫米脉冲数
    QPointF* posLmt;            //逻辑切割范围
    QPointF* posMax;            //全局最大运动边界
    QPointF* realToCutScale;    //实际切割缩放比例
    QPointF* posRt;             //实时机头位置
    double*  rtAgl;             //实时角度

//    QList<CfgApron*>* cfgApronList;
public:
    explicit CutFile_Data(QObject *parent = nullptr);

    QList<CutFile*>* GetFileList();

    void    SetPosOrg(QPointF* _pointF);
    void    SetPosToPulseScaleXY(double* _val);
    void    SetPosLmt(QPointF* _pointF);
    void    SetPosMax(QPointF* _pointF);
    void    SetRealToCutScale(QPointF* _pointF);
    void    SetPosRt(QPointF* _pointF);
    void    SetRtAgl(double *_agl);
//    void    SetListCfgApron(QList<CfgApron*>* _list);

    QPointF* GetPosOrg();
    double*  GetPosToPulseScaleXY();
    QPointF* GetPosLmt();
    QPointF* GetPosMax();
    QPointF* GetRealToCutScale();
    QPointF* GetPosRt();
    double*  GetRtAgl();

    void    SetKnifeOffset();//新增内容时调用
signals:

public slots:
};

#endif // CUTFILE_DATA_H
