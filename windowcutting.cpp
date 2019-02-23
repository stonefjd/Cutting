#include "windowcutting.h"
#include "ui_windowcutting.h"
#define AXIS 1
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
    sRtn = GT_AxisOff(AXIS);
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
    sRtn = GT_AxisOn(AXIS);

    sRtn = GT_Close();
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

    sRtn = GT_AxisOn(AXIS);
    sRtn = GT_ZeroPos(AXIS);
    sRtn = GT_SetPrfPos(AXIS, 0);
    sRtn = GT_PrfTrap(AXIS);

    TTrapPrm trap;
    long sts;
    double prfPos;

    sRtn = GT_GetTrapPrm(AXIS, &trap);
    qDebug()<<trap.acc;
    qDebug()<<trap.dec;
    qDebug()<<trap.smoothTime;
    trap.acc = 0.025;
    trap.dec = 0.125;
    trap.smoothTime = 25;
    sRtn = GT_SetTrapPrm(AXIS,&trap);
    sRtn = GT_SetPos(AXIS, 500L);
    sRtn = GT_SetVel(AXIS, 50);
    sRtn = GT_Update(1<<(AXIS-1));

    do
    {
        sRtn = GT_GetSts(AXIS, &sts);
        sRtn = GT_GetPrfPos(AXIS, &prfPos);
    }while(sts&0x400);
    sRtn = GT_AxisOff(AXIS);

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
