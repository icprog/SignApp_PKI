/**
 * @file main.c
 * @brief ��ģ�飨������ڣ�
 * @version  1.0
 * @author �ֽ���
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
 * �ڲ��궨��
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
 * �ڲ���������
 */
static int InitKeyPos(void);

static int adminOperate(void);
static int SetKEK(void);
static int Chg_KEKBranch(int id);
static void ResetPass(void);

static void GetCheckValue(char* key, char* checkValue, char cType);

/*�ⲿ��������*/
extern int ProMsgDlg(const char *pszTitle, const char *pszContent, int nBeep, int nTimeOut, int nMode);

int gKEK_GroupNo;
int gKEK_SerialNo;
int gTEK_changeflag;

static int StartMenu(void)
{
	while (1) {
#if LANGUAGE==L_CHINESE
		ShowTitle("�´�½ǩ��ϵͳ");
		NDK_ScrPrintf("1.ǩ���˵�\n");
		NDK_ScrPrintf("2.����˵�\n");
		NDK_ScrPrintf("4.test\n");
		//if (xauth_is_done()) {
		//NDK_ScrPrintf("3.ʱ������\n");
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
				/*�·���Կ֮ǰ������ȷ���Ȱ�װ��KEK��Կ�������޷����ܻ����Կ����*/
				if (gKEK_GroupNo < 0 || gKEK_SerialNo < 0) {
#if LANGUAGE==L_CHINESE
					EchoError("���Ƚ���'2.ϵͳ����'��װKEK!");
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
					PubMsgDlg("��ʾ", "����ʹ�ã��� �޸Ĺ���Ա1 ����!", 2, 10);
#else
					PubMsgDlg("NOTE", "Initial  Use,\nplease modify the\nAdmin1's PWD", 2, 10);
#endif
					ASSERT_FAIL(ResetOperPwd(KEK1MANAGEROPER));
				}
				if(operlog(KEK1MANAGEROPER)!=APP_SUCC)
					break;
				if((gTEK_changeflag&(1<<1))==0){
#if LANGUAGE==L_CHINESE
					PubMsgDlg("��ʾ", "����ʹ�ã����޸Ĺ���Ա2 ����!", 2, 10);
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
 * @brief �������
 * @param ��
 * @return ����
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
			PubMsgDlg("����", "��ʼ�����ɹ�!", 3, 10);
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
 *	�������ƣ�InitKeyPos
 *	�������ܣ� �״����г�ʼ������ĸPOS����
 *	����������
 *	��ڲ�������
 *	���ڲ�������
 *	����ֵ  ��
 *		FILE_SUCC �ɹ�
 *		FILE_FAIL   ʧ��
 *   	�޸���  ��	�ֽ���
 *   	�޸����ڣ�	2009-03-23
 *******************************************************************************/
static int InitKeyPos()
{
	char Initflag;
	int ret;
	int nRecLen = 0;
	char cType = SENDPOS;
	PubClearAll();
#if LANGUAGE==L_CHINESE
	PubDisplayGen(3, "��ʼ����ԿPOS...");
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
	PubDisplayGen(5, "��ʼ���������ɹ�!");
#else
	PubDisplayGen(5, "init parameters successfully!");
#endif
	PubGetKeyCode(1);
	return APP_SUCC;
}

/******************************************************************************
 *	�������ƣ�adminOperate
 *	�������ܣ�ϵͳ����Ա����
 *	����������
 *	��ڲ�������
 *	���ڲ�������
 *	����ֵ  ��
 *		FILE_SUCC �ɹ�
 *		FILE_FAIL   ʧ��
 *   	�޸���  ��	�ֽ���
 *   	�޸����ڣ�	2009-03-23
 *******************************************************************************/
static int adminOperate()
{
	int ret;

	while (1) {
		PubClearAll();
#if LANGUAGE==L_CHINESE
		ShowTitle("ϵͳ����");
		NDK_ScrPrintf("1 KEK����\n");
		NDK_ScrPrintf("2  �������\n");
		NDK_ScrPrintf("3  ��ʼ���豸\n");
		NDK_ScrPrintf("4  �ļ�����\n");
		NDK_ScrPrintf("5  ��������\n");
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
 *	�������ƣ�ResetPass
 *	�������ܣ���Կ�޸�
 *	����������
 *	��ڲ�������
 *	���ڲ�������
 *	����ֵ  ��
 *   	�޸���  ��	�ֽ���
 *   	�޸����ڣ�	2009-03-23
 *******************************************************************************/
static void ResetPass()
{
	int	nRet;
	int   nSelect=0xff;

	while (1) {
#if LANGUAGE==L_CHINESE
		nRet = PubSelectList( "1.����Ա1||2.����Ա2||3.��Կ�ַ�Ա", "�޸�����",  nSelect, &nSelect);
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
 *	�������ƣ�SetKEK
 *	�������ܣ�KEK��Կ����
 *	����������
 *	��ڲ�������
 *	���ڲ�������
 *	����ֵ  ��
 *		FILE_SUCC �ɹ�
 *		FILE_FAIL   ʧ��
 *   	�޸���  ��	�ֽ���
 *   	�޸����ڣ�	2009-03-23
 *******************************************************************************/
static int SetKEK()
{
	int nRecNum = 0;

#if 0
	/*˫����֤�������ִ��KEK��Կ�·�*/
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
		PubMsgDlg("��ʾ", "����ʹ�ã��޸�����!", 2, 10);
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
		PubMsgDlg("��ʾ", "����ʹ�ã��޸�����!", 2, 10);
#else
		PubMsgDlg("NOTE", "Initial  Use,modify the PSW", 2, 10);
#endif
		ASSERT_FAIL(ResetOperPwd(KEK2MANAGEROPER));
	}
	if (operlog(KEK2MANAGEROPER)!=APP_SUCC ) {
		return APP_FAIL;
	}

	ASSERT_FAIL(Chg_KEKBranch(2));
	/*ɾ�����е�TMK��Կ*/
	if (NDK_FsExist(KEY_FILE) == APP_SUCC) {
		NDK_FsDel(KEY_FILE);
		PubSaveVar((char*)&nRecNum, dRecNum_off, dRecNum_len);
	}
	return APP_SUCC;
}

/******************************************************************************
 *	�������ƣ�Chg_KEKBranch
 *	�������ܣ��ı�����Կ����ֵ
 *	����������
 *	��ڲ�����������ID��
 *	���ڲ�������
 *	����ֵ  ��
 *		FILE_SUCC �ɹ�
 *		FILE_FAIL   ʧ��
 *   	�޸���  ��	�ֽ���
 *   	�޸����ڣ�	2009-03-23
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
		sprintf(szTmpDispStr1, "KEK����%d����", id);
		sprintf(szTmpDispStr2,"�������%dǰ24λ:",id);
		sprintf(szTmpDispStr3,"�������%d��24λ:",id);
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
	sprintf(szTmpDispStr2,"����%dУ��ֵΪ:\n%s", id, checkvalue);
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
			ASSERT_FAIL(PubInputDlg("KEK����","������KEK������:\n", szIndexNum, &indexLen, 1, 2, 30, INPUT_MODE_NUMBER));
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

			/*��Կ��ֵ�����ɵ�����־���*/
			GetCheckValue(buf2,checkvalue2,TDESTYPE);
			if(!memcmp(checkvalue,checkvalue2,8)){
#if LANGUAGE==L_CHINESE
				EchoError("��Կ���(2)ֵ��Ч\n ����������! ");
#else
				EchoError("Invalid KEK component2 , please try again!");
#endif
				return APP_FAIL;
			}
			PubGetVar(buf2, dTek2_off, dTek2_len);
			GetCheckValue(buf2, checkvalue2, TDESTYPE);
			if(!memcmp(checkvalue,checkvalue2,8)){
#if LANGUAGE==L_CHINESE
				EchoError("��Կ���(1)ֵ��Ч\n ����������! ");
#else
				EchoError("Invalid KEK component1 , please try again!");
#endif
				return APP_FAIL;
			}


#if LANGUAGE==L_CHINESE
			sprintf(szTmpDispStr1,"KEKУ��ֵΪ:\n%s", checkvalue);
			if (APP_SUCC != ProMsgDlg("KEK�������ϲ�",szTmpDispStr1,1,30,LANGUAGE))
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
				ProMsgDlg(szTmpDispStr1,"����ʧ��!",3,30,LANGUAGE);
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
 *	�������ƣ�GetCheckValue
 *	�������ܣ����У��ֵ
 *	����������
 *	��ڲ�����char * key �ն�����Կ����
 *	���ڲ�����char* checkValue �������У��ֵ
 *	����ֵ  ��
 *		APP_SUCC �ɹ�
 *		APP_FAIL   ʧ��
 *		APP_QUIT  �˳�
 *   	�޸���  ��	�ֽ���
 *   	�޸����ڣ�2009-03-23
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

