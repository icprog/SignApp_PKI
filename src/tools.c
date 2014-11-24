/**
*@file		tools.c
*@brief		提供基本工具的函数
*@version	1.0.0
*@author	yanm@newlandcomputer.com
*@date		2008-07-21
*@section 	history 	修改历史
	     		\<author\> \<time\> \<version\> \<desc\>
*/
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "NDK.h"
#include "ltool.h"
#include "lui.h"
#include "appinc.h"

/**
*@fn 		int EchoError(char *s)
*@brief 	显示错误
*@param	    s       显示字符串
*@return  	SUCC    成功
*@section	history 	修改历史
				\<author\>	\<time\>	\<desc\>
*/
int EchoError(char *s)
{
	NDK_ScrClrs();
	NDK_ScrSetAttr(TEXT_ATTRIBUTE_REVERSE, NULL);
	NDK_ScrPrintf(s);
	NDK_KbGetCode(20, NULL);
	return APP_FAIL;
}

/**
*@fn 		ShowTitle(const char *)
*@brief 	显示标题栏，自动居中对齐，标题栏字符大于16个字符时会自动截断
			并把光标移到第二行(16点行)
*@param	    szTitle 标题栏内容
*@return  	无
*@section	history 	修改历史
				\<author\>	\<time\>	\<desc\>
*/
void ShowTitle(const char *szTitle)
{
	char tmp[128];
	int i=0;
	uint fontw, fonth, view_w, view_h;
	EM_TEXT_ATTRIBUTE status;

	NDK_ScrClrs();
	NDK_ScrGetFontSize(&fontw,&fonth);
	fontw /= 2;
	NDK_ScrGetLcdSize(&view_w,&view_h);
	memset(tmp,0,sizeof(tmp));
	memset(tmp,0x20, ((view_w + fontw-1)/(fontw)-strlen(szTitle))/2);

	strcat(tmp, szTitle);
	if(((view_w+fontw-1)/fontw)>(view_w/fontw))
		i ++;

	if((((view_w+fontw-1)/(fontw)-strlen(szTitle))/2)!=(((view_w+fontw-1)/(fontw)-strlen(szTitle)+1)/2))
		i --;

	memset(tmp+((view_w+fontw-1)/(fontw)-strlen(szTitle))/2+strlen(szTitle),0x20,((view_w+fontw-1)/(fontw)-strlen(szTitle))/2-i);

	NDK_ScrSetAttr(TEXT_ATTRIBUTE_REVERSE,&status);
	NDK_ScrDispString(0, 0, tmp, 0);
	NDK_ScrSetAttr(status, NULL);
	NDK_ScrGotoxy(0, view_h);

	return;
}

int PubGetKeyCode(uiSecond)
{
	int code;
	int ret;

	ret=NDK_KbGetCode(uiSecond, &code);
	if (ret==NDK_OK){
		return code;
	}else{
		return ret;
	}
}

/******************************************************************************
*	函数名称：ProMsgDlg
*	函数介绍：	对话框(内部使用)
*	入口参数：	pszTitle--对话框标题
*					pszContent --对话框提示信息
*					nBeep --提示响铃次数
*					nTimeOut --输入超时时间
*					nMode --对话框类型GUI_DLG_CONFIRM(选择对话框)
*					GUI_DLG_DISPMSG (提示对话框)
*	出口参数：	无
*	返回值  ：	APP_SUCC--按确认退出
*					APP_QUIT--用户退出界面
*					APP_TIMEOUT--超时退出
*	修改者  ：周红弟
*	修改日期：2006-09-14
*******************************************************************************/
int ProMsgDlg(const char *pszTitle, const char *pszContent, int nBeep, int nTimeOut, int nMode)
{
	int	nPos = 1;
	int	nKey = 0;
	int nCode;
	uint fontw, fonth, view_w, view_h;

	NDK_ScrClrs();
	NDK_ScrGetFontSize(&fontw,&fonth);
	fontw /= 2;
	NDK_ScrGetLcdSize(&view_w,&view_h);
	
	if (pszTitle != NULL)
	{
		PubClearAll();
		if(strlen(pszTitle) == 0)
			nPos = 0;
		else
			nPos = 1;
		ShowTitle (pszTitle);
	}
	if (pszContent != NULL && strlen(pszContent) !=0)
	{
		PubClear2To4();
		NDK_ScrDispString(0, fonth*nPos, pszContent,0);
	}
	if (nMode == L_CHINESE)
	{
		NDK_ScrDispString(0, view_h - (fonth), "[取消]",0);
		NDK_ScrDispString(view_w - (fontw*6), view_h -  (fonth), "[确认]",0);
	}
	else
	{
		NDK_ScrDispString(0, view_h - (fonth), "[CANCLE]",0);
		NDK_ScrDispString(view_w - (fontw*8), view_h -  (fonth), "[ACCEPT]",0);	
	}
	NDK_ScrRefresh();
	/*响警告声*/
	PubBeep(nBeep);
	NDK_KbHit(&nCode);
	if( nTimeOut < 0 )
	{
		return APP_TIMEOUT;
	}

	for (; ;)
	{
		nKey = PubGetKeyCode(nTimeOut);
			switch (nKey)
			{
			case 0:
				return APP_TIMEOUT;
			case KEY_ENTER:
				return APP_SUCC;
			case KEY_ESC:
				return APP_QUIT;
			default:
				break;
			}
	}

	return APP_QUIT;
}

