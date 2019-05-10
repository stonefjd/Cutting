#include "cutfiledraw.h"

CutFileDraw::CutFileDraw(QWidget *parent) : QWidget(parent)
{
    paintFactor = 1;
    posFWheel.setX(0);
    posFWheel.setY(0);
    posFMousePressed.setX(0);
    posFMousePressed.setY(0);
    posFMouseReleased.setX(0);
    posFMouseReleased.setY(0);
    posFMouseMoved.setX(0);
    posFMouseMoved.setY(0);
    posFMouseDelta.setX(0);
    posFMouseDelta.setY(0);
}
void CutFileDraw::CutFileDraw_SetPaintFrame(QFrame *_paintFrame)
{
    this->paintFrame = _paintFrame;
}
void CutFileDraw::CutFileDraw_SetPaintContent(QList<fileData_t> *_fileContent)
{
    this->fileContent = _fileContent;
}
void CutFileDraw::CutFileDraw_SetPosFWheel(QPointF _posFMouse)
{
    this->posFWheel = _posFMouse;
}
void CutFileDraw::CutFileDraw_SetPosFMousePressed(QPointF _posFMouse)
{
    this->posFMousePressed = transPosToLogic.map(_posFMouse);
//    this->posFMouseDelta = this->posFMouseDelta+this->posFMousePressed-this->posFMouseReleased;
    qDebug()<<"Pressed:"<<posFMousePressed;
}
void CutFileDraw::CutFileDraw_SetPosFMouseReleased(QPointF _posFMouse)
{
    this->posFMouseReleased = transPosToLogic.map(_posFMouse);
//    this->posFMouseDelta = this->posFMouseMoved;
    qDebug()<<"delta:"<<posFMouseReleased;
}
void CutFileDraw::CutFileDraw_SetPosFMouseMoveDelta(QPointF _posFMouse)
{
    this->posFMouseMoved = (transPosToLogic.map(_posFMouse)-posFMousePressed);
//    this->posFMouseMoved.setY(_posFMouse.y()-posFMousePressed.y());
//            _posFMouse-this->posFMousePressed;
    qDebug()<<"movNow"<<_posFMouse;
}
void CutFileDraw::CutFileDraw_SetFactor(int _dir,bool _divEn)
{
    (_dir>0)?(_divEn?(paintFactor*=1.01):(paintFactor*=1.1)):(_divEn?(paintFactor/=1.01):(paintFactor/=1.1));
}
void CutFileDraw::CutFileDraw_DisplayFileData()
{
    QPainter painter(paintFrame);
    QPen pen(QColor(100,212,100),0);
    painter.setPen(pen);

    //----设置缩放和平移的量纲
    painter.scale(static_cast<qreal>(paintFactor),static_cast<qreal>(paintFactor));
    painter.translate(transPosToLogic.inverted().map(posFMouseMoved)/paintFactor);
    //----获取当前 控件坐标->刻度坐标的转换
    transPosToLogic = painter.combinedTransform().inverted();


    posLogic = painter.combinedTransform().inverted().map(posFWheel);
    qDebug()<<posFWheel<<posLogic;

//    painter.setViewport(static_cast<int>(-_pos.x()*(drawFactor-1)),static_cast<int>(-_pos.y()*(drawFactor-1)),static_cast<int>(2000*drawFactor) ,static_cast<int>(2000*drawFactor));
//    painter.setWindow(0,0,2000,2000);

    if(!fileContent->isEmpty())
    {
        for(int i= 0;i<fileContent->at(0).pageCluster.count();i++)
        {
            for(int j = 0;j<fileContent->at(0).pageCluster.at(i).sampleCluster.count();j++)
            {
                for(int k = 0;k<fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).lineCluster.count();k++)
                {
                    for(int l = 0;l<fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster.count();l++)
                    {
                        if(l >=1)
                        {
                            painter.drawLine(fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster.at(l-1)/128,
                                             fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster.at(l)/128);
                        }
                    }
                }
                for(int punchCnt = 0;punchCnt<fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).punchDotCount;punchCnt++)
                {
                    painter.drawEllipse(fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).punchCluster.at(punchCnt).dot/128,2,2);
                }
                for(int drillCnt = 0;drillCnt<fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).punchDotCount;drillCnt++)
                {
                    painter.drawEllipse(fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).punchCluster.at(drillCnt).dot/128,1,1);
                }
            }
        }
    }
}


