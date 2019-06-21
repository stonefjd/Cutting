#ifndef CFGMACHSETTINGS_H
#define CFGMACHSETTINGS_H

#include <QDialog>
#include <QFont>
#include "cfgmach.h"
#include "cfghead.h"
namespace Ui {
class CfgMachSettings;
}

class CfgMachSettings : public QDialog
{
    Q_OBJECT

public:
    explicit CfgMachSettings(QWidget *parent = nullptr);
    ~CfgMachSettings();

private:
    Ui::CfgMachSettings *ui;

private:
    CfgMach *cMach;
    CfgHead *cHead;
public:
    void SetCfgMach(CfgMach *_cMach);
    void SetCfgHead(CfgHead *_cHead);
    void LoadData();
private slots:
    void on_lEdtFeedLen_editingFinished();
};

#endif // CFGMACHSETTINGS_H
