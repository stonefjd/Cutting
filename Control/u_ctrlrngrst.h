#ifndef U_CTRLRNGRST_H
#define U_CTRLRNGRST_H

#include <QDialog>

#include "d_ctrlmach.h"
namespace Ui {
class U_CtrlRngRst;
}

class U_CtrlRngRst : public QDialog
{
    Q_OBJECT
private:
    Ui::U_CtrlRngRst *ui;
    D_CtrlMach*     d_ctrlMach;

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
public:
    explicit U_CtrlRngRst(QWidget *parent = nullptr);
    ~U_CtrlRngRst();

    void        SetCtrlMachObj(D_CtrlMach* _ctrlMach);
    D_CtrlMach* GetCtrlMachObj(void);
signals:
    void keyPressed(QKeyEvent);
    void keyReleased(QKeyEvent);
};

#endif // U_CTRLRNGRST_H
