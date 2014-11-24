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
    if (Auxautodetect) { //�����������أ��ڴ����Զ����ʧ��֮����ʾ�û�ѡ�����ط�ʽ��
        Auxautodetect = 0;
        DetectedPortType = SelectDownloadPort(0);
        if(DetectedPortType == PORT_AUX) {
            iRet = AuxConflictCheck();// 3.������̨�����ش����Ƿ�����  -------�е��������д��ļ�ʧ�ܵ�ʱ�򷵻ص�Ҳ��FAIL
            if(iRet == FAIL) {
                MessagePrint("��������ʧ��:\n����̨�ʹ��ڳ�ͻ\n�����USB����\n��U�̷�ʽ����...", "Serial conflict \nbetween console \nand download.\nUse usb download...",0);
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
                    iRet = SetDownloadPortType(PORT_USB);       //����USB��������
                    if(FAIL==iRet) {
                        MessagePrint("\n��USB����ʧ��!\n  �˳�����...", "\nOpen USB-Serial failed!\n exit download",0);
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
                return SUCC;//��ʱȷ�� ���ܻ�������
                break;
        }
    } else { //��ѯ���ڶˣ����Բ�ͬ�Ķ˿�����
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
            PortEnableCtrl &= ~(1<<PORT_USB);    //USB�л�ʧ�����ֹUSB�������ع���
            SetDownloadPortType(PORT_AUX);
            dl_initdownloadport();
        } else
            DetectedPortType = PORT_USB;
    } else if ( !(PortEnableCtrl & (1<<PORT_AUX)) ) {
        MessagePrint("\n   ����ʧ��!   ", "\nDownload Failed!",0);
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
            MessagePrint("\n   ����ʧ��!   ", "\nDownload Failed!",0);
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
    if ((Hnd = open("/proc/cmdline", O_RDONLY)) == FSFAIL) { //��/proc/cmdline�ļ�
        MessagePrint("/proc/cmdline\n�ļ���ʧ��","Error on open \n/proc/cmdline.",0);
        return FAIL;
    }
    while (((nBytesRead=read(Hnd,strBuf,sizeof(strBuf)))==FAIL)&&(errno==EINTR));//��ȡ�ļ���ǰ2048���ֽ�����
    if (nBytesRead < 0) {
        MessagePrint("/proc/cmdline\n�ļ���ȡʧ��","Error on read \n/proc/cmdline.",0);
        close(Hnd);
        return FAIL;
    }
    close(Hnd);
    //��"console=tty"ģʽƥ��
    pStrPattern = "console=tty";
    IndexPatStr = Index_FL(strBuf, pStrPattern, 0);
    if (IndexPatStr == FAIL) { //���ڲ�����
        return SUCC;
    } else { //��������
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
            ++i; //���²���ƥ����ʼ��
        } else if (S[i+tLength-1] != patEndChar) {
            //ģʽ����"β�ַ�"��ƥ��
            ++i; //���²���ƥ����ʼ��
        } else {
            //����м��ַ���ƥ�����
            k = 1;
            j = 1;
            while ( (j < tLength) && (S[i+k] == T[j]) ) {
                ++k;
                ++j;
            }
            if ( j == tLength ) {
                return i;
            } else {
                ++i;    //���¿�ʼ��һ�ε�ƥ����*/
            }
        }
    }
    return FAIL;
}

int ConflictOperate(void)
{
	return 0;

    Auxautodetect = 0;  //���ڳ�ͻ��������Ҫ���д��������Զ����
    PortEnableCtrl &= ~(1<<PORT_AUX);

    DetectedPortType = SelectDownloadPort(0);//�û�ѡ�����ط�ʽ
    switch(DetectedPortType) {
        case PORT_NONE:
            return FAIL;
            break;
        case PORT_AUX:
            MessagePrint("��������ʧ��:\n����̨�ʹ��ڳ�ͻ\n�����USB����\n��U�̷�ʽ����...", "Serial conflict \nbetween console \nand download.\nUse usb download...",0);
            return FAIL;
        default:
            break;
    }
    return SUCC;
}

