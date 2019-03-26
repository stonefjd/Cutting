#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QTreeView>
#include <QListWidget>
#include <QDebug>
#include <QSettings>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>


#include <Machine/Fan/fan.h>

struct SettingsCfg_T
{

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
    void resetSettingsData();

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
};

#endif // SETTINGS_H
