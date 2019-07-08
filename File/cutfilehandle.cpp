#include "cutfilehandle.h"

CutFileHandle::CutFileHandle(QObject *parent) : QObject(parent)
{
//    UI_cutFile->SetFileList(&this->qlcFileList);
}

CutFileHandle::CutFileHandle(QDockWidget *_dockwgt,QFrame *_frame)
{
     UI_cutFile->SetFileList(&this->qlcFileList);
     UI_cutFile->SetDockWidget(_dockwgt);
     UI_cutFile->SetPaintFrame(_frame);
     UI_cutFile->InitialModel();
}
