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
        StateMachScheduleSubCut();
        break;
    case stMain_Err:
        break;
    case stMain_Stop:
        break;
    }
}
void D_CtrlMach::StateMachScheduleSubInit()
{
    short crd=1,fifo0=0;
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
            posX = static_cast<long>(posOrg->x()*(*posToPulseScaleXY));
            posY = static_cast<long>(posOrg->y()*(*posToPulseScaleXY));
            spd  = *idleMoveSpd * (*posToPulseScaleXY);//
            acc  = *idleMoveAcc * (*posToPulseScaleXY)/1000;//
            ADP_StartMovePoint(crd,fifo0,posX,posY,spd,acc,crdPrm);
        }
    }
    else if(m_stSubInit == stInit_BackMachOrg)//condition
    {
        //循环：查询run到位
        short run;  // 坐标系运动完成段查询变量
        long segment;  // 坐标系的缓存区剩余空间查询变量
        ADP_GetRunStateAndSegment(crd,&run,&segment,fifo0);
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
    short crd=1,fifo0=0;
    TCrdPrm crdPrm = m_tCrdPrm;
//    TJogPrm jogPrm = m_tJogPrm;
    double spd = *idleMoveSpd * *posToPulseScaleXY;
    double acc = *idleMoveAcc * *posToPulseScaleXY/1000;
    double smooth = 0.5;
    long posOrgX = static_cast<long>(posOrg->x()* *posToPulseScaleXY);
    long posOrgY = static_cast<long>(posOrg->y()* *posToPulseScaleXY);
    long posLmtX = static_cast<long>(posLmt->x()* *posToPulseScaleXY);
    long posLmtY = static_cast<long>(posLmt->y()* *posToPulseScaleXY);

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
            ADP_StartMovePoint(crd,fifo0,posOrgX,posOrgY,spd,acc,crdPrm);
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
                posMax->setX(pluseX/ *posToPulseScaleXY);
                posMax->setY(pluseY/ *posToPulseScaleXY);
                emit UpdateDataHeadPosMax();
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
        ADP_CrdClear(crd, fifo0);//如果提前碰壁，还会出现问题，所以移动边界需要软限位，与硬限位边界至少预留1cm的距离
        ADP_LnXY(crd,posOrgX,posOrgY,spd,acc,0,fifo0);
        ADP_LnXY(crd,posOrgX,posLmtY,spd,acc,0,fifo0);
        ADP_LnXY(crd,posLmtX,posLmtY,spd,acc,0,fifo0);
        ADP_LnXY(crd,posLmtX,posOrgY,spd,acc,0,fifo0);
        ADP_LnXY(crd,posOrgX,posOrgY,spd,acc,0,fifo0);
        ADP_CrdStart(crd, fifo0);
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
            //动作：下刀
            ADP_ClrSts(AXIS_FIRST,AXIS_MAX);
            ADP_SetCrdPrm(crd, &crdPrm);
            ADP_CrdClear(crd, fifo0);
            //校准机头停在距离毛毡3mm处
//            ADP_LnXY(crd,edgeX,edgeY,spd,acc,0,fifo);
            long posGapZ = static_cast<long>((m_nKnifeMaxDeep-3) * 2000);
            ADP_BufMove(crd,m_nCtrlAxisZ,posGapZ,10,0.1,1,0);
            ADP_CrdStart(crd, fifo0);
        }
        else if(m_cdOprtStepToolPosCalib == stStep1)
        {
            //循环：查询run到位
            short run;  // 坐标系运动完成段查询变量
            long segment;  // 坐标系的缓存区剩余空间查询变量
            ADP_GetRunStateAndSegment(crd,&run,&segment,fifo0);
            //条件：
            if(run == 0 && m_stAxisRunState[m_nCtrlAxisZ-1]==0 &&m_stAxisRunState[m_nCtrlAxisA-1]==0)
            {
                //动作：提示放白纸，并且裁切十字
                QMessageBox msgBox;
                msgBox.setText(tr("请在下刀处放一张白纸"));
                msgBox.exec();

                ADP_ClrSts(AXIS_FIRST,AXIS_MAX);
                ADP_SetCrdPrm(crd, &crdPrm);
                ADP_CrdClear(crd, fifo0);
                double posRTX = posRT.x();
                double posRTY = posRT.y();
                long posCenterX = static_cast<long>((posRTX)* *posToPulseScaleXY);
                long posCenterY = static_cast<long>((posRTY)* *posToPulseScaleXY);
                long posStartX  = static_cast<long>((posRTX-mc_crossLen)* *posToPulseScaleXY);
                long posStartY  = static_cast<long>((posRTY-mc_crossLen)* *posToPulseScaleXY);
                long posStopX   = static_cast<long>((posRTX+mc_crossLen)* *posToPulseScaleXY);
                long posStopY   = static_cast<long>((posRTY+mc_crossLen)* *posToPulseScaleXY);
                long posMaxZ = static_cast<long>((m_nKnifeMaxDeep) * 2000);
                long posGapZ = static_cast<long>((m_nKnifeMaxDeep-3) * 2000);
                ADP_LnXY(crd,posStartX,posCenterY,spd,acc,0,fifo0);//移动
                ADP_BufMove(crd,m_nCtrlAxisA,0,100,0.1,1,0);//刀向
                ADP_BufMove(crd,m_nCtrlAxisZ,posMaxZ,10,0.1,1,0);//下刀
                ADP_LnXY(crd,posStopX, posCenterY,spd,acc,0,fifo0);//切割
                ADP_BufMove(crd,m_nCtrlAxisZ,posGapZ,10,0.1,1,0);//抬刀
                ADP_LnXY(crd,posCenterX,posStartY,spd,acc,0,fifo0);//移动
                ADP_BufMove(crd,m_nCtrlAxisA,2500,100,0.1,1,0);//刀向
                ADP_BufMove(crd,m_nCtrlAxisZ,posMaxZ,10,0.1,1,0);//下刀
                ADP_LnXY(crd,posCenterX, posStopY,spd,acc,0,fifo0);//切割
                ADP_BufMove(crd,m_nCtrlAxisZ,posGapZ,10,0.1,1,0);//抬刀
                ADP_LnXY(crd,posCenterX,posCenterY,spd,acc,0,fifo0);//移动
                ADP_BufMove(crd,m_nCtrlAxisA,0,100,0.1,1,0);//刀向
                ADP_CrdStart(crd, fifo0);
                //迁移：子状态：未进入；主状态：等待状态
                m_cdOprtStepToolPosCalib = stStep2;
            }
        }
        else if(m_cdOprtStepToolPosCalib == stStep2)
        {
            short run;  // 坐标系运动完成段查询变量
            long segment;  // 坐标系的缓存区剩余空间查询变量
            ADP_GetRunStateAndSegment(crd,&run,&segment,fifo0);
            //条件：十字裁切结束
            if(run == 0 && m_stAxisRunState[m_nCtrlAxisZ-1]==0 &&m_stAxisRunState[m_nCtrlAxisA-1]==0)
            {
                m_cdOprtStepToolPosCalib = stStep3;
            }
        }
        else if(m_cdOprtStepToolPosCalib == stStep3)
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
        ADP_GetRunStateAndSegment(crd,&run,&segment,fifo0);
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
void D_CtrlMach::StateMachScheduleSubCut()
{
    short crd=1,fifo0=0;
    TCrdPrm crdPrm = m_tCrdPrm;
    double spd = *idleMoveSpd * *posToPulseScaleXY;
    double acc = *idleMoveAcc * *posToPulseScaleXY/1000;
    long posOrgX = static_cast<long>(posOrg->x()* *posToPulseScaleXY);
    long posOrgY = static_cast<long>(posOrg->y()* *posToPulseScaleXY);
    //    TJogPrm jogPrm = m_tJogPrm;
    //    double smooth = 0.5;
    short run = 0;  // 坐标系运动完成段查询变量
    long segment = 0;  // 坐标系的缓存区剩余空间查询变量
    int crd1 = 8;//坐标系1比特位
    long mask = static_cast<long>(1<<crd1);//具体停止位
    long option = static_cast<long>(1<<crd1);//具体位动作

    if(m_stSubCut == stCut_NotIn)
    {
        //循环：
        //条件：
        //迁移：
        //动作：
    }
    else if(m_stSubCut == stCut_FirstIn)//外部进入
    {
        //条件
        if(!cutFile_Data->GetFileList()->isEmpty())
        {
            //跳转：跳入运行
            m_stSubCut = stCut_Run;
            ADP_SetCrdPrm(crd, &crdPrm);
            //动作：处理裁切指令
        }
        else
        {
            m_stSubCut = stCut_Stop;
        }

    }
    else if(m_stSubCut == stCut_Run)
    {
        //--
        ADP_ClrSts(AXIS_FIRST,AXIS_MAX);
        ADP_GetRunStateAndSegment(crd,&run,&segment,fifo0);
        if(run == 0 )
        {

            CutFile* tempFile = cutFile_Data->GetFileList()->at(0);
            if(m_ctCutSampleNow<tempFile->GetPage(0)->GetSampleList()->count())
            {
                // 即将把数据存入坐标系1的FIFO0中，所以要首先清除此缓存区中的数据
                TCrdData crdData[300];
                GT_InitLookAhead(1, 0, 5, 1, 500, crdData);
                ADP_CrdClear(crd, fifo0);
                if(m_ctCutSampleNow>0)
                {
                    tempFile->GetPage(0)->GetSample(m_ctCutSampleNow-1)->SetCutFinished(true);
                }
                CutSample *tempSample = tempFile->GetPage(0)->GetSample(m_ctCutSampleNow);
                for(int j=0;j<tempSample->GetNormalLineList()->count();j++)
                {
                    //此处添加下刀
                    CutLine *tempLine = tempSample->GetNormalLine(j);
                    for(int i=0;i<tempLine->GetPointList()->count();i++)
                    {
                        QPointF tempPointF = tempLine->GetPointList()->at(i);
                        long x = static_cast<long>(tempPointF.x()* *posToPulseScaleXY);
                        long y = static_cast<long>(tempPointF.y()* *posToPulseScaleXY);
//                        long xPos = x;
//                        long yPos = y;
                                                                //计算旋转绝对角度
                        ADP_LnXY(crd,x,y,spd,acc,0,fifo0); //插入插补运动Lp2
                    }
                    //此处添加半抬刀
                }
                GT_CrdData(1, nullptr, 0);
                ADP_CrdStart(crd, fifo0);
                m_ctCutSampleNow++;
//                qDebug()<<m_ctCutSampleNow;
            }
            else if(m_ctCutSampleNow == tempFile->GetPage(0)->GetSampleList()->count())
            {
                if(m_ctCutSampleNow>0)
                {
                    tempFile->GetPage(0)->GetSample(m_ctCutSampleNow-1)->SetCutFinished(true);
//                            qDebug()<<"run<<' '<<segment";
                }
                m_ctCutSampleNow = 0;
                m_stSubCut = stCut_Stop;
            }
        }
    }
    else if(m_stSubCut == stCut_Continue)//外部进入
    {

        short fifo1=1;
        if(m_cdCutStepCountine == stStepNotIn)
        {
            m_cdCutStepCountine = stStep1;
            ADP_ClrSts(AXIS_FIRST,AXIS_MAX);
            //ADP_SetCrdPrm(crd, &crdPrm); //这句不能添加，添加后，fifo中内容自动被清除
            ADP_CrdClear(crd, fifo1);
            long x = static_cast<long>(m_nPlusePause[0]);
            long y = static_cast<long>(m_nPlusePause[1]);
            ADP_LnXY(crd,4000,40000,spd,acc,0,fifo1);
            ADP_LnXY(crd,x,y,spd,acc,0,fifo1);
            ADP_CrdStart(crd, fifo1);
        }
        else if(m_cdCutStepCountine == stStep1)
        {
            ADP_GetRunStateAndSegment(crd,&run,&segment,fifo1);
            if(run == 0)
            {
                ADP_CrdStart(crd,fifo0);
                m_cdCutStepCountine = stStep2;
            }
        }
        else if(m_cdCutStepCountine == stStep2)
        {
            ADP_GetRunStateAndSegment(crd,&run,&segment,fifo0);
            if(run == 0)
            {
                ADP_CrdStart(crd,fifo0);
                m_cdCutStepCountine = stStepNotIn;
                m_stSubCut = stCut_Run;
            }
        }

    }
    else if(m_stSubCut == stCut_Pause)//外部进入
    {
        //循环：停止命令
        ADP_Stop(mask,option);
        //条件：已停止
        ADP_GetRunStateAndSegment(crd,&run,&segment,fifo0);
        if(run == 0)
        {
            //动作：记录当前位置
            ADP_GetCrdPos(1,m_nPlusePause);//必须现读
            //跳转：进入wait状态，使能运行面板
            m_stSubCut = stCut_Wait;
        }
    }
    else if(m_stSubCut == stCut_Wait)
    {
        JoggingForAxis(AXIS_X);
        JoggingForAxis(AXIS_Y);
    }
    else if(m_stSubCut == stCut_Stop)//外部进入
    {
        ADP_Stop(mask,option);
        ADP_GetRunStateAndSegment(crd,&run,&segment,fifo0);
        if(run == 0)
        {
            m_stSubCut = stCut_Finish;
            ADP_ClrSts(AXIS_FIRST,AXIS_MAX);
            ADP_SetCrdPrm(crd, &crdPrm);
            ADP_CrdClear(crd, fifo0);
            //添加模态抬刀
            ADP_LnXY(crd,posOrgX,posOrgY,spd,acc,0,fifo0);
            ADP_CrdStart(crd, fifo0);
        }
    }
    else if(m_stSubCut == stCut_Finish)
    {
        ADP_GetRunStateAndSegment(crd,&run,&segment,fifo0);
        if(run == 0)
        {
            m_stSubCut   = stCut_NotIn;
            m_stMainThis = stMain_Wait;
        }
    }
}
void D_CtrlMach::JoggingForAxis(short _axis,double _lowSpdScale)
{
    double spd = 0;
    double acc = *idleMoveAcc;
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
                spd = -*idleMoveSpd * *posToPulseScaleXY * _lowSpdScale;
            }
            else if(cmdPos&&!lmtPos)
            {
                spd =  *idleMoveSpd * *posToPulseScaleXY * _lowSpdScale;
            }
            else
            {
                spd = 0;
            }
            ADP_SetJogMode(_axis,spd,acc,smooth);
        }
    }
}
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
        m_stSubOprt  = stOprt_Fnsh;
        m_cdOprtStepToolPosCalib = stStepNotIn;
//        emit UpdateDataApronOffset(int _idApron);
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
void D_CtrlMach::EventRunSubEnterRunPuase(bool _clicked)
{
    if(_clicked)
    {
        if(m_stMainThis == stMain_Wait && m_stSubCut == stCut_NotIn)
        {
            m_stMainThis = stMain_Cut;
            m_stSubCut = stCut_FirstIn;
        }
        else if(m_stMainThis == stMain_Cut && m_stSubCut == stCut_Wait)
        {
            m_stSubCut = stCut_Continue;
        }
    }
    else
    {
        if(m_stMainThis == stMain_Cut && (m_stSubCut == stCut_Run || m_stSubCut == stCut_Continue))
        {
            m_stSubCut = stCut_Pause;
        }
    }
}
void D_CtrlMach::EventRunSubEnterStop()
{
    if(m_stMainThis == stMain_Cut)
    {
        m_stSubCut = stCut_Stop;
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
//--获取机头实时位置/mm
    //获取读取位置
    ADP_GetHeadPosRt(&posRT,*posToPulseScaleXY);//x与y一致,目前默认用y
    //限幅
    if(posRT.x()<0.0)
        posRT.setX(0.0);
    else if(posRT.x()>posMax->x())
        posRT.setX(posMax->x());
    if(posRT.y()<0.0)
        posRT.setY(0.0);
    else if(posRT.y()>posMax->y())
        posRT.setY(posMax->y());
//--获取机头实时位置/pluse
    short crd = 1;
    ADP_GetCrdPos(crd,pluseRT);
//--获取机头轴状态
    for(short i=0;i<AXIS_MAX;i++)
        m_stAxisRunState[i] = ADP_GetAxisRunState(i+1);//数组从0开始，轴号从1开始。
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
//--跳转状态读
StepCnt D_CtrlMach::GetCdtOprtStepToolPosCalib()
{
    return this->m_cdOprtStepToolPosCalib;
}
bool    D_CtrlMach::GetAxisRunState(short _axis)
{
    return  this->m_stAxisRunState[_axis-1];
}
//bool    D_CtrlMach::GetAxisRunStateAllStop()
//{
//    bool st = true;
//    for(int i=0;i<AXIS_MAX;i++)
//    {
//        if(m_stAxisRunState[i]==0)
//    }
//}

QPointF* D_CtrlMach::GetPosOrg()
{
    return this->posOrg;
}
double* D_CtrlMach::GetPosToPulseScaleXY()
{
    return this->posToPulseScaleXY;
}
QPointF* D_CtrlMach::GetPosLmt()
{
    return this->posLmt;
}
QPointF* D_CtrlMach::GetPosMax()
{
    return this->posMax;
}
double*  D_CtrlMach::GetIdleMoveSpd()
{
    return idleMoveSpd;
}
double*  D_CtrlMach::GetIdleMoveAcc()
{
    return idleMoveAcc;
}
QList<CfgApron*>* D_CtrlMach::GetCfgApronList()
{
    return cfgApronList;
}
void    D_CtrlMach::SetCtrlAxisGroup(int _idApron)//待修改和添加
{
    switch (_idApron)
    {
    case 0:
        this->m_nCtrlAxisZ = AXIS_Z1;
        this->m_nCtrlAxisA = AXIS_A1;
        this->m_emCtrlMode = ctrlModeFF;
        this->m_nKnifeMaxDeep = cfgApronList->at(_idApron)->GetKnife()->GetMaxPDDepth();
        break;
    default:
        this->m_nCtrlAxisZ = AXIS_NULL;
        this->m_nCtrlAxisA = AXIS_NULL;
        this->m_emCtrlMode = ctrlModeFF;
        this->m_nKnifeMaxDeep = 0;
    }

}
void    D_CtrlMach::SetPosOrg(QPointF *_pointF)
{
    this->posOrg = _pointF;
}

void    D_CtrlMach::SetPosToPulseScaleXY(double *_val)
{
    this->posToPulseScaleXY = _val;
}


void    D_CtrlMach::SetPosLmt(QPointF *_pointF)
{
    this->posLmt = _pointF;
}


void    D_CtrlMach::SetPosMax(QPointF* _pointF)
{
    this->posMax = _pointF;
}

void    D_CtrlMach::SetIdleMoveSpd(double* _val)
{
    idleMoveSpd = _val;
}
void    D_CtrlMach::SetIdleMoveAcc(double *_val)
{
    idleMoveAcc = _val;
}
void    D_CtrlMach::SetCfgApronList(QList<CfgApron*> *_list)
{
    this->cfgApronList = _list;
}
void    D_CtrlMach::SetCutFileData(CutFile_Data *_cutFile_Data)
{
    this->cutFile_Data = _cutFile_Data;
}
//--传出参数读
QPointF *D_CtrlMach::GetPosRT()
{
    return &this->posRT;
}
