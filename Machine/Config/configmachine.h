#ifndef CONFIGMACHINE_H
#define CONFIGMACHINE_H

#include <QWidget>
#include <QFile>
#include <QMessageBox>
#include <QSettings>
#include <QDebug>

#define AXIS_X 1
#define AXIS_Y 2
#define AXIS_SUM 2
class ConfigMachine : public QWidget
{
    Q_OBJECT
private:
    QString machCfgPath;

    QString versionHw;
    QString versionSw;
    double  feltThickness;
    double  machType;
    double  machTypeSub;
    double  machPhysical[AXIS_SUM];
    double  machRunMax[AXIS_SUM];
    double  machPulsePerMillimeter[AXIS_SUM];

    int     machHeadCount;
private:
public:
    explicit ConfigMachine(QWidget *parent = nullptr);
    void GetMachineInfo();

    QString GetMachCfgPath();
    void    SetMachRunMax(int _axis,double _pos);
    double  GetMachRunMax(int _axis);
    bool    UpdateMachRunMax(int _axis,double _pos);

    void    SetMachPulsePerMillimeter(int _axis,double _pos);
    double  GetMachPulsePerMillimeter(int _axis);

    bool GetPrivateProfileString(QString strSect,QString strKey,QString *szBuf,QString strConfigPath);
    bool WritePrivateProfileString(QString strSect,QString strKey,QString strText,QString strConfigPath);

signals:

public slots:
};

#endif // CONFIGMACHINE_H
