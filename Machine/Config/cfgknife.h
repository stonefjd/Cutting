#ifndef CFGKNIFE_H
#define CFGKNIFE_H

#include <QString>
#include "cfgbasedefine.h"
// 刀具id号定义
enum KnifeId
{
    CUTTINGTOOL_NULL,           // 未装载刀具
    CUTTINGTOOL_PEN,            // 笔     【PEN】
    CUTTINGTOOL_ROLL,			// 圆刀   【WCT】	Wheel Cut Tool
    CUTTINGTOOL_EOT,			// 电振动刀  【EOT】Electric Oscillating Tool
    CUTTINGTOOL_POT,			// 气动振动刀【POT】Pneumatic Oszillating Tool
    CUTTINGTOOL_VPUNCH,			// V型冲孔【VPT】   V Punch Tool
    CUTTINGTOOL_SPUNCH,			// 一字冲 【SPT】   Slit Punch Tool
    CUTTINGTOOL_RPUNCH,			// 圆形冲孔【RPT】  Round Punch Tool
    CUTTINGTOOL_DRILL,			// 钻孔   【DPT】   Drill Punch Tool
    CUTTINGTOOL_VCUT,           // 斜切刀 【VCT】
    CUTTINGTOOL_SCT,			// 刻痕刀 【SCT】   //Scoring Cutting Tool
    CUTTINGTOOL_KCT,			// 半刀   【KCT】   //kiss Cut
    CUTTINGTOOL_CREASE,			// 压痕刀 【CTT】   //Creasing Tool
    CUTTINGTOOL_MILL,			// 铣刀   【MCT】
    CUTTINGTOOL_EVCT,			// 震动斜切刀【EVCT】
    CUTTINGTOOL_RCT,			// 自转刀 【RCT】   Rotation Cut Tool
    CUTTINGTOOL_DCT,			// 拖刀   【DCT】   Drag Cut
    CUTTINGTOOL_PLOT,			// 喷墨	  【PLOT】  PLOT
    CUTTINGTOOL_REDLIGHT,		// 红光   【RDLT】  Red Light
    CUTTINGTOOL_LASER,			// 激光   【LAST】  Laser
    CUTTINGTOOL_CAMERA,			// 摄像头 【CAMT】  Camera
};



// 刀座id号(刀具刀座的控制方式)定义(根据刀座的控制方式划分)
enum ApronCtrlMode
{
    TOOLAPRON_CMODE_NULL,		// 空刀   【NULT】
    TOOLAPRON_CMODE_PEN,        // 笔     【PEN】
    TOOLAPRON_CMODE_ROLL,       // 圆刀   【WCT】	圆刀【圆刀，震动刀两种控制方式相同，分为两个是为了能同时安装圆刀和震动刀刀具】
    TOOLAPRON_CMODE_EOT,		// 电振动刀  【EOT】
    TOOLAPRON_CMODE_POT,		// 气动振动刀【POT】
    TOOLAPRON_CMODE_VPUNCH,		// V型冲孔【VPT】   【V型冲孔,一字型型冲孔,圆形冲孔 三种控制方式相同】
    TOOLAPRON_CMODE_SPUNCH,		// 一字冲   【SPT】
    TOOLAPRON_CMODE_RPUNCH,     // 圆形冲孔【RPT】
    TOOLAPRON_CMODE_DRILL,		// 钻孔   【DPT】
    TOOLAPRON_CMODE_VCUT,		// 斜切刀 【VCT】
    TOOLAPRON_CMODE_SCT,		// 刻痕刀 【SCT】
    TOOLAPRON_CMODE_KCT,		// 半刀   【KCT】
    TOOLAPRON_CMODE_CREASE,		// 压痕刀 【CTT】
    TOOLAPRON_CMODE_MILL,		// 铣刀   【MCT】
    TOOLAPRON_CMODE_EVCT,		// 震动斜切刀【EVCT】
    TOOLAPRON_CMODE_RCT,		// 自转刀 【RCT】
    TOOLAPRON_CMODE_DCT,		// 拖刀   【DCT】
    TOOLAPRON_CMODE_PLOT,		// 喷墨	  【PLOT】
    TOOLAPRON_CMODE_REDLIGHT,	// 红光   【RDLT】
    TOOLAPRON_CMODE_LASER,		// 激光   【LAST】
    TOOLAPRON_CMODE_CAMERA,		// 摄像头 【CAMT】
};




class CfgKnife
{
private:
    void Free();

    void UpdateOffsetFromApron(double x,double y);

public:
    CfgKnife();
    CfgKnife(KnifeId nCutToolId,short nKnifeId);
    CfgKnife& operator = (const CfgKnife& other);
    bool Copy(CfgKnife* pOther);
    CfgKnife* Copied();

    void LoadCutToolKey();
    void LoadKnifeKey();
    void InitKnifeNames();
    void ReadKnifeInfo(QString sConfigPath,QString sSect);
    void WriteKnifeInfo(QString sConfigPath,QString sSect);
public:
    //	   对象Id号
    void   SetCutInfoId(short nCutInfoId);
    short  GetCutInfoId();

    //	   刀具类型Id
    void     SetCutToolId(KnifeId emCutToolId);
    KnifeId  GetCutToolId();

    //	   子刀具类型Id（刀类型）
    void   SetKnifeId(short nKnifeId);
    short  GetKnifeId();
    //	   刀具所在刀座Guid (m_nApronGuid = (nApronIndex | (nMachineHead<<8));)
    //	   刀座Guid(全序号:刀座序号+机头序号)[(0--7位表示刀座序号，8--15位表示机头序号)]
    void   SetApronGuid(short nMachineHead,short nApronIndex);
    void   SetApronGuid(short nApronGuid);
    short  GetApronGuid();

    //     刀具所在刀座的机头
    short  GetMachinIndex();

    //	   刀具所在刀座的序号
    short  GetApronIndex();

    //     刀座控制方式
    void   SetApronCMode(ApronCtrlMode nMode);
    short  GetApronCMode();

    //	   设定刀具刀座的控制方式
    void   CreadApronCMode();

    //     刀具颜色
    void   SetColor(int nClr);
    int    GetColor();

    //	   刀具大类名
    void   SetCutToolName(QString sToolName);
    QString GetCutToolName();

    //	   刀具大类关键字
    void   SetCutToolKey(QString sKey);
    QString GetCutToolKey();

    //	   刀关键字
    void   SetKnifeKey(QString sKey);
    QString GetKnifeKey();

    //	   显示名 (选刀具时显示的名字)
    void   SetKnifeName(QString sName);
    QString GetKnifeName();

    //     刀具Guid(0--5位表示工具Id，6--15位表示刀id)
    void   SetGuid(int nGuid,bool bSetKnifeId = true);
    int    GetGuid();
    void   CreateGuid();
    QString GetGuidString();

    //     刀具直径
    void   SetDia(double dbValue);
    double GetDia();

    //     X偏心距 (eccentricity)
    void   SetXEtc(double dbValue);
    double GetXEtc();

    //	   Y偏心距 (eccentricity)
    void   SetYEtc(double dbValue);
    double GetYEtc();

    //     X偏移量
    void   SetXOffset(double dbValue);
    double GetXOffset();

    //	   Y偏移量
    void   SetYOffset(double dbValue);
    double GetYOffset();

    //	   宽度
    void   SetWidth(double dbValue);
    double GetWidth();

    //	   高度
    void   SetHeight(double dbValue);
    double GetHeight();

    //      角度
    void   SetAngle(double dbValue);
    double GetAngle();

    //     韧度
    void   SetTenacity(double dbValue);
    double GetTenacity();

    //      抬刀补偿量(过切量)(mm)
    double  GetPUCstVal();
    void    SetPUCstVal(double dbValue);

    //      落刀补偿量(过切量)(mm)
    double  GetPDCstVal();
    void    SetPDCstVal(double dbValue);

    //      刀与X轴正向夹角 (度)
    double  GetXAlixAngle();
    void    SetXAlixAngle(double dbValue);

    //      抬刀角度 (度)
    double  GetPUAngle();
    void    SetPUAngle(double dbValue);

    //      抬刀速度 (m/s)
    double  GetPUSpeed();
    void    SetPUSpeed(double dbValue);

    //      落刀速度 (m/s)
    double  GetPDSpeed();
    void    SetPDSpeed(double dbValue);

    //      落刀加速度(G)
    double  GetPDAcceleration();
    void    SetPDAcceleration(double dbValue);

    //      运动速度(m/s)
    double  GetMoveSpeed();
    void    SetMoveSpeed(double dbValue);

    //      运动加速度(g)
    double  GetMoveAcceleration();
    void    SetMoveAcceleration(double dbValue);

    //      转角速度()
    double  GetCornerSpeed();
    void    SetCornerSpeed(double dbValue);


    //     转刀速度
    double GetRoateSpeed();
    void   SetRoateSpeed(double dbValue);

    //     转刀加速度
    double GetRotateAcceleration();
    void   SetRotateAcceleration(double dbValue);

    //      最大落刀深度(mm)
    double  GetMaxPDDepth();
    void    SetMaxPDDepth(double dbValue);

    double  GetMaxPDDepth45();
    void    SetMaxPDDepth45(double dbValue);

    //      最大抬刀深度(mm)
    double  GetMaxPUDepth();
    void    SetMaxPUDepth(double dbValue);

    //      对刀偏差(mm)
    double  GetAlignZCal();
    void    SetAlignZCal(double dbValue);
    double  GetAlignZ();
    void    SetAlignZ(double dbValue);

    //      落刀前等待时间(ms)
    double  GetWaitTimeBeforePD();
    void    SetWaitTimeBeforePD(double dbValue);

    //      落刀后等待时间(ms)
    double  GetWaitTimeAfterPD();
    void    SetWaitTimeAfterPD(double dbValue);

    //      抬刀前等待时间(ms)
    double  GetWaitTimeBeforePU();
    void    SetWaitTimeBeforePU(double dbValue);

    //      抬刀后等待时间(ms)
    double  GetWaitTimeAfterPU();
    void    SetWaitTimeAfterPU(double dbValue);

    //      何种刀具
    bool    IsCutToolType(KnifeId emCutToolId);
    //      判断是否为冲孔刀具
    bool    IsCutToolType_Punch();
    //      判断是否为喷墨刀具（CUTTINGTOOL_PLOTTING + CUTTINGTOOL_NEWPLOT）
    bool    IsCutToolType_Plot();
    //      判断是否为笔刀具
    bool    IsCutToolType_Pen();
public:
    short           m_nCutInfoId;		//刀具信息Id
    KnifeId         m_emCutToolId;		//基础刀具类型 (如果m_nCutToolId == 0,表示刀具没有配置)
    short           m_nKnifeId;			//子刀具类型(如果m_nKnifeId == 0,表示是任意一种刀)
    short           m_nApronGuid;		//刀座Guid(机头+刀座)
    ApronCtrlMode   m_emApronCMode;		//刀座控制方式
    int             m_nGuid;			//Guid值
    int             m_nColor;			//颜色
    QString         m_sCutToolName;		//刀具大类名
    QString         m_sCutToolKey;		//刀具大类关键字
    QString         m_sKnifeKey;		//刀关键字
    QString         m_sKnifeName;		//刀具名(刀具大类名+关键参数或者刀具名+子Id号，或者用户编辑)
    double          m_dbDia;			//刀具直径
    int             m_nVersion;			//本结构版本

    double          m_dbWidth;			//宽度
    double          m_dbHeight;			//高度
    double          m_dbAngle;			//角度
    double          m_dbTenacity;		//韧度

    double          m_dbXEtc;			//X偏心距 (eccentricity)
    double          m_dbYEtc;			//Y偏心距 (eccentricity)

    double          m_dbXOffset;		//X偏移量
    double          m_dbYOffset;		//Y偏移量

    double          m_dbPUCstVal;		//抬刀补偿量(过切量)
    double          m_dbPDCstVal;		//落刀补偿量(过切量)
    double          m_dbToXAlixAngle;   //刀与X轴正向夹角 (度)
    double          m_dbPUAngle;		//抬刀角度 (度)
    double          m_dbPUSpeed;		//抬刀速度 (m/s)
    double          m_dbPDSpeed;		//落刀速度 (m/s)
    double          m_dbPDAcceleration;	//落刀加速度(G)
    double          m_dbMoveSpeed;		//XY运动速度(m/s)
    double          m_dbMoveAcceleration;//运动加速度(g)
    double          m_dbCornerSpeed;	//转角速度系数
    double          m_dbRotateSpeed;	//转刀速度(m/s)
    double          m_dbRotateAcceleration;	//转刀加速度(g)

    double          m_dbAlignZ;			//对刀值
    double          m_dbAlignZCal;		//对刀偏差

    double          m_dbMaxPDDepth;		//最大落刀深度(mm)
    double          m_dbMaxPUDepth;		//最大抬刀深度(mm)

    double          m_dbMaxPDDepth45;	//45度最大落刀深度(mm)

    double          m_dbWaitTimeBeforePD;	//落刀前等待时间(ms)
    double          m_dbWaitTimeAfterPD;	//落刀后等待时间(ms)

    double          m_dbWaitTimeBeforePU;	//抬刀前等待时间(ms)
    double          m_dbWaitTimeAfterPU;	//抬刀后等待时间(ms)
};

#endif // CFGKNIFE_H
