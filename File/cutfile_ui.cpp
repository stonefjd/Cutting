#include "cutfile_ui.h"

CutFile_UI::CutFile_UI(QObject *parent) : QObject(parent)
{
    this->qlcFileList->clear();
}
void CutFile_UI::SetFileList(QList<CutFile*>* _list)
{
    this->qlcFileList = _list;
}
void CutFile_UI::SetDockWidget(QDockWidget *_dockWidget)
{
    this->qwDockWidget = _dockWidget;
}
void CutFile_UI::SetPaintFrame(QFrame *_frame)
{
    this->qwFrame = _frame;
}
void CutFile_UI::InitialModel()
{
//----table widget
    gridLayout->addWidget(qwBtnAddt, 0, 0, 1, 1);
    gridLayout->addWidget(qwBtnUpwd, 0, 1, 1, 1);
    gridLayout->addWidget(qwBtnImpt, 0, 2, 1, 1);
    gridLayout->addWidget(qwBtnRemv, 1, 0, 1, 1);
    gridLayout->addWidget(qwBtnDnwd, 1, 1, 1, 1);
    gridLayout->addWidget(qwBtnExpt, 1, 2, 1, 1);


    vLayout->addWidget(this->qwTableWait);
    vLayout->addWidget(this->qwTableFnsh);
    vLayout->addLayout(gridLayout);

    qwDockWidget->widget()->setLayout(vLayout);
    qwDockWidget->setWindowTitle("任务列表");
    connect(qwBtnAddt,SIGNAL(clicked()),this,SLOT(SlotBtnAddtClicked()));
    connect(qwBtnRemv,SIGNAL(clicked()),this,SLOT(SlotBtnRemvClicked()));
    connect(qwBtnUpwd,SIGNAL(clicked()),this,SLOT(SlotBtnUpwdClicked()));
    connect(qwBtnDnwd,SIGNAL(clicked()),this,SLOT(SlotBtnDnwdClicked()));
    connect(qwBtnImpt,SIGNAL(clicked()),this,SLOT(SlotBtnImptClicked()));
    connect(qwBtnExpt,SIGNAL(clicked()),this,SLOT(SlotBtnExptClicked()));

    //设置单框选中
    qwTableWait->setSelectionMode(QAbstractItemView::SingleSelection);
    qwTableFnsh->setSelectionMode(QAbstractItemView::SingleSelection);
    //设置选择内容为整行
    qwTableWait->setSelectionBehavior(QAbstractItemView::SelectRows);
    qwTableFnsh->setSelectionBehavior(QAbstractItemView::SelectRows);
    //隐藏行列标题
    qwTableWait->verticalHeader()->setHidden(true);
    qwTableWait->horizontalHeader()->setHidden(true);
    qwTableFnsh->verticalHeader()->setHidden(true);
    qwTableFnsh->horizontalHeader()->setHidden(true);

    DisplayFileList(this->qwTableWait,this->qlcFileList);

//----frame
    qwFrame->installEventFilter(this);
}
//----event
bool CutFile_UI::eventFilter(QObject *watched, QEvent *e)
{
    if(watched == this->qwFrame)
    {
        if(e->type() == QEvent::Paint)
        {
            DrawFile();
        }
    }
    return true;
}
//----private
void CutFile_UI::DrawFile()
{
    QPainter painter(this->qwFrame);
    QPen pen(QColor(100,212,100),0);
    QPen penPaintLimit(QColor(255,255,0),0);
    QPen penPaintMax(QColor(255,0,0),0);
    QPen penCutLable(QColor(0,255,0),0);
    painter.setPen(pen);

    painter.drawRect(QRectF(10.0,10.0,100.0, 100.0));
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
        if(this->CheckFileRepeat(tempStrList.at(i),this->qlcFileList) == false)
        {
            this->AddFile(tempStrList.at(i),this->qlcFileList);
            LoadFileData(this->qlcFileList->last());
        }
    }
    this->DisplayFileList(this->qwTableWait,this->qlcFileList);
}
void CutFile_UI::SlotBtnRemvClicked()
{
    qDebug()<<"R";
    int rowNow = this->qwTableWait->currentRow();
    if(this->qlcFileList->count()>0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("确定移除该文件？"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes)
        {
            this->qlcFileList->removeAt(rowNow);
        }
    }
    this->DisplayFileList(this->qwTableWait,this->qlcFileList);
}
void CutFile_UI::SlotBtnUpwdClicked()
{
    int rowNow = qwTableWait->currentRow();
    if(rowNow>0)
    {
        qlcFileList->move(rowNow,rowNow-1);
        qwTableWait->setCurrentCell(rowNow,QItemSelectionModel::Deselect);
        qwTableWait->setCurrentCell(rowNow-1,0,QItemSelectionModel::Select);
    }
    this->DisplayFileList(this->qwTableWait,this->qlcFileList);
}
void CutFile_UI::SlotBtnDnwdClicked()
{
    int rowNow = qwTableWait->currentRow();
    if(rowNow<(qwTableWait->rowCount()-1)&&rowNow>=0&&qwTableWait->rowCount()>1)
    {
        qlcFileList->move(rowNow,rowNow+1);
        qwTableWait->setCurrentCell(rowNow,QItemSelectionModel::Deselect);
        qwTableWait->setCurrentCell(rowNow+1,0,QItemSelectionModel::Select);
    }
    this->DisplayFileList(this->qwTableWait,this->qlcFileList);
}
void CutFile_UI::SlotBtnImptClicked()
{
    this->ImportFiles(this->qlcFileList);
    this->DisplayFileList(this->qwTableWait,this->qlcFileList);
}
void CutFile_UI::SlotBtnExptClicked()
{
    QString file_path = QFileDialog::getSaveFileName(qwTableWait,"请选择模板保存路径...","","*.txt;;");
    if(!file_path.isEmpty() && !qlcFileList->isEmpty())
    {
        QFile file(file_path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        QTextStream in(&file);
        for(int i=0;i<qlcFileList->count();i++)
        {
            in<<qlcFileList->at(i)->GetCutTimes()<<'|'<<qlcFileList->at(i)->GetFilePath()<<'\n';
        }
        file.close();
    }
    this->DisplayFileList(this->qwTableWait,this->qlcFileList);
}
void CutFile_UI::SlotChkBxSpin(int _cnt)
{
    QSpinBox *spinBox = qobject_cast<QSpinBox*>(sender());
    if(spinBox == nullptr)
    {
        return;
    }
    int index = spinBox->property("index").toInt();
    this->qlcFileList->at(index)->SetCutTimes(_cnt);
}
