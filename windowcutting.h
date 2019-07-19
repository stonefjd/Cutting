#ifndef WINDOWCUTTING_H
#define WINDOWCUTTING_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHeaderView>
#include <QFile>
#include <QFrame>
#include <QPainter>
#include <QCloseEvent>
#include <QActionGroup>

#include "File/cutfilehandle.h"
#include "PhysicalLayer/gts.h"
#include "User/userhandle.h"
//#include "Machine/machine.h"
#include "Machine/Config/cfgmachhandle.h"
#include "Control/h_ctrlmach.h"

namespace Ui {
class WindowCutting;
}

class WindowCutting : public QMainWindow
{
    Q_OBJECT

public:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    explicit WindowCutting(QWidget *parent = nullptr);
    ~WindowCutting();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

    void on_actionReset_triggered();

    void on_actionLogOn_triggered();
    void on_actionWindIn_triggered(bool arg1);
    void on_actionWindOut_triggered(bool arg1);

    void debugTask_100ms();

    void on_actionStop_triggered();

    void on_actionLogManager_triggered();

    void on_dockWgtList_visibilityChanged(bool visible);

    void on_actionViewCutList_triggered(bool checked);

    void on_actionMachSetting_triggered();

    void on_actionKnifeSetting_triggered();

signals:
    void keyPressed(QKeyEvent);
    void keyReleased(QKeyEvent);
protected:
//    bool eventFilter(QObject *watched, QEvent *e);
    void userLog_PermissionConfirm();
private:

private:
    Ui::WindowCutting   *ui;
//    Machine             *mMachine = new Machine;
    H_CtrlMach          *handleCtrlMach;
    CfgMachHandle       *cfgMachHandle;
    UserHandle          *userHandle;
    QTimer              *debugTimer;
    CutFileHandle       *cutFileHandle;
};

#endif // WINDOWCUTTING_H
