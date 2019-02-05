#include "cutfilelistop.h"

CutFileListOp::CutFileListOp(QObject *parent) : QObject(parent)
{

}
void CutFileListOp::CutFileList_WidgetInit(QTableWidget *_tableWidget)
{
    CutFileList_Display(_tableWidget);
}
void CutFileListOp::CutFileList_Display(QTableWidget *_tableWidget)
{
    if(!filePathList.isEmpty())
    {
        _tableWidget->setColumnCount(3);
        _tableWidget->setRowCount(filePathList.count());
    }
}
void CutFileListOp::CutFileList_ListAll(QString _path)
{

}

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
                    cnt++;
                    filePathList.insert(j, QString::number(cnt) +' '+ tempStrList.at(i));
                    filePathList.removeAt(j+1);
                    flagReplace = true;
                }
            }
        }
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
QString CutFileListOp::CutFileList_GetPath()
{
    return filePath;
}
QStringList CutFileListOp::CutFileList_GetList()
{
    return filePathList;
}
