#ifndef CFGLIB_H
#define CFGLIB_H

#include <QObject>
#include <QDebug>
#include "cfgbasedefine.h"
#include "cfgknife.h"
#include "cfgcuttool.h"
class CfgLib
{
private:
    QList<CfgCutTool*> m_stvCutTools;
    QString m_sLibCfgPath;
    void FreeCutTools();
public:
    CfgLib();
    ~CfgLib(void);

    bool ReadCutToolLib();
    bool SaveCutToolLib();


public:
    //	添加刀具大类
    bool AddCutTool(CfgCutTool* pCutTool);

    //  获取刀具大类集合
    QList<CfgCutTool*>*	GetCutTools();

    //	获取刀具库中的所有子刀具
    void GetAllKnifes(QList<CfgKnife*> &vKnifes);

    //  获取刀具库中所有的子刀具名
    void GetAllKnifeNames(QList<QString> &vNames);


    //  获取刀具库中所有的子刀具关键字
    void GetAllKnifeKeys(QList<QString> &vKeys);

    //  获取刀具大类指针
    CfgCutTool* GetCutToolById(short nCutToolId);
    CfgCutTool* GetCutToolByIndex(int nIndex);
    CfgCutTool* GetCutToolByKey(QString sKey);

    //  获取刀具库中的刀
    CfgKnife*   GetKnifeById(short nCutToolId, short nKnifeId);

    //  获取刀具库中的刀
    CfgKnife*   GetKnifeByGuid(int nGuid);
    CfgKnife*   GetFirstCModeKnife(short nCModeId); //获取指定刀座控制方式的第一个刀具

    //  获取刀具库中指定控制模式的所有子刀具
    void GetAllKnifesOnCMode(short nCModeId,QList<CfgKnife*> &vKnifes);
    //  更新刀具库中对应的刀具参数
    void UpdateKnifeInfo(CfgKnife* pKinfe);
    void UpdateKnifeInfo(QList<CfgKnife*> *pKnifes);

};

#endif // CFGLIB_H
