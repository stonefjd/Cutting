#ifndef CUTLINE_H
#define CUTLINE_H

#include <QObject>
#include <QList>
#include <QPolygon>

class CutLine : public QObject
{
    Q_OBJECT
private:
    QPolygonF*      m_qpgLine  = new QPolygonF;
    QList<double>*  m_qldAngle = new QList<double>;
    double          m_dDepth;//0代表最深, 1代表离毛毡1mm
    int             m_nKnifeGuid;
    QString         m_qstrLable;
    QPointF         m_qpKnifeOffset;
public:
    explicit CutLine(QObject *parent = nullptr);

    void    AddCutPoint(QPointF _point,double _angle);

    QPolygonF* GetPointList();

    void    SetDepth(double _depth);
    double  GetDepth(void);

    void    SetKnifeGuid(int _guid);
    int     GetKnifeGuid(void);

    void    SetLineLable(QString _lineLable);
    QString GetLineLable(void);

    void    SetKnifeOffset(QPointF _pointF);
    QPointF GetKnifeOffset();
signals:

public slots:
};

#endif // CUTLINE_H
