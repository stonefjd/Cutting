#ifndef SDKNIFE_H
#define SDKNIFE_H

#include <QObject>
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QRgb>
#include <QMessageBox>
#include <QSettings>
#include <QDebug>
#include "Symbol.h"
//#include "Math/BaseMath_Dll.h"
//#include "Math/BaseStruct.h"
// 刀具id号定义
#define CUTTINGTOOL_PEN				1   // 笔     【PEN】
#define CUTTINGTOOL_ROLL			2   // 圆刀   【WCT】	Wheel Cut Tool
#define CUTTINGTOOL_EOT				3	// 电振动刀  【EOT】Electric Oscillating Tool
#define CUTTINGTOOL_POT				4   // 气动振动刀【POT】Pneumatic Oszillating Tool
#define CUTTINGTOOL_VPUNCH			5   // V型冲孔【VPT】   V Punch Tool
#define CUTTINGTOOL_SPUNCH			6	// 一字冲 【SPT】   Slit Punch Tool
#define CUTTINGTOOL_RPUNCH			7   // 圆形冲孔【RPT】  Round Punch Tool
#define CUTTINGTOOL_DRILL			8   // 钻孔   【DPT】   Drill Punch Tool
#define CUTTINGTOOL_VCUT			9	// 斜切刀 【VCT】
#define CUTTINGTOOL_SCT				10  // 刻痕刀 【SCT】   //Scoring Cutting Tool
#define CUTTINGTOOL_KCT				11  // 半刀   【KCT】   //kiss Cut
#define CUTTINGTOOL_CREASE			12  // 压痕刀 【CTT】   //Creasing Tool
#define CUTTINGTOOL_MILL			13  // 铣刀   【MCT】
#define CUTTINGTOOL_EVCT			14  // 震动斜切刀【EVCT】
#define CUTTINGTOOL_RCT			    15  // 自转刀 【RCT】   Rotation Cut Tool
#define CUTTINGTOOL_DCT				16  // 拖刀   【DCT】   Drag Cut
#define CUTTINGTOOL_PLOT			17  // 喷墨	  【PLOT】  PLOT
#define CUTTINGTOOL_REDLIGHT		18  // 红光   【RDLT】  Red Light
#define CUTTINGTOOL_LASER			19  // 激光   【LAST】  Laser
#define CUTTINGTOOL_CAMERA			20  // 摄像头 【CAMT】  Camera
#define CUTTINGTOOL_NULL			21  // 空刀   【NULT】  NULL Tool


#define MAX_TOOLAPRON				8	//刀座总数

// 刀座id号(刀具刀座的控制方式)定义(根据刀座的控制方式划分)
#define TOOLAPRON_CMODE_PEN				1   // 笔     【PEN】
#define TOOLAPRON_CMODE_ROLL			2   // 圆刀   【WCT】	圆刀【圆刀，震动刀两种控制方式相同，分为两个是为了能同时安装圆刀和震动刀刀具】
#define TOOLAPRON_CMODE_EOT				3	// 电振动刀  【EOT】
#define TOOLAPRON_CMODE_POT				4   // 气动振动刀【POT】
#define TOOLAPRON_CMODE_VPUNCH			5   // V型冲孔【VPT】   【V型冲孔,一字型型冲孔,圆形冲孔 三种控制方式相同】
#define TOOLAPRON_CMODE_SPUNCH			6	// 一字冲   【SPT】
#define TOOLAPRON_CMODE_RPUNCH			7   // 圆形冲孔【RPT】
#define TOOLAPRON_CMODE_DRILL			8   // 钻孔   【DPT】
#define TOOLAPRON_CMODE_VCUT			9	// 斜切刀 【VCT】
#define TOOLAPRON_CMODE_SCT				10  // 刻痕刀 【SCT】
#define TOOLAPRON_CMODE_KCT				11  // 半刀   【KCT】
#define TOOLAPRON_CMODE_CREASE			12  // 压痕刀 【CTT】
#define TOOLAPRON_CMODE_MILL			13  // 铣刀   【MCT】
#define TOOLAPRON_CMODE_EVCT			14  // 震动斜切刀【EVCT】
#define TOOLAPRON_CMODE_RCT			    15  // 自转刀 【RCT】
#define TOOLAPRON_CMODE_DCT				16  // 拖刀   【DCT】
#define TOOLAPRON_CMODE_PLOT			17  // 喷墨	  【PLOT】
#define TOOLAPRON_CMODE_REDLIGHT		18  // 红光   【RDLT】
#define TOOLAPRON_CMODE_LASER			19  // 激光   【LAST】
#define TOOLAPRON_CMODE_CAMERA			20  // 摄像头 【CAMT】
#define TOOLAPRON_CMODE_NULL			21  // 空刀   【NULT】

class SDKnife : public QWidget
{
    Q_OBJECT
public:
    explicit SDKnife(QWidget *parent = nullptr);
    SDKnife(short nCutToolId,short nKnifeId);
    virtual ~SDKnife(void);
signals:
public slots:
public:
	virtual SDKnife& operator = (const SDKnife& other);
	virtual SDKnife* Copied();
	virtual bool Copy(SDKnife* pOther);
    virtual bool Read(QDataStream *pFile);
    virtual bool Save(QDataStream *pFile);
    virtual bool ReadPro(QDataStream *pFile);
    virtual bool SavePro(QDataStream *pFile);
    virtual bool ReadEx(QString sConfigPath,QString sSect);
    virtual bool SaveEx(QString sConfigPath,QString sSect);

    virtual void Free();
    virtual bool IsSameParam(SDKnife* pOther);
public:
    //	   对象Id号
    void   SetCutInfoId(short nCutInfoId);
    short  GetCutInfoId();

    //	   刀具类型Id
    void   SetCutToolId(short nCutToolId);
    short  GetCutToolId();

    //	   子刀具类型Id（刀类型）
    //     比如VPUNCH刀具  1--20 VPUNCH, 21--40 SPUNCH,41-60 RPUNCH
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
    void   SetApronCMode(short nMode);
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

	//     刀具Guid(0--7位表示工具Id，8--15位表示刀id)
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

    void   LoadCutToolKey();
    void   LoadKnifeKey();
    void   InitKnifeNames();

    //	   从刀座同步偏移量
    void   UpdateOffsetFromApron(double x,double y);
public:

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
public:
    bool   IsCutToolType(short nCutToolId);
    //     判断是否为冲孔刀具
    bool   IsCutToolType_Punch();

    //     判断是否为喷墨刀具（CUTTINGTOOL_PLOTTING + CUTTINGTOOL_NEWPLOT）
    bool   IsCutToolType_Plot();

    //     判断是否为笔刀具
    bool   IsCutToolType_Pen();

public:

    //     设置默认刀具信息
    void   SetDefaultKnifeInfo(SDKnife* pTestKnife);
    int    GetPrivateProfileString(QString sSect,QString sKey,QString sDefault,QString *szBuf, QString sConfigPath);
    void   WritePrivateProfileString(QString sSect,QString sKey,QString sInfo,QString sConfigPath);

public:
	short				m_nCutInfoId;		//刀具信息Id
	short				m_nCutToolId;		//基础刀具类型 (如果m_nCutToolId == 0,表示刀具没有配置)
	short				m_nKnifeId;			//子刀具类型(如果m_nKnifeId == 0,表示是任意一种刀) 
	short				m_nApronGuid;		//刀座Guid(机头+刀座)
	short				m_nApronCMode;		//刀座控制方式
	int					m_nGuid;			//Guid值
    int 				m_nColor;			//颜色
    QString				m_sCutToolName;		//刀具大类名
    QString				m_sCutToolKey;		//刀具大类关键字
    QString				m_sKnifeKey;		//刀关键字
    QString				m_sKnifeName;		//刀具名(刀具大类名+关键参数或者刀具名+子Id号，或者用户编辑)
	double				m_dbDia;			//刀具直径
	int					m_nVersion;			//本结构版本
public:
    double				m_dbWidth;			//宽度
    double				m_dbHeight;			//高度
    double				m_dbAngle;			//角度
    double				m_dbTenacity;		//韧度

public:
    double				m_dbXEtc;			//X偏心距 (eccentricity)
    double				m_dbYEtc;			//Y偏心距 (eccentricity)

    double				m_dbXOffset;		//X偏移量
    double				m_dbYOffset;		//Y偏移量

    double				m_dbPUCstVal;		//抬刀补偿量(过切量)
    double				m_dbPDCstVal;		//落刀补偿量(过切量)
    double				m_dbToXAlixAngle;   //刀与X轴正向夹角 (度)
    double				m_dbPUAngle;		//抬刀角度 (度)
    double				m_dbPUSpeed;		//抬刀速度 (m/s)
    double				m_dbPDSpeed;		//落刀速度 (m/s)
    double				m_dbPDAcceleration;	//落刀加速度(G)
    double				m_dbMoveSpeed;		//XY运动速度(m/s)
    double				m_dbMoveAcceleration;//运动加速度(g)
    double				m_dbCornerSpeed;	//转角速度系数
    double				m_dbRotateSpeed;	//转刀速度(m/s)
    double				m_dbRotateAcceleration;	//转刀加速度(g)

    double              m_dbAlignZ;			//对刀值
    double				m_dbAlignZCal;		//对刀偏差

    double				m_dbMaxPDDepth;		//最大落刀深度(mm)
    double				m_dbMaxPUDepth;		//最大抬刀深度(mm)

    double				m_dbMaxPDDepth45;	//45度最大落刀深度(mm)

    double				m_dbWaitTimeBeforePD;	//落刀前等待时间(ms)
    double				m_dbWaitTimeAfterPD;	//落刀后等待时间(ms)

    double				m_dbWaitTimeBeforePU;	//抬刀前等待时间(ms)
    double				m_dbWaitTimeAfterPU;	//抬刀后等待时间(ms)
};

#endif // SDKNIFE_H
