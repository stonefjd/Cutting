#ifndef MACHINE_H
#define MACHINE_H

#include <QObject>

#include "Fan/fan.h"
class Machine : public QObject
{
    Q_OBJECT
public:
    explicit Machine(QObject *parent = nullptr);
    Fan mFan_1;
signals:

public slots:
};

#endif // MACHINE_H
