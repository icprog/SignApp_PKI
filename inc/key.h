/**
* @file oper.c
* @brief  ��Կ�ļ�����ģ��
* @version  1.0
* @author Ф����
* @date 2009-03-20
*/

#ifndef KEY_H
#define KEY_H

#include "apiinc.h"
#include "libapiinc.h"
#include "posdef.h"

#define KEY_FILE  "KEY.TXT"
#define KEYRECLEN (SHOPIDLEN + TERMINALIDLEN + KEYINFOLEN + CHKVALUELEN + KEKINDEX + 5)
#define TEMP_FILE "TEMP.TXT"
#define INDEXLEN  sizeof(INDEX_RECORD)

#define TDESTYPE '2'
#define DESTYPE '1'

#define SHOPIDLEN 15
#define TERMINALIDLEN 8
#define KEYINFOLEN 48
#define CHKVALUELEN 8
#define KEKINDEX 2
/*typedef struct
{
	char szGroupNo[4+1];
	char szKeyInfo[32+1];
	char szCheckValue[4+1];
	char szKEK[2+1];
	//char cStatus;
} STWATER_RECORD;*/

typedef struct
{
	char szShopId[SHOPIDLEN+1];
	char szTerminalId[TERMINALIDLEN+1];
	char szKeyInfo[KEYINFOLEN+1];
	char szCheckValue[CHKVALUELEN+1];
	char szKEK[KEKINDEX+1];
	char cDeleteFlag;		/*  '1'��ʾ��ɾ��*/
	char cType;
} STWATER_RECORD;

typedef struct
{
	char szShopId[SHOPIDLEN];
	char szTerminalId[TERMINALIDLEN];
	char szKeyInfo[KEYINFOLEN/2];
	char szCheckValue[CHKVALUELEN/2];
	char szKEK[KEKINDEX/2];
}STKEY_RECORD;

typedef struct
{
	char szShopId[SHOPIDLEN+1];
	char szTerminalId[TERMINALIDLEN+1];
	char cStatus;
	int nPosition;
}INDEX_RECORD;

/*��Կ��ϵ*/
enum sec_key_arch {
	KEY_ARCH_FIXED = 0x100,
	KEY_ARCH_MKSK,
	KEY_ARCH_DUKPT
};
#define SEC_KEY_TYPE_DUKPT	(0x10)

//int GetKeyGrpID(const char *pszTitle);
//int GetKeyData(const char *pszTitle, char *pszKey, int keylen);
//int GetKsn(const char *pszTitle, char *pszKsn);
//int KeyDataPack(int nGid, int nKeyArch, int nKeyType, const char *appname,const char *pszKey, int nKeyLen,const char *pszKsn, char *pszData);
int KeyDistribution(void);
//int download_key( char *data, int len);
int EchoError(char *s);
//void ShowTitle(const char *szTitle);

/*֤��·��*/
#define NL_KLD_RSA_KEY_SIZE	(256)	/*2048bit��rsa��Կ����256�ֽ�*/
#define NL_CA_PATH		"/etc/key/ca/"		/*CA֤���ļ�*/
#define NL_CA_CERT_FILE		"/etc/key/ca/Newland_Root_CA.crt"		/*CA֤���ļ�*/

#define NL_KLD_AUTH_KEY		"/etc/key/private/PED_AUTH_CERT.key"	/*AUTH˽Կ�ļ�*/
#define NL_KLD_AUTH_CERT_PATH		"/etc/key/certs/PED_AUTH_CERT.crt"		/*AUTH��֤��*/
#define NL_KLD_AUTH_CERT_NAME		"PED_AUTH_CERT.crt"		/*AUTH֤���ļ���*/

#define NL_KLD_ENC_KEY		"/etc/key/private/PED_ENC_CERT.key"	/*ENC˽Կ�ļ�*/
#define NL_KLD_ENC_CERT_PATH		"/etc/key/certs/PED_ENC_CERT.crt"		/*ENC��֤��*/
#define NL_KLD_ENC_CERT_NAME		"PED_ENC_CERT.crt"		/*ENC֤���ļ���*/


/*˫����֤ʹ�õ��Ĺ��ܺ���*/
//extern int xauth_is_done(void);
//extern int xauth_verify_cert(char *certfile);
//extern int xauth_cert_encrypt(char *certfile, int inlen, char *in, char *out);
//extern int xauth_private_encryption(char *keyfile, int inlen, char *in, char *out, int mode);
//extern int xauth_store_session_key(char *key, int len);
//extern int xauth_session_3des(char *in, int inlen, char *out, int do_encrypt);
//extern int xauth_data_3des(char *in, int inlen, char *out, int do_encrypt, char *key);
//extern int xauth_get_session_key(char *key);
//extern int xauth_abort(char *msg);

extern int CommInitConfig(void);
//extern int enter_x509_auth(void);	[>ʵ��˫����֤��������Э�顢����<]
//extern int get_app_list(list_t *plist);	[>ˢ��Ӧ���б�<]
//extern int set_key_owner_app(char *owner);	[>���ú�����װ��Կ������Ӧ������<]
//extern int choose_key_owner(void);	[>��������get_app_list()�Լ�set_key_owner_app()��ʵ����Կ����ѡ���Լ����ù���<]
//extern int set_kla_datetime(int soft_hard);

#endif

