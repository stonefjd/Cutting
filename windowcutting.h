#ifndef WINDOWCUTTING_H
#define WINDOWCUTTING_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QDebug>

#include "statemachine.h"
#include "Machine/machine.h"
#include "Machine/machine.h"

namespace Ui {
class WindowCutting;
}

class WindowCutting : public QMainWindow
{
    Q_OBJECT

public:
    void keyPressEvent(QKeyEvent *event);
    explicit WindowCutting(QWidget *parent = nullptr);
    ~WindowCutting();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::WindowCutting *ui;
//    StateMachine runStateMachine;
    Machine mMachine;
};

#endif // WINDOWCUTTING_H
