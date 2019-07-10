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
void CutFileHandle::SlotUpdateHeadPosRt(int _xPos,int _yPos)
{
    cutFile_Data.SetPosRt(QPointF(static_cast<double>(_xPos)/cutFile_Data.GetPosToPulseScale()->x(),
                                      static_cast<double>(_yPos)/cutFile_Data.GetPosToPulseScale()->y()));
}
