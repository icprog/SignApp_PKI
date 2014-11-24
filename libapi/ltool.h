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

#define APP_SUCC		(0)   	/**<³É¹¦      */
#define APP_FAIL		(-1)    /**<Ê§°Ü      */
#define APP_QUIT		(-2)    /**<ÍË³ö¡¢È¡Ïû*/
#define APP_TIMEOUT 	(-3)    /**<³¬Ê±      */
#define APP_FUNCQUIT	(-4)    /**<°´¹¦ÄÜ¼ü·µ»Ø*/

#define FILE_NOCREATEINDEX 0x00		/**<²»´´½¨Ë÷ÒıÎÄ¼ş*/
#define FILE_CREATEINDEX   0x01		/**<´´½¨Ë÷ÒıÎÄ¼ş  */

#define MAX_ERR_BUF_LEN 	(128)		/**<´íÎóÂëĞÅÏ¢×î´ó³¤¶È */
#define MAX_ERR_NUM		(1000)		/**<´íÎóÂëĞÅÏ¢×î´ó¸öÊı */

typedef enum
{
	NO   = '0',
	YES  = '1'
}YESORNO;

enum EM_ADDCH_MODE
{
	ADDCH_MODE_BEFORE_STRING=0,			/**<Íù×Ö·û´®Ç°Ãæ¼Ó×Ö·û*/
	ADDCH_MODE_AFTER_STRING,			/**<Íù×Ö·û´®ºóÃæ¼Ó×Ö·û*/
	ADDCH_MODE_BEFORE_AFTER_STRING		/**<Íù×Ö·û´®Ç°ºó¼Ó×Ö·û*/
};

enum EM_HARDWARE_SUPPORT
{
	HARDWARE_SUPPORT_WIRELESS=0,		/**<ÎŞÏßÄ£¿é*/
	HARDWARE_SUPPORT_RADIO_FREQUENCY,	/**<ÉäÆµÄ£¿é*/
	HARDWARE_SUPPORT_MAGCARD,			/**<´Å¿¨Ä£¿é*/
	HARDWARE_SUPPORT_SCANNER,			/**<É¨ÃèÍ·Ä£¿é*/
	HARDWARE_SUPPORT_PINPAD,			/**<ÊÇ·ñÖ§³ÖÍâ½ÓÃÜÂë¼üÅÌ*/
	HARDWARE_SUPPORT_COMM_NUM,			/**<´®¿Ú¸öÊı*/
	HARDWARE_SUPPORT_USB,				/**<ÊÇ·ñÖ§³ÖUSB*/
	HARDWARE_SUPPORT_MODEM,				/**<MODEMÄ£¿é*/
	HARDWARE_SUPPORT_WIFI,				/**<wifiÄ£¿é*/
	HARDWARE_SUPPORT_ETH,				/**<ÊÇ·ñÖ§³ÖÒÔÌ«Íø*/
	HARDWARE_SUPPORT_PRINTER,			/**<´òÓ¡Ä£¿é*/
	HARDWARE_SUPPORT_TOUCH_SCREEN,		/**<ÊÇ·ñÖ§³Ö´¥ÆÁ*/
	HARDWARE_SUPPORT_LED_LIGHT			/**<ÊÇ·ñÓĞÉäÆµLEDµÆ*/
};

enum EM_HARDWARE_GET
{
	HARDWARE_GET_BIOS_VER=2,		/**<È¡bios°æ±¾ĞÅÏ¢ */
	HARDWARE_GET_POS_USN,			/**<È¡»úÆ÷ĞòÁĞºÅ */
	HARDWARE_GET_POS_PSN,			/**<È¡»úÆ÷»úÆ÷ºÅ */
	HARDWARE_GET_BOARD_VER,			/**<È¡Ö÷°åºÅ */
	HARDWARE_GET_CREDITCARD_COUNT, /**<È¡posË¢¿¨×ÜÊı */
	HARDWARE_GET_PRN_LEN,			/**<È¡pos´òÓ¡×Ü³¤¶È */
	HARDWARE_GET_POS_RUNTIME,		/**<È¡pos»ú¿ª»úÔËĞĞÊ±¼ä */
	HARDWARE_GET_KEY_COUNT			/**<È¡pos»ú°´¼ü´ÎÊı */
};

typedef struct tagRecFile
{
	unsigned int unMaxOneRecLen;	/**<×î´óµÄµ¥Ìõ¼ÇÂ¼³¤¶È */  
	unsigned int unIndex1Start;		/**<Ë÷Òı×Ö¶Î1µÄÆğÊ¼Î»ÖÃ*/
	unsigned int unIndex1Len;		/**<Ë÷Òı×Ö¶Î1µÄ³¤¶È    */
	unsigned int unIndex2Start; 	/**<Ë÷Òı×Ö¶Î2µÄÆğÊ¼Î»ÖÃ*/
	unsigned int unIndex2Len;		/**<Ë÷Òı×Ö¶Î2µÄ³¤¶È    */
	char cIsIndex;					/**<ÊÇ·ñĞèÒª½¨Á¢Ë÷ÒıÎÄ¼ş£¬0x00²»½¨Á¢£¬0x01½¨Á¢*/
	char szFileName[128];			/**<¼ÇÂ¼ÎÄ¼şÃû,ÓĞĞ§µÄ¼ÇÂ¼ÎÄ¼şÃû³¤¶ÈÎª128*/
	char s[2];
}STRECFILE;


/**
* @brief 2¸ö×î´ó²»³¬¹ı12Î»µÄÎŞ·ûºÅÊı×Ö´®Öğ´ÎÖğÎ»Ïà¼Ó£¬Ïà¼Ó½á¹û²»ÄÜ³¬¹ı12Î»
* @param [in] pszDigStr1 Êı×Ö´®1
* @param [in] pszDigStr2 Êı×Ö´®2
* @param [out] pszResult Ïà¼ÓºÍµÄÊı×Ö´®
* @param [out] pnOutLen  Ïà¼ÓºÍµÄÎ»Êı
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubAddDigitStr (const char* pszDigStr1, const char* pszDigStr2, char* pszResult, int* pnResultLen );

/**
* @brief ½«6Î»Êı×Ö´®pcStrNumÔö¼Ó1ºó·Å»ØÔ­Öµ
* @param [in] pcStrNum  ĞèÒª±»Ôö¼ÓµÄÊı×Ö´®
* @param [out] pcStrNum Ôö¼ÓºóµÄ½á¹û´®
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubIncNum (char* pcStrNum );

/**
* @brief 	Á½¸öASCÊı×Ö´®Ïà¼Ó¡£
* @param [in] pszAsc1	¼ÓÊıASC×Ö·û´®
* @param [in] pszAsc2	¼ÓÊıASC×Ö·û´®
* @param [out] pszResult	Ïà¼ÓµÄ½á¹û
* @return 
* @li ÎŞ
*/
void PubAscAddAsc(uchar *pszAsc1, uchar *pszAsc2, uchar *pszSum);

/**
* @brief Á½¸öASC×Ö·û´®Ïà¼õ
* @param [in] pszAsc1	¼õÊıASC×Ö·û´®£¬²»³¬¹ı×î´ó³¤ÕûĞÍ
* @param [in] pszAsc2	±»¼õÊıASC×Ö·û´®£¬²»³¬¹ı×î´ó³¤ÕûĞÍ
* @param [out] pszResult	Ïà¼õµÄ½á¹û
* @return 
* @li ÎŞ
*/
void PubAscSubAsc(uchar *pszAsc1, uchar *pszAsc2, uchar *pszResult);

/**
* @brief Á½¸öASC×Ö·û´®Ïà³Ë
* @param [in] pszAsc1	³ËÊıASC×Ö·û´®
* @param [in] pszAsc2	³ËÊıASC×Ö·û´®
* @param [out] pszProduct	Ïà³ËµÄ½á¹û
* @return 
* @li ÎŞ
*/
void PubAscMulAsc(uchar *pszAsc1, uchar *pszAsc2, uchar *pszProduct );


/**
* @brief °Ñ´øĞ¡ÊıµãµÄ½ğ¶î×Ö·û´®×ªÎª²»´øĞ¡ÊıµãµÄ½ğ¶î×Ö·û´®
* @param [in] pszSource    ´ı×ª»»µÄ½ğ¶î×Ö·û´®
* @param [in] pnTargetLen  Ä¿±ê»º³åÇøµÄ´óĞ¡
* @param [out] pszTarget   ×ª»»ºóµÄ×Ö·û´®
* @param [out] pnTargetLen ×ª»»ºóµÄ×Ö·û´®³¤¶È
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubFmtAmtStr (const char* pszSource, char* pszTarget, int* pnTargetLen );

/**
* @brief ½«AscIIÂëµÄ×Ö·û´®×ª»»³ÉÑ¹ËõµÄHEX¸ñÊ½£¬·ÇÅ¼Êı³¤¶ÈµÄ×Ö·û´®¸ù¾İ¶ÔÆë·½Ê½£¬²ÉÈ¡×ó²¹0£¬ÓÒ²¹F·½Ê½
* @param [in] pszAsciiBuf ±»×ª»»µÄASCII×Ö·û´®
* @param [in] nLen        ÊäÈëÊı¾İ³¤¶È(ASCII×Ö·û´®µÄ³¤¶È)
* @param [in] cType       ¶ÔÆë·½Ê½  0£­×ó¶ÔÆë  1£­ÓÒ¶ÔÆë
* @param [out] pszBcdBuf  ×ª»»Êä³öµÄHEXÊı¾İ
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubAscToHex (const unsigned char* pszAsciiBuf, int nLen, char cType, unsigned char* pszBcdBuf);

/**
* @brief ½«HEXÂëÊı¾İ×ª»»³ÉAscIIÂë×Ö·û´®
* @param [in] pszBcdBuf    ±»×ª»»µÄHexÊı¾İ
* @param [in] nLen         ×ª»»Êı¾İ³¤¶È(ASCII×Ö·û´®µÄ³¤¶È)
* @param [in] cType        ¶ÔÆë·½Ê½  1£­×ó¶ÔÆë  0£­ÓÒ¶ÔÆë
* @param [out] pszAsciiBuf ×ª»»Êä³öµÄAscIIÂëÊı¾İ
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubHexToAsc (const unsigned char* pszBcdBuf, int nLen, char cType, unsigned char* pszAsciiBuf);

/**
* @brief ÕûĞÍ×ª»»Îª4×Ö½Ú×Ö·û´®£¨¸ßÎ»ÔÚÇ°£©
* @param [in] nNum    ĞèÒª×ª»»µÄÕûĞÍÊı
* @param [out] pszBuf ×ª»»Êä³öµÄ×Ö·û´®
* @return 
* @li ÎŞ
* @date 2012-06-19
*/
void PubIntToC4 (unsigned char* pszBuf, unsigned int nNum );

/**
* @brief ÕûĞÍ×ª»»Îª2×Ö½Ú×Ö·û´®£¨¸ßÎ»ÔÚÇ°£©
* @param [in] nNum    ĞèÒª×ª»»µÄÕûĞÍÊı
* @param [out] pszBuf ×ª»»Êä³öµÄ×Ö·û´®
* @return 
* @li ÎŞ
* @date 2012-06-19
*/
void PubIntToC2 (unsigned char* pszBuf, unsigned int nNum );

/**
* @brief 4×Ö½Ú×Ö·û´®×ª»»ÎªÕûĞÍ£¨¸ßÎ»ÔÚÇ°£©
* @param [in] pszBuf ĞèÒª×ª»»µÄ×Ö·û´®
* @param [out] nNum  ×ª»»Êä³öµÄÕûĞÍÊı
* @return 
* @li ÎŞ
* @date 2012-06-19
*/
void PubC4ToInt (unsigned int* nNum, unsigned char * pszBuf );

/**
* @brief 2×Ö½Ú×Ö·û´®×ª»»ÎªÕûĞÍ£¨¸ßÎ»ÔÚÇ°£©
* @param [in] pszBuf ĞèÒª×ª»»µÄ×Ö·û´®£¬pszBuf³¤¶ÈÒª>=2
* @param [out] nNum  ×ª»»Êä³öµÄÕûĞÍÊı
* @return 
* @li ÎŞ
* @date 2012-06-19
*/
void PubC2ToInt(unsigned int *nNum, unsigned char *pszBuf);

/**
* @brief ÕûÊı(0-99)×ª»»ÎªÒ»×Ö½ÚBCD
* @param [in] nNum ĞèÒª×ª»»µÄÕûĞÍÊı(0-99)
* @param [out] ch  ×ª»»Êä³öµÄÒ»¸öBCD×Ö·û
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubByteToBcd(int nNum, char *ch);

/**
* @brief Ò»×Ö½ÚBCD×ª»»ÎªÕûÊı(0-99)
* @param [in] ch     ĞèÒª×ª»»µÄBCD×Ö·û
* @param [out] pnNum ×ª»»Êä³öµÄÕûÊıÖµ(0-99)
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubBcdToByte(char ch, int *pnNum);

/**
* @brief ÕûÊı(0-9999)×ª»»Îª¶ş×Ö½ÚBCD
* @param [in] nNum      ĞèÒª×ª»»µÄÕûĞÍÊı(0-9999)
* @param [in] pnBcdLen  Êä³ö»º³åÇøµÄ´óĞ¡   
* @param [out] psBcd    ×ª»»Êä³öµÄÁ½×Ö½ÚBCD
* @param [out] pnBcdLen ×ª»»ºóµÄBCD³¤¶È£¬Èç¹û³É¹¦´ËÖµ£¬¹Ì¶¨·µ»ØÖµÎª2
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubIntToBcd(char *psBcd, int *pnBcdLen, int nNum);

/**
* @brief ¶ş×Ö½ÚBCD×ª»»ÎªÕûÊı(0-9999)
* @param [in] psBcd   ĞèÒª×ª»»µÄÁ½×Ö½ÚBCD£¬³¤¶ÈÓ¦µÈÓÚ2
* @param [out] nNum   ×ª»»ºóµÄÕûÊı(0-9999)
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubBcdToInt(const char * psBcd, int *nNum);

/**
* @brief ¼ÆËãLRC
* @param [in] psBuf  ĞèÒª¼ÆËãLRCµÄ×Ö·û´®
* @param [in] nLen   ĞèÒª¼ÆËãLRCµÄ×Ö·û´®µÄ³¤¶È
* @param [out] chLRC ¼ÆËãµÃ³öµÄLRC
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubCalcLRC(const char *psBuf, int nLen, char *chLRC);

/**
* @brief ×Ö·û´®È¥×ó¿Õ¸ñ
* @param [in] pszSrc  ´æ·Å×Ö·û´®µÄ»º³åÇø
* @param [out] pszSrc È¥µô×ó¿Õ¸ñºóµÄ×Ö·û´®
* @return 
* @li ÎŞ
* @date 2012-06-19
*/
void PubLeftTrim(char *pszSrc);

/**
* @brief ×Ö·û´®È¥ÓÒ¿Õ¸ñ
* @param [in] pszSrc  ´æ·Å×Ö·û´®µÄ»º³åÇø
* @param [out] pszSrc È¥µôÓÒ¿Õ¸ñºóµÄ×Ö·û´®
* @return 
* @li Ş
* @date 2012-06-19
*/
void PubRightTrim(char *pszSrc);

/**
* @brief ×Ö·û´®È¥ÓÒ¿Õ¸ñ
* @param [in] pszSrc  ´æ·Å×Ö·û´®µÄ»º³åÇø
* @param [out] pszSrc È¥µô×óÓÒ¿Õ¸ñºóµÄ×Ö·û´®
* @return 
* @li ÎŞ
* @date 2012-06-19
*/
void PubAllTrim(char *pszSrc);

/**
* @brief ´ÓÒ»×Ö·û´®ÀïÉ¾³ıÄ³Ò»×Ö·û
* @param [in] pszString		´ı´¦ÀíµÄ×Ö·û´®
* @param [in] ucSymbol	ËùÒªÉ¾³ıµÄ×Ö·û
* @param [out] pszString	É¾³ıÌØÊâ×Ö·ûucSymbolºóµÄ×Ö·û´®
* @return
* li ×ª»»ºóÕûÊı
*/
void PubDelSymbolFromStr(uchar *pszString, uchar ucSymbol);

/**
* @brief ÍùÒ»×Ö·û´®Àï¼ÓÈëÄ³Ò»×Ö·ûÊ¹Ö®³¤¶ÈÎªnLen
* @param [in] pszString  ´æ·Å×Ö·û´®µÄ»º³åÇø
* @param [in] nLen       ¼ÓÈë×Ö·ûºó×Ö·û´®µÄ³¤¶È
* @param [in] ch         ËùÒª¼ÓÈëµÄ×Ö·û
* @param [in] nOption    ²Ù×÷ÀàĞÍ--EM_ADDCH_MODE
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubAddSymbolToStr(char *pszString, int nLen, char ch, int nOption);

/**
* @brief É¾³ı×Ö·û´®×ó±ßÁ¬ĞøµÄÌØ¶¨×Ö·û
* @param [in] pszStringInOut 	´ı×ª»»µÄ×Ö·û´®
* @param [in] ucRemoveChar	´ıÉ¾³ı×Ö·û
* @param [out] pszString		×ª»»ºóµÄ×Ö·û´®
* @return
* li ÎŞ
*/
void PubLeftTrimChar(uchar *pszSrc, uchar ucRemoveChar);

/**
* @brief É¾³ı×Ö·û´®ÓÒ±ßÁ¬ĞøµÄÌØ¶¨×Ö·û
* @param [in] pszStringInOut	´ı×ª»»µÄ×Ö·û´®
* @param [in] ucRemoveChar	´ıÉ¾³ı×Ö·û
* @param [out] pszString		×ª»»ºóµÄ×Ö·û´®
* @return
* li ÎŞ
*/
void PubRightTrimChar(uchar *pszSrc, uchar ucRemoveChar);

/**
* @brief ²âÊÔÒ»×Ö´®ÊÇ·ñÎª´¿Êı×Ö´®
* @param [in] pszString    ĞèÒªÅĞ¶ÏµÄ×Ö·û´®
* @return 
* @li APP_FAIL ·ñ
* @li APP_SUCC ÊÇ
* @date 2012-06-19
*/
int PubIsDigitStr(const char *pszString);

/**
* @brief ÅĞ¶Ï¸ø¶¨Ò»×Ö·ûÊÇ²»ÊÇÊı×Ö×Ö·û
* @param [in] ch ĞèÒªÅĞ¶ÏµÄ×Ö·û
* @return 
* @li APP_FAIL ·ñ
* @li APP_SUCC ÊÇ
* @date 2012-06-19
*/
int PubIsDigitChar(char ch);

/**
* @brief ÅĞ¶ÏÌá¹©µÄ×Ö·û´®ÊÇ²»ÊÇºÏ·¨µÄÈÕÆÚ¸ñÊ½´®
* @param [in] pDate ÈÕÆÚ¸ñÊ½×Ö·û´®  ¸ñÊ½Îª YYYYMMDD
* @return 
* @li APP_FAIL ·Ç·¨
* @li APP_SUCC ºÏ·¨
* @date 2012-06-19
*/
int PubIsValidDate(const char *pDate);

/**
* @brief	×ª»»Êı×Ö´®µ½½ğ¶î¸ñÊ½£¬ÈçHKD$****.**, RMB****.**
* @param [in] pszPrefix 	pszPrefix  Ç°¶îµÄÇ°×º£¬Èç¡°HKD 200.00¡±ÖĞµÄ¡°HKD¡±
* @param [in] pszIn			ĞèÒª×ª»»µÄ´¿Êı×Ö´®,¹ıÂËµ½Ç°ÃæµÄ'0'
* @param [in] ucRadPt		Ğ¡ÊıµãºóµÄ½ğ¶îÎ»Êı£¬±ØĞèĞ¡ÓÚ4
* @param [out] pszOut		¸ñÊ½»¯ºóµÄ½ğ¶î´®
* @return
* li ×ª»»ºóÕûÊı
*/
void PubConvAmount(uchar *pszPrefix, uchar *pszIn, uchar ucRadPt, uchar *pszOut);

/**
* @brief È¡µÃµ±Ç°ÈÕÆÚÊ±¼ä
* @param [out] pDatetime ´æ·Åµ±Ç°ÈÕÆÚÊ±¼äÆä¸ñÊ½ÎªYYYYMMDDHHMMSS£¬³¤¶È±ØĞè>14
* @return 
* @li ÎŞ
* @date 2012-06-19
*/
void PubGetCurrentDatetime(char *pDatetime);

/**
* @brief ÉèÖÃPOSÈÕÆÚÊ±¼ä
* @param in pszDate ÈÕÆÚ
* @param in pszDateFormat ¸ñÊ½¶¨Òå
* @param in pszTime Ê±¼ä
* @return 
* @li APP_SUCC ³É¹¦
* @li APP_FAIL Ê§°Ü
*/
int PubSetPosDateTime(const char *pszDate, const char *pszDateFormat, const char *pszTime);

/**
* @brief ÕÒ³öÄ³ÄêÄ³ÔÂµÄ×î´óÌìÊı
* @param [in] nYear   Äê·İ
* @param [in] nMon    ÔÂ·İ
* @param [out] pnDays ¸ÃÄê·İ¸ÃÔÂ¶ÔÓ¦µÄ×î´óÌìÊı
* @return 
* @li APP_FAIL ·Ç·¨µÄÊäÈë²ÎÊı
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubMonthDays(int nYear, int nMon, int *pnDays);

/**
* @brief ÅĞ¶ÏÄ³ÄêÊÇ·ñÈòÄê
* @param [in] nYear Äê·İ
* @return 
* @li APP_FAIL ·ÇÈòÄê
* @li APP_SUCC ÈòÄê
* @date 2012-06-19
*/
int PubIsLeapYear(int nYear);

/**
* @brief »ñÈ¡³¬Ê±µÄÊ±¼ä¼ÆÊı
* @param [in]  unMsTime  ³¬Ê±Ê±¼ä (µ¥Î»:ms)
* @return 
* @li ·µ»ØÊ±¼ä¼ÆÊı
* @author Áõî¸
* @date 2012-10-24
*/
uint PubGetOverTimer(uint unMsTime);

/**
* @brief ÅĞ¶ÏÊÇ·ñµ½´ï³¬Ê±Ê±¼ä
* @param [in]  unOverTime  Ö®Ç°»ñÈ¡µÄ³¬Ê±Ê±¼ä¼ÆÊı (µ¥Î»:ms)
* @return 
* @li APP_APP_SUCC ÒÑ³¬Ê±
* @li APP_APP_FAIL Î´³¬Ê±
* @author Áõî¸
* @date 2012-10-24
*/
int PubTimerIsOver(uint unOverTime);

/**
* @brief È¡¹¤¾ß¿â°æ±¾ºÅ
* @param [out] pszVer ´æ·Å°æ±¾ºÅ£¬×Ö·û´®³¤¶È>12
* @return 
* @li ÎŞ
* @date 2012-06-19
*/
void PubGetToolsVer(char *pszVer);

/**
* @brief ´´½¨Ë÷ÒıÎÄ¼ş
* @param [in] pstRecFile   ²ÎÊı
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubCreatRecFile(const STRECFILE *pstRecFile);

/**
* @brief °´ÎÄ¼şÃû´ò¿ªÎÄ¼ş
* @param [in] pszFileName   Á÷Ë®ÎÄ¼şÃû
* @param [in] pszMode       ´ò¿ª·½Ê½
* @param [out] pnFileHandle ´ò¿ªµÄÎÄ¼ş¾ä±ú
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubOpenFile (const char *pszFileName, const char *pszMode,int *pnFileHandle);

/**
* @brief ¹Ø±ÕÎÄ¼ş¾ä±ú
* @param [in] pnFileHandle Òª¹Ø±ÕµÄÎÄ¼ş¾ä±ú
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubCloseFile (int *pnFileHandle);

/**
* @brief É¾³ıÁ÷Ë®ÎÄ¼ş
* @param [in] pszFileName Á÷Ë®ÎÄ¼şÃû
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubDeReclFile (const char *pszFileName);

/**
* @brief °´ÎÄ¼şÃû´ò¿ªÎÄ¼ş£¬»ñÈ¡ÎÄ¼ş¼ÇÂ¼×ÜÊı
* @param [in] pszFileName Á÷Ë®ÎÄ¼şÃû
* @param [out] pnRecSum   Ö¸Ïò¼ÇÂ¼ÊıÁ¿µÄÖ¸Õë
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubGetRecSum (const char *pszFileName, int *pnRecSum);

/**
* @brief Ôö¼ÓÁ÷Ë®¼ÇÂ¼£¬¶ÔÓÚ´´½¨¼ÇÂ¼ÊÇÖ¸¶¨ÁËĞèÒª½¨Á¢Ë÷ÒıÎÄ¼şµÄ»áÏàÓ¦Ôö¼ÓË÷Òı¼ÇÂ¼
* @param [in] pszFileName Á÷Ë®ÎÄ¼şÃû
* @param [in] pszRec ÊäÈëµÄÁ÷Ë®¼ÇÂ¼
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubAddRec (const char *pszFileName, const char *pszRec);

/**
* @brief °´¼ÇÂ¼ºÅ¶ÁÁ÷Ë®¼ÇÂ¼
* @param [in] nFileHandle ´ò¿ªµÄÎÄ¼ş¾ä±ú
* @param [in] nRecNo      ÒªÕÒµÄ¼ÇÂ¼ºÅ
* @param [out] psRec      ¼ÇÂ¼Ö¸Õë
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubReadRec (const int nFileHandle, const int nRecNo, char *psRec);

/**
* @brief ¸üĞÂ¼ÇÂ¼£¬°´Ö¸¶¨µÄ¼ÇÂ¼Î»ÖÃÖØĞ´Ö¸¶¨µÄ¼ÇÂ¼£¬Í¬Ê±¶ÔÓÚ´´½¨¼ÇÂ¼ÊÇÖ¸¶¨ÁËĞèÒª½¨Á¢Ë÷ÒıÎÄ¼şµÄ»áÏàÓ¦¸üĞÂË÷Òı¼ÇÂ¼
* @param [in] pszFileName ¼ÇÂ¼ÎÄ¼şÃû³Æ
* @param [in] nRecNo      ÒªĞŞ¸ÄµÄ¼ÇÂ¼ºÅ
* @param [in] psRec       ¼ÇÂ¼Ö¸Õë
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubUpdateRec (const char *pszFileName, const int nRecNo, const char *psRec);

/**
* @brief ¸üĞÂ¼ÇÂ¼£¬°´Ö¸¶¨µÄ¼ÇÂ¼Î»ÖÃÖØĞ´Ö¸¶¨µÄ¼ÇÂ¼£¬Í¬Ê±¶ÔÓÚ´´½¨¼ÇÂ¼ÊÇÖ¸¶¨ÁËĞèÒª½¨Á¢Ë÷ÒıÎÄ¼şµÄ»áÏàÓ¦¸üĞÂË÷Òı¼ÇÂ¼
* @param [in] nFileHandle ¼ÇÂ¼ÎÄ¼ş¾ä±ú
* @param [in] nRecNo      ÒªĞŞ¸ÄµÄ¼ÇÂ¼ºÅ
* @param [in] psRec       ¼ÇÂ¼Ö¸Õë
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubUpdateRecByHandle (int nFileHandle, const int nRecNo, const char *psRec);

/**
* @brief °´¼ÇÂ¼ºÅ¶ÁÈ¡µ¥Ìõ¼ÇÂ¼
* @param [in] pszFileName ¼ÇÂ¼ÎÄ¼şÃû³Æ
* @param [in] nRecNo      Òª¶ÁÈ¡µÄ¼ÇÂ¼ºÅ
* @param [out] psRec      ¼ÇÂ¼Ö¸Õë
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubReadOneRec(const char *pszFileName, const int nRecNo, char *psRec);

/**
* @brief °´Ë÷Òı²éÕÒ¼ÇÂ¼¡£¸ù¾İË÷Òı×Ö¶Î1/Ë÷Òı×Ö¶Î2´ÓÖ¸¶¨µÄ¼ÇÂ¼ºÅ¿ªÊ¼²éÕÒ¼ÇÂ¼£¬ÈôÍ¬Ê±Ö¸¶¨Ë÷Òı×Ö¶Î1/Ë÷Òı×Ö¶Î2£¬ÔòÒªÍ¬Ê±Âú×ãÕâÁ½¸öÌõ¼şµÄ¼ÇÂ¼Êä³ö£¬²»Ö¸¶¨Ê±ÓÃNULL,Èô·ûºÏË÷ÒıÌõ¼şµÄ¼ÇÂ¼´æÔÚÖØ¸´µÄÇé¿ö£¬Êä³öµÚÒ»Ìõ¼ÇÂ¼
* @param [in] pszFileName ¼ÇÂ¼ÎÄ¼şÃû³Æ
* @param [in] psIndexStr1 Ë÷Òı×Ö¶Î1
* @param [in] psIndexStr2 Ë÷Òı×Ö¶Î2
* @param [in] nBeginRecNo Ö¸¶¨µÄ¿ªÊ¼¼ÇÂ¼ºÅ
* @param [out] psRec ¼ÇÂ¼Ö¸Õë
* @param [out] pnRecNo ·ûºÏÌõ¼şµÄ¼ÇÂ¼ºÅ
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubFindRec(const char *pszFileName, const char *psIndexStr1, const char *psIndexStr2,const int nBeginRecNo, char *psRec, int *pnRecNo);

/**
* @brief °´Ë÷ÒıÉ¾³ı¼ÇÂ¼¡£¸ù¾İË÷Òı×Ö¶Î1/Ë÷Òı×Ö¶Î2´ÓÖ¸¶¨µÄ¼ÇÂ¼ºÅ¿ªÊ¼²éÕÒ¼ÇÂ¼£¬ÈôÍ¬Ê±Ö¸¶¨Ë÷Òı×Ö¶Î1/Ë÷Òı×Ö¶Î2£¬ÔòÉ¾³ıÍ¬Ê±Âú×ãÕâÁ½¸öÌõ¼şµÄ¼ÇÂ¼£¬²»Ö¸¶¨Ê±ÓÃNULL,Èô·ûºÏË÷ÒıÌõ¼şµÄ¼ÇÂ¼´æÔÚÖØ¸´µÄÇé¿ö£¬É¾³ıµÚÒ»Ìõ¼ÇÂ¼
* @param [in] pszFileName ¼ÇÂ¼ÎÄ¼şÃû³Æ
* @param [in] psIndexStr1 Ë÷Òı×Ö¶Î1
* @param [in] psIndexStr2 Ë÷Òı×Ö¶Î2
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubDelRec(const char *pszFileName, const char *psIndexStr1,  const char *psIndexStr2);

/**
* @brief ´íÎóÂëµÄ¼ÇÂ¼¼°´íÎóÈÕÖ¾µÄ´¦Àí
* @param [in] nErrorCode     ´íÎóÖµ
* @param [in] pszLogFileName LogÎÄ¼şÃû,ÎªNULL²»¼ÇÂ¼ÎÄ¼ş
* @param [in] pszMoudleName  Ä£¿éÃû
* @param [in] nLine          ĞĞÊı£¬µ÷ÓÃÕßÊ¹ÓÃ__LINE__
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubErrLog (const int nErrorCode, const char *pszLogFileName, char *pszMoudleName, int nLine );

/**
* @brief µÃµ½iniÎÄ¼şÖĞÖ¸¶¨µÄ¶ÎºÍÏîÖ¸¶¨µÄ×Ö·û´®
* @param [in] nHandle     INIÎÄ¼ş¾ä±ú
* @param [in] psSeg       ¶ÎÖ¸Õë
* @param [in] psItem      ÏîÖ¸Õë
* @param [in] nMaxStrLen  ×î´óÔÊĞíµÄÊä³ö×Ö·û´®³¤¶È
* @param [out] pcValueStr µÃµ½µÄ×Ö·û´®ÖµÖ¸Õë
* @param [out] pnValueLen µÃµ½µÄ×Ö·û´®³¤¶È
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubGetINIItemStr (const int nHandle, const char *psSeg, const char *psItem, const int nMaxStrLen, char *psValueStr, int *pnValueLen);

/**
* @brief µÃµ½iniÎÄ¼şÖĞÖ¸¶¨µÄ¶ÎºÍÏîÖ¸¶¨µÄÖµ
* @param [in] nHandle  INIÎÄ¼ş¾ä±ú
* @param [in] psSeg    ¶ÎÖ¸Õë
* @param [in] psItem   ÏîÖ¸Õë
* @param [out] pnValue µÃµ½µÄÖµÖ¸Õë
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubGetINIItemInt (const int nHandle,const char *psSeg, const char *psItem, int *pnValue);

/**
* @brief °´Ö¸¶¨µÄIDÑ°ÕÒÖ¸¶¨µÄÏîÄ¿Öµ£¬ĞèÖ¸¶¨²ÎÊıÎÄ¼şµÄÓĞĞ§ÄÚÈİ¿ªÊ¼Î»ÖÃ
* @param [in] pnHandle      ²ÎÊıÎÄ¼ş¾ä±ú
* @param [in] nPosition     ²ÎÊıÎÄ¼şÓĞĞ§ÄÚÈİ¿ªÊ¼Î»ÖÃ
* @param [in] psID          ÒªÕÒµÄIDÏî×Ö·û´®Ö¸Õë
* @param [out] psParamValue ÕÒµ½µÄIDÏîÖµÖ¸Õë
* @param [out] pnParamLen   ÕÒµ½µÄIDÏîÖµ³¤¶ÈÖ¸Õë
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubFindParam (const int pnHandle, const int nPosition, const char *psID, char *psParamValue, int *pnParamLen);

/**
* @brief É¾³ıÖ¸¶¨µÄ²ÎÊıÎÄ¼ş£¬ÃæÏòÄ¿Ç°ÒøÁªtmsÔ¶³ÌÏÂÔØÖĞµÄÌØ¶¨¸ñÊ½µÄ²ÎÊıÎÄ¼ş»òÕßÊÇINIÎÄ¼ş
* @param [in] pszFileName ²ÎÊıÎÄ¼şÃû
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @date 2012-06-19
*/
int PubDelFile (const char *pszFileName);

/**
* @brief »ñÈ¡×Ö·ûÔÚ×Ö·û´®ÖĞµÄÎ»ÖÃ
* @param [in] pszData     ---×Ö·û´®
* @param [in] cSubChar    ---×Ö·û
* @return 
* @li APP_FAIL  ---²»´æÔÚ
* @li >=0   ---ÔÚ×Ö·û´®ÖĞÎ»ÖÃÖµ
* @author Áõî¸
* @date 2012-7-23
*/
int PubPosChar(const char *pszData,char cSubChar);

/**
* @brief »ñÈ¡×Ó×Ö·û´®ÔÚ×Ö·û´®ÖĞµÄÎ»ÖÃ
* @param [in] pszData     ---×Ö·û´®
* @param [in] pszSub      ---×Ó×Ö·û´®
* @return 
* @li APP_FAIL  ---²»´æÔÚ
* @li >=0   ---ÔÚ×Ö·û´®ÖĞÎ»ÖÃÖµ
* @author Áõî¸
* @date 2012-7-23
*/
int PubPosStr(const char *pszData,const char *pszSub);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef BOOL
typedef unsigned char BOOL;
#endif

#define MAX_FIELD_LEN 1024		/**<Ã¿¸öÓòµÄ×î´ó³¤¶È*/
#define MAX_MSG_LEN 4096		/**<±¨ÎÄ×î´ó³¤¶È */

typedef enum 
{	/**<Óò¶ÔÆë·½Ê½ */
    ALIGN_TYPE_LEFT   = 0,
    ALIGN_TYPE_RIGHT  = 1
}EM_ALIGN_TYPE;

typedef enum 
{	/**<³¤¶ÈÀàĞÍ */
    LENGTH_TYPE_FIX    = 0,
    LENGTH_TYPE_LLVAR  = 1,
    LENGTH_TYPE_LLLVAR = 2
} EM_LENGTH_TYPE;

typedef struct STISO_FIELD STISO_FIELD;
typedef struct STISO_FIELD_DEF STISO_FIELD_DEF;

/**
* @brief ¶Ô8583Óò½øĞĞ´ò°ü£¬²¢·µ»Ø´ò°üºóµÄÊı¾İºÍ³¤¶È
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pfieldbuf		½«Òª´ò°üµÄ8583ÓòÊı¾İÖ¸Õë
* @param [in] fieldlen		½«Òª´ò°üµÄ8583ÓòÊı¾İ³¤¶È
* @param [out] poutdata		ÓÃÓÚ½ÓÊÕ¼ÆËãºóµÄÊı¾İµÄ»º³åÇø
* @return 
* @li	´ò°üºóµÄÊı¾İ³¤¶È
*/
typedef int (*FIELD_PACKAGER_PACK) (STISO_FIELD_DEF *pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief ½«»º³åÇøÀïÃæµÄÊı¾İ½â°üµ½8583ÓòÖĞ
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pindata		º¬ÓĞ¸ÃÓò±¨ÎÄµÄÊı¾İ»º³åÇø
* @param [out] pfieldbuf	½â°üºóµÄ8583ÓòÊı¾İ»º³åÇø
* @param [out] pfieldlen	·µ»ØÓòÊı¾İ³¤¶È
* @return 
* @li	½â°üÊ±´ÓpindataÖĞÊ¹ÓÃµÄÊı¾İ³¤¶È
*/
typedef int (*FIELD_PACKAGER_UNPACK) (STISO_FIELD_DEF *pthis, unsigned char *pfieldbuf, int *pfieldlen, unsigned char *pindata);

/**
* @brief ¸ù¾İISOÓòµÄÀàĞÍ¼ÆËã8583±¨ÎÄÖĞµÄ³¤¶È×Ö½Ú
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] len			ÓòÊı¾İµÄ³¤¶È
* @param [out] poutdata		ÓÃÓÚ½ÓÊÕ¼ÆËãºóµÄÊı¾İµÄ»º³åÇø 
* @param [out] pcount		³¤¶È×Ö½ÚÊı£¨¶¨³¤Îª0£¬LLVARĞÍÎª1£¬LLLVARĞÍÎª2£©
* @return 
* @li	ÎŞ
*/
typedef void (*FIELD_LENGTH_SET) (STISO_FIELD_DEF *pthis, int len, unsigned char *poutdata, int *pcount);

/**
* @brief ¸ù¾İISOÓòµÄÀàĞÍºÍ8583±¨ÎÄÖĞµÄ³¤¶È×Ö½Ú£¬¼ÆËã±¨ÎÄÖĞÓòµÄ³¤¶È
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pindata		º¬¸ÃÓò±¨ÎÄµÄÊı¾İÖ¸Õë
* @param [out] plen			ÓÃÓÚ½ÓÊÕ¼ÆËãºóµÄ³¤¶È
* @param [out] pcount		³¤¶È×Ö½ÚÊı£¨¶¨³¤Îª0£¬LLVARĞÍÎª1£¬LLLVARĞÍÎª2£©
* @return 
* @li	ÎŞ
*/
typedef void (*FIELD_LENGTH_GET) (STISO_FIELD_DEF *pthis, unsigned char *pindata, int *plen, int *pcount);

struct STISO_FIELD_LENGTH_CALC
{	/**< ISO 8583 Êı¾İÓò³¤¶È¼ÆËãº¯Êı½á¹¹ */
    FIELD_LENGTH_SET	pSet;		/**< ÉèÖÃ³¤¶ÈÊ±µ÷ÓÃµÄº¯Êı */
    FIELD_LENGTH_GET	pGet;		/**< È¡³ö³¤¶ÈÊ±µ÷ÓÃµÄº¯Êı */
}; 

struct STISO_FIELD
{	/**< ISO 8583 Êı¾İÓò½á¹¹ */
    int    nLen;
    int    nOff;					/**< Ö¸Ïòiso->databuf»º³åÇøµÄÆ«ÒÆ£¬Êı¾İÖĞ²»º¬³¤¶ÈÀàĞÍµÄ¼¸¸ö×Ö½Ú */
};

struct STISO_FIELD_DEF
{	/**< ISO 8583 Êı¾İÓò¶¨Òå */
    int                     nLen;			/**< Êı¾İÓò×î´ó³¤¶È */
    EM_LENGTH_TYPE		    lentype;		/**< Êı¾İÓò³¤¶ÈÀàĞÍ: 1--LLVARĞÍ 2--LLLVARĞÍ */
    EM_ALIGN_TYPE           align;			/**< ¶ÔÆëÀàĞÍ */
    char                    cPadchar;		/**< ²¹Æë×Ö·û */	
    FIELD_PACKAGER_PACK		pPack;			/**< ´ò°üº¯ÊıÖ¸Õë */
    FIELD_PACKAGER_UNPACK	pUnpack;		/**< ½â°üº¯ÊıÖ¸Õë */
};  


typedef struct STISODataStru
{	/**< ISO 8583 ±¨ÎÄ½á¹¹¶¨Òå */
    STISO_FIELD		fld[256];
    char			sBitmap[256];
    unsigned char 	szDatabuf[MAX_MSG_LEN + MAX_FIELD_LEN];		/**< ¶àÁôÒ»¸öÓòµÄ³¤¶È£¬·ÀÖ¹Òç³ö */
    int        		nUsed;
} STISODataStru;

/**
* @brief ¸ù¾İISOÓòµÄÀàĞÍ¼ÆËã8583±¨ÎÄÖĞµÄ³¤¶È×Ö½Ú(ASCĞÎÊ½)¡£ASCÂëĞÎÊ½£¬Èç³¤¶È104£¬½«±íÊ¾Îª 0x31, 0x30, 0x34,¹²3¸ö×Ö½Ú, Èç¹ûÊÇ9½«±íÊ¾Îª0x30, 0x39Á½¸ö×Ö½Ú
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] nLen			ÓòÊı¾İµÄ³¤¶È
* @param [out] poutdata		ÓÃÓÚ½ÓÊÕ¼ÆËãºóµÄÊı¾İµÄ»º³åÇø
* @param [out] pcount		³¤¶È×Ö½ÚÊı£¨¶¨³¤Îª0£¬LLVARĞÍÎª1£¬LLLVARĞÍÎª2£©
* @return 
* @li ÎŞ
*/
void PubFLALengthSet(STISO_FIELD_DEF *pthis, int len, unsigned char *poutdata, int *pcount);

/**
* @brief ¸ù¾İISOÓòµÄÀàĞÍºÍ8583±¨ÎÄÖĞµÄ³¤¶È×Ö½Ú£¬¼ÆËã±¨ÎÄÖĞÓòµÄ³¤¶È(ASCĞÎÊ½)¡£ASCÂëĞÎÊ½£¬Èç³¤¶È104£¬½«±íÊ¾Îª 0x31, 0x30, 0x34,¹²3¸ö×Ö½Ú, Èç¹ûÊÇ9½«±íÊ¾Îª0x30, 0x39Á½¸ö×Ö½Ú
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pindata		º¬¸ÃÓò±¨ÎÄµÄÊı¾İÖ¸Õë
* @param [out] plen			ÓÃÓÚ½ÓÊÕ¼ÆËãºóµÄ³¤¶È
* @param [out] pcount		³¤¶È×Ö½ÚÊı£¨¶¨³¤Îª0£¬LLVARĞÍÎª1£¬LLLVARĞÍÎª2£©
* @return 
* @li ÎŞ
*/
void PubFLALengthGet(STISO_FIELD_DEF *pthis, unsigned char *pindata, int *plen, int *pcount);

/**
* @brief ¸ù¾İISOÓòµÄÀàĞÍ¼ÆËã8583±¨ÎÄÖĞµÄ³¤¶È×Ö½Ú(BCDĞÎÊ½)¡£BCDÂëĞÎÊ½£¬Èç³¤¶È104£¬½«±íÊ¾Îª 0x01, 0x04,¹²2¸ö×Ö½Ú, Èç¹ûÊÇ9½«±íÊ¾Îª0x09,¹²1¸ö×Ö½Ú
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] nLen			ÓòÊı¾İµÄ³¤¶È
* @param [out] poutdata		ÓÃÓÚ½ÓÊÕ¼ÆËãºóµÄÊı¾İµÄ»º³åÇø
* @param [out] pcount		³¤¶È×Ö½ÚÊı£¨¶¨³¤Îª0£¬LLVARĞÍÎª1£¬LLLVARĞÍÎª2£©
* @return 
* @li ÎŞ
*/
void PubFLBLengthSet(STISO_FIELD_DEF *pthis, int len, unsigned char *poutdata, int *pcount);

/**
* @brief ¸ù¾İISOÓòµÄÀàĞÍºÍ8583±¨ÎÄÖĞµÄ³¤¶È×Ö½Ú£¬¼ÆËã±¨ÎÄÖĞÓòµÄ³¤¶È(BCDĞÎÊ½)¡£BCDÂëĞÎÊ½£¬Èç³¤¶È104£¬½«±íÊ¾Îª 0x01, 0x04,¹²2¸ö×Ö½Ú, Èç¹ûÊÇ9½«±íÊ¾Îª0x09,¹²1¸ö×Ö½Ú
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pindata		º¬¸ÃÓò±¨ÎÄµÄÊı¾İÖ¸Õë
* @param [out] plen			ÓÃÓÚ½ÓÊÕ¼ÆËãºóµÄ³¤¶È
* @param [out] pcount		³¤¶È×Ö½ÚÊı£¨¶¨³¤Îª0£¬LLVARĞÍÎª1£¬LLLVARĞÍÎª2£©
* @return 
* @li ÎŞ
*/
void PubFLBLengthGet(STISO_FIELD_DEF *pthis, unsigned char *pindata, int *plen, int *pcount);

/**
* @brief ¸ù¾İISOÓòµÄÀàĞÍ¼ÆËã8583±¨ÎÄÖĞµÄ³¤¶È×Ö½Ú(HEXĞÎÊ½)¡£HEXÂëĞÎÊ½£¬Èç³¤¶È104£¬½«±íÊ¾Îª 0x00, 0x68,¹²2¸ö×Ö½Ú, Èç¹ûÊÇ9½«±íÊ¾Îª0x09,¹²1¸ö×Ö½Ú
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] nLen			ÓòÊı¾İµÄ³¤¶È
* @param [out] poutdata		ÓÃÓÚ½ÓÊÕ¼ÆËãºóµÄÊı¾İµÄ»º³åÇø
* @param [out] pcount		³¤¶È×Ö½ÚÊı£¨¶¨³¤Îª0£¬LLVARĞÍÎª1£¬LLLVARĞÍÎª2£©
* @return 
* @li ÎŞ
*/
void PubFLHLengthSet(STISO_FIELD_DEF *pthis, int len, unsigned char *poutdata, int *pcount);

/**
* @brief ¸ù¾İISOÓòµÄÀàĞÍºÍ8583±¨ÎÄÖĞµÄ³¤¶È×Ö½Ú£¬¼ÆËã±¨ÎÄÖĞÓòµÄ³¤¶È(HEXĞÎÊ½)¡£HEXÂëĞÎÊ½£¬Èç³¤¶È104£¬½«±íÊ¾Îª 0x00, 0x68,¹²2¸ö×Ö½Ú, Èç¹ûÊÇ9½«±íÊ¾Îª0x09,¹²1¸ö×Ö½Ú
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pindata		º¬¸ÃÓò±¨ÎÄµÄÊı¾İÖ¸Õë
* @param [out] plen			ÓÃÓÚ½ÓÊÕ¼ÆËãºóµÄ³¤¶È
* @param [out] pcount		³¤¶È×Ö½ÚÊı£¨¶¨³¤Îª0£¬LLVARĞÍÎª1£¬LLLVARĞÍÎª2£©
* @return 
* @li ÎŞ
*/
void PubFLHLengthGet(STISO_FIELD_DEF *pthis, unsigned char *pindata, int *plen, int *pcount);

/**
* @brief ÎªÒ»¸öISOÓòµÄÊı¾İ½øĞĞ´ò°ü£¨MSG_IDÓòASCÂëĞÎÊ½£©¡£
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pfieldbuf		½«Òª´ò°üµÄ8583ÓòÊı¾İÖ¸Õë
* @param [in] nFieldlen		½«Òª´ò°üµÄ8583ÓòÊı¾İ³¤¶È
* @param [out] poutdata		ÓÃÓÚ½ÓÊÕ¼ÆËãºóµÄÊı¾İµÄ»º³åÇø
* @return 
* @li ´ò°üºóµÄÊı¾İ³¤¶È
*/
int PubFPAMsgIDPack(STISO_FIELD_DEF * pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief ÎªÒ»¸öISOÓòµÄÊı¾İ½øĞĞ½â°ü£¨MSG_IDÓòASCÂëĞÎÊ½£©
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pindata		º¬ÓĞ¸ÃÓò±¨ÎÄµÄÊı¾İ»º³åÇø
* @param [out] pfieldbuf	½â°üºóµÄ8583ÓòÊı¾İ»º³åÇø
* @param [out] pfieldlen	·µ»ØÓòÊı¾İ³¤¶È
* @return 
* @li ½â°üÊ±´ÓpindataÖĞÊ¹ÓÃµÄÊı¾İ³¤¶È
*/
int PubFPAMsgIDUnpack(STISO_FIELD_DEF * pthis, unsigned char *pfieldbuf, int  *pfieldlen, unsigned char *pindata);

/**
* @brief ÎªÒ»¸öISOÓòµÄÊı¾İ½øĞĞ´ò°ü£¨MSG_IDÓòBCDÂëĞÎÊ½£©
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pfieldbuf		½«Òª´ò°üµÄ8583ÓòÊı¾İÖ¸Õë
* @param [in] nFieldlen		½«Òª´ò°üµÄ8583ÓòÊı¾İ³¤¶È
* @param [out] poutdata		ÓÃÓÚ½ÓÊÕ¼ÆËãºóµÄÊı¾İµÄ»º³åÇø
* @return 
* @li ´ò°üºóµÄÊı¾İ³¤¶È
*/
int PubFPBMsgIDpack(STISO_FIELD_DEF * pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief ÎªÒ»¸öISOÓòµÄÊı¾İ½øĞĞ½â°ü£¨MSG_IDÓòBCDÂëĞÎÊ½£©
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pindata		º¬ÓĞ¸ÃÓò±¨ÎÄµÄÊı¾İ»º³åÇø
* @param [out] pfieldbuf		½â°üºóµÄ8583ÓòÊı¾İ»º³åÇø
* @param [out] pfieldlen		·µ»ØÓòÊı¾İ³¤¶È
* @return 
* @li ½â°üÊ±´ÓpindataÖĞÊ¹ÓÃµÄÊı¾İ³¤¶È
*/
int PubFPBMsgIDUnpack(STISO_FIELD_DEF * pthis, unsigned char *pfieldbuf, int *pfieldlen, unsigned char *pindata);

/**
* @brief ÎªÒ»¸öISOÓòµÄÊı¾İ½øĞĞ´ò°ü£¨BITMAPÎ»Í¼ÓòBCDÂëĞÎÊ½£©
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pfieldbuf		½«Òª´ò°üµÄ8583ÓòÊı¾İÖ¸Õë
* @param [in] nFieldlen		½«Òª´ò°üµÄ8583ÓòÊı¾İ³¤¶È
* @param [out] poutdata		ÓÃÓÚ½ÓÊÕ¼ÆËãºóµÄÊı¾İµÄ»º³åÇø
* @return 
* @li ´ò°üºóµÄÊı¾İ³¤¶È
*/
int PubFPABitmapPack(STISO_FIELD_DEF * pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief ÎªÒ»¸öISOÓòµÄÊı¾İ½øĞĞ½â°ü£¨BITMAPÎ»Í¼ÓòBCDÂëĞÎÊ½£©
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pindata		º¬ÓĞ¸ÃÓò±¨ÎÄµÄÊı¾İ»º³åÇø
* @param [out] pfieldbuf	½â°üºóµÄ8583ÓòÊı¾İ»º³åÇø
* @param [out] pfieldlen	·µ»ØÓòÊı¾İ³¤¶È
* @return 
* @li ½â°üÊ±´ÓpindataÖĞÊ¹ÓÃµÄÊı¾İ³¤¶È
*/
int PubFPABitmapUnPack(STISO_FIELD_DEF * pthis, unsigned char *pfieldbuf, int *pfieldlen, unsigned char *pindata);

/**
* @brief ÎªÒ»¸öISOÓòµÄÊı¾İ½øĞĞ´ò°ü£¨BITMAPÎ»Í¼ÓòASCÂëĞÎÊ½£©
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pfieldbuf		½«Òª´ò°üµÄ8583ÓòÊı¾İÖ¸Õë
* @param [in] nFieldlen		½«Òª´ò°üµÄ8583ÓòÊı¾İ³¤¶È
* @param [out] poutdata		ÓÃÓÚ½ÓÊÕ¼ÆËãºóµÄÊı¾İµÄ»º³åÇø
* @return 
* @li ´ò°üºóµÄÊı¾İ³¤¶È
*/
int PubFPBBitmapPack(STISO_FIELD_DEF * pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief ÎªÒ»¸öISOÓòµÄÊı¾İ½øĞĞ½â°ü£¨BITMAPÎ»Í¼ÓòASCÂëĞÎÊ½£©
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pindata		º¬ÓĞ¸ÃÓò±¨ÎÄµÄÊı¾İ»º³åÇø
* @param [out] pfieldbuf	½â°üºóµÄ8583ÓòÊı¾İ»º³åÇø
* @param [out] pfieldlen	·µ»ØÓòÊı¾İ³¤¶È
* @return 
* @li ½â°üÊ±´ÓpindataÖĞÊ¹ÓÃµÄÊı¾İ³¤¶È
*/
int PubFPBBitmapUnPack(STISO_FIELD_DEF * pthis, unsigned char *pfieldbuf, int *pfieldlen, unsigned char *pindata);

/**
* @brief ÎªÒ»¸öISOÓòµÄÊı¾İ½øĞĞ´ò°ü£¨×Ö·ûÀàĞÍÓòASCÂëĞÎÊ½£©
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pfieldbuf		½«Òª´ò°üµÄ8583ÓòÊı¾İÖ¸Õë
* @param [in] nFieldlen		½«Òª´ò°üµÄ8583ÓòÊı¾İ³¤¶È
* @param [out] poutdata		ÓÃÓÚ½ÓÊÕ¼ÆËãºóµÄÊı¾İµÄ»º³åÇø
* @return 
* @li ´ò°üºóµÄÊı¾İ³¤¶È
*/
int PubFPACharPack(STISO_FIELD_DEF * pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief ÎªÒ»¸öISOÓòµÄÊı¾İ½øĞĞ½â°ü£¨×Ö·ûÀàĞÍÓòASCÂëĞÎÊ½£©
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pindata		º¬ÓĞ¸ÃÓò±¨ÎÄµÄÊı¾İ»º³åÇø
* @param [out] pfieldbuf	½â°üºóµÄ8583ÓòÊı¾İ»º³åÇø
* @param [out] pfieldlen	·µ»ØÓòÊı¾İ³¤¶È
* @return 
* @li ½â°üÊ±´ÓpindataÖĞÊ¹ÓÃµÄÊı¾İ³¤¶È
*/
int PubFPACharUnPack(STISO_FIELD_DEF * pthis, unsigned char *pfieldbuf, int *pfieldlen, unsigned char *pindata);

/**
* @brief ÎªÒ»¸öISOÓòµÄÊı¾İ½øĞĞ´ò°ü£¨×Ö·ûÀàĞÍÓòBCDÂëĞÎÊ½£©
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pfieldbuf		½«Òª´ò°üµÄ8583ÓòÊı¾İÖ¸Õë
* @param [in] pfieldbuf		½«Òª´ò°üµÄ8583ÓòÊı¾İ³¤¶È
* @param [out] poutdata		ÓÃÓÚ½ÓÊÕ¼ÆËãºóµÄÊı¾İµÄ»º³åÇø
* @return 
* @li ´ò°üºóµÄÊı¾İ³¤¶È
*/
int PubFPBCharPack(STISO_FIELD_DEF * pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief ÎªÒ»¸öISOÓòµÄÊı¾İ½øĞĞ½â°ü£¨×Ö·ûÀàĞÍÓòBCDÂëĞÎÊ½£©
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pindata		º¬ÓĞ¸ÃÓò±¨ÎÄµÄÊı¾İ»º³åÇø
* @param [out] pfieldbuf	½â°üºóµÄ8583ÓòÊı¾İ»º³åÇø
* @param [out] pfieldlen	·µ»ØÓòÊı¾İ³¤¶È
* @return 
* @li ½â°üÊ±´ÓpindataÖĞÊ¹ÓÃµÄÊı¾İ³¤¶È
*/
int PubFPBCharUnPack(STISO_FIELD_DEF * pthis, unsigned char *pfieldbuf, int *pfieldlen, unsigned char *pindata);

/**
* @brief ÎªÒ»¸öISOÓòµÄÊı¾İ½øĞĞ´ò°ü£¨Êı×ÖÀàĞÍÓòASCÂëĞÎÊ½£©
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pfieldbuf		½«Òª´ò°üµÄ8583ÓòÊı¾İÖ¸Õë
* @param [in] nFieldlen		½«Òª´ò°üµÄ8583ÓòÊı¾İ³¤¶È
* @param [out] poutdata		ÓÃÓÚ½ÓÊÕ¼ÆËãºóµÄÊı¾İµÄ»º³åÇø
* @return 
* @li ´ò°üºóµÄÊı¾İ³¤¶È
*/
int PubFPADigitPack(STISO_FIELD_DEF * pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief ÎªÒ»¸öISOÓòµÄÊı¾İ½øĞĞ½â°ü£¨Êı×ÖÀàĞÍÓòASCÂëĞÎÊ½£©
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pindata		º¬ÓĞ¸ÃÓò±¨ÎÄµÄÊı¾İ»º³åÇø
* @param [out] pfieldbuf	½â°üºóµÄ8583ÓòÊı¾İ»º³åÇø
* @param [out] pfieldlen	·µ»ØÓòÊı¾İ³¤¶È
* @return 
* @li ½â°üÊ±´ÓpindataÖĞÊ¹ÓÃµÄÊı¾İ³¤¶È
*/
int PubFPADigitUnPack(STISO_FIELD_DEF * pthis, unsigned char *pfieldbuf, int *pfieldlen, unsigned char *pindata);

/**
* @brief ÎªÒ»¸öISOÓòµÄÊı¾İ½øĞĞ´ò°ü£¨Êı×ÖÀàĞÍÓòBCDÂëĞÎÊ½£©
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pfieldbuf		½«Òª´ò°üµÄ8583ÓòÊı¾İÖ¸Õë
* @param [in] nFieldlen		½«Òª´ò°üµÄ8583ÓòÊı¾İ³¤¶È
* @param [out] poutdata		ÓÃÓÚ½ÓÊÕ¼ÆËãºóµÄÊı¾İµÄ»º³åÇø
* @return 
* @li ´ò°üºóµÄÊı¾İ³¤¶È
*/
int PubFPBDigitPack(STISO_FIELD_DEF * pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief ÎªÒ»¸öISOÓòµÄÊı¾İ½øĞĞ½â°ü£¨Êı×ÖÀàĞÍÓòBCDÂëĞÎÊ½£©
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pindata		º¬ÓĞ¸ÃÓò±¨ÎÄµÄÊı¾İ»º³åÇø
* @param [out] pfieldbuf	½â°üºóµÄ8583ÓòÊı¾İ»º³åÇø
* @param [out] pfieldlen	·µ»ØÓòÊı¾İ³¤¶È
* @return 
* @li ½â°üÊ±´ÓpindataÖĞÊ¹ÓÃµÄÊı¾İ³¤¶È
*/
int PubFPBDigitUnPack(STISO_FIELD_DEF * pthis, unsigned char *pfieldbuf, int *pfieldlen, unsigned char *pindata);

/**
* @brief ÎªÒ»¸öISOÓòµÄÊı¾İ½øĞĞ´ò°ü£¨½ğ¶îÀàĞÍÓòASCÂëĞÎÊ½£©
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pfieldbuf		½«Òª´ò°üµÄ8583ÓòÊı¾İÖ¸Õë
* @param [in] nFieldlen		½«Òª´ò°üµÄ8583ÓòÊı¾İ³¤¶È
* @param [out] poutdata		ÓÃÓÚ½ÓÊÕ¼ÆËãºóµÄÊı¾İµÄ»º³åÇø
* @return 
* @li ´ò°üºóµÄÊı¾İ³¤¶È
*/
int PubFPBAmountPack(STISO_FIELD_DEF * pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief ÎªÒ»¸öISOÓòµÄÊı¾İ½øĞĞ½â°ü£¨½ğ¶îÀàĞÍÓòASCÂëĞÎÊ½£©
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pindata		º¬ÓĞ¸ÃÓò±¨ÎÄµÄÊı¾İ»º³åÇø
* @param [out] pfieldbuf	½â°üºóµÄ8583ÓòÊı¾İ»º³åÇø
* @param [out] pfieldlen	·µ»ØÓòÊı¾İ³¤¶È
* @return 
* @li ½â°üÊ±´ÓpindataÖĞÊ¹ÓÃµÄÊı¾İ³¤¶È
*/
int PubFPBAmountUnPack(STISO_FIELD_DEF * pthis, unsigned char *pfieldbuf, int *pfieldlen, unsigned char *pindata);

/**
* @brief ÎªÒ»¸öISOÓòµÄÊı¾İ½øĞĞ´ò°ü£¨¶ş½øÖÆÀàĞÍÓòBCDÂëĞÎÊ½£©
* @param [in] pthis			ISOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pfieldbuf		½«Òª´ò°üµÄ8583ÓòÊı¾İÖ¸Õë
* @param [in] nFieldlen		½«Òª´ò°üµÄ8583ÓòÊı¾İ³¤¶È
* @param [out] poutdata		ÓÃÓÚ½ÓÊÕ¼ÆËãºóµÄÊı¾İµÄ»º³åÇø
* @return 
* @li ´ò°üºóµÄÊı¾İ³¤¶È
*/
int PubFPBBinaryPack(STISO_FIELD_DEF * pthis, const unsigned char *pfieldbuf, int fieldlen, unsigned char *poutdata);

/**
* @brief ÎªÒ»¸öISOÓòµÄÊı¾İ½øĞĞ½â°ü£¨¶ş½øÖÆÀàĞÍÓòBCDÂëĞÎÊ½£©
* @param [in] pthis			SOÓò¶¨ÒåµÄÀàĞÍ½á¹¹Ö¸Õë
* @param [in] pindata		º¬ÓĞ¸ÃÓò±¨ÎÄµÄÊı¾İ»º³åÇø
* @param [out] pfieldbuf	½â°üºóµÄ8583ÓòÊı¾İ»º³åÇø
* @param [out] pfieldlen	·µ»ØÓòÊı¾İ³¤¶È
* @return 
* @li ½â°üÊ±´ÓpindataÖĞÊ¹ÓÃµÄÊı¾İ³¤¶È
*/
int PubFPBBinaryUnPack(STISO_FIELD_DEF * pthis, unsigned char *pfieldbuf, int *pfieldlen, unsigned char *pindata);

/**
* @brief ×ª»»×Ö·û´®ÎªISO½á¹¹
* @param [in] pcSourceStr		×ª»»µÄÔ´×Ö·û´®
* @param [in] nStrLen			Êı¾İ³¤¶È
* @param [out] pTargetIsoStru	×ª»»µÄ½á¹ûISO½á¹¹
* @param [out] pnPosition		´«ÈëÎªNULLÊ±£¬ºöÂÔ;·ñÔò´æ·Å×ª»»³ö´íÊ±µÄÓò±àºÅ£¨½ö¶Ô·µ»ØERRFIELDLENÊ±ÓĞĞ§£©£¬ÆäÓàÇé¿öÏÂ¾ùÎª-1
* @return 
* @li APP_FAIL		×ª»»Ê§°Ü£¬pcSourceStr»òÕßTargetIsoStruÎª¿Õ£¬½â°ü³ö´í
* @li APP_APP_SUCC	×ª»»³É¹¦
*/
int PubStrToIso(char *pcSourceStr, int nStrLen, STISODataStru *pTargetIsoStru, int *pnPosition);

/**
* @brief ½«ISO½á¹¹×ª»»³ÉÎŞ·ûºÅ×Ö·û´®
* @param [in] pSourceIsoStru	×ª»»µÄÔ´Êı¾İ½á¹¹
* @param [in] pnLen				´«ÈëpcTargetStrµÄ¿Õ¼ä´óĞ¡£¨°üº¬½áÊø·û£©
* @param [out] pcTargetStr		×ª»»µÄ½á¹û×Ö·û´®(BCDÂë)
* @param [out] pnLen			´æ·Å×ª»»³É¹¦ºóµÄ×Ö·û´®³¤¶È£¬Èç¹ûÊ§°Ü£¬³¤¶ÈÎª-1¡£
* @return 
* @li APP_FAIL		×ª»»Ê§°Ü£¬pcTargetStr»òÕßpSourceIsoStruÎª¿Õ£¬´ò°üÊ§°Ü
* @li APP_APP_SUCC	×ª»»³É¹¦
*/
int PubIsoToStr(char *pcTargetStr, STISODataStru *SourceIsoStru, int *pnLen);

/**
* @brief ½«½á¹¹ISOÖĞÖ¸¶¨³ÉÔ±ÌáÈ¡µ½×Ö·û´®szTargetStrÖĞ
* @param [in] pSourceIsoStru	Ô´Êı¾İ½á¹¹ISO_data ½á¹¹Ö¸Õë
* @param [in] nPosition			ISO_data½á¹¹ÖĞµÄµÚN¸ö³ÉÔ±
* @param [in] pnLen				´«ÈëÒª×ª»»×Ö´®µÄ¿Õ¼ä´óĞ¡£¨°üº¬½áÎ²·ûºÅ£©
* @param [out] pcTargetStr		Ä¿±ê×Ö·û´®
* @param [out] pnLen			·µ»Ø×ª»»³É¹¦Ê±×Ö·û´®µÄ³¤¶È£¬×ª»»Ê§°ÜÇÒpnLen·Ç¿ÕÊ±Îª-1
* @return 
* @li APP_FAIL		Ê§°Ü,TargetIsoStru»òÕßpcSourceStr»òÕßpnLenÎª¿Õ£¬»òÕßµ÷ÓÃHexToAsc³ö´í£¬»òÕßÖ¸¶¨µÄ³ÉÔ±ÎŞĞ§£¬»òÕß´«ÈëµÄpcSourceStr¿Õ¼ä²»¹»
* @li APP_APP_SUCC	³É¹¦
*/
int PubGetBit(STISODataStru *pSourceIsoStru, int nPosition, char *pcTargetStr, int *pnLen);

/**
* @brief ½«×Ö·û´®pcSourceStr°´Ö¸¶¨³¤¶ÈnStrLenÌî³äµ½½á¹¹TargetIsoStruÖĞÖ¸¶¨³ÉÔ±
* @param [in] nPosition			Ö¸¶¨µÄISO_data½á¹¹ÖĞµÄµÚN¸ö³ÉÔ±
* @param [in] pcSourceStr		´ò°üÊı¾İ
* @param [in] nStrLen			pcSourceStr µÄ³¤¶È
* @param [out] pTargetIsoStru	´ıÌî³äµÄÄ¿±ê½á¹¹ISO_data ½á¹¹µÄÖ¸Õë
* @return 
* @li APP_FAIL		Ê§°Ü£¬TargetIsostru»òÕßpcSourceStrÎªNULL£¬»òÕßÖ¸¶¨µÄ³ÉÔ±ÎŞĞ§£¬»òÕßµ÷ÓÃAscToHex³ö´í£¬»òÕßISO½á¹¹ÀÛ¼Æ³¤¶È³¬¹ıMAXISOLEN
* @li APP_APP_SUCC	ÉèÖÃ³É¹¦»òÕßnStrLen µÈÓÚ0
*/
int PubSetBit(STISODataStru *pTargetIsoStru, int nPosition, char *pcSourceStr, int nStrLen);

/**
* @brief Çå¿ÕISO_data½á¹¹ÖĞËùÓĞ³ÉÔ±±äÁ¿Öµ
* @param [in] pIsoStru		Ô´Êı¾İ½á¹¹ISO_data ½á¹¹Ö¸Õë
* @param [out] pIsoStru		Çå¿ÕºóµÄISO_data½á¹¹Ö¸Õë
* @return 
* @li APP_FAIL		Ê§°Ü£¬IsoStruÎª¿Õ
* @li APP_APP_SUCC	³É¹¦
*/
int PubDelAllBit(STISODataStru *pIsoStru);

/**
* @brief Çå¿ÕIsoStru½á¹¹ÖĞµÚnPositionÓòµÄÖµ£¬Í¬Ê±Çå³ıÎ»Í¼ÖĞµÄÏàÓ¦±êÖ¾
* @param [in] pIsoStru		Ô´Êı¾İ½á¹¹ISO_data ½á¹¹Ö¸Õë
* @param [in] nPosition		ISO_data½á¹¹ÖĞµÄµÚnPosition¸ö³ÉÔ±
* @param [out] pIsoStru		Çå³ıºóµÄISO_data½á¹¹Ö¸Õë
* @return 
* @li APP_FAIL		Ê§°Ü£¬IsoStruÎªNULL£¬»òÕßÎŞĞ§µÄ³ÉÔ±ºÅ£¨nPosition <0 »òÕß >=256£©
* @li APP_APP_SUCC	³É¹¦
*/
int PubDelOneBit(STISODataStru *pIsoStru, int nPosition);

/**
* @brief ÉèÖÃ8583Êı¾İ°ü¶¨Òå
* @param [in] nPosition		ÓòºÅ
* @param [in] nMaxLen		×î´ó³¤¶È
* @param [in] LenType		³¤¶ÈÀàĞÍ
* @param [in] AlignType		¶ÔÆëÀàĞÍ
* @param [in] chPadChar		²¹Æë×Ö·û
* @param [in] PackFunc		´ò°üº¯Êı
* @param [in] UnpackFunc	½â°üº¯Êı
* @return 
* @li APP_FAIL		Ê§°Ü
* @li APP_APP_SUCC	³É¹¦
*/
int PubSetDefine8583(int nPosition, int nMaxLen, EM_LENGTH_TYPE	LenType, EM_ALIGN_TYPE AlignType, char chPadChar, FIELD_PACKAGER_PACK PackFunc, FIELD_PACKAGER_UNPACK UnpackFunc);

/**
* @brief µ¼Èë8583½á¹¹
* @param [in] pNewDef		Òªµ¼ÈëµÄ8583½á¹¹
* @return 
* @li APP_FAIL		Ê§°Ü
* @li APP_APP_SUCC	³É¹¦
*/
int PubImport8583(const struct STISO_FIELD_DEF *pNewDef);

/**
* @brief °´ÓòÏÔÊ¾8583Êı¾İ°üÄÚÈİ
* @param [in] pIsoStru		´ıÏÔÊ¾µÄISO ½á¹¹
* @return 
* @li ÎŞ
*/
void PubFormatDisp8583(STISODataStru *pIsoStru);

/**
* @brief µ¼Èë8583Óò³¤¶È¼ÆËãº¯Êı½á¹¹
* @param [in] pNewCalc		Òªµ¼ÈëµÄ8583Óò³¤¶È¼ÆËãº¯Êı½á¹¹
* @return 
* @li APP_FAIL		Ê§°Ü
* @li APP_APP_SUCC	³É¹¦
*/
int PubSetFieldLengthCalc(const struct STISO_FIELD_LENGTH_CALC *pNewCalc);

/**
* @brief ¸´ÖÆÒ»¸öSTISODataStru½á¹¹
* @param [in] pSourceIsoStru		Ô´ISO_data½á¹¹µÄÖ¸Õë
* @param [out] pTargetIsoStru		´ıÌî³äµÄÄ¿±ê½á¹¹ISO_data ½á¹¹µÄÖ¸Õë
* @return 
* @li APP_FAIL		Ê§°Ü£¬pSourceIsoStru»òÕßpTargetIsoStruÎª¿Õ
* @li APP_APP_SUCC	ÉèÖÃ³É¹¦
*/
int PubCopyIso(STISODataStru *pSourceIsoStru, STISODataStru *pTargetIsoStru);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief Í¨¹ı´®¿Ú1µ¼³öÈÕÖ¾ÎÄ¼ş
* @detail ´®¿Ú£º1,115200
* @param ÎŞ
* @return 
* @li ÎŞ
* @author Áõî¸
* @date 2012-10-24
*/
void PubExportDebugFile();

/**
* @brief Í¨¹ı½«¶ş½øÖÆÊı¾İµ÷ÊÔĞÅÏ¢Êä³ö
* @param [in] pszTitle  --- ±êÌâ
* @param [in] pData     --- Êı¾İ
* @param [in] nLen      --- Êı¾İ³¤¶È
* @return 
* @li ÎŞ
* @author Áõî¸
* @date 2012-10-24
*/
void PubDebugData(const char* pszTitle,const void* pData,int nLen);

/**
* @brief ½«µ÷ÊÔĞÅÏ¢µ¼³ö
* @param [in]  lpszFormat   --- ¸ñÊ½»¯×Ö·û´®
* @return 
* @li ÎŞ
* @author Áõî¸
* @date 2012-10-24
*/
void PubDebug(char* lpszFormat, ...);

/**
* @brief »ñÈ¡¹¤¾ß¿âDebugÄ£Ê½
* @return 
* @li 0:  ·¢²¼Ä£Ê½:ÎŞµ÷ÊÔÊä³ö
* @li 1:  DebugÄ£Ê½  :´®¿ÚÊä³ö
* @li 2:  DebugÄ£Ê½  :ÎÄ¼şÊä³ö
*/
int PubGetDebugMode();


/**
* @brief ´Óµôµç±£»¤ÇøÌáÈ¡Êı¾İ
* @param [out]  psBuf   --- Êı¾İ
* @param [in]  nStart      --- ÆğÊ¼µØÖ·
* @param [in]  nLen        --- Êı¾İ³¤¶È
* @return 
* @li APP_SUCC ³É¹¦
* @li APP_FAIL Ê§°Ü
* @author Áõî¸
* @date 2012-10-24
*/
int PubGetVar (char *psBuf, const int nStart, const int nLen);

/**
* @brief ½«Êı¾İ±£´æµ½µôµç±£»¤Çø
* @param [in]  psSaveBuf   --- Êı¾İ
* @param [in]  nStart      --- ÆğÊ¼µØÖ·
* @param [in]  nLen        --- Êı¾İ³¤¶È
* @return 
* @li APP_SUCC ³É¹¦
* @li APP_FAIL Ê§°Ü
* @author Áõî¸
* @date 2012-10-24
*/
int PubSaveVar (const char *psSaveBuf, const int nStart, const int nLen);

/**
* @brief »ñÈ¡´íÎóÂë
* @param [out]  pnErrorCode			Ä£¿é´íÎóÂë
* @param [out]  pszErr					Ä£¿é´íÎóÂëÌáÊ¾ĞÅÏ¢
* @param [out]  pnNDKErrorCode		NDK´íÎóÂë
* @return 
* @li ÎŞ
*/
void PubGetErrorCode(int *pnErrorCode, char *pszErr, int *pnNdkErrorCode);

/**
* @brief ÉèÖÃ´íÎóÂë
* @param [in]  nErrCode			Ä£¿é´íÎóÂë
* @param [in]  pszErrTip			Ä£¿é´íÎóÂëÌáÊ¾ĞÅÏ¢
* @param [in]  nNdkErrCode		NDK´íÎóÂë
* @return 
* @li APP_FAIL Ê§°Ü
* @li APP_SUCC ³É¹¦
* @author Áõî¸
* @date 2012-10-22
*/
void PubSetErrorCode(int nErrCode,const char *pszErr,int nNdkErrCode);

/**
* @brief ÉèÖÃ´íÎóĞÅÏ¢
* @param [in]  nErrorCode			Ä£¿é´íÎóÂë
* @param [in]  nNDKErrorCode		NDK´íÎóÂë
* @param [in]  ppszErr				´íÎóĞÅÏ¢(¶şÎ¬Êı×é)
* @return 
* @li ÎŞ
*/
void PubSetErrorInfo(int nErrCode,const char *ppszErr[MAX_ERR_BUF_LEN],int nNdkErrCode);

/**
* @brief POSÏìÉù
* @param [in] nTimes	ÏìÉù´ÎÊı
* @return 
* @li ÎŞ
*/
void PubBeep(int nTimes);

/**
* @brief POS¹Ø»ú
* @return
* li APP_SUCC	³É¹¦ 
* li APP_FAIL   Ê§°Ü
*/
int PubShutDown();

/**
* @brief Æô¶¯ÅÜ±í£¬¿ªÊ¼¼ÆÊ±
* @return
* li APP_SUCC	³É¹¦ 
* li APP_FAIL   Ê§°Ü
*/
int PubStartWatch();

/**
* @brief Í£Ö¹ÅÜ±í²¢±£´æ¼ÆÊıÖµ 
* @param [in] punTime   ÅÜ±í½áÊøÊ±µÄ¼ÆÊıÖµ (ºÁÃë)
* @return
* li APP_SUCC	³É¹¦ 
* li APP_FAIL   Ê§°Ü
*/
int PubStopWatch(uint * punTime);

/**
* @brief ñÈ¡POSÓ²¼şÖ§³ÖĞÅÏ¢
* @param [in] emFlag	EM_HARDWARE_SUPPORT Ã¶¾Ù¸÷ÖÖÓ²¼ş
* @param [out] pszBuf	¶ÔÓ¦µÄÓ²¼şĞÅÏ¢
* @return 
* @li APP_FAIL		²»Ö§³Ö¸ÃÓ²¼ş
* @li APP_APP_SUCC	Ö§³Ö¸ÃÓ²¼ş
* @date 2012-11-13
*/
int PubGetHardwareSuppot(int emFlag, char* pszBuf);

/**
* @brief »ñÈ¡POSÓ²¼şĞÅÏ¢
* @param [in] emFlag	EM_HARDWARE_GET Ã¶¾Ù¸÷ÖÖÓ²¼ş
* @param [out] pszBuf	¶ÔÓ¦µÄÓ²¼şĞÅÏ¢
* @return 
* @li APP_FAIL		Ê§°Ü
* @li APP_APP_SUCC	³É¹¦
*/
int PubGetPosInfo(int emFlag, char* pszBuf);

#endif

