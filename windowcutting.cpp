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

    ui->btnDirGroup->setId(ui->btnOpLeft,BTN_ID_L);
    ui->btnDirGroup->setId(ui->btnOpRight,BTN_ID_R);
    ui->btnDirGroup->setId(ui->btnOpUp,BTN_ID_U);
    ui->btnDirGroup->setId(ui->btnOpDown,BTN_ID_D);
    ui->btnDirGroup->setId(ui->btnOpOrg,BTN_ID_O);
//----CutFileOperator
    ui->dockWgtCutFile->setWindowTitle(tr("任务列表"));
    ui->dockWgtCutFile->setMaximumWidth(200);
    cutFileList.CutFileList_WidgetInit(ui->tableWgtCutFile);

    ui->paintFrame->installEventFilter(this);
//----Machine Init
    //mMachine.mFan_1.StateMachineInit(ui->actionWindIn,ui->actionWindOut);
    mMachine = new Machine;
    connect(ui->btnDirGroup,SIGNAL(buttonPressed(int)),mMachine,SLOT(SubStateOpBtnPress(int)));
    connect(ui->btnDirGroup,SIGNAL(buttonReleased(int)),mMachine,SLOT(SubStateOpBtnRelease(int)));
    connect(this,SIGNAL(keyPressed(QKeyEvent)),mMachine,SLOT(SubStateOpKeyPress(QKeyEvent)));
    connect(this,SIGNAL(keyReleased(QKeyEvent)),mMachine,SLOT(SubStateOpKeyRelease(QKeyEvent)));
    connect(ui->actionSizeCalibration,SIGNAL(triggered()),mMachine,SLOT(SubStateOpBtnScanBoard()));


//----UserLog
    user = nullptr;
    this->userLog_PermissionConfirm();
//    user.exec();

    debugTimer=new QTimer(this);
    connect(debugTimer,SIGNAL(timeout()),this,SLOT(debugTask_10ms()));
    debugTimer->start(10);
}
void WindowCutting::debugTask_10ms()
{
    long x,y;
    double xPos=0,yPos=0;
    ADP_GetSts(1,&x);
    ADP_GetSts(2,&y);
    ADP_GetAxisPrfPos(AXIS_X,&xPos);
    ADP_GetAxisPrfPos(AXIS_Y,&yPos);
    ui->lb_x->setText(QString::number(x));
    ui->lb_y->setText(QString::number(y));
    ui->lb_st->setText(QString::number(mMachine->machine_ctSubState_Operate_Key));
    ui->lb_xPos->setText("x "+QString::number(static_cast<int>(xPos)));
    ui->lb_yPos->setText("y "+QString::number(static_cast<int>(yPos)));
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
//    actionList.append(ui->dockWgtOperate->findChildren<QWidget*>());
//    actionList.append(ui->dockWgtCutFile->findChildren<QWidget*>());

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
void WindowCutting::keyReleaseEvent(QKeyEvent *event)
{
    emit keyReleased(*event);
}
void WindowCutting::keyPressEvent(QKeyEvent *event)
{
    emit keyPressed(*event);
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
//    this->mMachine.mFan_1.SetState_FanWindIn();
}
void WindowCutting::on_pushButton_4_clicked()
{
//    this->mMachine.mFan_1.SetState_FanWindOut();
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
//--machine--fan
void WindowCutting::on_actionWindIn_toggled(bool arg1)
{
    if(arg1 == true)
    {
        //下面两句顺序不能反
        ui->actionWindOut->setChecked(false);
        mMachine->mFan_1.Fan_SetNormalState(FanWindIn);
    }
    else
    {
        mMachine->mFan_1.Fan_SetNormalState(FanStop);
    }
    ui->testLable->setText(QString::number(mMachine->mFan_1.Fan_GetState()));
}

void WindowCutting::on_actionWindOut_toggled(bool arg1)
{
    if(arg1 == true)
    {
        //下面两句顺序不能反
        ui->actionWindIn->setChecked(false);
        mMachine->mFan_1.Fan_SetNormalState(FanWindOut);
    }
    else
    {
        mMachine->mFan_1.Fan_SetNormalState(FanStop);
    }
    ui->testLable->setText(QString::number(mMachine->mFan_1.Fan_GetState()));
}
