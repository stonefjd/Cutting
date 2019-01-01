#include "windowcutting.h"
#include "ui_windowcutting.h"

WindowCutting::WindowCutting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WindowCutting)
{
    ui->setupUi(this);
}

WindowCutting::~WindowCutting()
{
    delete ui;
}

//----override----//
void WindowCutting::keyPressEvent(QKeyEvent *event)
{
    //-------------shift key should be first
    if(event->modifiers() == Qt::ShiftModifier)
    {
        if(event->key() == Qt::Key_Left)
        {
            qDebug() << "Shift+left" ;
        }
        else if(event->key() == Qt::Key_Right)
        {
            qDebug() << "Shift+right" ;
        }
        else if(event->key() == Qt::Key_Up)
        {
            qDebug() << "Shift+Up" ;
        }
        else if(event->key() == Qt::Key_Down)
        {
            qDebug() << "Shift+Down" ;
        }
    }
    else
    {
        if(event->key() == Qt::Key_Left)
        {
            qDebug() << "left" ;
        }
        else if(event->key() == Qt::Key_Right)
        {
            qDebug() << "right" ;
        }
        else if(event->key() == Qt::Key_Up)
        {
            qDebug() << "Up" ;
        }
        else if(event->key() == Qt::Key_Down)
        {
            qDebug() << "Down" ;
        }
    }
}
//signals and slots
void WindowCutting::on_actionSettingsParameter_triggered()
{
    this->settings.exec();
}

void WindowCutting::on_actionReset_triggered()
{
    QMessageBox msgBox;
    msgBox.setText(tr("请确认是否恢复出厂设置"));
    QPushButton *btnYes = msgBox.addButton(tr("确认"), QMessageBox::YesRole);
    QPushButton *btnNo = msgBox.addButton(tr("取消"), QMessageBox::NoRole);

    msgBox.exec();
    if(msgBox.clickedButton()== btnYes)
    {
        emit Signal_SettingsRecover();
        qDebug()<<"recover";
    }
    else if(msgBox.clickedButton()== btnNo)
    {

    }
}

//----------------TEST-----------------
void WindowCutting::on_pushButton_clicked()
{

}


void WindowCutting::on_pushButton_2_clicked()
{
    this->mMachine.mFan_1.SetState_FanStop();
}

void WindowCutting::on_pushButton_3_clicked()
{
    this->mMachine.mFan_1.SetState_FanWindIn();
}

void WindowCutting::on_pushButton_4_clicked()
{
    this->mMachine.mFan_1.SetState_FanWindOut();
}


