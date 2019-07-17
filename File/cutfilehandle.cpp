#include "cutfilehandle.h"

//CutFileHandle::CutFileHandle(QObject *parent) : QObject(parent)
//{
//}

CutFileHandle::CutFileHandle(QDockWidget *_dockwgt, QFrame *_frame)
{
     cutFile_UI->SetFileData(this->cutFile_Data);
     cutFile_UI->InitialModel(_dockwgt,_frame);
     connect(cutFile_UI,SIGNAL(UpdateFileAdded()),this,SLOT(SlotUpdateFileAdded()));
}
CutFile_Data* CutFileHandle::GetFileData()
{
    return this->cutFile_Data;
}
//设置实时的机头值
void CutFileHandle::SlotUpdateHeadPosRt(QPointF posRT)
{
    cutFile_Data->SetPosRt(posRT);
}
void CutFileHandle::SlotUpdateDataHead(CfgHead_T _data)
{
    cutFile_Data->SetPosOrg(_data.posOrg);
    cutFile_Data->SetPosLmt(_data.posLmt);
    cutFile_Data->SetPosMax(_data.posMax);
    cutFile_Data->SetPosToPulseScaleXY(_data.posToPulseScaleXY);
    cutFile_Data->SetRealToCutScale(_data.realToCutScale);
}
void CutFileHandle::SlotUpdateDataApron(QList<CfgApron_T> _aConfig)
{
    //通过机座数据更新裁切列表中的相关偏移数据
    QList<int> tempGuidList;
    QList<QPointF> tempOffsetList;
    for(int i=0;i<_aConfig.count();i++)
    {
        tempGuidList.append(_aConfig.at(i).apronKnifeGuid);
        tempOffsetList.append(QPointF(_aConfig.at(i).apronOffsetX,_aConfig.at(i).apronOffsetY));
    }
    cutFile_Data->SetKnifeOffset(tempGuidList,tempOffsetList);
}

void CutFileHandle::SlotUpdateFileAdded()
{
    //请求更新刀座参数
    qDebug()<<"added";
    emit UpdateDataApronRequest();
}
