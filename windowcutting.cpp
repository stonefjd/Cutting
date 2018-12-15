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
