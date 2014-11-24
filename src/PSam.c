#include "NDK.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>

#define ASSERT_FAIL(x) {if(x<0){fprintf(stderr,"%s,%d\n",__FUNCTION__,__LINE__);return -1;}}
//#define SELECT_APP 0
//#define SELECT_FILE 1

#define APP_SUCC 0
#define APP_QUIT -2
#define APP_FAIL -1

#define PSAM_MAX_APDU_BUFLEN    300     //APDU������󳤶�
#define PSAM_CARD               0x80    //PSAM������
#define SELECT_APP              0x00    //Ӧ��
#define SELECT_FILE             0x01    //�ļ�
#define FIRST_FILE              0xEF01  //EF01�ļ�
#define CHECK_PIN               0x00    //У������
#define MODIFY_PIN              0x01    //�޸�����

extern EM_ICTYPE g_Sam;
int BakPsam_ProICComm(const char cCLA,const char cINS,const char cP1,const char cP2,const char cLc,const char *psInBuf,char cLe,char* psOutBuf,int * pnOutDataLen);

void DebugData(char *title,char *buf,int len)
{
    int i;
    fprintf(stderr,"______%s_______\n",title);
    for(i=0; i<len; i++) {
        fprintf(stderr,"%x ",buf[i]);
    }
    fprintf(stderr,"\n__________________________\n");
}
/**
*����ԭ��: int BakPsam_PowerUp(void)
*��������: ��PSAM���ϵ����
*����:     ��
*����ֵ:   APP_SUCC �ɹ�
*          APP_FAIL ʧ��
**/
int BakPsam_PowerUp(void)
{
    int nRet,len;
    char sATR[64];
    memset(sATR, 0, sizeof(sATR));
    //fprintf(stderr,"gSam=%d\n__________________________\n",g_Sam);
    nRet =  NDK_IccPowerUp(g_Sam, sATR,&len);
    if (nRet != NDK_OK) {
        fprintf(stderr,"PSAM���ϵ�ʧ��:%d\n",nRet);
        return -1;
    }
    return 0;
}

/**
*����ԭ��: int BakPsam_PowerDown(void)
*��������: ��PSAM���µ�
*����:     ��
*����ֵ:   APP_SUCC �ɹ�
*          APP_FAIL ʧ��
**/
int BakPsam_PowerDown(void)
{
    int nRet;
    nRet =  NDK_IccPowerDown(g_Sam);
    if (nRet != NDK_OK) {
        fprintf(stderr,"PSAM���µ�ʧ��:%d\n",nRet);
        return -1;
    }

    return 0;
}

/**
*����ԭ��: int BakPsam_PIN_Operator(char cMode)
*��������: ���������ڸ���EF01�ļ�
*����:     char cMode: CHECK_PIN У������;MODIFY_PIN �޸�����
*����ֵ:   APP_SUCC �ɹ�
*          APP_FAIL ʧ��
*��ע:�ݲ�ʵ��PIN�޸����빦��
**/
int BakPsam_PIN_Operator(char cMode)
{
    int nLen;
    int nResp = 0;
    char sPinBuf[10];
    char szPin[6] = "123456";

    nLen = strlen(szPin);
    NDK_AscToHex((uchar*)szPin,6,0,(uchar*)sPinBuf);
    if ( CHECK_PIN == cMode ) {
        nResp = BakPsam_ProICComm(0x00,0x20,0x00,0x00,3,sPinBuf,0x00,NULL,NULL);
    }
    if ( MODIFY_PIN == cMode ) {
        nResp = BakPsam_ProICComm(0x00,0x20,0x01,0x00,3,sPinBuf,0x00,NULL,NULL);
    }
    ASSERT_FAIL(BakPsam_ChkRsp(nResp));
    return APP_SUCC;
}
/**
*����ԭ��: int BakPsam_Select_Aid(int nMode)
*��������: ��ȡAIDӦ�û��ļ�
*����:     nMode: SELECT_APP Ӧ��  SELECT_FILE �ļ�
*����ֵ:   APP_SUCC �ɹ�
*          APP_FAIL ʧ��
**/
int BakPsam_Select_Aid(int nMode)
{
    char cAidLen = 0 ;
    int nResp = 0;
    char cP1=0x04;
    char sAidTemp[20] = {0};

    switch(nMode) {
        case SELECT_APP:
            memcpy(sAidTemp,"\xA0\x00\x00\x03\x33\x4E\x4C\x42\x57\x43\x41\x52\x44",13);
            cAidLen = 0x0D;
            cP1 = 0x04;
            break;
        case SELECT_FILE:
            memcpy(sAidTemp,"\xEF\x01",2);
            cAidLen = 0x02;
            cP1 = 0x00;
            break;
        default:
            break;
    }
    nResp =  BakPsam_ProICComm(0x00,0xA4,cP1,0x00,cAidLen,sAidTemp,0,NULL,NULL);
    ASSERT_FAIL(BakPsam_ChkRsp(nResp));
    return APP_SUCC;
}





/**
*����ԭ��: int BakPsam_Update_Binary(char cP1,char cP2,const char *psData,int nDatalen)
*��������: ���������ڸ���EF01�ļ�
*����:     cP1 cP2 ƫ����; const char* psData д�뻺����; int nDataLen д������ݳ���
*����ֵ:   APP_SUCC �ɹ�
*          APP_FAIL ʧ��
**/
int BakPsam_Update_Binary(char cP1,char cP2,const char *psData,int nDatalen)
{
    int nResp = 0;
    char cDataLen;
    int offset;

    offset = 0xffff&((cP1<<8)|cP2);
    ASSERT_FAIL(BakPsam_PIN_Operator(CHECK_PIN));
    ASSERT_FAIL(BakPsam_Select_Aid(SELECT_FILE));
    do {
        if(nDatalen>0XFF) {
            cDataLen = 0XFF;
            nDatalen -=0XFF;
        } else {
            cDataLen = nDatalen;
            nDatalen = 0;
        }
        cP1 = offset>>8;
        cP2 = offset&0xff;
        nResp  = BakPsam_ProICComm(0x00,0xD6,cP1,cP2,cDataLen,psData+offset,0,NULL,NULL);
        ASSERT_FAIL(BakPsam_ChkRsp(nResp));
        offset+=cDataLen;
    } while(nDatalen);
    return APP_SUCC;
}

/**
*����ԭ��: int BakPsam_Read_Binary(char cP1,char cP2,char* psResponse,int *pnDataLen,int nLen)
*��������: ���������ڶ�ȡEF01�ļ�
*����:     cP1 cP2 ƫ����; const char* psResponse ��ȡ������; int nLen ������ȡ����
           int *pnDataLen ��������;
*����ֵ:   APP_SUCC �ɹ�
*          APP_FAIL ʧ��
**/
int BakPsam_Read_Binary(char cP1,char cP2,char* psResponse,int *pnDataLen,int nLen)
{
    char cLen;
    int nResp = 0;
    int offset,readlen = 0;
    if(nLen<0)
        return -1;
    offset = 0xffff&((cP1<<8)|cP2);

    do {
        if(nLen>0xff) {
            cLen = 0xff;
            nLen -=0xff;
        } else {
            cLen = nLen;
            nLen = 0;
        }
        cP1 = offset>>8;
        cP2 = offset&0xff;
        nResp = BakPsam_ProICComm(0x00,0xB0,cP1,cP2,NULL,NULL,cLen,psResponse+readlen,pnDataLen);
        ASSERT_FAIL(BakPsam_ChkRsp(nResp));
        offset +=*pnDataLen;
        readlen +=*pnDataLen;
    } while(nLen);
    *pnDataLen = readlen;
    return APP_SUCC;
}

int BakPsam_Read_Param(char* psResponse, int *pnDataLen,int nLen)
{
    int nRet = 0;

    //ASSERT_FAIL(BakPsam_PowerUp());
    ASSERT_FAIL(BakPsam_Select_Aid(SELECT_APP));
    ASSERT_FAIL(BakPsam_PIN_Operator(CHECK_PIN));
    ASSERT_FAIL(BakPsam_Select_Aid(SELECT_FILE));

    nRet = BakPsam_Read_Binary(0x00,0x00,psResponse,pnDataLen,nLen);
    BakPsam_PowerDown();
    return nRet;
}

/**
*����ԭ��: int BakPsam_CommWrite(unsigned char *psSend, int nSendLen, unsigned char *psRecv, int *pnRecvLen)
*��������: ������������ԭʼ�Ķ�д������
*����:     ��
*����ֵ:   APP_SUCC �ɹ�
           <0       ʧ��
**/
int BakPsam_CommWrite(unsigned char *psSend, int nSendLen, unsigned char *psRecv, int *pnRecvLen)
{
    int nRet=0;
    //DebugData("[IC Send]:",psSend,nSendLen);
    nRet =  NDK_Iccrw(g_Sam, nSendLen, (char *)psSend, pnRecvLen, (char *)psRecv);
    if (nRet != NDK_OK) {
        fprintf(stderr,"NDK_Iccrw err:%d\n",nRet);
        return nRet;
    }
    // DebugData("[IC Recv]:",psRecv,*pnRecvLen);
    return 0;
}

/**
*����ԭ��: int BakPsam_ProICComm(const char cCLA,const char cINS,const char cP1,const char cP2,const signed char cLc,const char *psInBuf,char cLe,char* psOutBuf,int * pnOutDataLen)
*��������: ���������ڶ�PSAM����д
*����:     ��
*����ֵ:   0xXXXX   Ӧ����
           APP_FAIL ʧ��
**/
int BakPsam_ProICComm(const char cCLA,const char cINS,const char cP1,const char cP2,const char cLc,const char *psInBuf,char cLe,char* psOutBuf,int * pnOutDataLen)
{
    char sCmd[PSAM_MAX_APDU_BUFLEN];
    int nCmdLen=0,nRecLen=0;
    char sResponse[PSAM_MAX_APDU_BUFLEN];
    int nRet =0;
    if ( cLc >= 256 || cLe >= 256) {
        fprintf(stderr,"ERROR:��д���ȹ���\n");
        return APP_FAIL;
    }
    fprintf(stderr,"%s,%d %d %d \n",__FUNCTION__,__LINE__,cLc,cLe);
    memset(sCmd,0,sizeof(sCmd));
    sCmd[0] = cCLA;
    sCmd[1] = cINS;
    sCmd[2] = cP1;
    sCmd[3] = cP2;
    nCmdLen = 4 ;
    if(cLc>0) { //�������ֽ���
        sCmd[4] = cLc;
        memcpy(sCmd+5,psInBuf,cLc);
        nCmdLen = nCmdLen + 1 + cLc ;
    }
    if(cLe!=0) {
        sCmd[nCmdLen] = cLe;
        nCmdLen = nCmdLen + 1 ;
    }
    memset(sResponse,0,sizeof(sResponse));

    if (NULL != pnOutDataLen ) {
        if( *pnOutDataLen > 0)
            nRecLen = *pnOutDataLen + 2 ;//β��2���ֽڵ�Ӧ����Ϣ
        else if( *pnOutDataLen < 0)
            nRecLen = *pnOutDataLen;
    }
    nRet = BakPsam_CommWrite((uchar*)sCmd,nCmdLen,(uchar*)sResponse,&nRecLen);
    if (nRet < 0) {
        return nRet ;
    }
    if (nRecLen -2 > 0) {
        if (NULL != pnOutDataLen) {
            *pnOutDataLen = nRecLen -2 ;//β��2���ֽڵ�Ӧ����Ϣ
        }
        if (NULL != psOutBuf) {
            memcpy (psOutBuf, sResponse,nRecLen - 2);
        }

    }
    if(nRecLen>=2) {
        return (((unsigned int)(sResponse[nRecLen - 2])) << 8) | sResponse[nRecLen - 1] ;
    } else {
        return APP_FAIL;
    }
}
/**
*����ԭ��: int BakPsam_ChkRsp(int nResponse)
*��������: ���������ڼ�ⷵ����
*����:     ��
*����ֵ:   APP_SUCC �ɹ�
           APP_FAIL ʧ��
**/
int BakPsam_ChkRsp(int nResponse)
{
    fprintf(stderr,"[nResponcse = %d]\n",nResponse);
    if ((nResponse == 0x9000)||((nResponse & 0xFF00) ==  0x6100)) {
        return APP_SUCC;
    }
    if (nResponse == 0x6A83|| nResponse == 0x6A86 || nResponse == 0x9402) {
        return APP_QUIT;
    }
    return APP_FAIL;
}

/**
*����ԭ��: int BakPsam_UpdateParam(const char* sParam, int nLen)
*��������: ���������ڸ��²���
*����:     char* sInput: �̻��š��ն˺ŵȲ���
*          int nLen: ���볤��
*
*����ֵ:   APP_SUCC �ɹ�
           APP_FIAL ʧ��
           APP_QUIT �洢�ռ䲻��
**/
int BakPsam_UpdateParam(const char* sParam, int nLen)
{
    int nRet = 0;
    //ASSERT_FAIL(BakPsam_PowerUp());
    ASSERT_FAIL(BakPsam_Select_Aid(SELECT_APP));
    ASSERT_FAIL(nRet);
    nRet = BakPsam_Update_Binary(0x00,0x00,sParam,nLen);
    BakPsam_PowerDown();
    return nRet;
}

/*int main(int argc,char *argv[])
{
    char buf[584];
    char read[584];
    int filelen,i;

    memset(read,0,sizeof(read));
    memset(buf,'1',72);
    memset(buf+72,'2',256);
    memset(buf+72+256,'3',256);

    if(BakPsam_UpdateParam(buf,sizeof(buf))<0)
    {
        fprintf(stderr,"BakPsam_UpdateParam err!!\n");
        return -1;
    }

    if(BakPsam_Read_Param(read,&filelen,sizeof(read))<0)
    {
        fprintf(stderr,"BakPsam_UpdateParam err!!\n");
        return -1;
    }
    fprintf(stderr,"read file len:%d\n",filelen);
    for(i=0;i<filelen;i++)
    {
        fprintf(stderr,"%x ",read[i]);
    }
    fprintf(stderr,"\nread file end\n",__FUNCTION__,__LINE__);

}*/

