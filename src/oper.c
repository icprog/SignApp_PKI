/**
* @file oper.c
* @brief 操作员处理模块
* @version  1.0
* @author 肖腾月
* @date 2009-03-20
*/
#include "oper.h"
#include "appinc.h" 

#define ADMINPWD		    "87654321"		/**< 系统管理员初始密码*/
#define MANAGERPWD		    "123456"			/**< 主管初始密码*/
#define KEK1MANAGERPWD		"88888888"			/**< KEK第一分量管理员初始密码*/
#define KEK2MANAGERPWD		"99999999"			/**< KEK第二分量管理员初始密码*/
#define NORMALOPERPWD	    "00000000"			/**< 普通操作员初始密码*/

#define MANAGERPWDLEN		    6				/**< 主管操作员密码长度*/
#define KEK1MANAGERPWDLEN		8				/**< KEK第一分量管理员密码长度*/
#define KEK2MANAGERPWDLEN		8				/**< KEK第二分量管理员密码长度*/
#define NORMALPWDLEN		    8				/**< 普通操作员密码长度*/
#define ADMINOPERPWDLEN	        8				/**< 系统管理员密码长度*/


/*外部函数声明*/
extern int ProMsgDlg(const char *pszTitle, const char *pszContent, int nBeep, int nTimeOut, int nMode);

extern int gTEK_changeflag;
/**
* @fn InitOper
* @brief 初始化操作员记录
*
*	初始化系统操作员数据，生成一个系统管理员，一个主管，KEK第一第二分量管理员
       五个普通操作员编号及相应的初始密码
* @return
* @li APP_SUCC
* @li APP_FAIL
*/
void InitOper(void)
{
	STOPER_RECORD stOperRec;
	STRECFILE stOperFile;

	/**
	*创建操作员文件，并进行初始化
	*/
	memset(&stOperFile, 0, sizeof(STRECFILE));
	strcpy( stOperFile.szFileName, FILE_OPER );
	stOperFile.cIsIndex = FILE_CREATEINDEX;						/**< 创建索引文件*/
	stOperFile.unMaxOneRecLen = sizeof(STOPER_RECORD);
	stOperFile.unIndex1Start =(unsigned int)( (char *)(stOperRec.szOperNo) - (char *)&stOperRec)+1;
	stOperFile.unIndex1Len =  OPERCODELEN;
	stOperFile.unIndex2Start =  (unsigned int)( (char *)(&stOperRec.cDeleFlag) - (char *)&stOperRec)+1;
	stOperFile.unIndex2Len = sizeof(stOperRec.cDeleFlag);
	ASSERT(PubCreatRecFile(&stOperFile));

	/**
	*初始化 系统管理员记录，编号99
	*/

	sprintf( stOperRec.szOperNo, "%0*d", OPERCODELEN, 99 );
	stOperRec.cOperRole = ADMINOPER;
	stOperRec.cOperPwdLen = ADMINOPERPWDLEN;
	strcpy(stOperRec.szPasswd, ADMINPWD );
	stOperRec.cDeleFlag = '+';
	PubAddRec(FILE_OPER, (const char *)&stOperRec );

	/**
	*初始化 主管操作员记录，编号00
	*/

	sprintf( stOperRec.szOperNo, "%0*d", OPERCODELEN, 0 );
	stOperRec.cOperRole = MANAGEROPER;
	stOperRec.cOperPwdLen = MANAGERPWDLEN;
	strcpy(stOperRec.szPasswd, MANAGERPWD );
	stOperRec.cDeleFlag = '+';
	PubAddRec(FILE_OPER, (const char *)&stOperRec );

	/**
	*初始化KEK第一分量管理员记录，编号91
	*/

	sprintf( stOperRec.szOperNo, "%0*d", OPERCODELEN, 91 );
	stOperRec.cOperRole = KEK1MANAGEROPER;
	stOperRec.cOperPwdLen = KEK1MANAGERPWDLEN;
	strcpy(stOperRec.szPasswd, KEK1MANAGERPWD );
	stOperRec.cDeleFlag = '+';
	PubAddRec(FILE_OPER, (const char *)&stOperRec );

	/**
	*初始化KEK第一分量管理员记录，编号92
	*/
	sprintf( stOperRec.szOperNo, "%0*d", OPERCODELEN, 92 );
	stOperRec.cOperRole = KEK2MANAGEROPER;
	stOperRec.cOperPwdLen = KEK2MANAGERPWDLEN;
	strcpy(stOperRec.szPasswd, KEK2MANAGERPWD );
	stOperRec.cDeleFlag = '+';
	PubAddRec(FILE_OPER, (const char *)&stOperRec );

	/**
	*初始化五个普通操作员记录,编号01-05
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
* @brief 根据提供的操作员的角色，得到操作员的信息。
* @param in nRole 操作员角色
* @param out STOPER_RECORD *pstOperRec 操作员记录信息
* @param out int *pnOperRecNum  操作员记录号
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
* @li		判断表中是否存在不同密钥ID但是相同值的密钥记录
* 			该函数用于允许覆盖安装的情况使用！
* @retval	1		存在该密钥
* @retval 	0		不存在该密钥
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
* @brief 根据提供的操作员的角色重置操作员的信息。
* @param in nRole 操作员角色
* @param out STOPER_RECORD *pstOperRec 操作员记录信息
* @param out int *pnOperRecNum  操作员记录号
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
			strcpy( szTmpDispStr1, "系统管理员改密" );
#else
			strcpy( szTmpDispStr1, "administrator");
#endif
			nPasswdLen = ADMINOPERPWDLEN;
			break;
		case KEK1MANAGEROPER:
#if LANGUAGE==L_CHINESE
			strcpy( szTmpDispStr1, "管理员1 改密" );
#else
			strcpy( szTmpDispStr1, "Admin1 Setting");
#endif
			nPasswdLen = KEK1MANAGERPWDLEN;
			break;
		case KEK2MANAGEROPER:
#if LANGUAGE==L_CHINESE
			strcpy( szTmpDispStr1, "管理员2 改密" );
#else
			strcpy( szTmpDispStr1, "Admin2 Setting");
#endif
			nPasswdLen = KEK2MANAGERPWDLEN;
			break;
		case NORMALOPER:
#if LANGUAGE==L_CHINESE
			strcpy( szTmpDispStr1, "密钥分发员改密" );
#else
			strcpy( szTmpDispStr1, "Operator Setting");
#endif
			nPasswdLen = NORMALPWDLEN;
			break;
		default:
			return APP_FAIL;
		}

#if LANGUAGE==L_CHINESE
		strcpy( szTmpDispStr2, "请输入密码:" );
#else
		strcpy( szTmpDispStr2, "input old PWD:" );
#endif
		/**
		 * 输入原密码并校验
		 */
		memset(szOperPasswd, 0, sizeof(szOperPasswd));
		nRet = PubInputDlg(szTmpDispStr1, szTmpDispStr2, szOperPasswd, &nlen, 7, nPasswdLen, 60, INPUT_MODE_PASSWD);
		if ( nRet != APP_SUCC ) {
			return nRet;
		}
		if ( stOperRec.cOperPwdLen != nlen || memcmp(szOperPasswd, stOperRec.szPasswd,  stOperRec.cOperPwdLen) ) {
#if LANGUAGE==L_CHINESE
			PubMsgDlg(szTmpDispStr1, "原密码不符", 1, 50 ) ;
#else
			PubMsgDlg(szTmpDispStr1, "old PWD is bad", 1, 50 ) ;
#endif
			continue;
		}

		memset(szOperPasswd, 0, sizeof(szOperPasswd));
#if LANGUAGE==L_CHINESE
		nRet = PubInputDlg(szTmpDispStr1, "请输入新密码:", szOperPasswd, &nlen, 7, nPasswdLen, 60, INPUT_MODE_PASSWD);
#else
		nRet = PubInputDlg(szTmpDispStr1, "input new PWD:", szOperPasswd, &nlen, 7, nPasswdLen, 60, INPUT_MODE_PASSWD);
#endif
		if ( nRet != APP_SUCC ) {
			return nRet;
		}
		memset(szPasswdStr, 0, sizeof(szPasswdStr));
#if LANGUAGE==L_CHINESE
		nRet = PubInputDlg(szTmpDispStr1, "再次输入:", szPasswdStr, &nlen, 7, nPasswdLen, 60, INPUT_MODE_PASSWD);
#else
		nRet = PubInputDlg(szTmpDispStr1, "input new PWD again:", szPasswdStr, &nlen, 7, nPasswdLen, 60, INPUT_MODE_PASSWD);
#endif
		if ( nRet != APP_SUCC ) {
			return nRet;
		}

		if (  memcmp(szOperPasswd, szPasswdStr, nPasswdLen) ) {
#if LANGUAGE==L_CHINESE
			PubMsgDlg(szTmpDispStr1, "两次密码输入不同", 1, 50 ) ;
#else
			PubMsgDlg(szTmpDispStr1, "difference between 2 new PWDs", 1, 50 ) ;
#endif
			continue;
		} 
		if(exist_other_value(szOperPasswd, nlen) ){
#if LANGUAGE==L_CHINESE
				PubMsgDlg(szTmpDispStr1, "已 存在相同的PSW值,请重新设置", 1, 50 ) ;
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
				PubMsgDlg(szTmpDispStr1, "密码修改成功", 1, 50 ) ;
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
				PubMsgDlg(szTmpDispStr1, "密码修改失败", 1, 50 ) ;
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
* @brief 操作员登陆
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
		strcpy( szTmpDispStr1, "密钥分发专用系统");
		strcpy( szTmpDispStr2, "请输入\n主管操作员密码:");
#else
		strcpy( szTmpDispStr1, "Key Distribution");
		strcpy( szTmpDispStr2, "input manager's PWD:");
#endif
		break;
	case NORMALOPER:
		memset(opercode, 0, sizeof(opercode));
#if LANGUAGE==L_CHINESE
		strcpy( szTmpDispStr1, "密钥分发专用系统");
		strcpy( szTmpDispStr2, "请输入\n分发操作员密码:");
#else
		strcpy( szTmpDispStr1, "Key Distribution");
		strcpy( szTmpDispStr2, "input operator's PWD:");
#endif
		break;
	case ADMINOPER:
#if LANGUAGE==L_CHINESE
		strcpy( szTmpDispStr1, "系统管理员设置");
		strcpy( szTmpDispStr2, "请输入密码:");
#else
		strcpy( szTmpDispStr1, "Key Distribution");
		strcpy( szTmpDispStr2, "input admin's PWD:");
#endif
		break;
	case KEK1MANAGEROPER:
#if LANGUAGE==L_CHINESE
		strcpy( szTmpDispStr1, "管理员1设置");
		strcpy( szTmpDispStr2, "请输入管理密码:");
#else
		strcpy( szTmpDispStr1, "Administor 1");
		strcpy( szTmpDispStr2, "input admin1's PWD:");
#endif
		break;
	case KEK2MANAGEROPER:
#if LANGUAGE==L_CHINESE
		strcpy( szTmpDispStr1, "管理员2设置");
		strcpy( szTmpDispStr2, "请输入管理密码:");
#else
		strcpy( szTmpDispStr1, "Administor 2");
		strcpy( szTmpDispStr2, "input admin2's PWD:");
#endif
		break;
	default:
#if LANGUAGE==L_CHINESE
		ProMsgDlg("警告","没有该操作员",2,10,LANGUAGE);
#else
		ProMsgDlg("warning","unknown operator",2,10,LANGUAGE);
#endif
		return APP_FAIL;
	}
	nRet = FindOper( operlevel, &stOperRec, &nOperRecNum);
	if (nRet == APP_SUCC) {
		nPasswdLen = 8;//stOperRec.cOperPwdLen; 允许输入7~8长度的密码
	} else {
#if LANGUAGE==L_CHINESE
		ProMsgDlg("警告","未找到该操作员信息",2,10,LANGUAGE);
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
		ProMsgDlg("警告","密码错误!",2,5,LANGUAGE);
#else
		ProMsgDlg("warning","bad PWD",2,5,LANGUAGE);
#endif
		return APP_FAIL;
	}
	return APP_SUCC;
}

