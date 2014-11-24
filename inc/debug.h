/**
* @file debug.h
* @brief
* @version  1.0
* @author
* @date 2007-01-22
*/
#ifndef _DEBUG_H_
#define _DEBUG_H_

/*
 * Debug Switch
 */
#define WPDEBUG
#undef WDEBUG
#ifdef WPDEBUG
#define WDEBUG(fmt, args...) fprintf(stderr,  "APP[%s][%d]: "fmt"\n",__FUNCTION__,__LINE__,##args)
#define WDEBUG_DATA(info, data, len) 		{int i;\
										fprintf(stderr,"APP[%s][%d]_%s: len=%d data=",__FUNCTION__,__LINE__, (info), (len));\
										for(i=0; i<(len); i++){\
										fprintf(stderr, "%02x ", *(data+i));\
										}\
										fprintf(stderr, "\n");\
										usleep(200*1000);\
										}
#define PRINT_LOG(fmt, args...) fprintf(stderr, "<in %s at line %d>:"fmt"\n", __FILE__, __LINE__, ##args);
#else
#define WDEBUG(fmt, args...)
#define WDEBUG_DATA(info, data, len)
#define PRINT_LOG(fmt, args...)
#endif

extern int debug(const int nRes);
extern int Debug(const int nRes, const char *pszFile, const int nLine);
extern int DebugBufToAux(const char *pszBuf);
extern void Trace(char* lpszFormat, ...);

//#define _DEBUG_

#ifdef _DEBUG_
#define ASSERT(e)  Debug(e, __FILE__, __LINE__)
#define TRACE(a) Trace##a
#define TRACE_DISP(a) DispTrace##a
#else
#define ASSERT(e)  debug(e)
#define TRACE(a) Trace##a
#define TRACE_DISP(a)
#endif

#define ASSERT_FAIL(e) \
	if (ASSERT(e) != APP_SUCC)\
	{\
		return APP_FAIL;\
	}

#define ASSERT_QUIT(e) \
	if (ASSERT(e) != APP_SUCC)\
	{\
		return APP_QUIT;\
	}

#define ASSERT_HANGUP_QUIT(e) \
	if (ASSERT(e) != APP_SUCC)\
	{\
		CommHangUp();\
		return APP_QUIT;\
	}

#define ASSERT_HANGUP_FAIL(e) \
	if (ASSERT(e) != APP_SUCC)\
	{\
		CommHangUp();\
		return APP_FAIL;\
	}

#endif

