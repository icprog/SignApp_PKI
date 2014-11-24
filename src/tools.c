/**
*@file		tools.c
*@brief		�ṩ�������ߵĺ���
*@version	1.0.0
*@author	yanm@newlandcomputer.com
*@date		2008-07-21
*@section 	history 	�޸���ʷ
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
*@brief 	��ʾ����
*@param	    s       ��ʾ�ַ���
*@return  	SUCC    �ɹ�
*@section	history 	�޸���ʷ
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
*@brief 	��ʾ���������Զ����ж��룬�������ַ�����16���ַ�ʱ���Զ��ض�
			���ѹ���Ƶ��ڶ���(16����)
*@param	    szTitle ����������
*@return  	��
*@section	history 	�޸���ʷ
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
*	�������ƣ�ProMsgDlg
*	�������ܣ�	�Ի���(�ڲ�ʹ��)
*	��ڲ�����	pszTitle--�Ի������
*					pszContent --�Ի�����ʾ��Ϣ
*					nBeep --��ʾ�������
*					nTimeOut --���볬ʱʱ��
*					nMode --�Ի�������GUI_DLG_CONFIRM(ѡ��Ի���)
*					GUI_DLG_DISPMSG (��ʾ�Ի���)
*	���ڲ�����	��
*	����ֵ  ��	APP_SUCC--��ȷ���˳�
*					APP_QUIT--�û��˳�����
*					APP_TIMEOUT--��ʱ�˳�
*	�޸���  ���ܺ��
*	�޸����ڣ�2006-09-14
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
		NDK_ScrDispString(0, view_h - (fonth), "[ȡ��]",0);
		NDK_ScrDispString(view_w - (fontw*6), view_h -  (fonth), "[ȷ��]",0);
	}
	else
	{
		NDK_ScrDispString(0, view_h - (fonth), "[CANCLE]",0);
		NDK_ScrDispString(view_w - (fontw*8), view_h -  (fonth), "[ACCEPT]",0);	
	}
	NDK_ScrRefresh();
	/*�쾯����*/
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

