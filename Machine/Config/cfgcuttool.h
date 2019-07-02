#ifndef CFGCUTTOOL_H
#define CFGCUTTOOL_H

#include <QObject>

#include "cfgknife.h"
class CfgCutTool
{
private:
    QList<CfgKnife*>   m_stvKnifes;			//刀集合
    KnifeId			   m_emCutToolId;		//刀具类型Id
    QString			   m_sCutToolKey;		//刀具关键字
    QString			   m_sCutToolName;		//刀具名
    short			   m_nMaxKnifeId;		//最大子刀具 1--20
    short			   m_nMaxKnifeId1;		//最大子刀具 21--40
    short			   m_nMaxKnifeId2;		//最大子刀具 41--60

    void   FreeKnifes();
public:
    CfgCutTool();
    CfgCutTool(short nCutToolId);
    ~CfgCutTool(void);
    void   LoadCutToolKey();

    CfgCutTool& operator = (const CfgCutTool& other);
    //	   刀具类型Id
    void   SetCutToolId(KnifeId nCutToolId);
    KnifeId  GetCutToolId();

    //	   刀具名关键字
    void   SetCutToolKey(QString sKey);
    QString GetCutToolKey();

    //	   刀具名
    void   SetCutToolName(QString sName);
    QString GetCutToolName();

    //	   添加子刀具
    bool   AddKnife(CfgKnife* pKnife,int nIdType = 0);
    bool   AddKnifePro(CfgKnife* pKnife);

    //       新生成一个子刀具
    CfgKnife* NewKnife(int nIdType = 0);
    CfgKnife* NewKnife(int nApronCMode,int nClr,double dbDia,double dbAngle,int nIdType = 0);

    //					获取子刀具集合
    QList<CfgKnife*>*	GetSubKnifes();

    //		 根据刀id获取子刀具对象指针
    CfgKnife* GetKnifeById(short nKnifeId);
    CfgKnife* GetKnifeByIndex(int nIndex);
    CfgKnife* GetKnifeByKey(QString sKey);
    CfgKnife* GetKnifeByName(QString sName);

    //		 删除子刀具
    bool     DelKnifeById(short nKnifeId);
    bool     DelKnife(CfgKnife* pTestKnife);
    bool     DelKnifeByKey(QString sKey);

    //	    nIdType==0第一梯段子刀具最大Id【1--20】 nIdType == 1第二梯段子刀具最大Id【21--40】,
    //      nIdType==2第三梯段子刀具最大Id【41--60】
    void    SetMaxKnifeId(short nMaxKnifeId,int nIdType=0);
    short   GetMaxKnifeId(int nIdType=0);

};

#endif // CFGCUTTOOL_H
