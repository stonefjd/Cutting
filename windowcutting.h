#ifndef WINDOWCUTTING_H
#define WINDOWCUTTING_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>

#include "settings.h"
#include "statemachine.h"
#include "Machine/machine.h"

#include "PhysicalLayer/gts.h"

#pragma execution_character_set("utf-8")

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

    void on_actionReset_triggered();
    void on_actionSettingsParameter_triggered();

signals:
    void Signal_SettingsRecover();
private:
    Ui::WindowCutting *ui;
//    StateMachine runStateMachine;
    Machine mMachine;
    Settings settings;
};

#endif // WINDOWCUTTING_H
