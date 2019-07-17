#include "ctrlmach_ui.h"

CtrlMach_UI::CtrlMach_UI(QObject *parent) : QObject(parent)
{

}

void CtrlMach_UI::SetCtrlMachObj(CtrlMach* _ctrlMach)
{
    this->ctrlMach = _ctrlMach;
}
CtrlMach* CtrlMach_UI::GetCtrlMachObj(void)
{
    return this->ctrlMach;
}
void CtrlMach_UI::InitialModel(QDockWidget* _ctrlDockWgt)
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
    connect(this->btnDirGroup,SIGNAL(buttonPressed(int)), ctrlMach,SLOT(SlotBtnPressed(int)));
    connect(this->btnDirGroup,SIGNAL(buttonReleased(int)),ctrlMach,SLOT(SlotBtnReleased(int)));
    ctrlDockWgt->widget()->setLayout(vLayout);
}
