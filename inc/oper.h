/**
* @file oper.h
* @brief 操作员处理模块
* @version  1.0
* @author 肖腾月
* @date 2007-02-5
*/

#ifndef _OPER_H_
#define _OPER_H_

#include "apiinc.h"
#include "libapiinc.h"
#include "posdef.h"
#include "debug.h"

#define MANAGEROPER      0				/**< 主管操作员标识*/
#define NORMALOPER         1				/**< 普通操作员标识*/
#define ADMINOPER		   2				/**< 系统管理员标识*/
#define KEK1MANAGEROPER		3				/**< KEK第一分量管理员标识*/
#define KEK2MANAGEROPER		4				/**< KEK第二分量管理员标识*/

#define OPERCODELEN		2				/**< 操作员编码所占用的长度*/

#define FILE_OPER		"OPER"

typedef struct
{
	char szOperNo[OPERCODELEN+1];
	char cOperRole;
	char cOperPwdLen;
	char szPasswd[12+1];
	char cDeleFlag;
} STOPER_RECORD;

/**
*以下为接口函数
*/
extern int operlog(int operlevel);
extern void InitOper(void);
extern int ResetOperPwd(int nRole);
extern int exist_other_value(char * psw, int pswlen);
#endif

