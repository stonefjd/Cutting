#include "u_ctrlbtndir.h"

U_CtrlBtnDir::U_CtrlBtnDir(QObject *parent) : QObject(parent)
{

}
void U_CtrlBtnDir::SetCtrlMachObj(D_CtrlMach* _ctrlMach)
{
    this->d_ctrlMach = _ctrlMach;
}
D_CtrlMach* U_CtrlBtnDir::GetCtrlMachObj(void)
{
    return this->d_ctrlMach;
}
void U_CtrlBtnDir::InitialModel(QDockWidget* _ctrlDockWgt)
{
    ctrlDockWgt = _ctrlDockWgt;
    QStringList strlist = {"UL","U","UR","L","ORG","R","DL","D","DR"};
    QGridLayout *gridLayout = new QGridLayout();
    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addItem(new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hLayout->addLayout(gridLayout);
    hLayout->addItem(new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    vLayout->addLayout(hLayout);
    vLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    for(int i = 0;i<DIRECTION_CNT;i++)
    {
        QPushButton* pBtn = new QPushButton(strlist.at(i));
        pBtn->setFixedWidth(30);
        pBtn->setFixedHeight(30);
        gridLayout->addWidget(pBtn,i/3,i%3,1,1);
        this->btnDirGroup->addButton(pBtn);
        this->btnDirGroup->setId(pBtn,i);
    }
    connect(this->btnDirGroup,SIGNAL(buttonPressed(int)), d_ctrlMach,SLOT(SlotBtnPressed(int)));
    connect(this->btnDirGroup,SIGNAL(buttonReleased(int)),d_ctrlMach,SLOT(SlotBtnReleased(int)));
    ctrlDockWgt->widget()->setLayout(vLayout);
}
