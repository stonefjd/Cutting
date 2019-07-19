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
}
