#ifndef CONFIGINFO_H
#define CONFIGINFO_H

#define SETTING_PATH "Settings\\CutterSet.ini"

#define AXIS_X 1
#define AXIS_Y 2
//#define AXIS_SUM 2

#define			GUID2CUTTOOLID(x)       (static_cast<short>((static_cast<int>(x))&0x3f))
#define			GUID2KNIFEID(x)         ((short)((((int)(x))>>6)&0x3f))
#define			KNIFETOOLID2GUID(a,b)   (static_cast<int>((static_cast<short>(a))|((static_cast<short>(b))<<6)))

#endif // CONFIGINFO_H
