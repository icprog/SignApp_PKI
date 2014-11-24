/**
* @file oper.h
* @brief ����Ա����ģ��
* @version  1.0
* @author Ф����
* @date 2007-02-5
*/

#ifndef _OPER_H_
#define _OPER_H_

#include "apiinc.h"
#include "libapiinc.h"
#include "posdef.h"
#include "debug.h"

#define MANAGEROPER      0				/**< ���ܲ���Ա��ʶ*/
#define NORMALOPER         1				/**< ��ͨ����Ա��ʶ*/
#define ADMINOPER		   2				/**< ϵͳ����Ա��ʶ*/
#define KEK1MANAGEROPER		3				/**< KEK��һ��������Ա��ʶ*/
#define KEK2MANAGEROPER		4				/**< KEK�ڶ���������Ա��ʶ*/

#define OPERCODELEN		2				/**< ����Ա������ռ�õĳ���*/

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
*����Ϊ�ӿں���
*/
extern int operlog(int operlevel);
extern void InitOper(void);
extern int ResetOperPwd(int nRole);
extern int exist_other_value(char * psw, int pswlen);
#endif

