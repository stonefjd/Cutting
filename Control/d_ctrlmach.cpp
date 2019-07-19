#include "d_ctrlmach.h"

D_CtrlMach::D_CtrlMach(QObject *parent) : QObject(parent)
{

//    ctrlTimer->start(10);
    //键盘按键查询结构体
    m_dirBitMove[AXIS_X-1].neg = DIR_A;
    m_dirBitMove[AXIS_X-1].pos = DIR_D;
    m_dirBitMove[AXIS_Y-1].neg = DIR_S;
    m_dirBitMove[AXIS_Y-1].pos = DIR_W;

    //轴插补模式结构体值初始化
    memset(&m_tCrdPrm, 0, sizeof(m_tCrdPrm));
    m_tCrdPrm.dimension=2;   // 坐标系为二维坐标系
    m_tCrdPrm.synVelMax=500;  // 最大合成速度：500pulse/ms
    m_tCrdPrm.synAccMax=1;   // 最大加速度：1pulse/ms^2，约为10m/s^2
    m_tCrdPrm.evenTime = 50;   // 最小匀速时间：50ms
    m_tCrdPrm.profile[0] = 1;   // 规划器1对应到X轴
    m_tCrdPrm.profile[1] = 2;   // 规划器2对应到Y轴
    m_tCrdPrm.setOriginFlag = 1;  // 表示需要指定坐标系的原点坐标的规划位置
    m_tCrdPrm.originPos[0] = 00000;  // 坐标系的原点坐标的规划位置为（100, 100）
    m_tCrdPrm.originPos[1] = 00000;

    //轴速度模式结构体值初始化
    m_tJogPrm.acc = 0;
    m_tJogPrm.dec = 0;
    m_tJogPrm.smooth = 0.5;
}
void D_CtrlMach::StateMachScheduleMain()
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
void D_CtrlMach::StateMachScheduleSubInit()
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
    else if(m_stSubInit == stInit_BoardInit)//condition
    {
        //循环：获取到位IO状态;注：此时脉冲板卡的限位被置位，需代码清除
        long tempValue;
        bool jumpCdt = true;
        ADP_GetGpi(&tempValue);

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
            //动作：结束机械回原点指令,清除正限位,执行回逻辑原点指令
            ADP_ClrSts(AXIS_FIRST,AXIS_MAX);
            ADP_StopHome();//结束原点检测信号,可以不需要,但为了下次触发,必须拉低
            ADP_ZeroPosALl();
            long posX,posY;
            double spd,acc;
            TCrdPrm crdPrm = m_tCrdPrm;
            posX = static_cast<long>(posOrg.x()*posToPulseScaleXY);
            posY = static_cast<long>(posOrg.y()*posToPulseScaleXY);
            spd  = idleMoveSpd * posToPulseScaleXY;//
            acc  = idleMoveAcc * posToPulseScaleXY/1000;//
            ADP_StartMovePoint(crd,fifo,posX,posY,spd,acc,crdPrm);
        }
    }
    else if(m_stSubInit == stInit_BackMachOrg)//condition
    {
        //循环：查询run到位
        short run;  // 坐标系运动完成段查询变量
        long segment;  // 坐标系的缓存区剩余空间查询变量
        ADP_GetRunStateAndSegment(crd,&run,&segment,fifo);
        //条件：run到位
        if(run == 0)
        {
            //迁移：子状态：未进入；主状态：等待状态
            m_stSubInit  = stInit_NotIn;
            m_stMainThis = stMain_Wait;
            //动作：清除负限位状态
            ADP_ClrSts(AXIS_FIRST,AXIS_MAX);
        }
    }
}
void D_CtrlMach::StateMachScheduleSubWait()
{
    //[BEGIN]转速给定并运行
    //循环：运行jog
    JoggingForAxis(AXIS_X);
    JoggingForAxis(AXIS_Y);
    //条件：
    //迁移：本身不带有条件迁移,通过事件触发迁移
    //动作：
    //[END]转速给定并运行
}
void D_CtrlMach::StateMachScheduleSubOprt()
{
    short crd=1,fifo=0;
    TCrdPrm crdPrm = m_tCrdPrm;
//    TJogPrm jogPrm = m_tJogPrm;
    double spd = idleMoveSpd * posToPulseScaleXY;
    double acc = idleMoveAcc * posToPulseScaleXY/1000;
    double smooth = 0.5;
    long posOrgX = static_cast<long>(posOrg.x()*posToPulseScaleXY);
    long posOrgY = static_cast<long>(posOrg.y()*posToPulseScaleXY);
    long posLmtX = static_cast<long>(posLmt.x()*posToPulseScaleXY);
    long posLmtY = static_cast<long>(posLmt.y()*posToPulseScaleXY);

    if(m_stSubOprt == stOprt_BtnO)
    {
        //循环：-
        //条件：轴停止运行
        if(GetAxisRunState(AXIS_X) == false && GetAxisRunState(AXIS_Y) == false)
        {
            //迁移：子状态:结束状态;主状态:不变
            m_stSubOprt = stOprt_Fnsh;
            //动作：清除状态故障位，运行到逻辑原点命令发出
            ADP_ClrSts(AXIS_FIRST,AXIS_MAX);
            ADP_StartMovePoint(crd,fifo,posOrgX,posOrgY,spd,acc,crdPrm);
        }
    }
    else if(m_stSubOprt == stOprt_BndrRsz)
    {
        if(m_cdOprtStepBndrRsz == stStepNotIn)
        {
            //循环：-
            //条件：-
            //迁移：负向匀速移动
            m_cdOprtStepBndrRsz = stStep1;
            //动作：
            ADP_ClrSts(AXIS_FIRST,AXIS_MAX);
            ADP_SetJogMode(AXIS_X,-spd,acc,smooth);
            ADP_SetJogMode(AXIS_Y,-spd,acc,smooth);
        }
        else if(m_cdOprtStepBndrRsz == stStep1)
        {
            //条件：回到机械零点
            if(GetAxisRunState(AXIS_X) == false && GetAxisRunState(AXIS_Y) == false)
            {
                //迁移:第二步
                m_cdOprtStepBndrRsz = stStep2;
                //动作:正向匀速运动
                ADP_ZeroPos(AXIS_X);
                ADP_ZeroPos(AXIS_Y);
                ADP_ClrSts(AXIS_FIRST,AXIS_MAX);
                ADP_SetJogMode(AXIS_X,spd,acc,smooth);
                ADP_SetJogMode(AXIS_Y,spd,acc,smooth);
            }
        }
        else if(m_cdOprtStepBndrRsz == stStep2)
        {
            //条件：轴停止运行
            if(GetAxisRunState(AXIS_X) == false && GetAxisRunState(AXIS_Y) == false)
            {
                //迁移:跳出小步骤；子状态切入回逻辑原点；主状态不变
                m_cdOprtStepBndrRsz = stStepNotIn;
                m_stSubOprt = stOprt_BtnO;
                //动作:更新边界尺寸并传出
                double pluseX,pluseY;
                ADP_GetAxisPrfPos(AXIS_X,&pluseX);
                ADP_GetAxisPrfPos(AXIS_Y,&pluseY);
                posMax.setX(pluseX/posToPulseScaleXY);
                posMax.setY(pluseY/posToPulseScaleXY);
                emit UpdateDataHeadPosMaxRequest();
            }
        }
    }
    else if(m_stSubOprt == stOprt_RngScan)
    {
        qDebug()<<"in Range Scane";
        //循环：-
        //条件：-
        //迁移：子状态:结束状态;主状态:不变
        m_stSubOprt = stOprt_Fnsh;
        //动作：压入移动路线,并开始运动
        ADP_ClrSts(AXIS_FIRST,AXIS_MAX);
        ADP_SetCrdPrm(crd, &crdPrm);
        ADP_CrdClear(crd, fifo);//如果提前碰壁，还会出现问题，所以移动边界需要软限位，与硬限位边界至少预留1cm的距离
        ADP_LnXY(crd,posOrgX,posOrgY,spd,acc,0,fifo);
        ADP_LnXY(crd,posOrgX,posLmtY,spd,acc,0,fifo);
        ADP_LnXY(crd,posLmtX,posLmtY,spd,acc,0,fifo);
        ADP_LnXY(crd,posLmtX,posOrgY,spd,acc,0,fifo);
        ADP_LnXY(crd,posOrgX,posOrgY,spd,acc,0,fifo);
        ADP_CrdStart(crd, 0);
    }
    else if(m_stSubOprt == stOprt_RngRst)
    {
        JoggingForAxis(AXIS_X);
        JoggingForAxis(AXIS_Y);
        if(m_cdOprtStepRngRst == stStepNotIn)
        {

        }
        m_stSubOprt = stOprt_Fnsh;
    }
    else if(m_stSubOprt == stOprt_ToolDeepCalib)
    {
        m_stSubOprt = stOprt_Fnsh;
    }
    else if(m_stSubOprt == stOprt_ToolPosCalib)
    {
        if(m_cdOprtStepToolPosCalib == stStepNotIn)
        {
            //迁移
            m_cdOprtStepToolPosCalib = stStep1;
            //动作
            ADP_ClrSts(AXIS_FIRST,AXIS_MAX);
            ADP_SetCrdPrm(crd, &crdPrm);
            ADP_CrdClear(crd, fifo);
            //校准机头停在距离x切割边界1/2处，停在Y边界1/8处
//            long edgeX = (posLmtX-posOrgX)/8+posOrgX;
//            long edgeY = (posLmtY-posOrgY)/2+posOrgY;
//            ADP_LnXY(crd,edgeX,edgeY,spd,acc,0,fifo);
            long posMaxZ = static_cast<long>(m_nKnifeMaxDeep * posToPulseScaleXY);
            ADP_BufMove(crd,m_nCtrlAxisZ,posMaxZ,5,0.1,1,0);
            ADP_CrdStart(crd, 0);
        }
        else if(m_cdOprtStepToolPosCalib == stStep1)
        {
            //循环：查询run到位
            short run;  // 坐标系运动完成段查询变量
            long segment;  // 坐标系的缓存区剩余空间查询变量
            ADP_GetRunStateAndSegment(crd,&run,&segment,fifo);
            //条件：
            if(run == 0)
            {
                //迁移：子状态：未进入；主状态：等待状态
                m_cdOprtStepToolPosCalib = stStep2;
                //动作：-
            }
        }
        else if(m_cdOprtStepToolPosCalib == stStep2)
        {
            JoggingForAxis(AXIS_X,0.2);
            JoggingForAxis(AXIS_Y,0.2);
        }
    }
    else if(m_stSubOprt == stOprt_Fnsh)
    {
        //循环：查询run到位
        short run;  // 坐标系运动完成段查询变量
        long segment;  // 坐标系的缓存区剩余空间查询变量
        ADP_GetRunStateAndSegment(crd,&run,&segment,fifo);
        //条件：
        if(run == 0)
        {
        //迁移：子状态：未进入；主状态：等待状态
            m_stSubOprt  = stOprt_NotIn;
            m_stMainThis = stMain_Wait;
        //动作：结束操作，清除残留状态置位
            ADP_ClrSts(AXIS_FIRST,AXIS_MAX);
        }
    }
}
void D_CtrlMach::JoggingForAxis(short _axis,double _lowSpdScale)
{
    double spd = 0;
    double acc = idleMoveAcc;
    double smooth = 0.5;
    bool cmdNeg = (m_cdDirCmd & (1<<m_dirBitMove[_axis-1].neg))&&!(m_cdDirCmd & (1<<m_dirBitMove[_axis-1].pos));
    bool cmdPos = !(m_cdDirCmd & (1<<m_dirBitMove[_axis-1].neg))&&(m_cdDirCmd & (1<<m_dirBitMove[_axis-1].pos));
    bool lmtNeg = false;
    bool lmtPos = false;
//暂时注释掉安全距离，应该用常量来设计
//    if(_axis == AXIS_X)
//    {
//        lmtNeg = GetPosRT().x()<GetPosOrg().x();
//        lmtPos = GetPosRT().x()>GetPosLmt().x();
//    }
//    if(_axis == AXIS_Y)
//    {
//        lmtNeg = GetPosRT().y()<GetPosOrg().y();
//        lmtPos = GetPosRT().y()>GetPosLmt().y();
//    }
    if(_axis == AXIS_X ||_axis == AXIS_Y)//目前只有X和Y轴可以设定为速度模式运行
    {
        //条件(有指令||        (没指令            &&在运行))
        if((cmdNeg||cmdPos)||(!(cmdNeg||cmdPos)&&m_stAxisRunState[_axis-1]))
        {
            ADP_ClrSts(_axis);
            if(cmdNeg&&!lmtNeg)
            {
                spd = -idleMoveSpd * posToPulseScaleXY * _lowSpdScale;
            }
            else if(cmdPos&&!lmtPos)
            {
                spd =  idleMoveSpd * posToPulseScaleXY * _lowSpdScale;
            }
            else
            {
                spd = 0;
            }
            ADP_SetJogMode(_axis,spd,acc,smooth);
        }
    }
}
//循环：
//条件：
//迁移：
//动作：
void D_CtrlMach::EventOprtSubEnterToolPosCalib()
{
    qDebug()<<"enter,calib";
    if(m_stMainThis == stMain_Wait)
    {
        m_stMainThis = stMain_Oprt;
        m_stSubOprt  = stOprt_ToolPosCalib;
    }
}
void D_CtrlMach::EventOprtSubExitToolPosCalib()
{
    qDebug()<<"exit,calib";
    if(m_stMainThis == stMain_Oprt)
    {
        m_stSubOprt  = stOprt_BtnO;
        m_cdOprtStepToolPosCalib = stStepNotIn;
    }
}
void D_CtrlMach::EventOprtSubEnter(int _id)
{
    if(m_stMainThis == stMain_Wait)
    {
        m_stMainThis = stMain_Oprt;
        if(_id == 0)
        {
            m_stSubOprt  = stOprt_BndrRsz;
        }
        else if(_id == 1)
        {
            m_stSubOprt  = stOprt_RngScan;
        }
        else if(_id == 2)
        {
            m_stSubOprt  = stOprt_RngRst;
        }
        else if(_id == 3)
        {
            m_stSubOprt  = stOprt_ToolDeepCalib;
        }
        else if(_id == 4)
        {
            m_stSubOprt  = stOprt_ToolPosCalib;
        }
    }
}
void D_CtrlMach::EventActionKey(QKeyEvent event)
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

void D_CtrlMach::GetRunningData()
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
    m_stAxisRunState[AXIS_Z1-1] = ADP_GetAxisRunState(AXIS_Z1);
    m_stAxisRunState[AXIS_A1-1] = ADP_GetAxisRunState(AXIS_A1);
//--可注释
    long xSts,ySts;
    ADP_GetSts(AXIS_X,&xSts);
    ADP_GetSts(AXIS_Y,&ySts);
//    qDebug()<<xSts<<' '<<ySts;
}

void D_CtrlMach::SlotBtnPressed(int _id)
{
    qDebug()<<"press"+QString::number(_id);
    //"UL","U","UR","L","ORG","R","DL","D","DR"
    switch(_id)
    {
    case 0:m_cdDirCmd |= (1<<DIR_W);m_cdDirCmd |= (1<<DIR_A);break;
    case 1:m_cdDirCmd |= (1<<DIR_W);break;
    case 2:m_cdDirCmd |= (1<<DIR_W);m_cdDirCmd |= (1<<DIR_D);break;
    case 3:m_cdDirCmd |= (1<<DIR_A);break;
    case 4:if(m_stMainThis == stMain_Wait)
        {
            m_stMainThis = stMain_Oprt;
            m_stSubOprt  = stOprt_BtnO;
        }
        break;//留着进入oprt状态
    case 5:m_cdDirCmd |= (1<<DIR_D);break;
    case 6:m_cdDirCmd |= (1<<DIR_S);m_cdDirCmd |= (1<<DIR_A);break;
    case 7:m_cdDirCmd |= (1<<DIR_S);break;
    case 8:m_cdDirCmd |= (1<<DIR_S);m_cdDirCmd |= (1<<DIR_D);break;
    }
}
void D_CtrlMach::SlotBtnReleased(int _id)
{
    qDebug()<<"release"+QString::number(_id);
    //"UL","U","UR","L","ORG","R","DL","D","DR"
    switch(_id)
    {
    case 0:m_cdDirCmd &= ~ (1<<DIR_W);m_cdDirCmd &= ~ (1<<DIR_A);break;
    case 1:m_cdDirCmd &= ~ (1<<DIR_W);break;
    case 2:m_cdDirCmd &= ~ (1<<DIR_W);m_cdDirCmd &= ~ (1<<DIR_D);break;
    case 3:m_cdDirCmd &= ~ (1<<DIR_A);break;
    case 4:break;
    case 5:m_cdDirCmd &= ~ (1<<DIR_D);break;
    case 6:m_cdDirCmd &= ~ (1<<DIR_S);m_cdDirCmd &= ~ (1<<DIR_A);break;
    case 7:m_cdDirCmd &= ~ (1<<DIR_S);break;
    case 8:m_cdDirCmd &= ~ (1<<DIR_S);m_cdDirCmd &= ~ (1<<DIR_D);break;
    }
}
MainState D_CtrlMach::GetMainState()
{
    return this->m_stMainThis;
}
void    D_CtrlMach::SetCtrlAxisGroup(short _axisZ, short _axisA, double _deep)
{
    this->m_nCtrlAxisZ = _axisZ;
    this->m_nCtrlAxisA = _axisA;
    this->m_nKnifeMaxDeep = _deep;
}
bool    D_CtrlMach::GetAxisRunState(short _axis)
{
    return  this->m_stAxisRunState[_axis-1];
}
void    D_CtrlMach::SetPosOrg(QPointF _pointF)
{
    this->posOrg = _pointF;
}
QPointF D_CtrlMach::GetPosOrg()
{
    return this->posOrg;
}

void    D_CtrlMach::SetPosToPulseScaleXY(double _val)
{
    this->posToPulseScaleXY = _val;
}

double D_CtrlMach::GetPosToPulseScaleXY()
{
    return this->posToPulseScaleXY;
}

void    D_CtrlMach::SetPosLmt(QPointF _pointF)
{
    this->posLmt = _pointF;
}

QPointF D_CtrlMach::GetPosLmt()
{
    return this->posLmt;
}

void    D_CtrlMach::SetPosMax(QPointF _pointF)
{
    this->posMax = _pointF;
}

QPointF D_CtrlMach::GetPosMax()
{
    return this->posMax;
}
void    D_CtrlMach::SetIdleMoveSpd(double _val)
{
    idleMoveSpd = _val;
}
double  D_CtrlMach::GetIdleMoveSpd()
{
    return idleMoveSpd;
}
void    D_CtrlMach::SetIdleMoveAcc(double _val)
{
    idleMoveAcc = _val;
}
double  D_CtrlMach::GetIdleMoveAcc()
{
    return idleMoveAcc;
}
//--传出参数读
QPointF D_CtrlMach::GetPosRT()
{
    return this->posRT;
}
