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

//----set btn id for ui
    ui->btnDirGroup->setId(ui->btnOpLeft,BTN_ID_L);
    ui->btnDirGroup->setId(ui->btnOpRight,BTN_ID_R);
    ui->btnDirGroup->setId(ui->btnOpUp,BTN_ID_U);
    ui->btnDirGroup->setId(ui->btnOpDown,BTN_ID_D);
    ui->btnDirGroup->setId(ui->btnOpOrg,BTN_ID_O);
//----status bar
    ui->statusBar->showMessage("ready");
//----new Handle,shouldn't change the order
    cutFileHandle = new CutFileHandle(ui->dockWgtList,ui->mainPaint);
    cfgMachHandle = new CfgMachHandle;
//----Machine Init
    //mMachine.mFan_1.StateMachineInit(ui->actionWindIn,ui->actionWindOut);
    mMachine->Mach_SetHead0Org(&cfgMachHandle->hConfig->posOrg);
    mMachine->Mach_SetHead0PulsePerMillimeter(&cfgMachHandle->hConfig->posToPulseScale);
    mMachine->Mach_SetHead0Limit(&cfgMachHandle->hConfig->posLimit);
    mMachine->Mach_SetHead0IdleMoveSpd(cfgMachHandle->hConfig->idleMoveSpd);
    mMachine->Mach_SetHead0IdleMoveAcc(cfgMachHandle->hConfig->idleMoveAcc);
//    mMachine->Mach_SetCutContent(&cutFileList.fileVector);

    connect(this,SIGNAL(keyPressed(QKeyEvent)), mMachine,SLOT(SubStateOpKeyPress(QKeyEvent)));
    connect(this,SIGNAL(keyReleased(QKeyEvent)),mMachine,SLOT(SubStateOpKeyRelease(QKeyEvent)));
    connect(ui->btnDirGroup,    SIGNAL(buttonPressed(int)), mMachine,SLOT(SubStateOpBtnPress(int)));
    connect(ui->btnDirGroup,    SIGNAL(buttonReleased(int)),mMachine,SLOT(SubStateOpBtnRelease(int)));
    connect(ui->actionRunPuase, SIGNAL(triggered(bool)),    mMachine,SLOT(SubStateCutRunOrPause(bool)));
    connect(ui->actionStop,     SIGNAL(triggered()),        mMachine,SLOT(SubStateCutStop()));
    connect(ui->actionResize,   SIGNAL(triggered()),        mMachine,SLOT(SubStateOpBtnReSize()));
    connect(ui->actionEdgeScan, SIGNAL(triggered()),        mMachine,SLOT(SubStateOpBtnEdgeScan()));

    connect(mMachine,           SIGNAL(UpdateMachineMaxPluse(double,double)),
            cfgMachHandle,      SLOT(UpdateConfigMaxPluse(double,double)));
    connect(mMachine,           SIGNAL(UpdateHeadPosRt(int,int)),
            cutFileHandle,      SLOT(SlotUpdateHeadPosRt(int,int)));
    connect(cfgMachHandle,      SIGNAL(UpdateDataHead(QPointF,QPointF,QPointF,QPointF,QPointF)),
            cutFileHandle,      SLOT(SlotUpdateDataHead(QPointF,QPointF,QPointF,QPointF,QPointF)));
    connect(cfgMachHandle,      SIGNAL(UpdateDataApron(QList<CfgApron*>)),
            cutFileHandle,      SLOT(SlotUpdateDataApron(QList<CfgApron*>)));
    connect(cutFileHandle,      SIGNAL(UpdateDataApron()),
            cfgMachHandle,      SLOT(SlotUpdateDataApron()));
//----UserLog
    userHandle = nullptr;
    //disable all the operate item
    this->userLog_PermissionConfirm();

//----
    cfgMachHandle->InitCommunicate();
//----Start debug timer
    debugTimer=new QTimer(this);
    connect(debugTimer,SIGNAL(timeout()),this,SLOT(debugTask_100ms()));
    debugTimer->start(20);
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
    //actionList.append(ui->menuBar->findChildren<QWidget*>());
    actionList.append(ui->dockWgtOperate->findChildren<QWidget*>());
    actionList.append(ui->dockWgtList->findChildren<QWidget*>());

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
    emit keyPressed(*event);
}
void WindowCutting::keyReleaseEvent(QKeyEvent *event)
{
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
