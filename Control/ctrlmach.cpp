#include "ctrlmach.h"

CtrlMach::CtrlMach(QObject *parent) : QObject(parent)
{

//    ctrlTimer->start(10);

    ADP_InitData();
    m_dirBitMove[AXIS_X-1].neg = DIR_A;
    m_dirBitMove[AXIS_X-1].pos = DIR_D;
    m_dirBitMove[AXIS_Y-1].neg = DIR_S;
    m_dirBitMove[AXIS_Y-1].pos = DIR_W;

}
void CtrlMach::StateMachScheduleMain()
{
    switch (m_stMainThis)
    {
    case stMain_Init:
    {
        StateMachScheduleSubInit();
        break;
    }
    case stMain_Wait:
    {
        StateMachScheduleSubWait();
        break;
    }
    case stMain_Oprt:
        StateMachScheduleSubOprt();
        break;
    case stMain_Cut:
        break;
    case stMain_Err:
        break;
    case stMain_Stop:
        break;
    }
}
void CtrlMach::StateMachScheduleSubInit()
{
    short crd=1,fifo=0;
    if(m_stSubInit == stInit_NotIn)
    {
        //循环：无
        //条件：无
        //迁移：子状态：回零状态；主状态：不变
        m_stSubInit = stInit_BoardInit;
        //动作：连接板子
        ADP_InitBoard("E:\\01.repository\\07.QT\\GTS800.cfg");            //轴卡连接，加载配置文件
        ADP_EnableAllAxis();        //清除状态位并使能伺服控制器所有轴号
        ADP_ZeroPosALl();           //将当前位置设为零位
        ADP_StartHome();
    }
    if(m_stSubInit == stInit_BoardInit)//condition
    {
        //循环：获取到位IO状态;注：此时脉冲板卡的限位被置位，需代码清除
        long tempValue;
        bool jumpCdt = true;
        ADP_GetGpi(&tempValue);
        //ADP_StopHome();//结束原点检测信号,不需要,理解为默认沿触发
        for(int i=0;i<AXIS_MAX;i++)//轴号与DI对应关系：X-DI0,Y-DI1,Z1-DI2,A2-DI3
        {
            if((tempValue & static_cast<long>(1<<i))==0)
            {
                m_cdInitMachOrg[i] = true;
            }
        }
        for(int i=0;i<AXIS_MAX;i++)
        {
            if(m_cdInitMachOrg[i] == false)
            {
                jumpCdt = false;
                break;
            }
        }
        //条件：IO全部出现过低电平状态
        if(jumpCdt == true)
        {
            //迁移：子状态：回设定原点；主状态：不变
            m_stSubInit = stInit_BackMachOrg;
            //动作：执行回原点指令
            ADP_ZeroPosALl();
            long posX,posY;
            double spd,acc;
            posX = static_cast<long>(posOrg.x()*posToPulseScaleXY);
            posY = static_cast<long>(posOrg.y()*posToPulseScaleXY);
            spd  = idleMoveSpd * posToPulseScaleXY;//
            acc  = idleMoveAcc * posToPulseScaleXY/1000;//
            ADP_StartMovePoint(crd,fifo,posX,posY,spd,acc);
        }
    }
    if(m_stSubInit == stInit_BackMachOrg)//condition
    {
        //循环：查询run到位
        short run;  // 坐标系运动完成段查询变量
        long segment;  // 坐标系的缓存区剩余空间查询变量
        ADP_GetRunStateAndSegment(crd,&run,&segment,fifo);
        //条件：run到位
        if(run == 0)
        {
            //迁移：子状态：未进入；主状态：等待状态
            m_stMainThis = stMain_Wait;
            //动作：清除负限位状态
            ADP_ClrSts(AXIS_FIRST,AXIS_MAX);
        }
    }
}
void CtrlMach::StateMachScheduleSubWait()
{
    //[BEGIN]转速给定并运行
    //循环：运行jog
    JoggingForAxis(AXIS_X);
    JoggingForAxis(AXIS_Y);
    //条件：
    //迁移：
    //动作：
    //[END]转速给定并运行
}
void CtrlMach::StateMachScheduleSubOprt()
{

}
void CtrlMach::JoggingForAxis(short _axis)
{
    double spd = 0;
    double acc = idleMoveAcc;
    if(_axis == AXIS_X ||_axis == AXIS_Y)//目前只有X和Y轴可以设定为速度运行
    {
        ADP_ClrSts(_axis);
        if((m_cdDirCmd & (1<<m_dirBitMove[_axis-1].neg))&&!(m_cdDirCmd & (1<<m_dirBitMove[_axis-1].pos)))
        {
            spd = -idleMoveSpd * posToPulseScaleXY;
        }
        else if(!(m_cdDirCmd & (1<<m_dirBitMove[_axis-1].neg))&&(m_cdDirCmd & (1<<m_dirBitMove[_axis-1].pos)))
        {
            spd = idleMoveSpd * posToPulseScaleXY;
        }
        else
        {
            spd = 0;
        }
        ADP_SetJogMode(_axis,spd,acc);
    }
}
//循环：
//条件：
//迁移：
//动作：
void CtrlMach::KeyActionEvent(QKeyEvent event)
{
//考虑到事件信号的发射次数,将发按键对象以及重复的条件放入发射信号的地方
    //[BEGIN]标志位记录
    if(event.type() == QEvent::KeyPress)
    {
        switch(event.key())
        {
        case Qt::Key_W:
            m_cdDirCmd |= (1<<DIR_W);
            break;
        case Qt::Key_S:
            m_cdDirCmd |= (1<<DIR_S);
            break;
        case Qt::Key_A:
            m_cdDirCmd |= (1<<DIR_A);
            break;
        case Qt::Key_D:
            m_cdDirCmd |= (1<<DIR_D);
            break;
        }
    }
    else if(event.type() == QEvent::KeyRelease)
    {
        switch(event.key())
        {
        case Qt::Key_W:
            m_cdDirCmd &= ~(1<<DIR_W);
            break;
        case Qt::Key_S:
            m_cdDirCmd &= ~(1<<DIR_S);
            break;
        case Qt::Key_A:
            m_cdDirCmd &= ~(1<<DIR_A);
            break;
        case Qt::Key_D:
            m_cdDirCmd &= ~(1<<DIR_D);
            break;
        }
    }
    //[END]标志位记录
    qDebug()<<QString::number(m_cdDirCmd,2);
}

void CtrlMach::GetRunningData()
{
//--获取机头实时位置
    //获取读取位置
    ADP_GetHeadPosRt(&posRT,this->posToPulseScaleXY);//x与y一致,目前默认用y
    //限幅
    if(posRT.x()<0.0)
        posRT.setX(0.0);
    else if(posRT.x()>posMax.x())
        posRT.setX(posMax.x());
    if(posRT.y()<0.0)
        posRT.setY(0.0);
    else if(posRT.y()>posMax.y())
        posRT.setY(posMax.y());
//--获取机头轴状态
    m_stAxisRunState[AXIS_X-1] = ADP_GetAxisRunState(AXIS_X);
    m_stAxisRunState[AXIS_Y-1] = ADP_GetAxisRunState(AXIS_Y);
}

void CtrlMach::SlotBtnPressed(int _id)
{
    qDebug()<<"press"+QString::number(_id);
    //"UL","U","UR","L","ORG","R","DL","D","DR"
    switch(_id)
    {
    case 0:m_cdDirCmd |= (1<<DIR_W);m_cdDirCmd |= (1<<DIR_A);break;
    case 1:m_cdDirCmd |= (1<<DIR_W);break;
    case 2:m_cdDirCmd |= (1<<DIR_W);m_cdDirCmd |= (1<<DIR_D);break;
    case 3:m_cdDirCmd |= (1<<DIR_A);break;
    case 4:break;//留着进入oprt状态
    case 5:m_cdDirCmd |= (1<<DIR_D);break;
    case 6:m_cdDirCmd |= (1<<DIR_S);m_cdDirCmd |= (1<<DIR_A);break;
    case 7:m_cdDirCmd |= (1<<DIR_S);break;
    case 8:m_cdDirCmd |= (1<<DIR_S);m_cdDirCmd |= (1<<DIR_D);break;
    }
}
void CtrlMach::SlotBtnReleased(int _id)
{
    qDebug()<<"release"+QString::number(_id);
    //"UL","U","UR","L","ORG","R","DL","D","DR"
    switch(_id)
    {
    case 0:m_cdDirCmd &= ~ (1<<DIR_W);m_cdDirCmd &= ~ (1<<DIR_A);break;
    case 1:m_cdDirCmd &= ~ (1<<DIR_W);break;
    case 2:m_cdDirCmd &= ~ (1<<DIR_W);m_cdDirCmd &= ~ (1<<DIR_D);break;
    case 3:m_cdDirCmd &= ~ (1<<DIR_A);break;
    case 4:break;//留着进入oprt状态
    case 5:m_cdDirCmd &= ~ (1<<DIR_D);break;
    case 6:m_cdDirCmd &= ~ (1<<DIR_S);m_cdDirCmd &= ~ (1<<DIR_A);break;
    case 7:m_cdDirCmd &= ~ (1<<DIR_S);break;
    case 8:m_cdDirCmd &= ~ (1<<DIR_S);m_cdDirCmd &= ~ (1<<DIR_D);break;
    }
}
MainState CtrlMach::GetMainState()
{
    return this->m_stMainThis;
}
bool    CtrlMach::GetAxisRunState(int _axis)
{
    return  this->m_stAxisRunState[_axis-1];
}
void    CtrlMach::SetPosOrg(QPointF _pointF)
{
    this->posOrg = _pointF;
}
QPointF CtrlMach::GetPosOrg()
{
    return this->posOrg;
}

void    CtrlMach::SetPosToPulseScaleXY(double _val)
{
    this->posToPulseScaleXY = _val;
}

double CtrlMach::GetPosToPulseScaleXY()
{
    return this->posToPulseScaleXY;
}

void    CtrlMach::SetPosLmt(QPointF _pointF)
{
    this->posLmt = _pointF;
}

QPointF CtrlMach::GetPosLmt()
{
    return this->posLmt;
}

void    CtrlMach::SetPosMax(QPointF _pointF)
{
    this->posMax = _pointF;
}

QPointF CtrlMach::GetPosMax()
{
    return this->posMax;
}
void    CtrlMach::SetIdleMoveSpd(double _val)
{
    idleMoveSpd = _val;
}
double  CtrlMach::GetIdleMoveSpd()
{
    return idleMoveSpd;
}
void    CtrlMach::SetIdleMoveAcc(double _val)
{
    idleMoveAcc = _val;
}
double  CtrlMach::GetIdleMoveAcc()
{
    return idleMoveAcc;
}
//--传出参数读
QPointF CtrlMach::GetPosRT()
{
    return this->posRT;
}
