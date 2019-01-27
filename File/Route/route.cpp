#include "route.h"

Route::Route(QObject *parent) : QObject(parent)
{
    PathDir.append("/home");
}
void Route::PathDir_Chose()
{
    QFileDialog *fileDialog = new QFileDialog;
    fileDialog->setWindowTitle(QTranslator::tr("打开刀路文件"));
//    fileDialog->setDirectory("/home/Debug");
    fileDialog->setNameFilter(QTranslator::tr("file(*.xml *.png)"));
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setViewMode(QFileDialog::Detail);

    fileDialog->exec();
    if(!fileDialog->selectedFiles().isEmpty())
        PathDir = fileDialog->selectedFiles();

    qDebug()<<PathDir;
}
QStringList Route::PathDir_Get()
{
    return PathDir;
}

