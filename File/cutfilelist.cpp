#include "cutfilelist.h"

CutFileList::CutFileList(QObject *parent) : QObject(parent)
{

}
void CutFileList::CutFileList_WidgetInit(QTableWidget *_tableWidget)
{
    //设置单框选中
    _tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //设置选择内容为整行
    _tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    CutFileList_DisplayList(_tableWidget);
}
//--2019.03.01 修改FileVector数据结构,修改最后一个文件移除后的逻辑
void CutFileList::CutFileList_DisplayList(QTableWidget *_tableWidget)
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

            spinBox->setValue(fileVector.at(i).cutTimes);
            spinBox->setProperty("index",QString::number(i));
            tableName->setFlags(tableName->flags() & (~Qt::ItemIsEditable));
            tablePath->setFlags(tablePath->flags() & (~Qt::ItemIsEditable));
            _tableWidget->setCellWidget(i, 1,spinBox);
            _tableWidget->setItem(i,0,tableName);
            _tableWidget->setItem(i,2,tablePath);
            connect(spinBox,SIGNAL(valueChanged(int)),this,SLOT(CutFileList_SpinBoxChg(int)));
        }
        if(fileVector.count() ==1 )
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
//--2019.03.01 FileVictor,修改BUG最后一个文件无法移除
void CutFileList::CutFileList_RemoveFileFromList(QTableWidget *_tableWidget)
{
    int rowNow = _tableWidget->currentRow();
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
void CutFileList::CutFileList_UpFileFromList(QTableWidget *_tableWidget)
{
    int rowNow = _tableWidget->currentRow();
    if(rowNow>0)
    {
        fileVector.move(rowNow,rowNow-1);
        _tableWidget->setCurrentCell(rowNow,QItemSelectionModel::Deselect);
        _tableWidget->setCurrentCell(rowNow-1,0,QItemSelectionModel::Select);
    }
}
void CutFileList::CutFileList_DownFileFromList(QTableWidget *_tableWidget)
{
    int rowNow = _tableWidget->currentRow();
    if(rowNow<(_tableWidget->rowCount()-1)&&rowNow>=0&&_tableWidget->rowCount()>1)
    {
        fileVector.move(rowNow,rowNow+1);
        _tableWidget->setCurrentCell(rowNow,QItemSelectionModel::Deselect);
        _tableWidget->setCurrentCell(rowNow+1,0,QItemSelectionModel::Select);
    }
}
void CutFileList::CutFileList_ExportFileFromList(QTableWidget *_tableWidget)
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
            in<<fileVector.at(i).cutTimes<<'|'<<fileVector.at(i).cutFilePath<<'\n';
        }
        file.close();
    }
}
//导入单个裁切文件
void CutFileList::CutFileList_ChoseSingleFile()
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
                    fileVector[j].cutTimes++;
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
            fileData.cutTimes = 1;
            fileVector.insert(fileVector.end(),fileData);
            CutFileList_LoadCutData(fileVector.count()-1);
        }
    }
}
//--2019.03.01导入文件列表
void CutFileList::CutFileList_ChoseList()
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
    fileVector.clear();
    in.seek(0);
    while(!in.atEnd())
    {
        QString pathInFileList = in.readLine();
        QFileInfo fileinfo(pathInFileList.split('|').at(1));
        fileData_t fileData;
        fileData.cutFileName = fileinfo.fileName();
        fileData.cutFilePath = fileinfo.filePath();
        fileData.cutTimes = pathInFileList.split('|').at(0).toInt();
        //将文件特性加载入文件容器中
        fileVector.insert(fileVector.end(),fileData);
    }
    file.close();
    for(int i=0;i<fileVector.count();i++)
    {
        CutFileList_LoadCutData(i);
    }
}


QString CutFileList::CutFileList_GetListPath()
{
    return filePath;
}

void CutFileList::CutFileList_SetPosLogicOrg(QPointF *_org)
{
    this->posLogicOrg = _org;
}
void CutFileList::CutFileList_SetFactorCutScale(QPointF *_scale)
{
    this->factorCutScale = _scale;
}

//--槽函数
//2019.03.01修改内容
void CutFileList::CutFileList_SpinBoxChg(int i)
{
    QSpinBox *spinBox = qobject_cast<QSpinBox*>(sender());
    if(spinBox == nullptr)
    {
        return;
    }
    int index = spinBox->property("index").toInt();
    fileVector[index].cutTimes = i;
}

//--私有成员函数
//--2019.03.01 设为私有函数
QStringList CutFileList::CutFileList_ViewOpenFile(QString _name,QString _filter,enum QFileDialog::FileMode _fileMode)
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
void CutFileList::CutFileList_PrintVector(QList<fileData_t> _fileVector)
{
    for(int i = 0;i<_fileVector.count();i++)
    {
        qDebug()<<_fileVector.at(i).cutFileName;
        qDebug()<<_fileVector.at(i).cutFilePath;
        qDebug()<<_fileVector.at(i).cutTimes;
    }
}
//--2019.03.01 添加，载入XML裁切数据
void CutFileList::CutFileList_LoadCutData(int _fIdx)
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
    QDomNode node = root.firstChild();


    int wIdx = 0;
    for(QDomNode w = node; !w.isNull(); w = w.nextSibling())
    {
        if(w.toElement().tagName()=="Page")
        {
            pageData_t window;
            int sIdx = 0;
            fileVector[fIdx].windowCluster.append(window);
            for(QDomNode s = w.firstChild();!s.isNull();s = s.nextSibling())
            {
                if(s.toElement().tagName() == "PageId")
                {
                    fileVector[fIdx].windowCluster[wIdx].pageId = s.toElement().text().toInt();
                }
                else if(s.toElement().tagName() == "PageLen")
                {
                    //过窗移动长度
                    fileVector[fIdx].windowCluster[wIdx].pageLength = s.toElement().text().toFloat();
                }
                else if(s.toElement().tagName() == "Sample")
                {
                    sampleData_t sample;
                    int lIdx = 0;
                    int punchIdx = 0;
                    int drillIdx = 0;
                    fileVector[fIdx].windowCluster[wIdx].sampleCluster.append(sample);
                    for(QDomNode l = s.firstChild();!l.isNull();l = l.nextSibling())
                    {
                        if(l.toElement().tagName() == "SampleId")
                        {
                            fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].sampleId = l.toElement().text().toInt();
                        }
                        else if(l.toElement().tagName() == "Line")
                        {
                            lineData_t line;
                            int dIdx = 0;
                            fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCluster.append(line);
                            for(QDomNode d = l.firstChild();!d.isNull();d=d.nextSibling())
                            {
                                if(d.toElement().tagName() == "Id")
                                {
                                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCluster[lIdx].lineId = d.toElement().text().toInt();
                                }
                                else if(d.toElement().tagName() == "Sp")
                                {
                                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCluster[lIdx].toolId = d.toElement().text().toInt();
                                }
                                else if(d.toElement().tagName() == "Depth")
                                {
                                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCluster[lIdx].lineDeep = d.toElement().text().toFloat();
                                }
                                else if(d.toElement().tagName() == "PtCoor")
                                {
                                    long temp = d.toElement().text().split(';').count()-1;
                                    for(;dIdx<temp;dIdx++)
                                    {
                                        QPointF dot;
                                        fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCluster[lIdx].pointCluster.append(dot);
                                        fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCluster[lIdx].pointCluster[dIdx].setX(d.toElement().text().split(';').at(dIdx).split(',').at(0).toInt());
                                        fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCluster[lIdx].pointCluster[dIdx].setY(d.toElement().text().split(';').at(dIdx).split(',').at(1).toInt());
                                    }
                                }
                            }
//                            fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCluster[lIdx].dotCount = dIdx;
                            lIdx++;
                        }
                        else if(l.toElement().tagName() == "SPunch")
                        {
                            dotData_t baseDot;
                            fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].punchCluster.append(baseDot);
                            for(QDomNode d = l.firstChild();!d.isNull();d=d.nextSibling())
                            {
                                if(d.toElement().tagName() == "Id")
                                {
                                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].punchCluster[punchIdx].dotId = d.toElement().text().toInt();
                                }
                                else if(d.toElement().tagName() == "Sp")
                                {
                                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].punchCluster[punchIdx].toolId = d.toElement().text().toInt();
                                }
                                else if(d.toElement().tagName() == "Depth")
                                {
                                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].punchCluster[punchIdx].dotDeep = d.toElement().text().toFloat();
                                }
                                else if(d.toElement().tagName() == "Angle")
                                {
                                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].punchCluster[punchIdx].dotAngle = d.toElement().text().toFloat();
                                }
                                else if(d.toElement().tagName() == "PtCoor")
                                {
                                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].punchCluster[punchIdx].dot.setX(d.toElement().text().split(';').at(0).split(',').at(0).toInt());
                                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].punchCluster[punchIdx].dot.setY(d.toElement().text().split(';').at(0).split(',').at(1).toInt());
                                }
                            }
                            punchIdx++;
                        }
                        else if(l.toElement().tagName() == "Drill")
                        {
                            dotData_t baseDot;
                            fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].drillCluster.append(baseDot);
                            for(QDomNode d = l.firstChild();!d.isNull();d=d.nextSibling())
                            {
                                if(d.toElement().tagName() == "Id")
                                {
                                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].drillCluster[drillIdx].dotId = d.toElement().text().toInt();
                                }
                                else if(d.toElement().tagName() == "Sp")
                                {
                                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].drillCluster[drillIdx].toolId = d.toElement().text().toInt();
                                }
                                else if(d.toElement().tagName() == "Depth")
                                {
                                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].drillCluster[drillIdx].dotDeep = d.toElement().text().toFloat();
                                }
                                else if(d.toElement().tagName() == "Angle")
                                {
                                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].drillCluster[drillIdx].dotAngle = d.toElement().text().toFloat();
                                }
                                else if(d.toElement().tagName() == "PtCoor")
                                {
                                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].drillCluster[drillIdx].dot.setX(d.toElement().text().split(';').at(0).split(',').at(0).toInt());
                                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].drillCluster[drillIdx].dot.setY(d.toElement().text().split(';').at(0).split(',').at(1).toInt());
                                }
                            }
                            drillIdx++;
                        }
                    }
//                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].lineCount =lIdx;
//                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].punchDotCount =punchIdx;
//                    fileVector[fIdx].windowCluster[wIdx].sampleCluster[sIdx].drillDotCount =drillIdx;
                    sIdx++;
                }
            }
//            fileVector[fIdx].windowCluster[wIdx].sampleCount = sIdx;
            wIdx++;
        }
    }
    fileVector[fIdx].pageCount = wIdx;

    file.close();
    //change to mm unit,change to scale and add org set
    for(int i=0;i<fileVector.count();i++)
        for(int j=0;j<fileVector.at(i).windowCluster.count();j++)
            for(int k=0;k<fileVector.at(i).windowCluster.at(j).sampleCluster.count();k++)
            {
                for(int l=0;l<fileVector.at(i).windowCluster.at(j).sampleCluster.at(k).lineCluster.count();l++)
                    for(int m=0;m<fileVector.at(i).windowCluster.at(j).sampleCluster.at(k).lineCluster.at(l).pointCluster.count();m++)
                    {
                        //step 01:set to mm unit
                        fileVector[i].windowCluster[j].sampleCluster[k].lineCluster[l].pointCluster[m]/=HEX_PER_MM;
                        //step 02:set to scale step
                        fileVector[i].windowCluster[j].sampleCluster[k].lineCluster[l].pointCluster[m].setX(
                                    fileVector[i].windowCluster[j].sampleCluster[k].lineCluster[l].pointCluster[m].x()*factorCutScale->x());
                        fileVector[i].windowCluster[j].sampleCluster[k].lineCluster[l].pointCluster[m].setY(
                                    fileVector[i].windowCluster[j].sampleCluster[k].lineCluster[l].pointCluster[m].y()*factorCutScale->y());
                        //step 03:add org offset
                        fileVector[i].windowCluster[j].sampleCluster[k].lineCluster[l].pointCluster[m].setX(
                                    fileVector[i].windowCluster[j].sampleCluster[k].lineCluster[l].pointCluster[m].x() + posLogicOrg->x());
                        fileVector[i].windowCluster[j].sampleCluster[k].lineCluster[l].pointCluster[m].setY(
                                    fileVector[i].windowCluster[j].sampleCluster[k].lineCluster[l].pointCluster[m].y() + posLogicOrg->y());
                    }
                for(int l=0;l<fileVector.at(i).windowCluster.at(j).sampleCluster.at(k).punchCluster.count();l++)
                {
                    fileVector[i].windowCluster[j].sampleCluster[k].punchCluster[l].dot/=HEX_PER_MM;
                    fileVector[i].windowCluster[j].sampleCluster[k].punchCluster[l].dot.setX(
                                fileVector[i].windowCluster[j].sampleCluster[k].punchCluster[l].dot.x()*factorCutScale->x());
                    fileVector[i].windowCluster[j].sampleCluster[k].punchCluster[l].dot.setY(
                                fileVector[i].windowCluster[j].sampleCluster[k].punchCluster[l].dot.y()*factorCutScale->y());

                    fileVector[i].windowCluster[j].sampleCluster[k].punchCluster[l].dot.setX(
                                fileVector[i].windowCluster[j].sampleCluster[k].punchCluster[l].dot.x() + posLogicOrg->x());
                    fileVector[i].windowCluster[j].sampleCluster[k].punchCluster[l].dot.setY(
                                fileVector[i].windowCluster[j].sampleCluster[k].punchCluster[l].dot.y() + posLogicOrg->y());
                }
                for(int l=0;l<fileVector.at(i).windowCluster.at(j).sampleCluster.at(k).drillCluster.count();l++)
                {
                    fileVector[i].windowCluster[j].sampleCluster[k].drillCluster[l].dot/=HEX_PER_MM;
                    fileVector[i].windowCluster[j].sampleCluster[k].drillCluster[l].dot.setX(
                                fileVector[i].windowCluster[j].sampleCluster[k].drillCluster[l].dot.x()*factorCutScale->x());
                    fileVector[i].windowCluster[j].sampleCluster[k].drillCluster[l].dot.setY(
                                fileVector[i].windowCluster[j].sampleCluster[k].drillCluster[l].dot.y()*factorCutScale->y());


                    fileVector[i].windowCluster[j].sampleCluster[k].drillCluster[l].dot.setX(
                                fileVector[i].windowCluster[j].sampleCluster[k].drillCluster[l].dot.x() + posLogicOrg->x());
                    fileVector[i].windowCluster[j].sampleCluster[k].drillCluster[l].dot.setY(
                                fileVector[i].windowCluster[j].sampleCluster[k].drillCluster[l].dot.y() + posLogicOrg->y());
                }
            }


    //set Sample Point
    for(int i=0;i<fileVector.count();i++)
        for(int j=0;j<fileVector.at(i).windowCluster.count();j++)
            for(int k=0;k<fileVector.at(i).windowCluster.at(j).sampleCluster.count();k++)
            {
                double area = 0;
                QPointF center;
                center.setX(0);
                center.setY(0);
                for(int l=0;l<fileVector.at(i).windowCluster.at(j).sampleCluster.at(k).lineCluster.count();l++)
                {
                    for(int m=0;m<fileVector.at(i).windowCluster.at(j).sampleCluster.at(k).lineCluster.at(l).pointCluster.count()-1;m++)
                    {
                        QPointF tempThis = fileVector.at(i).windowCluster.at(j).sampleCluster.at(k).lineCluster.at(l).pointCluster.at(m);
                        QPointF tempNext = fileVector.at(i).windowCluster.at(j).sampleCluster.at(k).lineCluster.at(l).pointCluster.at(m+1);

                        area +=     (tempThis.x()*tempNext.y() - tempNext.x()*tempThis.y())/2;
                        center.setX(center.x() + (tempThis.x()*tempNext.y() - tempNext.x()*tempThis.y()) * (tempThis.x() + tempNext.x()));
                        center.setY(center.y() + (tempThis.x()*tempNext.y() - tempNext.x()*tempThis.y()) * (tempThis.y() + tempNext.y()));
                    }
                }
                center.setX(center.x() / (6*area));
                center.setY(center.y() / (6*area));
                fileVector[i].windowCluster[j].sampleCluster[k].focusInSample = center;
            }
    //set scale Factor
}