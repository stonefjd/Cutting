#include "cutfiledraw.h"

CutFileDraw::CutFileDraw(QWidget *parent) : QWidget(parent)
{
    paintFactor = 1;
    posFWheel.setX(0);
    posFWheel.setY(0);
    posFMousePressed.setX(0);
    posFMousePressed.setY(0);
    posFMouseMoved.setX(0);
    posFMouseMoved.setY(0);
}
void CutFileDraw::CutFileDraw_SetPaintFrame(QFrame *_paintFrame)
{
    this->paintFrame = _paintFrame;
}
void CutFileDraw::CutFileDraw_SetPaintContent(QList<fileData_t> *_fileContent)
{
    this->fileContent = _fileContent;
}

void CutFileDraw::CutFileDraw_SetPaintFactorPulsePerMillimeter(QPointF *_factorPulsePerMillimeter)
{
    this->factorPulsePerMillimeter = _factorPulsePerMillimeter;
}
void CutFileDraw::CutFileDraw_SetPaintLogicOrg(QPoint *_org)
{
    this->posLogicOrg = _org;
}
void CutFileDraw::CutFileDraw_SetPaintLogicRealTime(QPoint *_pos)
{
    this->posLogicRealTime = _pos;
}
void CutFileDraw::CutFileDraw_SetRangePage(QPoint *_rectRangePage)
{
    this->posRangeLimit = _rectRangePage;
}
void CutFileDraw::CutFileDraw_SetRangeMax(QPoint *_rectRangeMax)
{
    this->posRangeMax = _rectRangeMax;
}
void CutFileDraw::CutFileDraw_SetPosFWheel(QPointF _posFMouse)
{
    this->posFWheel = _posFMouse;
}
void CutFileDraw::CutFileDraw_SetPosFMousePressed(QPointF _posFMouse)
{
    this->posFMousePressed = transPosToLogic.map(_posFMouse);
    qDebug()<<"Pressed:"<<posFMousePressed;
}
void CutFileDraw::CutFileDraw_SetPosFMouseReleased()
{
    this->posFMouseMoved = QPointF(0,0);
}
void CutFileDraw::CutFileDraw_SetPosFMouseMoveDelta(QPointF _posFMouse)
{
    this->posFMouseMoved = (transPosToLogic.map(_posFMouse)-posFMousePressed);
    qDebug()<<"movNow"<<_posFMouse;
}
void CutFileDraw::CutFileDraw_SetSizeFixed()
{
    qDebug()<<"doubleClicked";
    double factorWidth = static_cast<double>(this->paintFrame->width())/static_cast<double>(this->posRangeMax->x());
    double factorHeight = static_cast<double>(this->paintFrame->height())/static_cast<double>(this->posRangeMax->y());
    this->paintFactor = factorWidth<factorHeight?factorWidth:factorHeight;
    this->transPosToLogic.setMatrix(1/this->paintFactor,0,0,0,1/this->paintFactor,0,0,0,1/this->paintFactor);
    qDebug()<<this->transPosToLogic;
//    this->paintFactor = 0.99;
}
void CutFileDraw::CutFileDraw_SetFactor(int _dir,bool _divEn)
{
    (_dir>0)?(_divEn?(paintFactor*=1.01):(paintFactor*=1.1)):(_divEn?(paintFactor/=1.01):(paintFactor/=1.1));
}
void CutFileDraw::CutFileDraw_DisplayFileData()
{
    QPainter painter(paintFrame);
    QPen pen(QColor(100,212,100),0);
    QPen penPaintLimit(QColor(255,255,0),0);
    QPen penPaintMax(QColor(255,0,0),0);
    QPen penCutLable(QColor(100,150,200),0);
    painter.setPen(pen);

    //----设置缩放和平移的量纲
    painter.scale(static_cast<qreal>(paintFactor),static_cast<qreal>(paintFactor));
    painter.translate(transPosToLogic.inverted().map(posFMouseMoved)/paintFactor);
    //----获取当前 控件坐标->刻度坐标的转换
    transPosToLogic = painter.combinedTransform().inverted();
    //当前像素点和数字逻辑点的坐标
    posLogic = painter.combinedTransform().inverted().map(posFWheel);
//    qDebug()<<posFWheel<<posLogic;

    //----绘制静态图
    painter.save();
    //----绘制机床最大尺寸和允许裁剪尺寸
    painter.setPen(penPaintMax);
    painter.drawRect(0,0,posRangeMax->x(),posRangeMax->y());
    painter.setPen(penPaintLimit);
    painter.drawRect(posLogicOrg->x(),posLogicOrg->y(),posRangeLimit->x()-posLogicOrg->x(),posRangeLimit->y()-posLogicOrg->y());
    //----绘制下刀
    QPointF paintCutLable[5]={QPointF(0*factorPulsePerMillimeter->x()+posLogicRealTime->x(),0*factorPulsePerMillimeter->y()+posLogicRealTime->y()),
                              QPointF(5*factorPulsePerMillimeter->x()+posLogicRealTime->x(),5*factorPulsePerMillimeter->y()+posLogicRealTime->y()),
                              QPointF(20*factorPulsePerMillimeter->x()+posLogicRealTime->x(),5*factorPulsePerMillimeter->y()+posLogicRealTime->y()),
                              QPointF(20*factorPulsePerMillimeter->x()+posLogicRealTime->x(),-5*factorPulsePerMillimeter->y()+posLogicRealTime->y()),
                              QPointF(5*factorPulsePerMillimeter->x()+posLogicRealTime->x(),-5*factorPulsePerMillimeter->y()+posLogicRealTime->y())};

    painter.setBrush(QBrush(Qt::green));
    painter.setPen(penCutLable);
    painter.drawPolygon(paintCutLable,5);
    painter.restore();
    //----绘制样片
    if(!fileContent->isEmpty())
    {
        painter.setPen(pen);
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
                            painter.drawLine(static_cast<int>(fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster.at(l-1).x()/1000*factorPulsePerMillimeter->x()+posLogicOrg->x()),
                                             static_cast<int>(fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster.at(l-1).y()/1000*factorPulsePerMillimeter->y()+posLogicOrg->y()),
                                             static_cast<int>(fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster.at(l).x()  /1000*factorPulsePerMillimeter->x()+posLogicOrg->x()),
                                             static_cast<int>(fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster.at(l).y()  /1000*factorPulsePerMillimeter->y()+posLogicOrg->y()));
                        }
                    }
                }
                for(int punchCnt = 0;punchCnt<fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).punchDotCount;punchCnt++)
                {
                    QPointF center = QPointF(fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).punchCluster.at(punchCnt).dot.x()/1000*factorPulsePerMillimeter->x(),
                                             fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).punchCluster.at(punchCnt).dot.y()/1000*factorPulsePerMillimeter->y())
                                    +*posLogicOrg;
                    QLineF line;
//                    painter.drawEllipse(center,2*factorPulsePerMillimeter->x(),2*factorPulsePerMillimeter->y());
                    line.setPoints(center,QPointF(center.x()+5*factorPulsePerMillimeter->x(),center.y()));
                    line.setAngle(-static_cast<qreal>(fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).punchCluster.at(punchCnt).dotAngle));
                    painter.drawLine(line);
                }
                for(int drillCnt = 0;drillCnt<fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).punchDotCount;drillCnt++)
                {
                    QPointF center = QPointF(fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).punchCluster.at(drillCnt).dot.x()/1000*factorPulsePerMillimeter->x(),
                                             fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).punchCluster.at(drillCnt).dot.y()/1000*factorPulsePerMillimeter->y())
                                     +*posLogicOrg;
                    painter.drawEllipse(center,3*factorPulsePerMillimeter->x(),3*factorPulsePerMillimeter->y());
                }
            }
        }
    }
}
//void CutFileDraw::CutFileDraw_DrawLine(QPointF q1,QPointF q2,QPointF fact,QPointF offset)
//{
//    painter.drawLine(static_cast<int>(q1.x()/1000*fact->x()+offset->x()),
//                     static_cast<int>(fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster.at(l-1).y()/1000*factorPulsePerMillimeter->y()+posLogicOrg->y()),
//                     static_cast<int>(fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster.at(l).x()  /1000*factorPulsePerMillimeter->x()+posLogicOrg->x()),
//                     static_cast<int>(fileContent->at(0).pageCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster.at(l).y()  /1000*factorPulsePerMillimeter->y()+posLogicOrg->y()));

//}

