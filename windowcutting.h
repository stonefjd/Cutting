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

//#include "File/Settings/settings.h"
#include "File/CutFileListOp/cutfilelistop.h"
#include "File/IniOp/iniop.h"
#include "Machine/machine.h"
#include "PhysicalLayer/gts.h"
#include "User/userlog.h"

#define BTN_ID_L 0
#define BTN_ID_R 1
#define BTN_ID_U 2
#define BTN_ID_D 3
#define BTN_ID_O 4

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
    void on_actionWindIn_toggled(bool arg1);

    void on_actionWindOut_toggled(bool arg1);

    void debugTask_10ms();

signals:
    void keyPressed(QKeyEvent);
    void keyReleased(QKeyEvent);
protected:
    bool eventFilter(QObject *watched, QEvent *e);
    void userLog_PermissionConfirm();
private:
    void messageBoxAutoRemove(QString _str);

private:
    Ui::WindowCutting   *ui;
    Machine             *mMachine;
    UserLog             *user;
//    Settings    settings;
//    IniOp               iniOp;
    CutFileListOp       cutFileList;
    QTimer              *debugTimer;
};

#endif // WINDOWCUTTING_H
