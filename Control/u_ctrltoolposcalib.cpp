#include "u_ctrltoolposcalib.h"
#include "ui_u_ctrltoolposcalib.h"

U_CtrlToolPosCalib::U_CtrlToolPosCalib(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::U_CtrlToolPosCalib)
{
    ui->setupUi(this);
}

U_CtrlToolPosCalib::~U_CtrlToolPosCalib()
{
    delete ui;
    d_ctrlMach->EventOprtSubExitToolPosCalib();
}
void U_CtrlToolPosCalib::SetCtrlMachObj(D_CtrlMach* _ctrlMach)
{
    this->d_ctrlMach = _ctrlMach;
}
D_CtrlMach* U_CtrlToolPosCalib::GetCtrlMachObj(void)
{
    return this->d_ctrlMach;
}
bool U_CtrlToolPosCalib::InitialModel(int _apronId,double deep)
{
    bool ret = false;
    d_ctrlMach->EventOprtSubEnterToolPosCalib();
    if(_apronId == 0)
    {
        d_ctrlMach->SetCtrlAxisGroup(AXIS_Z1,AXIS_A1,deep);
        ret = true;
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("机器不支持其他机头校准配置"));
        msgBox.exec();
        this->close();
        ret = false;
    }
    return ret;
//    d_ctrlMach->SetCtrlAxisZ()
}
void U_CtrlToolPosCalib::keyPressEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat()&& (event->key() ==Qt::Key_A ||event->key() ==Qt::Key_D ||event->key() ==Qt::Key_W ||event->key() ==Qt::Key_S))
        emit keyPressed(*event);
}
void U_CtrlToolPosCalib::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat()&& (event->key() ==Qt::Key_A ||event->key() ==Qt::Key_D ||event->key() ==Qt::Key_W ||event->key() ==Qt::Key_S))
        emit keyReleased(*event);
}
