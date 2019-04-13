#include "windowcutting.h"
#include "ui_windowcutting.h"
#define AXIS_X 1
#define AXIS_Y 2
#pragma execution_character_set("utf-8")

WindowCutting::WindowCutting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowCutting)
{
    ui->setupUi(this);
}

WindowCutting::~WindowCutting()
{
    delete ui;
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
    this->settings.exec();
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
        settings.resetSettingsData();
        qDebug()<<"recover";
    }
    else if(msgBox.clickedButton()== btnNo)
    {

    }
}

//----------------TEST-----------------
void WindowCutting::on_pushButton_clicked()
{
    GT_Open();
    GT_SetDo(MC_GPO,0);
    double value=0;
    GT_GetEncPos(11,&value,1,nullptr);

    GT_Close();
    ui->label->setText(QString::number(value));
}

void WindowCutting::on_pushButton_2_clicked()
{
//    this->mMachine.mFan_1.SetState_FanStop();
    short sRtn;
    long int value;
    char *pVersion;
    sRtn = GT_Open();
    sRtn = GT_GetVersion(&pVersion);
//    GT_Reset();
    GT_SetDo(MC_GPO,0);
    GT_GetDi(MC_GPI,&value);
    sRtn = GT_AxisOff(AXIS_X);
    GT_Close();

    qDebug()<<QString(pVersion);
}
void WindowCutting::on_pushButton_4_clicked()
{
    short sRtn;
    QString qStr = "E:\\01.repository\\07.QT\\GTS800.cfg";
    QByteArray qByteArray= qStr.toUtf8();
    char *cStr = qByteArray.data();
    sRtn = GT_Open();
    sRtn = GT_Reset();
    sRtn = GT_LoadConfig(cStr);
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
    long space;
    // 即将把数据存入坐标系1的FIFO0中，所以要首先清除此缓存区中的数据
    sRtn = GT_CrdClear(1, 0);
    // 向缓存区写入第一段插补数据
    sRtn = GT_LnXY(    1,    // 该插补段的坐标系是坐标系1
                       15000, 15000,  // 该插补段的终点坐标(200000, 0)
                       20,    // 该插补段的目标速度：100pulse/ms
                       0.05,    // 插补段的加速度：0.1pulse/ms^2
                       0,    // 终点速度为0
                       0);    // 向坐标系1的FIFO0缓存区传递该直线插补数据
    sRtn =  GT_ArcXYR(
                1,     // 坐标系是坐标系1
                30000, 0,   // 该圆弧的终点坐标(0, 10000)
                -15000,   // 半径：5000pulse
                0,     // 该圆弧是shu时针圆弧
                50,     // 该插补段的目标速度：100pulse/ms
                0.1,     // 该插补段的加速度：0.1pulse/ms^2
                0,     // 终点速度为0
                0);     // 向坐标系1的FIFO0缓存区传递该直线插补数据
    sRtn = GT_CrdStart(1, 0);
    sRtn = GT_CrdStatus(1, &run, &segment, 0);
    do
    {
        // 查询坐标系1的FIFO的插补运动状态
        sRtn = GT_CrdStatus(     1,   // 坐标系是坐标系1
                                 &run,  // 读取插补运动状态
                                 &segment, // 读取当前已经完成的插补段数
                                 0);   // 查询坐标系1的FIFO0缓存区
        // 坐标系在运动, 查询到的run的值为1
    }while(run == 1);
}
void WindowCutting::on_pushButton_3_clicked()
{
    short sRtn;
    QString qStr = "E:\\01.repository\\07.QT\\GTS800.cfg";
    QByteArray qByteArray= qStr.toUtf8();
    char *cStr = qByteArray.data();
    sRtn = GT_Open();
    sRtn = GT_Reset();
    sRtn = GT_LoadConfig(cStr);
    sRtn = GT_ClrSts(1,8);

    sRtn = GT_AxisOn(AXIS_X);
    sRtn = GT_AxisOn(AXIS_Y);
    sRtn = GT_ZeroPos(AXIS_X);
    sRtn = GT_ZeroPos(AXIS_Y);
    sRtn = GT_SetPrfPos(AXIS_X, 0);
    sRtn = GT_SetPrfPos(AXIS_Y, 0);
    sRtn = GT_PrfTrap(AXIS_X);
    sRtn = GT_PrfTrap(AXIS_Y);

    TTrapPrm trap;
    long sts;
    double prfPos;

    sRtn = GT_GetTrapPrm(AXIS_X, &trap);

    qDebug()<<trap.acc;
    qDebug()<<trap.dec;
    qDebug()<<trap.smoothTime;
    trap.acc = 0.05;
    trap.dec = 0.05;
    trap.velStart = 60;
    trap.smoothTime = 50;
    sRtn = GT_SetTrapPrm(AXIS_X,&trap);
    sRtn = GT_SetTrapPrm(AXIS_Y,&trap);
    sRtn = GT_SetVel(AXIS_X, 40);
    sRtn = GT_SetVel(AXIS_Y, 40);




    sRtn = GT_SetPos(AXIS_X, 40000L);
    sRtn = GT_Update(1<<(AXIS_X-1));
    do
    {
        sRtn = GT_GetSts(AXIS_X, &sts);
        sRtn = GT_GetPrfPos(AXIS_X, &prfPos);
        ui->label->setText(QString::number(sts));
    }while(sts&0x400);

    sRtn = GT_SetPos(AXIS_Y, 40000L);
    sRtn = GT_Update(1<<(AXIS_Y-1));
    do
    {
        sRtn = GT_GetSts(AXIS_Y, &sts);
        sRtn = GT_GetPrfPos(AXIS_Y, &prfPos);
        ui->label->setText(QString::number(sts));
    }while(sts&0x400);

    sRtn = GT_ClrSts(1,8);

    sRtn = GT_SetPos(AXIS_X, -1L);
    sRtn = GT_Update(1<<(AXIS_X-1));
    do
    {
        sRtn = GT_GetSts(AXIS_X, &sts);
        sRtn = GT_GetPrfPos(AXIS_X, &prfPos);
        ui->label->setText(QString::number(sts));
    }while(sts&0x400);


    sRtn = GT_SetPos(AXIS_Y, 0);
    sRtn = GT_Update(1<<(AXIS_Y-1));
    do
    {
        sRtn = GT_GetSts(AXIS_Y, &sts);
        sRtn = GT_GetPrfPos(AXIS_Y, &prfPos);
        ui->label->setText(QString::number(sts));
    }while(sts&0x400);

    sRtn = GT_SetPos(AXIS_X, 2000L);
    sRtn = GT_SetPos(AXIS_Y, 2000L);
    sRtn = GT_Update(1<<(AXIS_X-1));
    do
    {
        sRtn = GT_GetSts(AXIS_X, &sts);
        sRtn = GT_GetPrfPos(AXIS_X, &prfPos);
        ui->label->setText(QString::number(sts));
    }while(sts&0x400);

    sRtn = GT_Update(1<<(AXIS_Y-1));
    do
    {
        sRtn = GT_GetSts(AXIS_Y, &sts);
        sRtn = GT_GetPrfPos(AXIS_Y, &prfPos);
        ui->label->setText(QString::number(sts));
    }while(sts&0x400);
    sRtn = GT_ClrSts(1,8);

//    sRtn = GT_AxisOff(AXIS_X);
//    sRtn = GT_AxisOff(AXIS_Y);

//    TCrdPrm crdPrm;
//    memset(&crdPrm, 0, sizeof(crdPrm));
// // 为结构体赋值
//    crdPrm.dimension=2;   // 坐标系为二维坐标系
//    crdPrm.synVelMax=500;  // 最大合成速度：500pulse/ms
//    crdPrm.synAccMax=1;   // 最大加速度：1pulse/ms^2
//    crdPrm.evenTime = 50;   // 最小匀速时间：50ms
//    crdPrm.profile[0] = 1;   // 规划器1对应到X轴
//    crdPrm.profile[1] = 2;   // 规划器2对应到Y轴
//    crdPrm.setOriginFlag = 1;  // 表示需要指定坐标系的原点坐标的规划位置
//    crdPrm.originPos[0] = 100;  // 坐标系的原点坐标的规划位置为（100, 100）
//    crdPrm.originPos[1] = 100;
//    sRtn = GT_SetCrdPrm(1, &crdPrm);


//    // 指令返回值变量
//    short run;  // 坐标系运动完成段查询变量
//    long segment;  // 坐标系的缓存区剩余空间查询变量
//    long space;
//    // 即将把数据存入坐标系1的FIFO0中，所以要首先清除此缓存区中的数据
//    sRtn = GT_CrdClear(1, 0);  // 向缓存区写入第一段插补数据
//    sRtn = GT_LnXY(    1,    // 该插补段的坐标系是坐标系1
//                       200000, 0,  // 该插补段的终点坐标(200000, 0)
//                       100,    // 该插补段的目标速度：100pulse/ms
//                       0.1,    // 插补段的加速度：0.1pulse/ms^2
//                       0,    // 终点速度为0
//                       0);    // 向坐标系1的FIFO0缓存区传递该直线插补数据
}





void WindowCutting::on_actionImport_triggered()
{
    records.fileDir_Chose();
}

void WindowCutting::on_push_Initial_clicked()
{
    short sRtn;
    QString qStr = "E:\\01.repository\\07.QT\\GTS800.cfg";
    QByteArray qByteArray= qStr.toUtf8();
    char *cStr = qByteArray.data();
    sRtn = GT_Open();
    sRtn = GT_Reset();
    sRtn = GT_LoadConfig(cStr);
    sRtn = GT_ClrSts(1,8);

    sRtn = GT_AxisOn(AXIS_X);
    sRtn = GT_AxisOn(AXIS_Y);
    sRtn = GT_ZeroPos(AXIS_X);
    sRtn = GT_ZeroPos(AXIS_Y);
    sRtn = GT_SetPrfPos(AXIS_X, 0);
    sRtn = GT_SetPrfPos(AXIS_Y, 0);
    sRtn = GT_PrfJog (AXIS_X);
    sRtn = GT_PrfJog (AXIS_Y);

    TJogPrm Jog;
    long sts;
    double prfPos;
    sRtn = GT_SetJogPrm (AXIS_X, &Jog);

    qDebug()<<Jog.acc;
    qDebug()<<Jog.dec;
    qDebug()<<Jog.smooth;
    Jog.acc = 0.05;
    Jog.dec = 0.05;
    Jog.smooth = 0.5;
    sRtn = GT_SetJogPrm (AXIS_X,&Jog);
    sRtn = GT_SetJogPrm (AXIS_Y,&Jog);
    sRtn = GT_SetVel(AXIS_X, 5);
    sRtn = GT_SetVel(AXIS_Y, 5);

    sRtn = GT_Update(1<<(AXIS_X-1));
    sRtn = GT_Update(1<<(AXIS_Y-1));
//    do
//    {
//        sRtn = GT_GetSts(AXIS_X, &sts);
//        sRtn = GT_GetPrfPos(AXIS_X, &prfPos);
//    }while(sts&0x060);

//    do
//    {
//        sRtn = GT_GetSts(AXIS_Y, &sts);
//        sRtn = GT_GetPrfPos(AXIS_Y, &prfPos);

//    }while(sts&0x060);

    //    sRtn = GT_SetPos(AXIS_X, 2000L);
    //    sRtn = GT_SetPos(AXIS_Y, 2000L);
    //    sRtn = GT_Update(1<<(AXIS_X-1));
    //    do
    //    {
    //        sRtn = GT_GetSts(AXIS_X, &sts);
    //        sRtn = GT_GetPrfPos(AXIS_X, &prfPos);
    //        ui->label->setText(QString::number(sts));
    //    }while(sts&0x400);

    //    sRtn = GT_Update(1<<(AXIS_Y-1));
    //    do
    //    {
    //        sRtn = GT_GetSts(AXIS_Y, &sts);
    //        sRtn = GT_GetPrfPos(AXIS_Y, &prfPos);
    //        ui->label->setText(QString::number(sts));
    //    }while(sts&0x400);
    //    sRtn = GT_ClrSts(1,8);

}

void WindowCutting::on_Getstatus_clicked()
{
    long sts1,sts2;
    GT_GetSts(AXIS_X, &sts1);
    GT_GetSts(AXIS_Y, &sts2);
    ui->label->setText(QString::number(sts1)+' '+QString::number(sts2));
}
