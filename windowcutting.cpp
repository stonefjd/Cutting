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
    //ui->menuSettings->setDisabled(true);
    //ui->menuViewItem->setDisabled(true);
    //ui->menuHelpItem->setDisabled(true);
//----设置菜单栏按钮的属性
//    QActionGroup *groupOprt = new QActionGroup(this);
    ui->actionBoundaryResize->setProperty("id","0");    //边界自校准
    ui->actionRangeScan->setProperty("id","1");         //裁剪边缘扫描
    ui->actionRangeReset->setProperty("id","2");        //裁剪边缘重设
    ui->actionToolDeepCalib->setProperty("id","3");     //校准刀深
    ui->actionToolPosCalib->setProperty("id","4");      //校准刀位
//    groupOprt->addAction(ui->actionBoundaryResize);
//    groupOprt->addAction(ui->actionRangeScan);
//    groupOprt->addAction(ui->actionRangeReset);
//    groupOprt->addAction(ui->actionToolDeepCalib);
//    groupOprt->addAction(ui->actionToolPosCalib);
//----status bar
    ui->statusBar->showMessage("ready");
//----new Handle, 不能改变顺序
    cutFileHandle   = new CutFileHandle(ui->dockWgtList,ui->mainPaint);
    cfgMachHandle   = new CfgMachHandle;
    handleCtrlMach  = new H_CtrlMach(ui->dockWgtCtrl);

    connect(cfgMachHandle,  SIGNAL(UpdateDataHead(CfgHead_T)),          cutFileHandle,  SLOT(SlotUpdateDataHead(CfgHead_T)));
    connect(cfgMachHandle,  SIGNAL(UpdateDataHead(CfgHead_T)),          handleCtrlMach, SLOT(SlotUpdateDataHead(CfgHead_T)));
    connect(cfgMachHandle,  SIGNAL(UpdateDataApron(QList<CfgApron_T>)), cutFileHandle,  SLOT(SlotUpdateDataApron(QList<CfgApron_T>)));
    connect(cutFileHandle,  SIGNAL(UpdateDataApronRequest()),           cfgMachHandle,  SLOT(SlotUpdateDataApronRequest()));
    connect(handleCtrlMach, SIGNAL(UpdateDataHeadPosRt(QPointF)),       cutFileHandle,  SLOT(SlotUpdateDataHeadPosRt(QPointF)));
    connect(this,           SIGNAL(keyPressed(QKeyEvent)),              handleCtrlMach, SLOT(SlotActionKeyBoard(QKeyEvent)));
    connect(this,           SIGNAL(keyReleased(QKeyEvent)),             handleCtrlMach, SLOT(SlotActionKeyBoard(QKeyEvent)));
    connect(handleCtrlMach, SIGNAL(UpdateDataHeadPosMax(QPointF)),      cfgMachHandle,  SLOT(SlotUpdateDataHeadPosMax(QPointF)));
    connect(ui->actionBoundaryResize,   SIGNAL(triggered()),            handleCtrlMach, SLOT(SlotActionOprt()));
    connect(ui->actionRangeScan,        SIGNAL(triggered()),            handleCtrlMach, SLOT(SlotActionOprt()));
    connect(ui->actionRangeReset,       SIGNAL(triggered()),            handleCtrlMach, SLOT(SlotActionOprt()));
    connect(ui->actionToolDeepCalib,    SIGNAL(triggered()),            handleCtrlMach, SLOT(SlotActionOprt()));
    connect(ui->actionToolPosCalib,     SIGNAL(triggered()),            handleCtrlMach, SLOT(SlotActionOprt()));
//    connect()
/*    //mMachine.mFan_1.StateMachineInit(ui->actionWindIn,ui->actionWindOut);
    mMachine->Mach_SetHead0Org(&cfgMachHandle->hConfig->posOrg);
    mMachine->Mach_SetHead0PulsePerMillimeter(&cfgMachHandle->hConfig->posToPulseScale);
    mMachine->Mach_SetHead0Limit(&cfgMachHandle->hConfig->posLimit);
    mMachine->Mach_SetHead0IdleMoveSpd(cfgMachHandle->hConfig->idleMoveSpd);
    mMachine->Mach_SetHead0IdleMoveAcc(cfgMachHandle->hConfig->idleMoveAcc);
    mMachine->fileData = cutFileHandle->GetFileData();


    connect(ui->btnDirGroup,    SIGNAL(buttonPressed(int)), mMachine,SLOT(SubStateOpBtnPress(int)));
    connect(ui->btnDirGroup,    SIGNAL(buttonReleased(int)),mMachine,SLOT(SubStateOpBtnRelease(int)));
    connect(ui->actionRunPuase, SIGNAL(triggered(bool)),    mMachine,SLOT(SubStateCutRunOrPause(bool)));
    connect(ui->actionStop,     SIGNAL(triggered()),        mMachine,SLOT(SubStateCutStop()));
    connect(ui->actionResize,   SIGNAL(triggered()),        mMachine,SLOT(SubStateOpBtnReSize()));
    connect(ui->actionEdgeScan, SIGNAL(triggered()),        mMachine,SLOT(SubStateOpBtnEdgeScan()));



*/
//----UserLog
    userHandle = nullptr;
    //disable all the operate item
    this->userLog_PermissionConfirm();
//----配置参数初始化，向其他模块传递配置参数
    cfgMachHandle->InitCommunicate();
//----启动控制模块定时器
    handleCtrlMach->StartCtrlTimer();
//----启动调试定时器
    debugTimer=new QTimer(this);
    connect(debugTimer,SIGNAL(timeout()),this,SLOT(debugTask_100ms()));//20ms
    debugTimer->start(20);
}

WindowCutting::~WindowCutting()
{
    delete ui;
    ADP_DisableALLAxis();
    qDebug()<<"deleted";
}
//----protected function
void WindowCutting::userLog_PermissionConfirm()
{
    QList<QWidget*> actionList;
//    actionList.append(ui->mainToolBar->findChildren<QWidget*>());
//    //actionList.append(ui->menuBar->findChildren<QWidget*>());
//    actionList.append(ui->dockWgtOperate->findChildren<QWidget*>());
//    actionList.append(ui->dockWgtList->findChildren<QWidget*>());

    if(userHandle == nullptr)
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
    if(!event->isAutoRepeat()&& (event->key() ==Qt::Key_A ||event->key() ==Qt::Key_D ||event->key() ==Qt::Key_W ||event->key() ==Qt::Key_S))
        emit keyPressed(*event);
}
void WindowCutting::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat()&& (event->key() ==Qt::Key_A ||event->key() ==Qt::Key_D ||event->key() ==Qt::Key_W ||event->key() ==Qt::Key_S))
        emit keyReleased(*event);
}
//-------------------signals and slots--------------------------
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

//--userLog
void WindowCutting::on_actionLogManager_triggered()
{
    userHandle->ShowManagerMent();
}

void WindowCutting::on_actionLogOn_triggered()
{
    if(userHandle == nullptr)
    {
        userHandle = new UserHandle;
        if(userHandle->GetUserChecked())
        {
            //add user manager action
            ui->menuUser->addAction(ui->actionLogManager);
            //change the user manager action
            ui->actionLogOn->setText(tr("退出"));

        }
        else
        {
            delete userHandle;
            userHandle = nullptr;
        }
    }
    else if(userHandle != nullptr)
    {
        QMessageBox msgBox;
        msgBox.setText(tr("是否确认退出"));
        QPushButton *btnYes = msgBox.addButton(tr("确认"), QMessageBox::YesRole);
        msgBox.addButton(tr("取消"), QMessageBox::NoRole);

        msgBox.exec();
        if(msgBox.clickedButton()== btnYes)
        {
            delete userHandle;
            userHandle = nullptr;
            ui->menuUser->removeAction(ui->actionLogManager);
            ui->actionLogOn->setText(tr("登录"));
        }
    }
    this->userLog_PermissionConfirm();
}
//----machine--fan
void WindowCutting::on_actionWindIn_triggered(bool arg1)
{
    (void)arg1;
//    if(arg1 == true)
//    {
//        //如果槽函数用toggled而不是triggered,则下面两句顺序不能反
//        if(ui->actionWindOut->isChecked())
//        {
//            ui->actionWindOut->setChecked(false);
//        }
//        mMachine->mFan_1.Fan_SetNormalState(FanWindIn);
//    }
//    else
//    {
//        qDebug()<<"fanStop";
//        mMachine->mFan_1.Fan_SetNormalState(FanStop);
//    }
//    ui->testLable->setText(QString::number(mMachine->mFan_1.Fan_GetState()));
}

void WindowCutting::on_actionWindOut_triggered(bool arg1)
{
    (void)arg1;
//    if(arg1 == true)
//    {
//        //trigger 代码触发后不会触发槽函数，toggle会
//        if(ui->actionWindIn->isChecked())
//        {
//            ui->actionWindIn->setChecked(false);
//        }
//        mMachine->mFan_1.Fan_SetNormalState(FanWindOut);
//    }
//    else
//    {
//        qDebug()<<"fanStop";
//        mMachine->mFan_1.Fan_SetNormalState(FanStop);
//    }
//    ui->testLable->setText(QString::number(mMachine->mFan_1.Fan_GetState()));
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
    long x=0,y=0;
    double xPos=0,yPos=0;
//    ADP_GetSts(1,&x);
//    ADP_GetSts(2,&y);
    ADP_GetAxisPrfPos(AXIS_X,&xPos);
    ADP_GetAxisPrfPos(AXIS_Y,&yPos);
    ui->lb_x->setText(QString::number(x));
    ui->lb_y->setText(QString::number(y));
//    ui->lb_st->setText(QString::number(mMachine->machine_ctSubState_Operate_Key));
    ui->lb_xPos->setText("x "+QString::number(xPos/cfgMachHandle->GetHConfig()->GetPosToPulseScaleXY()));
    ui->lb_yPos->setText("y "+QString::number(yPos/cfgMachHandle->GetHConfig()->GetPosToPulseScaleXY()));

    //    if(ctrlMachHandle->GetMachState() != stMain_Wait || ctrlMachHandle->GetAxisRunStateX()||ctrlMachHandle->GetAxisRunStateY())
//    if(ctrlMachHandle->GetAxisRunState(AXIS_X)||ctrlMachHandle->GetAxisRunState(AXIS_Y))
    {
        ui->mainPaint->update();
    }
}

void WindowCutting::on_dockWgtList_visibilityChanged(bool visible)
{
    ui->actionViewCutList->setChecked(visible);
}

void WindowCutting::on_actionViewCutList_triggered(bool checked)
{
    ui->dockWgtList->setVisible(checked);
}

void WindowCutting::on_actionMachSetting_triggered()
{
    cfgMachHandle->ShowMachSettings(userHandle);
}

void WindowCutting::on_actionKnifeSetting_triggered()
{
    cfgMachHandle->ShowKnifeManager(userHandle);
}
