#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NDK.h"
#include "Pri_DownloadTool.h"
#include "PriKeyDownload.h"
#include "Pri_DownloadApi.h"


//copy from comm.c
/*#include <stdlib.h>*/
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>

#include "apiinc.h"
#include "appinc.h"
#include "libapiinc.h"

/*#define MAXSENDLEN        200 [>帧中有效数据的长度，64 -> 200，暂定为200<]*/
/*#define MAXSENDLEN        2200 [>帧中有效数据的长度，64 -> 200，暂定为200<]*/

int Prompt(char *s, int nAttr, int nSeconds)
{
    int nKey;

    NDK_ScrClrs();
    NDK_ScrPrintf(s);
    NDK_KbGetCode(nSeconds,&nKey);
    return nKey; //等待在规定的时间里读按键
}

void NormalShow(char *szChinese, char *szEnglish, int nSeconds)
{
    if (g_Language == 0)
        Prompt(szChinese, TEXT_ATTRIBUTE_NORMAL, nSeconds);
    else
        Prompt(szEnglish, TEXT_ATTRIBUTE_NORMAL, nSeconds);
}

void DispMsg_exit(char *s)
{
    int nKey;

    NDK_ScrClrs();
    NDK_ScrPrintf(s);
    NDK_KbGetCode(0,&nKey);
    dl_portexit();
    exit(-1);
    //nlexit(-1);
}


/****************************************************************
** 函数功能：向下载串口发送一个字节数据
**
** 函数参数：
                    cCmd          发送的字节数据
** 返回值  ：
                    无
** 全局变量：
** 调用模块：
** 说    明：无
****************************************************************/
void WriteDownloadCommand(char cCmd)
{
    char szMsg[256];

    if (dl_portwrite(1, &cCmd) == FAIL) {
        if (cCmd != DL_CMD_ENQ) {
            if (g_Language !=0)
                sprintf(szMsg, "RS232: \nWrite %c Fail", cCmd);
            else
                sprintf(szMsg, "串口写%c失败", cCmd);
        } else {
            if (g_Language !=0)
                sprintf(szMsg, "RS232: \nFail to enquire\ndownload.");
            else
                strcpy(szMsg, "串口: \n发下载请求失败");            /* chenx, 101014 */
        }
        DispMsg_exit(szMsg); //显示信息后直接硬件复位
    }
}


/****************************************************************
** 函数功能：接收一个结构(frame)
**
** 函数参数：
                   len         接收的数据长度
                   buf         接收数据的缓冲区
                   time        超时时间
** 返回值  ：
                   SUCC        接收成功
                   FAIL        接收失败
** 全局变量：
** 调用模块：
** 说    明：每个frame 中有4个字节是额外信息:
                 'O'  'K'  ...  EXT  C
****************************************************************/
int RecOneFrame(int len, char *buf, int time)
{
    unsigned char sum;
    int i;
	/*int j;*/

    if (len < 4) {
        return FAIL;
    }
    // 1.在设定超时时间里，从串口AUX1 读取len 个字节数据到buf中
    //if((i = portread(DOWNLOAD_PORT, len, buf, time)) != len)
    if ((i = dl_portread(len, buf, time)) != len) { // 'O'K'+data+ETX(1byte)+CheckSum(1byte)
        //NDK_ScrPush();
        //ASSERT_CRLRS();
        //NormalShow("接收数据帧失败!","Failed in receiving data!",2);
        //NDK_ScrPop();
        return FAIL;
    }
    //for(j=0; j<len; j++)
        //PDEBUG("%02x-",buf[j]);
    //辅口接受数据成功
    // 2.检验接收到的数据是否合法

    //前两个字节为'O' 和'K'
    if ((buf[0] != 'O')||(buf[1] != 'K')) {
        //NormalShow("通讯中错误!\n没收到'OK'错\n","Error occured in\ncommunication\n",2);
        return FAIL;
    }

    //倒数第二个字节为EXT
    if (buf[len-2] != ETX) {
        //MessagePrint("通讯中错误\n没收到ETX错\n","Error occured in\ncommunication\nCannot receive\n\"ETX\"");
        return FAIL;
    }

    //最后一个字节为校验码
    sum = 0;
    for (i=2; i<len-2; i++) {
        sum += (unsigned char)buf[i];
    }

    PDEBUG("\n%s,%d,sum=%x--buflen=%x\n",__FUNCTION__,__LINE__,sum, (unsigned char)buf[len-1]);
    if (sum != (unsigned char)buf[len-1]) {
        //MessagePrint("通讯中错误\n检验错\n","Error occured in\ncommunication\nVerification\nfailed.");
        return FAIL;
    }
    return SUCC;
}

/****************************************************************
** 函数功能：接收一个帧，如失败则重复接收3次
**
** 函数参数：
                   len              接收的数据长度
                   buf              接收数据的缓冲区
                   time             超时时间
** 返回值  ：
                   SUCC             接收成功
                   FAIL             接收失败
** 全局变量：无
** 调用模块：
** 说    明：1. pos接收不成功则请求pc重发该帧
             2. 每个frame 中有4个字节是额外信息:
                    'O'  'K'  ...  EXT  C
****************************************************************/
int RecOneFrameWithRepeat(int len, char *buf, int time)
{
    int i;
    if (RecOneFrame(len, buf, time) == SUCC) { //接收一个帧
        WriteDownloadCommand(DL_CMD_RECEIVE_OK);//接收成功应答命令'Z'
        return SUCC;
    }
    for (i=0; i<3; i++) {
        WriteDownloadCommand(DL_CMD_RESEND);//发送下载帧重发命令'C'
        if (RecOneFrame(len, buf, time) == SUCC) {
            WriteDownloadCommand(DL_CMD_RECEIVE_OK);//接收成功应答命令'Z'
            return SUCC;
        }
    }
    return FAIL;
}


/****************************************************************
** 函数功能：对数据打包、加入协议字符
**
** 函数参数：
                  pbuf          帧指针
                  len           有效数据的长度
** 返回值  ：
                  数据打包后的长度
** 全局变量：无
** 调用模块：无
** 说    明：无
****************************************************************/
int insertprotocol(unsigned char *pbuf, unsigned long len)
{
    unsigned char tmpbuff[MAXSENDLEN+4];
    unsigned char checksum = 0;
    unsigned int i;
    memset(tmpbuff, 0, sizeof(tmpbuff));// 'O'+'K'+data+ETX(1byte)+CheckSum(1byte)
    tmpbuff[0] = 'O';
    tmpbuff[1] = 'K';
    memcpy(tmpbuff+2, pbuf, len);
    tmpbuff[2+len] = ETX;
    for (i=0; i<len; i++) {
        checksum += (unsigned char )pbuf[i];
    }
    tmpbuff[2+len+1] = checksum;
    memcpy(pbuf, tmpbuff, 2+len+1+1);

    return 2+len+1+1;
}


/****************************************************************
** 函数功能：发送一个数据帧
**
** 函数参数：
                   sendbuf      帧指针
                   len          帧中有效数据的长度
** 返回值  ：
                   SUCC         成功
                   FAIL         失败
** 全局变量：
** 调用模块：
** 说    明：1. 有效数据不能大于MAXSENDLEN，
             2. 重发次数为3次。
****************************************************************/
int SendFrameWithRepeat(char *sendbuf, int len)
{
    unsigned char buf[MAXSENDLEN+4];
    unsigned char recvbuf[4];
    int irepeat_w = 0;
    int irepeat_r = 0;
    int frame_len;

    if (len > MAXSENDLEN) {
        return FAIL;
    }

    memcpy(buf, sendbuf, len);
    frame_len = insertprotocol(buf, len);

    while (irepeat_w < 3) { //重发最大次数为3次
        if (dl_portwrite(frame_len, (char*)buf) == FAIL) {
            if (g_Language !=0)
                DispMsg_exit("RS232: \nWrite Frame Fail");
            else
                DispMsg_exit("串口写帧失败");
        }
        while (irepeat_r < 3) {
            if (dl_portread(1, (char*)recvbuf, 1000) < 1) {
                irepeat_r++;
                if (irepeat_r > 2) {
                    //gV2AppErrorCode = ERR_DOWN_COMM;
                    //通讯故障，可能是下载线链接问题
                    return FAIL;
                }
            } else if (recvbuf[0] == DL_CMD_RECEIVE_OK) {
                return SUCC;
            } else if (recvbuf[0] == DL_CMD_RESEND) {
                irepeat_w++;
                break;
            } else {
                return FAIL;
            }
        }
    }
    return FAIL;
}


static int gDownlaodPort = PORT_AUX;    //默认下载使用物理串口
static int gUsbOpenFlag = 0;        //USB串口句柄，以打开则为1,未打开则为0
static int s_nAuxPort=PORT_NUM_COM2;//PORT_NUM_USB;//

/****************************************************************
** 函数功能：设置下载端口: 串口/ USB
**
** 函数参数：porttype:下载端口类型PORT_AUX/PORT_USB
** 返回值  ：SUCC/FIAL
** 全局变量：无
** 调用模块：无
** 说    明：每次USB串口下载完毕，要调用SetDownloadPortType(PORT_AUX)关闭USB
****************************************************************/
int SetDownloadPortType(int porttype)
{
    switch (porttype) {
		case PORT_NUM_COM1:
        case PORT_NUM_COM2:
            gDownlaodPort = porttype;
            break;
        case PORT_USB:
            gDownlaodPort = porttype;
            if (!gUsbOpenFlag) {
                if (SUCC == NDK_PortOpen(PORT_NUM_USB,"115200,8,N,1"))
                    gUsbOpenFlag =1;
                else
                    return FAIL;
            }
            break;
        default:
            return FAIL;
    }
    return SUCC;
}

/****************************************************************
** 函数功能：返回下载端口: 串口/ USB
**
** 函数参数：
** 返回值  ：   当前下载所使用的方式:
                  串口-- PORT_AUX
                  USB   --  PORT_USB
** 全局变量：无
** 调用模块：无
** 说    明：无
****************************************************************/
int GetDownloadPortType(void)
{
    return gDownlaodPort;
}

/****************************************************************
** 函数功能：初始化下载端口: 串口/ USB
**
** 函数参数：port--串口号,bps--波特率,flags--参数
** 返回值  ：SUCC/FAIL
** 全局变量：无
** 调用模块：无
** 说    明：无
****************************************************************/
int dl_initdownloadport(void)
{
	return 0;

    int iRet;
    switch (gDownlaodPort) {
        case PORT_AUX:
            /*iRet = NDK_PortOpen(PORT_NUM_COM1,"115200,8,N,1");*/
            iRet = NDK_PortOpen(PORT_NUM_COM2,"115200,8,N,1");
            return iRet;
            break;
        case PORT_USB:
            if (gUsbOpenFlag)
                return SUCC;
            iRet = NDK_PortOpen(PORT_NUM_USB,"115200,8,N,1");
            if (SUCC == iRet) {
                gUsbOpenFlag = 1;
                return SUCC;
            } else {
                gUsbOpenFlag = 0;
                return FAIL;
            }
            break;
        default:
            break;
    }
    return FAIL;
}

/****************************************************************
** 函数功能：读取下载端口数据
**
** 函数参数：len --数据长度,OutBuf--输出缓冲区,seconds--超时时间
** 返回值  ：SUCC/FAIL
** 全局变量：无
** 调用模块：无
** 说    明：无
****************************************************************/
int dl_portread(int len,char *OutBuf,int seconds)
{
    int nLen = 0;
    int iret;
    switch (gDownlaodPort) {
		case PORT_NUM_COM1:
            NDK_PortRead(PORT_NUM_COM1,len,OutBuf,seconds,&nLen);
            return nLen;
            break;
       case PORT_NUM_COM2:
            NDK_PortRead(PORT_NUM_COM2,len,OutBuf,seconds,&nLen);
			WDEBUG_DATA("recv",OutBuf,nLen);
            return nLen;
            break;
        case PORT_USB:
            if (!gUsbOpenFlag) {
                if (SUCC == NDK_PortOpen(PORT_NUM_USB,"115200,8,N,1")) {
                    gUsbOpenFlag = 1;
                } else
                    return FAIL;
            }
            iret = NDK_PortRead(PORT_NUM_USB,len,OutBuf,seconds,&nLen);
            return nLen;
            break;
        default:
            break;
    }
    return FAIL;
}

/****************************************************************
** 函数功能：写下载端口数据
**
** 函数参数：len --数据长度,InBuf--下发数据指针
** 返回值  ：SUCC/FAIL
** 全局变量：无
** 调用模块：无
** 说    明：无
****************************************************************/
int dl_portwrite(int len,const char *InBuf)
{
	/*dl_clrportbuf(1);*/
    switch (gDownlaodPort) {
        case PORT_NUM_COM1:
			WDEBUG_DATA("send",InBuf,len);
            return NDK_PortWrite(PORT_NUM_COM1,len,InBuf);
            break;
		case PORT_NUM_COM2:
			WDEBUG_DATA("send",InBuf,len);
            return NDK_PortWrite(PORT_NUM_COM2,len,InBuf);
            break;
        case PORT_USB:
            if (!gUsbOpenFlag) {
                if (SUCC == NDK_PortOpen(PORT_NUM_USB,"115200,8,N,1")) {
                    gUsbOpenFlag = 1;
                } else
                    return FAIL;
            }
            return NDK_PortWrite(PORT_NUM_USB,len,InBuf);
            break;
        default:
            break;
    }
    return FAIL;
}

/****************************************************************
** 函数功能：清空端口缓冲区
**
** 函数参数：rxtx --0 - 清除发送缓冲区    1-清除接收缓冲区
** 返回值  ：SUCC/FAIL
** 全局变量：无
** 调用模块：无
** 说    明：无
****************************************************************/
int dl_clrportbuf(int rxtx)
{
    switch (gDownlaodPort) {
		case PORT_NUM_COM1:
            return NDK_PortClrBuf(PORT_NUM_COM1);
            break;
		case PORT_NUM_COM2:
            return NDK_PortClrBuf(PORT_NUM_COM2);
            break;
        case PORT_USB:
            if (!gUsbOpenFlag) {
                if (SUCC == NDK_PortOpen(PORT_NUM_USB,"115200,8,N,1")) {
                    gUsbOpenFlag = 1;
                } else {
                    return FAIL;
                }
            }
            if (rxtx != 1)      /*USB串口只支持清空接收缓冲区*/
                return SUCC;
            NDK_PortClrBuf(PORT_NUM_USB);
            break;
        default:
            break;
    }
    return SUCC;
}

/****************************************************************
** 函数功能：退出下载前，关闭下载端口(USB)
**
** 函数参数：无
** 返回值  ：无
** 说    明：无
****************************************************************/
void dl_portexit(void)
{
    switch (gDownlaodPort) {
        case PORT_AUX:
            break;
        case PORT_USB:
            if (gUsbOpenFlag) {
                NDK_PortClose(PORT_NUM_USB);
                gUsbOpenFlag = 0;
            }
            break;
        default:
            break;
    }
    return;
}


/****************************************************************
** 函数功能：界面提示用户，选择下载方式：串口或USB
**
** 函数参数：nseconds-- >0  等待的超时时间，单位秒，
                        0   阻塞等待，直到用户按键
                        <0  不等待，不显示界面提示，直接返回下载类型；
** 返回值  ： 下载的端口定义
    #define PORT_NONE   (-1)    无效下载端口（按键ESC退出）
    #define PORT_AUX    0       RS232串口
    #define PORT_USB    (PORT_AUX+1)    USB串口
    #define USB_DISK    (PORT_USB+1)    U盘下载的方式
** 说    明：
    从下载配置文件"donwnload.cfg"读取默认下载端口，若配置文件不存在，则创建默认配置“串口下载”
    配置文件格式为DOWNLOAD_PORT=XXX，"XXX"即上述返回值中的3中下载类型宏名称，例如串口下载（区分大小写）：
    DOWNLOAD_PORT=PORT_AUX
****************************************************************/
#define DOWNLOAD_CFG_FILE   "download.cfg"
#ifdef  fopen
#undef  fopen       //必须使用linux系统函数fopen，而不是pos_fopen
#endif
#ifdef  fclose
#undef  fclose
#endif

int SelectDownloadPort(int nSeconds)    //modify by zhengyn 20110505
{
	int nRet;
	nRet = CommInitConfig();
	gDownlaodPort = s_nAuxPort;
	return nRet;

    FILE *cfgfd;
    int status;
    char buf[32];
    int ret;
    uint nWidth,nHeigth;
    status = NDK_FsExist (DOWNLOAD_CFG_FILE);
    if (status != 0) {
        ret = PORT_AUX;     /*若配置文件不存在，则创建默认下载类型为串口*/
        cfgfd = fopen(DOWNLOAD_CFG_FILE, "w");
        if (cfgfd != 0) {
            fputs("DOWNLOAD_PORT=PORT_AUX",(FILE*)cfgfd);
        }
        fclose(cfgfd);
    } else {
        cfgfd = fopen(DOWNLOAD_CFG_FILE, "r");
        memset(buf, 0, sizeof(buf));
        status = fscanf((FILE*)cfgfd,"DOWNLOAD_PORT=%s",buf);
        if (status != -1) {
            if (strstr(buf,"PORT_USB"))
                ret = PORT_USB;
            else
                ret = PORT_AUX;
        } else
            ret = PORT_NONE;
        fclose(cfgfd);
    }
    if (nSeconds < 0)
        return ret;

    NDK_ScrGetFontSize(&nWidth,&nHeigth);
    while (1) {
        NDK_ScrClrs();
        if (g_Language !=0) {
            NDK_ScrPrintf("  Select port  \n");
            NDK_ScrPrintf(" 1.UART\n");
            NDK_ScrPrintf(" 2.USB-Serial\n");
        } else {
            NDK_ScrPrintf("__选择通讯方式__\n");
            NDK_ScrPrintf(" 1.RS232串口\n");
            NDK_ScrPrintf(" 2.USB串口\n");
        }
        switch (ret) {
            case PORT_AUX:
                NDK_ScrSetAttr(TEXT_ATTRIBUTE_REVERSE,NULL);
                NDK_ScrGotoxy(0,1*nHeigth);
                if (g_Language !=0) {
                    NDK_ScrPrintf(" 1.UART\n");
                } else {
                    NDK_ScrPrintf(" 1.RS232串口\n");
                }
                NDK_ScrSetAttr(TEXT_ATTRIBUTE_NORMAL,NULL);
                break;
            case PORT_USB:
                NDK_ScrSetAttr(TEXT_ATTRIBUTE_REVERSE,NULL);
                NDK_ScrGotoxy(0,2*nHeigth);
                if (g_Language !=0) {
                    NDK_ScrPrintf(" 2.USB-Serial\n");
                } else {
                    NDK_ScrPrintf(" 2.USB串口\n");
                }
                NDK_ScrSetAttr(TEXT_ATTRIBUTE_NORMAL,NULL);
                break;
        }
        NDK_KbGetCode(nSeconds,&status);
        switch (status) {
            case '1':
                if (ret != PORT_AUX) {
                    ret = PORT_AUX;
                    cfgfd = fopen(DOWNLOAD_CFG_FILE, "w");
                    if (cfgfd != 0)
                        fputs("DOWNLOAD_PORT=PORT_AUX",(FILE*)cfgfd);
                    fclose(cfgfd);
                }
                return ret;
            case '2':
                if (ret != PORT_USB) {
                    ret = PORT_USB;
                    cfgfd = fopen(DOWNLOAD_CFG_FILE, "w");
                    if (cfgfd != 0)
                        fputs("DOWNLOAD_PORT=PORT_USB",(FILE*)cfgfd);
                    fclose(cfgfd);
                }
                MessagePrint("\n启动USB串口\n请稍候 ...\n","\nload USB serial\nplease wait ...\n",1);
                return ret;
            case UP:
                if(ret!=0) {
                    ret = ret -1;
                } else {
                    ret = 2;
                }
                break;
            case DOWN:
                if(ret!=2) {
                    ret = ret +1;
                } else {
                    ret = 0;
                }
                break;
            case ENTER:
                if(ret == PORT_USB) {
                    MessagePrint("\n启动USB串口\n请稍候 ...\n","\nload USB serial\nplease wait ...\n",1);
                }
                return ret;
            case ESC:
                ret = PORT_NONE;
                return ret;
            default:
                break;
        }
    }
    return ret;
}

/**
*@fn        int CommInitConfig(void)
*@brief     初始化下载端口
*@param     @li 无
*@section   history     修改历史
            \<author\>  \<time\>    \<desc\>
*/
int CommInitConfig(void)
{
    int keycode;
	int iret;
    EM_TEXT_ATTRIBUTE status;
    char *com_menu_en[] = {
        "Select Com Port\n",
        "1.COM1\n",
        "2.COM2\n",
        "3.USB\n",
        NULL
    };
    char *com_menu_ch[] = {
        "下载端口选择\n",
        "1.串口一\n",
        "2.串口二\n",
        "3.USB\n",
        NULL
    };
    char **pmenu;
    int g_language = 0;

    /*char hwinfo[64];*/
    /*unsigned int len;*/

/*
    if (NDK_SysGetPosInfo(SYS_HWINFO_GET_HARDWARE_INFO, &len, hwinfo)==NDK_OK){
        if (hwinfo[5]==1){//硬件配置只有一个串口，直接打开串口一，不选择
            s_nAuxPort = PORT_NUM_COM1;
            if (NDK_PortOpen(s_nAuxPort, "115200,8,N,1") < 0) {
                return EchoError("Open comm port failed!");
            }
            return 0;
        }
    }
*/
    NDK_SysGetConfigInfo(SYS_CONFIG_LANGUAGE, &g_language);
    if (g_language) {
        pmenu = com_menu_en;
    } else {
        pmenu = com_menu_ch;
    }
    NDK_ScrClrs();
    NDK_ScrPrintf(pmenu[0]);
    switch (s_nAuxPort) {
    case PORT_NUM_COM1:
        NDK_ScrSetAttr(TEXT_ATTRIBUTE_REVERSE,&status);
        NDK_ScrPrintf(pmenu[1]);
        NDK_ScrSetAttr(status,NULL);
        NDK_ScrPrintf(pmenu[2]);
        NDK_ScrPrintf(pmenu[3]);
        break;
    case PORT_NUM_COM2:
        NDK_ScrPrintf(pmenu[1]);
        NDK_ScrSetAttr(TEXT_ATTRIBUTE_REVERSE,&status);
        NDK_ScrPrintf(pmenu[2]);
        NDK_ScrSetAttr(status,NULL);
        NDK_ScrPrintf(pmenu[3]);
        break;
    case PORT_NUM_USB:
        NDK_ScrPrintf(pmenu[1]);
        NDK_ScrPrintf(pmenu[2]);
        NDK_ScrSetAttr(TEXT_ATTRIBUTE_REVERSE,&status);
        NDK_ScrPrintf(pmenu[3]);
        NDK_ScrSetAttr(status,NULL);
        break;
    }
    NDK_KbGetCode(0, &keycode);
    switch (keycode) {
    case K_ONE:
        s_nAuxPort = PORT_NUM_COM1;
        break;
    case K_TWO:
        s_nAuxPort = PORT_NUM_COM2;
        break;
    case K_THREE:
        s_nAuxPort = PORT_NUM_USB;
        break;
    case K_ESC:
    	exit(0);
        return -1;
    case K_ENTER:
    	break;
//    default:
//        s_nAuxPort =  PORT_NUM_USB;
//        break;
    }
	gDownlaodPort = s_nAuxPort;
	iret = NDK_PortOpen(s_nAuxPort, "115200,8,N,1");

	if(s_nAuxPort == PORT_NUM_USB){
		if (SUCC == iret) {
			gUsbOpenFlag = 1;
			return SUCC;
		} else {
			gUsbOpenFlag = 0;
			return EchoError("Open USB port failed!");
		}
	}

    if ( iret < 0) {
        return EchoError("Open comm port failed!");
	}

    return 0;
}

#if 0
/**
*@fn 		void SendOneFrame(char cCmd)
*@brief 	发送一字节的请求或响应命令
*@param	    @li cCmd        命令字串
*@return  	无
*@section	history 	修改历史
				\<author\>	\<time\>	\<desc\>
*/
void SendOneFrame(char cCmd)
{
	char szMsg[256];

	if (NDK_PortWrite(s_nAuxPort, 1, (char *)&cCmd) != NDK_OK) {
#if LANGUAGE==L_CHINESE
		sprintf(szMsg,"串口发送%c失败",cCmd);
#else
		sprintf(szMsg,"Fail in sending %c!",cCmd);
#endif
		EchoError(szMsg);
	}
}
#endif

/**
*@brief 	与POS的握手协议，等待接收ENQ，并发送指定的命令操作。
*@param		@li opcode	检测到握手信号后，发送的操作码，用于通知POS后续的操作功能。
*@return  	0 -- 成功
			<0 -- 失败
*/
int comm_handshake_cmd(char opcode)
{
    int enqcount = 0;
    int wrongcount = 0;
    char buf[16];
    int downloadstatus;
	int len = 0;

    downloadstatus = NONEENQ;
    /*预留500ms，确保下端KLA有足够时间完成上一条指令!!!例如set_kla_datetime(0);紧接着调用enter_x509_auth()*/
    NDK_SysMsDelay(500);
    NDK_PortClrBuf(s_nAuxPort);
    
	//WDEBUG("run");
    //fprintf(stderr, "handshaking cmd %02x...\n",opcode);
    memset(buf, 0, sizeof(buf));
    while (1) {
        switch (downloadstatus) {
        case NONEENQ:
			WDEBUG("run");
           /*等待ENQ请求*/
            if (NDK_PortRead(s_nAuxPort, 1, buf, 1000, &len) !=NDK_OK||len<1) {
				WDEBUG("s_nAuxPort : %d", s_nAuxPort);
                EchoError("Failed: no respose");
                return APP_FAIL;
            }
            if (buf[0]==ENQ) {
                enqcount++;
            } else {
                wrongcount++;
                
                if (wrongcount > 5) {
                    if (PubGetKeyCode(1)==KEY_ESC) {
                        return APP_FAIL;
                    }
                    break;
                }
            }
            if (enqcount > 2) { /*连续收到3个ENQ才可进入下一步*/
                /*for (enqcount=0; enqcount<5; enqcount++) {*/
					WDEBUG("run");
                    //SendOneFrame(NEW_ENQ);
					WriteDownloadCommand(NEW_ENQ);
                /*}*/
                downloadstatus=_NEWENQRET;	/*等待*/
                enqcount = 0;
                wrongcount = 0;
            }
            break;

        case _NEWENQRET:	/*等待刷新操作NEW_ENQ(0x07)握手的响应 0x017*/
			WDEBUG("run");
            if (NDK_PortRead(s_nAuxPort, 1, buf, 1*1000, &len) !=NDK_OK||len<1) {
				WDEBUG("run");
                wrongcount++;
                break;
            }
            if (buf[0]==NEW_ENQ_ACK) {
				if(opcode != 0)
					//SendOneFrame(opcode);
					WriteDownloadCommand(opcode);
                return APP_SUCC;
            } else {
                if (wrongcount++ > 3) {
                    EchoError("Response Timeout");
                    return APP_FAIL;
                }
            }
            break;

        default:
            break;
        }
    }

    return APP_SUCC;
}
/*@fn 		int WritePortWithRepeat(int aux,int len,char *pbuf)
*@brief 	写丝谑莶⒌却Υ�
*@param	    @li aux        端口
            @li pbuf         发送缓冲区
            @li len         长度
*@return  	无
*@section	history 	修改历史
				\<author\>	\<time\>	\<desc\>
*/
int WritePortWithRepeat(int aux,int len,char *pbuf)
{
    char buf[20];
    int readlen = 0;
	int count = 0;

    do {
		WDEBUG("send cnt: %d", count++);
        NDK_PortClrBuf(aux);
        if (NDK_PortWrite(aux,len,pbuf) != NDK_OK) {
#if LANGUAGE==L_CHINESE
            return EchoError("写串口失败!");
#else
            return EchoError("Fail in portwriting!");
#endif
        }

       if (NDK_PortRead(aux, 1, buf, 5*1000, &readlen) != NDK_OK) {
#if LANGUAGE==L_CHINESE
            return EchoError("读串口失败!");
#else
            return EchoError("Fail in portreading!");
#endif
        }
    } while (buf[0] == 'C');

    return APP_SUCC;
}

/**
*@fn 		unsigned char GetCheckSum(char *pbuf,int len)
*@brief 	获取校验和
*@param	    @li pbuf        数据缓冲
            @li len         长度
*@return  	无
*@section	history 	修改历史
				\<author\>	\<time\>	\<desc\>
*/
unsigned char GetCheckSum(char *pbuf,int len)
{
    unsigned char sum = 0;
    int i = 0;
    for (; i < len; i ++)
        sum += (unsigned char)pbuf[i];
    return sum;
}
/**
*@brief 	实现接收POS证书的流程
*@param		pFilename证书名称
*@return  	0 -- 成功
			<0 -- 失败
*/
int RecieveCertFile(char *pFilename)
{
    int hnd;
    int len, i, j, rlen, lastframe;
    char buf[4096];
    union {
        char c[4];
        int i;
    } tmp;
    int nBytesRead, nBytesWrite;
    char *bp = NULL;

    // 1.....接收文件名长度..................................
    NDK_ScrClrs();
#if LANGUAGE==L_CHINESE
    NDK_ScrPrintf("等待证书名长度\n");
#else
    NDK_ScrPrintf("requesting file nlen...\n");
#endif
    if (RecOneFrameWithRepeat(6, buf, 1) == APP_FAIL) {
#if LANGUAGE==L_CHINESE
        EchoError("接收证书文件名长度失败");
#else
        EchoError("Fail recv file nlen");
#endif
        return APP_FAIL;
    }
    tmp.c[0] = buf[2];
    tmp.c[1] = buf[3];
    tmp.c[2] = 0;
    tmp.c[3] = 0;
    if ((tmp.i <= 0) || (tmp.i > 255)) {
#if LANGUAGE==L_CHINESE
        EchoError("证书文件名太长");
#else
        EchoError("Invaild nlen");
#endif
        return APP_FAIL;
    }
	WDEBUG("recv file name len: %d", tmp.i);
    // 2.....接收文件名..................................
    NDK_ScrClrs();
#if LANGUAGE==L_CHINESE
    NDK_ScrPrintf("接收文件名...\n");
#else
    NDK_ScrPrintf("Recv file name\n");
#endif
    //buf[0]='F';
    //SendOneFrame(DL_CMD_FILENAME);
	WriteDownloadCommand(DL_CMD_FILENAME);

    if (RecOneFrameWithRepeat(tmp.i+4, buf, 10) == APP_FAIL) {
#if LANGUAGE==L_CHINESE
        EchoError("接收文件名失败");
#else
        EchoError("Recv name fail");
#endif
        return APP_FAIL;
    }
    for (i=0; i<tmp.i; i++)
        pFilename[i] = buf[2+i];
    pFilename[i] = 0;
	WDEBUG("recv file name: %s",pFilename);
    // 3......接受文件长度.................................
    NDK_ScrClrs();
#if LANGUAGE==L_CHINESE
    NDK_ScrPrintf("接收数据长度...\n");
#else
    NDK_ScrPrintf("Recv file len\n");
#endif
    //buf[0]='R';
    //SendOneFrame(DL_CMD_FILELEN);
	WDEBUG("run");
	WriteDownloadCommand(DL_CMD_FILELEN);

    if (RecOneFrameWithRepeat(7, buf, 1) == APP_FAIL) {
#if LANGUAGE==L_CHINESE
        EchoError("接收数据长度失败");
#else
        EchoError("Recv flen failed");
#endif
        return APP_FAIL;
    }
    tmp.c[0] = buf[2];
    tmp.c[1] = buf[3];
    tmp.c[2] = buf[4];
    tmp.c[3] = 0;
    len = tmp.i;	/*要下载的文件长度*/
	WDEBUG("file len: %d", len);
    // 4......打开文件.................................
    if ((hnd=open(pFilename, O_RDWR|O_CREAT|O_TRUNC,0666)) == -1) { /*覆盖原文件*/
#if LANGUAGE==L_CHINESE
        EchoError("创建证书文件失败");
#else
        EchoError("store file failed");
#endif
        return APP_FAIL;
    }
    // 5......接受数据...................................
    NDK_ScrClrs();
#if LANGUAGE==L_CHINESE
    NDK_ScrPrintf("文件大小:%d\n", len);
    NDK_ScrPrintf("\n下载中...");
#else
    NDK_ScrPrintf("File length:\n%d\n", len);
    NDK_ScrPrintf("\nReceiving...");
#endif
    //接受数据并写到文件
    for (j=0; ; j++) {
        //buf[0]='S';
        //if(portwrite(DOWNLOAD_PORT, 1, "S") == APP_FAIL) {
        //SendOneFrame('S');
		WriteDownloadCommand('S');
        if (len > FL) {
            rlen = FL;
            len -= FL;
            lastframe = FALSE;
        } else {
            rlen = len;
            lastframe = TRUE;
        }
		WDEBUG("***rlen+4 :%d***", rlen);

        //接收数据
        if (RecOneFrameWithRepeat(rlen+4, buf, 20) == APP_FAIL) {
            close(hnd);
            remove(pFilename);
            EchoError("Receive data \nfailed.");
            return APP_FAIL;
        }
        //写数据到文件
#if 1 /*lipm add, 20081023 */
        nBytesRead = rlen;
        bp = &buf[2];
        while (nBytesRead > 0) {
            while (((nBytesWrite=write(hnd,bp,nBytesRead))==-1)&&(errno == EINTR))
                ;
            if (nBytesWrite < 0) {
#if LANGUAGE==L_CHINESE
                EchoError("写文件失败");
#else
                EchoError("Write file failed");
#endif
                close(hnd);  
                remove(pFilename);
                return APP_FAIL;
            }
            if (nBytesWrite == 0)
                break;
            nBytesRead -= nBytesWrite;
            bp += nBytesWrite;
        }
        if (nBytesRead != 0) {
            close(hnd);
            remove(pFilename);
            return APP_FAIL;
        }
#endif
        if (lastframe == TRUE)
            break;
    }

    close(hnd);
    return APP_SUCC;
}
/**
*@brief 	发送KeyloaderServer自身的证书给POS进行验证
*@param		无
*@return  	0 -- 成功
			<0 -- 失败
*/
int SendCertFile(char *fpath, char *fname)
{
    int fd;
    struct stat finfo;
    int len = 0;
    char buf[4096] = {0};
    int filelen;
    int lastframe = 0;
    int readlen;

    NDK_ScrClrs();
    NDK_ScrPrintf("sending file\n");
    if (stat(fpath, &finfo) < 0) {
        EchoError("Open file failed");
        return -1;
    }

    //SendOneFrame(DL_CMD_SENDCERT);
	WriteDownloadCommand(DL_CMD_SENDCERT);
    NDK_PortRead(s_nAuxPort, 1, buf, 5*1000, &readlen);
    if (buf[0]!='L') {
		WDEBUG("comm port: %d", s_nAuxPort);
		WDEBUG("error recv:%02x", buf[0]);
		WDEBUG_DATA("recv", buf, readlen);
        EchoError("Send file failed");
        return -1;
    }

    //1.发送文件名长度
    len = strlen(fname);
	WDEBUG("file name len: %d", len);
    buf[0] = 'O';
    buf[1] = 'K';
    buf[2] = len&0xFF;
    buf[3] = (len>>8)&0xFF;
    buf[4] = ETX;
    buf[5] = GetCheckSum(buf+2,2);
  
    if (WritePortWithRepeat(s_nAuxPort,6,buf)==APP_FAIL) {
        EchoError("Send file name len fail");
        return -1;
    }

    //2.发送文件名
    do {
        if (NDK_PortRead(s_nAuxPort, 1, buf, 1000, &readlen)!=NDK_OK) {
            EchoError("Fail in sending file!");
            return -1;
        }
    } while (buf[0]!='F');

    buf[0] = 'O';
    buf[1] = 'K';
    memcpy(buf+2, fname, len);
    buf[len+2] = ETX;
    buf[len+3] = GetCheckSum(buf+2,len);
    if (WritePortWithRepeat(s_nAuxPort,(len+4),buf)==APP_FAIL) {
        EchoError("Fail in sending name!");
        return -1;
    }

    //3.发送文件长度
    do {
        if (NDK_PortRead(s_nAuxPort, 1, buf, 1000, &readlen)!=NDK_OK) {
            EchoError("Fail in sending file!");
            return -1;
        }
    } while (buf[0]!='R');
    len = finfo.st_size;
    buf[0] = 'O';
    buf[1] = 'K';
    buf[2] = len&0xFF;
    buf[3] = (len>>8)&0xFF;
    buf[4] = (len>>16)&0xFF;
    buf[5] = ETX;
    buf[6] = GetCheckSum(buf+2,3);
	WDEBUG("data len:%d", len);
	WDEBUG_DATA("send data len", buf , 7);
    if (WritePortWithRepeat(s_nAuxPort,7,buf)==APP_FAIL) {
        EchoError("Send file len fail");
        return -1;
    }

    //4.发送文件数据
    fd = open(fpath, O_RDONLY);
    if (fd < 0) {
        EchoError("Fail open file!");
        return -1;
    }
    filelen = finfo.st_size;
    lastframe = 0;
    while (!lastframe) {
        do {
            if (NDK_PortRead(s_nAuxPort, 1, buf, 2000, &readlen)!=NDK_OK) {
                EchoError("Fail in sending file!");
                return -1;
            }
        } while (buf[0]!='S');
        //本次发送包的数据长度
        if (filelen > FL) {
            len = FL;
            filelen -= FL;
            lastframe = 0;
        } else {
            len = filelen;
            lastframe = 1;
        }
        if (len != read(fd, buf+2, len)) {
            EchoError("Read file fail");
            close(fd);
            return -1;
        }
        buf[0] = 'O';
        buf[1] = 'K';
        buf[len+2] = ETX;
        buf[len+3] = GetCheckSum(buf+2, len);
		WDEBUG_DATA("send", buf, len+4);
        if (WritePortWithRepeat(s_nAuxPort, len+4, buf)==APP_FAIL) {
            EchoError("Send file data fail");
            close(fd);
            return -1;
        }
    }
    close(fd);

    return 0;
}

