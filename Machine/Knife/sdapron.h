#ifndef SDAPRON_H
#define SDAPRON_H

#include <QObject>
#include "SDKnife.h"
#include "Symbol.h"
class SDApron : public QObject
{
    Q_OBJECT
public:
    explicit SDApron(QObject *parent = nullptr);
    virtual ~SDApron(void);
signals:

public slots:

public:
    SDApron& operator = (const SDApron& other);
    SDApron* Copied();
    bool Copy(SDApron* pOther);
    bool Read(QDataStream *pFile,int nVer);
    bool Save(QDataStream *pFile,int nVer);

    void Free();
public:

    //    刀座序号
    void  SetApronIndex(short nApronIndex);
    short GetApronIndex();

    //    机头序号
    void  SetMachineIndex(short nMachineIndex);
    short GetMachineIndex();

    //    刀座Guid(全序号:刀座序号+机头序号)[(0--7位表示刀座序号，8--15位表示机头序号)]
    short GetApronGuid();

    //    刀座控制方式
    void  SetApronCMode(short nCMode);
    short GetApronCMode();


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
    short		m_nApronIndex;		//刀座序号
    short       m_nMachineIndex;    //机头序号
    short		m_nApronCMode;		//控制方式
    int			m_nKnifeGuid;		//刀具Guid
    double      m_dbXOffset;		//刀座偏移量X。增加此变量的目的是为了更换刀具后保留刀座的偏移量，
    double      m_dbYOffset;		//刀座偏移量Y。

};

#endif // SDAPRON_H
