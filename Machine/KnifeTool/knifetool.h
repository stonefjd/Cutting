#ifndef KNIFETOOL_H
#define KNIFETOOL_H

#include <QObject>
#include <QPointF>

#define TOOLNUM 5

struct ToolSeatOffset_T
{
    double x;
    double y;
    double h;
};
struct LaserAbsOffset_T
{
    double x;
    double y;
};
struct ToolSpeed_T
{
    double cuttingSpd;
    double cuttingAcc;
    double movingSpd;
    double movingAcc;
    double desktopSpd;
    double toolDown;
};

class KnifeTool : public QObject
{
    Q_OBJECT
private:
    int idTool;
    int idSeat;
    QPointF offsetXY;
    int offsetZ;
    int state;
public:
    explicit KnifeTool(QObject *parent = nullptr);

    int GetId_Tool();
    int GetId_Seat();
    int GetState();
    QPointF GetOffset_XY();
    int     GetOffset_Z();

    void SetId_Tool(int id);
    void SetId_Seat(int id);
    void SetState_Enable();
    void SetState_Disable();
    void SetOffset_XY(QPointF offset);
    void SetOffset_Z(int offset);
signals:
    void Signal_Action_();
public slots:
};

#endif // KNIFETOOL_H
