#include "cutfilehandle.h"

CutFileHandle::CutFileHandle(QObject *parent) : QObject(parent)
{
//    cutFile_UI->SetFileList(&this->qlcFileList);
}

CutFileHandle::CutFileHandle(QDockWidget *_dockwgt,QFrame *_frame,CfgMachHandle *_machHandle)
{
     cutFile_UI->SetFileData(&this->cutFile_Data);
//     cutFile_UI->SetDockWidget(_dockwgt);
//     cutFile_UI->SetPaintFrame(_frame);
//     cutFile_UI->SetMachHandle(_machHandle);
     cutFile_UI->InitialModel(_dockwgt,_frame,_machHandle);
}
