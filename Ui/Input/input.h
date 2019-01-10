#ifndef INPUT_H
#define INPUT_H

#include <QObject>

class Input : public QObject
{
    Q_OBJECT
public:
    explicit Input(QObject *parent = nullptr);

signals:

public slots:
};

#endif // INPUT_H