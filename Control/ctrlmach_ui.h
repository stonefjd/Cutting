#ifndef CTRLMACH_UI_H
#define CTRLMACH_UI_H

#include <QObject>
#include <QDockWidget>
#include <QButtonGroup>
#include <QPushButton>
#include <QLayout>
#include "ctrlmach.h"
class CtrlMach_UI : public QObject
{
    Q_OBJECT
private:
    CtrlMach*       ctrlMach;
    QDockWidget*    ctrlDockWgt;
    QButtonGroup*   btnDirGroup = new QButtonGroup;

    const int DIRECTION_CNT=9;
public:
    explicit CtrlMach_UI(QObject *parent = nullptr);

    void        SetCtrlMachObj(CtrlMach* _ctrlMach);
    CtrlMach*   GetCtrlMachObj(void);

    void        InitialModel(QDockWidget* _ctrlDockWgt);

signals:

public slots:
};

#endif // CTRLMACH_UI_H
