/**
* @file debug.c
* @brief 调试模块
* @version  1.0
* @author 张捷
* @date 2007-01-22
*/
#include <string.h>
#include <stdarg.h>

#include "apiinc.h"
#include "libapiinc.h"
#include "posdef.h"
#include "debug.h"
/**
* 定义全局变量
*/


int debug(const int nRes)
{
	return nRes;
}
#ifdef _DEBUG_
/**
* @fn Debug(void)
* @brief 调试工具
* @param in
* @return 返回
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
* @brief 串口调试工具
* @param in
* @return 返回
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
* @brief 调试信息格式化函数
* @param in lpszFormat 格式化串
* @return	无
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


