#ifndef CUTLINE_H
#define CUTLINE_H

#include <QObject>
#include <QList>
#include <QPolygon>

class CutLine : public QObject
{
    Q_OBJECT
private:
    QPolygonF       m_pgLine;
    QList<double>   m_ldAngle;
    double          m_dDepth;//0代表最深, 1代表离毛毡1mm
    int             m_nKnifeGuid;
    QString         m_strLable;
public:
    explicit CutLine(QObject *parent = nullptr);

    void    AddPoint(QPointF _point,double _angle);

    void    SetDepth(double _depth);
    double  GetDepth(void);

    void    SetKnifeGuid(int _guid);
    int     GetKnifeGuid(void);

    void    SetLineLable(QString _lineLable);
    QString GetLineLable(void);
signals:

public slots:
};

#endif // CUTLINE_H
