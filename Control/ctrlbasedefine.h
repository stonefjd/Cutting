#ifndef CTRLBASEDEFINE_H
#define CTRLBASEDEFINE_H


struct DirBit
{
    int  pos;
    int  neg;
};
const int DIR_W = 0;
const int DIR_S = 1;
const int DIR_A = 2;
const int DIR_D = 3;
const int DIR_SUM = 4;
enum MainState
{
    stMain_Stop,
    stMain_Init,
    stMain_Wait,
    stMain_Oprt,
    stMain_Cut,
    stMain_Err,
};
enum SubStateInit
{
    stInit_NotIn,
    stInit_BoardInit,
    stInit_BackMachOrg,
    stInit_BackLogicOrg,
};

enum SubStateOprt
{
    stSubOprt_NotIn,
//    stSubOprt_Key,
//    stSubOprt_BtnL,
//    stSubOprt_BtnR,
//    stSubOprt_BtnU,
//    stSubOprt_BtnD,
    stSubOprt_BtnO,
    stSubOprt_Finish,
    stSubOprt_Fail,
    stSubOprt_SizeCalibration_step1,
    stSubOprt_SizeCalibration_step2,
    stSubOprt_SizeCalibration_step3,
    stSubOprt_EdgeScane_step1,
};

enum SubState_Cut
{
    stSubCut_NotIn,
    stSubCut_FirstIn,
    stSubCut_Run,
    stSubCut_Pause,
    stSubCut_Continue,
    stSubCut_Stop,
    stSubCut_Finish,
};
#endif // CTRLBASEDEFINE_H
