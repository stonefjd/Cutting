#include "cfgknifemanager.h"
#include "ui_cfgknifemanager.h"

CfgKnifeManager::CfgKnifeManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CfgKnifeManager)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("刀具管理中心"));

}

CfgKnifeManager::~CfgKnifeManager()
{
    delete ui;
}
void CfgKnifeManager::SetCfgHead(CfgHead *_cHead)
{
    this->cHead = _cHead;
}
void CfgKnifeManager::SetCfgApron(QList<CfgApron*> *_cApron)
{
    this->cApron = _cApron;
}

void CfgKnifeManager::SetCfgLib(CfgLib *_cLib)
{
    this->cLib = _cLib;
}
void CfgKnifeManager::SetCfgUser(UserHandle *_userHandle)
{
    this->userHandle = _userHandle;
}
void CfgKnifeManager::LoadData()
{
    ui->tabWidget->setCurrentIndex(0);
    QGridLayout *gridChkBoxLayout = new QGridLayout(ui->tabKnifeLoad);

    cLib->GetAllKnifeNames(tempKnifeName);



    for(int i=0;i<MAX_TOOLAPRON;i++)
    {
        //[BEGIN]添加分组
        QGroupBox *grpBoxKnife = new QGroupBox(ui->tabKnifeLoad);
        grpBoxKnife->setCheckable(true);
        grpBoxKnife->setChecked(false);
        grpBoxKnife->setTitle(tr("刀座")+QString::number(i));
        grpBoxKnife->setProperty("id",i);
        gridChkBoxLayout->addWidget(grpBoxKnife, i/4, i%4, 1, 1);
        //[END]添加分组

        //[BEGIN]添加XY参数及校正按钮组件
        QLabel *lbOffsetX = new QLabel(grpBoxKnife);
        QLabel *lbOffsetY = new QLabel(grpBoxKnife);
        QLineEdit *lEdtOffsetX = new QLineEdit(grpBoxKnife);
        QLineEdit *lEdtOffsetY = new QLineEdit(grpBoxKnife);
        lbOffsetX->setText(tr("X偏移"));
        lbOffsetY->setText(tr("Y偏移"));
        lEdtOffsetX->setEnabled(false);
        lEdtOffsetY->setEnabled(false);
        lbOffsetX->setBuddy(lEdtOffsetX);
        lbOffsetY->setBuddy(lEdtOffsetY);
        QPushButton *btnCalib = new QPushButton(grpBoxKnife);
        btnCalib->setText(tr("校正"));
        btnCalib->setProperty("id",i);
        connect(btnCalib,SIGNAL(clicked()),this,SLOT(SlotBtnCalibClicked()));
        //[END]添加XY参数及校正按钮组件

        //[BEGIN]添加Combo Box组件
        QComboBox *cbBox = new QComboBox(grpBoxKnife);
        //
        cbBox->setProperty("id",i);
        cbBox->addItems(tempKnifeName);
        cbBox->setCurrentIndex(-1);
        cbBoxList.append(cbBox);
        //[END]添加Combo Box组件

        //[BEGIN]添加布局
        QFormLayout *fLayOffsetXY = new QFormLayout();
        fLayOffsetXY->addRow(lbOffsetX,lbOffsetX->buddy());
        fLayOffsetXY->addRow(lbOffsetY,lbOffsetY->buddy());
        QVBoxLayout *vLayGroup = new QVBoxLayout(grpBoxKnife);
        vLayGroup->addLayout(fLayOffsetXY);
        vLayGroup->addWidget(btnCalib);
        vLayGroup->addWidget(cbBox);
        //[END]添加布局

        //[BEGIN]加载控件相关变量参数
        //set offset
        lEdtOffsetX->setText(QString::number(cApron->at(i)->GetXOffset()));
        lEdtOffsetY->setText(QString::number(cApron->at(i)->GetYOffset()));
        //set checked
        if(cApron->at(i)->GetApronUse() != 0)
        {
            grpBoxKnife->setChecked(true);
            cbBoxList.at(i)->setEnabled(true);
        }
        //guid to name
        int guid = cApron->at(i)->GetKnifeGuid();
        CfgKnife* _knife = cLib->GetKnifeByGuid(guid);
        if(_knife != nullptr)
        {
            QString _knifeName;
            _knifeName = _knife->GetKnifeName();
            cbBoxList.at(i)->setCurrentIndex(tempKnifeName.indexOf(_knifeName));
        }
        else
        {
            cbBoxList.at(i)->setCurrentIndex(-1);
        }
        //[END]加载控件相关变量参数
        connect(grpBoxKnife,SIGNAL(clicked(bool)),this,SLOT(SlotBtnGrpClicked(bool)));
    }
//    //未登录禁用组件
//    if(userHandle == nullptr ||userHandle->GetUser()->GetUserLevel()>5)
//    {
//        ui->tabWidget->setDisabled(true);
//    }
//    else
//    {
//        ui->tabWidget->setEnabled(true);
//    }
}

//slots
//刀座使能
void CfgKnifeManager::SlotBtnGrpClicked(bool _chk)
{
    QGroupBox *grpBox = qobject_cast<QGroupBox*>(sender());

    int id = grpBox->property("id").toInt();
    if(_chk)
    {

        cbBoxList.at(id)->setEnabled(true);
    }
    else
    {
        cbBoxList.at(id)->setDisabled(true);
        cbBoxList.at(id)->setCurrentIndex(tempKnifeName.indexOf("NULT"));
    }
}
//校准按键
void CfgKnifeManager::SlotBtnCalibClicked()
{
    QPushButton *btnCalib = qobject_cast<QPushButton*>(sender());
    int id = btnCalib->property("id").toInt();
    qDebug()<<id;
    this->close();
    emit EnterOprtToolPosCalibRequest(id);
}

void CfgKnifeManager::on_btnOK_clicked()
{
    on_btnApply_clicked();
    if(tab1Valid==0)
        this->close();
}

void CfgKnifeManager::on_btnApply_clicked()
{
    QList<int> apronChoseList;
    QList<int> knifeGuidChoseList;
    QList<QGroupBox*> groupBox;
    groupBox.append(ui->tabKnifeLoad->findChildren<QGroupBox*>());
    for(int i=0;i<MAX_TOOLAPRON;i++)
    {
        int chosed = 0;
        if(groupBox.at(i)->isChecked())
        {
            tab1Valid = 0;
            if(cbBoxList.at(i)->currentIndex() == -1)
            {
                tab1Valid = 1;
                break;
            }
            else
            {
                chosed = 1;
            }
        }
        apronChoseList.append(chosed);
        qDebug()<<cbBoxList.at(i)->currentText();
        CfgKnife* knife = cLib->GetKnifeByName(cbBoxList.at(i)->currentText());
        knifeGuidChoseList.append(knife->GetGuid());
    }
    switch(tab1Valid)
    {
    case 0://0:正常
        cApron->clear();
        for(int i=0;i<MAX_TOOLAPRON;i++)
        {
            int use = apronChoseList.at(i);
            int guid = knifeGuidChoseList.at(i);

//            QString *_tempStr = new QString;
//            QStringList _tempLst;
//            GetPrivateProfileString  ("MachHead0", "Apron"+QString::number(i),_tempStr,SETTING_PATH);
//            _tempLst = (*_tempStr).split(',');
//            _tempLst.replace(0,QString::number(use));
//            _tempLst.replace(2,QString::number(guid));
            WritePrivateProfileString("Head0-Apron"+QString::number(i), "Used",     QString::number(use), SETTING_PATH);
            WritePrivateProfileString("Head0-Apron"+QString::number(i), "KnifeGuid",QString::number(guid),SETTING_PATH);

            //重新装载刀座列表
            CfgApron *tempApron = new CfgApron;
            tempApron->GetApronInfo(i);

            //对刀座列表重新放入数据
            CfgKnife *tmpKnife = cLib->GetKnifeByGuid(tempApron->GetKnifeGuid());
            tempApron->SetKnife(tmpKnife);
            cApron->append(tempApron);
        }
        break;
    case 1://1:未选择刀具
    {
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("请选择刀座对应刀具"));
        msgBox.exec();
        break;
    }
    case 2://2:无选中
    {
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("机器无刀座被使用"));
        msgBox.exec();
        break;
    }
    default: break;
    }
}

void CfgKnifeManager::on_btnCancle_clicked()
{
    this->close();
}
