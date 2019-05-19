#ifndef CONFIGAPRON_H
#define CONFIGAPRON_H

#include <QWidget>

class configApron : public QWidget
{
    Q_OBJECT
public:
    explicit configApron(QWidget *parent = nullptr);

public:
    //    刀座序号
    void  SetApronIndex(int nApronIndex);
    int   GetApronIndex();

    //    机头序号
    void  SetApronHeadIndex(short nMachineIndex);
    short GetApronHeadeIndex();

//    //    刀座Guid(全序号:刀座序号+机头序号)[(0--7位表示刀座序号，8--15位表示机头序号)]
//    short GetApronGuid();

//    //    刀座控制方式
//    void  SetApronCMode(short nCMode);
//    short GetApronCMode();


    //    刀座配置的刀具Guid
    void  SetKnifeGuid(int nGuid);
    int   GetKnifeGuid();

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
    short       apronHeadIndex;     //机头序号
//    short		apronCtrlMode;		//控制方式
    int			apronKnifeGuid;		//刀具Guid
    double      apronXOffset;		//刀座偏移量X。增加此变量的目的是为了更换刀具后保留刀座的偏移量，
    double      apronYOffset;		//刀座偏移量Y。

signals:

public slots:
};

#endif // CONFIGAPRON_H
