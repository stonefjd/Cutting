#ifndef PARAMETERMACHINE_H
#define PARAMETERMACHINE_H

#include <QObject>

class ParameterMachine : public QObject
{
    Q_OBJECT
public:
    explicit ParameterMachine(QObject *parent = nullptr);

signals:

public slots:
};

#endif // PARAMETERMACHINE_H