﻿#ifndef CUTFILELISTOP_H
#define CUTFILELISTOP_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QDebug>
#include <QTranslator>
#include <QTableWidget>
#include <QMessageBox>
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

    QStringList CutFileList_GetList();
    QString CutFileList_GetPath();

    void CutFileList_WidgetInit(QTableWidget *_tableWidget);
    void CutFileList_ListAll(QString _path);
    void CutFileList_Display(QTableWidget *_tableWidget);
    QStringList CutFileList_ViewOpenFile(QString _name,QString _filter,enum QFileDialog::FileMode _fileMode);

signals:

public slots:
private:
    QString filePath;
    QStringList filePathList;
};

#endif // CUTFILELISTOP_H
