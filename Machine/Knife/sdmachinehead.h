#ifndef SDMACHINEHEAD_H
#define SDMACHINEHEAD_H

#include <QObject>
#include "SDApron.h"
#include "Symbol.h"
class SDMachineHead : public QObject
{
    Q_OBJECT
public:
    explicit SDMachineHead(QObject *parent = nullptr);
    virtual ~SDMachineHead(void);
signals:

public slots:
public:
    SDMachineHead& operator = (const SDMachineHead& other);
    SDMachineHead* Copied();
    bool Copy(SDMachineHead* pOther);
    bool Read(QDataStream *pFile,int nVer);
    bool Save(QDataStream *pFile,int nVer);

    void Free();

    void InitApron();
public:

    //     所在横梁序号
    void   SetMachineBeamIndex(short nIndex){m_nMachineBeamIndex = nIndex;}
    short  GetMachineBeamIndex(){return m_nMachineBeamIndex;}

    //     机头序号
    void   SetMachineHeadIndex(short nIndex){m_nMachineHeadIndex = nIndex;}
    short  GetMachineHeadIndex(){return m_nMachineHeadIndex;}

    //	   机头原点X
    double GetHeadXOrigin(){return m_dbHeadXOrigin;}
    void   SetHeadXOrigin(double dbValue){m_dbHeadXOrigin = dbValue;}
    //     机头原点Y
    double GetHeadYOrigin(){return m_dbHeadYOrigin;}
    void   SetHeadYOrigin(double dbValue){m_dbHeadYOrigin = dbValue;}

    //	   机头位置X
    double GetHeadXPos(){return m_dbHeadXPos;}
    void   SetHeadXPos(double dbValue){m_dbHeadXPos = dbValue;}
    //     机头位置Y
    double GetHeadYPos(){return m_dbHeadYPos;}
    void   SetHeadYPos(double dbValue){m_dbHeadYPos = dbValue;}

    //     实测长度
    double GetActualLen(){return m_dbActualLen;}
    void   SetActualLen(double dbValue){m_dbActualLen = dbValue;}
    //     预测长度
    double GetExpectLen(){return m_dbExpectLen;}
    void   SetExpectLen(double dbValue){m_dbExpectLen = dbValue;}

    //     X向系数
    double GetXScale(){return m_dbXScale;}
    void   SetXScale(double dbValue){m_dbXScale = dbValue;}

    //     实测宽度
    double GetActualWidth(){return m_dbActualWidth;}
    void   SetActualWidth(double dbValue){m_dbActualWidth = dbValue;}
    //     预测宽度
    double GetExpectWidth(){return m_dbExpectWidth;}
    void   SetExpectWidth(double dbValue){m_dbExpectWidth = dbValue;}
    //     Y向系数
    double GetYScale(){return m_dbYScale;}
    void   SetYScale(double dbValue){m_dbYScale = dbValue;}

    //     实测长度
    double GetPlotActualLen(){return m_dbPlotActualLen;}
    void   SetPlotActualLen(double dbPlotValue){m_dbPlotActualLen = dbPlotValue;}
    //     预测长度
    double GetPlotExpectLen(){return m_dbPlotExpectLen;}
    void   SetPlotExpectLen(double dbPlotValue){m_dbPlotExpectLen = dbPlotValue;}

    //     X向系数
    double GetPlotXScale(){return m_dbPlotXScale;}
    void   SetPlotXScale(double dbPlotValue){m_dbPlotXScale = dbPlotValue;}

    //     实测宽度
    double GetPlotActualWidth(){return m_dbPlotActualWidth;}
    void   SetPlotActualWidth(double dbPlotValue){m_dbPlotActualWidth = dbPlotValue;}

    //     预测宽度
    double GetPlotExpectWidth(){return m_dbPlotExpectWidth;}
    void   SetPlotExpectWidth(double dbPlotValue){m_dbPlotExpectWidth = dbPlotValue;}

    //     Y向系数
    double GetPlotYScale(){return m_dbPlotYScale;}
    void   SetPlotYScale(double dbPlotValue){m_dbPlotYScale = dbPlotValue;}


    //     切割范围(长度)
    double GetCuttingLen(){return m_dbCuttingLen;}
    void   SetCuttingLen(double dbValue){m_dbCuttingLen = dbValue;}

    //     切割范围(宽度)
    double GetCuttingHeight(){return m_dbCuttingHeight;}
    void   SetCuttingHeight(double dbValue){m_dbCuttingHeight = dbValue;}

    //     笔偏移X
    double GetPenXOffset(){return m_dbPenOffsetX;}
    void   SetPenXOffset(double dbValue){m_dbPenOffsetX = dbValue;}

    //     笔偏移Y
    double GetPenYOffset(){return m_dbPenOffsetY;}
    void   SetPenYOffset(double dbValue){m_dbPenOffsetY = dbValue;}

    //     红光定位 X偏移
    double GetGlowXOffset(){return m_dbGlowOffsetX;}
    void   SetGlowXOffset(double dbValue){m_dbGlowOffsetX = dbValue;}

    //     红光定位 Y偏移
    double GetGlowYOffset(){return m_dbGlowOffsetY;}
    void   SetGlowYOffset(double dbValue){m_dbGlowOffsetY = dbValue;}

    //     摄像头 X偏移
    double GetCameraXOffset(){return m_dbCameraOffsetX;}
    void   SetCameraXOffset(double dbValue){m_dbCameraOffsetX = dbValue;}

    //     摄像头 Y偏移
    double GetCameraYOffset(){return m_dbCameraOffsetY;}
    void   SetCameraYOffset(double dbValue){m_dbCameraOffsetY = dbValue;}

    //     摄像头 高度
    double GetCameraHeight(){return m_dbCameraHeight;}
    void   SetCameraHeight(double dbValue){m_dbCameraHeight = dbValue;}

    //     切割模式
    short  GetCuttingMode(){return m_nCuttingMode;}
    void   SetCuttingMode(short nValue){m_nCuttingMode = nValue;}

    //     减震模式
    short  GetDecoupleMode(){return m_nDecoupleMode;}
    void   SetDecoupleMode(short nValue){m_nDecoupleMode = nValue;}

    //     送料长度
    double GetFeedLen(){return m_dbFeedLen;}
    void   SetFeedLen(double dbValue){m_dbFeedLen = dbValue;}

    //     送料速度(m/s)
    double GetFeedSpeed(){return m_dbFeedSpeed;}
    void   SetFeedSpeed(double dbValue){m_dbFeedSpeed = dbValue;}

    double GetFeedJ(){return m_dbFeedJ;}
    void   SetFeedJ(double dbValue){m_dbFeedJ = dbValue;}

    //	   压料时间(s)
    double GetSwagingTime(){return m_dbSwagingTime;}
    void   SetSwagingTime(double dbValue){m_dbSwagingTime = dbValue;}

    //吹气时间
    double GetSwagingTime1(){return m_dbSwagingTime1;}
    void   SetSwagingTime1(double dbValue){m_dbSwagingTime1 = dbValue;}

    //放料开始提前时间
    double GetSwagingTime2(){return m_dbSwagingTime2;}
    void   SetSwagingTime2(double dbValue){m_dbSwagingTime2 = dbValue;}

    //放料结束提前时间
    double GetSwagingTime3(){return m_dbSwagingTime3;}
    void   SetSwagingTime3(double dbValue){m_dbSwagingTime3 = dbValue;}

    //     空走速度 (m/s)
    double GetIdleMoveSpeed(){return m_dbIdleMoveSpeed;}
    void   SetIdleMoveSpeed(double dbValue){m_dbIdleMoveSpeed = dbValue;}

    //     空走加速度(G)
    double GetIdleMoveAcceleration(){return m_dbIdleMoveAcceleration;}
    void   SetIdleMoveAcceleration(double dbValue){m_dbIdleMoveAcceleration = dbValue;}

    //     扫描长度
    double GetScanLen(){return m_dbScanLen;}
    void   SetScanLen(double dbValue){m_dbScanLen = dbValue;}

    //     扫描速度 (m/s)
    double GetScanSpeed(){return m_dbScanSpeed;}
    void   SetScanSpeed(double dbValue){m_dbScanSpeed = dbValue;}

    //     扫描加速度(G)
    double GetScanAcceleration(){return m_dbScanAcceleration;}
    void   SetScanAcceleration(double dbValue){m_dbScanAcceleration = dbValue;}



    //     减速边界
    double GetReducerEdge(){return m_dbReducerEdge;}
    void   SetReducerEdge(double dbValue){m_dbReducerEdge = dbValue;}

    //     吸气延迟时间(ms)
    double GetInhaleDelayTime(){return m_dbInhaleDelayTime;}
    void   SetInhaleDelayTime(double dbValue){m_dbInhaleDelayTime = dbValue;}

    //     最后一条切割的直线段id
    long   GetLastCutLineId(){return m_nLastCutLineId;}
    void   SetLastcutLineId(long nId){m_nLastCutLineId = nId;}

    //     最后一条切割的直线段id
    long   GetLastPlotLineId(){return m_nLastPLotLineId;}
    void   SetLastPlotLineId(long nId){m_nLastPLotLineId = nId;}
    int	   GetLastPlotFlag(){return m_nLastPlotFlag;}
    void   SetLastPlotFlag(int nId){m_nLastPlotFlag = nId;}

    //     机头是否有效
    void   SetValidFlag(bool bValue){m_bValid = bValue;}
    bool   IsValidFlag(){return m_bValid;}

    //     机头是否允许输出
    void   SetEnablePlot(bool bValue){m_bEnablePlot = bValue;}
    bool   IsEnablePlot(){return m_bEnablePlot;}
public:

    //	   临时变量，记录机头实际偏移
    double GetHeadFactXOffset(){return m_dbHeadFactXOffset;}
    void   SetHeadFactXOffset(double dbValue){m_dbHeadFactXOffset = dbValue;}

    double GetHeadFactYOffset(){return m_dbHeadFactYOffset;}
    void   SetHeadFactYOffset(double dbValue){m_dbHeadFactYOffset = dbValue;}
public:

    void     AddApron(SDApron* pApron);
    SDApron* AddApronIndex(int nApronIndex);
    SDApron* AddApronIndex(int nApronIndex,short nApronCMode);
    SDApron* GetApronByApronIndex(int nApronIndex);
    int		 FindApron(int nApronIndex);
    void     FreeAprons();
    void     UpdateOnlineAprons(QList<SDApron*> &vAprons);
    void     CheckAprons();
    int		 GetApronsCount();
    QList<SDApron*>* GetAprons();
private:
    QList<SDApron*> m_vstAprons;	//可用刀座列表
private:
    short  m_nMachineBeamIndex;		//所在横梁序号
    short  m_nMachineHeadIndex;     //机头序号
    double m_dbHeadXOrigin;			//机头原点X
    double m_dbHeadYOrigin;			//机头原点Y

    double m_dbHeadXPos;			//机头位置X
    double m_dbHeadYPos;			//机头位置Y

    double m_dbActualLen;			//实测长度
    double m_dbExpectLen;			//预测长度
    double m_dbXScale;				//X向系数

    double m_dbActualWidth;			//实测宽度
    double m_dbExpectWidth;			//预测宽度
    double m_dbYScale;				//Y向系数

    double m_dbPlotActualLen;		//打印实测长度
    double m_dbPlotExpectLen;		//打印预测长度
    double m_dbPlotXScale;			//打印X向系数

    double m_dbPlotActualWidth;		//打印实测宽度
    double m_dbPlotExpectWidth;		//打印预测宽度
    double m_dbPlotYScale;			//打印Y向系数

    double m_dbCuttingLen;			//切割范围(长度)
    double m_dbCuttingHeight;		//切割范围(宽度)

    double m_dbPenOffsetX;			//笔偏移X
    double m_dbPenOffsetY;			//笔偏移Y

    double m_dbGlowOffsetX;			//红光定位 X偏移
    double m_dbGlowOffsetY;			//红光定位 Y偏移

    double m_dbCameraOffsetX;		//摄像头 X偏移
    double m_dbCameraOffsetY;		//摄像头 Y偏移
    double m_dbCameraHeight;		//摄像头 高度

    short  m_nCuttingMode;			//切割模式
    short  m_nDecoupleMode;			//减震模式

    double m_dbFeedLen;				//送料长度
    double m_dbFeedSpeed;			//送料速度(m/s)
    double m_dbSwagingTime;			//压料时间(s)
    double m_dbSwagingTime1;		//吹气时间(s)
    double m_dbSwagingTime2;		//放料开始提前时间(s)
    double m_dbSwagingTime3;		//放料结束提前时间(s)
    double m_dbFeedJ;

    double m_dbScanLen;				//扫描长度
    double m_dbScanSpeed;			//扫描速度(m/s)
    double m_dbScanAcceleration;	//扫描加速度(G)

    double m_dbIdleMoveSpeed;		//空走速度 (m/s)
    double m_dbIdleMoveAcceleration;//空走加速度(G)


    double m_dbReducerEdge;			//减速边界

    double m_dbInhaleDelayTime;		//吸气延迟时间(ms)
private:
    long    m_nLastCutLineId;       //切割的最后一条直线段的序号
    long    m_nLastPLotLineId;       //打印的最后一条直线段的序号
    int     m_nLastPlotFlag;		 //打印标记
    bool    m_bValid;				// 标志机头是否有效 true--有效，false--无效
    bool    m_bEnablePlot;			// 标志机头是否能输出 true--能输出
public:
    double m_dbHeadFactXOffset;		//临时用变量 记录机头实际偏移量
    double m_dbHeadFactYOffset;
};

#endif // SDMACHINEHEAD_H
