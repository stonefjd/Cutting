#ifndef CUTFILEHANDLE_H
#define CUTFILEHANDLE_H

#include <QObject>
#include <QFrame>
#include <QDockWidget>

#include "Base/cutfile.h"
#include "cutfile_ui.h"
class CutFileHandle : public QObject
{
    Q_OBJECT
private:
    QList<CutFile*> qlcFileList;
    CutFile_UI *UI_cutFile = new CutFile_UI;

public:
    explicit CutFileHandle(QObject *parent = nullptr);
    CutFileHandle(QDockWidget *_dockwgt,QFrame *_frame);
signals:

public slots:
};

#endif // CUTFILEHANDLE_H
