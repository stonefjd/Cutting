#include "cutfilelistop.h"

CutFileListOp::CutFileListOp(QObject *parent) : QObject(parent)
{

}
void CutFileListOp::CutFileList_WidgetInit(QTableWidget *_tableWidget)
{
//    _tableWidget->setWindowTitle(tr("任务栏"));
    _tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    _tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    CutFileList_Display(_tableWidget);
}
void CutFileListOp::CutFileList_Display(QTableWidget *_tableWidget)
{
    if(!filePathList.isEmpty())
    {
        //以行为单位
        _tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        //设置列表格式
        _tableWidget->setColumnCount(3);
        _tableWidget->setColumnWidth(0,50);
        _tableWidget->setColumnWidth(1,50);
        _tableWidget->setColumnWidth(2,300);
        _tableWidget->setRowCount(filePathList.count());

        for(int i=0;i<filePathList.count();i++)
        {
            //设置尺寸
            _tableWidget->setRowHeight(i,15);
            //设置内容
            QSpinBox *spinBox = new QSpinBox();
            QTableWidgetItem *tableName = new QTableWidgetItem(CutFileList_GetColumnFileName(filePathList,i));
            QTableWidgetItem *tablePath = new QTableWidgetItem(CutFileList_GetColumnFilePath(filePathList,i));

            spinBox->setValue(CutFileList_GetColumnFileCounter(filePathList,i).toInt());
            spinBox->setProperty("index",QString::number(i));
            tableName->setFlags(tableName->flags() & (~Qt::ItemIsEditable));
            tablePath->setFlags(tablePath->flags() & (~Qt::ItemIsEditable));
            _tableWidget->setCellWidget(i, 1,spinBox);
            _tableWidget->setItem(i,0,tableName);
            _tableWidget->setItem(i,2,tablePath);
            connect(spinBox,SIGNAL(valueChanged(int)),this,SLOT(CutFileList_SpinBoxChg(int)));

        }
    }
}

void CutFileListOp::CutFileList_RemoveFileFromList(QTableWidget *_tableWidget)
{
    int rowNow = _tableWidget->currentRow();
    if(rowNow >= 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("提示"));
        msgBox.setText(tr("确定移除该文件？"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes)
        {
            filePathList.removeAt(rowNow);
        }
    }
//    qDebug()<<_tableWidget->currentRow();
}
void CutFileListOp::CutFileList_UpFileFromList(QTableWidget *_tableWidget)
{
    int rowNow = _tableWidget->currentRow();
    if(rowNow>0)
    {
        filePathList.move(rowNow,rowNow-1);
        _tableWidget->setCurrentCell(rowNow,QItemSelectionModel::Deselect);
        _tableWidget->setCurrentCell(rowNow-1,0,QItemSelectionModel::Select);
    }
}
void CutFileListOp::CutFileList_DownFileFromList(QTableWidget *_tableWidget)
{
    int rowNow = _tableWidget->currentRow();
    if(rowNow<_tableWidget->rowCount()-1)
    {
        filePathList.move(rowNow,rowNow+1);
        _tableWidget->setCurrentCell(rowNow,QItemSelectionModel::Deselect);
        _tableWidget->setCurrentCell(rowNow+1,0,QItemSelectionModel::Select);
    }
}
void CutFileListOp::CutFileList_ExportFileFromList(QTableWidget *_tableWidget)
{
    QString file_path = QFileDialog::getSaveFileName(_tableWidget,"请选择模板保存路径...","","*.txt;;");
    if(!file_path.isEmpty() && !filePathList.isEmpty())
    {
        QFile file(file_path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        QTextStream in(&file);
        for(int i=0;i<filePathList.count();i++)
        {
            in<<filePathList.at(i)<<'\n';
        }
        file.close();
    }

}
//打开单个文件
void CutFileListOp::CutFileList_ChoseSingleFile()
{
    QStringList tempStrList;
    tempStrList = CutFileList_ViewOpenFile(QTranslator::tr("打开刀路文件"),QTranslator::tr("file(*.xml *.png)"),QFileDialog::ExistingFiles);
    if(tempStrList.isEmpty())
        return;
    for(int i=0;i<tempStrList.count();i++)
    {
        bool flagReplace = false;
        if(filePathList.count()!=0)
        {
            QFileInfo fileinfoTemp(tempStrList.at(i));
            for(int j=0;j<filePathList.count();j++)
            {
                QString pathNow = filePathList.at(j).split(' ').at(1);
                int cnt = filePathList.at(j).split(' ').at(0).toInt();
                QFileInfo fileinfoListIndex(pathNow);

                if(fileinfoListIndex.fileName()==fileinfoTemp.fileName() &&
                        fileinfoListIndex.filePath()==fileinfoTemp.filePath())
                {
                    //只改变对应的次数，不增加新文件路径
                    cnt++;
                    filePathList.insert(j, QString::number(cnt) +' '+ tempStrList.at(i));
                    filePathList.removeAt(j+1);
                    flagReplace = true;
                }
            }
        }
        //增加新文件路径
        if(flagReplace == false)
        {
            filePathList.append("1 "+tempStrList.at(i));
        }
    }
    qDebug()<<tempStrList;
    qDebug()<<filePathList;
}
void CutFileListOp::CutFileList_ChoseList()
{
    //打开文件获取切割任务列表文件
    QStringList tempStrList;
    tempStrList = CutFileList_ViewOpenFile(QTranslator::tr("裁切列表"),QTranslator::tr("file(*.txt)"),QFileDialog::ExistingFile);//fileDialog->selectedFiles();
    if(tempStrList.isEmpty())
    {
        return;
    }

    //将被选择文件路径存入私有变量
    filePathList.clear();
    filePath = tempStrList.at(0);

    //打开文件获取每个任务的文件路径
    QFile file(filePath);
    QFileInfo fileinfo(filePath);
    //判断列表文件是否存在
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;
    QTextStream in(&file);
    //读取文件列表
    while (!in.atEnd())
    {
        QString pathInFileList = in.readLine();
        filePathList.append(pathInFileList);
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
    //添加文档路径到list
    qDebug()<<filePathList;
}

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
QString CutFileListOp::CutFileList_GetListPath()
{
    return filePath;
}
QStringList CutFileListOp::CutFileList_GetListContent()
{
    return filePathList;
}
QString CutFileListOp::CutFileList_GetColumnFileName(QStringList _fileList,int i)
{
    QFileInfo fileinfo(_fileList.at(i).split(' ').at(1));
    return fileinfo.fileName();
}
QString CutFileListOp::CutFileList_GetColumnFilePath(QStringList _fileList,int i)
{
    QFileInfo fileinfo(_fileList.at(i).split(' ').at(1));
    return fileinfo.filePath();
}
QString CutFileListOp::CutFileList_GetColumnFileCounter(QStringList _fileList,int i)
{
    return _fileList.at(i).split(' ').at(0);
}
void CutFileListOp::CutFileList_SetColumnFileCounter(QStringList *_fileList,int column,int counter)
{
    if(!(_fileList->count()>=column))
        return;
    QString tempStr = QString::number(counter) + ' ' + _fileList->at(column).split(' ').at(1);
    _fileList->removeAt(column);
    _fileList->insert(column,tempStr);

}

//-----slots
void CutFileListOp::CutFileList_SpinBoxChg(int i)
{
    QSpinBox *spinBox = qobject_cast<QSpinBox*>(sender());
    if(spinBox == nullptr)
    {
        return;
    }
    int index = spinBox->property("index").toInt();
    this->CutFileList_SetColumnFileCounter(&filePathList,index,i);
    qDebug()<<filePathList;
}
