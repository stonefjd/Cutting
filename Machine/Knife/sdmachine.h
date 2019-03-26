#ifndef SDMACHINE_H
#define SDMACHINE_H

#include <QObject>
#include <QRectF>
#include "SDMachineHead.h"
#include "Symbol.h"
class SDMachine : public QObject
{
    Q_OBJECT
public:
    explicit SDMachine(QObject *parent = nullptr);
    virtual ~SDMachine(void);
signals:

public slots:
public:
    SDMachine& operator = (const SDMachine& other);
    SDMachine* Copied();
    bool Copy(SDMachine* pOther);
    bool Read(QDataStream *pFile);
    bool Save(QDataStream *pFile);

    void Free();
    void FreeMachineHeads();
    void InitMachineHead();

public:
    bool ReadApron(QDataStream *pFile);
    bool SaveApron(QDataStream *pFile);
public:

    //     机器类型
    void   SetMachineType(short nType){m_nMachineType = nType;}
    short  GetMachineType(){return m_nMachineType;}

    //     机器子类型
    void   SetSubMachineType(short nType){m_nSubMachineType = nType;}
    short  GetSubMachineType(){return m_nSubMachineType;}

    //     机器长度
    void   SetMachineLength(double dbValue){m_dbMachineLen = dbValue;}
    double GetMachineLength(){return m_dbMachineLen;}

    //     机器宽度
    void   SetMachineHeight(double dbValue){m_dbMachineHeight = dbValue;}
    double GetMachineHeight(){return m_dbMachineHeight;}

    //     获取裁床矩形
    QRectF  GetMachineRect();
public:

    //	     所有刀座
    void     GetAllAprons(QList<SDApron*>& vAprons);

    //       根据机头和刀座序号获取刀座指针
    SDApron* GetApron(short nMachineIndex, short nApronIndex);

    //       根据刀座全序号获取刀座指针(包含机头的刀座序号)
    SDApron* GetApron(short nToolApron);


public:

    //      修正机头信息，检查机头数是否和指定数量一致
    void    ModifyMachineHead(int nHeadCount);

    //      添加机头
    void    AddMachineHead(SDMachineHead* pHead);
    //      机头数
    int     GetMachineHeadCount();

    QList<SDMachineHead*>* GetMachineHeads();

    //              新生成一个机头指针并追加到机头队列中
    SDMachineHead*  NewMachineHead();

    SDMachineHead*	GetFirstHead();
    SDMachineHead*	GetSecondHead();
    SDMachineHead*	GetMachineHeadByIndex(int nIndex);

    //      机头在横梁上的序号
    int		GetHeadIndexOnBeam(SDMachineHead* pHead);
private:
    int			m_nVersion;					//结构版本
    short		m_nMachineType;				//机器类型
    short		m_nSubMachineType;			//机器类型子类型
    double	    m_dbMachineLen;				//机器长度
    double      m_dbMachineHeight;			//机器宽度

    QList<SDMachineHead*> m_stMachineHeads;//机头参数列表
};

#endif // SDMACHINE_H
