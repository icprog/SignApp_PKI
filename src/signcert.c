#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "parsecfg.h"
#include "apiinc.h"
#include "appinc.h"
#include "libapiinc.h"
#include "debug.h"
#include "PriKeyDownload.h"

extern int gKEK_GroupNo;
extern int gKEK_SerialNo;
extern int RecieveCertFile(char *pFilename);
extern int SendCertFile(char *fpath, char *fname);

#if 0
int make_crt()
{
	int nRet;
	if (access(KEY_FILE, F_OK) < 0)
		return -1;

	nRet = recv_csr();
	if(nRet != APP_SUCC)
		return -1;

	if(APP_SUCC != show_csr())
		return -2;

	if(APP_SUCC != make_csr_sign())
		return -3;

	if(APP_SUCC != send_crt())
		return -4;

}
#endif

int edit_ca_ini()
{

	/* variables stored got value */

		/* If there is no parameter in the configuration file,
		   the value is initialized 0 or NULL (boolean value is
		   initialized -1(FALSE)). */

		char **ini_default_ca;
		char **ini_dir;
		/*char **ini_certs;*/
		char **ini_new_certs_dir;
		char **ini_database;
		char **ini_serial;
		char **ini_RANDFILE;
		char **ini_certificate;
		char **ini_private_key;
		char **ini_default_days;
		char **ini_default_crl_days;
		char **ini_default_md;
		/*char **ini_preserve;*/
		char **ini_policy;
		char **ini_countryName;
		char **ini_stateOrProvinceName;
		/*char **ini_localityName;*/
		char **ini_organizationName;
		char **ini_organazationUniteName;
		char **ini_commonName;
		char **ini_emailAddress;
		int sec_num;
		/*int cur_sec;				[>section number of input variable char *s <]*/

		char szTmpDispStr1[64], szTmpDispStr2[64];
		char InputBuf[64];
		int nLen = 0;
		int nRet = 0;
		int nSection = 0;

		/* array of cfgStruct */
		cfgStruct cfgini[] = {
			/* parameter  type  address of variable */
			{"default_ca",   		CFG_STRING, &ini_default_ca},
			{"dir",   				CFG_STRING, &ini_dir},
			{"database",		    CFG_STRING, &ini_database},
			//{"certs",  	  			CFG_STRING, &ini_certs},
			{"new_certs_dir",  		CFG_STRING, &ini_new_certs_dir},
			{"certificate", 	    CFG_STRING, &ini_certificate},
			{"serial",   		 	CFG_STRING, &ini_serial},
			{"private_key",		  	CFG_STRING, &ini_private_key},
			{"RANDFILE",		    CFG_STRING, &ini_RANDFILE},
			{"default_days",		CFG_STRING, &ini_default_days},
			{"default_crl_days", 	CFG_STRING, &ini_default_crl_days},
			{"default_md",			CFG_STRING, &ini_default_md},
			//{"preserve",			CFG_STRING, &ini_preserve},
			{"policy",				CFG_STRING, &ini_policy},
			{"countryName",      	CFG_STRING, &ini_countryName},
			{"stateOrProvinceName",	CFG_STRING, &ini_stateOrProvinceName},
			/*{"localityName",		CFG_STRING, &ini_localityName},*/
			{"organizationName",	CFG_STRING, &ini_organizationName},
			{"organizationalUnitName",CFG_STRING, &ini_organazationUniteName},
			{"commonName",			CFG_STRING, &ini_commonName},
			{"emailAddress",		CFG_STRING, &ini_emailAddress},
			{NULL, 					CFG_END, NULL}
		};


		nRet = cfgParse( CA_DEFAULT_CONFIG_FILE, cfgini, CFG_INI);
		if (nRet <= 0)
		{
			fprintf(stderr,"Err: Invalid configuration file!\n");
			return -1;
		}

		for (sec_num = 0; cfgini[sec_num].type != CFG_END; sec_num++) {
			//buff clear
			nLen = 0;
			memset(InputBuf, 0, sizeof(InputBuf));
			memset(szTmpDispStr1, 0, sizeof(szTmpDispStr1));
			memset(szTmpDispStr2, 0, sizeof(szTmpDispStr2));
			//section detect
			if (*(*(char ***) (cfgini[sec_num].value) + nSection) == NULL)
				nSection ++;

			WDEBUG("default value:[%s]\n", *(*(char ***) (cfgini[sec_num].value) + nSection));
			sprintf(szTmpDispStr1, "Pls input %s:", cfgini[sec_num].parameterName);
			sprintf(szTmpDispStr2, "default value:[%s]",*(*(char ***) (cfgini[sec_num].value) + nSection));

			nRet = PubInputDlg(szTmpDispStr1, szTmpDispStr2, InputBuf, &nLen, 0, 20, 0, INPUT_MODE_STRING);
			if (nRet != APP_SUCC) {
				return nRet;
			}

			if (nLen != 0) {
				WDEBUG("store value");
				nRet = cfgStoreValue(cfgini, cfgini[sec_num].parameterName, InputBuf, CFG_INI, 1);
				if (nRet != 0) {
					fprintf(stderr, "Err: store failed!\n");
					return -1;
				}
			}
		}


		nRet = cfgDump(CA_CONFIG_FILE,cfgini, 1, 3);
		if (nRet != 0)
		{
			fprintf(stderr,"Err: write file  failed!\n");
			/*return -1;*/
		}

		WDEBUG("edit end");
		return 0;
}

int make_csr_sign()
{
	int nRet;
	char cmd[512];
	char passwd[16+1] = {0};

	if (access(CSR_SIGN_FILE, F_OK) < 0)
		return -1;

	nRet = edit_ca_ini();

	if(nRet != 0)
		return -1;

	NDK_ScrClrs();
	NDK_ScrPrintf("Generate....");

	/*必须先确保先安装过KEK密钥*/
	if (gKEK_GroupNo < 0 || gKEK_SerialNo < 0)
		return -1;

	//if (NDK_SecCalcDes(SEC_KEY_TYPE_TDK, gKEK_GroupNo*10+gKEK_SerialNo+1, "Mypasswd", 8, passwd, SEC_DES_ENCRYPT | SEC_DES_KEYLEN_24)!=NDK_OK){
		//WDEBUG("encrypt passwd error");
		//return -2;
	//}
	WDEBUG_DATA("passwd",passwd,8);
	//NDK_HexToAsc(passwd, 8, 1, passwd);
	strcpy(passwd, "mypass");
	WDEBUG("passwd:%s",passwd);

	sprintf(cmd, "openssl ca -config %s -batch -passin pass:%s -out %s -infiles %s", CA_CONFIG_FILE, passwd, NEW_CERT_FILE ,CSR_SIGN_FILE);
	WDEBUG("%s", cmd);
	nRet = system(cmd);
	if(nRet != 0){
		WDEBUG("error");
		return -3;
	}

	NDK_ScrClrs();
	NDK_ScrPrintf("Generate Succ!\n");
	NDK_KbGetCode(0, &nRet);
	fprintf(stderr,"return 0\n");
	return 0;
}

int show_csr()
{
	char cmd[30];
	char szDisp[500] = {0};
	int fp;
	int rlen;

	snprintf(cmd,"openssl req -in %s -subject -noout > tmp.txt", CSR_SIGN_FILE);
	system(cmd);
	fp = open("tmp.txt", O_RDONLY);
	rlen = read(fp, szDisp, 500);
	
	if(APP_SUCC != ProMsgDlg("subject info", szDisp, 1, 0, 1))
		return APP_QUIT;

	WDEBUG("show accept");

	return 0;
}

int recv_csr()
{
	return tmp_entry(FIVE);
}

//int send_crt()
//{
	//int fp;
	//int len,  j, rlen, lastframe;
	//int count;
	//char buf[2048];
	//union {
		//char c[4];
		//int i;
	//} tmp;
	//int nBytesRead, nBytesWrite;
	//char *bp = NULL;
	//char *pFilename=CSR_SIGN_FILE;
	//char ch;
	//int iret;

	//fp = open(NEW_CERT_FILE,O_RDONLY);
	//lseek(fp, 0, SEEK_SET);
	//len = lseek(fp, 0, SEEK_END);
	//if(len <=0 || len > 2000)
		//return -1;

	//do {
		//WriteDownloadCommand(0x34);
		//iret = dl_portread(1, &ch, 3000);
		//PDEBUG("%s,%d,%c,%d-------------\n", __FUNCTION__, __LINE__, ch, iret);
	//}while(ch != 'R');
	//SendFrameWithRepeat(&len, 4);

	//lseek(fp, 0, SEEK_SET);
	//rlen = read(fp, buf, 2048);
	//if(rlen <= 0)
		//return -1;
	//WDEBUG("file data:%s", buf);
	//WDEBUG_DATA("file data", buf, rlen);
	//insertprotocol(buf, rlen);

	//count = 0;
	//do {
		//if (FAIL == dl_portwrite(len, (char *) buf)) {
			//return -2;
		//}
		//count++;
		//if (count > 5) {
			//return -2;
		//}
		//iret = dl_portread(1, &ch, 3000);
		//PDEBUG("%s,%d,%c,%d-------------\n", __FUNCTION__, __LINE__, ch, iret);
	//} while (ch == 'C');

	//if(ch != 'Z')
		//return -1;

	//return 0;
//}

