/**
* @file oper.c
* @brief ����Ա����ģ��
* @version  1.0
* @author Ф����
* @date 2009-03-20
*/
#include "oper.h"
#include "appinc.h" 

#define ADMINPWD		    "87654321"		/**< ϵͳ����Ա��ʼ����*/
#define MANAGERPWD		    "123456"			/**< ���ܳ�ʼ����*/
#define KEK1MANAGERPWD		"88888888"			/**< KEK��һ��������Ա��ʼ����*/
#define KEK2MANAGERPWD		"99999999"			/**< KEK�ڶ���������Ա��ʼ����*/
#define NORMALOPERPWD	    "00000000"			/**< ��ͨ����Ա��ʼ����*/

#define MANAGERPWDLEN		    6				/**< ���ܲ���Ա���볤��*/
#define KEK1MANAGERPWDLEN		8				/**< KEK��һ��������Ա���볤��*/
#define KEK2MANAGERPWDLEN		8				/**< KEK�ڶ���������Ա���볤��*/
#define NORMALPWDLEN		    8				/**< ��ͨ����Ա���볤��*/
#define ADMINOPERPWDLEN	        8				/**< ϵͳ����Ա���볤��*/


/*�ⲿ��������*/
extern int ProMsgDlg(const char *pszTitle, const char *pszContent, int nBeep, int nTimeOut, int nMode);

extern int gTEK_changeflag;
/**
* @fn InitOper
* @brief ��ʼ������Ա��¼
*
*	��ʼ��ϵͳ����Ա���ݣ�����һ��ϵͳ����Ա��һ�����ܣ�KEK��һ�ڶ���������Ա
       �����ͨ����Ա��ż���Ӧ�ĳ�ʼ����
* @return
* @li APP_SUCC
* @li APP_FAIL
*/
void InitOper(void)
{
	STOPER_RECORD stOperRec;
	STRECFILE stOperFile;

	/**
	*��������Ա�ļ��������г�ʼ��
	*/
	memset(&stOperFile, 0, sizeof(STRECFILE));
	strcpy( stOperFile.szFileName, FILE_OPER );
	stOperFile.cIsIndex = FILE_CREATEINDEX;						/**< ���������ļ�*/
	stOperFile.unMaxOneRecLen = sizeof(STOPER_RECORD);
	stOperFile.unIndex1Start =(unsigned int)( (char *)(stOperRec.szOperNo) - (char *)&stOperRec)+1;
	stOperFile.unIndex1Len =  OPERCODELEN;
	stOperFile.unIndex2Start =  (unsigned int)( (char *)(&stOperRec.cDeleFlag) - (char *)&stOperRec)+1;
	stOperFile.unIndex2Len = sizeof(stOperRec.cDeleFlag);
	ASSERT(PubCreatRecFile(&stOperFile));

	/**
	*��ʼ�� ϵͳ����Ա��¼�����99
	*/

	sprintf( stOperRec.szOperNo, "%0*d", OPERCODELEN, 99 );
	stOperRec.cOperRole = ADMINOPER;
	stOperRec.cOperPwdLen = ADMINOPERPWDLEN;
	strcpy(stOperRec.szPasswd, ADMINPWD );
	stOperRec.cDeleFlag = '+';
	PubAddRec(FILE_OPER, (const char *)&stOperRec );

	/**
	*��ʼ�� ���ܲ���Ա��¼�����00
	*/

	sprintf( stOperRec.szOperNo, "%0*d", OPERCODELEN, 0 );
	stOperRec.cOperRole = MANAGEROPER;
	stOperRec.cOperPwdLen = MANAGERPWDLEN;
	strcpy(stOperRec.szPasswd, MANAGERPWD );
	stOperRec.cDeleFlag = '+';
	PubAddRec(FILE_OPER, (const char *)&stOperRec );

	/**
	*��ʼ��KEK��һ��������Ա��¼�����91
	*/

	sprintf( stOperRec.szOperNo, "%0*d", OPERCODELEN, 91 );
	stOperRec.cOperRole = KEK1MANAGEROPER;
	stOperRec.cOperPwdLen = KEK1MANAGERPWDLEN;
	strcpy(stOperRec.szPasswd, KEK1MANAGERPWD );
	stOperRec.cDeleFlag = '+';
	PubAddRec(FILE_OPER, (const char *)&stOperRec );

	/**
	*��ʼ��KEK��һ��������Ա��¼�����92
	*/
	sprintf( stOperRec.szOperNo, "%0*d", OPERCODELEN, 92 );
	stOperRec.cOperRole = KEK2MANAGEROPER;
	stOperRec.cOperPwdLen = KEK2MANAGERPWDLEN;
	strcpy(stOperRec.szPasswd, KEK2MANAGERPWD );
	stOperRec.cDeleFlag = '+';
	PubAddRec(FILE_OPER, (const char *)&stOperRec );

	/**
	*��ʼ�������ͨ����Ա��¼,���01-05
	*/
	stOperRec.cOperRole = NORMALOPER;
	stOperRec.cOperPwdLen = NORMALPWDLEN;
	strcpy(stOperRec.szPasswd, NORMALOPERPWD );
	stOperRec.cDeleFlag = '+';

	sprintf( stOperRec.szOperNo, "%0*d", OPERCODELEN, 1 );
	PubAddRec(FILE_OPER, (const char *)&stOperRec );
}

/**
* @fn FindOper
* @brief �����ṩ�Ĳ���Ա�Ľ�ɫ���õ�����Ա����Ϣ��
* @param in nRole ����Ա��ɫ
* @param out STOPER_RECORD *pstOperRec ����Ա��¼��Ϣ
* @param out int *pnOperRecNum  ����Ա��¼��
* @return
* @li APP_SUCC
* @li APP_FAIL
*/
int FindOper( int nRole, STOPER_RECORD *pstOperRec, int *pnOperRecNum )
{
	int i;
	int nRecNum;

	PubGetRecSum(FILE_OPER, &nRecNum);
	for (i = 0; i < nRecNum; i++) {
		ASSERT_FAIL(PubReadOneRec(FILE_OPER, i+1, (char *)pstOperRec));
		if ( pstOperRec->cDeleFlag == '+'  && pstOperRec->cOperRole == nRole ) {
			*pnOperRecNum = i + 1;
			return APP_SUCC;
		}
	}
	return APP_FAIL;
}
/**
* @fn		int km_db_exist_sql(char *key_owner, char *sqlstr)
* @li		�жϱ����Ƿ���ڲ�ͬ��ԿID������ֵͬ����Կ��¼
* 			�ú������������ǰ�װ�����ʹ�ã�
* @retval	1		���ڸ���Կ
* @retval 	0		�����ڸ���Կ
*/
int exist_other_value(char *psw, int pswlen)
{
#if 0
	int i;
	int rc=0;
	int nRecNum;	
	STOPER_RECORD OperRec;
	PubGetRecSum(FILE_OPER, &nRecNum);
	for (i = 0; i < nRecNum; i++) {
		PubReadOneRec(FILE_OPER, i+1,&OperRec);
		if (!memcmp(psw,&OperRec.szPasswd,pswlen)) {
			rc =1;
		}
	}
	return rc;
#else
	return 0;
#endif
}


/**
* @fn ResetOperPwd
* @brief �����ṩ�Ĳ���Ա�Ľ�ɫ���ò���Ա����Ϣ��
* @param in nRole ����Ա��ɫ
* @param out STOPER_RECORD *pstOperRec ����Ա��¼��Ϣ
* @param out int *pnOperRecNum  ����Ա��¼��
* @return
* @li APP_SUCC
* @li APP_FAIL
*/
int ResetOperPwd(int nRole)
{
	STOPER_RECORD stOperRec;
	char szOperPasswd[ADMINOPERPWDLEN+1], szPasswdStr[ADMINOPERPWDLEN+1];
	char szTmpDispStr1[32], szTmpDispStr2[32];
	int nRet, nlen, nOperRecNum, nPasswdLen;

	if ( (nRet = FindOper( nRole, &stOperRec, &nOperRecNum  ) )!=APP_SUCC) {
		return nRet;
	}

	while (1) {
		switch ( nRole ) {
		case ADMINOPER:
#if LANGUAGE==L_CHINESE
			strcpy( szTmpDispStr1, "ϵͳ����Ա����" );
#else
			strcpy( szTmpDispStr1, "administrator");
#endif
			nPasswdLen = ADMINOPERPWDLEN;
			break;
		case KEK1MANAGEROPER:
#if LANGUAGE==L_CHINESE
			strcpy( szTmpDispStr1, "����Ա1 ����" );
#else
			strcpy( szTmpDispStr1, "Admin1 Setting");
#endif
			nPasswdLen = KEK1MANAGERPWDLEN;
			break;
		case KEK2MANAGEROPER:
#if LANGUAGE==L_CHINESE
			strcpy( szTmpDispStr1, "����Ա2 ����" );
#else
			strcpy( szTmpDispStr1, "Admin2 Setting");
#endif
			nPasswdLen = KEK2MANAGERPWDLEN;
			break;
		case NORMALOPER:
#if LANGUAGE==L_CHINESE
			strcpy( szTmpDispStr1, "��Կ�ַ�Ա����" );
#else
			strcpy( szTmpDispStr1, "Operator Setting");
#endif
			nPasswdLen = NORMALPWDLEN;
			break;
		default:
			return APP_FAIL;
		}

#if LANGUAGE==L_CHINESE
		strcpy( szTmpDispStr2, "����������:" );
#else
		strcpy( szTmpDispStr2, "input old PWD:" );
#endif
		/**
		 * ����ԭ���벢У��
		 */
		memset(szOperPasswd, 0, sizeof(szOperPasswd));
		nRet = PubInputDlg(szTmpDispStr1, szTmpDispStr2, szOperPasswd, &nlen, 7, nPasswdLen, 60, INPUT_MODE_PASSWD);
		if ( nRet != APP_SUCC ) {
			return nRet;
		}
		if ( stOperRec.cOperPwdLen != nlen || memcmp(szOperPasswd, stOperRec.szPasswd,  stOperRec.cOperPwdLen) ) {
#if LANGUAGE==L_CHINESE
			PubMsgDlg(szTmpDispStr1, "ԭ���벻��", 1, 50 ) ;
#else
			PubMsgDlg(szTmpDispStr1, "old PWD is bad", 1, 50 ) ;
#endif
			continue;
		}

		memset(szOperPasswd, 0, sizeof(szOperPasswd));
#if LANGUAGE==L_CHINESE
		nRet = PubInputDlg(szTmpDispStr1, "������������:", szOperPasswd, &nlen, 7, nPasswdLen, 60, INPUT_MODE_PASSWD);
#else
		nRet = PubInputDlg(szTmpDispStr1, "input new PWD:", szOperPasswd, &nlen, 7, nPasswdLen, 60, INPUT_MODE_PASSWD);
#endif
		if ( nRet != APP_SUCC ) {
			return nRet;
		}
		memset(szPasswdStr, 0, sizeof(szPasswdStr));
#if LANGUAGE==L_CHINESE
		nRet = PubInputDlg(szTmpDispStr1, "�ٴ�����:", szPasswdStr, &nlen, 7, nPasswdLen, 60, INPUT_MODE_PASSWD);
#else
		nRet = PubInputDlg(szTmpDispStr1, "input new PWD again:", szPasswdStr, &nlen, 7, nPasswdLen, 60, INPUT_MODE_PASSWD);
#endif
		if ( nRet != APP_SUCC ) {
			return nRet;
		}

		if (  memcmp(szOperPasswd, szPasswdStr, nPasswdLen) ) {
#if LANGUAGE==L_CHINESE
			PubMsgDlg(szTmpDispStr1, "�����������벻ͬ", 1, 50 ) ;
#else
			PubMsgDlg(szTmpDispStr1, "difference between 2 new PWDs", 1, 50 ) ;
#endif
			continue;
		} 
		if(exist_other_value(szOperPasswd, nlen) ){
#if LANGUAGE==L_CHINESE
				PubMsgDlg(szTmpDispStr1, "�� ������ͬ��PSWֵ,����������", 1, 50 ) ;
#else
				PubMsgDlg(szTmpDispStr1, "PSW same value already exits,please reset ", 1, 50 ) ;
#endif						
				continue;
		}else{
			strcpy( stOperRec.szPasswd,  szOperPasswd );
			stOperRec.cOperPwdLen = nlen;
			nRet = PubUpdateRec (FILE_OPER, nOperRecNum, (const char *)&stOperRec );
			if (nRet == APP_SUCC) {
#if LANGUAGE==L_CHINESE
				PubMsgDlg(szTmpDispStr1, "�����޸ĳɹ�", 1, 50 ) ;
#else
				PubMsgDlg(szTmpDispStr1, "change PWD successfully", 1, 50 ) ;
#endif			
				switch(nRole){
					case MANAGEROPER:
						break;
					case NORMALOPER:
						break;
					case ADMINOPER:
						break;
					case KEK1MANAGEROPER:
						gTEK_changeflag|=1;
						break;
					case KEK2MANAGEROPER:
						gTEK_changeflag|=(1<<1);
						break;
					default:
					return APP_FAIL;
				}
				PubSaveVar((char*)&gTEK_changeflag, dTekflag_off, dTekflag_len);
//				PDEBUG("gTEK_changeflag:%d",gTEK_changeflag);
			} else {
#if LANGUAGE==L_CHINESE
				PubMsgDlg(szTmpDispStr1, "�����޸�ʧ��", 1, 50 ) ;
#else
				PubMsgDlg(szTmpDispStr1, "Fail in changing PWD", 1, 50 ) ;
#endif
			}
			return nRet;
		}

	}
}

/**
* @fn OperLogon
* @brief ����Ա��½
* @return
* @li APP_SUCC
* @li APP_FAIL
*/
int operlog(int operlevel)
{
	STOPER_RECORD stOperRec;
	int nRet, nLen,nPasswdLen, nOperRecNum;
	char szOperPasswd[ADMINOPERPWDLEN+1];
	char opercode[OPERCODELEN+1];
	char szTmpDispStr1[32], szTmpDispStr2[32];

	memset(szTmpDispStr1,0,sizeof(szTmpDispStr1));
	memset(szTmpDispStr2,0,sizeof(szTmpDispStr2));
	switch (operlevel) {
	case MANAGEROPER:
#if LANGUAGE==L_CHINESE
		strcpy( szTmpDispStr1, "��Կ�ַ�ר��ϵͳ");
		strcpy( szTmpDispStr2, "������\n���ܲ���Ա����:");
#else
		strcpy( szTmpDispStr1, "Key Distribution");
		strcpy( szTmpDispStr2, "input manager's PWD:");
#endif
		break;
	case NORMALOPER:
		memset(opercode, 0, sizeof(opercode));
#if LANGUAGE==L_CHINESE
		strcpy( szTmpDispStr1, "��Կ�ַ�ר��ϵͳ");
		strcpy( szTmpDispStr2, "������\n�ַ�����Ա����:");
#else
		strcpy( szTmpDispStr1, "Key Distribution");
		strcpy( szTmpDispStr2, "input operator's PWD:");
#endif
		break;
	case ADMINOPER:
#if LANGUAGE==L_CHINESE
		strcpy( szTmpDispStr1, "ϵͳ����Ա����");
		strcpy( szTmpDispStr2, "����������:");
#else
		strcpy( szTmpDispStr1, "Key Distribution");
		strcpy( szTmpDispStr2, "input admin's PWD:");
#endif
		break;
	case KEK1MANAGEROPER:
#if LANGUAGE==L_CHINESE
		strcpy( szTmpDispStr1, "����Ա1����");
		strcpy( szTmpDispStr2, "�������������:");
#else
		strcpy( szTmpDispStr1, "Administor 1");
		strcpy( szTmpDispStr2, "input admin1's PWD:");
#endif
		break;
	case KEK2MANAGEROPER:
#if LANGUAGE==L_CHINESE
		strcpy( szTmpDispStr1, "����Ա2����");
		strcpy( szTmpDispStr2, "�������������:");
#else
		strcpy( szTmpDispStr1, "Administor 2");
		strcpy( szTmpDispStr2, "input admin2's PWD:");
#endif
		break;
	default:
#if LANGUAGE==L_CHINESE
		ProMsgDlg("����","û�иò���Ա",2,10,LANGUAGE);
#else
		ProMsgDlg("warning","unknown operator",2,10,LANGUAGE);
#endif
		return APP_FAIL;
	}
	nRet = FindOper( operlevel, &stOperRec, &nOperRecNum);
	if (nRet == APP_SUCC) {
		nPasswdLen = 8;//stOperRec.cOperPwdLen; ��������7~8���ȵ�����
	} else {
#if LANGUAGE==L_CHINESE
		ProMsgDlg("����","δ�ҵ��ò���Ա��Ϣ",2,10,LANGUAGE);
#else
		ProMsgDlg("warning","information not found",2,10,LANGUAGE);
#endif
		return APP_FAIL;
	}

	memset(szOperPasswd, 0, sizeof(szOperPasswd));
	if (PubInputDlg(szTmpDispStr1,szTmpDispStr2, szOperPasswd, &nLen, 7, nPasswdLen, 60, INPUT_MODE_PASSWD)!= APP_SUCC) {
		return APP_FAIL;
	}

	if (stOperRec.cOperPwdLen != nLen || memcmp(szOperPasswd, stOperRec.szPasswd, stOperRec.cOperPwdLen )) {
#if LANGUAGE==L_CHINESE
		ProMsgDlg("����","�������!",2,5,LANGUAGE);
#else
		ProMsgDlg("warning","bad PWD",2,5,LANGUAGE);
#endif
		return APP_FAIL;
	}
	return APP_SUCC;
}

