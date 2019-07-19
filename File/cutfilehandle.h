#ifndef CUTFILEHANDLE_H
#define CUTFILEHANDLE_H

#include <QObject>
#include <QFrame>
#include <QDockWidget>

#include "Base/cutfile.h"
#include "cutfile_ui.h"
#include "cutfile_data.h"
#include "Machine/Config/cfgmachhandle.h"
class CutFileHandle : public QObject
{
    Q_OBJECT
private:
    CutFile_UI *cutFile_UI = new CutFile_UI;
    CutFile_Data *cutFile_Data = new CutFile_Data;
public:
//    explicit CutFileHandle(QObject *parent = nullptr);
    CutFileHandle(QDockWidget *_dockwgt, QFrame *_frame);

    CutFile_Data* GetFileData();
signals:
    void UpdateDataApronRequest();
public slots:
    void SlotUpdateDataHeadPosRt(QPointF posRT);
    void SlotUpdateDataHead(CfgHead_T _data);
    void SlotUpdateDataApron(QList<CfgApron_T> _aConfig);
    void SlotUpdateFileAdded();
};

#endif // CUTFILEHANDLE_H
