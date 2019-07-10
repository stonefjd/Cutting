#include "cutfilehandle.h"

CutFileHandle::CutFileHandle(QObject *parent) : QObject(parent)
{
//    cutFile_UI->SetFileList(&this->qlcFileList);
}

CutFileHandle::CutFileHandle(QDockWidget *_dockwgt, QFrame *_frame)
{
     cutFile_UI->SetFileData(&this->cutFile_Data);
     cutFile_UI->InitialModel(_dockwgt,_frame);
     connect(cutFile_UI,SIGNAL(UpdateFileAdded()),this,SLOT(SlotUpdateFileAdded()));
}
void CutFileHandle::SlotUpdateHeadPosRt(int _xPos,int _yPos)
{
    cutFile_Data.SetPosRt(QPointF(static_cast<double>(_xPos)/cutFile_Data.GetPosToPulseScale().x(),
                                  static_cast<double>(_yPos)/cutFile_Data.GetPosToPulseScale().y()));
}
void CutFileHandle::SlotUpdateDataHead(QPointF _posOrg,QPointF _posLmt,QPointF _posMax,QPointF _posToPulseScale,QPointF _realToCutScale)
{
    cutFile_Data.SetPosOrg(_posOrg);
    cutFile_Data.SetPosLmt(_posLmt);
    cutFile_Data.SetPosMax(_posMax);
    cutFile_Data.SetPosToPulseScale(_posToPulseScale);
    cutFile_Data.SetRealToCutScale(_realToCutScale);
}
void CutFileHandle::SlotUpdateDataApron(QList<CfgApron*> _aConfig)
{
    //通过机座数据更新裁切列表中的相关偏移数据
    QList<int> tempGuidList;
    QList<QPointF> tempOffsetList;
    for(int i=0;i<_aConfig.count();i++)
    {
        tempGuidList.append(_aConfig.at(i)->GetKnifeGuid());
        tempOffsetList.append(QPointF(_aConfig.at(i)->GetXOffset(),_aConfig.at(i)->GetYOffset()));
    }
//    qDebug()<<tempGuidList<<' '<<tempOffsetList;
    cutFile_Data.SetKnifeOffset(tempGuidList,tempOffsetList);
}

void CutFileHandle::SlotUpdateFileAdded()
{
    qDebug()<<"added";
    emit UpdateDataApron();
}
