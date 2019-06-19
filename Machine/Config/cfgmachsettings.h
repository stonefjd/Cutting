#ifndef CFGMACHSETTINGS_H
#define CFGMACHSETTINGS_H

#include <QDialog>
#include "configmachine.h"
#include "confighead.h"
namespace Ui {
class cfgMachSettings;
}

class cfgMachSettings : public QDialog
{
    Q_OBJECT

public:
    explicit cfgMachSettings(QWidget *parent = nullptr);
    ~cfgMachSettings();

private:
    Ui::cfgMachSettings *ui;

private:
    ConfigMachine   *cMach;
    ConfigHead      *cHead;
public:
    void SetCfgMach(ConfigMachine *_cMach);
    void SetCfgHead(ConfigHead  *_cHead);
};

#endif // CFGMACHSETTINGS_H
