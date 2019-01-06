#ifndef DESKTOP_H
#define DESKTOP_H

#include <QObject>

struct DesktopHOffset_T
{
    double h;
};
struct DesktopSizeCut_T
{
    double x;
    double y;
};

class Desktop : public QObject
{
    Q_OBJECT
public:
    explicit Desktop(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DESKTOP_H
