#include "cutfile_ui.h"

CutFile_UI::CutFile_UI(QObject *parent) : QObject(parent)
{

}
void CutFile_UI::SetFileData(CutFile_Data *_fileData)
{
    this->cFileData = _fileData;
}
void CutFile_UI::InitEventFilter()
{
    qwFrame->installEventFilter(this);
}
void CutFile_UI::InitialModel(QDockWidget *_dockwgt, QFrame *_frame)
{
//----set the parameter
    this->qwDockWidget = _dockwgt;
    this->qwFrame = _frame;

//----table widget UI

    gridLayout->addWidget(qwBtnAddt, 0, 0, 1, 1);
    gridLayout->addWidget(qwBtnUpwd, 1, 0, 1, 1);
    gridLayout->addWidget(qwBtnImpt, 2, 0, 1, 1);
    gridLayout->addWidget(qwBtnRemv, 0, 1, 1, 1);
    gridLayout->addWidget(qwBtnDnwd, 1, 1, 1, 1);
    gridLayout->addWidget(qwBtnExpt, 2, 1, 1, 1);
    gridLayout->setSizeConstraint(QLayout::SetMinimumSize);

    //设置单框选中
    qwTableWait->setSelectionMode(QAbstractItemView::SingleSelection);
    qwTableFnsh->setSelectionMode(QAbstractItemView::SingleSelection);
    //设置选择内容为整行
    qwTableWait->setSelectionBehavior(QAbstractItemView::SelectRows);
    qwTableFnsh->setSelectionBehavior(QAbstractItemView::SelectRows);
    //隐藏列标题
    qwTableWait->verticalHeader()->setHidden(true);
    qwTableFnsh->verticalHeader()->setHidden(true);
    //隐藏行标题
    qwTableWait->horizontalHeader()->setHidden(true);
    qwTableFnsh->horizontalHeader()->setHidden(true);
    //设置无选中
    qwTableWait->setFocusPolicy(Qt::NoFocus);
    qwTableFnsh->setFocusPolicy(Qt::NoFocus);

//    qwTableWait->setFixedWidth(40);
//    qwTableFnsh->setFixedWidth(40);
//    qwTableWait->minimumWidth();
//    qwTableFnsh->minimumWidth();
//    qwTableWait->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Preferred);
//    qwTableFnsh->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Preferred);

    vLayout->addWidget(this->qwTableWait);
    vLayout->addWidget(this->qwTableFnsh);
    vLayout->addLayout(gridLayout);

    qwDockWidget->widget()->setLayout(vLayout);
    qwDockWidget->setFixedWidth(180);
    qwDockWidget->setWindowTitle("任务列表");
    qwDockWidget->resize(qwDockWidget->minimumSizeHint());
    qwDockWidget->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);//设置移动和浮动（不可关闭）
    connect(qwBtnAddt,SIGNAL(clicked()),this,SLOT(SlotBtnAddtClicked()));
    connect(qwBtnRemv,SIGNAL(clicked()),this,SLOT(SlotBtnRemvClicked()));
    connect(qwBtnUpwd,SIGNAL(clicked()),this,SLOT(SlotBtnUpwdClicked()));
    connect(qwBtnDnwd,SIGNAL(clicked()),this,SLOT(SlotBtnDnwdClicked()));
    connect(qwBtnImpt,SIGNAL(clicked()),this,SLOT(SlotBtnImptClicked()));
    connect(qwBtnExpt,SIGNAL(clicked()),this,SLOT(SlotBtnExptClicked()));

    connect(qwTableWait,SIGNAL(cellClicked(int,int)),this,SLOT(SlotCellClicked(int,int)));

    DisplayFileList(this->qwTableWait,this->cFileData->GetFileList());

//----frame UI
    qwFrame->setStyleSheet("background-color:rgb(50,50,50);");
    qwFrame->show();
    qwFrame->setMouseTracking(false);
//    qwFrame->setFocusPolicy(Qt::StrongFocus);

    paintFactor = 1;
    posFWheel.setX(0);
    posFWheel.setY(0);
    posFMousePressed.setX(0);
    posFMousePressed.setY(0);
    posFMouseMoved.setX(0);
    posFMouseMoved.setY(0);
}

//----event
bool CutFile_UI::eventFilter(QObject *watched, QEvent *e)
{
    if(watched == this->qwFrame)
    {
        if(e->type() == QEvent::Paint)
        {
            DrawFile(displayRow);
            DisplayFileList(this->qwTableWait,this->cFileData->GetFileList());
        }
        if(e->type() == QEvent::Wheel)
        {
            bool subDiv =false;
            QKeyEvent *eventKey = static_cast<QKeyEvent*>(e);
            //滚轮是否按住ctrl
            if(eventKey->modifiers() == Qt::ControlModifier)
            {
                subDiv = true;
            }
            //根据ctrl调节大小
            QWheelEvent *eventWheel = static_cast<QWheelEvent*>(e);
            posFWheel = eventWheel->pos();
            (eventWheel->delta()>0)?(subDiv?(paintFactor*=1.01):(paintFactor*=1.1)):(subDiv?(paintFactor/=1.01):(paintFactor/=1.1));
            qwFrame->repaint();
        }
        if(e->type() == QEvent::MouseMove)
        {
            QMouseEvent *eventMouse = static_cast<QMouseEvent*>(e);
            this->posFMouseMoved = (transPosToLogic.map(eventMouse->localPos())-posFMousePressed);
            qwFrame->update();
        }
        if(e->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *eventMouse = static_cast<QMouseEvent*>(e);
            this->posFMousePressed = transPosToLogic.map(eventMouse->localPos());
        }
        if(e->type() == QEvent::MouseButtonRelease)
        {
            this->posFMouseMoved = QPointF(0,0);
        }
        if(e->type() == QEvent::MouseButtonDblClick)
        {
            double factorWidth  = static_cast<double>(qwFrame->width() )/static_cast<double>(this->cFileData->GetPosMax()->x());
            double factorHeight = static_cast<double>(qwFrame->height())/static_cast<double>(this->cFileData->GetPosMax()->y());
            this->paintFactor = factorWidth<factorHeight?factorWidth:factorHeight;
            this->transPosToLogic.setMatrix(1/this->paintFactor,0,0,0,1/this->paintFactor,0,0,0,1/this->paintFactor);

            qwFrame->repaint();
        }
    }
    return true;
}
//----private
void CutFile_UI::DrawFile(int _fileIndex)
{
    QPainter painter(this->qwFrame);
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

    //----绘制静态图
    painter.save();
    //----绘制机床最大尺寸和允许裁剪尺寸
    painter.setPen(penPaintMax);
    painter.drawRect(QRectF(0.0,0.0,cFileData->GetPosMax()->x(), cFileData->GetPosMax()->y()));
//    painter.setFont(QFont("华文行楷", 30));
//    painter.drawText(QPointF(200,200), "你好123");
    painter.setPen(penPaintLimit);
    painter.drawRect(QRectF(cFileData->GetPosOrg()->x(),cFileData->GetPosOrg()->y(),
                            cFileData->GetPosLmt()->x()-cFileData->GetPosOrg()->x(),cFileData->GetPosLmt()->y()-cFileData->GetPosOrg()->y()));
    //----绘制下刀+实际偏移补偿
    painter.setBrush(QColor(0,255,0,100));
    painter.setPen(penCutLable);
    QPointF offset(cFileData->GetPosRt()->x(),
                   cFileData->GetPosRt()->y());
    QPointF paintCutLable[6]={QPointF( 0, 0)+offset,
                              QPointF( 5, 5)+offset,
                              QPointF(20, 5)+offset,
                              QPointF(20,-5)+offset,
                              QPointF( 5,-5)+offset,
                              QPointF( 0, 0)+offset};
    painter.drawPolygon(paintCutLable,5);
    painter.restore();

    if((!cFileData->GetFileList()->isEmpty()) && cFileData->GetFileList()->count()>_fileIndex)
    {
        painter.setPen(pen);
        painter.setRenderHint(QPainter::Antialiasing,true);

        CutFile *_file = cFileData->GetFileList()->at(_fileIndex);
        for(int i= 0;i<_file->GetPageList()->count();i++)
        {
            CutPage *_page = _file->GetPage(i);
            for(int j = 0;j<_page->GetSampleList()->count();j++)
            {
                CutSample *_sample = _page->GetSample(j);
                for(int k = 0;k<_sample->GetNormalLineList()->count();k++)
                {
                    painter.save();
                    painter.setBrush(QColor(0,255,0,100));
                    painter.setPen(penCutLable);
                    QPolygonF *tempPolygon(_sample->GetNormalLine(k)->GetPointList());
                    //just one line
                    if(tempPolygon->first() != tempPolygon->last() || !_sample->GetCutFinished())
                    {
                        painter.drawPolyline(*tempPolygon);
                    }
                    else
                    {
                        painter.drawPolygon(*tempPolygon);
                    }
                    painter.restore();
                }
                //尺寸与原点偏移补偿
                painter.setFont(QFont("华文行楷", 10));
                painter.drawText(_sample->GetPointGravity(), QString::number(j));
                //Vcut
//                for(int punchCnt = 0;punchCnt<fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).punchCluster.count();punchCnt++)
//                {
//                    QPointF center = fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).punchCluster.at(punchCnt).dot;
//                    QLineF line;
//                    line.setPoints(center,QPointF(center.x()+5*(factorCutScale->x()),center.y()));
//                    line.setAngle(-static_cast<qreal>(fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).punchCluster.at(punchCnt).dotAngle));
//                    painter.drawLine(line);
//                }
//                //Drill
//                for(int drillCnt = 0;drillCnt<fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).drillCluster.count();drillCnt++)
//                {
//                    QPointF center = fileContent->at(0).windowCluster.at(i).sampleCluster.at(j).drillCluster.at(drillCnt).dot;
//                    painter.drawEllipse(center,3*factorCutScale->x(),3*factorCutScale->y());
//                }
            }
        }
    }
}

void CutFile_UI::LoadFileData(CutFile *_file)
{
    QFile file(_file->GetFilePath());
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {

    }
    QString errorStr;
    int errorLine;
    int errorColumn;
    QDomDocument doc;
    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn))
    {
        qDebug()<<errorStr<<'\n'<<errorLine<<'\n'<<errorColumn;
        return;
    }
    QDomElement root = doc.documentElement();//content
    QDomNode node = root.firstChild();

    for(QDomNode p = node; !p.isNull(); p = p.nextSibling())
    {
        if(p.toElement().tagName()=="Page")
        {
            CutPage *page = new CutPage;
            _file->GetPageList()->append(page);
            for(QDomNode s = p.firstChild();!s.isNull();s = s.nextSibling())
            {
                if(s.toElement().tagName() == "PageLen")
                {
                    //过窗移动长度
                    page->SetPageLength(s.toElement().text().toFloat());
                }
                else if(s.toElement().tagName() == "Sample")
                {
                    CutSample *sample = new CutSample;
                    page->GetSampleList()->append(sample);
                    for(QDomNode l = s.firstChild();!l.isNull();l = l.nextSibling())
                    {
                        if(l.toElement().tagName() == "AirDraft")
                        {
                            QStringList _tempList = l.toElement().text().split(',');
                            QPointF _tl = QPointF(_tempList.at(0).toDouble(),_tempList.at(2).toDouble());
                            QPointF _br = QPointF(_tempList.at(1).toDouble(),_tempList.at(3).toDouble());
                            sample->SetInhaleSqare(QRectF(_tl,_br));
                        }
                        else if(l.toElement().tagName() == "Line")
                        {
                            CutLine *line = new CutLine;
                            sample->GetNormalLineList()->append(line);
                            for(QDomNode d = l.firstChild();!d.isNull();d=d.nextSibling())
                            {
                                if(d.toElement().tagName() == "Sp")
                                {
                                    line->SetKnifeGuid(d.toElement().text().toInt());
                                }
                                else if(d.toElement().tagName() == "Depth")
                                {
                                    line->SetDepth(d.toElement().text().toDouble());
                                }
                                else if(d.toElement().tagName() == "PtCoor")
                                {
                                    QStringList tempList = d.toElement().text().split(';');
                                    for(int i = 0;i<tempList.count()-1;i++)
                                    {
                                        QPointF dot;
                                        dot.setX(tempList.at(i).split(',').at(0).toDouble());
                                        dot.setY(tempList.at(i).split(',').at(1).toDouble());
                                        line->AddCutPoint(dot,0);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    file.close();

    //change to mm unit,change to scale and add org set
    for(int i=0;i<_file->GetPageList()->count();i++)
    {
        CutPage *_page = _file->GetPage(i);
        for(int j=0;j<_page->GetSampleList()->count();j++)
        {
            CutSample *_sample = _page->GetSample(j);
            for(int k=0;k<_sample->GetNormalLineList()->count();k++)
            {
                CutLine *_line = _sample->GetNormalLine(k);
                for(int l=0;l<_line->GetPointList()->count();l++)
                {
                    //step 01:set to mm unit
                    QPointF _tempPoint1 = _line->GetPointList()->at(l).toPoint()/HEX_PER_MM;
                    //step 02:set to scale step
                    QPointF _tempPoint2;
                    _tempPoint2.setX(_tempPoint1.x()*cFileData->GetRealToCutScale()->x());
                    _tempPoint2.setY(_tempPoint1.y()*cFileData->GetRealToCutScale()->y());
                    //step 03:add org offset
                    QPointF _tempPoint3;
                    _tempPoint3.setX(_tempPoint2.x() + cFileData->GetPosOrg()->x());
                    _tempPoint3.setY(_tempPoint2.y() + cFileData->GetPosOrg()->y());
                    _line->GetPointList()->replace(l, _tempPoint3);
                }
            }
//            for(int l=0;l<fileVector.at(i).windowCluster.at(j).sampleCluster.at(k).punchCluster.count();l++)
//            {
//                fileVector[i].windowCluster[j].sampleCluster[k].punchCluster[l].dot/=HEX_PER_MM;
//                fileVector[i].windowCluster[j].sampleCluster[k].punchCluster[l].dot.setX(
//                            fileVector[i].windowCluster[j].sampleCluster[k].punchCluster[l].dot.x()*factorCutScale->x());
//                fileVector[i].windowCluster[j].sampleCluster[k].punchCluster[l].dot.setY(
//                            fileVector[i].windowCluster[j].sampleCluster[k].punchCluster[l].dot.y()*factorCutScale->y());

//                fileVector[i].windowCluster[j].sampleCluster[k].punchCluster[l].dot.setX(
//                            fileVector[i].windowCluster[j].sampleCluster[k].punchCluster[l].dot.x() + posLogicOrg->x());
//                fileVector[i].windowCluster[j].sampleCluster[k].punchCluster[l].dot.setY(
//                            fileVector[i].windowCluster[j].sampleCluster[k].punchCluster[l].dot.y() + posLogicOrg->y());
//            }
//            for(int l=0;l<fileVector.at(i).windowCluster.at(j).sampleCluster.at(k).drillCluster.count();l++)
//            {
//                fileVector[i].windowCluster[j].sampleCluster[k].drillCluster[l].dot/=HEX_PER_MM;
//                fileVector[i].windowCluster[j].sampleCluster[k].drillCluster[l].dot.setX(
//                            fileVector[i].windowCluster[j].sampleCluster[k].drillCluster[l].dot.x()*factorCutScale->x());
//                fileVector[i].windowCluster[j].sampleCluster[k].drillCluster[l].dot.setY(
//                            fileVector[i].windowCluster[j].sampleCluster[k].drillCluster[l].dot.y()*factorCutScale->y());


//                fileVector[i].windowCluster[j].sampleCluster[k].drillCluster[l].dot.setX(
//                            fileVector[i].windowCluster[j].sampleCluster[k].drillCluster[l].dot.x() + posLogicOrg->x());
//                fileVector[i].windowCluster[j].sampleCluster[k].drillCluster[l].dot.setY(
//                            fileVector[i].windowCluster[j].sampleCluster[k].drillCluster[l].dot.y() + posLogicOrg->y());
//            }
        }
    }
    //set Sample Point
    for(int i=0;i<_file->GetPageList()->count();i++)
    {
        CutPage *_page = _file->GetPage(i);
        for(int j=0;j<_page->GetSampleList()->count();j++)
        {
            double area = 0;
            QPointF center;
            center.setX(0);
            center.setY(0);
            CutSample *_sample = _page->GetSample(j);
            for(int k=0;k<_sample->GetNormalLineList()->count();k++)
            {
                CutLine *_line = _sample->GetNormalLine(k);
                for(int m=0;m<_line->GetPointList()->count()-1;m++)
                {
                    QPointF tempThis = _line->GetPointList()->at(m);
                    QPointF tempNext = _line->GetPointList()->at(m+1);

                    area +=     (tempThis.x()*tempNext.y() - tempNext.x()*tempThis.y())/2;
                    center.setX(center.x() + (tempThis.x()*tempNext.y() - tempNext.x()*tempThis.y()) * (tempThis.x() + tempNext.x()));
                    center.setY(center.y() + (tempThis.x()*tempNext.y() - tempNext.x()*tempThis.y()) * (tempThis.y() + tempNext.y()));
                }
            }
            center.setX(center.x() / (6*area));
            center.setY(center.y() / (6*area));
            _sample->SetPointGravity(center);
        }
    }
}
void CutFile_UI::DisplayFileList(QTableWidget *_tableWidget, QList<CutFile*>* _fileList)
{
    if(!_fileList->isEmpty())
    {
        //以行为单位
        _tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        //设置列表格式
        _tableWidget->setColumnCount(3);
//        _tableWidget->setColumnWidth(0,50);
//        _tableWidget->setColumnWidth(1,50);
//        _tableWidget->setColumnWidth(2,300);
        _tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        _tableWidget->setRowCount(_fileList->count());

        _tableWidget->hideColumn(2);
        for(int i=0;i<_fileList->count();i++)
        {
            //设置尺寸
            _tableWidget->setRowHeight(i,15);

            //设置内容
            QSpinBox *spinBox = new QSpinBox();
            QTableWidgetItem *tableName = new QTableWidgetItem(_fileList->at(i)->GetFileName());
            QTableWidgetItem *tablePath = new QTableWidgetItem(_fileList->at(i)->GetFilePath());

            spinBox->setValue(_fileList->at(i)->GetCutTimes());
            spinBox->setRange(1,1000);
            spinBox->setProperty("index",QString::number(i));
            tableName->setFlags(tableName->flags() & (~Qt::ItemIsEditable));
            tablePath->setFlags(tablePath->flags() & (~Qt::ItemIsEditable));
            _tableWidget->setCellWidget(i, 1,spinBox);
            _tableWidget->setItem(i,0,tableName);
            _tableWidget->setItem(i,2,tablePath);
            connect(spinBox,SIGNAL(valueChanged(int)),this,SLOT(SlotChkBxSpin(int)));
        }
        if(_fileList->count() ==1 )
        {
            _tableWidget->setCurrentCell(0,QItemSelectionModel::Select);
        }
    }
    else
    {
        _tableWidget->clear();
        for(int i=0;i<_tableWidget->rowCount();i++)
        {

            _tableWidget->removeRow(0);
        }
    }
}

QStringList CutFile_UI::GetOpenFileList(QString _name,QString _filter,enum QFileDialog::FileMode _fileMode)
{
    QFileDialog *fileDialog = new QFileDialog;
    QStringList tempStrList;
    fileDialog->setWindowTitle(_name);
    fileDialog->setNameFilter(_filter);
    fileDialog->setFileMode(_fileMode);
    fileDialog->setViewMode(QFileDialog::Detail);

    fileDialog->exec();
    if(!fileDialog->selectedFiles().isEmpty())
    {

    }
    return  fileDialog->selectedFiles();
}
bool CutFile_UI::CheckFileRepeat(QString _filePath, QList<CutFile*>* _fileList)
{
    bool flagRepeated= false;
    QFileInfo fileinfoTemp(_filePath);
    for(int j=0;j<_fileList->count();j++)
    {
        QString pathNow = _fileList->at(j)->GetFilePath();
        QFileInfo fileinfoListIndex(pathNow);

        if(_fileList->at(j)->GetFileName() == fileinfoTemp.fileName() &&
                _fileList->at(j)->GetFilePath() == fileinfoTemp.filePath())
        {
            //只改变对应的次数，不增加新文件路径
            int times =  _fileList->at(j)->GetCutTimes();
            _fileList->at(j)->SetCutTimes(times+1);
            flagRepeated = true;
        }
    }
    return flagRepeated;
}
void CutFile_UI::AddFile(QString _filePath, QList<CutFile*>* _fileList)
{
    CutFile *fileData = new CutFile;
    QFileInfo fileinfo(_filePath);
    fileData->SetFileName(fileinfo.fileName());
    fileData->SetFilePath(fileinfo.filePath());
    fileData->SetCutTimes(1);
    _fileList->append(fileData);
}
void CutFile_UI::ImportFiles(QList<CutFile*>* _fileList)
{
    //打开文件获取切割任务列表文件
    QStringList tempStrList;
    tempStrList = GetOpenFileList(tr("裁切列表"),tr("file(*.txt)"),QFileDialog::ExistingFile);
    if(tempStrList.isEmpty())
    {
        return;
    }
    //清除文件结构内容
    QString filePath = tempStrList.at(0);
    //打开文件获取每个任务的文件路径
    QFile file(filePath);
    QFileInfo fileinfo(filePath);
    //判断列表文件是否存在
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    //读取文件列表
    while (!in.atEnd())
    {
        QString pathInFileList = in.readLine();
        //没有文档地址
        if(pathInFileList.split('|').count()<2)
        {
            QMessageBox msgBox;
            msgBox.setText(tr("列表内有文件不存在，损坏或者路径被修改"));
            msgBox.exec();
            return;
        }
        QFileInfo fileinfo(pathInFileList.split('|').at(1));
        //如果列表内的文件不存在则报错
        if(!fileinfo.isFile())
        {
            QMessageBox msgBox;
            msgBox.setText(tr("列表内文件不存在，损坏或者路径被修改"));
            msgBox.exec();
            return;
        }
    }
    _fileList->clear();
    in.seek(0);
    while(!in.atEnd())
    {
        QString pathInFileList = in.readLine();
        QFileInfo fileinfo(pathInFileList.split('|').at(1));
        CutFile *fileData = new CutFile;

        fileData->SetFileName(fileinfo.fileName());
        fileData->SetFilePath(fileinfo.filePath());
        fileData->SetCutTimes(1);

        fileData->SetCutTimes(pathInFileList.split('|').at(0).toInt());
        //将文件特性加载入文件容器中
        _fileList->append(fileData);
    }
    file.close();
    for(int i=0;i<_fileList->count();i++)
    {
        LoadFileData(_fileList->at(i));
    }
}
//----SLOTS
void CutFile_UI::SlotBtnAddtClicked()
{
    QStringList tempStrList;
    tempStrList = GetOpenFileList(tr("打开刀路文件"),tr("file(*.xml *.html)"),QFileDialog::ExistingFiles);
    if(tempStrList.isEmpty())
        return;
    for(int i=0;i<tempStrList.count();i++)
    {
        if(this->CheckFileRepeat(tempStrList.at(i),this->cFileData->GetFileList()) == false)
        {
            this->AddFile(tempStrList.at(i),this->cFileData->GetFileList());
            LoadFileData(this->cFileData->GetFileList()->last());
        }
    }
    this->DisplayFileList(this->qwTableWait,this->cFileData->GetFileList());
//    emit UpdateFileAdded();
    this->qwFrame->repaint();
}
void CutFile_UI::SlotBtnRemvClicked()
{
    qDebug()<<"R";
    int rowNow = this->qwTableWait->currentRow();
    if(this->cFileData->GetFileList()->count()>0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("确定移除该文件？"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes)
        {
            this->cFileData->GetFileList()->removeAt(rowNow);
        }
        if(displayRow>0)
        {
            displayRow--;
        }
    }
    this->DisplayFileList(this->qwTableWait,this->cFileData->GetFileList());
    this->qwFrame->repaint();
}
void CutFile_UI::SlotBtnUpwdClicked()
{
    int rowNow = qwTableWait->currentRow();
    if(rowNow>0)
    {
        this->cFileData->GetFileList()->move(rowNow,rowNow-1);
        qwTableWait->setCurrentCell(rowNow,QItemSelectionModel::Deselect);
        qwTableWait->setCurrentCell(rowNow-1,0,QItemSelectionModel::Select);
    }
    this->DisplayFileList(this->qwTableWait,this->cFileData->GetFileList());
    this->qwFrame->repaint();
}
void CutFile_UI::SlotBtnDnwdClicked()
{
    int rowNow = qwTableWait->currentRow();
    if(rowNow<(qwTableWait->rowCount()-1)&&rowNow>=0&&qwTableWait->rowCount()>1)
    {
        this->cFileData->GetFileList()->move(rowNow,rowNow+1);
        qwTableWait->setCurrentCell(rowNow,QItemSelectionModel::Deselect);
        qwTableWait->setCurrentCell(rowNow+1,0,QItemSelectionModel::Select);
    }
    this->DisplayFileList(this->qwTableWait,this->cFileData->GetFileList());
    this->qwFrame->repaint();
}
void CutFile_UI::SlotBtnImptClicked()
{
    this->ImportFiles(this->cFileData->GetFileList());
    this->DisplayFileList(this->qwTableWait,this->cFileData->GetFileList());
//    emit UpdateFileAdded();
    this->qwFrame->repaint();
}
void CutFile_UI::SlotBtnExptClicked()
{
    QString file_path = QFileDialog::getSaveFileName(qwTableWait,"请选择模板保存路径...","","*.txt;;");
    if(!file_path.isEmpty() && !this->cFileData->GetFileList()->isEmpty())
    {
        QFile file(file_path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        QTextStream in(&file);
        for(int i=0;i<this->cFileData->GetFileList()->count();i++)
        {
            in<<this->cFileData->GetFileList()->at(i)->GetCutTimes()<<'|'<<this->cFileData->GetFileList()->at(i)->GetFilePath()<<'\n';
        }
        file.close();
    }
    this->DisplayFileList(this->qwTableWait,this->cFileData->GetFileList());
}
void CutFile_UI::SlotChkBxSpin(int _cnt)
{
    QSpinBox *spinBox = qobject_cast<QSpinBox*>(sender());
    if(spinBox == nullptr)
    {
        return;
    }
    int index = spinBox->property("index").toInt();
    this->cFileData->GetFileList()->at(index)->SetCutTimes(_cnt);
}
void CutFile_UI::SlotCellClicked(int row, int column)
{
    (void)column;
    displayRow = row;
}
