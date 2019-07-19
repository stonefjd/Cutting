#include "machine.h"
#include "PhysicalLayer/gts.h"
static const double puntchLimitSpd = 8;
static const double puntchLimitAcc = 0.1;
static const double puntchLimitSmooth = 0.5;
static const double velRatio=2;
Machine::Machine(QObject *parent) : QObject(parent)
{
//    this->mFan_1.SetState_FanStop();
    //--------DATA structure settings--------//
    Jog.acc = puntchLimitAcc;
    Jog.dec = puntchLimitAcc;
    Jog.smooth = puntchLimitSmooth;

    memset(&crdPrm, 0, sizeof(crdPrm));
    crdPrm.dimension=2;   // 坐标系为二维坐标系
    crdPrm.synVelMax=50;  // 最大合成速度：50pulse/ms
    crdPrm.synAccMax=1;   // 最大加速度：1pulse/ms^2
    crdPrm.evenTime = 50;   // 最小匀速时间：50ms
    crdPrm.profile[0] = 1;   // 规划器1对应到X轴
    crdPrm.profile[1] = 2;   // 规划器2对应到Y轴
    crdPrm.setOriginFlag = 1;  // 表示需要指定坐标系的原点坐标的规划位置
    crdPrm.originPos[0] = 0;  // 坐标系的原点坐标的规划位置为（100, 100）
    crdPrm.originPos[1] = 0;

    //----set the knife of the machine
//    sdKnifeConfigLib.ReadConfigFile();
//    qDebug()<<sdKnifeConfigLib.GetKnifesCount();

    //--------StateMachine Setting--------//
    machine_stMainState = stMain_Init;
    machine_stSubState_Init     = stSubInit_NotIn;
    machine_stSubState_Operate  = stSubOperate_NotIn;
    machine_stSubState_Cut      = stSubCut_NotIn;
//    machine_stSubState_Stop = stSubInitNotIn;
//    machine_stSubState_Wait = stSubNotIn;
//    machine_stSubState_Pause = stSubNotIn;
//    machine_stSubState_Err = stSubNotIn;
    machine_ctSubState_Operate_Key = 0;
    machine_ctSubState_Cut_SampleFinished = 0;
    machine_ctSubState_Cut_WindowFinished = 0;
    machine_ctSubState_Cut_FileFinished = 0;

    //start the timer for the main state machine
    mTimer=new QTimer(this);
    connect(mTimer,SIGNAL(timeout()),this,SLOT(Task_10ms()));
    mTimer->start(10);

    //----
}

//    GT_SetDoBit(MC_GPO,1,0);
//    GT_SetDoBit(MC_GPO,2,0);
//    GT_SetDoBit(MC_GPO,3,0);
void Machine::MainStateRun()
{
    switch (machine_stMainState)
    {
        case stMain_Stop:
        {
            break;
        }
        case stMain_Init:
        {
            SubStateRunInitial();
            break;
        }
        case stMain_Wait:
        {

            break;
        }
        case stMain_Operate:
        {
            SubStateRunOperate();
            break;
        }
        case stMain_Cut:
        {
            SubStateRunCut();
            break;
        }
        case stMain_Err:
        {
            break;
        }
    }
}
void Machine:: SubStateRunWait()
{

}
void Machine::SubStateRunInitial()
{
    switch(machine_stSubState_Init)
    {
        case stSubInit_NotIn:
        {
            machine_stSubState_Init = stSubInit_In;
            break;
        }
        case stSubInit_In:
        {
            ADP_Disconnect();
            ADP_Connect();
            ADP_Reset();
            ADP_LoadCfgFile("E:\\01.repository\\07.QT\\GTS800.cfg");
            ADP_ClrSts(1,4);
            //----check is the knife changed
            {}

            //----set the axis on and clear axis position
            ADP_AxisOn(AXIS_X);
            ADP_AxisOn(AXIS_Y);
            ADP_ZeroPos(AXIS_X);
            ADP_ZeroPos(AXIS_Y);

            //----prepare for jog mod
            ADP_PrfJog(AXIS_X);
            ADP_PrfJog(AXIS_Y);

            ADP_SetJogPrm (AXIS_X,&Jog);
            ADP_SetJogPrm (AXIS_Y,&Jog);
            ADP_SetVel(AXIS_X, -(puntchLimitSpd));
            ADP_SetVel(AXIS_Y, -(puntchLimitSpd));
            machine_stSubState_Init = stSubInit_MOrg;
            break;
        }
        case stSubInit_MOrg:
        {
        //----get the limitState and init
            bool limitStateXNeg;
            bool limitStateYNeg;
            ADP_GetLimitState(AXIS_X,false,&limitStateXNeg);
            ADP_GetLimitState(AXIS_Y,false,&limitStateYNeg);

            if(limitStateXNeg == false)
            {
                if(ADP_GetAxisPlanRunState(AXIS_X) == false)
                {
                    ADP_ClrSts(1,4);
                    ADP_Update(AXIS_X);
                }
            }
            if(limitStateYNeg == false)
            {
                if(ADP_GetAxisPlanRunState(AXIS_Y) == false)
                {
                    ADP_ClrSts(1,4);
                    ADP_Update(AXIS_Y);
                }
            }
            if(limitStateXNeg == true && limitStateYNeg == true)
            {
                //----prepare for 2 insert mode
                ADP_ClrSts(1,4);
                ADP_ZeroPos(AXIS_X);
                ADP_ZeroPos(AXIS_Y);
                ADP_SetPrfPos(AXIS_X, 0);
                ADP_SetPrfPos(AXIS_Y, 0);

                ADP_SetCrdPrm(1, &crdPrm);
                ADP_CrdClear(1, 0);
                 // 该插补段的坐标系是坐标系1 //xy点// 该插补段的目标速度：3pulse/ms // 插补段的加速度：0.1pulse/ms^2// 终点速度为0 // 向坐标系1的FIFO0缓存区传递该直线插补数据
                ADP_LnXY(1,static_cast<long>(head0_Org->x()*head0_PulsePerMillimeter->x()),static_cast<long>(head0_Org->y()*head0_PulsePerMillimeter->y()) ,*head0_IdleMoveSpd,*head0_IdleMoveAcc,0,0);
                machine_stSubState_Init = stSubInit_LOrg;
                ADP_CrdStart(1, 0);
                break;
            }
            break;
        }
        case stSubInit_LOrg:
        {
            short run;  // 坐标系运动完成段查询变量
            long segment;  // 坐标系的缓存区剩余空间查询变量
            GT_CrdStatus(1, &run, &segment, 0);
            if(run == 0)
            {
                machine_stSubState_Init = stSubInit_Finish;
            }
            break;
        }
        case stSubInit_Finish:
        {
            machine_stMainState = stMain_Wait;
            machine_stSubState_Init = stSubInit_NotIn;
            break;
        }
        case stSubInit_Fail:
        {
            break;
        }
    }
}
void Machine::SubStateRunOperate()
{
    bool limitStateXNeg;
    bool limitStateYNeg;
    bool limitStateXPos;
    bool limitStateYPos;
    double xPos = 0;
    double yPos = 0;

    switch(machine_stSubState_Operate)
    {
    case stSubOperate_NotIn:
    case stSubOperate_Key:
    case stSubOperate_BtnL:
    case stSubOperate_BtnR:
    case stSubOperate_BtnU:
    case stSubOperate_BtnD:
    case stSubOperate_Fail:
        break;

    case stSubOperate_SizeCalibration_step1:
        ADP_GetLimitState(AXIS_X,false,&limitStateXNeg);
        ADP_GetLimitState(AXIS_Y,false,&limitStateYNeg);
        if(limitStateXNeg == true && limitStateYNeg == true)
        {
            machine_stSubState_Operate = stSubOperate_SizeCalibration_step2;
            ADP_ZeroPos(AXIS_X);
            ADP_ZeroPos(AXIS_Y);
            ADP_SetPrfPos(AXIS_X, 0);
            ADP_SetPrfPos(AXIS_Y, 0);
            ADP_ClrSts(1,4);
            ADP_SetVel(AXIS_X, puntchLimitSpd);
            ADP_SetVel(AXIS_Y, puntchLimitSpd);
            ADP_Update(AXIS_X);
            ADP_Update(AXIS_Y);
        }
        break;
    case stSubOperate_SizeCalibration_step2:
        ADP_GetLimitState(AXIS_X,true,&limitStateXPos);
        ADP_GetLimitState(AXIS_Y,true,&limitStateYPos);
        if(limitStateXPos == true && limitStateYPos == true)
        {
            machine_stSubState_Operate = stSubOperate_SizeCalibration_step3;

            ADP_GetAxisPrfPos(AXIS_X,&xPos);
            ADP_GetAxisPrfPos(AXIS_Y,&yPos);
            emit UpdateMachineMaxPluse(xPos,yPos);

            ADP_ClrSts(1,4);

            ADP_SetCrdPrm(1, &crdPrm);
            ADP_CrdClear(1, 0);
             // 该插补段的坐标系是坐标系1 //xy点// 该插补段的目标速度：3pulse/ms // 插补段的加速度：0.05pulse/ms^2// 终点速度为0 // 向坐标系1的FIFO0缓存区传递该直线插补数据
            ADP_LnXY(1,static_cast<long>(head0_Org->x()*head0_PulsePerMillimeter->x()),static_cast<long>(head0_Org->y()*head0_PulsePerMillimeter->y()),*head0_IdleMoveSpd,*head0_IdleMoveAcc,0,0);
            ADP_CrdStart(1, 0);
        }
        break;
    case stSubOperate_SizeCalibration_step3:
    case stSubOperate_EdgeScane_step1:
    case stSubOperate_BtnO:
        short run;  // 坐标系运动完成段查询变量
        long segment;  // 坐标系的缓存区剩余空间查询变量
        GT_CrdStatus(1, &run, &segment, 0);
        if(run == 0)
        {
            machine_stSubState_Operate = stSubOperate_Finish;
        }
        break;

    case stSubOperate_Finish:
        machine_stSubState_Operate = stSubOperate_NotIn;
        machine_stMainState = stMain_Wait;
    }
}
void Machine::SubStateRunCut()
{

    switch (machine_stSubState_Cut)
    {
    case stSubCut_NotIn:
        break;
    case stSubCut_FirstIn:
        {
            //do load file

            //jump to continue substate
            machine_stSubState_Cut = stSubCut_Run;
        }
        break;
    case stSubCut_Run:
        {

            if(!fileData->GetFileList()->isEmpty())
            {
                QList<CutFile*>* tempCutFileDataList = fileData->GetFileList();
                ADP_ClrSts(1,4);
                ADP_SetCrdPrm(1, &crdPrm);
                //获取当前运动状态;坐标系 1;插补运动状态 run;当前插补段数 segment; 查询的坐标系缓存区 0;
                short run;  // 坐标系运动完成段查询变量
                long segment;  // 坐标系的缓存区剩余空间查询变量
                GT_CrdStatus(1, &run,&segment,0);
                if(run == 0)
                {
                    //当前window中的sample数量进行裁切
                    if(machine_ctSubState_Cut_SampleFinished<tempCutFileDataList->at(0)->GetPage(0)->GetSampleList()->count())
                    {
//                        QThread::msleep(200);
                        // 即将把数据存入坐标系1的FIFO0中，所以要首先清除此缓存区中的数据
                        TCrdData crdData[500];
                        GT_InitLookAhead(1, 0, 5, 1, 500, crdData);
                        GT_CrdClear(1, 0);
                        if(machine_ctSubState_Cut_SampleFinished>0)
                        {
                            tempCutFileDataList->at(0)->GetPage(0)->GetSample(machine_ctSubState_Cut_SampleFinished-1)->SetCutFinished(true);
                        }
                        for(int j=0;j<tempCutFileDataList->at(0)->GetPage(0)->GetSample(machine_ctSubState_Cut_SampleFinished)->GetNormalLineList()->count();j++)
                        {
                            for(int i=0;i<tempCutFileDataList->at(0)->GetPage(0)->GetSample(machine_ctSubState_Cut_SampleFinished)->GetNormalLine(j)->GetPointList()->count();i++)
                            {
                                QPointF tempPointF = tempCutFileDataList->at(0)->GetPage(0)->GetSample(machine_ctSubState_Cut_SampleFinished)->GetNormalLine(j)->GetPointList()->at(i);
                                long x = static_cast<long>(tempPointF.x()*head0_PulsePerMillimeter->x());
                                long y = static_cast<long>(tempPointF.y()*head0_PulsePerMillimeter->y());
                                ADP_LnXY(    1,    // 该插补段的坐标系是坐标系1
                                            x,
                                            y,  // 该插补段的终点坐标(15000, 15000)
                                            30,    // 该插补段的目标速度：100pulse/ms
                                            0.1,    // 插补段的加速度：0.1pulse/ms^2
                                            0,    // 终点速度为0
                                            0);    // 向坐标系1的FIFO0缓存区传递该直线插补数据
                            }
                        }
                        GT_CrdData(1, nullptr, 0);
                        GT_CrdStart(1, 0);
                        machine_ctSubState_Cut_SampleFinished++;
                    }
                    else if(machine_ctSubState_Cut_SampleFinished == tempCutFileDataList->at(0)->GetPage(0)->GetSampleList()->count())
                    {
                        if(machine_ctSubState_Cut_SampleFinished>0)
                        {
                            tempCutFileDataList->at(0)->GetPage(0)->GetSample(machine_ctSubState_Cut_SampleFinished-1)->SetCutFinished(true);
//                            qDebug()<<"run<<' '<<segment";
                        }
                        machine_ctSubState_Cut_SampleFinished = 0;
                        machine_stSubState_Cut = stSubCut_Stop;
                    }
                }
            }
        }
        break;
    case stSubCut_Pause:
        {
            GT_Stop(1<<8, 1<<8);
        }
        break;
    case stSubCut_Continue:
        {
            short run;  // 坐标系运动完成段查询变量
            long segment;  // 坐标系的缓存区剩余空间查询变量
            GT_CrdStatus(1, &run,&segment,0);
            if(run == 0)
            {
                machine_stSubState_Cut = stSubCut_Run;
            }
        }
        break;
    case stSubCut_Stop:
        {
            //do some thing
            GT_Stop(1<<8, 1<<8);
            QThread::msleep(20);
            ADP_CrdClear(1, 0);
            ADP_SetCrdPrm(1, &crdPrm);
             // 该插补段的坐标系是坐标系1 //xy点// 该插补段的目标速度：3pulse/ms // 插补段的加速度：0.1pulse/ms^2// 终点速度为0 // 向坐标系1的FIFO0缓存区传递该直线插补数据
            ADP_LnXY(1,static_cast<long>(head0_Org->x()*head0_PulsePerMillimeter->x()),static_cast<long>(head0_Org->y()*head0_PulsePerMillimeter->y()) ,*head0_IdleMoveSpd,*head0_IdleMoveAcc,0,0);
            ADP_CrdStart(1, 0);
            //jump to the last state
            machine_stSubState_Cut = stSubCut_Finish;
        }
        break;
    case stSubCut_Finish:
        {
            short run;  // 坐标系运动完成段查询变量
            long segment;  // 坐标系的缓存区剩余空间查询变量
            GT_CrdStatus(1, &run,&segment,0);
            if(run == 0)
            {
                machine_stSubState_Cut = stSubCut_NotIn;
                machine_stMainState = stMain_Wait;
            }
        }
        break;
    }
}
void Machine::SubStateCutRunOrPause(bool _pressed)
{
    if(_pressed)
    {
        if(machine_stMainState == stMain_Wait && machine_stSubState_Cut == stSubCut_NotIn)
        {
            qDebug()<<"cut first";
            machine_stMainState = stMain_Cut;
            machine_stSubState_Cut = stSubCut_FirstIn;
        }
        else if(machine_stMainState == stMain_Cut && machine_stSubState_Cut == stSubCut_Pause)
        {
            qDebug()<<"cut continue";
            machine_stSubState_Cut = stSubCut_Continue;
            GT_CrdStart(1, 0);
        }
    }
    else
    {
        if(machine_stMainState == stMain_Cut && (machine_stSubState_Cut == stSubCut_Run || machine_stSubState_Cut == stSubCut_Continue))
        {
            qDebug()<<"cut pause";
            machine_stSubState_Cut = stSubCut_Pause;
        }
    }
}
void Machine::SubStateCutStop()
{
    if(machine_stMainState == stMain_Cut)
    {
        qDebug()<<"cut stop";
        machine_stSubState_Cut = stSubCut_Stop;
    }
}
void Machine::SubStateOpBtnEdgeScan()
{
    if(machine_stMainState == stMain_Wait && machine_stSubState_Operate == stSubOperate_NotIn)
    {
        machine_stMainState = stMain_Operate;
        machine_stSubState_Operate = stSubOperate_EdgeScane_step1;
    //        machine_stSubState_Operate = stSubOperate_E_step1;

        ADP_ClrSts(1,4);
        ADP_SetCrdPrm(1, &crdPrm);
        ADP_CrdClear(1, 0);
        // 该插补段的坐标系是坐标系1 //xy点// 该插补段的目标速度：3pulse/ms // 插补段的加速度：0.05pulse/ms^2// 终点速度为0 // 向坐标系1的FIFO0缓存区传递该直线插补数据
        ADP_LnXY(1,static_cast<long>(head0_Org->x()*head0_PulsePerMillimeter->x()),static_cast<long>(head0_Org->y()*head0_PulsePerMillimeter->y()),*head0_IdleMoveSpd,*head0_IdleMoveAcc,0,0);
        ADP_LnXY(1,static_cast<long>(head0_Org->x()*head0_PulsePerMillimeter->x()),static_cast<long>(head0_Limit->y()*head0_PulsePerMillimeter->y()),*head0_IdleMoveSpd,*head0_IdleMoveAcc,0,0);
        ADP_LnXY(1,static_cast<long>(head0_Limit->x()*head0_PulsePerMillimeter->x()),static_cast<long>(head0_Limit->y()*head0_PulsePerMillimeter->y()),*head0_IdleMoveSpd,*head0_IdleMoveAcc,0,0);
        ADP_LnXY(1,static_cast<long>(head0_Limit->x()*head0_PulsePerMillimeter->x()),static_cast<long>(head0_Org->y()*head0_PulsePerMillimeter->y()),*head0_IdleMoveSpd,*head0_IdleMoveAcc,0,0);
        ADP_LnXY(1,static_cast<long>(head0_Org->x()*head0_PulsePerMillimeter->x()),static_cast<long>(head0_Org->y()*head0_PulsePerMillimeter->y()),*head0_IdleMoveSpd,*head0_IdleMoveAcc,0,0);
        ADP_CrdStart(1, 0);
    }
}
void Machine::SubStateOpBtnReSize()
{
    qDebug()<<"scane";
    if(machine_stMainState == stMain_Wait && machine_stSubState_Operate == stSubOperate_NotIn)
    {
        machine_stMainState = stMain_Operate;
        machine_stSubState_Operate = stSubOperate_SizeCalibration_step1;

        ADP_ClrSts(1,4);
        ADP_PrfJog(AXIS_X);
        ADP_PrfJog(AXIS_Y);
        ADP_SetJogPrm (AXIS_X,&Jog);
        ADP_SetJogPrm (AXIS_Y,&Jog);
        ADP_SetVel(AXIS_X, -puntchLimitSpd);
        ADP_SetVel(AXIS_Y, -puntchLimitSpd);
        ADP_Update(AXIS_X);
        ADP_Update(AXIS_Y);
    }
}
void Machine::SubStateOpBtnPress(int id)
{
    qDebug()<<"pre"+QString::number(id);
    if(machine_stMainState == stMain_Wait && machine_stSubState_Operate == stSubOperate_NotIn)
    {
        machine_stMainState = stMain_Operate;
        Jog.acc = 0.05;
        Jog.dec = 0.05;
        Jog.smooth = 0.5;
        ADP_ClrSts(1,4);
        switch (id)
        {
        case 0:
            machine_stSubState_Operate = stSubOperate_BtnL;
            ADP_PrfJog(AXIS_X);
            ADP_SetJogPrm (AXIS_X,&Jog);
            ADP_SetVel(AXIS_X, -puntchLimitSpd*velRatio);
            ADP_Update(AXIS_X);
            break;
        case 1:
            machine_stSubState_Operate = stSubOperate_BtnR;
            ADP_PrfJog(AXIS_X);
            ADP_SetJogPrm (AXIS_X,&Jog);
            ADP_SetVel(AXIS_X, puntchLimitSpd*velRatio);
            ADP_Update(AXIS_X);
            break;
        case 2:
            machine_stSubState_Operate = stSubOperate_BtnU;
            ADP_PrfJog(AXIS_Y);
            ADP_SetJogPrm (AXIS_Y,&Jog);
            ADP_SetVel(AXIS_Y, puntchLimitSpd*velRatio);
            ADP_Update(AXIS_Y);
            break;
        case 3:
            machine_stSubState_Operate = stSubOperate_BtnD;
            ADP_PrfJog(AXIS_Y);
            ADP_SetJogPrm (AXIS_Y,&Jog);
            ADP_SetVel(AXIS_Y, -puntchLimitSpd*velRatio);
            ADP_Update(AXIS_Y);
            break;
        case 4:
            machine_stSubState_Operate = stSubOperate_BtnO;
            ADP_SetCrdPrm(1, &crdPrm);
            ADP_CrdClear(1, 0);
             // 该插补段的坐标系是坐标系1 //xy点// 该插补段的目标速度：3pulse/ms // 插补段的加速度：0.1pulse/ms^2// 终点速度为0 // 向坐标系1的FIFO0缓存区传递该直线插补数据
            ADP_LnXY(1,static_cast<long>(head0_Org->x()*head0_PulsePerMillimeter->x()),static_cast<long>(head0_Org->y()*head0_PulsePerMillimeter->y()) ,*head0_IdleMoveSpd,*head0_IdleMoveAcc,0,0);
            ADP_CrdStart(1, 0);
            break;
        }
        ADP_ClrSts(1,4);
    }
}
void Machine::SubStateOpBtnRelease(int id)
{
    qDebug()<<"rel"+QString::number(id);
    if(machine_stMainState == stMain_Operate &&
            (machine_stSubState_Operate == stSubOperate_BtnL||machine_stSubState_Operate == stSubOperate_BtnR||
             machine_stSubState_Operate == stSubOperate_BtnU||machine_stSubState_Operate == stSubOperate_BtnD||machine_stSubState_Operate == stSubOperate_BtnO)
      )
    {
        machine_stMainState = stMain_Wait;
        machine_stSubState_Operate = stSubOperate_NotIn;
        switch (id)
        {
        case 0:
            ADP_Stop(1<<(AXIS_X-1),0);
            break;
        case 1:
            ADP_Stop(1<<(AXIS_X-1),0);
            break;
        case 2:
            ADP_Stop(1<<(AXIS_Y-1),0);
            break;
        case 3:
            ADP_Stop(1<<(AXIS_Y-1),0);
            break;
        }
        ADP_ClrSts(1,4);
    }
}
void Machine::SubStateOpKeyPress(QKeyEvent event)
{
    if(!event.isAutoRepeat())
    {
        qDebug()<<"pre"+QString::number(event.key());
        if(event.key() ==Qt::Key_A ||event.key() ==Qt::Key_D ||event.key() ==Qt::Key_W ||event.key() ==Qt::Key_S)
        {
            if((machine_stMainState == stMain_Wait && machine_stSubState_Operate == stSubOperate_NotIn)
                ||(machine_stMainState == stMain_Operate && machine_stSubState_Operate == stSubOperate_Key)
                    )
            {
                machine_ctSubState_Operate_Key++;
                machine_stMainState = stMain_Operate;
                machine_stSubState_Operate = stSubOperate_Key;
                Jog.acc = 0.05;
                Jog.dec = 0.05;
                Jog.smooth = 0.5;
                ADP_ClrSts(1,4);

                switch(event.key())
                {
                case Qt::Key_A:
                    ADP_PrfJog(AXIS_X);
                    ADP_SetJogPrm (AXIS_X,&Jog);
                    ADP_SetVel(AXIS_X, -puntchLimitSpd*velRatio);
                    ADP_Update(AXIS_X);
                    break;
                case Qt::Key_D:
                    ADP_PrfJog(AXIS_X);
                    ADP_SetJogPrm (AXIS_X,&Jog);
                    ADP_SetVel(AXIS_X, puntchLimitSpd*velRatio);
                    ADP_Update(AXIS_X);
                    break;
                case Qt::Key_W:
                    ADP_PrfJog(AXIS_Y);
                    ADP_SetJogPrm (AXIS_Y,&Jog);
                    ADP_SetVel(AXIS_Y, puntchLimitSpd*velRatio);
                    ADP_Update(AXIS_Y);
                    break;
                case Qt::Key_S:
                    ADP_PrfJog(AXIS_Y);
                    ADP_SetJogPrm (AXIS_Y,&Jog);
                    ADP_SetVel(AXIS_Y, -puntchLimitSpd*velRatio);
                    ADP_Update(AXIS_Y);
                    break;
                }
            }
        }
    }
}
void Machine::SubStateOpKeyRelease(QKeyEvent event)
{
    if(!event.isAutoRepeat())
    {
        if(event.key() ==Qt::Key_A ||event.key() ==Qt::Key_D ||event.key() ==Qt::Key_W ||event.key() ==Qt::Key_S)
        {
            qDebug()<<"rel"+QString::number(event.key());
            if(machine_stMainState == stMain_Operate && machine_stSubState_Operate == stSubOperate_Key)
            {
                machine_ctSubState_Operate_Key--;
                if(machine_ctSubState_Operate_Key == 0)
                {
                    machine_stMainState = stMain_Wait;
                    machine_stSubState_Operate = stSubOperate_NotIn;
                }
                switch (event.key())
                {
                case Qt::Key_A:
                    ADP_Stop(1<<(AXIS_X-1),0);
                    break;
                case Qt::Key_D:
                    ADP_Stop(1<<(AXIS_X-1),0);
                    break;
                case Qt::Key_W:
                    ADP_Stop(1<<(AXIS_Y-1),0);
                    break;
                case Qt::Key_S:
                    ADP_Stop(1<<(AXIS_Y-1),0);
                    break;
                }
                ADP_ClrSts(1,4);
            }
        }
    }
}

void Machine::Task_10ms()
{
    MainStateRun();
//    qDebug()<<machine_stMainState<<' '<<machine_stSubState_Operate;
    GetRunningData();
}
void Machine::GetRunningData()
{
    //----x,y position
    double xPos,yPos;
    ADP_GetAxisPrfPos(AXIS_X,&xPos);
    ADP_GetAxisPrfPos(AXIS_Y,&yPos);
    emit UpdateDataHeadPosRt(static_cast<int>(xPos),static_cast<int>(yPos));
    //获取当前角度和上个周期的角度
    {
        head0_PosLast.setX(head0_Pos.x());
        head0_PosLast.setY(head0_Pos.y());
        head0_Pos.setX(static_cast<int>(xPos));
        head0_Pos.setY(static_cast<int>(yPos));
    }

    head0_MoveAngel = QLineF(head0_PosLast,head0_Pos).angle();
    //----x,y running state
    long xSts,ySts;
    ADP_GetSts(AXIS_X,&xSts);
    ADP_GetSts(AXIS_Y,&ySts);
    ((xSts&0x0400) != 0)?(mStateMotorRunningX=true):(mStateMotorRunningX=false);
    ((ySts&0x0400) != 0)?(mStateMotorRunningY=true):(mStateMotorRunningY=false);
}
//QPointF Machine::GetHeadPosRt()
//{
//    return this->head0_Pos;
//}
void Machine::Mach_SetHead0Org(QPointF *_head0_Org)
{
    this->head0_Org = _head0_Org;
}
void Machine::Mach_SetHead0PulsePerMillimeter(QPointF *_head0_PulsePerMillimeter)
{
    this->head0_PulsePerMillimeter = _head0_PulsePerMillimeter;
}
void Machine::Mach_SetHead0Limit(QPointF *_head0_Limit)
{
    this->head0_Limit = _head0_Limit;
}
//void Machine::Mach_SetCutContent(QList<fileData_t> *_fileContent)
//{
//    this->fileContent = _fileContent;
//}
void Machine::Mach_SetHead0IdleMoveSpd(double *_movSpd)
{
    this->head0_IdleMoveSpd = _movSpd;
}
void Machine::Mach_SetHead0IdleMoveAcc(double *_movAcc)
{
    this->head0_IdleMoveAcc = _movAcc;
}
uint8_t Machine::GetMachineMainState()
{
    return machine_stMainState;
}
bool Machine::GetStateMotorRunningX()
{
    return mStateMotorRunningX;
}
bool Machine::GetStateMotorRunningY()
{
    return mStateMotorRunningY;
}
