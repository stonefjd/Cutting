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
    QFileDialog *fileDialog = new QFileDialog;
    fileDialog->setWindowTitle(QTranslator::tr("打开刀路文件"));
//    fileDialog->setDirectory("/home/Debug");
    fileDialog->setNameFilter(QTranslator::tr("file(*.xml *.png)"));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::Detail);

    fileDialog->exec();
    if(!fileDialog->selectedFiles().isEmpty())
    {
        QStringList tempStrList;
        tempStrList = fileDialog->selectedFiles();
        for(int i=0;i<tempStrList.count();i++)
            filePathList.append("1 "+tempStrList.at(i));

    }
    qDebug()<<filePathList;
}
void CutFileListOp::CutFileList_ChoseList()
{
    //设置打开的界面
    QFileDialog *fileDialog = new QFileDialog;
    fileDialog->setWindowTitle(QTranslator::tr("裁切列表"));
//    fileDialog->setDirectory("/home/Debug");
    fileDialog->setNameFilter(QTranslator::tr("file(*.txt)"));
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setViewMode(QFileDialog::Detail);

    //打开文件获取切割任务列表文件
    fileDialog->exec();
    if(fileDialog->selectedFiles().isEmpty())
        return;
    //将被选择文件路径存入私有变量
    filePath = fileDialog->selectedFiles().at(0);

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
QString CutFileListOp::CutFile_Get()
{
    return filePath;
}
QStringList CutFileListOp::CutFileList_Get()
{
    return filePathList;
}
