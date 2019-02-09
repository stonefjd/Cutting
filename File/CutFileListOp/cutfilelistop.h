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
struct cutFileNode_t
{
    QString fName;
    QString fPath;
    QString fCnt;
    cutFileNode_t *next;
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

    QStringList CutFileList_GetListContent();
    QString CutFileList_GetListPath();

    void CutFileList_WidgetInit(QTableWidget *_tableWidget);
    void CutFileList_Display(QTableWidget *_tableWidget);
    QStringList CutFileList_ViewOpenFile(QString _name,QString _filter,enum QFileDialog::FileMode _fileMode);
    QString CutFileList_GetColumnFileName(QStringList _pathList,int i);
    QString CutFileList_GetColumnFilePath(QStringList _pathList,int i);
    QString CutFileList_GetColumnFileCounter(QStringList _pathList,int i);
    void CutFileList_SetColumnFileCounter(QStringList *_pathList,int column,int counter);

signals:

public slots:
    void CutFileList_SpinBoxChg(int i);
private:
    QString filePath;
    QStringList filePathList;
};

#endif // CUTFILELISTOP_H
