#ifndef SYMBOL_H
#define SYMBOL_H

#define		GUID2CUTTOOLID(x)       (static_cast<short>((static_cast<int>(x))&0xff))
#define		GUID2KNIFEID(x)		  (static_cast<short>(((static_cast<int>(x))>>8)&0xff))
#define		KNIFETOOLID2GUID(a,b)	  (static_cast<int>((static_cast<short>(a))|((static_cast<short>(b))<<8)))

#define		ISCUTTOOLTYPE(a,b)	  ((static_cast<short>(SP2CUTTOOLID(a)) == (static_cast<short>(b)))

//系统精度
const double	TOLERANCE_EQUAL  = 0.05;		// 系统精度,0.05毫米（两点重合误差量）
const double	TOLERANCE_INSERT = 0.05;		// 离散精度,0.05毫米

#ifndef PI
#define PI		3.141592653589793238462643
#endif

#ifndef TWOPI
#define TWOPI	6.283185307179586476925286
#endif

#ifndef SQR_3
#define SQR_3	1.7320508075688772935274463415059
#endif

#ifndef SQR_2
#define SQR_2	1.4142135623730950488016887242097
#endif

const int		MAX_SIZECOUNT  = 100;			// 本系统最大档数

const int		ANGLE_SCALE = 100;
const int		BUFFER_COMMON= 32;				// 一般字符串长度
const int		BUFFER_PATH= 260;				// 一行文字的长度
const int		BUFFER_BIGPATH= 1024;			// 路径等字符串长度
const int		BUFFER_MAXSIZE = 32768;			// 默认缓存区大小
const int		MAX_INSERTNUM = 1000;			// 预分配离散点数
const int		XMAX_INSERTNUM = 3000;			// 预分配离散点数 (较大)
const int		MAX_DATANUM = 1000;			    // 预分配离散点数
const double	MAX_LENGTH = 100000;			// 比较大的长度值（100米）
const int		TOLERANCE_CATCH  = 10;			// 选点的误差值（10个像素）

const double	MAX_SCALE = 200000;				// 最大放大比例
const double	MIN_SCALE = 0.0000001;			// 最小缩小比例
const double	BASE_SCALE = 6;					// 初始化比例 实际尺寸的1/6

const double    STRIP_HEIGHT = 0.5;				// 分条高度 0.5mm

//点属性
#define			POINT_START		0x00000011		// 开始点
#define			POINT_CONTROL	0x00000012		// 折点
#define			POINT_CURVE		0x00000003		// 曲点
#define			POINT_END		0x00000014		// 结束点
#define			POINT_ONLINE	0x00000005		// 线上点
#define			POINT_ARC		0x00000006		// 圆弧点

#define			MARKP			0x000000f0
#define			MARKT			0x00000f00

#define			POINT_FLAT		0x00000100		// 平刀点
#define			POINT_CONVEX	0x00000200		// 凹凸点
#define			POINT_INFLECT	0x00000400		// 抬刀点(拐点)
#define			POINT_TRANSFER	0x00000800		// 过渡点(前后三点接近直线)

#define			CONTROLPOINT(X)	((X & MARKP) == 0x00000010)	//判断是否为折点
#define			FLATPOINT(X)	((X & MARKT) == 0x00000100)	//判断是否为平刀点
#define			CONVEXPOINT(X)	((X & MARKT) == 0x00000200) //判断是否为凹凸点
#define			INFLECTPOINT(X)	((X & MARKT) == 0x00000400) //判断是否为抬刀点
#define			TRANSFERPOINT(X)((X & MARKT) == 0x00000800) //判断是否为过渡点

//单位标识(参照dxf标准)
const int		UNIT_MM = 4;					// 毫米,系数=1
const int		UNIT_CM = 5;					// 厘米，系数=10
const int		UNIT_INCH = 1;					// 英寸，系数=25.4
const int		UNIT_DM = 14;					// 分米，系数=100
const int		UNIT_FOOT = 2;					// 英尺，系数=304.8
const int		UNIT_M = 6;						// 米，系数=1000
const int		UNIT_DMM = 8;					// 十分之一毫米，系数=0.1
const int		UNIT_HMM = 9;					// 百分之一毫米，系数=0.01
const int		UNIT_MICROINCH = 10;			// 百分之一英寸，系数=0.254
const int		UNIT_MILINCH = 11;				// 千分之一英寸，系数=0.0254
const int		UNIT_YARD = 12;				    // 码，系数=914.4
const int		UNIT_KM = 7;					// 千米，系数=1000000
const int		UNIT_MILE = 3;					// 英里，系数=
const int		UNIT_DEFAULT = 0;				// 默认单位 

//单位系数
const double	FACTOR_MM = 1;					// 毫米,系数=1
const double	FACTOR_CM = 10;					// 厘米，系数=10
const double	FACTOR_INCH = 25.4;				// 英寸，系数=25.4
const double	FACTOR_DM = 100;				// 分米，系数=100
const double	FACTOR_FOOT = 304.8;			// 英尺，系数=304.8
const double	FACTOR_YARD = 914.4;			// 码，系数=914.4
const double	FACTOR_M = 1000;				// 米，系数=1000
const double	FACTOR_KM = 1000000;			// 千米，系数=1000000
const double	FACTOR_DMM = 0.1;				// 十分之一毫米，系数=0.1
const double	FACTOR_HMM = 0.01;				// 百分之一毫米，系数=0.01
const double	FACTOR_MICROINCH = 0.254;		// 百分之一英寸，系数=0.254
const double	FACTOR_MILINCH = 0.0254;		// 千分之一英寸，系数=0.0254

const int		SCALE_TENTIME = 0;				// 系数=10
const int		SCALE_ONETIME = 1;				// 系数=1
const int		SCALE_DECI = 2;					// 系数=0.1
const int		SCALE_CENTI = 3;				// 系数=0.01
const int		SCALE_MILLI = 4;				// 系数=0.001

//Dxf文件类型
const int		DXFTYPE_AAMA = 0;				// Aama 格式的Dxf文件
const int		DXFTYPE_TIIP = 1;				// Tiip 格式的Dxf文件
const int		DXFTYPE_DXF = 2;				// dxf 格式的Dxf文件

//功能id
const int		OPER_DART = 0;					//省道工具id
const int		OPER_CRAFT = 1;					//工艺工具id
const int		OPER_PEN = 2;					//智能笔id
const int		OPER_PATTERN = 3;				//制图工具id
const int		OPER_GRADE = 4;					//放码工具id
const int		OPER_DIGIT = 5;					//数值化仪工具id
const int		OPER_SEW = 6;					//放缝工具id

#define			FONTNAME_DEFINE	  "Arial"		//默认字体
#define			DEFAULT_PIECESPEC "S"		    //默认规格
#define			DEFAULT_PIECEPAT  "Pat"			//默认版型
//

//颜色值
const int		COLORREF_RECT   = 0x000000ff;    // 红色,RGB(255,0,0)
const int		COLORREF_RED    = 0x000000ff;    // 红色,RGB(255,0,0)
const int		COLORREF_BLUE   = 0x00ff0000;    // 蓝色,RGB(0,0,255)
const int		COLORREF_GREEN  = 0x0000ff00;    // 绿色,RGB(0,255,0)
const int		COLORREF_YEELOW = 0x0000ffff;    // 黄色,RGB(255,255,0)
const int		COLORREF_AQUA   = 0x00ffff00;    // 粉蓝,RGB(0,255,255)
const int		COLORREF_GRAY   = 0x00808080;    // 灰色,RGB(128,128,128)
const int		COLORREF_WHITE  = 0x00ffffff;    // 白色,RGB(255,255,255)

//旋转类型
//const int		ROTATETYPE_0 = 0;				 // 0
//const int		ROTATETYPE_180 = 1;				 // 0->180
//const int		ROTATETYPE_90 = 2;				 // 0->90
//const int		ROTATETYPE_45 = 3;				 // 0->45
//const int		ROTATETYPE_FREE = 4;			 // 任意角度

//排料类型
const int		MARKTYPE_COMPLETE = 0;			 // 普通排料
const int		MARKTYPE_FIXEDLENGTH = 1;		 // 定长排料
const int		MARKTYPE_COLORSHADING = 2;		 // 分组色差排料
const int		MARKTYPE_TAOSET = 3;	         // 分组套排
const int		MARKTYPE_PACK = 4;	             // 紧压

//分组排料类型
const int		SUBGROUPTYPE_NONE = 0;			 // 不分组
const int		SUBGROUPTYPE_SIZE = 1;			 // 按尺码分组 （色差排料)
const int		SUBGROUPTYPE_TAO = 2;			 // 按套分组    (套排)
const int		SUBGROUPTYPE_PIECE = 3;			 // 按序号分组    (序号排)

//裁片排序方式
#define			PIECESORTTYPE_AREA_DOWN		0	 //按面积从大到小
#define			PIECESORTTYPE_RECT_DOWN		1	 //按外接矩形从大到小
#define			PIECESORTTYPE_PERI_DOWN		2	 //按周长从大到小
#define			PIECESORTTYPE_LENGTH_DOWN	3	 //按长度从大到小
#define			PIECESORTTYPE_HEIGHT_DOWN	4	 //按高度从大到小

//条格类型
#define			STRIPEPLAID_STRIPEPLAID		0	 //对条对格
#define			STRIPEPLAID_STRIPE			1	 //对条
#define			STRIPEPLAID_PLAID			2	 //对格
#define			STRIPEPLAID_MIDSTRIPE		3	 //对中


//				条格基点关联的对象
#define			PLSTOBJTYPE_NULL			0	 //无
#define			PLSTOBJTYPE_NOTCH			1	 //刀眼
#define			PLSTOBJTYPE_INNER			2	 //内线
#define			PLSTOBJTYPE_BOUND			3	 //轮廓
#define			PLSTOBJTYPE_SILK			4	 //丝缕
#define			PLSTOBJTYPE_TAG				5	 //标记


//				对条对格点的条格类别
#define			PLSTCATEGORY_ALL			0	 //对条和对格 ,包括对中，对条对格，对条，对格
#define			PLSTCATEGORY_STRIPE			1	 //对条,包括 对中，对条对格，对条
#define			PLSTCATEGORY_PLAID			2	 //对格,包括 对条对格，对格

#define			MAXLEVEL_STRIPEPLAID		10000 //条格最大等级

//边类型
#define			EGE_TOP						0	//上边
#define			EGE_LEFT					1	//左边
#define			EGE_BOTTOM					2	//下边

#define			SCLMATCHKNIFE_SP			0	// Sp-->Knife
#define			SCLMATCHKNIFE_COLOR			1	// Color-->Knife
#define			SCLMATCHKNIFE_LAYER			2	// Layer-->Knife
#define			SCLMATCHKNIFE_SPCLRLAY		3	// Sp+Color+Layer-->Knife

//操作类型
#define			OP_SELECT		200201		//选择状态
#define			OP_MOVE			200202		//移动样片
#define			OP_ZOOM_IN		200203		//放大
#define			OP_ZOOM_OUT		200204		//缩小
#define			OP_RECTANGLE	200205		//拉框放大
#define			OP_LINE_DRAW	200206		//画线,(直线和曲线)
#define			OP_LINE_BREAK	200207		//打断,(直线和曲线)
#define			OP_LINE_UNION	200208		//合并,(直线和曲线)
#define			OP_LINE_MOVE	200209		//移动,(直线和曲线)
#define			OP_LINE_PARA	200210		//平行,(直线和曲线)
#define			OP_LINE_MIRROR	200211		//镜像,(直线和曲线)
#define			OP_LINE_ADJUST	200212		//调整线,(直线和曲线)
#define			OP_LINE_ROTATE	200213		//旋转线,(直线和曲线)
#define			OP_LINE_CROSS	200214		//线求交点,(直线和曲线)
#define			OP_LINE_FITTED	200215		//线拟合,(直线和曲线)
#define			OP_ARC			200216		//圆弧


//				更新视图标志
#define			INVALIDATE_VIEW_UNMARK      200101
#define			INVALIDATE_VIEW_MARKED      200102
#define			INVALIDATE_VIEW_SPEC		200103
#define			INVALIDATE_VIEW_REC			200104

//				超级工具操作Id
#define			SUPEROP_MOVEWHEEL			200301		//滚轮放大
#define			SUPEROP_VIEWJING			200302		//显示净样


//				定义旋转范围类型
#define			RT_NONE					0 //不允许旋转
#define			RT_180					1 //180度
#define			RT_90					2 //90度旋转
#define			RT_45					3 //45度旋转
#define			RT_FREE					4 //任意角度旋转

//				定义翻转范围类型
#define			FLIP_NONE				0 //不允许翻转
#define			FLIP_X					1 //X方向翻转
#define			FLIP_Y					2 //Y方向翻转
#define			FLIP_XY					3 //XY方向翻转


//				定义缓冲类型
#define			GAPTYPE_WHOLE					0 //整体
#define			GAPTYPE_RECT					1 //包围盒
#define			GAPTYPE_CONVEXHULL				2 //凸包

#define			GAPTYPE_TOP						3 //上
#define			GAPTYPE_BOTTOM					4 //下
#define			GAPTYPE_LEFT					5 //左
#define			GAPTYPE_RIGHT					6 //右

#define			GAPTYPE_LEFTTOP					7 //左上
#define			GAPTYPE_LEFTBOTTOM				8 //左下

#define			GAPTYPE_RIGHTTOP				9 //右上
#define			GAPTYPE_RIGHTBOTTOM				10 //右下

#define			GAPTYPE_LTOPBOTTOM				11 //左上下
#define			GAPTYPE_RTOPBOTTOM				12 //右上下
#define			GAPTYPE_TLEFTRIGHT				13 //上左右
#define			GAPTYPE_BLEFTRIGHT				14 //下左右
#define			GAPTYPE_SPEC					15 //特别


//				平行线是对拐角的处理方式
#define			PARALL_CORNERTYPE_ONELINE			0 //一段线段连接
#define			PARALL_CORNERTYPE_TWOLINE			1 //两段线段连接
#define			PARALL_CORNERTYPE_ARC				2 //圆弧线连接
#define			PARALL_CORNERTYPE_EXTEND			3 //延长或者剪切
#define			PARALL_CORNERTYPE_NONE				4 //不处理

//				定义排料行为类型
#define			NESTBEHAVIOR_INDEPENDENT 0 //独立性
#define			NESTBEHAVIOR_RELEVANCE	 1 //关联性
#define			NESTBEHAVIOR_SHAPE		 2 //实例性


//				瑕疵样片类型
#define			FLAWTYPE_NORMAL			   0x00000000	   //普通样片
#define			FLAWTYPE_FABRIC			   0x00000001      //面料上的瑕疵(直线，矩形，多边形)
#define			FLAWTYPE_LEATHER_HOLE	   0x00000002	   //母版样片外接矩形区域内,母版样片内部的瑕疵样片
#define			FLAWTYPE_LEATHER_EGE	   0x00000003      //母版样片外接矩形区域内,母版样片外部的瑕疵样片
#define			FLAWTYPE_LEATHER_SURFACE   0x00000004      //不规则排料的母版样片
#define			FLAWTYPE_LEATHER_ZONES	   0x00000005      //分区排料的母版样片


//				款式类型
#define			MARKSTYLETYPE_NORMAL	    0x00000000		//普通款式
#define			MARKSTYLETYPE_IMPORT	    0x00000001		//外部数据款式
#define			MARKSTYLETYPE_LEATHER	    0x00000002		//皮料款式

//				面料瑕疵类型
#define			FABRIC_DEFECTTYPE_POINT		0x00000000		//点
#define			FABRIC_DEFECTTYPE_LINE		0x00000001		//直线段
#define			FABRIC_DEFECTTYPE_RECT		0x00000002		//矩形
#define			FABRIC_DEFECTTYPE_POLYGON	0x00000003		//多边形
#define			FABRIC_DEFECTTYPE_HLINE		0x00000004		//水平线
#define			FABRIC_DEFECTTYPE_VLINE		0x00000005		//垂直线


#define			FILETYPE_PLT				0
#define			FILETYPE_GBR				1
#define			FILETYPE_AAMA				2
#define			FILETYPE_DXF				3
#define			FILETYPE_ASTM				4

#define			MSGFROMSELF_EDITVIEW		0				//进入或者退出编辑视图
#define			MSGFROMSELF_PLSTVIEW		1				//进入或者退出条格编辑视图
#define			MSGFROMSELF_REDOUNDO		2				//前进后退
#define			MSGFROMSELF_UPDATELANGUAGE	3				//切换语言

#define			MSGFROMMCC_HIDEWND			0				//通知输出中心隐藏窗口
#define			MSGFROMMCC_TOPMOSTWND		1				//通知输出中心前置窗口
#define			MSGFROMMCC_UPDATEKNIFE		2				//通知输出中心更新刀具配置
#define			MSGFROMMCC_EXIT				3				//通知输出中心退出
#define			MSGFROMMCC_UPDATELANGUAGE	4				//通知输出中心更新语言
#define			MSGFROMMCC_READMATPIECE		5				//通知输出中心读取收料数据
#define			MSGFROMMCC_MULTITABLE		6				//通知输出中心读取多台面数据
#define			MSGFROMMCC_READDXFFILE		7				//通知输出中心读取外部数据


#define			MSGFTOMCC_HIDEWND			0				//通知控制中心隐藏窗口
#define			MSGFTOMCC_TOPMOSTWND		1				//通知控制中心前置窗口

//			    视图Id号定义
#define			VIEWID_MARKEDVIEW			0				//
#define			VIEWID_EDITVIEW				1
#define			VIEWID_TABLEVIEW			2
#define			VIEWID_PLSTVIEW				3
#define			VIEWID_UNMARKVIEW			4

//			    浮动窗口Id号定义
#define			DOCKWNDID_SIZEWND			0				//
#define			DOCKWNDID_PROPERTYWND		1				//
#define			DOCKWNDID_DYNVIEWWND		2				//
#define			DOCKWNDID_PLSTWND			3				//

#endif
