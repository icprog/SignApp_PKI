#ifndef _LTOOLS_H_
#define _LTOOLS_H_

#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "NDK.h"

#define SOH     1
#define STX     2
#define ETX     3
#define EOT     4
#define ENQ     5
#define ACK     6
#define DLE     0x10
#define NAK     0x15
#define ETB     0x17

#define FALSE 0
#define TRUE (!FALSE)

#define APP_SUCC		(0)   	/**<�ɹ�      */
#define APP_FAIL		(-1)    /**<ʧ��      */
#define APP_QUIT		(-2)    /**<�˳���ȡ��*/
#define APP_TIMEOUT 	(-3)    /**<��ʱ      */
#define APP_FUNCQUIT	(-4)    /**<�����ܼ�����*/

#define FILE_NOCREATEINDEX 0x00		/**<�����������ļ�*/
#define FILE_CREATEINDEX   0x01		/**<���������ļ�  */

#define MAX_ERR_BUF_LEN 	(128)		/**<��������Ϣ��󳤶� */
#define MAX_ERR_NUM		(1000)		/**<��������Ϣ������ */

typedef enum
{
	NO   = '0',
	YES  = '1'
}YESORNO;

enum EM_ADDCH_MODE
{
	ADDCH_MODE_BEFORE_STRING=0,			/**<���ַ���ǰ����ַ�*/
	ADDCH_MODE_AFTER_STRING,			/**<���ַ���������ַ�*/
	ADDCH_MODE_BEFORE_AFTER_STRING		/**<���ַ���ǰ����ַ�*/
};

enum EM_HARDWARE_SUPPORT
{
	HARDWARE_SUPPORT_WIRELESS=0,		/**<����ģ��*/
	HARDWARE_SUPPORT_RADIO_FREQUENCY,	/**<��Ƶģ��*/
	HARDWARE_SUPPORT_MAGCARD,			/**<�ſ�ģ��*/
	HARDWARE_SUPPORT_SCANNER,			/**<ɨ��ͷģ��*/
	HARDWARE_SUPPORT_PINPAD,			/**<�Ƿ�֧������������*/
	HARDWARE_SUPPORT_COMM_NUM,			/**<���ڸ���*/
	HARDWARE_SUPPORT_USB,				/**<�Ƿ�֧��USB*/
	HARDWARE_SUPPORT_MODEM,				/**<MODEMģ��*/
	HARDWARE_SUPPORT_WIFI,				/**<wifiģ��*/
	HARDWARE_SUPPORT_ETH,				/**<�Ƿ�֧����̫��*/
	HARDWARE_SUPPORT_PRINTER,			/**<��ӡģ��*/
	HARDWARE_SUPPORT_TOUCH_SCREEN,		/**<�Ƿ�֧�ִ���*/
	HARDWARE_SUPPORT_LED_LIGHT			/**<�Ƿ�����ƵLED��*/
};

enum EM_HARDWARE_GET
{
	HARDWARE_GET_BIOS_VER=2,		/**<ȡbios�汾��Ϣ */
	HARDWARE_GET_POS_USN,			/**<ȡ�������к� */
	HARDWARE_GET_POS_PSN,			/**<ȡ���������� */
	HARDWARE_GET_BOARD_VER,			/**<ȡ����� */
	HARDWARE_GET_CREDITCARD_COUNT, /**<ȡposˢ������ */
	HARDWARE_GET_PRN_LEN,			/**<ȡpos��ӡ�ܳ��� */
	HARDWARE_GET_POS_RUNTIME,		/**<ȡpos����������ʱ�� */
	HARDWARE_GET_KEY_COUNT			/**<ȡpos���������� */
};

typedef struct tagRecFile
{
	unsigned int unMaxOneRecLen;	/**<���ĵ�����¼���� */  
	unsigned int unIndex1Start;		/**<�����ֶ�1����ʼλ��*/
	unsigned int unIndex1Len;		/**<�����ֶ�1�ĳ���    */
	unsigned int unIndex2Start; 	/**<�����ֶ�2����ʼλ��*/
	unsigned int unIndex2Len;		/**<�����ֶ�2�ĳ���    */
	char cIsIndex;					/**<�Ƿ���Ҫ���������ļ���0x00��������0x01����*/
	char szFileName[128];			/**<��¼�ļ���,��Ч�ļ�¼�ļ�������Ϊ128*/
	char s[2];
}STRECFILE;


/**
* @brief 2����󲻳���12λ���޷������ִ������λ��ӣ���ӽ�����ܳ���12λ
* @param [in] pszDigStr1 ���ִ�1
* @param [in] pszDigStr2 ���ִ�2
* @param [out] pszResult ��Ӻ͵����ִ�
* @param [out] pnOutLen  ��Ӻ͵�λ��
* @return 
* @li APP_FAIL ʧ��
* @li APP_APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubAddDigitStr (const char* pszDigStr1, const char* pszDigStr2, char* pszResult, int* pnResultLen );

/**
* @brief ��6λ���ִ�pcStrNum����1��Ż�ԭֵ
* @param [in] pcStrNum  ��Ҫ�����ӵ����ִ�
* @param [out] pcStrNum ���Ӻ�Ľ����
* @return 
* @li APP_FAIL ʧ��
* @li APP_APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubIncNum (char* pcStrNum );

/**
* @brief 	����ASC���ִ���ӡ�
* @param [in] pszAsc1	����ASC�ַ���
* @param [in] pszAsc2	����ASC�ַ���
* @param [out] pszResult	��ӵĽ��
* @return 
* @li ��
*/
void PubAscAddAsc(uchar *pszAsc1, uchar *pszAsc2, uchar *pszSum);

/**
* @brief ����ASC�ַ������
* @param [in] pszAsc1	����ASC�ַ������������������
* @param [in] pszAsc2	������ASC�ַ������������������
* @param [out] pszResult	����Ľ��
* @return 
* @li ��
*/
void PubAscSubAsc(uchar *pszAsc1, uchar *pszAsc2, uchar *pszResult);

/**
* @brief ����ASC�ַ������
* @param [in] pszAsc1	����ASC�ַ���
* @param [in] pszAsc2	����ASC�ַ���
* @param [out] pszProduct	��˵Ľ��
* @return 
* @li ��
*/
void PubAscMulAsc(uchar *pszAsc1, uchar *pszAsc2, uchar *pszProduct );


/**
* @brief �Ѵ�С����Ľ���ַ���תΪ����С����Ľ���ַ���
* @param [in] pszSource    ��ת���Ľ���ַ���
* @param [in] pnTargetLen  Ŀ�껺�����Ĵ�С
* @param [out] pszTarget   ת������ַ���
* @param [out] pnTargetLen ת������ַ�������
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubFmtAmtStr (const char* pszSource, char* pszTarget, int* pnTargetLen );

/**
* @brief ��AscII����ַ���ת����ѹ����HEX��ʽ����ż�����ȵ��ַ������ݶ��뷽ʽ����ȡ��0���Ҳ�F��ʽ
* @param [in] pszAsciiBuf ��ת����ASCII�ַ���
* @param [in] nLen        �������ݳ���(ASCII�ַ����ĳ���)
* @param [in] cType       ���뷽ʽ  0�������  1���Ҷ���
* @param [out] pszBcdBuf  ת�������HEX����
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubAscToHex (const unsigned char* pszAsciiBuf, int nLen, char cType, unsigned char* pszBcdBuf);

/**
* @brief ��HEX������ת����AscII���ַ���
* @param [in] pszBcdBuf    ��ת����Hex����
* @param [in] nLen         ת�����ݳ���(ASCII�ַ����ĳ���)
* @param [in] cType        ���뷽ʽ  1�������  0���Ҷ���
* @param [out] pszAsciiBuf ת�������AscII������
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubHexToAsc (const unsigned char* pszBcdBuf, int nLen, char cType, unsigned char* pszAsciiBuf);

/**
* @brief ����ת��Ϊ4�ֽ��ַ�������λ��ǰ��
* @param [in] nNum    ��Ҫת����������
* @param [out] pszBuf ת��������ַ���
* @return 
* @li ��
* @date 2012-06-19
*/
void PubIntToC4 (unsigned char* pszBuf, unsigned int nNum );

/**
* @brief ����ת��Ϊ2�ֽ��ַ�������λ��ǰ��
* @param [in] nNum    ��Ҫת����������
* @param [out] pszBuf ת��������ַ���
* @return 
* @li ��
* @date 2012-06-19
*/
void PubIntToC2 (unsigned char* pszBuf, unsigned int nNum );

/**
* @brief 4�ֽ��ַ���ת��Ϊ���ͣ���λ��ǰ��
* @param [in] pszBuf ��Ҫת�����ַ���
* @param [out] nNum  ת�������������
* @return 
* @li ��
* @date 2012-06-19
*/
void PubC4ToInt (unsigned int* nNum, unsigned char * pszBuf );

/**
* @brief 2�ֽ��ַ���ת��Ϊ���ͣ���λ��ǰ��
* @param [in] pszBuf ��Ҫת�����ַ�����pszBuf����Ҫ>=2
* @param [out] nNum  ת�������������
* @return 
* @li ��
* @date 2012-06-19
*/
void PubC2ToInt(unsigned int *nNum, unsigned char *pszBuf);

/**
* @brief ����(0-99)ת��Ϊһ�ֽ�BCD
* @param [in] nNum ��Ҫת����������(0-99)
* @param [out] ch  ת�������һ��BCD�ַ�
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubByteToBcd(int nNum, char *ch);

/**
* @brief һ�ֽ�BCDת��Ϊ����(0-99)
* @param [in] ch     ��Ҫת����BCD�ַ�
* @param [out] pnNum ת�����������ֵ(0-99)
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubBcdToByte(char ch, int *pnNum);

/**
* @brief ����(0-9999)ת��Ϊ���ֽ�BCD
* @param [in] nNum      ��Ҫת����������(0-9999)
* @param [in] pnBcdLen  ����������Ĵ�С   
* @param [out] psBcd    ת����������ֽ�BCD
* @param [out] pnBcdLen ת�����BCD���ȣ�����ɹ���ֵ���̶�����ֵΪ2
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubIntToBcd(char *psBcd, int *pnBcdLen, int nNum);

/**
* @brief ���ֽ�BCDת��Ϊ����(0-9999)
* @param [in] psBcd   ��Ҫת�������ֽ�BCD������Ӧ����2
* @param [out] nNum   ת���������(0-9999)
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubBcdToInt(const char * psBcd, int *nNum);

/**
* @brief ����LRC
* @param [in] psBuf  ��Ҫ����LRC���ַ���
* @param [in] nLen   ��Ҫ����LRC���ַ����ĳ���
* @param [out] chLRC ����ó���LRC
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubCalcLRC(const char *psBuf, int nLen, char *chLRC);

/**
* @brief �ַ���ȥ��ո�
* @param [in] pszSrc  ����ַ����Ļ�����
* @param [out] pszSrc ȥ����ո����ַ���
* @return 
* @li ��
* @date 2012-06-19
*/
void PubLeftTrim(char *pszSrc);

/**
* @brief �ַ���ȥ�ҿո�
* @param [in] pszSrc  ����ַ����Ļ�����
* @param [out] pszSrc ȥ���ҿո����ַ���
* @return 
* @li �
* @date 2012-06-19
*/
void PubRightTrim(char *pszSrc);

/**
* @brief �ַ���ȥ�ҿո�
* @param [in] pszSrc  ����ַ����Ļ�����
* @param [out] pszSrc ȥ�����ҿո����ַ���
* @return 
* @li ��
* @date 2012-06-19
*/
void PubAllTrim(char *pszSrc);

/**
* @brief ��һ�ַ�����ɾ��ĳһ�ַ�
* @param [in] pszString		��������ַ���
* @param [in] ucSymbol	��Ҫɾ�����ַ�
* @param [out] pszString	ɾ�������ַ�ucSymbol����ַ���
* @return
* li ת��������
*/
void PubDelSymbolFromStr(uchar *pszString, uchar ucSymbol);

/**
* @brief ��һ�ַ��������ĳһ�ַ�ʹ֮����ΪnLen
* @param [in] pszString  ����ַ����Ļ�����
* @param [in] nLen       �����ַ����ַ����ĳ���
* @param [in] ch         ��Ҫ������ַ�
* @param [in] nOption    ��������--EM_ADDCH_MODE
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubAddSymbolToStr(char *pszString, int nLen, char ch, int nOption);

/**
* @brief ɾ���ַ�������������ض��ַ�
* @param [in] pszStringInOut 	��ת�����ַ���
* @param [in] ucRemoveChar	��ɾ���ַ�
* @param [out] pszString		ת������ַ���
* @return
* li ��
*/
void PubLeftTrimChar(uchar *pszSrc, uchar ucRemoveChar);

/**
* @brief ɾ���ַ����ұ��������ض��ַ�
* @param [in] pszStringInOut	��ת�����ַ���
* @param [in] ucRemoveChar	��ɾ���ַ�
* @param [out] pszString		ת������ַ���
* @return
* li ��
*/
void PubRightTrimChar(uchar *pszSrc, uchar ucRemoveChar);

/**
* @brief ����һ�ִ��Ƿ�Ϊ�����ִ�
* @param [in] pszString    ��Ҫ�жϵ��ַ���
* @return 
* @li APP_FAIL ��
* @li APP_SUCC ��
* @date 2012-06-19
*/
int PubIsDigitStr(const char *pszString);

/**
* @brief �жϸ���һ�ַ��ǲ��������ַ�
* @param [in] ch ��Ҫ�жϵ��ַ�
* @return 
* @li APP_FAIL ��
* @li APP_SUCC ��
* @date 2012-06-19
*/
int PubIsDigitChar(char ch);

/**
* @brief �ж��ṩ���ַ����ǲ��ǺϷ������ڸ�ʽ��
* @param [in] pDate ���ڸ�ʽ�ַ���  ��ʽΪ YYYYMMDD
* @return 
* @li APP_FAIL �Ƿ�
* @li APP_SUCC �Ϸ�
* @date 2012-06-19
*/
int PubIsValidDate(const char *pDate);

/**
* @brief	ת�����ִ�������ʽ����HKD$****.**, RMB****.**
* @param [in] pszPrefix 	pszPrefix  ǰ���ǰ׺���硰HKD 200.00���еġ�HKD��
* @param [in] pszIn			��Ҫת���Ĵ����ִ�,���˵�ǰ���'0'
* @param [in] ucRadPt		С�����Ľ��λ��������С��4
* @param [out] pszOut		��ʽ����Ľ�
* @return
* li ת��������
*/
void PubConvAmount(uchar *pszPrefix, uchar *pszIn, uchar ucRadPt, uchar *pszOut);

/**
* @brief ȡ�õ�ǰ����ʱ��
* @param [out] pDatetime ��ŵ�ǰ����ʱ�����ʽΪYYYYMMDDHHMMSS�����ȱ���>14
* @return 
* @li ��
* @date 2012-06-19
*/
void PubGetCurrentDatetime(char *pDatetime);

/**
* @brief ����POS����ʱ��
* @param in pszDate ����
* @param in pszDateFormat ��ʽ����
* @param in pszTime ʱ��
* @return 
* @li APP_SUCC �ɹ�
* @li APP_FAIL ʧ��
*/
int PubSetPosDateTime(const char *pszDate, const char *pszDateFormat, const char *pszTime);

/**
* @brief �ҳ�ĳ��ĳ�µ��������
* @param [in] nYear   ���
* @param [in] nMon    �·�
* @param [out] pnDays ����ݸ��¶�Ӧ���������
* @return 
* @li APP_FAIL �Ƿ����������
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubMonthDays(int nYear, int nMon, int *pnDays);

/**
* @brief �ж�ĳ���Ƿ�����
* @param [in] nYear ���
* @return 
* @li APP_FAIL ������
* @li APP_SUCC ����
* @date 2012-06-19
*/
int PubIsLeapYear(int nYear);

/**
* @brief ��ȡ��ʱ��ʱ�����
* @param [in]  unMsTime  ��ʱʱ�� (��λ:ms)
* @return 
* @li ����ʱ�����
* @author ���
* @date 2012-10-24
*/
uint PubGetOverTimer(uint unMsTime);

/**
* @brief �ж��Ƿ񵽴ﳬʱʱ��
* @param [in]  unOverTime  ֮ǰ��ȡ�ĳ�ʱʱ����� (��λ:ms)
* @return 
* @li APP_APP_SUCC �ѳ�ʱ
* @li APP_APP_FAIL δ��ʱ
* @author ���
* @date 2012-10-24
*/
int PubTimerIsOver(uint unOverTime);

/**
* @brief ȡ���߿�汾��
* @param [out] pszVer ��Ű汾�ţ��ַ�������>12
* @return 
* @li ��
* @date 2012-06-19
*/
void PubGetToolsVer(char *pszVer);

/**
* @brief ���������ļ�
* @param [in] pstRecFile   ����
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubCreatRecFile(const STRECFILE *pstRecFile);

/**
* @brief ���ļ������ļ�
* @param [in] pszFileName   ��ˮ�ļ���
* @param [in] pszMode       �򿪷�ʽ
* @param [out] pnFileHandle �򿪵��ļ����
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubOpenFile (const char *pszFileName, const char *pszMode,int *pnFileHandle);

/**
* @brief �ر��ļ����
* @param [in] pnFileHandle Ҫ�رյ��ļ����
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubCloseFile (int *pnFileHandle);

/**
* @brief ɾ����ˮ�ļ�
* @param [in] pszFileName ��ˮ�ļ���
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubDeReclFile (const char *pszFileName);

/**
* @brief ���ļ������ļ�����ȡ�ļ���¼����
* @param [in] pszFileName ��ˮ�ļ���
* @param [out] pnRecSum   ָ���¼������ָ��
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubGetRecSum (const char *pszFileName, int *pnRecSum);

/**
* @brief ������ˮ��¼�����ڴ�����¼��ָ������Ҫ���������ļ��Ļ���Ӧ����������¼
* @param [in] pszFileName ��ˮ�ļ���
* @param [in] pszRec �������ˮ��¼
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubAddRec (const char *pszFileName, const char *pszRec);

/**
* @brief ����¼�Ŷ���ˮ��¼
* @param [in] nFileHandle �򿪵��ļ����
* @param [in] nRecNo      Ҫ�ҵļ�¼��
* @param [out] psRec      ��¼ָ��
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubReadRec (const int nFileHandle, const int nRecNo, char *psRec);

/**
* @brief ���¼�¼����ָ���ļ�¼λ����дָ���ļ�¼��ͬʱ���ڴ�����¼��ָ������Ҫ���������ļ��Ļ���Ӧ����������¼
* @param [in] pszFileName ��¼�ļ�����
* @param [in] nRecNo      Ҫ�޸ĵļ�¼��
* @param [in] psRec       ��¼ָ��
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubUpdateRec (const char *pszFileName, const int nRecNo, const char *psRec);

/**
* @brief ���¼�¼����ָ���ļ�¼λ����дָ���ļ�¼��ͬʱ���ڴ�����¼��ָ������Ҫ���������ļ��Ļ���Ӧ����������¼
* @param [in] nFileHandle ��¼�ļ����
* @param [in] nRecNo      Ҫ�޸ĵļ�¼��
* @param [in] psRec       ��¼ָ��
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubUpdateRecByHandle (int nFileHandle, const int nRecNo, const char *psRec);

/**
* @brief ����¼�Ŷ�ȡ������¼
* @param [in] pszFileName ��¼�ļ�����
* @param [in] nRecNo      Ҫ��ȡ�ļ�¼��
* @param [out] psRec      ��¼ָ��
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubReadOneRec(const char *pszFileName, const int nRecNo, char *psRec);

/**
* @brief ���������Ҽ�¼�����������ֶ�1/�����ֶ�2��ָ���ļ�¼�ſ�ʼ���Ҽ�¼����ͬʱָ�������ֶ�1/�����ֶ�2����Ҫͬʱ���������������ļ�¼�������ָ��ʱ��NULL,���������������ļ�¼�����ظ�������������һ����¼
* @param [in] pszFileName ��¼�ļ�����
* @param [in] psIndexStr1 �����ֶ�1
* @param [in] psIndexStr2 �����ֶ�2
* @param [in] nBeginRecNo ָ���Ŀ�ʼ��¼��
* @param [out] psRec ��¼ָ��
* @param [out] pnRecNo ���������ļ�¼��
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubFindRec(const char *pszFileName, const char *psIndexStr1, const char *psIndexStr2,const int nBeginRecNo, char *psRec, int *pnRecNo);

/**
* @brief ������ɾ����¼�����������ֶ�1/�����ֶ�2��ָ���ļ�¼�ſ�ʼ���Ҽ�¼����ͬʱָ�������ֶ�1/�����ֶ�2����ɾ��ͬʱ���������������ļ�¼����ָ��ʱ��NULL,���������������ļ�¼�����ظ��������ɾ����һ����¼
* @param [in] pszFileName ��¼�ļ�����
* @param [in] psIndexStr1 �����ֶ�1
* @param [in] psIndexStr2 �����ֶ�2
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubDelRec(const char *pszFileName, const char *psIndexStr1,  const char *psIndexStr2);

/**
* @brief ������ļ�¼��������־�Ĵ���
* @param [in] nErrorCode     ����ֵ
* @param [in] pszLogFileName Log�ļ���,ΪNULL����¼�ļ�
* @param [in] pszMoudleName  ģ����
* @param [in] nLine          ������������ʹ��__LINE__
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubErrLog (const int nErrorCode, const char *pszLogFileName, char *pszMoudleName, int nLine );

/**
* @brief �õ�ini�ļ���ָ���Ķκ���ָ�����ַ���
* @param [in] nHandle     INI�ļ����
* @param [in] psSeg       ��ָ��
* @param [in] psItem      ��ָ��
* @param [in] nMaxStrLen  ������������ַ�������
* @param [out] pcValueStr �õ����ַ���ֵָ��
* @param [out] pnValueLen �õ����ַ�������
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubGetINIItemStr (const int nHandle, const char *psSeg, const char *psItem, const int nMaxStrLen, char *psValueStr, int *pnValueLen);

/**
* @brief �õ�ini�ļ���ָ���Ķκ���ָ����ֵ
* @param [in] nHandle  INI�ļ����
* @param [in] psSeg    ��ָ��
* @param [in] psItem   ��ָ��
* @param [out] pnValue �õ���ֵָ��
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubGetINIItemInt (const int nHandle,const char *psSeg, const char *psItem, int *pnValue);

/**
* @brief ��ָ����IDѰ��ָ������Ŀֵ����ָ�������ļ�����Ч���ݿ�ʼλ��
* @param [in] pnHandle      �����ļ����
* @param [in] nPosition     �����ļ���Ч���ݿ�ʼλ��
* @param [in] psID          Ҫ�ҵ�ID���ַ���ָ��
* @param [out] psParamValue �ҵ���ID��ֵָ��
* @param [out] pnParamLen   �ҵ���ID��ֵ����ָ��
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubFindParam (const int pnHandle, const int nPosition, const char *psID, char *psParamValue, int *pnParamLen);

/**
* @brief ɾ��ָ���Ĳ����ļ�������Ŀǰ����tmsԶ�������е��ض���ʽ�Ĳ����ļ�������INI�ļ�
* @param [in] pszFileName �����ļ���
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @date 2012-06-19
*/
int PubDelFile (const char *pszFileName);

/**
* @brief ��ȡ�ַ����ַ����е�λ��
* @param [in] pszData     ---�ַ���
* @param [in] cSubChar    ---�ַ�
* @return 
* @li APP_FAIL  ---������
* @li >=0   ---���ַ�����λ��ֵ
* @author ���
* @date 2012-7-23
*/
int PubPosChar(const char *pszData,char cSubChar);

/**
* @brief ��ȡ���ַ������ַ����е�λ��
* @param [in] pszData     ---�ַ���
* @param [in] pszSub      ---���ַ���
* @return 
* @li APP_FAIL  ---������
* @li >=0   ---���ַ�����λ��ֵ
* @author ���
* @date 2012-7-23
*/
int PubPosStr(const char *pszData,const char *pszSub);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef BOOL
typedef unsigned char BOOL;
#endif

#define MAX_FIELD_LEN 1024		/**<ÿ�������󳤶�*/
#define MAX_MSG_LEN 4096		/**<������󳤶� */

typedef enum 
{	/**<����뷽ʽ */
    ALIGN_TYPE_LEFT   = 0,
    ALIGN_TYPE_RIGHT  = 1
}EM_ALIGN_TYPE;

typedef enum 
{	/**<�������� */
    LENGTH_TYPE_FIX    = 0,
    LENGTH_TYPE_LLVAR  = 1,
    LENGTH_TYPE_LLLVAR = 2
} EM_LENGTH_TYPE;

typedef struct STISO_FIELD STISO_FIELD;
typedef struct STISO_FIELD_DEF STISO_FIELD_DEF;

/**
* @brief ��8583����д���������ش��������ݺͳ���
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pfieldbuf		��Ҫ�����8583������ָ��
* @param [in] fieldlen		��Ҫ�����8583�����ݳ���
* @param [out] poutdata		���ڽ��ռ��������ݵĻ�����
* @return 
* @li	���������ݳ���
*/
typedef int (*FIELD_PACKAGER_PACK) (STISO_FIELD_DEF *pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief ����������������ݽ����8583����
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pindata		���и����ĵ����ݻ�����
* @param [out] pfieldbuf	������8583�����ݻ�����
* @param [out] pfieldlen	���������ݳ���
* @return 
* @li	���ʱ��pindata��ʹ�õ����ݳ���
*/
typedef int (*FIELD_PACKAGER_UNPACK) (STISO_FIELD_DEF *pthis, unsigned char *pfieldbuf, int *pfieldlen, unsigned char *pindata);

/**
* @brief ����ISO������ͼ���8583�����еĳ����ֽ�
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] len			�����ݵĳ���
* @param [out] poutdata		���ڽ��ռ��������ݵĻ����� 
* @param [out] pcount		�����ֽ���������Ϊ0��LLVAR��Ϊ1��LLLVAR��Ϊ2��
* @return 
* @li	��
*/
typedef void (*FIELD_LENGTH_SET) (STISO_FIELD_DEF *pthis, int len, unsigned char *poutdata, int *pcount);

/**
* @brief ����ISO������ͺ�8583�����еĳ����ֽڣ����㱨������ĳ���
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pindata		�������ĵ�����ָ��
* @param [out] plen			���ڽ��ռ����ĳ���
* @param [out] pcount		�����ֽ���������Ϊ0��LLVAR��Ϊ1��LLLVAR��Ϊ2��
* @return 
* @li	��
*/
typedef void (*FIELD_LENGTH_GET) (STISO_FIELD_DEF *pthis, unsigned char *pindata, int *plen, int *pcount);

struct STISO_FIELD_LENGTH_CALC
{	/**< ISO 8583 �����򳤶ȼ��㺯���ṹ */
    FIELD_LENGTH_SET	pSet;		/**< ���ó���ʱ���õĺ��� */
    FIELD_LENGTH_GET	pGet;		/**< ȡ������ʱ���õĺ��� */
}; 

struct STISO_FIELD
{	/**< ISO 8583 ������ṹ */
    int    nLen;
    int    nOff;					/**< ָ��iso->databuf��������ƫ�ƣ������в����������͵ļ����ֽ� */
};

struct STISO_FIELD_DEF
{	/**< ISO 8583 �������� */
    int                     nLen;			/**< ��������󳤶� */
    EM_LENGTH_TYPE		    lentype;		/**< �����򳤶�����: 1--LLVAR�� 2--LLLVAR�� */
    EM_ALIGN_TYPE           align;			/**< �������� */
    char                    cPadchar;		/**< �����ַ� */	
    FIELD_PACKAGER_PACK		pPack;			/**< �������ָ�� */
    FIELD_PACKAGER_UNPACK	pUnpack;		/**< �������ָ�� */
};  


typedef struct STISODataStru
{	/**< ISO 8583 ���Ľṹ���� */
    STISO_FIELD		fld[256];
    char			sBitmap[256];
    unsigned char 	szDatabuf[MAX_MSG_LEN + MAX_FIELD_LEN];		/**< ����һ����ĳ��ȣ���ֹ��� */
    int        		nUsed;
} STISODataStru;

/**
* @brief ����ISO������ͼ���8583�����еĳ����ֽ�(ASC��ʽ)��ASC����ʽ���糤��104������ʾΪ 0x31, 0x30, 0x34,��3���ֽ�, �����9����ʾΪ0x30, 0x39�����ֽ�
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] nLen			�����ݵĳ���
* @param [out] poutdata		���ڽ��ռ��������ݵĻ�����
* @param [out] pcount		�����ֽ���������Ϊ0��LLVAR��Ϊ1��LLLVAR��Ϊ2��
* @return 
* @li ��
*/
void PubFLALengthSet(STISO_FIELD_DEF *pthis, int len, unsigned char *poutdata, int *pcount);

/**
* @brief ����ISO������ͺ�8583�����еĳ����ֽڣ����㱨������ĳ���(ASC��ʽ)��ASC����ʽ���糤��104������ʾΪ 0x31, 0x30, 0x34,��3���ֽ�, �����9����ʾΪ0x30, 0x39�����ֽ�
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pindata		�������ĵ�����ָ��
* @param [out] plen			���ڽ��ռ����ĳ���
* @param [out] pcount		�����ֽ���������Ϊ0��LLVAR��Ϊ1��LLLVAR��Ϊ2��
* @return 
* @li ��
*/
void PubFLALengthGet(STISO_FIELD_DEF *pthis, unsigned char *pindata, int *plen, int *pcount);

/**
* @brief ����ISO������ͼ���8583�����еĳ����ֽ�(BCD��ʽ)��BCD����ʽ���糤��104������ʾΪ 0x01, 0x04,��2���ֽ�, �����9����ʾΪ0x09,��1���ֽ�
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] nLen			�����ݵĳ���
* @param [out] poutdata		���ڽ��ռ��������ݵĻ�����
* @param [out] pcount		�����ֽ���������Ϊ0��LLVAR��Ϊ1��LLLVAR��Ϊ2��
* @return 
* @li ��
*/
void PubFLBLengthSet(STISO_FIELD_DEF *pthis, int len, unsigned char *poutdata, int *pcount);

/**
* @brief ����ISO������ͺ�8583�����еĳ����ֽڣ����㱨������ĳ���(BCD��ʽ)��BCD����ʽ���糤��104������ʾΪ 0x01, 0x04,��2���ֽ�, �����9����ʾΪ0x09,��1���ֽ�
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pindata		�������ĵ�����ָ��
* @param [out] plen			���ڽ��ռ����ĳ���
* @param [out] pcount		�����ֽ���������Ϊ0��LLVAR��Ϊ1��LLLVAR��Ϊ2��
* @return 
* @li ��
*/
void PubFLBLengthGet(STISO_FIELD_DEF *pthis, unsigned char *pindata, int *plen, int *pcount);

/**
* @brief ����ISO������ͼ���8583�����еĳ����ֽ�(HEX��ʽ)��HEX����ʽ���糤��104������ʾΪ 0x00, 0x68,��2���ֽ�, �����9����ʾΪ0x09,��1���ֽ�
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] nLen			�����ݵĳ���
* @param [out] poutdata		���ڽ��ռ��������ݵĻ�����
* @param [out] pcount		�����ֽ���������Ϊ0��LLVAR��Ϊ1��LLLVAR��Ϊ2��
* @return 
* @li ��
*/
void PubFLHLengthSet(STISO_FIELD_DEF *pthis, int len, unsigned char *poutdata, int *pcount);

/**
* @brief ����ISO������ͺ�8583�����еĳ����ֽڣ����㱨������ĳ���(HEX��ʽ)��HEX����ʽ���糤��104������ʾΪ 0x00, 0x68,��2���ֽ�, �����9����ʾΪ0x09,��1���ֽ�
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pindata		�������ĵ�����ָ��
* @param [out] plen			���ڽ��ռ����ĳ���
* @param [out] pcount		�����ֽ���������Ϊ0��LLVAR��Ϊ1��LLLVAR��Ϊ2��
* @return 
* @li ��
*/
void PubFLHLengthGet(STISO_FIELD_DEF *pthis, unsigned char *pindata, int *plen, int *pcount);

/**
* @brief Ϊһ��ISO������ݽ��д����MSG_ID��ASC����ʽ����
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pfieldbuf		��Ҫ�����8583������ָ��
* @param [in] nFieldlen		��Ҫ�����8583�����ݳ���
* @param [out] poutdata		���ڽ��ռ��������ݵĻ�����
* @return 
* @li ���������ݳ���
*/
int PubFPAMsgIDPack(STISO_FIELD_DEF * pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief Ϊһ��ISO������ݽ��н����MSG_ID��ASC����ʽ��
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pindata		���и����ĵ����ݻ�����
* @param [out] pfieldbuf	������8583�����ݻ�����
* @param [out] pfieldlen	���������ݳ���
* @return 
* @li ���ʱ��pindata��ʹ�õ����ݳ���
*/
int PubFPAMsgIDUnpack(STISO_FIELD_DEF * pthis, unsigned char *pfieldbuf, int  *pfieldlen, unsigned char *pindata);

/**
* @brief Ϊһ��ISO������ݽ��д����MSG_ID��BCD����ʽ��
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pfieldbuf		��Ҫ�����8583������ָ��
* @param [in] nFieldlen		��Ҫ�����8583�����ݳ���
* @param [out] poutdata		���ڽ��ռ��������ݵĻ�����
* @return 
* @li ���������ݳ���
*/
int PubFPBMsgIDpack(STISO_FIELD_DEF * pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief Ϊһ��ISO������ݽ��н����MSG_ID��BCD����ʽ��
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pindata		���и����ĵ����ݻ�����
* @param [out] pfieldbuf		������8583�����ݻ�����
* @param [out] pfieldlen		���������ݳ���
* @return 
* @li ���ʱ��pindata��ʹ�õ����ݳ���
*/
int PubFPBMsgIDUnpack(STISO_FIELD_DEF * pthis, unsigned char *pfieldbuf, int *pfieldlen, unsigned char *pindata);

/**
* @brief Ϊһ��ISO������ݽ��д����BITMAPλͼ��BCD����ʽ��
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pfieldbuf		��Ҫ�����8583������ָ��
* @param [in] nFieldlen		��Ҫ�����8583�����ݳ���
* @param [out] poutdata		���ڽ��ռ��������ݵĻ�����
* @return 
* @li ���������ݳ���
*/
int PubFPABitmapPack(STISO_FIELD_DEF * pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief Ϊһ��ISO������ݽ��н����BITMAPλͼ��BCD����ʽ��
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pindata		���и����ĵ����ݻ�����
* @param [out] pfieldbuf	������8583�����ݻ�����
* @param [out] pfieldlen	���������ݳ���
* @return 
* @li ���ʱ��pindata��ʹ�õ����ݳ���
*/
int PubFPABitmapUnPack(STISO_FIELD_DEF * pthis, unsigned char *pfieldbuf, int *pfieldlen, unsigned char *pindata);

/**
* @brief Ϊһ��ISO������ݽ��д����BITMAPλͼ��ASC����ʽ��
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pfieldbuf		��Ҫ�����8583������ָ��
* @param [in] nFieldlen		��Ҫ�����8583�����ݳ���
* @param [out] poutdata		���ڽ��ռ��������ݵĻ�����
* @return 
* @li ���������ݳ���
*/
int PubFPBBitmapPack(STISO_FIELD_DEF * pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief Ϊһ��ISO������ݽ��н����BITMAPλͼ��ASC����ʽ��
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pindata		���и����ĵ����ݻ�����
* @param [out] pfieldbuf	������8583�����ݻ�����
* @param [out] pfieldlen	���������ݳ���
* @return 
* @li ���ʱ��pindata��ʹ�õ����ݳ���
*/
int PubFPBBitmapUnPack(STISO_FIELD_DEF * pthis, unsigned char *pfieldbuf, int *pfieldlen, unsigned char *pindata);

/**
* @brief Ϊһ��ISO������ݽ��д�����ַ�������ASC����ʽ��
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pfieldbuf		��Ҫ�����8583������ָ��
* @param [in] nFieldlen		��Ҫ�����8583�����ݳ���
* @param [out] poutdata		���ڽ��ռ��������ݵĻ�����
* @return 
* @li ���������ݳ���
*/
int PubFPACharPack(STISO_FIELD_DEF * pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief Ϊһ��ISO������ݽ��н�����ַ�������ASC����ʽ��
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pindata		���и����ĵ����ݻ�����
* @param [out] pfieldbuf	������8583�����ݻ�����
* @param [out] pfieldlen	���������ݳ���
* @return 
* @li ���ʱ��pindata��ʹ�õ����ݳ���
*/
int PubFPACharUnPack(STISO_FIELD_DEF * pthis, unsigned char *pfieldbuf, int *pfieldlen, unsigned char *pindata);

/**
* @brief Ϊһ��ISO������ݽ��д�����ַ�������BCD����ʽ��
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pfieldbuf		��Ҫ�����8583������ָ��
* @param [in] pfieldbuf		��Ҫ�����8583�����ݳ���
* @param [out] poutdata		���ڽ��ռ��������ݵĻ�����
* @return 
* @li ���������ݳ���
*/
int PubFPBCharPack(STISO_FIELD_DEF * pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief Ϊһ��ISO������ݽ��н�����ַ�������BCD����ʽ��
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pindata		���и����ĵ����ݻ�����
* @param [out] pfieldbuf	������8583�����ݻ�����
* @param [out] pfieldlen	���������ݳ���
* @return 
* @li ���ʱ��pindata��ʹ�õ����ݳ���
*/
int PubFPBCharUnPack(STISO_FIELD_DEF * pthis, unsigned char *pfieldbuf, int *pfieldlen, unsigned char *pindata);

/**
* @brief Ϊһ��ISO������ݽ��д��������������ASC����ʽ��
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pfieldbuf		��Ҫ�����8583������ָ��
* @param [in] nFieldlen		��Ҫ�����8583�����ݳ���
* @param [out] poutdata		���ڽ��ռ��������ݵĻ�����
* @return 
* @li ���������ݳ���
*/
int PubFPADigitPack(STISO_FIELD_DEF * pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief Ϊһ��ISO������ݽ��н��������������ASC����ʽ��
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pindata		���и����ĵ����ݻ�����
* @param [out] pfieldbuf	������8583�����ݻ�����
* @param [out] pfieldlen	���������ݳ���
* @return 
* @li ���ʱ��pindata��ʹ�õ����ݳ���
*/
int PubFPADigitUnPack(STISO_FIELD_DEF * pthis, unsigned char *pfieldbuf, int *pfieldlen, unsigned char *pindata);

/**
* @brief Ϊһ��ISO������ݽ��д��������������BCD����ʽ��
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pfieldbuf		��Ҫ�����8583������ָ��
* @param [in] nFieldlen		��Ҫ�����8583�����ݳ���
* @param [out] poutdata		���ڽ��ռ��������ݵĻ�����
* @return 
* @li ���������ݳ���
*/
int PubFPBDigitPack(STISO_FIELD_DEF * pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief Ϊһ��ISO������ݽ��н��������������BCD����ʽ��
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pindata		���и����ĵ����ݻ�����
* @param [out] pfieldbuf	������8583�����ݻ�����
* @param [out] pfieldlen	���������ݳ���
* @return 
* @li ���ʱ��pindata��ʹ�õ����ݳ���
*/
int PubFPBDigitUnPack(STISO_FIELD_DEF * pthis, unsigned char *pfieldbuf, int *pfieldlen, unsigned char *pindata);

/**
* @brief Ϊһ��ISO������ݽ��д�������������ASC����ʽ��
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pfieldbuf		��Ҫ�����8583������ָ��
* @param [in] nFieldlen		��Ҫ�����8583�����ݳ���
* @param [out] poutdata		���ڽ��ռ��������ݵĻ�����
* @return 
* @li ���������ݳ���
*/
int PubFPBAmountPack(STISO_FIELD_DEF * pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief Ϊһ��ISO������ݽ��н�������������ASC����ʽ��
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pindata		���и����ĵ����ݻ�����
* @param [out] pfieldbuf	������8583�����ݻ�����
* @param [out] pfieldlen	���������ݳ���
* @return 
* @li ���ʱ��pindata��ʹ�õ����ݳ���
*/
int PubFPBAmountUnPack(STISO_FIELD_DEF * pthis, unsigned char *pfieldbuf, int *pfieldlen, unsigned char *pindata);

/**
* @brief Ϊһ��ISO������ݽ��д����������������BCD����ʽ��
* @param [in] pthis			ISO��������ͽṹָ��
* @param [in] pfieldbuf		��Ҫ�����8583������ָ��
* @param [in] nFieldlen		��Ҫ�����8583�����ݳ���
* @param [out] poutdata		���ڽ��ռ��������ݵĻ�����
* @return 
* @li ���������ݳ���
*/
int PubFPBBinaryPack(STISO_FIELD_DEF * pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief Ϊһ��ISO������ݽ��н����������������BCD����ʽ��
* @param [in] pthis			SO��������ͽṹָ��
* @param [in] pindata		���и����ĵ����ݻ�����
* @param [out] pfieldbuf	������8583�����ݻ�����
* @param [out] pfieldlen	���������ݳ���
* @return 
* @li ���ʱ��pindata��ʹ�õ����ݳ���
*/
int PubFPBBinaryUnPack(STISO_FIELD_DEF * pthis, unsigned char *pfieldbuf, int *pfieldlen, unsigned char *pindata);

/**
* @brief ת���ַ���ΪISO�ṹ
* @param [in] pcSourceStr		ת����Դ�ַ���
* @param [in] nStrLen			���ݳ���
* @param [out] pTargetIsoStru	ת���Ľ��ISO�ṹ
* @param [out] pnPosition		����ΪNULLʱ������;������ת������ʱ�����ţ����Է���ERRFIELDLENʱ��Ч������������¾�Ϊ-1
* @return 
* @li APP_FAIL		ת��ʧ�ܣ�pcSourceStr����TargetIsoStruΪ�գ��������
* @li APP_APP_SUCC	ת���ɹ�
*/
int PubStrToIso(char *pcSourceStr, int nStrLen, STISODataStru *pTargetIsoStru, int *pnPosition);

/**
* @brief ��ISO�ṹת�����޷����ַ���
* @param [in] pSourceIsoStru	ת����Դ���ݽṹ
* @param [in] pnLen				����pcTargetStr�Ŀռ��С��������������
* @param [out] pcTargetStr		ת���Ľ���ַ���(BCD��)
* @param [out] pnLen			���ת���ɹ�����ַ������ȣ����ʧ�ܣ�����Ϊ-1��
* @return 
* @li APP_FAIL		ת��ʧ�ܣ�pcTargetStr����pSourceIsoStruΪ�գ����ʧ��
* @li APP_APP_SUCC	ת���ɹ�
*/
int PubIsoToStr(char *pcTargetStr, STISODataStru *SourceIsoStru, int *pnLen);

/**
* @brief ���ṹISO��ָ����Ա��ȡ���ַ���szTargetStr��
* @param [in] pSourceIsoStru	Դ���ݽṹISO_data �ṹָ��
* @param [in] nPosition			ISO_data�ṹ�еĵ�N����Ա
* @param [in] pnLen				����Ҫת���ִ��Ŀռ��С��������β���ţ�
* @param [out] pcTargetStr		Ŀ���ַ���
* @param [out] pnLen			����ת���ɹ�ʱ�ַ����ĳ��ȣ�ת��ʧ����pnLen�ǿ�ʱΪ-1
* @return 
* @li APP_FAIL		ʧ��,TargetIsoStru����pcSourceStr����pnLenΪ�գ����ߵ���HexToAsc��������ָ���ĳ�Ա��Ч�����ߴ����pcSourceStr�ռ䲻��
* @li APP_APP_SUCC	�ɹ�
*/
int PubGetBit(STISODataStru *pSourceIsoStru, int nPosition, char *pcTargetStr, int *pnLen);

/**
* @brief ���ַ���pcSourceStr��ָ������nStrLen��䵽�ṹTargetIsoStru��ָ����Ա
* @param [in] nPosition			ָ����ISO_data�ṹ�еĵ�N����Ա
* @param [in] pcSourceStr		�������
* @param [in] nStrLen			pcSourceStr �ĳ���
* @param [out] pTargetIsoStru	������Ŀ��ṹISO_data �ṹ��ָ��
* @return 
* @li APP_FAIL		ʧ�ܣ�TargetIsostru����pcSourceStrΪNULL������ָ���ĳ�Ա��Ч�����ߵ���AscToHex��������ISO�ṹ�ۼƳ��ȳ���MAXISOLEN
* @li APP_APP_SUCC	���óɹ�����nStrLen ����0
*/
int PubSetBit(STISODataStru *pTargetIsoStru, int nPosition, char *pcSourceStr, int nStrLen);

/**
* @brief ���ISO_data�ṹ�����г�Ա����ֵ
* @param [in] pIsoStru		Դ���ݽṹISO_data �ṹָ��
* @param [out] pIsoStru		��պ��ISO_data�ṹָ��
* @return 
* @li APP_FAIL		ʧ�ܣ�IsoStruΪ��
* @li APP_APP_SUCC	�ɹ�
*/
int PubDelAllBit(STISODataStru *pIsoStru);

/**
* @brief ���IsoStru�ṹ�е�nPosition���ֵ��ͬʱ���λͼ�е���Ӧ��־
* @param [in] pIsoStru		Դ���ݽṹISO_data �ṹָ��
* @param [in] nPosition		ISO_data�ṹ�еĵ�nPosition����Ա
* @param [out] pIsoStru		������ISO_data�ṹָ��
* @return 
* @li APP_FAIL		ʧ�ܣ�IsoStruΪNULL��������Ч�ĳ�Ա�ţ�nPosition <0 ���� >=256��
* @li APP_APP_SUCC	�ɹ�
*/
int PubDelOneBit(STISODataStru *pIsoStru, int nPosition);

/**
* @brief ����8583���ݰ�����
* @param [in] nPosition		���
* @param [in] nMaxLen		��󳤶�
* @param [in] LenType		��������
* @param [in] AlignType		��������
* @param [in] chPadChar		�����ַ�
* @param [in] PackFunc		�������
* @param [in] UnpackFunc	�������
* @return 
* @li APP_FAIL		ʧ��
* @li APP_APP_SUCC	�ɹ�
*/
int PubSetDefine8583(int nPosition, int nMaxLen, EM_LENGTH_TYPE	LenType, EM_ALIGN_TYPE AlignType, char chPadChar, FIELD_PACKAGER_PACK PackFunc, FIELD_PACKAGER_UNPACK UnpackFunc);

/**
* @brief ����8583�ṹ
* @param [in] pNewDef		Ҫ�����8583�ṹ
* @return 
* @li APP_FAIL		ʧ��
* @li APP_APP_SUCC	�ɹ�
*/
int PubImport8583(const struct STISO_FIELD_DEF *pNewDef);

/**
* @brief ������ʾ8583���ݰ�����
* @param [in] pIsoStru		����ʾ��ISO �ṹ
* @return 
* @li ��
*/
void PubFormatDisp8583(STISODataStru *pIsoStru);

/**
* @brief ����8583�򳤶ȼ��㺯���ṹ
* @param [in] pNewCalc		Ҫ�����8583�򳤶ȼ��㺯���ṹ
* @return 
* @li APP_FAIL		ʧ��
* @li APP_APP_SUCC	�ɹ�
*/
int PubSetFieldLengthCalc(const struct STISO_FIELD_LENGTH_CALC *pNewCalc);

/**
* @brief ����һ��STISODataStru�ṹ
* @param [in] pSourceIsoStru		ԴISO_data�ṹ��ָ��
* @param [out] pTargetIsoStru		������Ŀ��ṹISO_data �ṹ��ָ��
* @return 
* @li APP_FAIL		ʧ�ܣ�pSourceIsoStru����pTargetIsoStruΪ��
* @li APP_APP_SUCC	���óɹ�
*/
int PubCopyIso(STISODataStru *pSourceIsoStru, STISODataStru *pTargetIsoStru);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief ͨ������1������־�ļ�
* @detail ���ڣ�1,115200
* @param ��
* @return 
* @li ��
* @author ���
* @date 2012-10-24
*/
void PubExportDebugFile();

/**
* @brief ͨ�������������ݵ�����Ϣ���
* @param [in] pszTitle  --- ����
* @param [in] pData     --- ����
* @param [in] nLen      --- ���ݳ���
* @return 
* @li ��
* @author ���
* @date 2012-10-24
*/
void PubDebugData(const char* pszTitle,const void* pData,int nLen);

/**
* @brief ��������Ϣ����
* @param [in]  lpszFormat   --- ��ʽ���ַ���
* @return 
* @li ��
* @author ���
* @date 2012-10-24
*/
void PubDebug(char* lpszFormat, ...);

/**
* @brief ��ȡ���߿�Debugģʽ
* @return 
* @li 0:  ����ģʽ:�޵������
* @li 1:  Debugģʽ  :�������
* @li 2:  Debugģʽ  :�ļ����
*/
int PubGetDebugMode();


/**
* @brief �ӵ��籣������ȡ����
* @param [out]  psBuf   --- ����
* @param [in]  nStart      --- ��ʼ��ַ
* @param [in]  nLen        --- ���ݳ���
* @return 
* @li APP_SUCC �ɹ�
* @li APP_FAIL ʧ��
* @author ���
* @date 2012-10-24
*/
int PubGetVar (char *psBuf, const int nStart, const int nLen);

/**
* @brief �����ݱ��浽���籣����
* @param [in]  psSaveBuf   --- ����
* @param [in]  nStart      --- ��ʼ��ַ
* @param [in]  nLen        --- ���ݳ���
* @return 
* @li APP_SUCC �ɹ�
* @li APP_FAIL ʧ��
* @author ���
* @date 2012-10-24
*/
int PubSaveVar (const char *psSaveBuf, const int nStart, const int nLen);

/**
* @brief ��ȡ������
* @param [out]  pnErrorCode			ģ�������
* @param [out]  pszErr					ģ���������ʾ��Ϣ
* @param [out]  pnNDKErrorCode		NDK������
* @return 
* @li ��
*/
void PubGetErrorCode(int *pnErrorCode, char *pszErr, int *pnNdkErrorCode);

/**
* @brief ���ô�����
* @param [in]  nErrCode			ģ�������
* @param [in]  pszErrTip			ģ���������ʾ��Ϣ
* @param [in]  nNdkErrCode		NDK������
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @author ���
* @date 2012-10-22
*/
void PubSetErrorCode(int nErrCode,const char *pszErr,int nNdkErrCode);

/**
* @brief ���ô�����Ϣ
* @param [in]  nErrorCode			ģ�������
* @param [in]  nNDKErrorCode		NDK������
* @param [in]  ppszErr				������Ϣ(��ά����)
* @return 
* @li ��
*/
void PubSetErrorInfo(int nErrCode,const char *ppszErr[MAX_ERR_BUF_LEN],int nNdkErrCode);

/**
* @brief POS����
* @param [in] nTimes	��������
* @return 
* @li ��
*/
void PubBeep(int nTimes);

/**
* @brief POS�ػ�
* @return
* li APP_SUCC	�ɹ� 
* li APP_FAIL   ʧ��
*/
int PubShutDown();

/**
* @brief �����ܱ���ʼ��ʱ
* @return
* li APP_SUCC	�ɹ� 
* li APP_FAIL   ʧ��
*/
int PubStartWatch();

/**
* @brief ֹͣ�ܱ��������ֵ 
* @param [in] punTime   �ܱ����ʱ�ļ���ֵ (����)
* @return
* li APP_SUCC	�ɹ� 
* li APP_FAIL   ʧ��
*/
int PubStopWatch(uint * punTime);

/**
* @brief �ȡPOSӲ��֧����Ϣ
* @param [in] emFlag	EM_HARDWARE_SUPPORT ö�ٸ���Ӳ��
* @param [out] pszBuf	��Ӧ��Ӳ����Ϣ
* @return 
* @li APP_FAIL		��֧�ָ�Ӳ��
* @li APP_APP_SUCC	֧�ָ�Ӳ��
* @date 2012-11-13
*/
int PubGetHardwareSuppot(int emFlag, char* pszBuf);

/**
* @brief ��ȡPOSӲ����Ϣ
* @param [in] emFlag	EM_HARDWARE_GET ö�ٸ���Ӳ��
* @param [out] pszBuf	��Ӧ��Ӳ����Ϣ
* @return 
* @li APP_FAIL		ʧ��
* @li APP_APP_SUCC	�ɹ�
*/
int PubGetPosInfo(int emFlag, char* pszBuf);

#endif

