#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "NDK.h"
#include "PriKeyDownload.h"
#include "debug.h"


extern  uchar g_passBuf[8];
int PriKey_Deal(R_RSA_PRIVATE_KEY *prikey,char *inbuf,char *outbuf,int flag)
{
    int ret,i,count,num;
    char Rand_Num[8];
    uchar udesout[8]= {0}, udesin[8]= {0},udataout[8]= {0};
    int nInFileHandle, nOutFileHandle;
    char cmd[256];
    ST_SEC_KCV_INFO stKcvInfoIn;
    ST_SEC_KEY_INFO stKeyInfo;

	WDEBUG("run");
    memset(cmd,0x00,sizeof(cmd));
    memset(udesin, 0x00, sizeof(udesin));
    num=GetNum(inbuf);
    if(FAIL==num) {
        PDEBUG("%s,%d,num=%d-----",__FUNCTION__,__LINE__,num);
        return FAIL;
    }
    stKeyInfo.ucScrKeyIdx=0;
    stKeyInfo.ucScrKeyType=0;
    stKeyInfo.ucDstKeyIdx=num;
    stKeyInfo.ucDstKeyType = SEC_KEY_TYPE_TDK;
    stKeyInfo.nDstKeyLen=8;
    ret= NDK_SecGetRandom(8,Rand_Num);
    char *p;
    if(ret!=NDK_OK) {
        MessagePrint("»ñÈ¡Ëæ»úÊýÊ§°Ü\n","Get Randnum Fail\n",0);
        return FAIL;
    }
    strncpy((char *)stKeyInfo.sDstKeyValue,Rand_Num,8);
    stKcvInfoIn.nCheckMode=SEC_KCV_NONE;
    ret=NDK_SecLoadKey(&stKeyInfo, &stKcvInfoIn);
    if(ret!=NDK_OK) {
        MessagePrint("×°ÔØÃÜÔ¿Ê§°Ü\n","Load Key Fail\n",0);
		fprintf(stderr,"Load Key fail [ret = %d]\n",ret);
		PDEBUG("Load Key fail [ret = %d]\n",ret);
		WDEBUG("Load Key fail [ret = %d]\n",ret);
        return FAIL;
    }

    if ((nInFileHandle = open((const char *)inbuf, O_RDWR|O_CREAT)) <0) {
        PDEBUG("%s,%d,open %s fail\n",__FUNCTION__,__LINE__,inbuf);
        return FAIL;
    }
    if(flag==1) {
        if ((nOutFileHandle = open((const char *)outbuf,O_RDWR)) < 0) {
            PDEBUG("%s,%d,open %s fail,iret=%d\n",__FUNCTION__,__LINE__,outbuf,nOutFileHandle);
            close(nInFileHandle);
            return FAIL;
        }
    } else {
        if ((nOutFileHandle = open((const char *)outbuf, O_RDWR|O_CREAT|O_TRUNC, 0666)) < 0) {
            PDEBUG("%s,%d,open %s fail\n",__FUNCTION__,__LINE__,outbuf);
            close(nInFileHandle);
            return FAIL;
        }
    }
    if(flag==1) {
        p=(char *)prikey;
        for(i=0; i<sizeof(R_RSA_PRIVATE_KEY)/8; i++) {
            count=read(nOutFileHandle,udesin,8);
            if(count!=8) {
                close(nInFileHandle);
                close(nOutFileHandle);
                return FAIL;
            }
            ret=NDK_AlgTDes(udesin,udataout,g_passBuf,8,ALG_TDS_MODE_DEC);
            if(ret!=NDK_OK) {
                MessagePrint("¿ÚÁî½âÃÜÊ§°Ü\n","Password DEC Fail\n",0);
                close(nInFileHandle);
                close(nOutFileHandle);
                return FAIL;
            }
            memcpy(p,udataout,8);
            p+=8;
            ret=NDK_SecCalcDes(SEC_KEY_TYPE_TDK, num, udataout, 8, udesout, SEC_DES_ENCRYPT|SEC_DES_KEYLEN_8);
            if(ret!=NDK_OK) {
                MessagePrint("¼ÓÃÜÊ§°Ü\n","ENCRYPT Fail\n",0);
                close(nInFileHandle);
                close(nOutFileHandle);
                return FAIL;
            }
            count=write(nInFileHandle,udesout,8);
            if(count!=8) {
                close(nInFileHandle);
                close(nOutFileHandle);
                return FAIL;
            }
        }
    } else if(0==flag) {
        p = (char *)prikey;
        for(i=0; i<sizeof(R_RSA_PRIVATE_KEY)/8; i++) {
            memcpy(udesin,p,8);
            p+=8;
            ret=NDK_AlgTDes(udesin,udataout,g_passBuf,8,ALG_TDS_MODE_ENC);
            if(ret!=NDK_OK) {
                MessagePrint("¿ÚÁî¼ÓÃÜÊ§°Ü\n","Password ENC Fail\n",0);
                close(nInFileHandle);
                close(nOutFileHandle);
                return FAIL;
            }
            count=write(nOutFileHandle,udataout,8);
            if(count!=8) {
                close(nInFileHandle);
                close(nOutFileHandle);
                return FAIL;
            }
            ret=NDK_SecCalcDes(SEC_KEY_TYPE_TDK, num, udesin, 8, udesout, SEC_DES_ENCRYPT|SEC_DES_KEYLEN_8);
            if(ret!=NDK_OK) {
                MessagePrint("¼ÓÃÜÊ§°Ü\n","ENCRYPT Fail\n",0);
                close(nInFileHandle);
                close(nOutFileHandle);
                return FAIL;
            }
            count=write(nInFileHandle,udesout,8);
            if(count!=8) {
                close(nInFileHandle);
                close(nOutFileHandle);
                return FAIL;
            }
        }
    } else {
        p = (char *)prikey;
        for(i=0; i<sizeof(R_RSA_PRIVATE_KEY)/8; i++) {
            count=read(nInFileHandle,udesin,8);
            if(count!=8) {
                close(nInFileHandle);
                close(nOutFileHandle);
                return FAIL;
            }
            memcpy(p,udesin,8);
            p+=8;
            ret=NDK_SecCalcDes(SEC_KEY_TYPE_TDK, num, udesin, 8, udesout, SEC_DES_ENCRYPT|SEC_DES_KEYLEN_8);
            if(ret!=NDK_OK) {
                MessagePrint("¼ÓÃÜÊ§°Ü\n","ENCRYPT Fail\n",0);
                close(nInFileHandle);
                close(nOutFileHandle);
                return FAIL;
            }
            count=write(nOutFileHandle,udesout,8);
            if(count!=8) {
                close(nInFileHandle);
                close(nOutFileHandle);
                return FAIL;
            }
        }
    }
    close(nInFileHandle);
    close(nOutFileHandle);
    return SUCC;
}

