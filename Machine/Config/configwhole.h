#ifndef CONFIGWHOLE_H
#define CONFIGWHOLE_H

#include <QWidget>

#include "configmachine.h"
class ConfigWhole : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigWhole(QWidget *parent = nullptr);
public:
    ConfigMachine   mConfig;
    QList<ConfigHead*> hConfig;

signals:

public slots:
    void UpdateConfigMaxPluse(double _xPos, double _yPos);

};

#endif // CONFIGWHOLE_H
