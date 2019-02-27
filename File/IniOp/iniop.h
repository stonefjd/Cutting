#ifndef INIOP_H
#define INIOP_H

#include <QDialog>
#include <QString>
#include <QSettings>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QMap>

struct HwInfo_T
{
    QString Version;
};
struct SwInfo_T
{
    QString Version;
    QString Title;
    QString Language;
};
struct MachInfo_T
{
    QString MainType;
    QString SubType;
    double Length;
    double Width;
    int BeamCount;
    int HeadCount;
    bool LimitSwitchLevel;
    double LimitSwitchLength;
};
struct MachSet_T
{
    double CutLength;
    double FeedLength;
    double FeltThickness;
};
struct FanSet_T
{
    bool ZoneEn;
    bool FreqChgEn;
    bool InhaleEn;
    bool BlowEN;
    int InhaleFreq;
    int BlowFreq;
};
struct SpeedSet_T
{
    double CutSpd;
    double CutAcc;
    double MoveSpd;
    double MoveAcc;
    double FeltMovSpd;
    double ToolDownSpd;
    double FeedSpd;
};
struct TimeSet_T
{
    int SwagingTime;
    int BlowTimg;
    int InhaleDelayTime;
};
struct AlignToolSet_T
{
    bool En;
    double Z1;
    double AbsX;
    double AbsY;
    double MaxZ;
    double ZCal;
};
struct Head1Set_T
{
    int Index;
    int SeatNum;
    QStringList Knifeilds;
    QStringList SeatOffsetX;
    QStringList SeatOffsetY;
    QStringList SeatOffsetZ;
    double AbsX;
    double AbsY;

    double LaserOffsetX;
    double LaserOffsetY;
    double FctLenX;
    double FctLenY;
    double StdLenX;
    double StdLenY;
    double ScaleX;
    double ScaleY;
};
struct RecordDetail_T
{
    bool LastPlotFlag;
    int LastCutLineId;
    int LastPlotLineId;
    QString LastFilePathList;
};
struct InitItem_T
{
    HwInfo_T    hwInfo;
    SwInfo_T    swInfo;
    MachInfo_T  machInfo;
    MachSet_T   machSet;
    FanSet_T    fanSet;
    SpeedSet_T  speedSet;
    TimeSet_T   timeSet;
    AlignToolSet_T alignToolSet;
    Head1Set_T  head1Set;
    RecordDetail_T recordDetail;
};
namespace Ui {
class IniOp;
}

class IniOp : public QDialog
{
    Q_OBJECT

public:
    explicit IniOp(QWidget *parent = nullptr);
    QString iniFilePath;
    QMap<QString, QString> iniFileMap;
    QStringList iniFileKeyList;


    void IniOp_FromIniToMap(QMap<QString, QString> *_qMap,QSettings _qSetting);
    void IniOp_FromMapToIni(QMap<QString, QString> _qMap,QSettings *_qSetting);
    void IniOp_FromMapToLbl(QMap<QString, QString> _qMap);
    void IniOp_FromLblToMap(QMap<QString, QString> *_qMap,QSettings *_qSetting);

    InitItem_T initItem;

    void IniOp_ReadFromIniFile(InitItem_T *_obj,QSettings settings);
    void IniOp_WriteToIniFile(InitItem_T _obj,QSettings *settings);
    void IniOp_ReadFromUi(InitItem_T *_obj);
    void IniOp_DisplayToUi(InitItem_T _obj);
    ~IniOp();

private:
    Ui::IniOp *ui;
};

#endif // INIOP_H
