#include "cutfilehandle.h"

//CutFileHandle::CutFileHandle(QObject *parent) : QObject(parent)
//{
//}

CutFileHandle::CutFileHandle(QDockWidget *_dockwgt, QFrame *_frame)
{
     cutFile_UI->SetFileData(this->cutFile_Data);
     cutFile_UI->InitialModel(_dockwgt,_frame);
//     connect(cutFile_UI,SIGNAL(UpdateFileAdded()),this,SLOT(SlotUpdateFileAdded()));
}
CutFile_Data* CutFileHandle::GetFileData()
{
    return this->cutFile_Data;
}
void CutFileHandle::InitEventFilter()
{
    cutFile_UI->InitEventFilter();
}
void CutFileHandle::SlotOneFileFinished()
{
    cutFile_Data->OneFileFinished();
}
