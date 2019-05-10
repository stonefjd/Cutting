#include "windowcutting.h"
#include "ui_windowcutting.h"
#pragma execution_character_set("utf-8")

WindowCutting::WindowCutting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowCutting)
{
    ui->setupUi(this);
//----Initial the private variable

//----disable the ui
    ui->menuSettings->setDisabled(true);
    ui->menuViewItem->setDisabled(true);
    ui->menuHelpItem->setDisabled(true);

    ui->btnDirGroup->setId(ui->btnOpLeft,BTN_ID_L);
    ui->btnDirGroup->setId(ui->btnOpRight,BTN_ID_R);
    ui->btnDirGroup->setId(ui->btnOpUp,BTN_ID_U);
    ui->btnDirGroup->setId(ui->btnOpDown,BTN_ID_D);
    ui->btnDirGroup->setId(ui->btnOpOrg,BTN_ID_O);
//----status bar
    ui->statusBar->showMessage("ready");
//----CutFileOperator
    ui->dockWgtCutFile->setWindowTitle(tr("任务列表"));
    ui->dockWgtCutFile->setMaximumWidth(200);
    cutFileList.CutFileList_WidgetInit(ui->tableWgtCutFile);

//----CutFileDraw
    ui->paintFrame->setMouseTracking(false);
    ui->paintFrame->installEventFilter(this);
    cutFlieDraw.CutFileDraw_SetPaintFrame(ui->paintFrame);
    cutFlieDraw.CutFileDraw_SetPaintContent(&cutFileList.fileVector);
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
    if(watched == ui->paintFrame)
    {
        if(e->type() == QEvent::Paint)
        {
            cutFlieDraw.CutFileDraw_DisplayFileData();
        }
        if(e->type() == QEvent::Wheel)
        {
            bool subDiv =false;
            QKeyEvent *eventKey = static_cast<QKeyEvent*>(e);
            if(eventKey->modifiers() == Qt::ControlModifier)
            {
                subDiv = true;
            }
            QWheelEvent *eventWheel = static_cast<QWheelEvent*>(e);
            cutFlieDraw.CutFileDraw_SetPosFWheel(eventWheel->pos());
            cutFlieDraw.CutFileDraw_SetFactor(eventWheel->delta(),subDiv);
            ui->paintFrame->repaint();
        }
        if(e->type() == QEvent::MouseMove)
        {
            QMouseEvent *eventMouse = static_cast<QMouseEvent*>(e);
            cutFlieDraw.CutFileDraw_SetPosFMouseMoveDelta(eventMouse->localPos());
            ui->paintFrame->repaint();
        }
        if(e->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent *eventMouse = static_cast<QMouseEvent*>(e);
            cutFlieDraw.CutFileDraw_SetPosFMouseReleased(eventMouse->localPos());
        }
        if(e->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *eventMouse = static_cast<QMouseEvent*>(e);
            cutFlieDraw.CutFileDraw_SetPosFMousePressed(eventMouse->localPos());
        }
    }
    return QMainWindow::eventFilter(watched,e);
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
    short sRtn;
    sRtn = GT_ClrSts(1,8);

    sRtn = GT_AxisOn(AXIS_X);
    sRtn = GT_AxisOn(AXIS_Y);
    sRtn = GT_ZeroPos(AXIS_X);
    sRtn = GT_ZeroPos(AXIS_Y);
    sRtn = GT_SetPrfPos(AXIS_X, 0);
    sRtn = GT_SetPrfPos(AXIS_Y, 0);

    TCrdPrm crdPrm;
    memset(&crdPrm, 0, sizeof(crdPrm));
    crdPrm.dimension=2;   // 坐标系为二维坐标系
    crdPrm.synVelMax=50;  // 最大合成速度：500pulse/ms
    crdPrm.synAccMax=1;   // 最大加速度：1pulse/ms^2
    crdPrm.evenTime = 50;   // 最小匀速时间：50ms
    crdPrm.profile[0] = 1;   // 规划器1对应到X轴
    crdPrm.profile[1] = 2;   // 规划器2对应到Y轴
    crdPrm.setOriginFlag = 1;  // 表示需要指定坐标系的原点坐标的规划位置
    crdPrm.originPos[0] = 100;  // 坐标系的原点坐标的规划位置为（100, 100）
    crdPrm.originPos[1] = 100;
    sRtn = GT_SetCrdPrm(1, &crdPrm);

    // 指令返回值变量
    short run;  // 坐标系运动完成段查询变量
    long segment;  // 坐标系的缓存区剩余空间查询变量
    // 即将把数据存入坐标系1的FIFO0中，所以要首先清除此缓存区中的数据
    TCrdData crdData[500];
    GT_InitLookAhead(1, 0, 5, 1, 500, crdData);
    sRtn = GT_CrdClear(1, 0);
    // 向缓存区写入第一段插补数据
    if(cutFileList.fileVector[0].pageCluster[0].sampleCluster[0].lineCluster[0].dotCount!=0)
    {
        for(int i=0;i<cutFileList.fileVector[0].pageCluster[0].sampleCluster[0].lineCluster[0].dotCount!=0;i++)
        {
            sRtn = GT_LnXY(    1,    // 该插补段的坐标系是坐标系1
                               static_cast<long>(cutFileList.fileVector[0].pageCluster[0].sampleCluster[0].lineCluster[0].pointCluster[i].x()),
                               static_cast<long>(cutFileList.fileVector[0].pageCluster[0].sampleCluster[0].lineCluster[0].pointCluster[i].y()),  // 该插补段的终点坐标(15000, 15000)
                               20,    // 该插补段的目标速度：100pulse/ms
                               0.05,    // 插补段的加速度：0.1pulse/ms^2
                               0,    // 终点速度为0
                               0);    // 向坐标系1的FIFO0缓存区传递该直线插补数据
        }
    }
    GT_CrdData(1, nullptr, 0);
    sRtn = GT_CrdStart(1, 0);
    do
    {
        sRtn = GT_CrdStatus(     1,   // 坐标系是坐标系1
                                 &run,  // 读取插补运动状态
                                 &segment, // 读取当前已经完成的插补段数
                                 0);   // 查询坐标系1的FIFO0缓存区
    }while(run == 1);
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
    ui->paintFrame->repaint();
}
void WindowCutting::on_btnFileImport_clicked()
{
    cutFileList.CutFileList_ChoseList();
    cutFileList.CutFileList_DisplayList(ui->tableWgtCutFile);
    ui->paintFrame->repaint();
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
    ui->paintFrame->repaint();
}
void WindowCutting::on_btnFileDown_clicked()
{
    cutFileList.CutFileList_DownFileFromList(ui->tableWgtCutFile);
    cutFileList.CutFileList_DisplayList(ui->tableWgtCutFile);
    ui->paintFrame->repaint();
}
void WindowCutting::on_btnFileExport_clicked()
{
    cutFileList.CutFileList_ExportFileFromList(ui->tableWgtCutFile);
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

//void WindowCutting::messageBoxAutoRemove(QString _str)
//{
//    QMessageBox *msgBox = new QMessageBox;
//    msgBox->setText(_str);
//    QTimer::singleShot(500,msgBox,SLOT(accept()));
//    msgBox->exec();
//    delete msgBox;
//}
