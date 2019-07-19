#include "u_ctrlrngrst.h"
#include "ui_u_ctrlrngrst.h"

U_CtrlRngRst::U_CtrlRngRst(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::U_CtrlRngRst)
{
    ui->setupUi(this);
}

U_CtrlRngRst::~U_CtrlRngRst()
{
    delete ui;
}
void U_CtrlRngRst::SetCtrlMachObj(D_CtrlMach* _ctrlMach)
{
    this->d_ctrlMach = _ctrlMach;
}
D_CtrlMach* U_CtrlRngRst::GetCtrlMachObj(void)
{
    return this->d_ctrlMach;
}
void U_CtrlRngRst::InitialModel(void)
{

}
void U_CtrlRngRst::keyPressEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat()&& (event->key() ==Qt::Key_A ||event->key() ==Qt::Key_D ||event->key() ==Qt::Key_W ||event->key() ==Qt::Key_S))
        emit keyPressed(*event);
}
void U_CtrlRngRst::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat()&& (event->key() ==Qt::Key_A ||event->key() ==Qt::Key_D ||event->key() ==Qt::Key_W ||event->key() ==Qt::Key_S))
        emit keyReleased(*event);
}
