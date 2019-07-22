#ifndef U_CTRLTOOLPOSCALIB_H
#define U_CTRLTOOLPOSCALIB_H

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
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

//对刀前原始位置
    QPointF posOrgCalib;
//对刀刀座编号
    int     idApron;
//UI界面组件
    QLineEdit   *lEdtPosX = new QLineEdit;
    QLineEdit   *lEdtPosY = new QLineEdit;
    QLabel      *lbPosX   = new QLabel(tr("x偏移"));
    QLabel      *lbPosY   = new QLabel(tr("Y偏移"));
    QPushButton *btnSure  = new QPushButton(tr("确认"));
    QPushButton *btnCancel= new QPushButton(tr("取消"));
private:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
public:
    explicit U_CtrlToolPosCalib(QWidget *parent = nullptr);
    ~U_CtrlToolPosCalib();

    void        SetCtrlMachObj(D_CtrlMach* _ctrlMach);
    D_CtrlMach* GetCtrlMachObj(void);

    bool InitialModel(int _idApron);

signals:
    void keyPressed(QKeyEvent);
    void keyReleased(QKeyEvent);
private slots:
    void SlotBtnSureClicked();
    void SlotBtnCancleClicked();

};

#endif // U_CTRLTOOLPOSCALIB_H
