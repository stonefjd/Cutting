#include "cutfilelistop.h"

CutFileListOp::CutFileListOp(QObject *parent) : QObject(parent)
{

}
void CutFileListOp::CutFileList_WidgetInit(QTableWidget *_tableWidget)
{
    //设置单框选中
    _tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //设置选择内容为整行
    _tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    CutFileList_DisplayList(_tableWidget);
}
//--2019.03.01 修改FileVector数据结构,修改最后一个文件移除后的逻辑
void CutFileListOp::CutFileList_DisplayList(QTableWidget *_tableWidget)
{
    if(!fileVector.isEmpty())
    {
        //以行为单位
        _tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        //设置列表格式
        _tableWidget->setColumnCount(3);
        _tableWidget->setColumnWidth(0,50);
        _tableWidget->setColumnWidth(1,50);
        _tableWidget->setColumnWidth(2,300);
        _tableWidget->setRowCount(fileVector.count());

        for(int i=0;i<fileVector.count();i++)
        {
            //设置尺寸
            _tableWidget->setRowHeight(i,15);
            //设置内容
            QSpinBox *spinBox = new QSpinBox();
            QTableWidgetItem *tableName = new QTableWidgetItem(fileVector.at(i).cutFileName);
            QTableWidgetItem *tablePath = new QTableWidgetItem(fileVector.at(i).cutFilePath);

            spinBox->setValue(fileVector.at(i).cutCount);
            spinBox->setProperty("index",QString::number(i));
            tableName->setFlags(tableName->flags() & (~Qt::ItemIsEditable));
            tablePath->setFlags(tablePath->flags() & (~Qt::ItemIsEditable));
            _tableWidget->setCellWidget(i, 1,spinBox);
            _tableWidget->setItem(i,0,tableName);
            _tableWidget->setItem(i,2,tablePath);
            connect(spinBox,SIGNAL(valueChanged(int)),this,SLOT(CutFileList_SpinBoxChg(int)));
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
//--2019.03.01 FileVictor,修改BUG最后一个文件无法移除
void CutFileListOp::CutFileList_RemoveFileFromList(QTableWidget *_tableWidget)
{
    int rowNow = _tableWidget->currentRow();
    qDebug()<<rowNow;
    if(fileVector.count()>0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("确定移除该文件？"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes)
        {
            fileVector.removeAt(rowNow);
        }
    }
}
void CutFileListOp::CutFileList_UpFileFromList(QTableWidget *_tableWidget)
{
    int rowNow = _tableWidget->currentRow();
    if(rowNow>0)
    {
        fileVector.move(rowNow,rowNow-1);
        _tableWidget->setCurrentCell(rowNow,QItemSelectionModel::Deselect);
        _tableWidget->setCurrentCell(rowNow-1,0,QItemSelectionModel::Select);
    }
}
void CutFileListOp::CutFileList_DownFileFromList(QTableWidget *_tableWidget)
{
    int rowNow = _tableWidget->currentRow();
    if(rowNow<_tableWidget->rowCount()-1)
    {
        fileVector.move(rowNow,rowNow+1);
        _tableWidget->setCurrentCell(rowNow,QItemSelectionModel::Deselect);
        _tableWidget->setCurrentCell(rowNow+1,0,QItemSelectionModel::Select);
    }
}
void CutFileListOp::CutFileList_ExportFileFromList(QTableWidget *_tableWidget)
{
    QString file_path = QFileDialog::getSaveFileName(_tableWidget,"请选择模板保存路径...","","*.txt;;");
    if(!file_path.isEmpty() && !fileVector.isEmpty())
    {
        QFile file(file_path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        QTextStream in(&file);
        for(int i=0;i<fileVector.count();i++)
        {
            in<<fileVector.at(i).cutCount<<' '<<fileVector.at(i).cutFilePath<<'\n';
        }
        file.close();
    }
}
//导入单个裁切文件
void CutFileListOp::CutFileList_ChoseSingleFile()
{
    QStringList tempStrList;
    tempStrList = CutFileList_ViewOpenFile(QTranslator::tr("打开刀路文件"),QTranslator::tr("file(*.xml *.png)"),QFileDialog::ExistingFiles);
    if(tempStrList.isEmpty())
        return;
    for(int i=0;i<tempStrList.count();i++)
    {
        bool flagReplace = false;
        if(fileVector.count()!=0)
        {
            QFileInfo fileinfoTemp(tempStrList.at(i));
            for(int j=0;j<fileVector.count();j++)
            {
                QString pathNow = fileVector.at(j).cutFilePath;
                QFileInfo fileinfoListIndex(pathNow);

                if(fileVector.at(j).cutFileName == fileinfoTemp.fileName() &&
                        fileVector.at(j).cutFilePath == fileinfoTemp.filePath())
                {
                    //只改变对应的次数，不增加新文件路径
                    fileVector[j].cutCount++;
                    flagReplace = true;
                }
            }
        }
        //增加新文件路径
        if(flagReplace == false)
        {
            fileData_t fileData;
            QFileInfo fileinfo(tempStrList.at(i));
            fileData.cutFileName = fileinfo.fileName();
            fileData.cutFilePath = fileinfo.filePath();
            fileData.cutCount = 1;
            fileVector.insert(fileVector.end(),fileData);
            CutFileList_LoadCutData(fileVector.count()-1);
        }
    }
//    CutFileList_PrintVector(fileVector);

}
//--2019.03.01导入文件列表
void CutFileListOp::CutFileList_ChoseList()
{
    //打开文件获取切割任务列表文件
    QStringList tempStrList;
    tempStrList = CutFileList_ViewOpenFile(QTranslator::tr("裁切列表"),QTranslator::tr("file(*.txt)"),QFileDialog::ExistingFile);//fileDialog->selectedFiles();
    if(tempStrList.isEmpty())
    {
        return;
    }
    //清除文件结构内容
    filePath = tempStrList.at(0);
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
        if(pathInFileList.split(' ').count()<2)
        {
            QMessageBox msgBox;
            msgBox.setText(tr("列表内有文件不存在，损坏或者路径被修改"));
            msgBox.exec();
            return;
        }
        QFileInfo fileinfo(pathInFileList.split(' ').at(1));
        //如果列表内的文件不存在则报错
        if(!fileinfo.isFile())
        {
            QMessageBox msgBox;
            msgBox.setText(tr("列表内文件不存在，损坏或者路径被修改"));
            msgBox.exec();
            return;
        }
    }
    fileVector.clear();
    in.seek(0);
    while(!in.atEnd())
    {
        QString pathInFileList = in.readLine();
        QFileInfo fileinfo(pathInFileList.split(' ').at(1));
        fileData_t fileData;
        fileData.cutFileName = fileinfo.fileName();
        fileData.cutFilePath = fileinfo.filePath();
        fileData.cutCount = pathInFileList.split(' ').at(0).toInt();
        //将文件特性加载入文件容器中
        fileVector.insert(fileVector.end(),fileData);
    }
    file.close();
    for(int i=0;i<fileVector.count();i++)
    {
        CutFileList_LoadCutData(i);
    }
}


QString CutFileListOp::CutFileList_GetListPath()
{
    return filePath;
}

void CutFileListOp::CutFileList_DrawFileData(QFrame *_ptFrame)
{
    QPainter painter(_ptFrame);
    QPen pen(QColor(100,212,100),0);

    painter.setViewport(0,0,150,150);
    painter.setWindow(0,0,150,150);
    painter.setPen(pen);
    if(!fileVector.isEmpty())
    {
        for(int i= 0;i<fileVector.at(0).windowCluster.count();i++)
        {
            for(int j = 0;j<fileVector.at(0).windowCluster.at(i).sampleCluster.count();j++)
            {
                for(int k = 0;k<fileVector.at(0).windowCluster.at(i).sampleCluster.at(j).lineCluster.count();k++)
                {
                    for(int l = 0;l<fileVector.at(0).windowCluster.at(i).sampleCluster.at(j).lineCluster.at(k).dotCluster.count();l++)
                    {
                        if(fileVector.at(0).windowCluster.at(i).sampleCluster.at(j).lineCluster.at(k).lineType==0 && l >=1)
                        {
                            painter.drawLine(fileVector.at(0).windowCluster.at(i).sampleCluster.at(j).lineCluster.at(k).dotCluster.at(l-1).dotOrg,
                                             fileVector.at(0).windowCluster.at(i).sampleCluster.at(j).lineCluster.at(k).dotCluster.at(l).dotOrg);
                        }
                        else if(fileVector.at(0).windowCluster.at(i).sampleCluster.at(j).lineCluster.at(k).lineType==1)
                        {
                            painter.drawEllipse(fileVector.at(0).windowCluster.at(i).sampleCluster.at(j).lineCluster.at(k).dotCluster.at(l).dotOrg,
                                                2,2);
                        }
                    }
                }
            }
        }
    }
}

//--槽函数
//2019.03.01修改内容
void CutFileListOp::CutFileList_SpinBoxChg(int i)
{
    QSpinBox *spinBox = qobject_cast<QSpinBox*>(sender());
    if(spinBox == nullptr)
    {
        return;
    }
    int index = spinBox->property("index").toInt();
    fileVector[index].cutCount = i;
}

//--私有成员函数
//--2019.03.01 设为私有函数
QStringList CutFileListOp::CutFileList_ViewOpenFile(QString _name,QString _filter,enum QFileDialog::FileMode _fileMode)
{
    QFileDialog *fileDialog = new QFileDialog;
    QStringList tempStrList;
    fileDialog->setWindowTitle(_name);
//    fileDialog->setDirectory("/home/Debug");
    fileDialog->setNameFilter(_filter);
    fileDialog->setFileMode(_fileMode);
    fileDialog->setViewMode(QFileDialog::Detail);

    fileDialog->exec();
    if(!fileDialog->selectedFiles().isEmpty())
    {

    }
    return  fileDialog->selectedFiles();
}
//--2019.03.01 添加
void CutFileListOp::CutFileList_PrintVector(QList<fileData_t> _fileVector)
{
    for(int i = 0;i<_fileVector.count();i++)
    {
        qDebug()<<_fileVector.at(i).cutFileName;
        qDebug()<<_fileVector.at(i).cutFilePath;
        qDebug()<<_fileVector.at(i).cutCount;
    }
    qDebug()<<_fileVector[0].windowCluster[0].sampleCluster[0].lineCluster[0].dotCluster[0].dotId;
    qDebug()<<_fileVector[0].windowCluster[0].sampleCluster[0].lineCluster[0].dotCluster[1].dotId;
    qDebug()<<_fileVector[0].windowCluster[0].sampleCluster[0].lineCluster[0].dotCluster[2].dotId;
    qDebug()<<_fileVector[0].windowCluster[0].sampleCluster[0].lineCluster[0].dotCluster[3].dotId;
}
//--2019.03.01 添加，载入XML裁切数据
void CutFileListOp::CutFileList_LoadCutData(int _fIdx)
{
    int fIdx = _fIdx;
    QFile file(fileVector[fIdx].cutFilePath);
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
    QDomNode node = root.firstChild().firstChild();


    int wIdx = 0;
    for(QDomNode w = node; !w.isNull(); w = w.nextSibling())
    {
        if(w.toElement().tagName()=="window")
        {
            windowData_t window;
            int sIdx = 0;
            fileVector[fIdx].windowCluster.append(window);
            for(QDomNode s = w.firstChild();!s.isNull();s = s.nextSibling())
            {
                if(s.toElement().tagName() == "wId")
                {
                    fileVector[fIdx].windowCluster[wIdx].windowId = s.toElement().text().toInt();
                }
                else if(s.toElement().tagName() == "length")
                {
                    //过窗移动长度
                    fileVector[fIdx].windowCluster[wIdx].windowLength = s.toElement().text().toFloat();
                }
                else if(s.toElement().tagName() == "sample")
                {
                    sampleData_t sample;
                    int lIdx = 0;
                    fileVector[fIdx].windowCluster[wIdx].sampleCluster.append(sample);
                    for(QDomNode l = s.firstChild();!l.isNull();l = l.nextSibling())
                    {
                        if(l.toElement().tagName() == "sId")
                        {
                            fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].sampleId = l.toElement().text().toInt();
                        }
                        else if(l.toElement().tagName() == "line")
                        {
                            lineData_t line;
                            int dIdx = 0;
                            fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCluster.append(line);
                            for(QDomNode d = l.firstChild();!d.isNull();d=d.nextSibling())
                            {

                                if(d.toElement().tagName() == "lId")
                                {
                                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCluster[lIdx].lineId = d.toElement().text().toInt();
                                }
                                else if(d.toElement().tagName() == "lType")
                                {
                                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCluster[lIdx].lineType = d.toElement().text().toInt();
                                }
                                else if(d.toElement().tagName() == "toolId")
                                {
                                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCluster[lIdx].toolId = d.toElement().text().toInt();
                                }
                                else if(d.toElement().tagName() == "height")
                                {
                                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCluster[lIdx].lineDeep = d.toElement().text().toFloat();
                                }
                                else if(d.toElement().tagName() == "dot")
                                {
                                    dotData_t dot;
                                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCluster[lIdx].dotCluster.append(dot);
                                    for(QDomNode min = d.firstChild();!min.isNull();min = min.nextSibling())
                                    {
                                        if(min.toElement().tagName() == "dId")
                                        {
                                            fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCluster[lIdx].dotCluster[dIdx].dotId = min.toElement().text().toInt();
                                        }
                                        else if(min.toElement().tagName() == "x")
                                        {
                                            fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCluster[lIdx].dotCluster[dIdx].dotOrg.setX(min.toElement().text().toDouble());
                                        }
                                        else if(min.toElement().tagName() == "y")
                                        {
                                            fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCluster[lIdx].dotCluster[dIdx].dotOrg.setY(min.toElement().text().toDouble());
                                        }
                                        else if(min.toElement().tagName() == "angle")
                                        {
                                            fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCluster[lIdx].dotCluster[dIdx].dotAngle = min.toElement().text().toFloat();
                                        }
                                    }
                                    dIdx++;
                                }
                            }
                            fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCluster[lIdx].dotCount = dIdx;
                            lIdx++;
                        }
                    }
                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCount =lIdx;
                    sIdx++;
                }
            }
            fileVector[fIdx].windowCluster[wIdx].sampleCount = sIdx;
            wIdx++;
        }
    }
    fileVector[fIdx].windowCount = wIdx;

    file.close();
}
