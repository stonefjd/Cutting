#ifndef CUTFILEFORMAT_H
#define CUTFILEFORMAT_H

#include<QString>
#include<QPointF>
#include<QList>
#define HEX_PER_MM 1000.0

#define CODE_TEST 0
struct dotData_t
{
    int dotId;
    int toolId;//切割当前线条的刀ID
    float dotAngle;
    float dotDeep;
    QPointF dot;
};
struct lineData_t
{
    int toolId;//切割当前线条的刀ID
    int lineId;//线条编号
//    int lineType;//当前线条类型：0 末尾抬刀 1 每点抬刀（当前样片用同一把冲时，所有冲的点也当作线条，只是这一类线条每一点下刀后都会抬刀）
//    int dotCount;//当前线条的点数量
    float lineDeep;//当前线条刀深
    QPointF toolOffset;//刀偏置
    QVector<QPointF> pointCluster;//当前线条的点集合
};
struct sampleData_t
{
    int sampleId;//当前样片ID
//    int lineCount;//当前窗中线条数量
//    int punchDotCount;
//    int drillDotCount;
    QPointF focusInSample;
    QList<lineData_t> lineCluster;//当前窗线条数据集
    QList<dotData_t> punchCluster;
    QList<dotData_t> drillCluster;
    bool isFinished;
};
struct pageData_t
{
    int pageId;//当前窗ID pageId
//    int sampleCount;//当前窗中的样片数量
    float pageLength;//当前窗裁完后，调用该长度进行移动
    QList<sampleData_t> sampleCluster;//当前窗的样片数据集
};

struct fileData_t
{
    QString cutFileName;
    QString cutFilePath;
    int cutTimes;//切割次数
    int pageCount;//当前文档中窗数量
    QList<pageData_t> windowCluster;//当前文档中的窗数据集
};
#endif // CUTFILEFORMAT_H
