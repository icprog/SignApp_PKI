#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "errno.h"

#include "NDK.h"
#include "Pri_DownloadApi.h"
#include "Pri_DownloadTool.h"
#include "PriKeyDownload.h"

extern int DetectedPortType;
extern int Auxautodetect;
extern unsigned int PortEnableCtrl;

int TimeOutProcess(void)
{
    int iRet;
    if (Auxautodetect) { //若是正常下载，在串口自动检测失败之后，提示用户选择下载方式。
        Auxautodetect = 0;
        DetectedPortType = SelectDownloadPort(0);
        if(DetectedPortType == PORT_AUX) {
            iRet = AuxConflictCheck();// 3.检测控制台和下载串口是否争用  -------有点问题其中打开文件失败的时候返回的也是FAIL
            if(iRet == FAIL) {
                MessagePrint("串口下载失败:\n控制台和串口冲突\n请改用USB串口\n或U盘方式下载...", "Serial conflict \nbetween console \nand download.\nUse usb download...",0);
                iRet = ConflictOperate();
                dl_portexit();
            }
        }
        switch(DetectedPortType) {
            case PORT_NONE:
                return -2;
                break;
            case PORT_USB:
                PortEnableCtrl &= ~(1<<PORT_AUX);
                if (PortEnableCtrl & (1<<PORT_USB)) {
                    iRet = SetDownloadPortType(PORT_USB);       //启动USB串口下载
                    if(FAIL==iRet) {
                        MessagePrint("\n打开USB串口失败!\n  退出下载...", "\nOpen USB-Serial failed!\n exit download",0);
                        return FAIL;
                    }
                } else {
                    return FAIL;
                }
                break;
            default :
                PortEnableCtrl &= ~(1<<PORT_USB);
                DetectedPortType = PORT_AUX;
                dl_initdownloadport();
                return SUCC;//暂时确定 可能会有问题
                break;
        }
    } else { //轮询串口端，尝试不同的端口下载
        PollAuxPort();
    }
    return SUCC;
}

int PollAuxPort()
{
    switch(DetectedPortType) {
        case PORT_AUX:
        case PORT_NUM_COM2:
            PollUSBPort();
            break;
        case PORT_USB:
            PollSeriPort();
            break;
        default :
            break;
    }
    return SUCC;
}
int PollUSBPort()
{
    int iRet;
    if ( PortEnableCtrl & (1<<PORT_USB) ) {
        iRet = SetDownloadPortType(PORT_USB);
        if (iRet == FAIL) {
            PortEnableCtrl &= ~(1<<PORT_USB);    //USB切换失败则禁止USB串口下载功能
            SetDownloadPortType(PORT_AUX);
            dl_initdownloadport();
        } else
            DetectedPortType = PORT_USB;
    } else if ( !(PortEnableCtrl & (1<<PORT_AUX)) ) {
        MessagePrint("\n   下载失败!   ", "\nDownload Failed!",0);
        return FAIL;
    }
    return SUCC;
}
int PollSeriPort()
{
    if (PORT_USB == DetectedPortType) {
        if ( PortEnableCtrl & (1<<PORT_AUX) ) {
            DetectedPortType = PORT_AUX;
            SetDownloadPortType(DetectedPortType);
        } else if ( !(PortEnableCtrl & (1<<PORT_USB)) ) {
            MessagePrint("\n   下载失败!   ", "\nDownload Failed!",0);
            return FAIL ;
        }
    }
    return SUCC;
}

int AuxConflictCheck(void)
{
    char strBuf[2048];
    int Hnd;
    int nBytesRead;
    char *pStrPattern = NULL;
    int IndexPatStr;
    if ((Hnd = open("/proc/cmdline", O_RDONLY)) == FSFAIL) { //打开/proc/cmdline文件
        MessagePrint("/proc/cmdline\n文件打开失败","Error on open \n/proc/cmdline.",0);
        return FAIL;
    }
    while (((nBytesRead=read(Hnd,strBuf,sizeof(strBuf)))==FAIL)&&(errno==EINTR));//读取文件的前2048个字节数据
    if (nBytesRead < 0) {
        MessagePrint("/proc/cmdline\n文件读取失败","Error on read \n/proc/cmdline.",0);
        close(Hnd);
        return FAIL;
    }
    close(Hnd);
    //串"console=tty"模式匹配
    pStrPattern = "console=tty";
    IndexPatStr = Index_FL(strBuf, pStrPattern, 0);
    if (IndexPatStr == FAIL) { //串口不争用
        return SUCC;
    } else { //串口争用
        return FAIL;
    }
}

int Index_FL(char *S, char *T, int pos)
{
    int i, j, k;
    int sLength, tLength;
    char patStartChar, patEndChar;

    sLength = strlen(S);
    tLength = strlen(T);
    i = pos;
    if ((!sLength)||(!tLength)||(pos<0)||(pos>sLength)) {
        return FAIL;
    }
    patStartChar = T[0];
    patEndChar = T[tLength-1];

    while (i <= sLength - tLength + 1) {
        if (S[i] != patStartChar) {
            ++i; //重新查找匹配起始点
        } else if (S[i+tLength-1] != patEndChar) {
            //模式串的"尾字符"不匹配
            ++i; //重新查找匹配起始点
        } else {
            //检查中间字符的匹配情况
            k = 1;
            j = 1;
            while ( (j < tLength) && (S[i+k] == T[j]) ) {
                ++k;
                ++j;
            }
            if ( j == tLength ) {
                return i;
            } else {
                ++i;    //重新开始下一次的匹配检测*/
            }
        }
    }
    return FAIL;
}

int ConflictOperate(void)
{
	return 0;

    Auxautodetect = 0;  //串口冲突，则不再需要进行串口下载自动检测
    PortEnableCtrl &= ~(1<<PORT_AUX);

    DetectedPortType = SelectDownloadPort(0);//用户选择下载方式
    switch(DetectedPortType) {
        case PORT_NONE:
            return FAIL;
            break;
        case PORT_AUX:
            MessagePrint("串口下载失败:\n控制台和串口冲突\n请改用USB串口\n或U盘方式下载...", "Serial conflict \nbetween console \nand download.\nUse usb download...",0);
            return FAIL;
        default:
            break;
    }
    return SUCC;
}

