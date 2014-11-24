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
//专用键
#define  BASP       0x0a    //backspace
#define  BACKSPACE  BASP
#define  CR         0x0D    //确认键
#define  ENTER      CR
#define  ESC        0x1B
#define  ZMK        0x1C    //字母键
#define  DOT        0x2E    //.
//数字键
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
#define FUNCQUIT (-4)  //功能键退出
#define FSSUCC      0
extern int ErrorCode;
extern unsigned int g_language; /* 1 english, 0 chinese */
#define ETX     3

#define RMFL    200 /*远程下载的帧长*/
#define AUX1 0
#define AUX2 1
#define AUX3 2

#define DOWNLOAD_PORT AUX1       /*串口ttyS2 对应AUX1，表示串口0*/

#define PORT_NONE   (-1)// 下载的端口定义
#define PORT_AUX    0       /*RS232串口*/
//#define PORT_USB    (PORT_AUX+1)        [>USB串口<]
#define PORT_USB    PORT_NUM_USB        /*USB串口*/
#define USB_DISK    (PORT_USB+1)        /*U盘下载的方式*/
#define MAX_MENU_NAME	256
#define ENQ     5

// 下载命令定义
#define DL_CMD_ENQ              ENQ     /* 下载请求*/
#define DL_CMD_TYPE             'T'     /* 下载类型*/
#define DL_CMD_PASSWORD         'P'     /* 下载密码*/
#define DL_CMD_FILENAMELEN      'L'     /* 下载文件名长度*/
#define DL_CMD_FILENAME         'F'     /* 下载文件名*/
#define DL_CMD_FILEOWER         'R'     /* 下载文件长度*/
#define DL_CMD_RECEIVE_OK       'Z'     /* 下载帧正确接收之应答*/
#define DL_CMD_RESEND           'C'     /* 下载帧重发*/
#define DL_CMD_FILEVER      'S'     /* 请求下帧数据*/

// 新增通讯命令
#define DL_ENQ_TYPE             (0X17)  /*请求操作类型*/    //modify by zhengyn from 0X17 to 0X18 20110518
#define DL_PROC_UPT             (0X08)  /*上传文件列表操作类型*/
#define DL_PROC_DOWN            (0X09)  /*下载文件操作类型*/
#define DL_PROC_DEL             (0x0A)  /*删除所选应用操作类型*/
#define DL_PROC_PRIKEY          (0x30)  /*下载私钥文件*/
#define DL_PROC_PUBKEY          (0x31)

#ifdef  CONFIG_NLGP730_L1
#define DL_PROC_AUTH            (0x10)  /*PC端请求双向认证*/    //modify by zhengyn from 0X10 to 0X11 20110518
#define DL_PROC_GETINFO         (0x11)  /*PC端请求获取POS的机型信息*/    //modify by zhengyn from 0X11 to 0X10 20110518
#endif

#define DL_CMD_KEEPOPER         'K'     /* 继续操作命令*/
#define DL_CMD_BATCH            'B'     /* 继续下载或删除命令*/
#define DL_CMD_END              'E'     /* 下载或删除结束*/

//新增文件路径
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
 * 以下为拷贝自传统下载协议的宏定义
 */

#define MAXSENDLEN	512

#define NONEENQ		0	//等待 ENQ请求
#define _TCHARFOR	1	//等待 文件类型
#define _TCHARRET	2//11	//等待 文件类型		响应
#define _PCHARFOR	3//2	//等待 下载密码
#define _PCHARRET	4//22	//等待 下载密码		响应
#define _NCHARFOR	5//3	//等待 删除扇区数
#define _NCHARRET	6//33	//等待 删除扇区数	响应
#define _RCHARFOR	7//4	//等待 文件长度
#define _RCHARRET	8//44	//等待 文件长度		响应
#define _SCHARFOR	9//5	//等待 发送文件内容
#define _SCHARRET	10//55	//等待 发送文件内容	响应
#define _sumCHARFOR 11//6	//等待 接收校验和

#define _LCHARFOR	12//7	//等待 文件名长度
#define _LCHARRET	13//77	//等待 文件名长度	响应
#define _FCHARFOR	14//8	//等待 文件名
#define _FCHARRET	15//88	//等待 文件名		响应
#define _TIMEFOR	16//9	//等待 下载时间
#define _TIMERET	17//99	//等待 下载时间		响应

// 新增状态
#define _NEWENQRET	18	//等待握手信号NEW_ENQ(0x07)的响应 0x017

//////////////////////////////////////////////////////////////////////////
// 新增的多应用下载流程
//#define FL		2044 [>不包括协议字符的帧长, lipm modify '500' -> '2048-4', 090730 <]
#define FL		4044 /*不包括协议字符的帧长, lipm modify '500' -> '2048-4', 090730 */
#define DL_CMD_FILENAMELEN		'L'		/* 下载文件名长度 0x4C*/
#define DL_CMD_FILENAME			'F' 	/* 下载文件名 0x46*/
#define DL_CMD_FILELEN			'R' 	/* 下载文件长度 0x52*/
#define DL_CMD_RECEIVE_OK		'Z' 	/* 下载帧正确接收之应答 0x5A*/
#define DL_CMD_RESEND			'C' 	/* 下载帧重发 0x43*/
#define DL_CMD_SENDCERT			'A' 	/* 新增发送证书命令*/

#define NEW_ENQ				0x07	//新BIOS的握手请求
#define NEW_ENQ_ACK			0x17	//新BIOS的握手应答
#define GETAPPLIST			0x08	//获取POS应用列表命令
#define SENDOPERATION		0x09	//发送命令提示POS进入接收操作列表的流程

#define DL_PROC_KEY_LOAD	(0x20)  /*密钥下载命令*/
#define DL_PROC_MUTUAL_AUTH	(0x21)  /*证书下载命令*/
#define DL_PROC_SET_OWNER	(0x22)  /*设置密钥属主名称*/
#define DL_PROC_SET_DATETIME_SOFT	(0x24)  /*设置密钥属主名称*/
#define DL_PROC_SET_DATETIME_HARD	(0x25)  /*设置密钥属主名称*/

//////////////////////////////////////////////////////////////////////////

//语言选项
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
    unsigned char owner[32];            /*私钥所有方*/
    unsigned char ver[16];               /*私钥版本*/
    unsigned char info_reserved[16];
    unsigned int mod_bits;                    /*模长bit位数 */
    unsigned char modulus[MAX_RSA_MODULUS_LEN];      /*模 */
    unsigned int exp_bits;                    /*指数bit位数 */
    unsigned char exponent[MAX_RSA_MODULUS_LEN];      /* 指数 */
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

