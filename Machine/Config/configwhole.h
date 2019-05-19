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
    //这样定义，割裂了机器，机头从属关系，但可以理解为两者本身耦合不紧密。
    ConfigMachine   mConfig;
    QList<ConfigHead*> hConfig;

signals:

public slots:
    void UpdateConfigMaxPluse(double _xPos, double _yPos);

};

#endif // CONFIGWHOLE_H
