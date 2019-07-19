#ifndef CUTFILE_UI_H
#define CUTFILE_UI_H

#include <QObject>
#include <QDebug>
#include <QDockWidget>
#include <QFrame>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QFile>
#include <QFileDialog>
#include <QSpinBox>
#include <QHeaderView>
#include <QMessageBox>
#include <QDomElement>
#include <QPainter>
#include <QSizePolicy>

#include "Base/cutfile.h"
#include "cutfile_data.h"
class CutFile_UI : public QObject
{
    Q_OBJECT
private:
    CutFile_Data *cFileData;

    QPointF posFWheel;
    QPointF posFMousePressed;
    QPointF posFMouseMoved;

    QTransform transPosToLogic;
    QPointF posLogic;
    double  paintFactor;

    QDockWidget *qwDockWidget;
    QFrame      *qwFrame;

    QPushButton *qwBtnAddt  = new QPushButton(tr("添加"));
    QPushButton *qwBtnRemv  = new QPushButton(tr("移除"));
    QPushButton *qwBtnUpwd  = new QPushButton(tr("上移"));
    QPushButton *qwBtnDnwd  = new QPushButton(tr("下移"));
    QPushButton *qwBtnImpt  = new QPushButton(tr("导入列表"));
    QPushButton *qwBtnExpt  = new QPushButton(tr("导出列表"));

    QTableWidget *qwTableWait = new QTableWidget();
    QTableWidget *qwTableFnsh = new QTableWidget();

    QGridLayout *gridLayout = new QGridLayout();
    QVBoxLayout *vLayout    = new QVBoxLayout();

    QStringList GetOpenFileList (QString _name,QString _filter,enum QFileDialog::FileMode _fileMode);
    void        DisplayFileList (QTableWidget *_tableWidget,QList<CutFile*>* _fileList);
    bool        CheckFileRepeat (QString _filePath,         QList<CutFile*>* _fileList);
    void        AddFile         (QString _filePath,         QList<CutFile*>* _fileList);
    void        ImportFiles     (                           QList<CutFile*>* _fileList);
    void        LoadFileData    (CutFile *_file);
    void        DrawFile        (int _fileIndex);
protected:
    bool eventFilter(QObject *watched, QEvent *e);

public:
    explicit CutFile_UI(QObject *parent = nullptr);
    void SetFileData(CutFile_Data *_fileData);
    void InitialModel(QDockWidget *_dockwgt, QFrame *_frame);
    void InitEventFilter();
signals:
//    void UpdateFileAdded();
public slots:
    void SlotBtnAddtClicked();
    void SlotBtnRemvClicked();
    void SlotBtnUpwdClicked();
    void SlotBtnDnwdClicked();
    void SlotBtnImptClicked();
    void SlotBtnExptClicked();
    void SlotChkBxSpin(int _cnt);
};

#endif // CUTFILE_UI_H
