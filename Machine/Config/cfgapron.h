#ifndef CFGAPRON_H
#define CFGAPRON_H

#include <QObject>
#include <QDebug>

#include "cfgknife.h"
class CfgApron
{
public:
    CfgApron();
public:
    void GetApronInfo(int index);
    //    刀座序号
    void  SetApronIndex(int nApronIndex);
    int   GetApronIndex();

    void  SetApronUse(int _use);
    int   GetApronUse(void);

    //    机头序号
//    void  SetApronHeadIndex(short nMachineIndex);
//    short GetApronHeadeIndex();

//    //    刀座控制方式
//    void  SetApronCMode(short nCMode);
//    short GetApronCMode();

    //    刀座配置的刀具Guid
    void  SetKnifeGuid(int nGuid);
    int   GetKnifeGuid();

    void        SetKnife(CfgKnife *_knife);
    CfgKnife*   GetKnife();
    //     X偏移量，
    //     增加此变量的目的是为了更换刀具后保留刀座的偏移量
    //	   例如，刀座1设置了圆刀，后来刀座1没有装刀具，再后来又装了刀具，此时如果刀座1保留了偏移量，就不用调试刀具偏移量了。
    void   SetXOffset(double dbValue);
    double GetXOffset();

    //	   Y偏移量
    void   SetYOffset(double dbValue);
    double GetYOffset();

private:
    int 		apronIndex; 		//刀座序号
    int         apronUsed;
    int 		apronCtrlMode;		//控制方式
    int			apronKnifeGuid;		//刀具Guid
    double      apronOffsetX;		//刀座偏移量X。增加此变量的目的是为了更换刀具后保留刀座的偏移量，
    double      apronOffsetY;		//刀座偏移量Y。
    CfgKnife    *knifeInApron;

    QString apronCfgPath;
};

#endif // CFGAPRON_H
