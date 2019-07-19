#ifndef U_CTRLTOOLPOSCALIB_H
#define U_CTRLTOOLPOSCALIB_H

#include <QDialog>
#include <QMessageBox>
#include "d_ctrlmach.h"
namespace Ui {
class U_CtrlToolPosCalib;
}

class U_CtrlToolPosCalib : public QDialog
{
    Q_OBJECT
private:
    Ui::U_CtrlToolPosCalib *ui;
    D_CtrlMach*     d_ctrlMach;

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
public:
    explicit U_CtrlToolPosCalib(QWidget *parent = nullptr);
    ~U_CtrlToolPosCalib();

    void        SetCtrlMachObj(D_CtrlMach* _ctrlMach);
    D_CtrlMach* GetCtrlMachObj(void);

    bool InitialModel(int _apronId, double deep);

signals:
    void keyPressed(QKeyEvent);
    void keyReleased(QKeyEvent);
};

#endif // U_CTRLTOOLPOSCALIB_H
