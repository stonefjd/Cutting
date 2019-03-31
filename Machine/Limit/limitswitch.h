#ifndef LIMITSWITCH_H
#define LIMITSWITCH_H

#include <QObject>
#include <PhysicalLayer/hardwareadaptor.h>

#ifdef GTSLIB
    #include <PhysicalLayer/gts.h>
#endif

class LimitSwitch : public QObject
{
    Q_OBJECT
private:
    short  axisIndex;

public:
    explicit LimitSwitch(short _index,QObject *parent = nullptr);

    short GetLimit(long *_pPos,long *_pNeg);
    int  GetIndex();
    void SetIndex(short _index);
signals:

public slots:

};

#endif // LIMITSWITCH_H
