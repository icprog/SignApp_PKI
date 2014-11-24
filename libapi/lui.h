#ifndef _LUI_H_
#define _LUI_H_
#include "NDK.h"

#define KEY_0				'0'
#define KEY_1				'1'
#define KEY_2				'2'
#define KEY_3				'3'
#define KEY_4				'4'
#define KEY_5				'5'
#define KEY_6				'6'
#define KEY_7				'7'
#define KEY_8				'8'
#define KEY_9				'9'
#define KEY_F1				0x01
#define KEY_F2				0x02
#define KEY_F3				0x03
#define KEY_F4				0x04
#define KEY_F5				0x05
#define KEY_F6				0x06
#define KEY_F7				0x07
#define KEY_F8				0x08
#define KEY_F9				0x09
#define KEY_LEFT			KEY_F1
#define KEY_RIGHT			KEY_F2
#define KEY_UP				KEY_F1
#define KEY_DOWN			KEY_F2
#define KEY_UP_720			0x11
#define KEY_DOWN_720		0x12
#define KEY_LEFT_720		0x13
#define KEY_RIGHT_720		0x14
#define KEY_POINT			0x2e
#define KEY_BACK			0x0a		/**<�˸��*/
#define KEY_ENTER			0x0d		/**<ȷ�ϼ�*/
#define KEY_ESC				0x1b		/**<ȡ����*/
#define KEY_MENU			0x03		/**<�˵���*/
#define KEY_ENTERPAPER  	0xb1		/**<��ֽ��*/
#define KEY_BACKPAPER   	0xb2		/**<��ֽ��*/
#define KEY_NULL			0xfe		/**<�������޴˰�����ֵ��Ϊ0xfe*/

/*<POS���Ͷ���*/
#define NL8000				0x80
#define NL8080				0x88
#define NLE80				0xE8
#define NL8200				0x82
#define NL8300				0x83
#define NL8510				0x85
#define NLGP8510			0xF5
#define NLGP710				0x71
#define NLGP720				0x72
#define NLGP730				0x73
#define NLGP730CS			0x74		/**<730����*/
#define NLGP750				0x75
#define SP60				0xA6
#define SP80				0xA8

typedef enum
{
	MENU_TITLE_MUST = 0,				/**<Menu��������������*/
	MENU_TITLE_AUTO					/**<�����������Ӧ */
}EM_MENU_TITLE;

typedef enum
{
	DISPLAY_MODE_NORMAL=0,			/**<��ʾǰ������*/
	DISPLAY_MODE_CLEARLINE=1,			/**<��ʾǰ����*/
	DISPLAY_MODE_LEFT=2,				/**<������ʾ*/
	DISPLAY_MODE_CENTER=4,			/**<������ʾ*/
	DISPLAY_MODE_RIGHT=8,				/**<������ʾ*/
}EM_DISPLAY_MODE;

typedef enum
{
	DISPLAY_ALIGN_BIGFONT	=0,			/**<�����������ж���*/
	DISPLAY_ALIGN_SMALLFONT			/**<��С�������ж���*/
}EM_DISPLAY_ALIGN;

typedef enum
{
	TIME_MODE_HOUR_MIN_SEC=0,			/**<ʱ:��:��*/
	TIME_MODE_ONELINE_YMD_HM,			/**<һ����ʾ ��:��:�� ʱ:��*/
	TIME_MODE_TWOLINE_YMD_HM			/**<������ʾ ��:��:�� ʱ:��*/
}EM_TIME_MODE;

typedef enum 
{
	MENU_MODE_NONE = 0,				/**<������˵��˳�*/
	MENU_MODE_ESCCONFIRM = 0x01,		/**<�˳��Ƿ���Ҫȷ��*/
	MENU_MODE_ESC = 0x02,				/**<��ESC�˳�*/
	MENU_MODE_AUTOESC=0x03			/**<ִ�����Զ��˳�*/
}EM_MENU_MODE;

typedef enum
{
	INPUT_MODE_STRING,					/**<����ģʽ:һ���ִ�*/
	INPUT_MODE_NUMBER,					/**<����ģʽ:ֻ��������*/
	INPUT_MODE_PASSWD,					/**<����ģʽ:��������*/
	INPUT_MODE_AMOUNT,					/**<����ģʽ:���*/
	INPUT_MODE_NUMBERPOINT			/**<�������ֺ͵�*/
}EM_INPUT_MODE;

typedef enum
{
	INPUT_DATE_MODE_YYMM,				/**<���ڸ�ʽ����ģʽ*/
	INPUT_DATE_MODE_MMDD,
	INPUT_DATE_MODE_YYMMDD,
	INPUT_DATE_MODE_YYYYMMDD,
	INPUT_DATE_MODE_MMDD_NULL,
	INPUT_DATE_MODE_YYMM_NULL,
	INPUT_DATE_MODE_YYMMDD_NULL,
	INPUT_DATE_MODE_YYYYMMDD_NULL
}EM_INPUT_DATE_MODE;

typedef enum
{
	INPUT_AMOUNT_MODE_NONE,			/**<�����������Ϊ��(����Ľ��0)*/
	INPUT_AMOUNT_MODE_NOT_NONE		/**<�������������0*/
}EM_INPUT_AMOUNT_MODE;

typedef enum
{
	CHOOSE_IME_MODE_NUMPY,			/**<ѡ����ƴ*/
	CHOOSE_IME_MODE_ENGLISH ,			/**<ѡ��Ӣ��*/
	CHOOSE_IME_MODE_IME_NUM,    		/**<����*/
	CHOOSE_IME_MODE_IME_BIHUA,		/**<�ʻ�*/
	CHOOSE_IME_MODE_QUWEI				/**<ѡ����λ*/
}EM_CHOOSE_IME_MODE;

typedef struct
{
	char szContent[16];				/**<��Ŀ����         */
	int	(*action)(void);				/**<��Ŀִ�к�����ָ��*/
} STMENUTYPE;

typedef struct
{
	uchar ucSum;						/**<�˵�����*/
	uchar ucIndex;						/**<�˵�����*/
	uchar ucFlag;						/**<�˵���0��ʼ����1��ʼ*/
	uchar ucDefaultFlag;				/**<�Ƿ�Ĭ��1�ǣ�0��*/
	char szText[21][16+1];				/**< �˵���ʾ��Ϣ,���˵���21*/
}STMENU_LIST;

typedef struct
{
	EM_MENU_TITLE emMenu;						/**<EM_MENU_TITLE*/
	char szPageDown[4+1];						/**<��ҳ������ʾ��Ϣ*/
	char szPageUp[4+1];						/**<��ҳ������ʾ��Ϣ*/
}STUIFUN_STYLE;

/**
* @brief ȡUI��汾��
* @param [out] pszVer ���UI�汾��
* @return 
* @li��
* @author ��ε
* @date 2012-06-26
*/
void PubGetUIVer(char *pszVer);

/**
* @brief ��ȡPOS����
* @return 
* @li APP_FAIL ʧ��
* @li Others --�ɹ���NL8000,NL8080,NLE80,NL8200,NL8300,NL8510,NLGP8510,NLGP710,NLGP730,NLGP730CS
* @author ��ε
* @date 2012-07-12
*/
int PubGetPosType();

/**
* @brief ��ȡPOS����
* @return 
* @li NULL ʧ��
* @li POS�����ַ��� --�ɹ�
* @author ��ε
* @date 2013-05-27
*/
char * PubGetPosTypeStr();


/**
* @brief ��ʼ��UI������ʹ��UI��ǰ������øú���
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @author ��ε
* @date 2012-07-12
*/
int PubInitUiParam();

/**
* @brief ����UI�������
* @return 
* @li ��
* @author ��ε
* @date 2012-11-28
*/
void PubSetUiStyle(STUIFUN_STYLE stUiFunStyle);


/**
* @brief �����Ļ������
* @return 
* @li��
*/
void PubClearAll(void);

/**
* @brief �����Ļ�ĵڶ������һ�С�
* @return 
* @li ��
*/
void PubClear2To4 ( void );

/**
* @brief �����Ļĳ�У������壩����
* @param [in] ucStartLine ��Ҫ��յ��кſ�ʼ�У���1��ʼ
* @param [in] ucEndLine  ��Ҫ��յ��кŽ����У�ĩ�п�����(0xff)
* @return 
* @li ��
*/
void PubClearLine(uchar ucStartLine, uchar ucEndLine);

/**
* @brief �����Ļĳ�У�С���壩����
* @param [in] ucStartLine ��Ҫ��յ��кſ�ʼ�У���1��ʼ
* @param [in] ucEndLine  ��Ҫ��յ��кŽ����У�ĩ�п�����(0xff)
* @return 
* @li ��
*/
void PubClearLines(uchar ucStartLine, uchar ucEndLine);

/**
* @brief ��ȡ�������е��׸����̼�ֵ����������
* @return 
* @li ��������ֵ,�ް�������ʱΪ0
*/
int PubKbHit();

/**
* @brief ��ȡ����ֵ
* @param [in] nTimeout	��ʱʱ��
* @return 
* @li ��������ֵ
*/
int PubGetKeyCode(int nTimeout);

/**
* @brief ��ָ��λ�ð���ʽ��ʾ���ַ�������ʾ�����ַ���
* @param [in] nMode   ��ʾģʽ---EM_DISPLAY_MODE 
* @param [in] nLineno ָ����λ�ã���1��ʼ
* @param [in] nClumno ָ����λ�ã���1��ʼ
* @param [in] pFormat ��ʾ��ʽ 
* @return 
* @li ��
*/
void PubDisplayStr(int nMode, int nLineno, int nClumno, char * pFormat,...);

/**
* @brief ��ָ��λ�ð���ʽ��ʾС�ַ���(��ʾ�����ַ�)
* @param [in] nAlign   С����Ķ���ģʽ---EM_DISPLAY_ALIGN
* @param [in] nMode   ��ʾģʽ---EM_DISPLAY_MODE
* @param [in] nLineno ָ����λ�ã���1��ʼ
* @param [in] nClumno ָ����λ�ã���1��ʼ
* @param [in] pFormat ��ʾ��ʽ 
* @return 
* @li ��
*/
void PubDisplayStrs(int nAlign, int nMode, int nLineno, int nClumno, char *pFormat,...);

/**
* @brief ��POS��Ļָ���У�������ʾ���ַ�������ʾǰ���У�
* @param [in] pStr    �����ַ���
* @param [in] nLineno ָ����λ�ã���1��ʼ
* @return 
* @li ��
*/
void PubDisplayGen(int nLineno, char *pStr); 

/**
* @brief ��POS��Ļָ���У�������ʾС�ַ�������ʾǰ���У�
* @param [in] nAlign   С����Ķ���ģʽ---EM_DISPLAY_ALIGN
* @param [in] pStr    �����ַ���
* @param [in] nLineno ָ����λ�ã���1��ʼ
* @return 
* @li ��
*/
void PubDisplayGens(int nAlign, int nLineno, char *pStr);

/**
* @brief ��POS��Ļָ���з�����ʾ���ַ���
* @param [in] pStr    �����ַ���
* @param [in] nLineno ָ����λ�ã�ȡֵ��ΧΪ1~7
* @return 
* @li ��
*/
void PubDisplayInv(int nLineno, char *pstr);

/**
* @brief ��POS��Ļָ���з�����ʾС�ַ�������ʾǰ���У�
* @param [in] nAlign   С����Ķ���ģʽ---EM_DISPLAY_ALIGN
* @param [in] nLineno ָ����λ�ã���1��ʼ
* @param [in] pStr    �����ַ���
* @return 
* @li ��
*/
void PubDisplayInvs(int nAlign, int nLineno, char *pstr); 

/**
* @brief ��ʾ����
* @param [in] pszTitle ---��ʾ����
* @return 
* @author ���
* @date 2012-7-23
*/
void PubDisplayTitle(char *pszTitle);

/**
* @brief ��ĩ��ʾ
* @param [in] nFont	����
* @param [in] nMode	��ʾģʽ---EM_DISPLAY_MODE 
* @param [in] nIsInv	�Ƿ񷴰���ʾ0����1����
* @param [in] pFormat	��ʾ����
* @return 
*/
void PubDisplayTail(int nFont, int nMode, int nIsInv, char * pFormat,...);

/**
* @brief ��ָ��λ����ʾ����(��С)�ַ���
* @param [in] nFont	0 ������, 1 С����
* @param [in] nLineno	ָ����λ�ã�ȡֵ��ΧΪ1~8
* @param [in] nClumno	ָ����λ��,ȡֵ��ΧΪ1~16
* @param [in] pFormat		��ʾ����
* @return 
* @li ��
*/
void PubDispMultLines(int nFont, int nLineno, int nClumno, char * pFormat,...);

/**
* @brief ��ָ������ʾ(��С)�ַ���
* @param [in] nFont	0 ������, 1 С����
* @param [in] nLineno	ָ����λ�ã�ȡֵ��ΧΪ1~8
* @param [in] pStr		��ʾ���ݴ���ʽL����C����R���ҡ�����("L%s|C%s|R%s",szLeft,szCenter,szRight)
* @return 
* @li ��
*/
void PubDispStrFormat(int nFont, int nLineno, char * pFormat,...);

/**
* @brief ��ȡָ����ʽ(��С)�ַ������ɶ�������
* @param [in] nFont	0 ������, 1 С����
* @param [in] pFormat ��ʾ��ʽ: ���ݴ���ʽL����C����R���ҡ�����("L%s|C%s|R%s",szLeft,szCenter,szRight)
* @param [out] pOutStr ����ʽ������ַ���
* @return 
* @li ��
*/
void PubGetStrFormat(int nFont, char * pOutStr, char * pFormat,...);

/**
* @brief ��ʾͼ�ο�Ϊ64��Ϊ48��ͼƬ
* @param [in] pszPath Ҫ��ʾ��ͼƬ·��
* @return 
* @li ��
*/
void PubDisplayLogo(char *pszPath, int nX, int nY);

/**
* @brief ��ʾʱ��
* @param [in] nLineno ָ����λ�ã�ȡֵ��ΧΪ1~8
* @param [in] nClumno ָ����λ��,ȡֵ��ΧΪ1~16
* @param [in] nStyle  ʱ����ʾ���---EM_SHOWTIME_MODE
* @return 
* @li ��
*/
void PubShowRtc(int nLineno, int nClumno, int nStyle);

/**
* @brief �ر�ʱ����ʾ
* @return 
* @li ��
*/
void PubCloseShowRtc(void);

/**
* @brief ��ȡһ�������ź�ֵ����(6+12)*12ͼ����ʾ
* @param [in] nX ����λ��,ȡֵ��ΧΪ0~127
* @param [in] nY ����λ��,ȡֵ��ΧΪ0~63
* @return 
* @li ��
*/
void PubShowSignal(int nX, int nY);

/**
* @brief ��ȡһ�ε�Դ��ѹֵ����12*12ͼ����ʾ
* @param [in] nX ����λ��,ȡֵ��ΧΪ0~127
* @param [in] nY ����λ��,ȡֵ��ΧΪ0~63
* @return 
* @li ��
*/
void PubShowBattery(int nX, int nY);

/**
* @brief ״̬����ʾ
* @return 
* @li ��
*/
void PubShowStatusBar();

/**
* @brief �ر�״̬����ʾ
* @return 
* @li ��
*/
void PubCloseShowStatusBar();

/**
* @brief ��POS��Ļָ���У�����ʽ��ʾ���ַ���(��ʾ�����ַ�)
* @param [in] nMode	��ʾģʽ---EM_DISPLAY_MODE
* @param [in] nLineno ָ����λ�ã���1��ʼ
* @param [in] pFormat ��ʾ��ʽ
* @return 
* @li ��
*/
void PubDisplayStrInline(int nMode, int nLineno, char *pFormat,...);

/**
* @brief ��POS��Ļָ���У�����ʽ��ʾС�ַ���(��ʾ�����ַ�)
* @param [in] nAlign   С����Ķ���ģʽ---EM_DISPLAY_ALIGN
* @param [in] nMode	��ʾģʽ---EM_DISPLAY_MODE
* @param [in] nLineno ָ����λ�ã���1��ʼ
* @param [in] pFormat ��ʾ��ʽ
* @return 
* @li ��
*/
void PubDisplayStrInlines(int nAlign, int nMode, int nLineno, char *pFormat,...);

/**
* @brief �Ӽ��̶����ִ�
* @param [in] nX        ��λ��(1<= nX <=16)
* @param [in] nY        ��λ��(1<= nY <=8)
* @param [in] nMinLen   ��С���볤��
* @param [in] nMaxLen   ������볤��
* @param [in] nTimeOut  ���볬ʱʱ��
* @param [in] nEditMask ����ģʽ---EM_INPUT_MODE
* @param [out] pszOut   ���뻺����
* @param [out] pnOutLen ������ַ�����
* @return 
* @li APP_TIMEOUT ��ʱ�˳�
* @li APP_FAIL    ��ʾ�쳣�˳�
* @li APP_QUIT    �û��˳�����
* @li APP_SUCC    ����ɹ�
*/
int PubInputxy(int nX, int nY, char* pszOut, int* pnOutLen, int nMinLen, int nMaxLen, int nTimeOut, int nEditMask);

/**
* @brief ����Ի���
* @param [in] pszTitle   �Ի������
* @param [in] pszContent �Ի�����ʾ��Ϣ
* @param [in] nMinLen    ��С���볤��
* @param [in] nMaxLen    ������볤��
* @param [in] nTimeOut   ���볬ʱʱ��
* @param [in] nEditMask  ����ģʽ---EM_INPUT_MODE
* @param [out] pszOut    ���뻺����
* @param [out] pnOutLen  ������ַ�����
* @return 
* @li APP_TIMEOUT ��ʱ�˳�
* @li APP_FAIL    ��ʾ�쳣�˳�
* @li APP_QUIT    �û��˳�����
* @li APP_SUCC    ����ɹ�
*/
int PubInputDlg(const char *pszTitle, const char *pszContent, char *pszOut, int *pnOutLen, \
				int nMinLen, int nMaxLen, int nTimeOut, int nEditMask);

/**
* @brief ����Ի���
* @param [in] pszTitle   �Ի������
* @param [in] pszContent �Ի�����ʾ��Ϣ
* @param [in] pInfo      ���û��ΪNULL
* @param [in] x          x����
* @param [in] y          y����
* @param [in] nMinLen    ��С���볤��
* @param [in] nMaxLen    ������볤��
* @param [in] nTimeOut   ���볬ʱʱ��
* @param [in] nEditMask  ����ģʽ---EM_INPUT_MODE
* @param [out] pszOut    ���뻺����
* @param [out] pnOutLen  ������ַ�����
* @return 
* @li APP_TIMEOUT ��ʱ�˳�
* @li APP_FAIL    ��ʾ�쳣�˳�
* @li APP_QUIT    �û��˳�����
* @li APP_SUCC    ����ɹ�
*/
int PubExtInputDlg(const char *pszTitle, const char *pszContent, char* psInfo, \
                int x, int y, char *pszOut, int *pnOutLen,int nMinLen, \
                int nMaxLen, int nTimeOut, int nEditMask);

/**
* @brief ��ʾ�Ի���
* @param [in] pszTitle   �Ի������
* @param [in] pszContent �Ի�����ʾ��Ϣ
* @param [in] nBeep      ��ʾ�������
* @param [in] nTimeOut   ���볬ʱʱ��
* @return 
* @li APP_TIMEOUT ��ʱ�˳�
* @li APP_SUCC    ����ɹ�
*/
int PubMsgDlg(const char *pszTitle, const char *pszContent, int nBeep, int nTimeOut);

/**
* @brief ȷ�϶Ի���
* @param [in] pszTitle   �Ի������
* @param [in] pszContent �Ի�����ʾ��Ϣ
* @param [in] nBeep      ��ʾ�������
* @param [in] nTimeOut   ���볬ʱʱ��
* @return 
* @li APP_TIMEOUT ��ʱ�˳�
* @li APP_QUIT    �û�ȡ��
* @li APP_SUCC    �û�ȷ��
*/
int PubConfirmDlg(const char *pszTitle, const char *pszContent, int nBeep, int nTimeOut);

/**
* @brief �������ڶԻ���
* @param [in] pszTitle   �Ի������
* @param [in] pszContent �Ի�����ʾ��Ϣ
* @param [in] nFormat    ���ڸ�ʽ---EM_INPUT_DATE_MODE
* @param [in] nTimeOut   ���볬ʱʱ��
* @param [out] pszDate   ����
* @return 
* @li APP_FAIL    ��ʾ�쳣�˳�
* @li APP_TIMEOUT ��ʱ�˳�
* @li APP_QUIT    �û��˳�����
* @li APP_SUCC    ��ʾ����ɹ�
*/
int PubInputDate(const char *pszTitle, const char *pszContent, char *pszDate, int nFormat, int nTimeOut);

/**
* @brief �������ڶԻ���
* @param [in] pszTitle   �Ի������
* @param [in] pszContent �Ի�����ʾ��Ϣ
* @param [in] pInfo      ���û��ΪNULL
* @param [in] x          x����
* @param [in] y          y����
* @param [in] nFormat    ���ڸ�ʽ---EM_INPUT_DATE_MODE
* @param [in] nTimeOut   ���볬ʱʱ��
* @param [out] pszDate   ����
* @return 
* @li APP_FAIL    ��ʾ�쳣�˳�
* @li APP_TIMEOUT ��ʱ�˳�
* @li APP_QUIT    �û��˳�����
* @li APP_SUCC    ��ʾ����ɹ�
*/
int PubExtInputDate(const char *pszTitle, const char *pszContent, const char *pInfo, int x, int y,\
					char *pszDate,int nFormat, int nTimeOut);

/**
* @brief ������Ի���
* @param [in] pszTitle   �Ի������
* @param [in] pszContent �Ի�����ʾ��Ϣ
* @param [in] nNoneFlag  EM_INPUT_AMOUNT_MODE
* @param [in] nMaxLen    ������볤��
* @param [in] nTimeOut   ���볬ʱʱ��
* @param [out] pszAmount ���
* @param [out] pnInputLen ���볤��
* @return 
* @li APP_TIMEOUT ��ʱ�˳�
* @li APP_FAIL    ��ʾ�쳣�˳�
* @li APP_QUIT    �û��˳�����
* @li APP_Others  ����ĳ���
*/
int PubInputAmount(const char *pszTitle, const char *pszContent, char *pszAmount, int *pnInputLen,\
				   int nNoneFlag, int nTimeOut);

/**
* @brief ���뺺�ֶԻ���
* @param [in] pszStr      �Ի����ʼֵ
* @param [in] nMinLen     �������С����
* @param [in] nMaxLen     �������󳤶�
* @param [in] nImeMode    Ĭ��ѡ������뷨---EM_CHOOSE_IME_MODE
* @param [out] pszStr     ������Ϣ
* @param [out] pnInputLen ����ĳ���
* @return 
* @li APP_FAIL    ��ʾ�쳣�˳�
* @li APP_TIMEOUT ��ʱ�˳�
* @li APP_QUIT    �û��˳�����
* @li APP_SUCC    ��ʾ����ɹ�
*/
int PubInputCNMode(const char *pszTitle, const char *pszContent,char *pszStr, int *pnInputLen, int nMinLen, int nMaxLen, int nImeMode);

/**
* @brief �˵���ʾ���� ��ʾҳ�桢������
* @param [in] pstMenu      �˵�ָ��
* @param [in] pszTitle     �˵����⣬���û�о�ΪNULL
* @param [in] cMenuFlag    �˵���־---MENU_OPTION
* @param [in] (*pnTimer)() ��̨��������ָ�룬���û�о�ΪNULL
* @param [in] nInterval    ��ͣ���˵�����ʱ�򣬼��ʱ�����pnTimer
* @return 
* @li APP_FAIL ��ʾpstMenu��ʽ����ʶ��
* @li APP_QUIT �û��˳�����
*/
int PubOpenMenu(const STMENUTYPE *pstMenu, const char *pszTitle, char cMenuFlag, int(*pnTimer)(), int nInterval);

/**
* @brief �˵���ʾ���� ��ʾҳ�桢������
* @param [in] pstMenu      �˵�ָ��
* @param [in] pszTitle     �˵����⣬���û�о�ΪNULL
* @param [in] cMenuFlag    �˵���־---MENU_OPTION
* @return 
* @li APP_FAIL ��ʾpstMenu��ʽ����ʶ��
* @li APP_QUIT �û��˳�����
*/
int PubOpenEasyMenu(const STMENUTYPE * pstMenu, const char * pszTitle, char cMenuFlag);

/**
* @brief �б���ʾҪѡ�����Ŀ
* @param [in] pszStr       �б����ݣ���'|'����
* @param [in] pszTitle     �˵����⣬���û�о�ΪNULL
* @param [in] pszContent   �˵�������ʾ��û����ΪNULL
* @param [in] nDefault     Ĭ�ϵ�ѡ��(0-9)����Ĭ��Ϊ0
* @param [out] pnItemnum   ���ص�ѡ��� ��ֵ
* @return 
* @li APP_FAIL ��ʾpstMenu��ʽ����ʶ��
* @li APP_QUIT �û��˳�����
* @li APP_SUCC �û���������ȷ��ѡ��
*/
int PubSelectListItem(const char *pszStr, const char *pszTitle, const char* pszContent, int nDefault, int *pnItemnum);

/**
* @brief �б���ʾҪѡ�����Ŀ
* @param [in] pszStr       �б����ݣ���'|'����
* @param [in] pszTitle     �˵����⣬���û�о�ΪNULL
* @param [in] pszContent   �˵�������ʾ��û����ΪNULL
* @param [in] nDefault     Ĭ�ϵ�ѡ��(0-9)����Ĭ��Ϊ0
* @param [in] PnItemnum    ���ص�ѡ��� ��ֵ
* @param [in] nTimeOut     �ȴ�������ʱʱ��
* @param [in] pszFunKey    �ڴ����ع��ܼ��봮�����û����ΪNULL
* @param [out] pnItemnum   �ͻ����ڵ���Ŀ(1-9)
* @return 
* @li APP_FAIL ��ʾpszStr��ʽ����ʶ��,��ʾ��Ŀ�����
* @li APP_QUIT �û��˳�����
* @li APP_SUCC �û���������ȷ��ѡ��
*/
int PubSelectListItemExtend( const char* pszStr, const char* pszTitle, const char* pszContent, int nDefault,\
							int* pnItemNum, int nTimeOut, char* pszFunKey);

/**
* @brief ��ʾͼƬ������
* @param [in] unWidth		ͼƬ��ʾ�Ŀ�
* @param [in] unHeight		ͼƬ��ʾ�ĸ�
* @param [in] pszBmp  		ͼƬ�ļ�����
* @param [in] pszStr     	�����б����ݣ���'|'����ѡ�����ֱ����ʾ����
* @param [out] PnItemnum    ���ص�ѡ��
* @return 
* @li ��
*/
void PubDrawBitmapList(const uint unWidth, const uint unHeight, const char *pszBitmap, const char *pszStr, int nTimeout, int* pnItemNum);

/**
* @brief ��ʾͼƬ������
* @param [in] unWidth		ͼƬ��ʾ�Ŀ�
* @param [in] unHeight		ͼƬ��ʾ�ĸ�
* @param [in] pszPic   		ͼƬ�ļ����ڵ�·��
* @param [in] pszStr     	�����б����ݣ���'|'����ѡ�����ֱ����ʾ����
* @param [out] PnItemnum    ���ص�ѡ��
* @return 
* @li ��
*/
void PubDispPicList(const uint unWidth, const uint unHeight, const char *pszPic, const char *pszStr, int nTimeout, int* pnItemNum);

/**
* @brief �˵��б���ʾѡ��
* @param [in] pszTitle  �˵����⣬���û�о�ΪNULL
* @param [in] pstMenu   �˵��б�
* @param [in] pszFunKey ���ܼ��б�,����޴���NULL,
* @param [in] nTimeOut  ������ʱʱ��
* @param [in] nTimeOut  �ȴ�������ʱʱ��
* @param [out] pnKey    �������,��������˵���ֵ������ǹ��ܼ���������ܼ�ֵ+0xff
* @return 
* @li APP_FAIL    ��ʾpszStr��ʽ����ʶ��,��ʾ��Ŀ�����
* @li APP_TIMEOUT ��ʱ�˳�
* @li APP_SUCC    �û���������ȷ��ѡ��
*/
int PubDispSelectMenu (const char * pszTitle, STMENU_LIST * pstMenu, const char* pszFunKey, int nTimeOut, int* pnKey);

/**
* @brief ����IP
* @param [in] pszTitle   �˵�����
* @param [in] pszContent �˵�������ʾ
* @param [in] pnOutLen   �����ַ���pszOut�ĳ���
* @param [out] pszOut    �����IP
* @param [out] pnOutLen  �����ַ���pszOut�ĳ���
* @return
* @li APP_QUIT    �˳�
* @li APP_SUCC    ��ȷ
*/
int PubInputIp(const char * pszTitle, const char * pszContent, char * pszOut, int * pnOutLen);

/**
* @brief ����Pin����
* @param [in] pszTitle    ---����
* @param [in] pszAmount   ---����Ľ�����NULL
* @param [in] pszContent  ---��ʾ���ݻ���NULL
* @param [in] nMinLen     ---���������Сλ��
* @param [in] nMaxLen     ---����������λ��
* @param [out] pszOut     ---��������
* @return 
* @li APP_SUCC  ---�ɹ�
* @li APP_FAIL  ---ʧ�� 
* @author ���
* @date 2012-7-23
*/
int PubInputPin(const char *pszTitle,const char * pszAmount,const char * pszContent,int nMinLen, int nMaxLen,char *pszOut);

/**
* @brief ���·�ҳ��ʾ�Ի���
* @param [in] pszTitle     ---����
* @param [in] pszContent   ---��ʾ����
* @param [in] nIsResKey	---�Ƿ���Ӧ����YES or No
* @param [in] nTimeOut     ---��ʱʱ��
* @param [out] nResKey	---���ذ���ֵ
* @return 
* @li APP_SUCC  ---�ɹ�
* @li APP_QUIT  ---�˳�
* @li APP_FAIL  ---ʧ�� 
* @author ���
* @date 2012-8-2
*/
int PubUpDownMsgDlg(const char* pszTitle,const char* pszContent,int nIsResKey,int nTimeOut,int* nResKey);

/**
* @brief ȷ�϶Ի���(F1F2��ҳ)
* @param [in] pszTitle	 �Ի������
* @param [in] pszContent �Ի�����ʾ��Ϣ
* @param [in] nBeep 	 ��ʾ�������
* @param [in] nTimeOut	 ���볬ʱʱ��
* @return 
* @li TIMEOUT ��ʱ�˳�
* @li APP_QUIT	  �û�ȡ��
* @li APP_SUCC	  �û�ȷ��
*/
int PubUpDownConfirmDlg(const char* pszTitle,const char* pszContent,int nBeep,int nTimeOut);

/**
* @brief ������ʾ���� 
* @param ��
* @return ��
* @author ���
* @date 2012-7-20
*/
void PubUpdateWindow(void);

/**
* @brief ��ʾ������
* @param [in] pszTitle ��ʾ����
* @return 
* @li APP_SUCC  ---�޴���
* @li APP_FAIL  ---�д�����ʾ������
*/
int PubDispErr(const char *pszTitle);

#endif

