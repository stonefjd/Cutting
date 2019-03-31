#ifndef LIMITSWITCH_H
#define LIMITSWITCH_H

#include <QObject>
#include <PhysicalLayer/hardwareadaptor.h>



class LimitSwitch : public QObject
{
    Q_OBJECT
private:
    short  axisIndex;

public:
    explicit LimitSwitch(short _index,QObject *parent = nullptr);

    short GetLimitState(short _axis,bool _polar,bool *_state);
    int  GetIndex();
    void SetIndex(short _index);
signals:

public slots:

};

#endif // LIMITSWITCH_H
