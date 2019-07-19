#ifndef U_CTRLTOOLPOSCALIB_H
#define U_CTRLTOOLPOSCALIB_H

#include <QDialog>

namespace Ui {
class U_CtrlToolPosCalib;
}

class U_CtrlToolPosCalib : public QDialog
{
    Q_OBJECT

public:
    explicit U_CtrlToolPosCalib(QWidget *parent = nullptr);
    ~U_CtrlToolPosCalib();

private:
    Ui::U_CtrlToolPosCalib *ui;
};

#endif // U_CTRLTOOLPOSCALIB_H
