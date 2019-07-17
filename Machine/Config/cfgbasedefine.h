#ifndef CFGBASEDEFINE_H
#define CFGBASEDEFINE_H

#include <QWidget>
#include <QFile>
#include <QSettings>
#include <QMessageBox>

#define SETTING_PATH "Settings\\CutterSet.ini"
#define KNIFETOOLLIB_PATH "Settings\\KnifeToolLib.ini"

//#define AXIS_X 1
//#define AXIS_Y 2
//#define AXIS_SUM 2
#define MAX_TOOLAPRON				8	//刀座总数

#define			GUID2CUTTOOLID(x)       (static_cast<short>((static_cast<int>(x))&0x3f))
#define			GUID2KNIFEID(x)         (static_cast<short>(((static_cast<int>(x))>>6)&0x3f))
#define			KNIFETOOLID2GUID(a,b)   (static_cast<int>((static_cast<short>(a))|((static_cast<short>(b))<<6)))


class CfgBaseDefine
{
public:
    CfgBaseDefine();


};
bool GetPrivateProfileString(QString strSect,QString strKey,QString *szBuf,QString strConfigPath);
bool WritePrivateProfileString(QString strSect,QString strKey,QString strText,QString strConfigPath);
bool WritePrivateProfileString(QString strSect,QString strKey,QStringList strText,QString strConfigPath);

#endif // CFGBASEDEFINE_H
