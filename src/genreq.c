#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
//#include "tinystr.h"
//#include "tinyxml.h"
#include "parsecfg.h"
#include "PriKeyDownload.h"

#include <string.h>
#include "apiinc.h"
#include "appinc.h"
#include "libapiinc.h"
#include "debug.h"

extern int gKEK_GroupNo;
extern int gKEK_SerialNo;
extern int RecieveCertFile(char *pFilename);
extern int SendCertFile(char *fpath, char *fname);

/**
 *@brief 	与POS的握手协议，等待接收ENQ，并发送指定的命令操作。
 *@param		@li opcode	检测到握手信号后，发送的操作码，用于通知POS后续的操作功能。
 *@return  	0 -- 成功
 <0 -- 失败
 */
//int comm_handshake_cmd(char opcode)
//{
//int enqcount = 0;
//int wrongcount = 0;
//char buf[1024];
//int downloadstatus,nLen,i;
//char iFind=FALSE;

//downloadstatus = 0;
//memset(buf, 0, sizeof(buf));

//while (1)
//{
//switch (downloadstatus)
//{
//case 0:		[>等待ENQ请求<]
////			m_portBase->flushport();

//nLen = dl_portread(1, buf, 100);
//if (nLen!=1)
//{
//return APP_FAIL;
//}
//if (buf[0] == DL_ENQ_TYPE)
//{
//enqcount++;
//}
//else
//{
//wrongcount++;
//if (wrongcount > 5)
//{
//return APP_FAIL;
//break;
//}
//}
//if (enqcount > 2)
//{ [>连续收到3个ENQ才可进入下一步<]
////                SendOneFrame(NEW_ENQ);
//WriteDownloadCommand(0x07);
//downloadstatus=1;	[>等待<]
//enqcount = 0;
//wrongcount = 0;
//}
//break;

//case 1:	[>等待刷新操作NEW_ENQ(0x07)握手的响应 0x017<]

//memset(buf,0,sizeof(buf));

//while(buf[0]!=0x17)
//{
////				m_portBase->ReadDataEx(buf,1,100);
//dl_portread(1,buf,100);
//}

//SendOneFrame(opcode);
//WriteDownloadCommand(opcode);
//return APP_SUCC;

//break;

//default:
//break;
//}
//}

//return APP_SUCC;
//}

int wait_connect()
{
	return 0;
}

int wait_respond()
{
	return 0;
}
int make_csr(void)
{
	int nRet;
	char cmd[100];
	char passwd[16+1]; 
	int count;
	int len;

	if(access(CSR_FILE, F_OK) == 0)
		if(APP_SUCC != ProMsgDlg("warning", "file exist! \n Cover it? ", 1, 0, 1))
			return -1;
	/*必须先确保先安装过KEK密钥*/
	if (gKEK_GroupNo < 0 || gKEK_SerialNo < 0){
		WDEBUG("install KEK first GroupNo:%d SerialNO:%d", gKEK_GroupNo, gKEK_SerialNo);
		return -1;
	}

	nRet = edit_csr_ini();
	if(nRet != APP_SUCC){
		WDEBUG("edit error");
		return nRet;
	}
	if((nRet = NDK_SecCalcDes(SEC_KEY_TYPE_TDK, gKEK_GroupNo*10+gKEK_SerialNo+1, "Mypasswd", 8, passwd, SEC_DES_ENCRYPT | SEC_DES_KEYLEN_24))!=NDK_OK){
		WDEBUG("run nRet:%d", nRet);
		strcpy(passwd, "mypass");
		/*return -1;*/
	}
	WDEBUG_DATA("passwd",passwd,8);
	NDK_HexToAsc(passwd, 8, 1, passwd);
	WDEBUG("passwd:%s",passwd);

	NDK_ScrClrs();
	NDK_ScrPrintf("Genrating....");
	sprintf(cmd, "openssl req -new -config %s -passout pass:%s -out %s", CSR_CONFIG_FILE, passwd, CSR_FILE);
	nRet = system(cmd);
	if(nRet != 0){
		EchoError("Generate Failed!");
		return -1;
	}
	NDK_ScrClrs();
	NDK_ScrPrintf("Generate Succ!\n");
	NDK_KbGetCode(1,NULL);

	if(send_csr() != SUCC){
		EchoError("CSR Signed Failed!");
		return -1;
	}
	ProMsgDlg("Info", "Generate CERT SUCC.", 1, 0, 1);

	return APP_SUCC;
}

int edit_csr_ini()
{
	/* variables stored got value */

	/* If there is no parameter in the configuration file,
	   the value is initialized 0 or NULL (boolean value is
	   initialized -1(FALSE)). */

	char **ini_default_bits;
	char **ini_default_keyfile;
	char **ini_default_md;
	char **ini_distinguished_name;
	char **ini_attributes;
	char **ini_prompt;
	char **ini_output_password;
	char **ini_country_name;
	char **ini_state_name;
	char **ini_locality_name;
	char **ini_organization_name;
	char **ini_organization_unit_name;
	char **ini_common_name;
	char **ini_email_address;
	char **ini_challenge_password;
	int sec_num;
	int cur_sec;				/*section number of input variable char *s */

	char szTmpDispStr1[64], szTmpDispStr2[64],szTmpDispStr3[64];
	char InputBuf[64];
	int nLen;
	int nRet;
	int nSection = 0;

	/* array of cfgStruct */
	cfgStruct cfgini[] = {
		/* parameter  type  address of variable */
		{"default_bits",   		CFG_STRING, &ini_default_bits},
		{"default_keyfile",  	  CFG_STRING, &ini_default_keyfile},
		{"default_md",  	  CFG_STRING, &ini_default_md},
		{"distinguished_name",    CFG_STRING, &ini_distinguished_name},
		{"attributes",   		 CFG_STRING, &ini_attributes},
		{"prompt",    CFG_STRING, &ini_prompt},
		/*{"output_password",    CFG_STRING, &ini_output_password},*/
		{"C", CFG_STRING, &ini_country_name},
		{"ST",CFG_STRING, &ini_state_name},
		{"L", CFG_STRING, &ini_locality_name},
		{"O",CFG_STRING, &ini_organization_name},
		{"OU",CFG_STRING, &ini_organization_unit_name},
		{"CN",CFG_STRING, &ini_common_name},
		{"emailAddress",      CFG_STRING, &ini_email_address},
		{"challengePassword",CFG_STRING, &ini_challenge_password},
		{NULL, CFG_END, NULL}
	};


	sec_num = cfgParse( CSR_DEFAULT_CONFIG_FILE, cfgini, CFG_INI);
	if (sec_num <= 0)
	{
		fprintf(stderr,"Err: Invalid configuration file!\n");
		return -1;
	}

	for (sec_num = 0; cfgini[sec_num].type != CFG_END; sec_num++) {
		//buff clear
		memset(InputBuf, 0, sizeof(InputBuf));
		memset(szTmpDispStr1, 0, sizeof(szTmpDispStr1));
		memset(szTmpDispStr2, 0, sizeof(szTmpDispStr2));
		//section detect
		/*if (sec_num <= 6)*/
		/*nSection = 0;*/
		/*else if(sec_num <= 13)*/
		/*nSection = 1;*/
		/*else*/
		/*nSection = 2;*/
		if (*(*(char ***) (cfgini[sec_num].value) + nSection) == NULL)
			nSection ++;

		WDEBUG("default value:[%s]\n", *(*(char ***) (cfgini[sec_num].value) + nSection));
		sprintf(szTmpDispStr1, "Pls input %s:", cfgini[sec_num].parameterName);
		sprintf(szTmpDispStr2, "default value:[%s]",*(*(char ***) (cfgini[sec_num].value) + nSection));
		WDEBUG("DispStr1[%s]\n",szTmpDispStr1);

		nRet = PubInputDlg(szTmpDispStr1, szTmpDispStr2, InputBuf, &nLen, 0, 20, 0, INPUT_MODE_STRING);
		if (nRet != APP_SUCC) {
			return nRet;
		}

		if (nLen != 0) {
			nRet = cfgStoreValue(cfgini, cfgini[sec_num].parameterName, InputBuf, CFG_INI, 1);
			if (nRet != 0) {
				fprintf(stderr, "Err: store failed!\n");
				//				return -1;
			}
		}
	}

	nRet = cfgDump(CSR_CONFIG_FILE,cfgini, 1, 3);
	if (nRet != 0)
	{
		fprintf(stderr,"Err: write file  failed!\n");
		/*return -1;*/
	}
	return 0;
}

int send_csr(void)
{
	int nRet;
	char cmd[30];
	char buf[10];
	int passwd[16+1]; 
	int count;
	int len;
	char recFilename[30] = {0};
	char ch;


	if(APP_SUCC != ProMsgDlg("Ready to Sign", "Connect CA to Sign now?",1,0,1))
		return 0;
	/*nRet = dl_initdownloadport();*/
	nRet = CommInitConfig();

	comm_handshake_cmd(0);
	nRet = SendCertFile(CSR_FILE, CSR_SIGN_FILE);
	if(nRet != SUCC){
		EchoError("Send CSR Failed!");
		return -1;
	}

	count = 0;
	do {
		if (FAIL == dl_portread(1, &ch, 1000)) {
			return -2;
		}
		count++;
		if (count > 100*100) {
			return -2;
		}
		WDEBUG("%s,%d,%d-------------\n", __FUNCTION__, __LINE__, ch);
	} while (ch != 'A');
	WriteDownloadCommand('L');
	if(RecieveCertFile(recFilename) != SUCC){
		EchoError("Generate Certification Failed");
		return -1;
	}
	if(strcmp(recFilename, CERT_FILE) != 0){
		WDEBUG("here");
		EchoError("file name not equal");	
		return -3;
	}
	WDEBUG("done");

	return APP_SUCC;
}
