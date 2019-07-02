#include "cfgknifemanager.h"
#include "ui_cfgknifemanager.h"

CfgKnifeManager::CfgKnifeManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CfgKnifeManager)
{
    ui->setupUi(this);
    grpChkBox = new QButtonGroup;
    connect(grpChkBox,SIGNAL(buttonClicked(int)),this,SLOT(SlotBtnGrpClicked(int)));

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
    grpChkBox->setExclusive(false);//不互斥
    QGridLayout *gridChkBoxLayout = new QGridLayout(ui->groupChkBox);
    QGridLayout *gridCbBoxLayout = new QGridLayout(ui->groupCbBox);

    cLib->GetAllKnifeNames(tempKnifeName);



    for(int i=0;i<MAX_TOOLAPRON;i++)
    {
    //[BEGIN]添加checkbox组件
        QCheckBox *chkBox = new QCheckBox(ui->groupChkBox);
        //check box 本身修饰
        chkBox->setText(tr("刀座")+QString::number(i));
        chkBox->setProperty("id",i);
        gridChkBoxLayout->addWidget(chkBox, i/4, i%4, 1, 1);
        //check box 加入group后的状态
        grpChkBox->addButton(chkBox);
        grpChkBox->setId(chkBox,i);
    //[END]添加checkbox组件

    //[BEGIN]添加Combo Box组件
        QComboBox *cbBox = new QComboBox(ui->groupCbBox);
        //
        cbBox->setProperty("id",i);
        cbBox->addItems(tempKnifeName);
        cbBox->setCurrentIndex(-1);
        cbBox->setDisabled(true);
        gridCbBoxLayout->addWidget(cbBox, i/4, i%4, 1, 1);
        //
        cbBoxList.append(cbBox);
    //[END]添加Combo Box组件
    }
//    QStringList tempSeat = cHead->GetApronIndexList();
    for(int i=0;i<MAX_TOOLAPRON;i++)
    {
        int guid = cApron->at(i)->GetKnifeGuid();
        QString knifeName = cLib->GetKnifeByGuid(guid)->GetKnifeName();
        if(cApron->at(i)->GetApronUse() != 0)
        {

            grpChkBox->button(i)->setChecked(true);
            cbBoxList.at(i)->setEnabled(true);
        }
        cbBoxList.at(i)->setCurrentIndex(tempKnifeName.indexOf(knifeName));
    }

    //未登录禁用组件
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
void CfgKnifeManager::SlotBtnGrpClicked(int id)
{
    if(grpChkBox->button(id)->isChecked())
    {
        cbBoxList.at(id)->setEnabled(true);
    }
    else
    {
        cbBoxList.at(id)->setDisabled(true);
        cbBoxList.at(id)->setCurrentIndex(tempKnifeName.indexOf("NULT"));
    }
}

void CfgKnifeManager::on_btnOK_clicked()
{
    on_btnApply_clicked();
    if(tab1Valid==0)
        this->close();
}

void CfgKnifeManager::on_btnApply_clicked()
{
//    int grpChkState = 2;
    QList<int> apronChoseList;
    QList<int> knifeGuidChoseList;
//    QString     knifeGuidStr;
    for(int i=0;i<MAX_TOOLAPRON;i++)
    {
        int chosed = 0;
        if(grpChkBox->button(i)->isChecked())
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
//                knifeGuid.append();
            }
        }
        apronChoseList.append(chosed);

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
//            cApron->at(i)->SetApronUse(use);
//            cApron->at(i)->SetKnifeGuid(knifeGuidChoseList.at(i));
//            cApron->at(i)->SetKnife(cLib->GetKnifeByGuid(knifeGuidChoseList.at(i)));
            WritePrivateProfileString("Apron"+QString::number(i),"Used"             ,QString::number(use),SETTING_PATH);
            WritePrivateProfileString("Apron"+QString::number(i),"AddedKnifeGuid"   ,QString::number(guid),SETTING_PATH);

            CfgApron *tempApron = new CfgApron;
            tempApron->GetApronInfo(i);

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
