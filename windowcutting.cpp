#include "windowcutting.h"
#include "ui_windowcutting.h"
#pragma execution_character_set("utf-8")

WindowCutting::WindowCutting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowCutting)
{
    ui->setupUi(this);
//----disable the ui
    ui->menuSettings->setDisabled(true);
    ui->menuViewItem->setDisabled(true);
    ui->menuHelpItem->setDisabled(true);


//----CutFileOperator
    ui->dockWgtCutFile->setWindowTitle(tr("任务列表"));
    ui->dockWgtCutFile->setMaximumWidth(200);
    cutFileList.CutFileList_WidgetInit(ui->tableWgtCutFile);

    ui->paintFrame->installEventFilter(this);
//----knifeConfig
    sdKnifeConfigLib.ReadConfigFile();
//----UserLog
    user = nullptr;
    this->userLog_PermissionConfirm();
//    user.exec();
}
bool WindowCutting::eventFilter(QObject *watched, QEvent *e)
{
    if(watched == ui->paintFrame && e->type() == QEvent::Paint)
    {
        cutFileList.CutFileList_DrawFileData(ui->paintFrame);
    }
    return true;
}

WindowCutting::~WindowCutting()
{
    delete ui;
}
//----protected function
void WindowCutting::userLog_PermissionConfirm()
{
    QList<QWidget*> actionList;
    actionList.append(ui->mainToolBar->findChildren<QWidget*>());
    actionList.append(ui->menuBar->findChildren<QWidget*>());
    if(user == nullptr)
    {
        for(int i = 0; i < actionList.size(); i++)
        {
            actionList.at(i)->setDisabled(true);
        }
        ui->menuUser->setEnabled(true);
    }
    else
    {
        for(int i = 0; i < actionList.size(); i++)
        {
            actionList.at(i)->setEnabled(true);
        }
    }
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
//-------------------signals and slots--------------------------
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

//--only for TEST
void WindowCutting::on_pushButton_clicked()
{
//    GT_SetDoBit(MC_GPO,0,0);
    this->update();
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

//--userLog
void WindowCutting::on_actionLogOn_triggered()
{
    if(user == nullptr)
    {
        user = new UserLog;
        if(user->userIsChecked())
        {
            ui->actionLogOn->setText(tr("退出"));
        }
        else
        {
            delete user;
            user = nullptr;
        }
    }
    else if(user != nullptr)
    {
        QMessageBox msgBox;
        msgBox.setText(tr("是否确认退出"));
        QPushButton *btnYes = msgBox.addButton(tr("确认"), QMessageBox::YesRole);
//        QPushButton *btnNo = msgBox.addButton(tr("取消"), QMessageBox::NoRole);
        msgBox.addButton(tr("取消"), QMessageBox::NoRole);

        msgBox.exec();
        if(msgBox.clickedButton()== btnYes)
        {
            delete user;
            user = nullptr;
            ui->actionLogOn->setText(tr("登录"));
        }
    }
    this->userLog_PermissionConfirm();
}
