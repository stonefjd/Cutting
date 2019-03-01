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
#include <QXmlSimpleReader>

struct lineData_t
{
    int toolId;
    int windowSN;
    float cutDeep;
    QList<QPointF> cutLine;
};
struct drillData_t
{
    int toolId;
    int windowSN;
    float drillDeep;
    float drillAngle;
    QPointF drillDot;
};

struct fileData_t
{
    QString cutFileName;
    QString cutFilePath;
    int cutCount;
    QList<lineData_t> lineCluster;
    QList<drillData_t> dotCluster;
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
    void CutFileList_Display(QTableWidget *_tableWidget);

signals:

public slots:
    void CutFileList_SpinBoxChg(int i);
private:
    QString filePath;//特指列表文档的路径!
    QStringList filePathList;
    QList<fileData_t> fileVector;

    QStringList CutFileList_ViewOpenFile(QString _name,QString _filter,enum QFileDialog::FileMode _fileMode);
    void CutFileList_PrintVector(QList<fileData_t> _fileVector);
};

#endif // CUTFILELISTOP_H
