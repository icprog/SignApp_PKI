#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "libconfig.h"
#include "parsecfg.h"
#include "NDK.h"
#include "config.h"
#include "gui.h"
#include "compatible.h"

#define MAX_MENU_NAME	64

#define DEBUG
#ifdef DEBUG
#define PDEBUG(fmt, args...) fprintf(stderr, "sysapp_selftest: "fmt, ##args)
#else
#define PDEBUG(fmt, args...)
#endif


#define Language_CHINESE 0
#define FUNCKEY_CNT	4
#define FAIL (-1)
#define SUCC 0
#define FALSE 0
#define TRUE (!FALSE)
#define QUIT (-2)

#define  TK1	  0x01	//只读一磁道
#define  TK2    0x02		/*只读二道*/
#define  TK3    0x04		/*只读三道*/
#define  TK2_3    	(TK2 | TK3)   	/* 0x06  同时读二三道*/
#define  TK1_2_3	( TK1 | TK2 | TK3 )
#define  TK1_2		( TK1 | TK2 )
#define  TK1_3		( TK1 | TK3 )

#define		BPS300		0
#define		BPS1200		1
#define		BPS2400		2
#define		BPS4800		3
#define		BPS7200		4
#define		BPS9600		5
#define		BPS19200	6
#define		BPS38400	7
#define		BPS57600	8
#define		BPS115200	10
#define     BPS230400   11

#define K_UP				0x11
#define K_DOWN			0x12
#define K_LEFT				0x13
#define K_RIGHT			0x14


/*转换后的方向键*/
#define DFUNCKEY_UP		0XA0
#define DFUNCKEY_DOWN	0XA1
#define DFUNCKEY_LEFT	0XA2
#define DFUNCKEY_RIGHT	0xA3

#define PIC_H	10

#define ARR_SIZE( a ) 		( sizeof( (a) ) / sizeof( (a[0]) ) ) 



typedef enum {
    LANGUE_CHINESE,
    LANGUE_ENGLISH
} stLANGUE;
/**
 * 液晶显示尺寸
 */
typedef enum{
	LCDSIZE_128X64,
	LCDSIZE_128X160,
	LCDSIZE_240X320,
	LCDSIZE_MAX
}SCR_SIZE;

enum SYS_ERRORCODE {
    MAGCARD_TK1_LRC_ERR=0xC01,										// 一道LRC校验失败
    MAGCARD_TK2_LRC_ERR=0xC02,										// 二道LRC校验失败
    MAGCARD_TK3_LRC_ERR=0xC08,										// 三道LRC校验失败
    MAGCARD_TK12_LRC_ERR=MAGCARD_TK1_LRC_ERR|MAGCARD_TK2_LRC_ERR,	// 一、二道LRC校验失败
    MAGCARD_TK23_LRC_ERR=MAGCARD_TK2_LRC_ERR|MAGCARD_TK3_LRC_ERR,	// 二、三道LRC校验失败
    MAGCARD_TK13_LRC_ERR=MAGCARD_TK1_LRC_ERR|MAGCARD_TK3_LRC_ERR,	// 一、三道LRC校验失败
    MAGCARD_TK123_LRC_ERR=MAGCARD_TK1_LRC_ERR|MAGCARD_TK2_LRC_ERR|MAGCARD_TK3_LRC_ERR	// 一、二、三道LRC校验失败
};


typedef struct st_item_details{
	char name[2][MAX_MENU_NAME];
	int (*func)(char *);
}st_item_details;

typedef struct ST_Funtion_key{
	int keytype;
	int funckey[FUNCKEY_CNT];
}ST_Funtion_key;

extern int item_func(char * str);
extern void ShowTitle(const char *szTitle);
extern int DoExtTest(const char *pszPath, const char *pszFileName, const char *pszTitle);


extern char arrow_down[10];
extern char arrow_up[10];
extern char radio_chosed[10];
extern char radio[10];
extern char arrow_left[10];
extern char arrow_right[10];

extern uint gview_w,gview_h;
extern char *menuname;
extern uint gfonth,gfontw;
extern uint w_space,h_space;
extern char hardwareinfo[16],hardwaretype[16];
extern unsigned int glcd_size_flag;
extern int g_language;

