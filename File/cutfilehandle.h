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
    CutFile_Data cutFile_Data;
public:
    explicit CutFileHandle(QObject *parent = nullptr);
    CutFileHandle(QDockWidget *_dockwgt, QFrame *_frame, CfgMachHandle *_machHandle);
signals:

public slots:
};

#endif // CUTFILEHANDLE_H
