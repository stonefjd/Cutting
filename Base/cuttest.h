#ifndef CUTTEST_H
#define CUTTEST_H

#include <QObject>
#include "cutsample.h"
class CutTest : public QObject
{
    Q_OBJECT
public:
    explicit CutTest(QObject *parent = nullptr);

signals:

public slots:

private:
    CutSample *sample;
};

#endif // CUTTEST_H
