#ifndef ROUTE_H
#define ROUTE_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QDebug>
#include <QTranslator>
class Route : public QObject
{
    Q_OBJECT
public:
    explicit Route(QObject *parent = nullptr);
    void        PathDir_Chose();
    QStringList PathDir_Get();
private:
    QStringList PathDir;

signals:

public slots:
};

#endif // ROUTE_H
