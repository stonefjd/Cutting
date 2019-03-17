#ifndef CUTFILELISTOP_H
#define CUTFILELISTOP_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QDebug>
#include <QTranslator>
#include <QTableWidget>
#include <QMessageBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QPointF>
#include <QDomElement>
#include <QFrame>
#include <QPainter>
struct dotData_t
{
    int dotId;
    float dotAngle;
    QPointF dotOrg;
};

struct lineData_t
{
    int toolId;//切割当前线条的刀ID
    int lineId;//线条编号
    int lineType;//当前线条类型：0 末尾抬刀 1 每点抬刀（当前样片用同一把冲时，所有冲的点也当作线条，只是这一类线条每一点下刀后都会抬刀）
    int dotCount;//当前线条的点数量
    float lineDeep;//当前线条刀深
    QPointF toolOffset;//刀偏置
    QList<dotData_t> dotCluster;//当前线条的点集合
};
struct sampleData_t
{
    int sampleId;//当前样片ID
    int lineCount;//当前窗中线条数量
    QList<lineData_t> lineCluster;//当前窗线条数据集
};
struct windowData_t
{
    int windowId;//当前窗ID
    int sampleCount;//当前窗中的样片数量
    float windowLength;//当前窗裁完后，调用该长度进行移动
    QList<sampleData_t> sampleCluster;//当前窗的样片数据集
};

struct fileData_t
{
    QString cutFileName;
    QString cutFilePath;
    int cutCount;
    int windowCount;//当前文档中窗数量
    QList<windowData_t> windowCluster;//当前文档中的窗数据集
};

class CutFileListOp : public QObject
{
    Q_OBJECT
public:
    explicit CutFileListOp(QObject *parent = nullptr);
    void CutFileList_ChoseList();
    void CutFileList_ChoseSingleFile();
    void CutFileList_RemoveFileFromList(QTableWidget *_tableWidget);
    void CutFileList_UpFileFromList(QTableWidget *_tableWidget);
    void CutFileList_DownFileFromList(QTableWidget *_tableWidget);
    void CutFileList_ExportFileFromList(QTableWidget *_tableWidget);

    QString CutFileList_GetListPath();

    void CutFileList_WidgetInit(QTableWidget *_tableWidget);
    void CutFileList_DisplayList(QTableWidget *_tableWidget);
    void CutFileList_DrawFileData(QFrame *_ptFrame);

signals:

public slots:
    void CutFileList_SpinBoxChg(int i);
private:
    QString filePath;//特指列表文档的路径!
    QStringList filePathList;
    QList<fileData_t> fileVector;

    QStringList CutFileList_ViewOpenFile(QString _name,QString _filter,enum QFileDialog::FileMode _fileMode);
    void CutFileList_PrintVector(QList<fileData_t> _fileVector);
    void CutFileList_LoadCutData(int _fIdx);
};

#endif // CUTFILELISTOP_H
