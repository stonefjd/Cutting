#ifndef CUTFILELIST_H
#define CUTFILELIST_H

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
#include "File/cutfileformat.h"

class CutFileList : public QObject
{
    Q_OBJECT
public:
    explicit CutFileList(QObject *parent = nullptr);
    void CutFileList_ChoseList();
    void CutFileList_ChoseSingleFile();
    void CutFileList_RemoveFileFromList(QTableWidget *_tableWidget);
    void CutFileList_UpFileFromList(QTableWidget *_tableWidget);
    void CutFileList_DownFileFromList(QTableWidget *_tableWidget);
    void CutFileList_ExportFileFromList(QTableWidget *_tableWidget);

    QString CutFileList_GetListPath();
    void CutFileList_SetPosLogicOrg(QPointF *_org);
    void CutFileList_SetFactorCutScale(QPointF *_scale);

    void CutFileList_WidgetInit(QTableWidget *_tableWidget);
    void CutFileList_DisplayList(QTableWidget *_tableWidget);
signals:

public slots:
    void CutFileList_SpinBoxChg(int i);

public:
    QList<fileData_t> fileVector;

private:
    QString filePath;//特指列表文档的路径!
//    QStringList filePathList;
    QPointF *posLogicOrg;
    QPointF *factorCutScale;
    QStringList CutFileList_ViewOpenFile(QString _name,QString _filter,enum QFileDialog::FileMode _fileMode);
    void CutFileList_PrintVector(QList<fileData_t> _fileVector);
    void CutFileList_LoadCutData(int _fIdx);
};

#endif // CUTFILELIST_H
