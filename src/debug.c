/**
* @file debug.c
* @brief ����ģ��
* @version  1.0
* @author �Ž�
* @date 2007-01-22
*/
#include <string.h>
#include <stdarg.h>

#include "apiinc.h"
#include "libapiinc.h"
#include "posdef.h"
#include "debug.h"
/**
* ����ȫ�ֱ���
*/


int debug(const int nRes)
{
	return nRes;
}
#ifdef _DEBUG_
/**
* @fn Debug(void)
* @brief ���Թ���
* @param in
* @return ����
*/
int Debug(const int nRes, const char *pszFile, const int nLine)
{
	if (nRes != APP_SUCC) {
		pushscreen();
		PubClearAll();
		PubDisplayStr(0, 1, 1, "%s[%d]", pszFile, nLine);
		PubGetKeyCode(0);
		popscreen();
		return nRes;
	}
	return APP_SUCC;
}
#endif

/**
* @fn DebugBufToAux
* @brief ���ڵ��Թ���
* @param in
* @return ����
*/
//int DebugBufToAux(const char *pszBuf)
//{
//#if 0
//	char cDebugAux = AUX1;
//
//	initaux(cDebugAux, BPS9600, DB8 |STOP1 |NP);
//	clrportbuf(cDebugAux, 0);
//	return portwrite(cDebugAux, strlen(pszBuf), pszBuf);
//#else
//	fprintf(stderr, "%s", pszBuf);
//#endif
//	return 0;
//}
#ifdef _DEBUG_
/**
* @fn Trace
* @brief ������Ϣ��ʽ������
* @param in lpszFormat ��ʽ����
* @return	��
*/
//void Trace(char* lpszFormat, ...)
//{
//	va_list args;
//	int nBuf;
//	char buf[2048];
//
//	va_start(args, lpszFormat);
//	nBuf=vsprintf(buf, lpszFormat, args);
//	strcat(buf, "\n");
//	DebugBufToAux(buf);
//	ASSERT((nBuf>=0) && (nBuf<sizeof(buf)-2));
//	va_end(args);
//}

void DispTrace(char* lpszFormat, ...)
{
	va_list args;
	int nBuf;
	char buf[2048];

	va_start(args, lpszFormat);
	nBuf=vsprintf(buf, lpszFormat, args);
	pushscreen();
	PubClearAll();
	printf(buf);
	getkeycode(0);
	popscreen();
	ASSERT((nBuf>=0) && (nBuf<sizeof(buf)-2));
	va_end(args);
}
#else
void Trace(char* lpszFormat, ...) {}
#endif


