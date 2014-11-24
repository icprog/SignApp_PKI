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

/*#define MAXSENDLEN        200 [>Ö¡ÖÐÓÐÐ§Êý¾ÝµÄ³¤¶È£¬64 -> 200£¬ÔÝ¶¨Îª200<]*/
/*#define MAXSENDLEN        2200 [>Ö¡ÖÐÓÐÐ§Êý¾ÝµÄ³¤¶È£¬64 -> 200£¬ÔÝ¶¨Îª200<]*/

int Prompt(char *s, int nAttr, int nSeconds)
{
    int nKey;

    NDK_ScrClrs();
    NDK_ScrPrintf(s);
    NDK_KbGetCode(nSeconds,&nKey);
    return nKey; //µÈ´ýÔÚ¹æ¶¨µÄÊ±¼äÀï¶Á°´¼ü
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
** º¯Êý¹¦ÄÜ£ºÏòÏÂÔØ´®¿Ú·¢ËÍÒ»¸ö×Ö½ÚÊý¾Ý
**
** º¯Êý²ÎÊý£º
                    cCmd          ·¢ËÍµÄ×Ö½ÚÊý¾Ý
** ·µ»ØÖµ  £º
                    ÎÞ
** È«¾Ö±äÁ¿£º
** µ÷ÓÃÄ£¿é£º
** Ëµ    Ã÷£ºÎÞ
****************************************************************/
void WriteDownloadCommand(char cCmd)
{
    char szMsg[256];

    if (dl_portwrite(1, &cCmd) == FAIL) {
        if (cCmd != DL_CMD_ENQ) {
            if (g_Language !=0)
                sprintf(szMsg, "RS232: \nWrite %c Fail", cCmd);
            else
                sprintf(szMsg, "´®¿ÚÐ´%cÊ§°Ü", cCmd);
        } else {
            if (g_Language !=0)
                sprintf(szMsg, "RS232: \nFail to enquire\ndownload.");
            else
                strcpy(szMsg, "´®¿Ú: \n·¢ÏÂÔØÇëÇóÊ§°Ü");            /* chenx, 101014 */
        }
        DispMsg_exit(szMsg); //ÏÔÊ¾ÐÅÏ¢ºóÖ±½ÓÓ²¼þ¸´Î»
    }
}


/****************************************************************
** º¯Êý¹¦ÄÜ£º½ÓÊÕÒ»¸ö½á¹¹(frame)
**
** º¯Êý²ÎÊý£º
                   len         ½ÓÊÕµÄÊý¾Ý³¤¶È
                   buf         ½ÓÊÕÊý¾ÝµÄ»º³åÇø
                   time        ³¬Ê±Ê±¼ä
** ·µ»ØÖµ  £º
                   SUCC        ½ÓÊÕ³É¹¦
                   FAIL        ½ÓÊÕÊ§°Ü
** È«¾Ö±äÁ¿£º
** µ÷ÓÃÄ£¿é£º
** Ëµ    Ã÷£ºÃ¿¸öframe ÖÐÓÐ4¸ö×Ö½ÚÊÇ¶îÍâÐÅÏ¢:
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
    // 1.ÔÚÉè¶¨³¬Ê±Ê±¼äÀï£¬´Ó´®¿ÚAUX1 ¶ÁÈ¡len ¸ö×Ö½ÚÊý¾Ýµ½bufÖÐ
    //if((i = portread(DOWNLOAD_PORT, len, buf, time)) != len)
    if ((i = dl_portread(len, buf, time)) != len) { // 'O'K'+data+ETX(1byte)+CheckSum(1byte)
        //NDK_ScrPush();
        //ASSERT_CRLRS();
        //NormalShow("½ÓÊÕÊý¾ÝÖ¡Ê§°Ü!","Failed in receiving data!",2);
        //NDK_ScrPop();
        return FAIL;
    }
    //for(j=0; j<len; j++)
        //PDEBUG("%02x-",buf[j]);
    //¸¨¿Ú½ÓÊÜÊý¾Ý³É¹¦
    // 2.¼ìÑé½ÓÊÕµ½µÄÊý¾ÝÊÇ·ñºÏ·¨

    //Ç°Á½¸ö×Ö½ÚÎª'O' ºÍ'K'
    if ((buf[0] != 'O')||(buf[1] != 'K')) {
        //NormalShow("Í¨Ñ¶ÖÐ´íÎó!\nÃ»ÊÕµ½'OK'´í\n","Error occured in\ncommunication\n",2);
        return FAIL;
    }

    //µ¹ÊýµÚ¶þ¸ö×Ö½ÚÎªEXT
    if (buf[len-2] != ETX) {
        //MessagePrint("Í¨Ñ¶ÖÐ´íÎó\nÃ»ÊÕµ½ETX´í\n","Error occured in\ncommunication\nCannot receive\n\"ETX\"");
        return FAIL;
    }

    //×îºóÒ»¸ö×Ö½ÚÎªÐ£ÑéÂë
    sum = 0;
    for (i=2; i<len-2; i++) {
        sum += (unsigned char)buf[i];
    }

    PDEBUG("\n%s,%d,sum=%x--buflen=%x\n",__FUNCTION__,__LINE__,sum, (unsigned char)buf[len-1]);
    if (sum != (unsigned char)buf[len-1]) {
        //MessagePrint("Í¨Ñ¶ÖÐ´íÎó\n¼ìÑé´í\n","Error occured in\ncommunication\nVerification\nfailed.");
        return FAIL;
    }
    return SUCC;
}

/****************************************************************
** º¯Êý¹¦ÄÜ£º½ÓÊÕÒ»¸öÖ¡£¬ÈçÊ§°ÜÔòÖØ¸´½ÓÊÕ3´Î
**
** º¯Êý²ÎÊý£º
                   len              ½ÓÊÕµÄÊý¾Ý³¤¶È
                   buf              ½ÓÊÕÊý¾ÝµÄ»º³åÇø
                   time             ³¬Ê±Ê±¼ä
** ·µ»ØÖµ  £º
                   SUCC             ½ÓÊÕ³É¹¦
                   FAIL             ½ÓÊÕÊ§°Ü
** È«¾Ö±äÁ¿£ºÎÞ
** µ÷ÓÃÄ£¿é£º
** Ëµ    Ã÷£º1. pos½ÓÊÕ²»³É¹¦ÔòÇëÇópcÖØ·¢¸ÃÖ¡
             2. Ã¿¸öframe ÖÐÓÐ4¸ö×Ö½ÚÊÇ¶îÍâÐÅÏ¢:
                    'O'  'K'  ...  EXT  C
****************************************************************/
int RecOneFrameWithRepeat(int len, char *buf, int time)
{
    int i;
    if (RecOneFrame(len, buf, time) == SUCC) { //½ÓÊÕÒ»¸öÖ¡
        WriteDownloadCommand(DL_CMD_RECEIVE_OK);//½ÓÊÕ³É¹¦Ó¦´ðÃüÁî'Z'
        return SUCC;
    }
    for (i=0; i<3; i++) {
        WriteDownloadCommand(DL_CMD_RESEND);//·¢ËÍÏÂÔØÖ¡ÖØ·¢ÃüÁî'C'
        if (RecOneFrame(len, buf, time) == SUCC) {
            WriteDownloadCommand(DL_CMD_RECEIVE_OK);//½ÓÊÕ³É¹¦Ó¦´ðÃüÁî'Z'
            return SUCC;
        }
    }
    return FAIL;
}


/****************************************************************
** º¯Êý¹¦ÄÜ£º¶ÔÊý¾Ý´ò°ü¡¢¼ÓÈëÐ­Òé×Ö·û
**
** º¯Êý²ÎÊý£º
                  pbuf          Ö¡Ö¸Õë
                  len           ÓÐÐ§Êý¾ÝµÄ³¤¶È
** ·µ»ØÖµ  £º
                  Êý¾Ý´ò°üºóµÄ³¤¶È
** È«¾Ö±äÁ¿£ºÎÞ
** µ÷ÓÃÄ£¿é£ºÎÞ
** Ëµ    Ã÷£ºÎÞ
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
** º¯Êý¹¦ÄÜ£º·¢ËÍÒ»¸öÊý¾ÝÖ¡
**
** º¯Êý²ÎÊý£º
                   sendbuf      Ö¡Ö¸Õë
                   len          Ö¡ÖÐÓÐÐ§Êý¾ÝµÄ³¤¶È
** ·µ»ØÖµ  £º
                   SUCC         ³É¹¦
                   FAIL         Ê§°Ü
** È«¾Ö±äÁ¿£º
** µ÷ÓÃÄ£¿é£º
** Ëµ    Ã÷£º1. ÓÐÐ§Êý¾Ý²»ÄÜ´óÓÚMAXSENDLEN£¬
             2. ÖØ·¢´ÎÊýÎª3´Î¡£
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

    while (irepeat_w < 3) { //ÖØ·¢×î´ó´ÎÊýÎª3´Î
        if (dl_portwrite(frame_len, (char*)buf) == FAIL) {
            if (g_Language !=0)
                DispMsg_exit("RS232: \nWrite Frame Fail");
            else
                DispMsg_exit("´®¿ÚÐ´Ö¡Ê§°Ü");
        }
        while (irepeat_r < 3) {
            if (dl_portread(1, (char*)recvbuf, 1000) < 1) {
                irepeat_r++;
                if (irepeat_r > 2) {
                    //gV2AppErrorCode = ERR_DOWN_COMM;
                    //Í¨Ñ¶¹ÊÕÏ£¬¿ÉÄÜÊÇÏÂÔØÏßÁ´½ÓÎÊÌâ
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


static int gDownlaodPort = PORT_AUX;    //Ä¬ÈÏÏÂÔØÊ¹ÓÃÎïÀí´®¿Ú
static int gUsbOpenFlag = 0;        //USB´®¿Ú¾ä±ú£¬ÒÔ´ò¿ªÔòÎª1,Î´´ò¿ªÔòÎª0
static int s_nAuxPort=PORT_NUM_COM2;//PORT_NUM_USB;//

/****************************************************************
** º¯Êý¹¦ÄÜ£ºÉèÖÃÏÂÔØ¶Ë¿Ú: ´®¿Ú/ USB
**
** º¯Êý²ÎÊý£ºporttype:ÏÂÔØ¶Ë¿ÚÀàÐÍPORT_AUX/PORT_USB
** ·µ»ØÖµ  £ºSUCC/FIAL
** È«¾Ö±äÁ¿£ºÎÞ
** µ÷ÓÃÄ£¿é£ºÎÞ
** Ëµ    Ã÷£ºÃ¿´ÎUSB´®¿ÚÏÂÔØÍê±Ï£¬Òªµ÷ÓÃSetDownloadPortType(PORT_AUX)¹Ø±ÕUSB
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
** º¯Êý¹¦ÄÜ£º·µ»ØÏÂÔØ¶Ë¿Ú: ´®¿Ú/ USB
**
** º¯Êý²ÎÊý£º
** ·µ»ØÖµ  £º   µ±Ç°ÏÂÔØËùÊ¹ÓÃµÄ·½Ê½:
                  ´®¿Ú-- PORT_AUX
                  USB   --  PORT_USB
** È«¾Ö±äÁ¿£ºÎÞ
** µ÷ÓÃÄ£¿é£ºÎÞ
** Ëµ    Ã÷£ºÎÞ
****************************************************************/
int GetDownloadPortType(void)
{
    return gDownlaodPort;
}

/****************************************************************
** º¯Êý¹¦ÄÜ£º³õÊ¼»¯ÏÂÔØ¶Ë¿Ú: ´®¿Ú/ USB
**
** º¯Êý²ÎÊý£ºport--´®¿ÚºÅ,bps--²¨ÌØÂÊ,flags--²ÎÊý
** ·µ»ØÖµ  £ºSUCC/FAIL
** È«¾Ö±äÁ¿£ºÎÞ
** µ÷ÓÃÄ£¿é£ºÎÞ
** Ëµ    Ã÷£ºÎÞ
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
** º¯Êý¹¦ÄÜ£º¶ÁÈ¡ÏÂÔØ¶Ë¿ÚÊý¾Ý
**
** º¯Êý²ÎÊý£ºlen --Êý¾Ý³¤¶È,OutBuf--Êä³ö»º³åÇø,seconds--³¬Ê±Ê±¼ä
** ·µ»ØÖµ  £ºSUCC/FAIL
** È«¾Ö±äÁ¿£ºÎÞ
** µ÷ÓÃÄ£¿é£ºÎÞ
** Ëµ    Ã÷£ºÎÞ
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
** º¯Êý¹¦ÄÜ£ºÐ´ÏÂÔØ¶Ë¿ÚÊý¾Ý
**
** º¯Êý²ÎÊý£ºlen --Êý¾Ý³¤¶È,InBuf--ÏÂ·¢Êý¾ÝÖ¸Õë
** ·µ»ØÖµ  £ºSUCC/FAIL
** È«¾Ö±äÁ¿£ºÎÞ
** µ÷ÓÃÄ£¿é£ºÎÞ
** Ëµ    Ã÷£ºÎÞ
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
** º¯Êý¹¦ÄÜ£ºÇå¿Õ¶Ë¿Ú»º³åÇø
**
** º¯Êý²ÎÊý£ºrxtx --0 - Çå³ý·¢ËÍ»º³åÇø    1-Çå³ý½ÓÊÕ»º³åÇø
** ·µ»ØÖµ  £ºSUCC/FAIL
** È«¾Ö±äÁ¿£ºÎÞ
** µ÷ÓÃÄ£¿é£ºÎÞ
** Ëµ    Ã÷£ºÎÞ
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
            if (rxtx != 1)      /*USB´®¿ÚÖ»Ö§³ÖÇå¿Õ½ÓÊÕ»º³åÇø*/
                return SUCC;
            NDK_PortClrBuf(PORT_NUM_USB);
            break;
        default:
            break;
    }
    return SUCC;
}

/****************************************************************
** º¯Êý¹¦ÄÜ£ºÍË³öÏÂÔØÇ°£¬¹Ø±ÕÏÂÔØ¶Ë¿Ú(USB)
**
** º¯Êý²ÎÊý£ºÎÞ
** ·µ»ØÖµ  £ºÎÞ
** Ëµ    Ã÷£ºÎÞ
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
** º¯Êý¹¦ÄÜ£º½çÃæÌáÊ¾ÓÃ»§£¬Ñ¡ÔñÏÂÔØ·½Ê½£º´®¿Ú»òUSB
**
** º¯Êý²ÎÊý£ºnseconds-- >0  µÈ´ýµÄ³¬Ê±Ê±¼ä£¬µ¥Î»Ãë£¬
                        0   ×èÈûµÈ´ý£¬Ö±µ½ÓÃ»§°´¼ü
                        <0  ²»µÈ´ý£¬²»ÏÔÊ¾½çÃæÌáÊ¾£¬Ö±½Ó·µ»ØÏÂÔØÀàÐÍ£»
** ·µ»ØÖµ  £º ÏÂÔØµÄ¶Ë¿Ú¶¨Òå
    #define PORT_NONE   (-1)    ÎÞÐ§ÏÂÔØ¶Ë¿Ú£¨°´¼üESCÍË³ö£©
    #define PORT_AUX    0       RS232´®¿Ú
    #define PORT_USB    (PORT_AUX+1)    USB´®¿Ú
    #define USB_DISK    (PORT_USB+1)    UÅÌÏÂÔØµÄ·½Ê½
** Ëµ    Ã÷£º
    ´ÓÏÂÔØÅäÖÃÎÄ¼þ"donwnload.cfg"¶ÁÈ¡Ä¬ÈÏÏÂÔØ¶Ë¿Ú£¬ÈôÅäÖÃÎÄ¼þ²»´æÔÚ£¬Ôò´´½¨Ä¬ÈÏÅäÖÃ¡°´®¿ÚÏÂÔØ¡±
    ÅäÖÃÎÄ¼þ¸ñÊ½ÎªDOWNLOAD_PORT=XXX£¬"XXX"¼´ÉÏÊö·µ»ØÖµÖÐµÄ3ÖÐÏÂÔØÀàÐÍºêÃû³Æ£¬ÀýÈç´®¿ÚÏÂÔØ£¨Çø·Ö´óÐ¡Ð´£©£º
    DOWNLOAD_PORT=PORT_AUX
****************************************************************/
#define DOWNLOAD_CFG_FILE   "download.cfg"
#ifdef  fopen
#undef  fopen       //±ØÐëÊ¹ÓÃlinuxÏµÍ³º¯Êýfopen£¬¶ø²»ÊÇpos_fopen
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
        ret = PORT_AUX;     /*ÈôÅäÖÃÎÄ¼þ²»´æÔÚ£¬Ôò´´½¨Ä¬ÈÏÏÂÔØÀàÐÍÎª´®¿Ú*/
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
            NDK_ScrPrintf("__Ñ¡ÔñÍ¨Ñ¶·½Ê½__\n");
            NDK_ScrPrintf(" 1.RS232´®¿Ú\n");
            NDK_ScrPrintf(" 2.USB´®¿Ú\n");
        }
        switch (ret) {
            case PORT_AUX:
                NDK_ScrSetAttr(TEXT_ATTRIBUTE_REVERSE,NULL);
                NDK_ScrGotoxy(0,1*nHeigth);
                if (g_Language !=0) {
                    NDK_ScrPrintf(" 1.UART\n");
                } else {
                    NDK_ScrPrintf(" 1.RS232´®¿Ú\n");
                }
                NDK_ScrSetAttr(TEXT_ATTRIBUTE_NORMAL,NULL);
                break;
            case PORT_USB:
                NDK_ScrSetAttr(TEXT_ATTRIBUTE_REVERSE,NULL);
                NDK_ScrGotoxy(0,2*nHeigth);
                if (g_Language !=0) {
                    NDK_ScrPrintf(" 2.USB-Serial\n");
                } else {
                    NDK_ScrPrintf(" 2.USB´®¿Ú\n");
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
                MessagePrint("\nÆô¶¯USB´®¿Ú\nÇëÉÔºò ...\n","\nload USB serial\nplease wait ...\n",1);
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
                    MessagePrint("\nÆô¶¯USB´®¿Ú\nÇëÉÔºò ...\n","\nload USB serial\nplease wait ...\n",1);
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
*@brief     ³õÊ¼»¯ÏÂÔØ¶Ë¿Ú
*@param     @li ÎÞ
*@section   history     ÐÞ¸ÄÀúÊ·
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
        "ÏÂÔØ¶Ë¿ÚÑ¡Ôñ\n",
        "1.´®¿ÚÒ»\n",
        "2.´®¿Ú¶þ\n",
        "3.USB\n",
        NULL
    };
    char **pmenu;
    int g_language = 0;

    /*char hwinfo[64];*/
    /*unsigned int len;*/

/*
    if (NDK_SysGetPosInfo(SYS_HWINFO_GET_HARDWARE_INFO, &len, hwinfo)==NDK_OK){
        if (hwinfo[5]==1){//Ó²¼þÅäÖÃÖ»ÓÐÒ»¸ö´®¿Ú£¬Ö±½Ó´ò¿ª´®¿ÚÒ»£¬²»Ñ¡Ôñ
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
*@brief 	·¢ËÍÒ»×Ö½ÚµÄÇëÇó»òÏìÓ¦ÃüÁî
*@param	    @li cCmd        ÃüÁî×Ö´®
*@return  	ÎÞ
*@section	history 	ÐÞ¸ÄÀúÊ·
				\<author\>	\<time\>	\<desc\>
*/
void SendOneFrame(char cCmd)
{
	char szMsg[256];

	if (NDK_PortWrite(s_nAuxPort, 1, (char *)&cCmd) != NDK_OK) {
#if LANGUAGE==L_CHINESE
		sprintf(szMsg,"´®¿Ú·¢ËÍ%cÊ§°Ü",cCmd);
#else
		sprintf(szMsg,"Fail in sending %c!",cCmd);
#endif
		EchoError(szMsg);
	}
}
#endif

/**
*@brief 	ÓëPOSµÄÎÕÊÖÐ­Òé£¬µÈ´ý½ÓÊÕENQ£¬²¢·¢ËÍÖ¸¶¨µÄÃüÁî²Ù×÷¡£
*@param		@li opcode	¼ì²âµ½ÎÕÊÖÐÅºÅºó£¬·¢ËÍµÄ²Ù×÷Âë£¬ÓÃÓÚÍ¨ÖªPOSºóÐøµÄ²Ù×÷¹¦ÄÜ¡£
*@return  	0 -- ³É¹¦
			<0 -- Ê§°Ü
*/
int comm_handshake_cmd(char opcode)
{
    int enqcount = 0;
    int wrongcount = 0;
    char buf[16];
    int downloadstatus;
	int len = 0;

    downloadstatus = NONEENQ;
    /*Ô¤Áô500ms£¬È·±£ÏÂ¶ËKLAÓÐ×ã¹»Ê±¼äÍê³ÉÉÏÒ»ÌõÖ¸Áî!!!ÀýÈçset_kla_datetime(0);½ô½Ó×Åµ÷ÓÃenter_x509_auth()*/
    NDK_SysMsDelay(500);
    NDK_PortClrBuf(s_nAuxPort);
    
	//WDEBUG("run");
    //fprintf(stderr, "handshaking cmd %02x...\n",opcode);
    memset(buf, 0, sizeof(buf));
    while (1) {
        switch (downloadstatus) {
        case NONEENQ:
			WDEBUG("run");
           /*µÈ´ýENQÇëÇó*/
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
            if (enqcount > 2) { /*Á¬ÐøÊÕµ½3¸öENQ²Å¿É½øÈëÏÂÒ»²½*/
                /*for (enqcount=0; enqcount<5; enqcount++) {*/
					WDEBUG("run");
                    //SendOneFrame(NEW_ENQ);
					WriteDownloadCommand(NEW_ENQ);
                /*}*/
                downloadstatus=_NEWENQRET;	/*µÈ´ý*/
                enqcount = 0;
                wrongcount = 0;
            }
            break;

        case _NEWENQRET:	/*µÈ´ýË¢ÐÂ²Ù×÷NEW_ENQ(0x07)ÎÕÊÖµÄÏìÓ¦ 0x017*/
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
*@brief 	Ð´Ë¿ÚÊý¾Ý²¢µÈ´ýÓ¦´ð
*@param	    @li aux        ¶Ë¿Ú
            @li pbuf         ·¢ËÍ»º³åÇø
            @li len         ³¤¶È
*@return  	ÎÞ
*@section	history 	ÐÞ¸ÄÀúÊ·
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
            return EchoError("Ð´´®¿ÚÊ§°Ü!");
#else
            return EchoError("Fail in portwriting!");
#endif
        }

       if (NDK_PortRead(aux, 1, buf, 5*1000, &readlen) != NDK_OK) {
#if LANGUAGE==L_CHINESE
            return EchoError("¶Á´®¿ÚÊ§°Ü!");
#else
            return EchoError("Fail in portreading!");
#endif
        }
    } while (buf[0] == 'C');

    return APP_SUCC;
}

/**
*@fn 		unsigned char GetCheckSum(char *pbuf,int len)
*@brief 	»ñÈ¡Ð£ÑéºÍ
*@param	    @li pbuf        Êý¾Ý»º³å
            @li len         ³¤¶È
*@return  	ÎÞ
*@section	history 	ÐÞ¸ÄÀúÊ·
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
*@brief 	ÊµÏÖ½ÓÊÕPOSÖ¤ÊéµÄÁ÷³Ì
*@param		pFilenameÖ¤ÊéÃû³Æ
*@return  	0 -- ³É¹¦
			<0 -- Ê§°Ü
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

    // 1.....½ÓÊÕÎÄ¼þÃû³¤¶È..................................
    NDK_ScrClrs();
#if LANGUAGE==L_CHINESE
    NDK_ScrPrintf("µÈ´ýÖ¤ÊéÃû³¤¶È\n");
#else
    NDK_ScrPrintf("requesting file nlen...\n");
#endif
    if (RecOneFrameWithRepeat(6, buf, 1) == APP_FAIL) {
#if LANGUAGE==L_CHINESE
        EchoError("½ÓÊÕÖ¤ÊéÎÄ¼þÃû³¤¶ÈÊ§°Ü");
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
        EchoError("Ö¤ÊéÎÄ¼þÃûÌ«³¤");
#else
        EchoError("Invaild nlen");
#endif
        return APP_FAIL;
    }
	WDEBUG("recv file name len: %d", tmp.i);
    // 2.....½ÓÊÕÎÄ¼þÃû..................................
    NDK_ScrClrs();
#if LANGUAGE==L_CHINESE
    NDK_ScrPrintf("½ÓÊÕÎÄ¼þÃû...\n");
#else
    NDK_ScrPrintf("Recv file name\n");
#endif
    //buf[0]='F';
    //SendOneFrame(DL_CMD_FILENAME);
	WriteDownloadCommand(DL_CMD_FILENAME);

    if (RecOneFrameWithRepeat(tmp.i+4, buf, 10) == APP_FAIL) {
#if LANGUAGE==L_CHINESE
        EchoError("½ÓÊÕÎÄ¼þÃûÊ§°Ü");
#else
        EchoError("Recv name fail");
#endif
        return APP_FAIL;
    }
    for (i=0; i<tmp.i; i++)
        pFilename[i] = buf[2+i];
    pFilename[i] = 0;
	WDEBUG("recv file name: %s",pFilename);
    // 3......½ÓÊÜÎÄ¼þ³¤¶È.................................
    NDK_ScrClrs();
#if LANGUAGE==L_CHINESE
    NDK_ScrPrintf("½ÓÊÕÊý¾Ý³¤¶È...\n");
#else
    NDK_ScrPrintf("Recv file len\n");
#endif
    //buf[0]='R';
    //SendOneFrame(DL_CMD_FILELEN);
	WDEBUG("run");
	WriteDownloadCommand(DL_CMD_FILELEN);

    if (RecOneFrameWithRepeat(7, buf, 1) == APP_FAIL) {
#if LANGUAGE==L_CHINESE
        EchoError("½ÓÊÕÊý¾Ý³¤¶ÈÊ§°Ü");
#else
        EchoError("Recv flen failed");
#endif
        return APP_FAIL;
    }
    tmp.c[0] = buf[2];
    tmp.c[1] = buf[3];
    tmp.c[2] = buf[4];
    tmp.c[3] = 0;
    len = tmp.i;	/*ÒªÏÂÔØµÄÎÄ¼þ³¤¶È*/
	WDEBUG("file len: %d", len);
    // 4......´ò¿ªÎÄ¼þ.................................
    if ((hnd=open(pFilename, O_RDWR|O_CREAT|O_TRUNC,0666)) == -1) { /*¸²¸ÇÔ­ÎÄ¼þ*/
#if LANGUAGE==L_CHINESE
        EchoError("´´½¨Ö¤ÊéÎÄ¼þÊ§°Ü");
#else
        EchoError("store file failed");
#endif
        return APP_FAIL;
    }
    // 5......½ÓÊÜÊý¾Ý...................................
    NDK_ScrClrs();
#if LANGUAGE==L_CHINESE
    NDK_ScrPrintf("ÎÄ¼þ´óÐ¡:%d\n", len);
    NDK_ScrPrintf("\nÏÂÔØÖÐ...");
#else
    NDK_ScrPrintf("File length:\n%d\n", len);
    NDK_ScrPrintf("\nReceiving...");
#endif
    //½ÓÊÜÊý¾Ý²¢Ð´µ½ÎÄ¼þ
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

        //½ÓÊÕÊý¾Ý
        if (RecOneFrameWithRepeat(rlen+4, buf, 20) == APP_FAIL) {
            close(hnd);
            remove(pFilename);
            EchoError("Receive data \nfailed.");
            return APP_FAIL;
        }
        //Ð´Êý¾Ýµ½ÎÄ¼þ
#if 1 /*lipm add, 20081023 */
        nBytesRead = rlen;
        bp = &buf[2];
        while (nBytesRead > 0) {
            while (((nBytesWrite=write(hnd,bp,nBytesRead))==-1)&&(errno == EINTR))
                ;
            if (nBytesWrite < 0) {
#if LANGUAGE==L_CHINESE
                EchoError("Ð´ÎÄ¼þÊ§°Ü");
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
*@brief 	·¢ËÍKeyloaderServer×ÔÉíµÄÖ¤Êé¸øPOS½øÐÐÑéÖ¤
*@param		ÎÞ
*@return  	0 -- ³É¹¦
			<0 -- Ê§°Ü
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

    //1.·¢ËÍÎÄ¼þÃû³¤¶È
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

    //2.·¢ËÍÎÄ¼þÃû
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

    //3.·¢ËÍÎÄ¼þ³¤¶È
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

    //4.·¢ËÍÎÄ¼þÊý¾Ý
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
        //±¾´Î·¢ËÍ°üµÄÊý¾Ý³¤¶È
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

