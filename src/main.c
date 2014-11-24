/**
 * @file main.c
 * @brief 主模块（函数入口）
 * @version  1.0
 * @author 林金珠
 * @date 2009-03-17
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../env/NDK.h"
#include "../inc/appinc.h"
#include "../inc/debug.h"
#include "../inc/key.h"
#include "../inc/oper.h"
#include "../inc/posdef.h"
#include "../libapi/ltool.h"
#include "../libapi/lui.h"
//#include "apiinc.h"
//#include "libapiinc.h"

#include "PriKeyDownload.h"
/**
 * 内部宏定义
 */
#define KEKBRANCHLEN  24
#define INITFLAG 199
#define DES 8
#define TDES 16
#define OPENLINE 1
#define CLOSELINE 0
#define SENDOFFLINE 2
#define SENDONLINE 3
#define SENDPOS '0'
#define SENDPINPAD '1'

/**
 * 内部函数声明
 */
static int InitKeyPos(void);

static int adminOperate(void);
static int SetKEK(void);
static int Chg_KEKBranch(int id);
static void ResetPass(void);

static void GetCheckValue(char* key, char* checkValue, char cType);

/*外部函数声明*/
extern int ProMsgDlg(const char *pszTitle, const char *pszContent, int nBeep, int nTimeOut, int nMode);

int gKEK_GroupNo;
int gKEK_SerialNo;
int gTEK_changeflag;

static int StartMenu(void)
{
	while (1) {
#if LANGUAGE==L_CHINESE
		ShowTitle("新大陆签名系统");
		NDK_ScrPrintf("1.签名菜单\n");
		NDK_ScrPrintf("2.管理菜单\n");
		NDK_ScrPrintf("4.test\n");
		//if (xauth_is_done()) {
		//NDK_ScrPrintf("3.时间设置\n");
		//}
#else
		ShowTitle("NL Signer APP");
		NDK_ScrPrintf("1.Operator\n");
		NDK_ScrPrintf("2.Manager\n");
		//if (xauth_is_done()) {
		//NDK_ScrPrintf("3.Data Setting\n");
		//}
#endif
		switch (PubGetKeyCode(0)) {
			case K_ONE:
#if 1
				/*下发密钥之前必须先确保先安装过KEK密钥，否则无法解密获得密钥明文*/
				if (gKEK_GroupNo < 0 || gKEK_SerialNo < 0) {
#if LANGUAGE==L_CHINESE
					EchoError("请先进入'2.系统管理'安装KEK!");
#else
					EchoError("Pls install KEK first\n in menu '2.manager'!");
#endif
					break;
				}
#endif

				if (access(PRI_KEY_FILE, F_OK) < 0){
					EchoError("NO SIGN KEY!\n");
					return -1;
				}

				if (APP_SUCC == operlog(NORMALOPER)) {
					tmp_entry();
				}
				break;

			case K_TWO:
				PubClearAll();
				if((gTEK_changeflag&(1))==0){
#if LANGUAGE==L_CHINESE
					PubMsgDlg("提示", "初次使用，请 修改管理员1 密码!", 2, 10);
#else
					PubMsgDlg("NOTE", "Initial  Use,\nplease modify the\nAdmin1's PWD", 2, 10);
#endif
					ASSERT_FAIL(ResetOperPwd(KEK1MANAGEROPER));
				}
				if(operlog(KEK1MANAGEROPER)!=APP_SUCC)
					break;
				if((gTEK_changeflag&(1<<1))==0){
#if LANGUAGE==L_CHINESE
					PubMsgDlg("提示", "初次使用，请修改管理员2 密码!", 2, 10);
#else
					PubMsgDlg("NOTE", "Initial  Use,\nplease modify the\nAdmin2's PWD", 2, 10);
#endif
					ASSERT_FAIL(ResetOperPwd(KEK2MANAGEROPER));
				}
				if(operlog(KEK2MANAGEROPER)==APP_SUCC)
				{
					adminOperate();
				}
				break;
				//case K_THREE:
				//if (xauth_is_done()) {
				//set_kla_datetime(1);
				//}
				//break;
			case K_FOUR:
				make_csr();
				/*send_csr();*/
				fprintf(stderr, "make csr return\n");
				break;
			case K_FIVE:
				send_csr();
				fprintf(stderr, "send csr return\n");
				break;
			break;
			case K_ESC:
				return APP_QUIT;

			default:
				break;
		}
	}
	return 0;
}

/**
 * @fn nlmain(void)
 * @brief 程序入口
 * @param 无
 * @return 返回
 */
int main(void)
{
	char Initflag;

	NDK_SysInit();
	PubInitUiParam();
	NDK_ScrAutoUpdate(1, NULL);
	PubClearAll();
	PubKbHit();

	if (NDK_FsExist(TEMP_FILE) == APP_SUCC)
		NDK_FsDel(TEMP_FILE);

	PubGetVar(&Initflag, dInited_off, dInited_len);

	if (Initflag != INITFLAG) {
		if (InitKeyPos()!= APP_SUCC) {
#if LANGUAGE==L_CHINESE
			PubMsgDlg("警告", "初始化不成功!", 3, 10);
#else
			PubMsgDlg("warning", "Fail in the initialization!", 3, 10);
#endif
			return APP_FAIL;
		}
	} else {
		PubGetVar((char*)&gKEK_GroupNo, dKekGroupNo_off, dKekGroupNo_len);
		PubGetVar((char*)&gKEK_SerialNo, dKekSerialNo_off, dKekSerialNo_len);
		PubGetVar((char*)&gTEK_changeflag, dTekflag_off, dTekflag_len);
	}
	//	CommInitConfig();
	return StartMenu();
}

/******************************************************************************
 *	函数名称：InitKeyPos
 *	函数介绍： 首次运行初始化各种母POS参数
 *	函数描述：
 *	入口参数：无
 *	出口参数：无
 *	返回值  ：
 *		FILE_SUCC 成功
 *		FILE_FAIL   失败
 *   	修改者  ：	林金珠
 *   	修改日期：	2009-03-23
 *******************************************************************************/
static int InitKeyPos()
{
	char Initflag;
	int ret;
	int nRecLen = 0;
	char cType = SENDPOS;
	PubClearAll();
#if LANGUAGE==L_CHINESE
	PubDisplayGen(3, "初始化密钥POS...");
#else
	PubDisplayGen(3, "init Key POS...");
#endif
	InitOper();

	if (NDK_FsExist(KEY_FILE) == NDK_OK){
		NDK_FsDel(KEY_FILE);
	}

	PubSaveVar((char*)&nRecLen, dRecNum_off, dRecNum_len);
	PubSaveVar((char*)&cType, dTermtype_off, dTermtype_len);

	gKEK_GroupNo = -1;
	gKEK_SerialNo = -1;
	PubSaveVar((char*)&gKEK_GroupNo, dKekGroupNo_off, dKekGroupNo_len);
	PubSaveVar((char*)&gKEK_SerialNo, dKekSerialNo_off, dKekSerialNo_len);

	gTEK_changeflag= 0;
	PubSaveVar((char*)&gTEK_changeflag, dTekflag_off, dTekflag_len);

	Initflag = INITFLAG;
	ret = NDK_SecKeyErase();
	if ((ret += PubSaveVar(&Initflag, dInited_off, dInited_len)) != APP_SUCC)
		return APP_FAIL;
	PubClearAll();
#if LANGUAGE==L_CHINESE
	PubDisplayGen(5, "初始化各参数成功!");
#else
	PubDisplayGen(5, "init parameters successfully!");
#endif
	PubGetKeyCode(1);
	return APP_SUCC;
}

/******************************************************************************
 *	函数名称：adminOperate
 *	函数介绍：系统管理员界面
 *	函数描述：
 *	入口参数：无
 *	出口参数：无
 *	返回值  ：
 *		FILE_SUCC 成功
 *		FILE_FAIL   失败
 *   	修改者  ：	林金珠
 *   	修改日期：	2009-03-23
 *******************************************************************************/
static int adminOperate()
{
	int ret;

	while (1) {
		PubClearAll();
#if LANGUAGE==L_CHINESE
		ShowTitle("系统管理");
		NDK_ScrPrintf("1 KEK设置\n");
		NDK_ScrPrintf("2  密码改密\n");
		NDK_ScrPrintf("3  初始化设备\n");
		NDK_ScrPrintf("4  文件导出\n");
		NDK_ScrPrintf("5  连接设置\n");
#else
		ShowTitle("management");
		NDK_ScrPrintf("1 KEK setup\n");
		NDK_ScrPrintf("2 Change PWD\n");
		NDK_ScrPrintf("3 Generate CSR\n");
		NDK_ScrPrintf("4 File Backup\n");
		NDK_ScrPrintf("5 Connection Setting\n");
#endif

		switch (ret = PubGetKeyCode(30)) {
			case KEY_ESC:
				return APP_QUIT;
			case KEY_1:
				SetKEK();
				break;
			case KEY_2:
				ResetPass();
				break;
			case KEY_3:
				ret = make_csr();
				WDEBUG("ret = %d", ret);
				break;
			case KEY_4:
				break;
			case KEY_5:
				break;
			default:
				break;
		}
	}
	return APP_SUCC;
}
/******************************************************************************
 *	函数名称：ResetPass
 *	函数介绍：密钥修改
 *	函数描述：
 *	入口参数：无
 *	出口参数：无
 *	返回值  ：
 *   	修改者  ：	林金珠
 *   	修改日期：	2009-03-23
 *******************************************************************************/
static void ResetPass()
{
	int	nRet;
	int   nSelect=0xff;

	while (1) {
#if LANGUAGE==L_CHINESE
		nRet = PubSelectList( "1.管理员1||2.管理员2||3.密钥分发员", "修改密码",  nSelect, &nSelect);
#else
		nRet = PubSelectList( "1.administrator 1||2.administrator 2||3.operator", "change PWD",  nSelect, &nSelect);
#endif
		if (nRet==APP_QUIT || nRet==APP_TIMEOUT) {
			return;
		}

		switch (nSelect) {
			case 1:
				ResetOperPwd(KEK1MANAGEROPER);
				break;
			case 2:
				ResetOperPwd(KEK2MANAGEROPER);
				break;
			case 3:
				ResetOperPwd(NORMALOPER);
				break;
			default:
				break;
		}
	}

}
/******************************************************************************
 *	函数名称：SetKEK
 *	函数介绍：KEK密钥设置
 *	函数描述：
 *	入口参数：无
 *	出口参数：无
 *	返回值  ：
 *		FILE_SUCC 成功
 *		FILE_FAIL   失败
 *   	修改者  ：	林金珠
 *   	修改日期：	2009-03-23
 *******************************************************************************/
static int SetKEK()
{
	int nRecNum = 0;

#if 0
	/*双向认证过才梢灾葱蠯EK密钥下发*/
	if (!xauth_is_done()) {
		if (enter_x509_auth() < 0)
			return -1;
	}
#endif

	PubClearAll();
	//	PDEBUG("gTEK1_changeflag:%d",gTEK_changeflag&(1));
	//	PDEBUG("gTEK2_changeflag:%d",gTEK_changeflag&(1<<1));
	if((gTEK_changeflag&(1))==0){
#if LANGUAGE==L_CHINESE
		PubMsgDlg("提示", "初次使用，修改密码!", 2, 10);
#else
		PubMsgDlg("NOTE", "Initial  Use,modify the PSW", 2, 10);
#endif
		ASSERT_FAIL(ResetOperPwd(KEK1MANAGEROPER));
	}
	if (operlog(KEK1MANAGEROPER)!=APP_SUCC ) {
		return APP_FAIL;
	}	

	ASSERT_FAIL(Chg_KEKBranch(1));
	if((gTEK_changeflag&(1<<1))==0){
#if LANGUAGE==L_CHINESE
		PubMsgDlg("提示", "初次使用，修改密码!", 2, 10);
#else
		PubMsgDlg("NOTE", "Initial  Use,modify the PSW", 2, 10);
#endif
		ASSERT_FAIL(ResetOperPwd(KEK2MANAGEROPER));
	}
	if (operlog(KEK2MANAGEROPER)!=APP_SUCC ) {
		return APP_FAIL;
	}

	ASSERT_FAIL(Chg_KEKBranch(2));
	/*删除所有的TMK密钥*/
	if (NDK_FsExist(KEY_FILE) == APP_SUCC) {
		NDK_FsDel(KEY_FILE);
		PubSaveVar((char*)&nRecNum, dRecNum_off, dRecNum_len);
	}
	return APP_SUCC;
}

/******************************************************************************
 *	函数名称：Chg_KEKBranch
 *	函数介绍：改变主密钥分量值
 *	函数描述：
 *	入口参数：分量的ID号
 *	出口参数：无
 *	返回值  ：
 *		FILE_SUCC 成功
 *		FILE_FAIL   失败
 *   	修改者  ：	林金珠
 *   	修改日期：	2009-03-23
 *******************************************************************************/
static int Chg_KEKBranch(int id)
{
	char buf1[48+ 1], buf2[24+1], keybuf[25], checkvalue[8+1], szIndexNum[2+1],checkvalue2[8+1];
	int  nRet,nLen,i,indexLen;
	char szTmpDispStr1[32], szTmpDispStr2[32],szTmpDispStr3[32];
	int nGroupNo = 0;
	int nSerialNo = 0;
	ST_SEC_KEY_INFO stSecKeyInfo;
	ST_SEC_KCV_INFO stKcvInfo; 

	while (1) {
#if LANGUAGE==L_CHINESE
		sprintf(szTmpDispStr1, "KEK分量%d设置", id);
		sprintf(szTmpDispStr2,"输入分量%d前24位:",id);
		sprintf(szTmpDispStr3,"输入分量%d后24位:",id);
#else
		sprintf(szTmpDispStr1, "KEK component%d", id);
		sprintf(szTmpDispStr2,"input component%d(1st 24 HEX):",id);
		sprintf(szTmpDispStr3,"input component%d(2nd 24 HEX):",id);
#endif

		memset(buf1, 0, sizeof(buf1));
		nRet = PubInputDlg(szTmpDispStr1, szTmpDispStr2, buf1, &nLen, KEKBRANCHLEN, KEKBRANCHLEN, 0, INPUT_MODE_STRING);
		if ( nRet != APP_SUCC ) {
			return nRet;
		}
		nRet = PubInputDlg(szTmpDispStr1, szTmpDispStr3, buf1+KEKBRANCHLEN, &nLen, KEKBRANCHLEN, KEKBRANCHLEN, 0, INPUT_MODE_STRING);
		if ( nRet != APP_SUCC ) {
			return nRet;
		}
		break;
	}

	memset(keybuf, 0 ,sizeof(keybuf));
	memset(checkvalue, 0, sizeof(checkvalue));
	PubAscToHex((unsigned char*)buf1, 48, 0, (unsigned char*)keybuf);
	GetCheckValue(keybuf, checkvalue, TDESTYPE);
#if LANGUAGE==L_CHINESE
	sprintf(szTmpDispStr2,"分量%d校验值为:\n%s", id, checkvalue);
#else
	sprintf(szTmpDispStr2,"KCV of component%d:%s", id, checkvalue);
#endif
	if (APP_SUCC != ProMsgDlg(szTmpDispStr1,szTmpDispStr2,1,30,LANGUAGE)) {
		return APP_QUIT;
	}

	switch (id) {
		case 1:
			PubSaveVar(keybuf, dTek1_off , dTek1_len);
			break;
		case 2:
			PubSaveVar(keybuf, dTek2_off, dTek2_len);


			memset(szIndexNum, 0, sizeof(szIndexNum));
#if LANGUAGE==L_CHINESE
			ASSERT_FAIL(PubInputDlg("KEK设置","请输入KEK索引号:\n", szIndexNum, &indexLen, 1, 2, 30, INPUT_MODE_NUMBER));
#else
			ASSERT_FAIL(PubInputDlg("KEK setup","input KEK's ID:\n", szIndexNum, &indexLen, 1, 2, 30, INPUT_MODE_NUMBER));
#endif
			switch (indexLen) {
				case 0:
					break;
				case 1:
					nSerialNo  = szIndexNum[0] - '0';
					break;
				case 2:
					nGroupNo = szIndexNum[0] -'0';
					nSerialNo = szIndexNum[1] - '0';
					break;
				default:
					break;
			}
			memset(buf2,0,sizeof(buf2));
			PubGetVar(buf2, dTek1_off, dTek1_len);
			for (i=0; i<24; i++)
				keybuf[i] ^= buf2[i];
			memset(checkvalue, 0, sizeof(checkvalue));
			GetCheckValue(keybuf, checkvalue, TDESTYPE);

			/*密钥的值不能由单个组分决定*/
			GetCheckValue(buf2,checkvalue2,TDESTYPE);
			if(!memcmp(checkvalue,checkvalue2,8)){
#if LANGUAGE==L_CHINESE
				EchoError("密钥组分(2)值无效\n 请重新输入! ");
#else
				EchoError("Invalid KEK component2 , please try again!");
#endif
				return APP_FAIL;
			}
			PubGetVar(buf2, dTek2_off, dTek2_len);
			GetCheckValue(buf2, checkvalue2, TDESTYPE);
			if(!memcmp(checkvalue,checkvalue2,8)){
#if LANGUAGE==L_CHINESE
				EchoError("密钥组分(1)值无效\n 请重新输入! ");
#else
				EchoError("Invalid KEK component1 , please try again!");
#endif
				return APP_FAIL;
			}


#if LANGUAGE==L_CHINESE
			sprintf(szTmpDispStr1,"KEK校验值为:\n%s", checkvalue);
			if (APP_SUCC != ProMsgDlg("KEK两分量合并",szTmpDispStr1,1,30,LANGUAGE))
#else
				sprintf(szTmpDispStr1,"CheckValue of KEK:%s", checkvalue);
			if (APP_SUCC != ProMsgDlg("KEK combination",szTmpDispStr1,1,30,LANGUAGE))
#endif
			{
				return APP_QUIT;
			}

			stSecKeyInfo.ucScrKeyIdx=0;
			stSecKeyInfo.ucDstKeyIdx =nGroupNo*10+nSerialNo+1;
			stSecKeyInfo.ucDstKeyType = SEC_KEY_TYPE_TDK;
			stSecKeyInfo.nDstKeyLen = 24;
			memcpy(stSecKeyInfo.sDstKeyValue, keybuf, 24);
			stKcvInfo.nCheckMode=SEC_KCV_NONE;
			stKcvInfo.nLen=0;
			int ret;
			ret=NDK_SecLoadKey(&stSecKeyInfo, &stKcvInfo);
			fprintf(stdout,"ret=[%d]/n",ret);
			if (ret==NDK_OK) {
				gKEK_GroupNo = nGroupNo;
				gKEK_SerialNo = nSerialNo;
				PubSaveVar((char*)&gKEK_GroupNo, dKekGroupNo_off, dKekGroupNo_len);
				PubSaveVar((char*)&gKEK_SerialNo, dKekSerialNo_off, dKekSerialNo_len);
				return APP_SUCC;
			} else {
				gKEK_GroupNo = -1;
				gKEK_SerialNo = -1;
				PubSaveVar((char*)&gKEK_GroupNo, dKekGroupNo_off, dKekGroupNo_len);
				PubSaveVar((char*)&gKEK_SerialNo, dKekSerialNo_off, dKekSerialNo_len);
#if LANGUAGE==L_CHINESE
				ProMsgDlg(szTmpDispStr1,"保存失败!",3,30,LANGUAGE);
#else
				ProMsgDlg(szTmpDispStr1,"Fail in save!",3,30,LANGUAGE);
#endif
				return APP_FAIL;
			}
			break;
		default:
			return APP_FAIL;
	}
	return APP_SUCC;
}

/******************************************************************************
 *	函数名称：GetCheckValue
 *	函数介绍：获得校验值
 *	函数描述：
 *	入口参数：char * key 终端主密钥明文
 *	出口参数：char* checkValue 计算出的校验值
 *	返回值  ：
 *		APP_SUCC 成功
 *		APP_FAIL   失败
 *		APP_QUIT  退出
 *   	修改者  ：	林金珠
 *   	修改日期：2009-03-23
 *******************************************************************************/
void GetCheckValue(char* key, char* checkValue, char cType)
{
	unsigned char szTmp[8  + 1];
	unsigned char szTmpOut[8 + 1];
	char szCheckValue[8+1];
	memset(szTmp, 0, sizeof(szTmp));
	memset(szTmpOut, 0, sizeof(szTmpOut));

	if (cType == '1') {
		NDK_AlgTDes(szTmp, szTmpOut, (unsigned char*)key, 8, ALG_TDS_MODE_ENC);
	} else {
		NDK_AlgTDes(szTmp, szTmpOut, (unsigned char*)key, 24, ALG_TDS_MODE_ENC);
	}
	memcpy(szCheckValue, szTmpOut, 4);
	PubHexToAsc ((unsigned char*)szCheckValue, 8, 0, (unsigned char*)checkValue);
}

