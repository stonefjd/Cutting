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
