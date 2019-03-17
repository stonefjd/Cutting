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

#include "File/Settings/settings.h"
#include "File/CutFileListOp/cutfilelistop.h"
#include "File/IniOp/iniop.h"
#include "Machine/machine.h"
#include "PhysicalLayer/gts.h"
#include "User/userlog.h"

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
    void on_btnFileAdd_clicked();
    void on_btnFileImport_clicked();
    void on_btnFileRmv_clicked();
    void on_btnFileDown_clicked();
    void on_btnFileUp_clicked();
    void on_btnFileExport_clicked();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

    void on_actionReset_triggered();
    void on_actionSettingsParameter_triggered();

    void on_actionImportCutFile_triggered();

    void on_actionImportCutFileList_triggered();

    void on_actionLogOn_triggered();
signals:

protected:
    bool eventFilter(QObject *watched, QEvent *e);
    void userLog_PermissionConfirm();
private:
    Ui::WindowCutting *ui;
    StateMachine runStateMachine;
    Machine mMachine;
    UserLog *user;
    Settings    settings;
    IniOp   iniOp;
    CutFileListOp   cutFileList;
};

#endif // WINDOWCUTTING_H
