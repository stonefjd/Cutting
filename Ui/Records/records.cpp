#include "records.h"

Records::Records(QObject *parent) : QObject(parent)
{
    recordsFileDir.append("/home");
}

void Records :: fileDir_Chose()
{
    QFileDialog *fileDialog = new QFileDialog;
    fileDialog->setWindowTitle(QTranslator::tr("打开刀路文件"));
//    fileDialog->setDirectory("/home/Debug");
    fileDialog->setNameFilter(QTranslator::tr("file(*.xml *.png)"));
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setViewMode(QFileDialog::Detail);

    fileDialog->exec();
    if(!fileDialog->selectedFiles().isEmpty())
        recordsFileDir = fileDialog->selectedFiles();

    qDebug()<<recordsFileDir;
}
QStringList Records :: fileDir_Get()
{
    return recordsFileDir;
}
