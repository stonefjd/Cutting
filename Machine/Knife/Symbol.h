#ifndef SYMBOL_H
#define SYMBOL_H

#define		GUID2CUTTOOLID(x)       (static_cast<short>((static_cast<int>(x))&0xff))
#define		GUID2KNIFEID(x)		  (static_cast<short>(((static_cast<int>(x))>>8)&0xff))
#define		KNIFETOOLID2GUID(a,b)	  (static_cast<int>((static_cast<short>(a))|((static_cast<short>(b))<<8)))

#define		ISCUTTOOLTYPE(a,b)	  ((static_cast<short>(SP2CUTTOOLID(a)) == (static_cast<short>(b)))

//ϵͳ����
const double	TOLERANCE_EQUAL  = 0.05;		// ϵͳ����,0.05���ף������غ��������
const double	TOLERANCE_INSERT = 0.05;		// ��ɢ����,0.05����

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

const int		MAX_SIZECOUNT  = 100;			// ��ϵͳ�����

const int		ANGLE_SCALE = 100;
const int		BUFFER_COMMON= 32;				// һ���ַ�������
const int		BUFFER_PATH= 260;				// һ�����ֵĳ���
const int		BUFFER_BIGPATH= 1024;			// ·�����ַ�������
const int		BUFFER_MAXSIZE = 32768;			// Ĭ�ϻ�������С
const int		MAX_INSERTNUM = 1000;			// Ԥ������ɢ����
const int		XMAX_INSERTNUM = 3000;			// Ԥ������ɢ���� (�ϴ�)
const int		MAX_DATANUM = 1000;			    // Ԥ������ɢ����
const double	MAX_LENGTH = 100000;			// �Ƚϴ�ĳ���ֵ��100�ף�
const int		TOLERANCE_CATCH  = 10;			// ѡ������ֵ��10�����أ�

const double	MAX_SCALE = 200000;				// ���Ŵ����
const double	MIN_SCALE = 0.0000001;			// ��С��С����
const double	BASE_SCALE = 6;					// ��ʼ������ ʵ�ʳߴ��1/6

const double    STRIP_HEIGHT = 0.5;				// �����߶� 0.5mm

//������
#define			POINT_START		0x00000011		// ��ʼ��
#define			POINT_CONTROL	0x00000012		// �۵�
#define			POINT_CURVE		0x00000003		// ����
#define			POINT_END		0x00000014		// ������
#define			POINT_ONLINE	0x00000005		// ���ϵ�
#define			POINT_ARC		0x00000006		// Բ����

#define			MARKP			0x000000f0
#define			MARKT			0x00000f00

#define			POINT_FLAT		0x00000100		// ƽ����
#define			POINT_CONVEX	0x00000200		// ��͹��
#define			POINT_INFLECT	0x00000400		// ̧����(�յ�)
#define			POINT_TRANSFER	0x00000800		// ���ɵ�(ǰ������ӽ�ֱ��)

#define			CONTROLPOINT(X)	((X & MARKP) == 0x00000010)	//�ж��Ƿ�Ϊ�۵�
#define			FLATPOINT(X)	((X & MARKT) == 0x00000100)	//�ж��Ƿ�Ϊƽ����
#define			CONVEXPOINT(X)	((X & MARKT) == 0x00000200) //�ж��Ƿ�Ϊ��͹��
#define			INFLECTPOINT(X)	((X & MARKT) == 0x00000400) //�ж��Ƿ�Ϊ̧����
#define			TRANSFERPOINT(X)((X & MARKT) == 0x00000800) //�ж��Ƿ�Ϊ���ɵ�

//��λ��ʶ(����dxf��׼)
const int		UNIT_MM = 4;					// ����,ϵ��=1
const int		UNIT_CM = 5;					// ���ף�ϵ��=10
const int		UNIT_INCH = 1;					// Ӣ�磬ϵ��=25.4
const int		UNIT_DM = 14;					// ���ף�ϵ��=100
const int		UNIT_FOOT = 2;					// Ӣ�ߣ�ϵ��=304.8
const int		UNIT_M = 6;						// �ף�ϵ��=1000
const int		UNIT_DMM = 8;					// ʮ��֮һ���ף�ϵ��=0.1
const int		UNIT_HMM = 9;					// �ٷ�֮һ���ף�ϵ��=0.01
const int		UNIT_MICROINCH = 10;			// �ٷ�֮һӢ�磬ϵ��=0.254
const int		UNIT_MILINCH = 11;				// ǧ��֮һӢ�磬ϵ��=0.0254
const int		UNIT_YARD = 12;				    // �룬ϵ��=914.4
const int		UNIT_KM = 7;					// ǧ�ף�ϵ��=1000000
const int		UNIT_MILE = 3;					// Ӣ�ϵ��=
const int		UNIT_DEFAULT = 0;				// Ĭ�ϵ�λ 

//��λϵ��
const double	FACTOR_MM = 1;					// ����,ϵ��=1
const double	FACTOR_CM = 10;					// ���ף�ϵ��=10
const double	FACTOR_INCH = 25.4;				// Ӣ�磬ϵ��=25.4
const double	FACTOR_DM = 100;				// ���ף�ϵ��=100
const double	FACTOR_FOOT = 304.8;			// Ӣ�ߣ�ϵ��=304.8
const double	FACTOR_YARD = 914.4;			// �룬ϵ��=914.4
const double	FACTOR_M = 1000;				// �ף�ϵ��=1000
const double	FACTOR_KM = 1000000;			// ǧ�ף�ϵ��=1000000
const double	FACTOR_DMM = 0.1;				// ʮ��֮һ���ף�ϵ��=0.1
const double	FACTOR_HMM = 0.01;				// �ٷ�֮һ���ף�ϵ��=0.01
const double	FACTOR_MICROINCH = 0.254;		// �ٷ�֮һӢ�磬ϵ��=0.254
const double	FACTOR_MILINCH = 0.0254;		// ǧ��֮һӢ�磬ϵ��=0.0254

const int		SCALE_TENTIME = 0;				// ϵ��=10
const int		SCALE_ONETIME = 1;				// ϵ��=1
const int		SCALE_DECI = 2;					// ϵ��=0.1
const int		SCALE_CENTI = 3;				// ϵ��=0.01
const int		SCALE_MILLI = 4;				// ϵ��=0.001

//Dxf�ļ�����
const int		DXFTYPE_AAMA = 0;				// Aama ��ʽ��Dxf�ļ�
const int		DXFTYPE_TIIP = 1;				// Tiip ��ʽ��Dxf�ļ�
const int		DXFTYPE_DXF = 2;				// dxf ��ʽ��Dxf�ļ�

//����id
const int		OPER_DART = 0;					//ʡ������id
const int		OPER_CRAFT = 1;					//���չ���id
const int		OPER_PEN = 2;					//���ܱ�id
const int		OPER_PATTERN = 3;				//��ͼ����id
const int		OPER_GRADE = 4;					//���빤��id
const int		OPER_DIGIT = 5;					//��ֵ���ǹ���id
const int		OPER_SEW = 6;					//�ŷ칤��id

#define			FONTNAME_DEFINE	  "Arial"		//Ĭ������
#define			DEFAULT_PIECESPEC "S"		    //Ĭ�Ϲ��
#define			DEFAULT_PIECEPAT  "Pat"			//Ĭ�ϰ���
//

//��ɫֵ
const int		COLORREF_RECT   = 0x000000ff;    // ��ɫ,RGB(255,0,0)
const int		COLORREF_RED    = 0x000000ff;    // ��ɫ,RGB(255,0,0)
const int		COLORREF_BLUE   = 0x00ff0000;    // ��ɫ,RGB(0,0,255)
const int		COLORREF_GREEN  = 0x0000ff00;    // ��ɫ,RGB(0,255,0)
const int		COLORREF_YEELOW = 0x0000ffff;    // ��ɫ,RGB(255,255,0)
const int		COLORREF_AQUA   = 0x00ffff00;    // ����,RGB(0,255,255)
const int		COLORREF_GRAY   = 0x00808080;    // ��ɫ,RGB(128,128,128)
const int		COLORREF_WHITE  = 0x00ffffff;    // ��ɫ,RGB(255,255,255)

//��ת����
//const int		ROTATETYPE_0 = 0;				 // 0
//const int		ROTATETYPE_180 = 1;				 // 0->180
//const int		ROTATETYPE_90 = 2;				 // 0->90
//const int		ROTATETYPE_45 = 3;				 // 0->45
//const int		ROTATETYPE_FREE = 4;			 // ����Ƕ�

//��������
const int		MARKTYPE_COMPLETE = 0;			 // ��ͨ����
const int		MARKTYPE_FIXEDLENGTH = 1;		 // ��������
const int		MARKTYPE_COLORSHADING = 2;		 // ����ɫ������
const int		MARKTYPE_TAOSET = 3;	         // ��������
const int		MARKTYPE_PACK = 4;	             // ��ѹ

//������������
const int		SUBGROUPTYPE_NONE = 0;			 // ������
const int		SUBGROUPTYPE_SIZE = 1;			 // ��������� ��ɫ������)
const int		SUBGROUPTYPE_TAO = 2;			 // ���׷���    (����)
const int		SUBGROUPTYPE_PIECE = 3;			 // ����ŷ���    (�����)

//��Ƭ����ʽ
#define			PIECESORTTYPE_AREA_DOWN		0	 //������Ӵ�С
#define			PIECESORTTYPE_RECT_DOWN		1	 //����Ӿ��δӴ�С
#define			PIECESORTTYPE_PERI_DOWN		2	 //���ܳ��Ӵ�С
#define			PIECESORTTYPE_LENGTH_DOWN	3	 //�����ȴӴ�С
#define			PIECESORTTYPE_HEIGHT_DOWN	4	 //���߶ȴӴ�С

//��������
#define			STRIPEPLAID_STRIPEPLAID		0	 //�����Ը�
#define			STRIPEPLAID_STRIPE			1	 //����
#define			STRIPEPLAID_PLAID			2	 //�Ը�
#define			STRIPEPLAID_MIDSTRIPE		3	 //����


//				�����������Ķ���
#define			PLSTOBJTYPE_NULL			0	 //��
#define			PLSTOBJTYPE_NOTCH			1	 //����
#define			PLSTOBJTYPE_INNER			2	 //����
#define			PLSTOBJTYPE_BOUND			3	 //����
#define			PLSTOBJTYPE_SILK			4	 //˿��
#define			PLSTOBJTYPE_TAG				5	 //���


//				�����Ը����������
#define			PLSTCATEGORY_ALL			0	 //�����ͶԸ� ,�������У������Ը񣬶������Ը�
#define			PLSTCATEGORY_STRIPE			1	 //����,���� ���У������Ը񣬶���
#define			PLSTCATEGORY_PLAID			2	 //�Ը�,���� �����Ը񣬶Ը�

#define			MAXLEVEL_STRIPEPLAID		10000 //�������ȼ�

//������
#define			EGE_TOP						0	//�ϱ�
#define			EGE_LEFT					1	//���
#define			EGE_BOTTOM					2	//�±�

#define			SCLMATCHKNIFE_SP			0	// Sp-->Knife
#define			SCLMATCHKNIFE_COLOR			1	// Color-->Knife
#define			SCLMATCHKNIFE_LAYER			2	// Layer-->Knife
#define			SCLMATCHKNIFE_SPCLRLAY		3	// Sp+Color+Layer-->Knife

//��������
#define			OP_SELECT		200201		//ѡ��״̬
#define			OP_MOVE			200202		//�ƶ���Ƭ
#define			OP_ZOOM_IN		200203		//�Ŵ�
#define			OP_ZOOM_OUT		200204		//��С
#define			OP_RECTANGLE	200205		//����Ŵ�
#define			OP_LINE_DRAW	200206		//����,(ֱ�ߺ�����)
#define			OP_LINE_BREAK	200207		//���,(ֱ�ߺ�����)
#define			OP_LINE_UNION	200208		//�ϲ�,(ֱ�ߺ�����)
#define			OP_LINE_MOVE	200209		//�ƶ�,(ֱ�ߺ�����)
#define			OP_LINE_PARA	200210		//ƽ��,(ֱ�ߺ�����)
#define			OP_LINE_MIRROR	200211		//����,(ֱ�ߺ�����)
#define			OP_LINE_ADJUST	200212		//������,(ֱ�ߺ�����)
#define			OP_LINE_ROTATE	200213		//��ת��,(ֱ�ߺ�����)
#define			OP_LINE_CROSS	200214		//���󽻵�,(ֱ�ߺ�����)
#define			OP_LINE_FITTED	200215		//�����,(ֱ�ߺ�����)
#define			OP_ARC			200216		//Բ��


//				������ͼ��־
#define			INVALIDATE_VIEW_UNMARK      200101
#define			INVALIDATE_VIEW_MARKED      200102
#define			INVALIDATE_VIEW_SPEC		200103
#define			INVALIDATE_VIEW_REC			200104

//				�������߲���Id
#define			SUPEROP_MOVEWHEEL			200301		//���ַŴ�
#define			SUPEROP_VIEWJING			200302		//��ʾ����


//				������ת��Χ����
#define			RT_NONE					0 //��������ת
#define			RT_180					1 //180��
#define			RT_90					2 //90����ת
#define			RT_45					3 //45����ת
#define			RT_FREE					4 //����Ƕ���ת

//				���巭ת��Χ����
#define			FLIP_NONE				0 //������ת
#define			FLIP_X					1 //X����ת
#define			FLIP_Y					2 //Y����ת
#define			FLIP_XY					3 //XY����ת


//				���建������
#define			GAPTYPE_WHOLE					0 //����
#define			GAPTYPE_RECT					1 //��Χ��
#define			GAPTYPE_CONVEXHULL				2 //͹��

#define			GAPTYPE_TOP						3 //��
#define			GAPTYPE_BOTTOM					4 //��
#define			GAPTYPE_LEFT					5 //��
#define			GAPTYPE_RIGHT					6 //��

#define			GAPTYPE_LEFTTOP					7 //����
#define			GAPTYPE_LEFTBOTTOM				8 //����

#define			GAPTYPE_RIGHTTOP				9 //����
#define			GAPTYPE_RIGHTBOTTOM				10 //����

#define			GAPTYPE_LTOPBOTTOM				11 //������
#define			GAPTYPE_RTOPBOTTOM				12 //������
#define			GAPTYPE_TLEFTRIGHT				13 //������
#define			GAPTYPE_BLEFTRIGHT				14 //������
#define			GAPTYPE_SPEC					15 //�ر�


//				ƽ�����ǶԹսǵĴ���ʽ
#define			PARALL_CORNERTYPE_ONELINE			0 //һ���߶�����
#define			PARALL_CORNERTYPE_TWOLINE			1 //�����߶�����
#define			PARALL_CORNERTYPE_ARC				2 //Բ��������
#define			PARALL_CORNERTYPE_EXTEND			3 //�ӳ����߼���
#define			PARALL_CORNERTYPE_NONE				4 //������

//				����������Ϊ����
#define			NESTBEHAVIOR_INDEPENDENT 0 //������
#define			NESTBEHAVIOR_RELEVANCE	 1 //������
#define			NESTBEHAVIOR_SHAPE		 2 //ʵ����


//				覴���Ƭ����
#define			FLAWTYPE_NORMAL			   0x00000000	   //��ͨ��Ƭ
#define			FLAWTYPE_FABRIC			   0x00000001      //�����ϵ�覴�(ֱ�ߣ����Σ������)
#define			FLAWTYPE_LEATHER_HOLE	   0x00000002	   //ĸ����Ƭ��Ӿ���������,ĸ����Ƭ�ڲ���覴���Ƭ
#define			FLAWTYPE_LEATHER_EGE	   0x00000003      //ĸ����Ƭ��Ӿ���������,ĸ����Ƭ�ⲿ��覴���Ƭ
#define			FLAWTYPE_LEATHER_SURFACE   0x00000004      //���������ϵ�ĸ����Ƭ
#define			FLAWTYPE_LEATHER_ZONES	   0x00000005      //�������ϵ�ĸ����Ƭ


//				��ʽ����
#define			MARKSTYLETYPE_NORMAL	    0x00000000		//��ͨ��ʽ
#define			MARKSTYLETYPE_IMPORT	    0x00000001		//�ⲿ���ݿ�ʽ
#define			MARKSTYLETYPE_LEATHER	    0x00000002		//Ƥ�Ͽ�ʽ

//				����覴�����
#define			FABRIC_DEFECTTYPE_POINT		0x00000000		//��
#define			FABRIC_DEFECTTYPE_LINE		0x00000001		//ֱ�߶�
#define			FABRIC_DEFECTTYPE_RECT		0x00000002		//����
#define			FABRIC_DEFECTTYPE_POLYGON	0x00000003		//�����
#define			FABRIC_DEFECTTYPE_HLINE		0x00000004		//ˮƽ��
#define			FABRIC_DEFECTTYPE_VLINE		0x00000005		//��ֱ��


#define			FILETYPE_PLT				0
#define			FILETYPE_GBR				1
#define			FILETYPE_AAMA				2
#define			FILETYPE_DXF				3
#define			FILETYPE_ASTM				4

#define			MSGFROMSELF_EDITVIEW		0				//��������˳��༭��ͼ
#define			MSGFROMSELF_PLSTVIEW		1				//��������˳�����༭��ͼ
#define			MSGFROMSELF_REDOUNDO		2				//ǰ������
#define			MSGFROMSELF_UPDATELANGUAGE	3				//�л�����

#define			MSGFROMMCC_HIDEWND			0				//֪ͨ����������ش���
#define			MSGFROMMCC_TOPMOSTWND		1				//֪ͨ�������ǰ�ô���
#define			MSGFROMMCC_UPDATEKNIFE		2				//֪ͨ������ĸ��µ�������
#define			MSGFROMMCC_EXIT				3				//֪ͨ��������˳�
#define			MSGFROMMCC_UPDATELANGUAGE	4				//֪ͨ������ĸ�������
#define			MSGFROMMCC_READMATPIECE		5				//֪ͨ������Ķ�ȡ��������
#define			MSGFROMMCC_MULTITABLE		6				//֪ͨ������Ķ�ȡ��̨������
#define			MSGFROMMCC_READDXFFILE		7				//֪ͨ������Ķ�ȡ�ⲿ����


#define			MSGFTOMCC_HIDEWND			0				//֪ͨ�����������ش���
#define			MSGFTOMCC_TOPMOSTWND		1				//֪ͨ��������ǰ�ô���

//			    ��ͼId�Ŷ���
#define			VIEWID_MARKEDVIEW			0				//
#define			VIEWID_EDITVIEW				1
#define			VIEWID_TABLEVIEW			2
#define			VIEWID_PLSTVIEW				3
#define			VIEWID_UNMARKVIEW			4

//			    ��������Id�Ŷ���
#define			DOCKWNDID_SIZEWND			0				//
#define			DOCKWNDID_PROPERTYWND		1				//
#define			DOCKWNDID_DYNVIEWWND		2				//
#define			DOCKWNDID_PLSTWND			3				//

#endif
