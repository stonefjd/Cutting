#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QTreeView>
#include <QListWidget>
#include <QDebug>
#include <QSettings>
#include <QFile>
#include <QMessageBox>

#include <Machine/KnifeTool/knifetool.h>
#include <Machine/Desktop/desktop.h>
#include <Machine/Fan/fan.h>

#pragma execution_character_set("utf-8")
//struct SettingMech
struct SettingsCfg_T
{
    LaserAbsOffset_T laserAbs;
    DesktopHOffset_T desktopH;
    DesktopSizeCut_T desktopSizeCut;
    ToolSeatOffset_T toolSeat[TOOLNUM];
    ToolSpeed_T toolSpeed;
    FanSpeed_T fanSpeed;
};

namespace Ui {
class Settings;
}
class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButtonOk_clicked();

    void on_pushButtonApply_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::Settings *ui;
    QString pathSettingFile;
    SettingsCfg_T settingsCfg,settingsCfg_Default;

    void SettingsCfg_SetDefault(SettingsCfg_T *cfg);
    void SettingsCfg_Set(QSettings *settings,SettingsCfg_T *cfg);
    bool SettingsCfg_GetInit(QSettings *settings,SettingsCfg_T *cfg);
    bool SettingsCfg_GetEditLine(SettingsCfg_T *cfg);
    void SettingsCfg_DisplayNum(SettingsCfg_T *cfg);

    void SettingsCfg_Get();
    void SettingsCfg_Apply();
    void SettingsCfg_Confirm();
};

#endif // SETTINGS_H
