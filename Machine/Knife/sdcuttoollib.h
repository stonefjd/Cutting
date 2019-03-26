#ifndef SDCUTTOOLLIB_H
#define SDCUTTOOLLIB_H

#include <QObject>
#include <QRgb>
#include <QSettings>
#include <QMessageBox>
#include "SDKnife.h"
class SDCutTool : public QObject
{
public:
    SDCutTool(void);
    SDCutTool(short nCutToolId);
    ~SDCutTool(void);
public:

    SDCutTool& operator = (const SDCutTool& other);

    void   FreeKnifes();

    void   LoadCutToolKey();

    bool Read(QDataStream *pFile);
    bool Save(QDataStream *pFile);

public:

    //	   刀具类型Id
    void   SetCutToolId(short nCutToolId);
    short  GetCutToolId();

    //	   刀具名关键字
    void   SetCutToolKey(QString sKey);
    QString GetCutToolKey();

    //	   刀具名
    void   SetCutToolName(QString sName);
    QString GetCutToolName();

    //	   添加子刀具
    bool   AddKnife(SDKnife* pKnife,int nIdType = 0);
    bool   AddKnifePro(SDKnife* pKnife);

    //       新生成一个子刀具
    SDKnife* NewKnife(int nIdType = 0);
    SDKnife* NewKnife(int nApronCMode,int nClr,double dbDia,double dbAngle,int nIdType = 0);

    //					获取子刀具集合
    QList<SDKnife*>*	GetSubKnifes();

    //		 根据刀id获取子刀具对象指针
    SDKnife* GetKnifeById(short nKnifeId);
    SDKnife* GetKnifeByIndex(int nIndex);
    SDKnife* GetKnifeByKey(QString sKey);

    //		 删除子刀具
    bool     DelKnifeById(short nKnifeId);
    bool     DelKnife(SDKnife* pTestKnife);
    bool     DelKnifeByKey(QString sKey);

    //	    nIdType==0第一梯段子刀具最大Id【1--20】 nIdType == 1第二梯段子刀具最大Id【21--40】,
    //      nIdType==2第三梯段子刀具最大Id【41--60】
    void    SetMaxKnifeId(short nMaxKnifeId,int nIdType=0);
    short   GetMaxKnifeId(int nIdType=0);


private:

    QList<SDKnife*>   m_stvKnifes;			//刀集合
    short			   m_nCutToolId;		//刀具类型Id
    QString			   m_sCutToolKey;		//刀具关键字
    QString			   m_sCutToolName;		//刀具名
    short			   m_nMaxKnifeId;		//最大子刀具 1--20
    short			   m_nMaxKnifeId1;		//最大子刀具 21--40
    short			   m_nMaxKnifeId2;		//最大子刀具 41--60
};

class SDCutToolLib : public QObject
{
    Q_OBJECT
public:
    explicit SDCutToolLib(QObject *parent = nullptr);
    ~SDCutToolLib(void);
signals:

public slots:
public:
    SDCutToolLib& operator = (const SDCutToolLib& other);
    void FreeCutTools();

public:
    void InitDefaultCutToolLib();


    bool ReadCutToolLib(QString sLocalDir);
    bool SaveCutToolLib(QString sLocalDir);

    //   导入系统文件，bConver--是否覆盖参数。
    bool ImportSysCutToolLib(QString sLocalDir,bool bConver);

public:

    //	 添加刀具大类
    bool AddCutTool(SDCutTool* pCutTool);

    //					获取刀具大类集合
    QList<SDCutTool*>*	GetCutTools();

    //	 获取刀具库中的所有子刀具
    void GetAllKnifes(QList<SDKnife*> &vKnifes);

    //   获取刀具库中所有的子刀具名
    void GetAllKnifeNames(QList<QString> &vNames);

    //   获取刀具库中所有的子刀具关键字
    void GetAllKnifeKeys(QList<QString> &vKeys);

    //		   获取刀具大类指针
    SDCutTool* GetCutToolById(short nCutToolId);
    SDCutTool* GetCutToolByIndex(int nIndex);
    SDCutTool* GetCutToolByKey(QString sKey);

    //         //获取刀具库中的刀
    SDKnife*   GetKnifeById(short nCutToolId, short nKnifeId);

    //         //获取刀具库中的刀
    SDKnife*   GetKnifeByGuid(int nGuid);
    SDKnife*   GetFirstCModeKnife(short nCModeId); //获取指定刀座控制方式的第一个刀具

    //	 获取刀具库中指定控制模式的所有子刀具
    void GetAllKnifesOnCMode(short nCModeId,QList<SDKnife*> &vKnifes);
public:

    //         更新刀具库中对应的刀具参数
    void       UpdateKnifeInfo(SDKnife* pKinfe);
    void       UpdateKnifeInfo(QList<SDKnife*> *pKnifes);

    int GetPrivateProfileString(QString strSect,QString strKey,QString strDefault,QString *szBuf,QString strConfigPath);
    void WritePrivateProfileString(QString strSect,QString strKey,QString strText,QString strConfigPath);

private:

    QList<SDCutTool*> m_stvCutTools;     //基础刀具集合
};

#endif // SDCUTTOOLLIB_H
