#include "windowcutting.h"
#include "ui_windowcutting.h"
#pragma execution_character_set("utf-8")

WindowCutting::WindowCutting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowCutting)
{
    ui->setupUi(this);
//----Initial the private variable
    this->setFocus();
//----disable the ui
    ui->menuSettings->setDisabled(true);
    ui->menuViewItem->setDisabled(true);
    ui->menuHelpItem->setDisabled(true);

//----set btn id for ui
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
    ui->tableWgtCutFile->setFocusPolicy(Qt::NoFocus);
    cutFileList.CutFileList_WidgetInit(ui->tableWgtCutFile);
    cutFileList.CutFileList_SetPosLogicOrg(&wConfig->hConfig.at(0)->headOrg);
    cutFileList.CutFileList_SetFactorCutScale(&wConfig->hConfig.at(0)->headCutScale);

//----CutFileDraw
    ui->paintFrame->setMouseTracking(false);
    ui->paintFrame->installEventFilter(this);
    ui->paintFrame->setFocusPolicy(Qt::StrongFocus);
    cutFlieDraw.CutFileDraw_SetPaintFrame(ui->paintFrame);
    cutFlieDraw.CutFileDraw_SetPaintContent(&cutFileList.fileVector);
    cutFlieDraw.CutFileDraw_SetRangePage(&wConfig->hConfig.at(0)->headLimit);
    cutFlieDraw.CutFileDraw_SetRangeMax(&wConfig->hConfig.at(0)->headMaxLength);
    cutFlieDraw.CutFileDraw_SetPaintFactorPulsePerMillimeter(&wConfig->hConfig.at(0)->headPluseScale);
    cutFlieDraw.CutFileDraw_SetPaintLogicOrg(&wConfig->hConfig.at(0)->headOrg);
    cutFlieDraw.CutFileDraw_SetFactorCutScale(&wConfig->hConfig.at(0)->headCutScale);
    cutFlieDraw.CutFileDraw_SetPaintLogicRealTime(&mMachine->head0_Pos,&mMachine->head0_MoveAngel);
//----Machine Init
    //mMachine.mFan_1.StateMachineInit(ui->actionWindIn,ui->actionWindOut);
    mMachine->Mach_SetHead0Org(&wConfig->hConfig.at(0)->headOrg);
    mMachine->Mach_SetHead0PulsePerMillimeter(&wConfig->hConfig.at(0)->headPluseScale);
    mMachine->Mach_SetHead0Limit(&wConfig->hConfig.at(0)->headLimit);
    mMachine->Mach_SetHead0IdleMoveSpd(&wConfig->hConfig.at(0)->idleMoveSpd);
    mMachine->Mach_SetHead0IdleMoveAcc(&wConfig->hConfig.at(0)->idleMoveAcc);
    mMachine->Mach_SetCutContent(&cutFileList.fileVector);

    connect(this,SIGNAL(keyPressed(QKeyEvent)), mMachine,SLOT(SubStateOpKeyPress(QKeyEvent)));
    connect(this,SIGNAL(keyReleased(QKeyEvent)),mMachine,SLOT(SubStateOpKeyRelease(QKeyEvent)));
    connect(ui->btnDirGroup,    SIGNAL(buttonPressed(int)), mMachine,SLOT(SubStateOpBtnPress(int)));
    connect(ui->btnDirGroup,    SIGNAL(buttonReleased(int)),mMachine,SLOT(SubStateOpBtnRelease(int)));
    connect(ui->actionRunPuase, SIGNAL(triggered(bool)),    mMachine,SLOT(SubStateCutRunOrPause(bool)));
    connect(ui->actionStop,     SIGNAL(triggered()),        mMachine,SLOT(SubStateCutStop()));
    connect(ui->actionResize,   SIGNAL(triggered()),        mMachine,SLOT(SubStateOpBtnReSize()));
    connect(ui->actionEdgeScan, SIGNAL(triggered()),        mMachine,SLOT(SubStateOpBtnEdgeScan()));

    connect(mMachine,           SIGNAL(UpdateMachineMaxPluse(double,double)),wConfig,SLOT(UpdateConfigMaxPluse(double,double)));

//----UserLog
    user = nullptr;
    //disable all the operate item
    this->userLog_PermissionConfirm();

//----Start debug timer
    debugTimer=new QTimer(this);
    connect(debugTimer,SIGNAL(timeout()),this,SLOT(debugTask_100ms()));
    debugTimer->start(20);
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
            ui->paintFrame->update();
        }
        if(e->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *eventMouse = static_cast<QMouseEvent*>(e);
            cutFlieDraw.CutFileDraw_SetPosFMousePressed(eventMouse->localPos());
        }
        if(e->type() == QEvent::MouseButtonRelease)
        {
            cutFlieDraw.CutFileDraw_SetPosFMouseReleased();
        }
        if(e->type() == QEvent::MouseButtonDblClick)
        {
//            QMouseEvent *eventMouse = static_cast<QMouseEvent*>(e);
            cutFlieDraw.CutFileDraw_SetSizeFixed();
            ui->paintFrame->repaint();
        }
    }
//    if(e->type() == QEvent::KeyPress)
//    {
//        QKeyEvent *eventKey = static_cast<QKeyEvent*>(e);
//        emit keyPressed(*eventKey);
//    }
//    if(e->type() == QEvent::KeyRelease)
//    {
//        QKeyEvent *eventKey = static_cast<QKeyEvent*>(e);
//        emit keyReleased(*eventKey);
//    }
    return QMainWindow::eventFilter(watched,e);
}

WindowCutting::~WindowCutting()
{
    delete ui;
    qDebug()<<"deleted";
}
//----protected function
void WindowCutting::userLog_PermissionConfirm()
{
    QList<QWidget*> actionList;
    actionList.append(ui->mainToolBar->findChildren<QWidget*>());
    actionList.append(ui->menuBar->findChildren<QWidget*>());
    actionList.append(ui->dockWgtOperate->findChildren<QWidget*>());
    actionList.append(ui->dockWgtCutFile->findChildren<QWidget*>());

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
    emit keyPressed(*event);
}
void WindowCutting::keyReleaseEvent(QKeyEvent *event)
{
    emit keyReleased(*event);
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
    if(cutFileList.fileVector[0].windowCluster[0].sampleCluster[0].lineCluster[0].dotCount!=0)
    {
        for(int i=0;i<cutFileList.fileVector[0].windowCluster[0].sampleCluster[0].lineCluster[0].dotCount;i++)
        {
            sRtn = GT_LnXY(    1,    // 该插补段的坐标系是坐标系1
                               static_cast<long>(cutFileList.fileVector[0].windowCluster[0].sampleCluster[0].lineCluster[0].pointCluster[i].x()*107),
                               static_cast<long>(cutFileList.fileVector[0].windowCluster[0].sampleCluster[0].lineCluster[0].pointCluster[i].y()*107),  // 该插补段的终点坐标(15000, 15000)
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
        qDebug()<<"run:"<<run<<" seg:"<<segment;
    }while(run == 1);
}
void WindowCutting::on_pushButton_2_clicked()
{
}
void WindowCutting::on_pushButton_3_clicked()
{
}
void WindowCutting::on_pushButton_4_clicked()
{
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
void WindowCutting::on_actionLogManager_triggered()
{
    user->ShowManagerMent();
}

void WindowCutting::on_actionLogOn_triggered()
{
    if(user == nullptr)
    {
        user = new UserHandle;
        if(user->GetUserChecked())
        {
            //add user manager action
            ui->menuUser->addAction(ui->actionLogManager);
            //change the user manager action
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
        msgBox.addButton(tr("取消"), QMessageBox::NoRole);

        msgBox.exec();
        if(msgBox.clickedButton()== btnYes)
        {
            delete user;
            user = nullptr;
            ui->menuUser->removeAction(ui->actionLogManager);
            ui->actionLogOn->setText(tr("登录"));
        }
    }
    this->userLog_PermissionConfirm();
}
//--machine--fan
void WindowCutting::on_actionWindIn_triggered(bool arg1)
{
    if(arg1 == true)
    {
        //如果槽函数用toggled而不是triggered,则下面两句顺序不能反
        if(ui->actionWindOut->isChecked())
        {
            ui->actionWindOut->setChecked(false);
        }
        mMachine->mFan_1.Fan_SetNormalState(FanWindIn);
    }
    else
    {
        qDebug()<<"fanStop";
        mMachine->mFan_1.Fan_SetNormalState(FanStop);
    }
    ui->testLable->setText(QString::number(mMachine->mFan_1.Fan_GetState()));
}

void WindowCutting::on_actionWindOut_triggered(bool arg1)
{
    if(arg1 == true)
    {
        //trigger 代码触发后不会触发槽函数，toggle会
        if(ui->actionWindIn->isChecked())
        {
            ui->actionWindIn->setChecked(false);
        }
        mMachine->mFan_1.Fan_SetNormalState(FanWindOut);
    }
    else
    {
        qDebug()<<"fanStop";
        mMachine->mFan_1.Fan_SetNormalState(FanStop);
    }
    ui->testLable->setText(QString::number(mMachine->mFan_1.Fan_GetState()));
}
//just for change the icon display
void WindowCutting::on_actionStop_triggered()
{
    if(ui->actionRunPuase->isChecked())
    {
        //no actionRunPuase signal sent
        ui->actionRunPuase->setChecked(false);
    }
}
void WindowCutting::debugTask_100ms()
{
    long x,y;
    double xPos=0,yPos=0;
    ADP_GetSts(1,&x);
    ADP_GetSts(2,&y);
    ADP_GetAxisPrfPos(AXIS_X,&xPos);
    ADP_GetAxisPrfPos(AXIS_Y,&yPos);
    ui->lb_x->setText(QString::number(x));
    ui->lb_y->setText(QString::number(y));
//    ui->lb_st->setText(QString::number(mMachine->machine_ctSubState_Operate_Key));
    ui->lb_xPos->setText("x "+QString::number(static_cast<int>(xPos)));
    ui->lb_yPos->setText("y "+QString::number(static_cast<int>(yPos)));

    if(mMachine->GetMachineMainState() != stMain_Wait || mMachine->GetStateMotorRunningX()||mMachine->GetStateMotorRunningY())
    {
        ui->paintFrame->update();
    }
}
//void WindowCutting::messageBoxAutoRemove(QString _str)
//{
//    QMessageBox *msgBox = new QMessageBox;
//    msgBox->setText(_str);
//    QTimer::singleShot(500,msgBox,SLOT(accept()));
//    msgBox->exec();
//    delete msgBox;
//}


