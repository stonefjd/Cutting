#ifndef U_CTRLBTNDIR_H
#define U_CTRLBTNDIR_H

#include <QObject>
#include <QDockWidget>
#include <QButtonGroup>
#include <QPushButton>
#include <QLayout>

#include "d_ctrlmach.h"
class U_CtrlBtnDir : public QObject
{
    Q_OBJECT
private:
    D_CtrlMach*     d_ctrlMach;
    QDockWidget*    ctrlDockWgt;
    QButtonGroup*   btnDirGroup = new QButtonGroup;

    const int DIRECTION_CNT=9;
public:
    explicit    U_CtrlBtnDir(QObject *parent = nullptr);

    void        SetCtrlMachObj(D_CtrlMach* _ctrlMach);
    D_CtrlMach* GetCtrlMachObj(void);
    void        InitialModel(QDockWidget* _ctrlDockWgt);
signals:

public slots:
};

#endif // U_CTRLBTNDIR_H
