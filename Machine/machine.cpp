#include "machine.h"
#include "PhysicalLayer/gts.h"
Machine::Machine(QObject *parent) : QObject(parent)
{
//    this->mFan_1.SetState_FanStop();

//--------DATA structure settings--------//
//----set the knife of the machine
    sdKnifeConfigLib.ReadConfigFile();
    qDebug()<<sdKnifeConfigLib.GetKnifesCount();
//--------StateMachine Running--------//
    mTimer=new QTimer(this);
    connect(mTimer,SIGNAL(timeout()),this,SLOT(Task_10ms_stateMachine()));
    mTimer->start(10);
//----InitMachine
    this->MInit();
//------creat the limit State of the machine
    for(short i=0;i<sdKnifeConfigLib.GetKnifesCount()+2;i++)
    {
        LimitSwitch *limit = new LimitSwitch(i+1,nullptr);
        limitList.push_back(limit);
    }
//----
}
void Machine::MInit()
{
    ADP_Connect();
    ADP_Reset();
    ADP_LoadCfgFile("E:\\01.repository\\07.QT\\GTS800.cfg");
    ADP_ClrSts(1,4);
//----check is the knife changed
    {}

//----set the machine limitSwitch
    GT_AxisOn(AXIS_X);
    GT_AxisOn(AXIS_Y);
    GT_ZeroPos(AXIS_X);
    GT_ZeroPos(AXIS_Y);
    GT_SetPrfPos(AXIS_X, 0);
    GT_SetPrfPos(AXIS_Y, 0);
    bool limitStateXPos;
    bool limitStateXNeg;
    bool limitStateYPos;
    bool limitStateYNeg;
    ADP_GetLimitState(AXIS_X,true, &limitStateXPos);
    ADP_GetLimitState(AXIS_X,false,&limitStateXNeg);
    ADP_GetLimitState(AXIS_Y,true, &limitStateYPos);
    ADP_GetLimitState(AXIS_Y,false,&limitStateYNeg);

    qDebug()<<limitStateXPos<<' '<<limitStateXNeg<<' '<<limitStateYPos<<' '<<limitStateYNeg;

    QPointF firstDot(0,0);
    if(limitStateXNeg == true)
    {
        firstDot.setX(2000);
    }
    if(limitStateYNeg == true)
    {
        firstDot.setY(2000);
    }
    if(firstDot!=QPointF(0.0,0.0))
    {
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
        GT_SetCrdPrm(1, &crdPrm);

        // 指令返回值变量
        short run;  // 坐标系运动完成段查询变量
        long segment;  // 坐标系的缓存区剩余空间查询变量
        long space;
        short sRtn;
        // 即将把数据存入坐标系1的FIFO0中，所以要首先清除此缓存区中的数据
        sRtn = GT_CrdClear(1, 0);
        // 向缓存区写入第一段插补数据
        sRtn = GT_LnXY(    1,    // 该插补段的坐标系是坐标系1
                           static_cast<long>(firstDot.x()), static_cast<long>(firstDot.y()),  //
                           10,    // 该插补段的目标速度：100pulse/ms
                           0.05,    // 插补段的加速度：0.1pulse/ms^2
                           0,    // 终点速度为0
                           0);    // 向坐标系1的FIFO0缓存区传递该直线插补数据
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
//    GT_SetDoBit(MC_GPO,1,0);
//    GT_SetDoBit(MC_GPO,2,0);
//    GT_SetDoBit(MC_GPO,3,0);
}

void Machine::Task_10ms_stateMachine()
{


}
