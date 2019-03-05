#include "windowcutting.h"
#include "ui_windowcutting.h"
#pragma execution_character_set("utf-8")

WindowCutting::WindowCutting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowCutting)
{
    ui->setupUi(this);

//----CutFileOperator
    ui->dockWgtCutFile->setWindowTitle(tr("任务列表"));
    ui->dockWgtCutFile->setMaximumWidth(200);
    cutFileList.CutFileList_WidgetInit(ui->tableWgtCutFile);

    ui->paintFrame->installEventFilter(this);
//----
    //添加右键支持
    ui->tableWgtCutFile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWgtCutFile,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(CutFileContextMenuRKey(const QPoint&)));
}
bool WindowCutting::eventFilter(QObject *watched, QEvent *e)
{
    if(watched == ui->paintFrame && e->type() == QEvent::Paint)
    {
        QPainter painter(ui->paintFrame);
        QPen pen(QColor(50,212,50),0);
        painter.setPen(pen);
        painter.drawLine(QPointF(0,0),QPointF(100,200));
    }
    return true;
}

WindowCutting::~WindowCutting()
{
    delete ui;
}


void WindowCutting::CutFileAddList(QString _name,QString _path,unsigned int _counter)
{
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole,_name);
    item->setData(Qt::UserRole+1,_path);
    item->setData(Qt::UserRole+2,_counter);
//    ui->tableWgtCutFile->add;
}
void WindowCutting::CutFileContextMenuRKey(const QPoint& pt)
{
    //当选中项
    QTableWidgetItem* selected = ui->tableWgtCutFile->currentItem();

    QMenu menu;
    menu.addAction(ui->actionCutFileAdd);
    menu.addAction(ui->actionCutFileRmv);
    menu.addAction(ui->actionCutFileUp);
    menu.addAction(ui->actionCutFileDown);
    qDebug()<<pt;
    //显示菜单
    menu.exec(ui->tableWgtCutFile->mapToGlobal(pt));
}


//----override----//
void WindowCutting::keyPressEvent(QKeyEvent *event)
{
    //-------------shift key should be first
    if(event->modifiers() == Qt::ShiftModifier)
    {
        if(event->key() == Qt::Key_Left)
        {
            qDebug() << "Shift+left" ;
        }
        else if(event->key() == Qt::Key_Right)
        {
            qDebug() << "Shift+right" ;
        }
        else if(event->key() == Qt::Key_Up)
        {
            qDebug() << "Shift+Up" ;
        }
        else if(event->key() == Qt::Key_Down)
        {
            qDebug() << "Shift+Down" ;
        }
    }
    else
    {
        if(event->key() == Qt::Key_Left)
        {
            qDebug() << "left" ;
        }
        else if(event->key() == Qt::Key_Right)
        {
            qDebug() << "right" ;
        }
        else if(event->key() == Qt::Key_Up)
        {
            qDebug() << "Up" ;
        }
        else if(event->key() == Qt::Key_Down)
        {
            qDebug() << "Down" ;
        }
    }
}
//signals and slots
void WindowCutting::on_actionSettingsParameter_triggered()
{
//    this->settings.exec();
}

void WindowCutting::on_actionReset_triggered()
{
    QMessageBox msgBox;
    msgBox.setText(tr("请确认是否恢复出厂设置"));
    QPushButton *btnYes = msgBox.addButton(tr("确认"), QMessageBox::YesRole);
    QPushButton *btnNo = msgBox.addButton(tr("取消"), QMessageBox::NoRole);

    msgBox.exec();
    if(msgBox.clickedButton()== btnYes)
    {
//        settings.resetSettingsData();
        qDebug()<<"recover";
    }
    else if(msgBox.clickedButton()== btnNo)
    {

    }
}

//----------------TEST-----------------
void WindowCutting::on_pushButton_clicked()
{
//    GT_SetDoBit(MC_GPO,0,0);
}


void WindowCutting::on_pushButton_2_clicked()
{
//    this->mMachine.mFan_1.SetState_FanStop();
//    GT_SetDoBit(MC_GPO,0,1);
}

void WindowCutting::on_pushButton_3_clicked()
{
    this->mMachine.mFan_1.SetState_FanWindIn();
}

void WindowCutting::on_pushButton_4_clicked()
{
    this->mMachine.mFan_1.SetState_FanWindOut();
}






//--CutFileOperator
void WindowCutting::on_btnFileAdd_clicked()
{
    cutFileList.CutFileList_ChoseSingleFile();
    cutFileList.CutFileList_DisplayList(ui->tableWgtCutFile);
}
void WindowCutting::on_btnFileImport_clicked()
{
    cutFileList.CutFileList_ChoseList();
    cutFileList.CutFileList_DisplayList(ui->tableWgtCutFile);
}
void WindowCutting::on_actionImportCutFile_triggered()
{
    cutFileList.CutFileList_ChoseSingleFile();
    cutFileList.CutFileList_DisplayList(ui->tableWgtCutFile);
}
void WindowCutting::on_actionImportCutFileList_triggered()
{
    cutFileList.CutFileList_ChoseList();
    cutFileList.CutFileList_DisplayList(ui->tableWgtCutFile);
}
void WindowCutting::on_btnFileRmv_clicked()
{
    cutFileList.CutFileList_RemoveFileFromList(ui->tableWgtCutFile);
    cutFileList.CutFileList_DisplayList(ui->tableWgtCutFile);
}
void WindowCutting::on_btnFileUp_clicked()
{
    cutFileList.CutFileList_UpFileFromList(ui->tableWgtCutFile);
    cutFileList.CutFileList_DisplayList(ui->tableWgtCutFile);
}
void WindowCutting::on_btnFileDown_clicked()
{
    cutFileList.CutFileList_DownFileFromList(ui->tableWgtCutFile);
    cutFileList.CutFileList_DisplayList(ui->tableWgtCutFile);
}
void WindowCutting::on_btnFileExport_clicked()
{
    cutFileList.CutFileList_ExportFileFromList(ui->tableWgtCutFile);
}

