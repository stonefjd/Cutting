#ifndef SDKNIFECONFIG_H
#define SDKNIFECONFIG_H

#include <QObject>
#include <QWidget>
#include "SDKnife.h"
#include "SDMachine.h"
#include "SDCutToolLib.h"


class SDKnifeConfig : public QWidget
{
    Q_OBJECT
public:
    explicit SDKnifeConfig(QWidget *parent = nullptr);
    ~SDKnifeConfig(void);
signals:

public slots:
public:

    void FreeKnifes();

public:
    bool InitDefaultKnifeLib();

    bool ReadKnifeLib();
    bool SaveKnifeLib();

    //    配置文件路径
    void  SetLocalDir(QString sDir);

    bool  ReadConfigFile();
    void  CheckKnifeConfig();

public:

    //	    添加刀具
    bool    AddKnife(SDKnife* pKnife);

    //      获取已配置的刀具集合
    QList<SDKnife*>*	GetKnifes();

    //	     获取配置的刀具数量
    int      GetKnifesCount();

    //       根据Guid获取刀对象指针
    SDKnife* GetKnifeByGuid(int nGuid);

    //       根据刀名获取刀对象指针
    SDKnife* GetKnifeByName(QString sName);

    //		 根据刀座Guid获取刀对象指针
    SDKnife* GetKnifeByApronGuid(short nApronGuid);

    //       移除刀具
    bool     DeleteKnifeFromKnifes(SDKnife* pKnife);

    //		 根据刀序号获取刀对象指针
    SDKnife* GetKnifeByIndex(int nIndex);


    //		 根据刀具Guid获取刀具序号
    int      GetKnifeIndexByGuid(int nGuid);

    //       获取最大的刀具偏心距
    double   GetMaxKnifeEtc();

public:
    SDKnife* GetKnife_Pen();
    SDKnife* GetKnife_Mill();
    SDKnife* GetKnife_VCut();
    SDKnife* GetKnife_VPunch(); // VPT
    SDKnife* GetKnife_SPunch(); // SPT+VFPT
    SDKnife* GetKnife_RPunch(); //RPT+VRPT

    short    GetCutToolTypeByGuid(int nGuid);
    bool     IsCutToolType(int nGuid,short nCutToolType);

    //       判断是否为冲孔刀具 包括CUTTINGTOOL_RPUNCH+CUTTINGTOOL_VPUNCH + CUTTINGTOOL_FLAT
    bool     IsCutToolType_Punch(int nGuid);

    //		 判断是否为|字型冲孔
    bool     IsKnifeTool_SPunch(int nGuid); // SPT+ VFPT

    //		 判断是否为圆孔冲孔刀
    bool     IsKnifeTool_RPunch(int nGuid); // RPT+ VRPT

    //       判断是否为单纯的V刀。
    bool     IsKnifeTool_VPTPunch(int nGuid); // VPT
public: //Active knive

    void     LoadActiveKnifes();
    SDKnife* GetActiveKnifeByGuid(int nGuid);
    void     FreeActiveKnifes();
public: //机器信息
    SDMachine* GetMachineInfo();
    void       SetMachineInfo(SDMachine* pMachineInfo);
    bool	   ReadMachineInfo();
    bool       SaveMachineInfo();

    void	   GetAllAprons(QList<SDApron*> &vAprons);

    //         读写最后一条直线段id
    void       SaveLastCutLine();
    void       SaveLastPlotLine();
    void       LoadLastCutLine();
    int        GetLastCuttingLineId();
    int        GetLastPlottingLineId();
    int        GetLastPlottingFlag();
    int        GetLastCuttingLineSp();

public:

    //			  刀具库
    SDCutToolLib* GetCutToolLib();
public:
    //		       刀具参数方案库
//    SDKPDesignLib* GetKPDesignLib();
//    void		   GetKPDesignNames(int nSp,CStringArray &arrDesignNames);
//    QString         GetKPDesignName(int nDesignId);
public:


public: //默认切割信息

//    SDCutInfo* GetCutInfo();
//    void       SetCutInfo(SDCutInfo* pCutInfo);

    bool       ReadCutInfo();
    bool       SaveCutInfo();
//    bool       SaveCutDesign(SDCutDesign* pCutInfo,QString strSect);
//    bool       ReadCutDesign(SDCutDesign* pCutInfo,QString strSect);

//    //		   材料厚度
    void	   SetMateriaThick(double dbValue);
    double     GetMateriaThick();

public: //默认切割信息
    SDKnife*   GetDefaultKnife();
    void       SetDefaultKnife(SDKnife* pTestKnife);

    int GetPrivateProfileString(QString strSect,QString strKey,QString strDefault,QString *szBuf,QString strConfigPath);
    void WritePrivateProfileString(QString strSect,QString strKey,QString strText,QString strConfigPath);

public:


    QString			 m_sLocalDir;				//本地目录
    SDKnife			 m_stDefaultknife;			//默认刀具参数，无需关心

    SDMachine		 m_stMachineInfo;			//机器信息
//    SDCutInfo		 m_stCutInfo;				//最近一次的切割信息，设置的参数信息，暂时用不到

    SDCutToolLib     m_stCutToolLib;			//刀具库
//    SDKPDesignLib	 m_stKPDesignLib;			//刀具参数方案库，暂时用不到

    double			 m_dbMaterialThick;
private:
    QList<SDKnife*> m_stvKnifes;				//刀集合
    QList<SDKnife*> m_stvActiveKnifes;			//刀具库中的可用刀集合(刀具库中有很多种刀，但是一种机型一般只用到其中的几种而已)

};

#endif // SDKNIFECONFIG_H
