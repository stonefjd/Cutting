#ifndef WINDOWCUTTING_H
#define WINDOWCUTTING_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>
#include <QString>

#include "File/Settings/settings.h"
#include "File/Route/route.h"
#include "statemachine.h"
#include "Machine/machine.h"
#include "PhysicalLayer/gts.h"


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

    void on_actionImport_triggered();

signals:

private:
    Ui::WindowCutting *ui;
//    StateMachine runStateMachine;
    Machine mMachine;
    Settings    settings;
    Route     route;
};

#endif // WINDOWCUTTING_H
