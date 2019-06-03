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
void CutFileDraw::CutFileDraw_SetPaintLogicOrg(QPointF *_org)
{
    this->posLogicOrg = _org;
}
void CutFileDraw::CutFileDraw_SetFactorCutScale(QPointF *_scale)
{
    this->factorCutScale = _scale;
}
void CutFileDraw::CutFileDraw_SetPaintLogicRealTime(QPointF *_pos,double *_angle)
{
    this->posLogicRealTime = _pos;
    this->angleLogicRealTime = _angle;
}
void CutFileDraw::CutFileDraw_SetRangePage(QPointF *_rectRangePage)
{
    this->posRangeLimit = _rectRangePage;
}
void CutFileDraw::CutFileDraw_SetRangeMax(QPointF *_rectRangeMax)
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
    QPen penCutLable(QColor(0,255,0),0);
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
    painter.drawRect(QRectF(0.0,0.0,posRangeMax->x(), posRangeMax->y()));
//    painter.setFont(QFont("华文行楷", 30));
//    painter.drawText(QPointF(200,200), "你好123");
    painter.setPen(penPaintLimit);
    painter.drawRect(QRectF(posLogicOrg->x(),posLogicOrg->y(),posRangeLimit->x()-posLogicOrg->x(),posRangeLimit->y()-posLogicOrg->y()));
    //----绘制下刀+实际偏移补偿
    painter.setBrush(QColor(0,255,0,100));
    painter.setPen(penCutLable);
    QPointF offset(posLogicRealTime->x()/factorPulsePerMillimeter->x(),posLogicRealTime->y()/factorPulsePerMillimeter->y());
    QPointF paintCutLable[6]={QPointF( 0, 0)+offset,
                              QPointF( 5, 5)+offset,
                              QPointF(20, 5)+offset,
                              QPointF(20,-5)+offset,
                              QPointF( 5,-5)+offset,
                              QPointF( 0, 0)+offset};

//    QLineF line;
//    line.setPoints(QPointF(0, 0),
//                   QPointF(5, 5));
//    line.setAngle(*angleLogicRealTime+225);
//    painter.drawLine(line.translated(offset));
//    line.setPoints(QPointF(0, 0),
//                   QPointF(-5, -5));
//    line.setAngle(*angleLogicRealTime+135);
//    painter.drawLine(line.translated(offset));

    painter.drawPolygon(paintCutLable,5);
    painter.restore();
    //----绘制样片
    if(!fileContent->isEmpty())
    {
        painter.setPen(pen);
        painter.setRenderHint(QPainter::Antialiasing,true);

        for(int i= 0;i<fileContent->at(0).windowCluster.count();i++)
        {
            for(int j = 0;j<fileContent->at(0).windowCluster.at(i).sampleCluster.count();j++)
            {
                //Draw sample
                for(int k = 0;k<fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).lineCluster.count();k++)
                {
                    painter.save();
                    painter.setBrush(QColor(0,255,0,100));
                    painter.setPen(penCutLable);
                    QPolygonF tempPolygon(fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster);
                    //just one line
                    if(tempPolygon.first() != tempPolygon.last() || fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).isFinished == false)
                    {
                        painter.drawPolyline(QPolygonF(fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster));
                    }
                    else
                    {
                        painter.drawPolygon(QPolygonF(fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster));
                    }

//                    if(fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).isFinished == false)
//                    {
//                        painter.drawPolyline(QPolygonF(fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster));
//                    }
//                    else if(tempPolygon.first() == tempPolygon.last())
//                    {
//                        painter.drawPolygon(QPolygonF(fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster));
//                    }
//                    else
//                    {
//                        painter.drawPolyline(QPolygonF(fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster));
//                    }

//                    for(int l = 0;l<fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster.count();l++)
//                    {
//                        if(l >=1)
//                        {
//                            painter.drawLine(fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster.at(l-1)/HEX_PER_MM+*posLogicOrg,
//                                             fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster.at(l)  /HEX_PER_MM+*posLogicOrg);
//                        }
//                    }
                    painter.restore();
                }
                //尺寸与原点偏移补偿
                painter.setFont(QFont("华文行楷", 10));
                painter.drawText(fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).focusInSample, QString::number(fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).sampleId));
                //Vcut
                for(int punchCnt = 0;punchCnt<fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).punchDotCount;punchCnt++)
                {
                    QPointF center = fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).punchCluster.at(punchCnt).dot;
                    QLineF line;
                    line.setPoints(center,QPointF(center.x()+5*(factorCutScale->x()),center.y()));
                    line.setAngle(-static_cast<qreal>(fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).punchCluster.at(punchCnt).dotAngle));
                    painter.drawLine(line);
                }
                //Drill
                for(int drillCnt = 0;drillCnt<fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).punchDotCount;drillCnt++)
                {
                    QPointF center = fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).punchCluster.at(drillCnt).dot;
                    painter.drawEllipse(center,3*factorCutScale->x(),3*factorCutScale->y());
                }
            }
        }
    }
}
//void CutFileDraw::CutFileDraw_DrawLine(QPointF q1,QPointF q2,QPointF fact,QPointF offset)
//{
//    painter.drawLine(static_cast<int>(q1.x()/HEX_PER_MM*fact->x()+offset->x()),
//                     static_cast<int>(fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster.at(l-1).y()/HEX_PER_MM*factorPulsePerMillimeter->y()+posLogicOrg->y()),
//                     static_cast<int>(fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster.at(l).x()  /HEX_PER_MM*factorPulsePerMillimeter->x()+posLogicOrg->x()),
//                     static_cast<int>(fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).lineCluster.at(k).pointCluster.at(l).y()  /HEX_PER_MM*factorPulsePerMillimeter->y()+posLogicOrg->y()));

//}

