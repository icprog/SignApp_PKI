#include "libconfig.h"
#ifndef __DownLoad_H__
#define __DownLoad_H__

#undef MAX_RSA_MODULUS_LEN
#define FILELEN  584
#define MAX_RSA_MODULUS_LEN 256

#define DEBUG
#ifdef DEBUG
#define PDEBUG(fmt, args...) fprintf(stderr,  fmt, ##args);
#else
#define PDEBUG(fmt, args...)
#endif

//#define DOWNLOAD_PORT AUX1
#define  F1         0x01
#define  F2         0x02
#define  F3         0x03
#define  F4         0x04
#define  F5         0x05
#define  F6         0x06
#define  F7         0x07
#define  F8         0x08
#define  F9         0x09
#define  LEFT       0x13
#define  RIGHT      0x14
#define  UP         0x11
#define  DOWN       0x12
#define  MENU       F3
//ר�ü�
#define  BASP       0x0a    //backspace
#define  BACKSPACE  BASP
#define  CR         0x0D    //ȷ�ϼ�
#define  ENTER      CR
#define  ESC        0x1B
#define  ZMK        0x1C    //��ĸ��
#define  DOT        0x2E    //.
//���ּ�
#define ZERO        0x30
#define ONE         0x31
#define TWO         0x32
#define THREE       0x33
#define FOUR        0x34
#define FIVE        0x35
#define SIX         0x36
#define SEVEN       0x37
#define EIGHT       0x38
#define NINE        0x39

#define FALSE 0
#define TRUE (!FALSE)
#define  ESC        0x1B
#define FAIL (-1)
#define SUCC 0
#define FSFAIL  (-1)
#define QUIT (-2)
#define FUNCQUIT (-4)  //���ܼ��˳�
#define FSSUCC      0
extern int ErrorCode;
extern unsigned int g_language; /* 1 english, 0 chinese */
#define ETX     3

#define RMFL    200 /*Զ�����ص�֡��*/
#define AUX1 0
#define AUX2 1
#define AUX3 2

#define DOWNLOAD_PORT AUX1       /*����ttyS2 ��ӦAUX1����ʾ����0*/

#define PORT_NONE   (-1)// ���صĶ˿ڶ���
#define PORT_AUX    0       /*RS232����*/
//#define PORT_USB    (PORT_AUX+1)        [>USB����<]
#define PORT_USB    PORT_NUM_USB        /*USB����*/
#define USB_DISK    (PORT_USB+1)        /*U�����صķ�ʽ*/
#define MAX_MENU_NAME	256
#define ENQ     5

// ���������
#define DL_CMD_ENQ              ENQ     /* ��������*/
#define DL_CMD_TYPE             'T'     /* ��������*/
#define DL_CMD_PASSWORD         'P'     /* ��������*/
#define DL_CMD_FILENAMELEN      'L'     /* �����ļ�������*/
#define DL_CMD_FILENAME         'F'     /* �����ļ���*/
#define DL_CMD_FILEOWER         'R'     /* �����ļ�����*/
#define DL_CMD_RECEIVE_OK       'Z'     /* ����֡��ȷ����֮Ӧ��*/
#define DL_CMD_RESEND           'C'     /* ����֡�ط�*/
#define DL_CMD_FILEVER      'S'     /* ������֡����*/

// ����ͨѶ����
#define DL_ENQ_TYPE             (0X17)  /*�����������*/    //modify by zhengyn from 0X17 to 0X18 20110518
#define DL_PROC_UPT             (0X08)  /*�ϴ��ļ��б��������*/
#define DL_PROC_DOWN            (0X09)  /*�����ļ���������*/
#define DL_PROC_DEL             (0x0A)  /*ɾ����ѡӦ�ò�������*/
#define DL_PROC_PRIKEY          (0x30)  /*����˽Կ�ļ�*/
#define DL_PROC_PUBKEY          (0x31)

#ifdef  CONFIG_NLGP730_L1
#define DL_PROC_AUTH            (0x10)  /*PC������˫����֤*/    //modify by zhengyn from 0X10 to 0X11 20110518
#define DL_PROC_GETINFO         (0x11)  /*PC�������ȡPOS�Ļ�����Ϣ*/    //modify by zhengyn from 0X11 to 0X10 20110518
#endif

#define DL_CMD_KEEPOPER         'K'     /* ������������*/
#define DL_CMD_BATCH            'B'     /* �������ػ�ɾ������*/
#define DL_CMD_END              'E'     /* ���ػ�ɾ������*/

//�����ļ�·��
#define CSR_FILE	"MyCSR.pem"
#define CERT_FILE	"MyCert.pem"
#define CSR_DEFAULT_CONFIG_FILE	"req_default.ini"
#define CSR_CONFIG_FILE	"req.ini"
#define PRI_KEY_FILE "keyfile.pem"
#define CSR_SIGN_FILE "RecvCSR.pem"
#define NEW_CERT_FILE "NewSignedCert.pem"
#define CA_DEFAULT_CONFIG_FILE "CA_default.ini"
#define CA_CONFIG_FILE "CA.ini"
#define CA_FILE "CA.crt"


//copy from comm.c
/**
 * ����Ϊ�����Դ�ͳ����Э��ĺ궨��
 */

#define MAXSENDLEN	512

#define NONEENQ		0	//�ȴ� ENQ����
#define _TCHARFOR	1	//�ȴ� �ļ�����
#define _TCHARRET	2//11	//�ȴ� �ļ�����		��Ӧ
#define _PCHARFOR	3//2	//�ȴ� ��������
#define _PCHARRET	4//22	//�ȴ� ��������		��Ӧ
#define _NCHARFOR	5//3	//�ȴ� ɾ��������
#define _NCHARRET	6//33	//�ȴ� ɾ��������	��Ӧ
#define _RCHARFOR	7//4	//�ȴ� �ļ�����
#define _RCHARRET	8//44	//�ȴ� �ļ�����		��Ӧ
#define _SCHARFOR	9//5	//�ȴ� �����ļ�����
#define _SCHARRET	10//55	//�ȴ� �����ļ�����	��Ӧ
#define _sumCHARFOR 11//6	//�ȴ� ����У���

#define _LCHARFOR	12//7	//�ȴ� �ļ�������
#define _LCHARRET	13//77	//�ȴ� �ļ�������	��Ӧ
#define _FCHARFOR	14//8	//�ȴ� �ļ���
#define _FCHARRET	15//88	//�ȴ� �ļ���		��Ӧ
#define _TIMEFOR	16//9	//�ȴ� ����ʱ��
#define _TIMERET	17//99	//�ȴ� ����ʱ��		��Ӧ

// ����״̬
#define _NEWENQRET	18	//�ȴ������ź�NEW_ENQ(0x07)����Ӧ 0x017

//////////////////////////////////////////////////////////////////////////
// �����Ķ�Ӧ����������
//#define FL		2044 [>������Э���ַ���֡��, lipm modify '500' -> '2048-4', 090730 <]
#define FL		4044 /*������Э���ַ���֡��, lipm modify '500' -> '2048-4', 090730 */
#define DL_CMD_FILENAMELEN		'L'		/* �����ļ������� 0x4C*/
#define DL_CMD_FILENAME			'F' 	/* �����ļ��� 0x46*/
#define DL_CMD_FILELEN			'R' 	/* �����ļ����� 0x52*/
#define DL_CMD_RECEIVE_OK		'Z' 	/* ����֡��ȷ����֮Ӧ�� 0x5A*/
#define DL_CMD_RESEND			'C' 	/* ����֡�ط� 0x43*/
#define DL_CMD_SENDCERT			'A' 	/* ��������֤������*/

#define NEW_ENQ				0x07	//��BIOS����������
#define NEW_ENQ_ACK			0x17	//��BIOS������Ӧ��
#define GETAPPLIST			0x08	//��ȡPOSӦ���б�����
#define SENDOPERATION		0x09	//����������ʾPOS������ղ����б������

#define DL_PROC_KEY_LOAD	(0x20)  /*��Կ��������*/
#define DL_PROC_MUTUAL_AUTH	(0x21)  /*֤����������*/
#define DL_PROC_SET_OWNER	(0x22)  /*������Կ��������*/
#define DL_PROC_SET_DATETIME_SOFT	(0x24)  /*������Կ��������*/
#define DL_PROC_SET_DATETIME_HARD	(0x25)  /*������Կ��������*/

//////////////////////////////////////////////////////////////////////////

//����ѡ��
int g_Language; /* 1 english, 0 chinese */

typedef enum {
    LCDSIZE_128X64,
    LCDSIZE_128X160,
    LCDSIZE_240X320,
    LCDSIZE_MAX
} SCR_SIZE;

typedef struct st_item_details{
	char name[2][MAX_MENU_NAME];
	int (*func)(char *);
}st_item_details;

typedef struct {
    unsigned char owner[32];            /*˽Կ���з�*/
    unsigned char ver[16];               /*˽Կ�汾*/
    unsigned char info_reserved[16];
    unsigned int mod_bits;                    /*ģ��bitλ�� */
    unsigned char modulus[MAX_RSA_MODULUS_LEN];      /*ģ */
    unsigned int exp_bits;                    /*ָ��bitλ�� */
    unsigned char exponent[MAX_RSA_MODULUS_LEN];      /* ָ�� */
} R_RSA_PRIVATE_KEY;

#endif
void MessagePrint(char *szChinese, char *szEnglish,int time);
int init(void);
int HandShake();
int Trim(char* lpStr);
int sys_initconfig(char *path,config_t *cfg_file);
int PriKeyConfDeal(unsigned char *owner,unsigned char *ver,char *filenamebuf);
int strtobcd(char *pFilename,R_RSA_PRIVATE_KEY *prikey);
int PriFile_Creat(R_RSA_PRIVATE_KEY *prikey);
int GetNum(char *filename);
int SumSignature(R_RSA_PRIVATE_KEY *prikey);
int GetPriKeyFile();
int EnterNewDownload(R_RSA_PRIVATE_KEY *prikey);
int PriKeyDownload(R_RSA_PRIVATE_KEY *prikey);
int PriKeyInput();
int KeyDesEnc(char *file_name,char *name);
int PriKeyOutput();
int SetPassword(int flag);
int IsUdiskReady();
int IsSamICReady();
int SelectFunc(void);
st_item_details * build_menu(st_item_details *list);

