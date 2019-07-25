#include "u_ctrltoolposcalib.h"
#include "ui_u_ctrltoolposcalib.h"

U_CtrlToolPosCalib::U_CtrlToolPosCalib(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::U_CtrlToolPosCalib)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("设置偏移"));
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
bool U_CtrlToolPosCalib::InitialModel(int _idApron)
{
    bool ret = false;
    //进入状态切换
    d_ctrlMach->EventOprtSubEnterToolPosCalib();
    //判断机头序号是否支持切换
    if(_idApron == 0)
    {
        //设置操作机头的相关轴号
        d_ctrlMach->SetCtrlAxisGroup(_idApron);
        //设置UI
        lEdtPosX->setDisabled(true);
        lEdtPosY->setDisabled(true);

        QFormLayout *formLayout = new QFormLayout;
        QVBoxLayout *vBox = new QVBoxLayout;
        QHBoxLayout *hBox = new QHBoxLayout;
        formLayout->addRow(lbPosX,lEdtPosX);
        formLayout->addRow(lbPosY,lEdtPosY);

        btnSure->setFixedWidth(50);
        btnCancel->setFixedWidth(50);
        hBox->addWidget(btnSure);
        hBox->addWidget(btnCancel);
        vBox->addLayout(formLayout);
        vBox->addLayout(hBox);
        this->setLayout(vBox);
        //设置量
        idApron = _idApron;
        posOrgCalib.setX(d_ctrlMach->GetPosRT()->x());
        posOrgCalib.setY(d_ctrlMach->GetPosRT()->y());
        lEdtPosX->setText(QString::number(d_ctrlMach->GetCfgApronList()->at(idApron)->GetXOffset()));
        lEdtPosY->setText(QString::number(d_ctrlMach->GetCfgApronList()->at(idApron)->GetYOffset()));

        connect(btnSure,SIGNAL(clicked()),this,SLOT(SlotBtnSureClicked()));
        connect(btnCancel,SIGNAL(clicked()),this,SLOT(SlotBtnCancleClicked()));
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
}
void U_CtrlToolPosCalib::keyPressEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat()&& (event->key() ==Qt::Key_A ||event->key() ==Qt::Key_D ||event->key() ==Qt::Key_W ||event->key() ==Qt::Key_S))
    {
        if( d_ctrlMach->GetCdtOprtStepToolPosCalib() == stStep3)
        {
            emit keyPressed(*event);
        }
    }
}
void U_CtrlToolPosCalib::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat()&& (event->key() ==Qt::Key_A ||event->key() ==Qt::Key_D ||event->key() ==Qt::Key_W ||event->key() ==Qt::Key_S))
    {
        if( d_ctrlMach->GetCdtOprtStepToolPosCalib() == stStep3)
        {
            emit keyReleased(*event);
            lEdtPosX->setText(QString::number(d_ctrlMach->GetPosRT()->x()-posOrgCalib.x()));
            lEdtPosY->setText(QString::number(d_ctrlMach->GetPosRT()->y()-posOrgCalib.y()));
        }
    }
}
void U_CtrlToolPosCalib::SlotBtnSureClicked()
{
    qDebug()<<"idSet";
    double offsetX = lEdtPosX->text().toDouble();
    double offsetY = lEdtPosY->text().toDouble();
    //将偏移量修改到内存
    d_ctrlMach->GetCfgApronList()->at(idApron)->SetXOffset(offsetX);
    d_ctrlMach->GetCfgApronList()->at(idApron)->SetYOffset(offsetY);
    //将偏移量修改到文件
    WritePrivateProfileString("Head0-Apron"+QString::number(idApron), "OffsetX",QString::number(offsetX), SETTING_PATH);
    WritePrivateProfileString("Head0-Apron"+QString::number(idApron), "OffsetY",QString::number(offsetY),SETTING_PATH);

//    QString *_tempStr = new QString;
//    QStringList _tempLst;
//    GetPrivateProfileString  ("MachHead0", "Apron"+QString::number(idApron),_tempStr,SETTING_PATH);
//    _tempLst = (*_tempStr).split(',');
//    _tempLst.replace(3,QString::number(offsetX));
//    _tempLst.replace(4,QString::number(offsetY));
//    WritePrivateProfileString("MachHead0", "Apron"+QString::number(idApron),_tempLst,SETTING_PATH);
    this->close();
}
void U_CtrlToolPosCalib::SlotBtnCancleClicked()
{
    qDebug()<<"idCancle";
    this->close();
}
