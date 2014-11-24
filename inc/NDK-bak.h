/*
* 2011-2015 Newland Co., Ltd.
*
* Unified platform NDK API
* Author:	Product Development Dept.
* Date:	2012-08-17
* Version：	V1.00
* Last modified by 
* Last modified on: 
*/
#include <stdio.h>
#include <time.h>
#include <sys/socket.h>
#ifndef __NDKAPI__H
#define __NDKAPI__H

/** @addtogroup ErrorCodeDefinition
* @{
*/



typedef void *	NDK_HANDLE;         ///<SSL Timer handle

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

/**
 *@brief Error code function returns
*/
typedef enum {
	NDK_OK,					/**<operation succeeded*/
	NDK_ERR=-1,				/**<operation failed*/
	NDK_ERR_INIT_CONFIG = -2,	 /**<failed to initialize configuration*/
	NDK_ERR_CREAT_WIDGET = -3,	/**<error creating interface */
	NDK_ERR_OPEN_DEV = -4,/**<error opening device file */
	NDK_ERR_IOCTL = -5,	/**<error calling driver */
	NDK_ERR_PARA = -6,	/**<illegal parameter*/
	NDK_ERR_PATH = -7,	/**<illegal file path*/
	NDK_ERR_DECODE_IMAGE = -8,	/**<failed to decode image */
	NDK_ERR_MACLLOC=-9,			/*out of memory*/
	NDK_ERR_TIMEOUT = -10,		/**<timeout error*/
	NDK_ERR_QUIT = -11,		/**<press Cancel to exit*/
	NDK_ERR_WRITE = -12, /**<failed to write into file */
	NDK_ERR_READ = -13, 	/**<failed to read from file */
	NDK_ERR_OVERFLOW = -15,		/**<buffer overflow*/
	NDK_ERR_SHM = -16,	/**<error sharing memory */
	NDK_ERR_NO_DEVICES=-17,	/**<POS Without this equipment*/
	NDK_ERR_NOT_SUPPORT=-18, /**<Does not support this feature*/
	NDK_ERR_NOSWIPED = -50,	/**<no magnetic card swiping record*/
	NDK_ERR_SWIPED_DATA=-51,		/**<Drive the magnetic card data format is wrong*/
	NDK_ERR_NO_SIMCARD = -201,	/**<no SIM card*/
	NDK_ERR_PIN = -202, /**<incorrect SIM card password*/
	NDK_ERR_PIN_LOCKED = -203,	/**<SIM card locked*/
	NDK_ERR_PIN_UNDEFINE = -204,	/**<undefined SIM card error*/
	NDK_ERR_EMPTY = -205,			/**<empty string returned*/
	NDK_ERR_PPP_PARAM = -301,	/**<PPP parameter error*/
	NDK_ERR_PPP_DEVICE = -302,/**<PPP invalid device*/
	NDK_ERR_PPP_OPEN = -303, /**<PPP already open*/
	NDK_ERR_TCP_ALLOC = -304,	/**<can't allocate */
	NDK_ERR_TCP_PARAM = -305,	/**<invalid parameter*/
	NDK_ERR_TCP_TIMEOUT = -306,	/**<transmission timeout*/
	NDK_ERR_TCP_INVADDR = -307,	/**<invalid address*/
	NDK_ERR_TCP_CONNECT = -308,	/**<no connection*/
	NDK_ERR_TCP_PROTOCOL = -309,/**<protocol error*/
	NDK_ERR_TCP_NETWORK = -310,	/**<network error*/
	NDK_ERR_TCP_SEND = -311,	/**<error sending*/
	NDK_ERR_TCP_RECV = -312,	/**<error receiving*/


	NDK_ERR_SSL_PARAM = -350,       /**<invalid parameter*/
	NDK_ERR_SSL_ALREADCLOSE = -351, /**<connection already closed */
	NDK_ERR_SSL_ALLOC = -352,       /**<can't allocate*/
	NDK_ERR_SSL_INVADDR = -353,     /**<invalid address*/
	NDK_ERR_SSL_TIMEOUT = -354,     /**<connection Timeout */
	NDK_ERR_SSL_MODEUNSUPPORTED = -355, /**<unsupport mode*/
	NDK_ERR_SSL_SEND = -356,        /**<error sending*/
	NDK_ERR_SSL_RECV = -357,        /**<error receiving*/
	NDK_ERR_SSL_CONNECT = -358,       /**<no connection*/

	NDK_ERR_GET_NETADDR = -401, /**<failed to obtain local address or subnet mask */
	NDK_ERR_GET_GATEWAY = -402,	/**<failed to obtain gateway address */
	NDK_ERR_ADDR_ILLEGAL =-403, /**<failed to obtain address format*/

	NDK_ERR_THREAD_PARAM = -450,     /**<invalid address*/
	NDK_ERR_THREAD_ALLOC = -451,     /**<can't allocate*/
	NDK_ERR_THREAD_CMDUNSUPPORTED = -452,     /**<unsupported command*/

	NDK_ERR_MODEM_INIT_NOT=-505, /**<MODEM not initialized*/
	NDK_ERR_MODEM_SDLCWRITEFAIL=-506,	/**<MODEM sync write failure*/
	NDK_ERR_MODEM_SDLCHANGUPFAIL =-510,	/**<MODEM sync hangup failure*/
	NDK_ERR_MODEM_ASYNHANGUPFAIL=-511,	/**<MODEM async hangup failure*/
	NDK_ERR_MODEM_SDLCCLRBUFFAIL=-512,	/**<MODEM failed to sync clear buffer*/
	NDK_ERR_MODEM_ASYNCLRBUFFAIL=-513,	/**<MODEM failed to async clear buffer*/
	NDK_ERR_MODEM_ATCOMNORESPONSE=-514,/**<MODEM AT command no response*/
	NDK_ERR_MODEM_PORTWRITEFAIL=-515,/**<MODEM port to write data failed*/
	NDK_ERR_MODEM_SETCHIPFAIL=-516,/**<MODEM set register setting failed*/
	NDK_ERR_MODEM_STARTSDLCTASK=-517,/**<MODEM dialing on SDLC tasks fail*/

	NDK_ERR_MODEM_QUIT=-519,/**<MODEM hand out*/
	NDK_ERR_MODEM_NOPREDIAL=-520,/**<MODEM not dial*/
	NDK_ERR_MODEM_NOCARRIER=-521,/**<MODEM no carrier*/

	NDK_ERR_MODEM_NOLINE=-523,/**not plug wire*/
	NDK_ERR_MODEM_OTHERMACHINE=-524,/**there is the weaver*/
	NDK_ERR_MODEM_PORTREADFAIL=-525,/**<MODEM port to read data failed*/
	NDK_ERR_MODEM_CLRBUFFAIL=-526,/**<MODEM empty buffer failure*/
	NDK_ERR_MODEM_ATCOMMANDERR=-527,/**<MODEM AT command error */
	NDK_ERR_MODEM_STATUSUNDEFINE=-528,/**<MODEM unrecognized state*/

	NDK_ERR_ICC_WRITE_ERR =			-601,	/**<error writing device 83c26*/
	NDK_ERR_ICC_COPYERR=			-602,	/**<failed to copy kernel data*/
	NDK_ERR_ICC_POWERON_ERR=		-603,	/**<powerup error*/
	NDK_ERR_ICC_COM_ERR=			-604,	/**<command error*/
	NDK_ERR_ICC_CARDPULL_ERR=		-605,	/**<card pulled out*/
	NDK_ERR_ICC_CARDNOREADY_ERR=	-606,	/**<card not ready*/

	NDK_ERR_USDDISK_PARAM =  -650,          /**<Invalid parameter*/
	NDK_ERR_USDDISK_DRIVELOADFAIL =  -651,  /**<U disk or SD card drive load failure*/
	NDK_ERR_USDDISK_NONSUPPORTTYPE =  -652, /**<unsupported type */
	NDK_ERR_USDDISK_UNMOUNTFAIL =  -653,    /**<Mount failed*/
	NDK_ERR_USDDISK_UNLOADDRIFAIL =  -654,  /**<Failure to unloading the driver*/
	NDK_ERR_USDDISK_IOCFAIL =  -655,        /**<Drivers call wrong*/
	NDK_ERR_APP_BASE=(-800),							/**<application interface error cardinality*/
	NDK_ERR_APP_NOT_EXIST=(NDK_ERR_APP_BASE-1),			/**<application item does not exist*/
	NDK_ERR_APP_NOT_MATCH=(NDK_ERR_APP_BASE-2),	   /**fix pack file does not match**/
	NDK_ERR_APP_FAIL_SEC=(NDK_ERR_APP_BASE-3),	   			/**access to security attacks status failed**/
	NDK_ERR_APP_SEC_ATT=(NDK_ERR_APP_BASE-4),	  	 		/**there are security attacks**/
	NDK_ERR_APP_FILE_EXIST=(NDK_ERR_APP_BASE-5),	/**<Application of the file already exists*/
	NDK_ERR_APP_FILE_NOT_EXIST=(NDK_ERR_APP_BASE-6),/**<Application of the file does not exist*/
	NDK_ERR_APP_FAIL_AUTH=(NDK_ERR_APP_BASE-7),	  	/**<Certificate authentication failure*/
	NDK_ERR_APP_LOW_VERSION=(NDK_ERR_APP_BASE-8),	/**<Fix pack version lower than the application version*/

	NDK_ERR_APP_MAX_CHILD=(NDK_ERR_APP_BASE-9),			/**<application running more than maximum number*/
	NDK_ERR_APP_CREAT_CHILD=(NDK_ERR_APP_BASE-10),		/**<error creating the child process*/
	NDK_ERR_APP_WAIT_CHILD=(NDK_ERR_APP_BASE-11),		/**<wait for the child over mistakes*/
	NDK_ERR_APP_FILE_READ=(NDK_ERR_APP_BASE-12),		/**<error reading*/
	NDK_ERR_APP_FILE_WRITE=(NDK_ERR_APP_BASE-13),		/**<error writing*/
	NDK_ERR_APP_FILE_STAT=(NDK_ERR_APP_BASE-14),		/**<error get file information*/
	NDK_ERR_APP_FILE_OPEN=(NDK_ERR_APP_BASE-15),		/**<error open file*/
	NDK_ERR_APP_NLD_HEAD_LEN=(NDK_ERR_APP_BASE-16),		/**<error NLD length of the file header information */
	NDK_ERR_APP_PUBKEY_EXPIRED=(NDK_ERR_APP_BASE-17),	/**<the validity of the public*/
	NDK_ERR_APP_MMAP=(NDK_ERR_APP_BASE-18),				/**<error memory mapping*/
	NDK_ERR_APP_MALLOC=(NDK_ERR_APP_BASE-19),			/**<error in dynamic memory allocation*/
	NDK_ERR_APP_SIGN_DECRYPT=(NDK_ERR_APP_BASE-20),		/**<signature sign error data solution*/
	NDK_ERR_APP_SIGN_CHECK=(NDK_ERR_APP_BASE-21),		/**<signature data validation errors*/
	NDK_ERR_APP_MUNMAP=(NDK_ERR_APP_BASE-22),			/**<memory mapping error release*/
	NDK_ERR_APP_TAR=(NDK_ERR_APP_BASE-23),				/**<tar failed to perform commands*/
	NDK_ERR_APP_KEY_UPDATE_BAN=(NDK_ERR_APP_BASE-24),				/**Debug state key update is prohibited*/
	NDK_ERR_APP_FIRM_PATCH_VERSION=(NDK_ERR_APP_BASE-25),				/**A firmware patch incremental package versions do not match*/

    NDK_ERR_SECP_BASE = (-1000),
    NDK_ERR_SECP_TIMEOUT = (NDK_ERR_SECP_BASE - 1),             /**<obtain key value timeout*/
    NDK_ERR_SECP_PARAM = (NDK_ERR_SECP_BASE - 2),               /**<illegal input parameter*/
    NDK_ERR_SECP_DBUS = (NDK_ERR_SECP_BASE - 3),                /**<DBUS communication error*/
    NDK_ERR_SECP_MALLOC = (NDK_ERR_SECP_BASE - 4),              /**<error in dynamic memory allocation*/
    NDK_ERR_SECP_OPEN_SEC = (NDK_ERR_SECP_BASE - 5),            /**<error opening security device */
    NDK_ERR_SECP_SEC_DRV = (NDK_ERR_SECP_BASE - 6),             /**<security device operation error*/
    NDK_ERR_SECP_GET_RNG = (NDK_ERR_SECP_BASE - 7),             /**<obtain random number*/
    NDK_ERR_SECP_GET_KEY = (NDK_ERR_SECP_BASE - 8),             /**<obtain key value*/
    NDK_ERR_SECP_KCV_CHK = (NDK_ERR_SECP_BASE - 9),             /**<KCV check error*/
    NDK_ERR_SECP_GET_CALLER = (NDK_ERR_SECP_BASE - 10),         /**<error obtaining caller info */
    NDK_ERR_SECP_OVERRUN = (NDK_ERR_SECP_BASE - 11),            /**<run number wrong*/
    NDK_ERR_SECP_NO_PERMIT = (NDK_ERR_SECP_BASE - 12),          /**<permissions are not allowed to*/
	NDK_ERR_SECP_TAMPER = (NDK_ERR_SECP_BASE - 13),          	/**<security attack*/

    NDK_ERR_SECVP_BASE = (-1100),                           /**<unknown error*/
    NDK_ERR_SECVP_TIMEOUT = (NDK_ERR_SECVP_BASE - 1),       /**<obtain key value timeout*/
    NDK_ERR_SECVP_PARAM = (NDK_ERR_SECVP_BASE - 2),         /**<illegal input parameter */
    NDK_ERR_SECVP_DBUS = (NDK_ERR_SECVP_BASE - 3),          /**<DBUS communication error*/
    NDK_ERR_SECVP_OPEN_EVENT0 =	(NDK_ERR_SECVP_BASE - 4),   /**<error opening event0 device */
    NDK_ERR_SECVP_SCAN_VAL = (NDK_ERR_SECVP_BASE - 5),      /**<scan value out of range*/
    NDK_ERR_SECVP_OPEN_RNG = (NDK_ERR_SECVP_BASE - 6),      /**<error opening random number device*/
    NDK_ERR_SECVP_GET_RNG = (NDK_ERR_SECVP_BASE - 7),       /**<error obtaining random number */
    NDK_ERR_SECVP_GET_ESC = (NDK_ERR_SECVP_BASE - 8),       /**<the user to cancel key to exit*/
    NDK_ERR_SECVP_VPP = (-1120),
    NDK_ERR_SECVP_INVALID_KEY=(NDK_ERR_SECVP_VPP),  		/**<invalid key, for internal use.*/
	NDK_ERR_SECVP_NOT_ACTIVE=(NDK_ERR_SECVP_VPP-1),  		/**<VPPIs not active, the first call VPPInit.*/
	NDK_ERR_SECVP_TIMED_OUT=(NDK_ERR_SECVP_VPP-2),			/**<already more than VPP initialization time*/
	NDK_ERR_SECVP_ENCRYPT_ERROR=(NDK_ERR_SECVP_VPP-3),		/**<after press the confirmation key, to encrypt errors.*/
	NDK_ERR_SECVP_BUFFER_FULL=(NDK_ERR_SECVP_VPP-4),		/**<BUF over*/
	NDK_ERR_SECVP_PIN_KEY=(NDK_ERR_SECVP_VPP-5),  			/**<data key press, echo "*".*/
	NDK_ERR_SECVP_ENTER_KEY=(NDK_ERR_SECVP_VPP-6),			/**<confirm key press, PIN processing.*/
	NDK_ERR_SECVP_BACKSPACE_KEY=(NDK_ERR_SECVP_VPP-7),		/**<press the backspace key.*/
	NDK_ERR_SECVP_CLEAR_KEY=(NDK_ERR_SECVP_VPP-8),  		/**<clear key pressed to remove all the '*'.*/
	NDK_ERR_SECVP_CANCEL_KEY=(NDK_ERR_SECVP_VPP-9),  		/**<cancel button is pressed.*/
	NDK_ERR_SECVP_GENERALERROR=(NDK_ERR_SECVP_VPP-10),  	/**<the process cannot continue. Internal error.*/
	NDK_ERR_SECVP_CUSTOMERCARDNOTPRESENT=(NDK_ERR_SECVP_VPP-11), /**<IC Card is pulled out*/
	NDK_ERR_SECVP_HTCCARDERROR=(NDK_ERR_SECVP_VPP-12),  	/**<access smart card error.*/
	NDK_ERR_SECVP_WRONG_PIN_LAST_TRY=(NDK_ERR_SECVP_VPP-13),/**<Smart card - the password is not correct, try again one more time*/
	NDK_ERR_SECVP_WRONG_PIN=(NDK_ERR_SECVP_VPP-14), 		/**<Smart card - try one last time.*/
	NDK_ERR_SECVP_ICCERROR=(NDK_ERR_SECVP_VPP-15),  		/**<Smart card - try again so many times*/
	NDK_ERR_SECVP_PIN_BYPASS=(NDK_ERR_SECVP_VPP-16),  		/**<Smart card - PIN verification through, and the PIN length is zero*/
	NDK_ERR_SECVP_ICCFAILURE=(NDK_ERR_SECVP_VPP-17),  		/**<Smart card - a fatal error.*/
	NDK_ERR_SECVP_GETCHALLENGE_BAD=(NDK_ERR_SECVP_VPP-18),  /**<Smart card - response is not 90, 00.*/
	NDK_ERR_SECVP_GETCHALLENGE_NOT8=(NDK_ERR_SECVP_VPP-19), /**<Smart card - invalid response length.*/
 	NDK_ERR_SECVP_PIN_ATTACK_TIMER=(NDK_ERR_SECVP_VPP-20),  /**<PIN attack timer is activated*/

    NDK_ERR_SECCR_BASE = (-1200),                           /**<unknown error*/
    NDK_ERR_SECCR_TIMEOUT = (NDK_ERR_SECCR_BASE - 1),       /**<obtain key value timeout*/
    NDK_ERR_SECCR_PARAM = (NDK_ERR_SECCR_BASE - 2),         /**<illegal input parameter*/
    NDK_ERR_SECCR_DBUS = (NDK_ERR_SECCR_BASE - 3),          /**<DBUS communication error*/
    NDK_ERR_SECCR_MALLOC = (NDK_ERR_SECCR_BASE - 4),        /**<error in dynamic memory allocation*/
    NDK_ERR_SECCR_OPEN_RNG = (NDK_ERR_SECCR_BASE - 5),      /**<error opening random number device*/
    NDK_ERR_SECCR_DRV = (NDK_ERR_SECCR_BASE - 6),           /**<error in drive encryption*/
    NDK_ERR_SECCR_KEY_TYPE = (NDK_ERR_SECCR_BASE - 7),      /**<incorrect key type*/
    NDK_ERR_SECCR_KEY_LEN = (NDK_ERR_SECCR_BASE - 8),       /**<incorrect key type*/
    NDK_ERR_SECCR_GET_KEY = (NDK_ERR_SECCR_BASE - 9),       /**<error in obtaining key*/

    NDK_ERR_SECKM_BASE = (-1300),
    NDK_ERR_SECKM_TIMEOUT = (NDK_ERR_SECKM_BASE - 1),           /**<obtain key value timeout*/
    NDK_ERR_SECKM_PARAM = (NDK_ERR_SECKM_BASE - 2),             /**<illegal input parameter*/
    NDK_ERR_SECKM_DBUS = (NDK_ERR_SECKM_BASE - 3),              /**<DBUS communication error*/
    NDK_ERR_SECKM_MALLOC = (NDK_ERR_SECKM_BASE - 4),            /**<error in dynamic memory allocation */
    NDK_ERR_SECKM_OPEN_DB = (NDK_ERR_SECKM_BASE - 5),           /**<error opening database*/
    NDK_ERR_SECKM_DEL_DB = (NDK_ERR_SECKM_BASE - 6),            /**<error deleting database*/
    NDK_ERR_SECKM_DEL_REC = (NDK_ERR_SECKM_BASE - 7),           /**<error deleting record*/
    NDK_ERR_SECKM_INSTALL_REC = (NDK_ERR_SECKM_BASE - 8),       /**<error installing key record*/
    NDK_ERR_SECKM_READ_REC = (NDK_ERR_SECKM_BASE - 9),          /**<error reading key record*/
    NDK_ERR_SECKM_OPT_NOALLOW = (NDK_ERR_SECKM_BASE - 10),      /**<operation not allowed*/
    NDK_ERR_SECKM_KEY_MAC = (NDK_ERR_SECKM_BASE - 11),          /**<key MAC check error*/
    NDK_ERR_SECKM_KEY_TYPE = (NDK_ERR_SECKM_BASE - 12),         /**<key type error*/
    NDK_ERR_SECKM_KEY_ARCH = (NDK_ERR_SECKM_BASE - 13),         /**<key system error*/
    NDK_ERR_SECKM_KEY_LEN  = (NDK_ERR_SECKM_BASE - 14),         /**<key length error*/

	NDK_ERR_RFID_INITSTA=			-2005,	/**<contactless card - RF interface item failure or not configured*/
	NDK_ERR_RFID_NOCARD=			-2008,	/**<contactless card - no card  0x0D*/
	NDK_ERR_RFID_MULTICARD=			-2009,  /**<contactless card - multi-card state*/
	NDK_ERR_RFID_SEEKING=			-2010,	/**<contactless card - card seeking/activation failure*/
	NDK_ERR_RFID_PROTOCOL=			-2011,	/**<contactless card - not compliant with ISO1444-4 protocol, e.g. M1 card F*/

	NDK_ERR_RFID_NOPICCTYPE=		-2012,	/**<contactless card - card not set 0x01*/
	NDK_ERR_RFID_NOTDETE=			-2013,  /**<contactless card - card not detected  0x02*/
	NDK_ERR_RFID_AANTI=				-2014,	/**<contactless card - A card collision (multiple cards exist)  0x03*/
	NDK_ERR_RFID_RATS=				-2015,  /**<contactless card - A card RATS process error   0x04*/
	NDK_ERR_RFID_BACTIV=			-2016,  /**<contactless card - B card activation failure  0x07*/
	NDK_ERR_RFID_ASEEK=				-2017,  /**<contactless card - seek A card failed (probably multiple cards exist)   0x0A*/
	NDK_ERR_RFID_BSEEK=				-2018,  /**<contactless card - seek B card failed (probably multiple cards exist)   0x0B*/
	NDK_ERR_RFID_ABON=				-2019,  /**<contactless card - both A and B cards exist   0x0C*/
	NDK_ERR_RFID_UPED=				-2020,  /**<contactless card - already activated (powered up)   0x0E*/
	NDK_ERR_RFID_NOTACTIV=			-2021,  /**<contactless card - not activated*/
	NDK_ERR_RFID_COLLISION_A=       -2022,  /**<contactless card - A Card conflict*/
	NDK_ERR_RFID__COLLISION_B=      -2023,  /**<contactless card - B Card conflict*/

	NDK_ERR_MI_NOTAGERR=			-2030,  /**<contactless card - no card,				0xff*/
	NDK_ERR_MI_CRCERR=				-2031,  /**<contactless card - CRC error,				0xfe*/
	NDK_ERR_MI_EMPTY=				-2032,  /**<contactless card - not empty,				0xfd*/
	NDK_ERR_MI_AUTHERR=				-2033,  /**<contactless card - authentication error,			0xfc*/
	NDK_ERR_MI_PARITYERR=			-2034,  /**<contactless card - parity error,			0xfb*/
	NDK_ERR_MI_CODEERR=				-2035,  /**<contactless card - error receiving code			0xfa*/
	NDK_ERR_MI_SERNRERR=            -2036,  /**<contactless card - error in anti-collision data check	0xf8*/
	NDK_ERR_MI_KEYERR=              -2037,  /**<contactless card - KEY authentication error			0xf7*/
	NDK_ERR_MI_NOTAUTHERR=          -2038,  /**<contactless card - unauthenticated				0xf6*/
	NDK_ERR_MI_BITCOUNTERR=         -2039,  /**<contactless card - error receiving BIT 			0xf5*/
	NDK_ERR_MI_BYTECOUNTERR=        -2040,  /**<contactless card - error receiving byte			0xf4*/
	NDK_ERR_MI_WriteFifo=           -2041,  /**<contactless card - error writing FIFO			0xf3*/
	NDK_ERR_MI_TRANSERR=            -2042,  /**<contactless card - error sending		0xf2*/
	NDK_ERR_MI_WRITEERR=            -2043,  /**<contactless card - error writing			0xf1*/
	NDK_ERR_MI_INCRERR=				-2044,  /**<contactless card - error incrementing		0xf0*/
	NDK_ERR_MI_DECRERR=             -2045,  /**<contactless card - error decrementing		0xef*/
	NDK_ERR_MI_OVFLERR=             -2046,  /**<contactless card - overflow error			0xed*/
	NDK_ERR_MI_FRAMINGERR=          -2047,  /**<contactless card - frame error				0xeb*/
	NDK_ERR_MI_COLLERR=             -2048,  /**<contactless card - collision				0xe8*/
	NDK_ERR_MI_INTERFACEERR=        -2049,  /**<contactless card - reset interface read & write error		0xe6*/
	NDK_ERR_MI_ACCESSTIMEOUT=       -2050,  /**<contactless card - receive timeout			0xe5*/
	NDK_ERR_MI_PROTOCOLERR=			-2051,  /**<contactless card - protocol error				0xe4*/
	NDK_ERR_MI_QUIT=                -2052,  /**<contactless card - abnormal abortion 			0xe2*/
	NDK_ERR_MI_PPSErr=				-2053,  /**<contactless card - error in PPS operation			0xe1*/
	NDK_ERR_MI_SpiRequest=			-2054,  /**<contactless card - error applying SPI		0xa0*/
	NDK_ERR_MI_NY_IMPLEMENTED=		-2055,  /**<contactless card - unidentified error state	0x9c*/
	NDK_ERR_MI_CardTypeErr=			-2056,  /**<contactless card - card type error			0x83*/
	NDK_ERR_MI_ParaErrInIoctl=		-2057,  /**<contactless card - IOCTL parameter	error	0x82*/
	NDK_ERR_MI_Para=				-2059,  /**<contactless card - internal parameter error			0xa9*/
	NDK_ERR_WIFI_INVDATA=           -3001,  /**<WIFI-Invalid parameter*/
    NDK_ERR_WIFI_DEVICE_FAULT=      -3002,  /**<WIFI-Equipment state error*/
    NDK_ERR_WIFI_CMD_UNSUPPORTED=   -3003,  /**<WIFI-unsupported command */
    NDK_ERR_WIFI_DEVICE_UNAVAILABLE=-3004,  /**<WIFI-Device unavailable */
    NDK_ERR_WIFI_DEVICE_NOTOPEN=    -3005,  /**<WIFI-No scan to AP*/
    NDK_ERR_WIFI_DEVICE_BUSY=       -3006,  /**<WIFI-Device is busy */
    NDK_ERR_WIFI_UNKNOWN_ERROR=     -3007,  /**<WIFI-Unknown Error */
    NDK_ERR_WIFI_PROCESS_INBADSTATE=-3008,  /**<WIFI-Could not Connect AP*/
    NDK_ERR_WIFI_SEARCH_FAULT=      -3009,  /**<WIFI-Scanning state error*/
    NDK_ERR_WIFI_DEVICE_TIMEOUT=    -3010,  /**<WIFI-DEVICE TIMEOUT */
	NDK_ERR_LINUX_ERRNO_BASE=		-5000, /**<<LINUX>System function returns the ERROR ERROR prefix*/
}EM_NDK_ERR;

/** @} */ // end of error code function returns

/** @addtogroup Display
* @{
*/

#ifndef NL_COLOR_T
#define NL_COLOR_T
typedef unsigned int color_t;/**<RGB color value, 0 (black) - 0xFFFF (white)*/
#endif

/**
 *@brief display mode definition
*/
typedef enum {
	TEXT_ATTRIBUTE_NORMAL = 1<<0,			/**<normal font display*/
	TEXT_ATTRIBUTE_REVERSE = 1<<1,		/**<reverse font display*/
	TEXT_ATTRIBUTE_UNDERLINE = 1<<2,		/**<underline font*/
}EM_TEXT_ATTRIBUTE;

/**
 *@brief backlit control
*/
typedef enum {
	BACKLIGHT_OFF ,			/**<turn on LCD backlit*/ 
	BACKLIGHT_ON,			/**<turn off LCD backlit*/
	BACKLIGHT_LOCKON,		/**<disable LCD backlit automatic OFF*/
}EM_BACKLIGHT;

/**
 *@brief system font options definition
*/
typedef enum {
	DISPFONT_CUSTOM,			/**<system default display font*/
	DISPFONT_EXTRA,			/**<extra sized display font*/
	DISPFONT_USER,				/**<customized font*/
}EM_DISPFONT;

/**
 *@brief system font color setting definition
*/
typedef enum {
	FONTCOLOR_NORMAL,				/**<font color when font normally displayed*/
	FONTCOLOR_REVERSE,				/**<font color when font reversely displayed*/
	FONTCOLOR_BG_REVERSE,				/**<background color when font  reversely displayed*/
}EM_FONTCOLOR;

/**
 *@brief rectangular fill mode definition
*/
typedef	enum  {
    RECT_PATTERNS_NO_FILL,        /**<no fill, only draw borders*/
    RECT_PATTERNS_SOLID_FILL      /**<fill mode*/
}EM_RECT_PATTERNS;

/**
 *@brief	 user-program interface initialization.
 *@details this function is recommended to be called when the program starts, and the API of display module won?ˉt be operable until this function is successfully called.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	Other EM_NDK_ERR		operation failed
*/
int NDK_ScrInitGui(void);/**	*@example NDK_disp_example.c**/


/**
 *@brief	 obtaining display module version.
 *@retval	pszVer	returns the module version; and the pnVer input shall be no less than 16 bytes.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	Other EM_NDK_ERR		operation failed
*/
int NDK_ScrGetVer(char *pszVer);

/**
 *@brief	 setting display mode and obtaining previous display mode.
 *@param	emNewattr	new display mode to set 
 *@retval	pemOldattr	outputs previous display mode, it has no return if peOldattr is NULL.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	Other EM_NDK_ERR		operation failed
*/
int NDK_ScrSetAttr(EM_TEXT_ATTRIBUTE emNewattr, EM_TEXT_ATTRIBUTE *pemOldattr);

/**
 *@brief 	saving current screen
 *@details	this includes saving display content, cursor position and display mode; and you can call \ref NDK_ScrPop "NDK_ScrPop" to use the result saved to restore display rapidly.
			NDK_ScrPush and \ref NDK_ScrPop "NDK_ScrPop" are used in pairs, no nesting.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	Other EM_NDK_ERR		operation failed
*/
int NDK_ScrPush(void);

/**
 *@brief	 restoring display state rapidly with what is saved by calling \ref NDK_ScrPush "NDK_ScrPush"; and the state includs display content, cursor position and text display proprieties.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	Other EM_NDK_ERR		operation failed
*/
int NDK_ScrPop(void);

/**
 *@brief		setting background image; please refer to each model?ˉs image file format limits for image file format supported.
 *@param	pszfilepath 	image file path + file name
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	Other EM_NDK_ERR		operation failed
*/
int NDK_ScrSetbgPic(char *pszfilepath);

/**
 *@brief		canceling background image.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	Other EM_NDK_ERR		operation failed
*/
int NDK_ScrClrbgPic(void);

/**
 *@brief		clearing screen, moving cursor to pixel coordinates (0,0), and settinig screen display mode as TEXT_ATTRIBUTE_NORMAL.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	Other EM_NDK_ERR		operation failed
*/
int NDK_ScrClrs(void);

/**
 *@brief	 clearing several lines (unit: pixel), moving cursor to the coordinates (0, unStartY).
		  	this function is invalid with invalid parameter input and returns error info. 
 *@param	unStartY	starting line No. (Y-coordinate, unit: pixel), start with 0
 *@param	unEndY		end line No. (Y-coordinate, unit: pixel), start with 0
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	Other EM_NDK_ERR		operation failed
*/
int NDK_ScrClrLine(uint unStartY,uint unEndY);


/**
 *@brief 	moving the cursor on LCD display to pixel coordinates (unX,unY). 
			the cursor stays unmoved with illegal parameter input and error info will be returned.
 *@param	unX 	X-coordinate (unit: pixel)
 *@param	unY 	Y-coordinate (unit: pixel)
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	Other EM_NDK_ERR		operation failed
*/
int NDK_ScrGotoxy(uint unX, uint unY);


/**
 *@brief	 obtaining X and Y coordinates of current cursor position.
 *@retval	punX returns X-coordinate of cursor position (unit: pixel).
 *@retval	punY returns Y-coordinate of cursor position (unit: pixel).
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	Other EM_NDK_ERR		operation failed
*/
int NDK_ScrGetxy(uint *punX, uint *punY);


/**
 *@brief	 setting size of display area.
 *@details  if not set, the display area is the actual screen size; once display area  is set via this interface, display operations of other API are only effective in the area set. \n
			if you set (10,10,100,100) as the display area of application , the pixel coordinates (0,0) used in the application is in fact
			the pixel coordinates (10,10) on screen; and the clear screen operation can only remove data displayed within the area defined by pixel coordinates (10,10,100,100)
 *@param	unX		X-coordinate of starting point of display area for the application (unit: pixel).
 *@param	unY		the Y-coordinate of starting point of display area for the application (unit: pixel).
 *@param	unWidth	The application display area width (unit: pixel). 
 *@param	unHeight 	The application display area (unit: pixel). 
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrSetViewPort(uint unX,uint unY,uint unWidth, uint unHeight);

/**
 *@brief	 obtaining size of current display area.
 *@retval	punX		X-coordinate of starting point of display area (unit: pixel).
 *@retval	punY		Y-coordinate of starting point of display area (unit: pixel).
 *@retval	punWidth	width of display area (unit: pixel). 
 *@retval	punHeight	height of display area (unit: pixel). 
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrGetViewPort(uint *punX,uint *punY,uint *punWidth,uint *punHeight);


/**
 *@brief	 displaying Bitmap image in display area.
 *@details   bitmap format: 8 pixel points in 1 byte, 0 for white point, 1 for black point, display data in horizontal arrangement, as shown in the image below:\n
-----------------D7~~D0--------------D7~~D0------------------\n
Byte 1: ○ ○ ○ ○ ○ ○ ○ ○  ○  ○ ○ ○ ○ ○ ○ ○ Byte2	\n
Byte 3: ○ ○ ○ ○ ○ ○ ○ ○  ○  ○ ○ ○ ○ ○ ○ ○ Byte4	\n
Byte 5: ○ ○ ○ ○ ○ ○ ○ ○  ○  ○ ○ ○ ○ ○ ○ ○ Byte6	\n
Byte 7: ○ ○ ● ● ● ● ● ●  ●  ● ● ● ● ● ○ ○ Byte8	\n
Byte 9: ○ ○ ○ ○ ○ ○ ○ ○  ○  ○ ○ ○ ○ ○ ○ ○ Byte10	\n
Byte11: ○ ○ ○ ○ ○ ○ ○ ○  ○  ○ ○ ○ ○ ○ ○ ○ Byte12	\n
Byte13: ○ ○ ○ ○ ○ ○ ○ ○  ○  ○ ○ ○ ○ ○ ○ ○ Byte14	\n
Byte15: ○ ○ ○ ○ ○ ○ ○ ○  ○  ○ ○ ○ ○ ○ ○ ○ Byte16	\n
---------------------------------------------------------------\n
	if the image to be displayed is outside of the screen or the area set up for use via \ref NDK_ScrSetViewPort "NDK_ScrSetViewPort()", this function is invalid and will return call failed.
 *@param	unX 		X-coordinate of upper-left corner of image in display area (unit:  pixel)
 *@param	unY 		Y-coordinate of upper-left corner of image in display area (unit:  pixel)
 *@param	unWidth 	width of image (unit: pixel)
 *@param	unHeight 	height of image (unit: pixel)
 *@param	psBuf 		Bitmap image data
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrDrawBitmap(uint unX,uint unY,uint unWidth, uint unHeight, const char *psBuf);


/**
 *@brief	 drawing a line from pixel coordinates (unStartX,unStartY) to pixel coordinates (unEndX,unEndY) in display area, unColor is RGB color value of the line. 
 *@param	unStartX 	X-coordinate of starting point of line (unit: pixel)
 *@param	unStartY 	Y-coordinate of starting point of line (unit: pixel)
 *@param	unEndX 		X-coordinate of end point of line (unit: pixel)
 *@param	unEndY 		Y-coordinate of end point of line (unit: pixel)
 *@param	unColor 		color value <0-0xFFFF>
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrLine(uint unStartX, uint unStartY, uint unEndX, uint unEndY, color_t unColor);


/**
 *@brief	 drawing a rectangle in display area.
 *@details	if the border of rectangle is outside of screen or the area set up for use via \ref NDK_ScrSetViewPort "NDK_ScrSetViewPort()", this function operation is invalid and will return call failed.
 *@param	unX 		X-coordinate of starting point of rectangle (unit: pixel)
 *@param	unY 		Y-coordinate of starting point of rectangle (unit: pixel)
 *@param	unWidth 		width of rectangle (unit: pixel)
 *@param	unHeight 		height of rectangle (unit: pixel)
 *@param	emFill_pattern 	0 = fill mode; 1 = fill mode 
 *@param	unColor	 color value <0-0xFFFF>
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrRectangle(uint unX, uint unY, uint unWidth, uint unHeight, EM_RECT_PATTERNS emFill_pattern, color_t unColor);


/**
 *@brief	 to display specific image in display area; please refer to image format file limits of each model for image formats supported.
 *@details	if the image displayed is outside of screen or the area set up for use via \ref NDK_ScrSetViewPort "NDK_ScrSetViewPort()", this function operation is invalid and will return call failed.
 *@param	unX 		X-coordinate of upper-left corner of image displayed (unit:  pixel)
 *@param	unY 		Y-coordinate of upper-left corner of image displayed (unit:  pixel)
 *@param	unWidth 	Width of image (unit: pixel)
 *@param	unHeight 	Height of image displayed [unit: pixel)
 *@param	pszPic 	the path of image file
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrDispPic(uint unX,uint unY,uint unWidth, uint unHeight, const char *pszPic);

/**
 *@brief	 to obtain color value of specific pixel-coordinate point in display area. 
 *@param	unX 		X-coordinate (unit: pixel)
 *@param	unY 		Y-coordinate (unit: pixel)
 *@retval	punColor	color value returned.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrGetPixel(uint unX, uint unY, color_t *punColor);


/**
 *@brief	 to draw point at specific pixel coordinate in display area
 *@param	unX 		X-coordinate (unit: pixel)
 *@param	unY		Y-coordinate (unit: pixel)
 *@param	unColor 	 color value <0-0xFFFF>
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrPutPixel(uint unX, uint unY, color_t unColor);


/**
 *@brief to refresh LCD display with data set by user in graphic memory which is to be used inside of display area. 
 *@details	system default: auto refresh; to avoid blinking screen, you can set it as no auto refresh via \ref NDK_ScrAutoUpdate "NDK_ScrAutoUpdate()", then the system won't refresh LCD display with the data in graphic memory until 			NDK_ScrRefresh is called.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrRefresh(void);

/**
 *@brief	 refreshing LCD display in full screen with all data in graphic memory.
 *@details	this interface differs from \ref NDK_ScrRefresh "NDK_ScrRefresh()" in that it is not limited by the size of display area; when it is set as display in full screen via NDK_ScrSetViewPort, 
			\ref NDK_ScrRefresh "NDK_ScrRefresh()" will have the same effect as of this interface.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrFullRefresh(void);

/**
 *@brief	 to set whether auto refresh is applied.
 *@param	nNewauto
					non-zero:Auto Refresh 
					0: no auto refresh, Only call \ ref NDK_ScrRefresh NDK_ScrRefresh "()" to display the data in the memory.
 *@retval	pnOldauto	return to auto refresh state before the setting. 
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrAutoUpdate(int nNewauto, int *pnOldauto);


/**
 *@brief	 to obtain LCD size
 *@retval		punWidth	return width of LCD (unit: pixel).support punWidth=NULL
 *@retval		punHeight	return height of LCD (unit: pixel).support punHeight=NULL
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrGetLcdSize(uint *punWidth,uint *punHeight);

/**
 *@brief	 to obtain color depth of LCD
 *@details	it can be used to determine if it is a monochrome or color LCD
 *@retval		puncd	Return color depth of LCD: 1 ---- black and white
										16----16-bit color, color screen
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrGetColorDepth(uint *puncd);

/**
 *@brief to ON/OFF backlit.
 *@param	emBL	BACKLIGHT_OFF ¨C turn off LCD backlit
 					BACKLIGHT_ON ¨C turn on LCD backlit
 					BACKLIGHT_LOCKON ¨C LCD backlit always ON
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrBackLight(EM_BACKLIGHT emBL);

/**
 *@brief		to set screen contrast.
 *@param		unContrast	Contrast level of 0, 0 ~ 7 is the most weak, 7 the most, the default is 5.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrSetContrast(uint unContrast);


/**
 *@brief	 to set display font to be used.
 *@details  system allows for switching between two sizes of bitmap fonts by default; different models may have different system default font size settings\n\n
			color screen supports: Chinese character 16x16 ASCII:8x16 (DISPFONT_CUSTOM)\n
					 Chinese character 24x24 ASCII:12x24 (DISPFONT_EXTRA)\n
			Back-and-white support: Chinese character 12x12 ASCII:6x12 (DISPFONT_CUSTOM)\n
						Chinese character 16x16 ASCII:8x16 (DISPFONT_EXTRA)\n\n
			display font setting is only effective on font afterward, not on previous display content already refreshed 
 *@param	emType	to select font
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrSetFontType(EM_DISPFONT emType);


/**
 *@brief	 to obtain width and height of Chinese font currently used.
 *@details  the width of ASCII character bitmap in the system is always half of that of Chinese character
 *@retval	punWidth	return the width of Chinese character bitmap currently used in the system.
 *@retval	punHeight	return the height of Chinese character bitmap currently used in system.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrGetFontSize(uint *punWidth,uint *punHeight);


/**
 *@brief	 to set line spacing and word spacing.
 *@details  when wspace is larger than twice of the pixel width of English font currently used, the word spacing is set as twice of the English font pixel width
			when hspace is larger than the pixel height of English font currently used, the line spacing is set as the pixel height of English font
 *@param	unWspace	word spacing (unit: pixel)
 *@param	unHpace	line spacing (unit: pixel)
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrFontAdd(const char *pcCpath,const char *pcApath);


/**
 *@brief	Set the line spacing and word spacing.
 *@details  wspaceGreater than the current use of English font is 2 times of the width of the pixel, word spacing is set to 2 times of the width of the English font pixel
			hspace Greater than the current use of English font pixel height, line spacing is set to English font pixel level
 *@param	unWspace	Word spacing (unit: pixels)
 *@param	unHpace	    Line spacing (unit: pixels)
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_ScrSetSpace(uint unWspace,uint unHpace);


/**
 *@brief	 to set font colors (incl. normal display color, reverse display color and its background color).
 *@param	unColor	 color value
 *@param	emType	select object to set

 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrSetFontColor(color_t unColor, EM_FONTCOLOR emType);



/**
 *@brief	 to display string.
 *@param	unX	display X-coordinate of string 
 *@param	unY	 display Y-coordinate of string 
 *@param	pszS	string pointer to be displayed 
 *@param	unMode	 set ASCII character display size
					1: use small-sized English font, not applicable to string that contains Chinese character
						black and white screen: English font of 8x8 
						color screen: English font of 8x16 
					0: size of ASCII bitmap in current used display font
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrDispString(uint unX,uint unY,const char *pszS,uint unMode);

/**
 *@brief	 formatted output display on screen; same usage method as of printf
 *@param	format	format of parameter output
  *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ScrPrintf(const char *format, ...);

/**
 *@brief	Control at the bottom of the screen shows the status bar
 *@details	Did not call the interface, the system is off by default, according to the status bar by the interface closed when the status bar, the status bar displays the location of the data is not restored, recommended to refresh the display data set before closed or open the status bar
 *@param	unFlag	0 close the status bar display\n
					1 fully display the status bar, including wireless signal, time and power\n
					2 show only the time\n
					4 show only the battery\n
					8 display only a wireless signal
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_ScrStatusbar(uint unFlag);

/**
 *@brief	Load BDF Font
 *@details	User-defined BDF font format to support load multiple BDF font file
 *@param	unFontID A custom font ID, such as 0. If uFontID BDF font is the same with before setting, gauge BDF font before replacement
 *@param    pszFile BDF file path + file name
 *@param    punWidth To obtain the biggest BDF font pixel wide, supporting the value to NULL
 *@param    punHeight To obtain the biggest BDF font pixels high, supporting the value to NULL
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	NDK_ERR	BDF Font file format can't recognize
*/
int NDK_ScrLoadBDF(uint unFontID,char *pszFile,uint *punWidth,uint *punHeight);


/**
 *@brief	Use loaded BDF font display data
 *@details
 *@param	unFontID \ref NDK_ScrLoadBDF "NDK_ScrLoadBDF()"Loading the corresponding font ID number
 *@param	unX	Display the string location of the abscissa
 *@param	unY	Display the string ordinate
 *@param    pszText According to string, its value is BDF file character code corresponding to the value of some code or UNICODE, specific depending on BDF file
 *@return
 *@li	NDK_OK	operation succeeded
 *@li	NDK_ERR_PARA Parameter is illegal
 *@li	NDK_ERR	BDF Font is not loaded
*/
int NDK_ScrDispBDFText(uint unFontID,uint unX,uint unY,ushort *pszText);

/** @} */ // End of the display module

/** @addtogroup Keyboard
* @{
*/
/**
 *@brief Function keys defined
*/
#define  K_F1			0x01
#define  K_F2			0x02
#define  K_F3			0x03
#define  K_F4			0x04
#define  K_F5			0x05
#define  K_F6			0x06
#define	 K_F7			0x07
#define	 K_F8			0x08
#define	 K_F9			0x09
#define  K_BASP		0x0a    /**<backspace key*/
#define  K_ENTER		0x0D	/**<Cancel-key*/
#define  K_ESC		0x1B	/**<Enter key*/
#define	 K_ZMK		0x1C	/**<letter key*/
#define	 K_DOT		0x2E	/**<decimal point*/

/**
 *@brief input control
*/
#define K_ZERO		0x30
#define K_ONE		0x31
#define K_TWO		0x32
#define K_THREE		0x33
#define K_FOUR		0x34
#define K_FIVE		0x35
#define K_SIX		0x36
#define K_SEVEN		0x37
#define K_EIGHT		0x38
#define K_NINE		0x39

/**
 *@brief input control 
*/
typedef enum {
	INPUT_CONTRL_NOLIMIT, 		/**<Can input any ASCII characters, returned directly after the expiration of the lost*/
	INPUT_CONTRL_LIMIT,		/**<Only allow you to input Numbers with decimal point, directly after the expiration of the lost back*/
	INPUT_CONTRL_NOLIMIT_ERETURN,		/**<Can input any ASCII characters, after the expiration of the lost waiting for the confirm button*/
	INPUT_CONTRL_LIMIT_ERETURN,			/**<Only allow you to input Numbers with decimal point, waiting for the confirm button to return to after the expiration of the lost*/
}EM_INPUT_CONTRL;

/**
 *@brief input character display control
*/
typedef enum {
	INPUTDISP_NORMAL, 		/**<characters of input content normally displayed*/
	INPUTDISP_PASSWD,			/**<input content displayed as '*' */
	INPUTDISP_OTHER,			/**<support input receiving buffer with preset values*/
}EM_INPUTDISP;

/**
 *@brief input method type
*/
typedef enum {
    IME_NUMPY,	/**<Several spelling*/
    IME_ENGLISH, 	/**<English*/
	IME_NUM,	/**<digit*/
	IME_BIHUA,	/**<strokes*/
    IME_QUWEI,	/**< zone bit*/
    IME_GBK,
    IME_MAXNUM=IME_GBK,	/**<Only for bad judgment*/
}EM_IME;

/**
 *@brief	 to clear keyboard buffer.
 *@return
 *@li		NDK_OK			   operation succeeded
 *@li		other EM_NDK_ERR    operation failed
*/
int NDK_KbFlush(void);

/**
 *@brief	ON/OFF hold-on key and key combination function.
 *@param	nSelect 	0   OFF 1   ON
 *@param	nMode 		0   hold-on key  1   key combination
 *@param	pnState 	obtain the previous state of hold-on key or key combination, 0 -- OFF 1 -- ON.
 *@return
 *@li		NDK_OK				  operation succeeded
 *@li		other EM_NDK_ERR    operation failed
*/
int NDK_KbSwitch(int nSelect, int nMode,int *pnState);

/**
 *@brief 	to obtain ON/OFF state of hold-on key or key combination.
 *@param	nMode 	0   hold-on key  1   key combination
 *@param	pnState 	obtain the previous state of hold-on key or key combination, 0 -- OFF 1 -- ON.
 *@return
 *@li		NDK_OK 				   operation succeeded
 *@li		other EM_NDK_ERR	   operation failed
*/
int NDK_KbGetSwitch(int nMode,int *pnState);

/**
 *@brief 	to read key value of keyboard in timeout
 *@details	read key within time limit, the process is as follows: press one key, release it, and return key code 
 *@param	unTime	<=0: not timeout, keep on waiting for reading key
							other value: latency time (unit: second)
 *@param	pnCode	Obtain input key code; if no key is pressed in regulated time, pnCode value is 0. 
 *@li       NDK_OK 				   operation succeeded
 *@li   	other EM_NDK_ERR	   operation failed
*/
int NDK_KbGetCode(uint unTime, int *pnCode);

/**
 *@brief	 to obtain first key value of keyboard in buffer; it will return immediately. 
 *@details	check if there is a keystroke in keystroke buffer, if yes, read the key and return key code; if no keystroke, return 0 immediately.
   			generally, the API is used in a programmed loop body, and ref NDK_KbFlush "NDK_KbFlush" shall be used to clear buffer before such API is used.
 			This function differs from \ref NDK_KbGetCode "NDK_KbGetCode" in that it will return immediately without waiting.
 *@param	pnCode	Obtain input key code; if no key is pressed, pnCode value is 0
 *@return
 *@li        	NDK_OK 				   operation succeeded
 *@li   		other EM_NDK_ERR	   operation failed
*/
int NDK_KbHit(int *pnCode);

/**
*@brief		to input string
*@details	read from keyboard a string ended with a line feed, and save it in buffer pszBuf.
			with ESC key, it will return ?°operation failed?±, and Enter key, it will finish reading key and return; other function keys are invalid. 
*@param		pszBuf	receive string data
*@param		unMin	minimum length of input string 
*@param		unMaxlen	maximum length of input string 
*@param		punLen	obtain actual length of input length (>0)
*@param		emMode	display type,
					display characters when the value is INPUTDISP_NORMAL;
					'*' is displayed when the value is INPUTDISP_PASSWD;
					When the value is INPUTDISP_OTHER, if there is any content (string ended with \0) in pcBuf, it is deemed as already having data input from keyboard and displayed in plain code.
*@param		unWaittime	Input waiting time; 0 - keep on waiting; others ¨C number of seconds for waiting If Enter keystroke is out of time, and then automatically return with TimeOut. 
*@param		emControl	INPUT_CONTRL_NOLIMIT:Any ASCII characters, returned directly after the expiration of the lost
						INPUT_CONTRL_LIMIT:Only Numbers and the decimal point, directly after the expiration of the lost back
						INPUT_CONTRL_NOLIMIT_ERETURN: Any ASCII code character, wait for Enter key to return when input is full
						INPUT_CONTRL_LIMIT_ERETURN:Read only numbers and decimal points, wait for Enter key to return when input is full
 *@return
 *@li        	NDK_OK 			   operation succeeded
 *@li   		other EM_NDK_ERR	   operation failed

*/
int NDK_KbGetInput(char *pszBuf,uint unMin,uint unMaxlen,uint *punLen,EM_INPUTDISP emMode,uint unWaittime, EM_INPUT_CONTRL emControl);

/**
 *@brief Chinese character input method
 *@details 	Through the press "letter key" select input method.
			input steps:
			a. Pinyin input in pinyin input field directly such as "xin" input "946", and select. Press "backspace" clear input, press the direction key to move around pinyin.
			b. Press confirmation "to enter alternate characters column, select the need of Chinese characters, the direction key to left shift and moves to the right. 
			    If the" backspace "key to return to 'a' steps. Press the "confirm" button is selected needs to Chinese characters.
			c. you can use the direction keys to make a left or right move in order to select desired character when input method is activated.
	 		to input punctuations:
				In increase in open input method, punctuation press numeric key "0" appears, press the direction key to move around selection code, press the confirmation key back to the selected symbol;

 *@param	pszS 		to receive data string; if pcS has content (string ended with \0), it is deemed as already having data input from the keyboard.
 *@param	unMaxlen 	maximum length of data string allowed to receive.
 *@param	emMethod		input method selection; if emMethod is assigned with any value but EM_IME, this function will activate Shupin input method by default.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_KbHZInput(char *pszS,uint unMaxlen,EM_IME emMethod);

/** @} */ // end of keyboard module


/** @addtogroup Print
* @{
*/

/**
 *@brief font definition value
*/
typedef enum {
	PRN_HZ_FONT_24x24 = 1,
	PRN_HZ_FONT_16x32 ,
	PRN_HZ_FONT_32x32 ,
	PRN_HZ_FONT_32x16 ,
	PRN_HZ_FONT_24x32 ,
	PRN_HZ_FONT_16x16 ,
	PRN_HZ_FONT_12x16 ,
	PRN_HZ_FONT_16x8 ,
	PRN_HZ_FONT_24x24A ,			/**<ProprietarySong 24x24 bitmap*/
	PRN_HZ_FONT_24x24B ,			/**<FangSong 24x24 bitmap*/
	PRN_HZ_FONT_24x24C ,			/**<KaiTi 24x24 bitmap*/
	PRN_HZ_FONT_24x24USER ,
	PRN_HZ_FONT_12x12A ,			/**<SimSun 12x12 bitmap*/
	PRN_HZ_FONT_48x24A ,
	PRN_HZ_FONT_48x24B ,
	PRN_HZ_FONT_48x24C ,
	PRN_HZ_FONT_24x48A ,
	PRN_HZ_FONT_24x48B ,
	PRN_HZ_FONT_24x48C ,
	PRN_HZ_FONT_48x48A ,
	PRN_HZ_FONT_48x48B ,
	PRN_HZ_FONT_48x48C
}EM_PRN_HZ_FONT;

typedef enum {
	PRN_ZM_FONT_8x16 = 1,
	PRN_ZM_FONT_16x16 ,
	PRN_ZM_FONT_16x32 ,
	PRN_ZM_FONT_24x32 ,
	PRN_ZM_FONT_6x8 ,
	PRN_ZM_FONT_8x8 ,
	PRN_ZM_FONT_5x7 ,
	PRN_ZM_FONT_5x16 ,
	PRN_ZM_FONT_10x16 ,
	PRN_ZM_FONT_10x8 ,
	PRN_ZM_FONT_12x16A ,       /**<MSGothic bold 12x16 bitmap*/
	PRN_ZM_FONT_12x24A ,				/**<Gulimche font 12x24 bitmap*/
	PRN_ZM_FONT_16x32A ,				/**<MSGothic bold 16x32 bitmap*/
	PRN_ZM_FONT_12x16B ,				/**<MSGothic bold 12x16 bitmap*/
	PRN_ZM_FONT_12x24B ,				/**<MSGothic bold 12x24 bitmap*/
	PRN_ZM_FONT_16x32B ,				/**<MSGothic bold 16x32 bitmap*/
	PRN_ZM_FONT_12x16C ,				/**<KaiTi bold 12x16 bitmap*/
	PRN_ZM_FONT_12x24C ,				/**<KaiTi bold 12x24 bitmap*/
	PRN_ZM_FONT_16x32C ,				/**<KaiTi bold 16x32 bitmap*/
	PRN_ZM_FONT_24x24A ,
	PRN_ZM_FONT_32x32A ,
	PRN_ZM_FONT_24x24B ,
	PRN_ZM_FONT_32x32B ,
	PRN_ZM_FONT_24x24C ,
	PRN_ZM_FONT_32x32C ,
	PRN_ZM_FONT_12x12
}EM_PRN_ZM_FONT;

/**
 *@brief  printer status and error definition; obtaining return value of printer status; two or more relationships exist 
*/

typedef enum{
	PRN_STATUS_OK = 0,			/**<printer operates well*/
	PRN_STATUS_BUSY = 8,			/**<printer is printing*/
	PRN_STATUS_NOPAPER = 2,       /**<printer out of paper*/
	PRN_STATUS_OVERHEAT = 4,      /**<printer overheat*/
	PRN_STATUS_VOLERR = 112       /**<printer has abnormal voltage*/
}EM_PRN_STATUS;

/**
 *@brief  printer type enumeration
*/

typedef enum {
    PRN_TYPE_TP = 0,             /**<thermal printer*/
    PRN_TYPE_HIP,              /**<Punch & dot-matrix*/
    PRN_TYPE_FIP,              /**<Friction & Dot-matrix*/
    PRN_TYPE_END               /**<NULL*/
}EM_PRN_TYPE;

/**
 *@brief  printing modes
*/
typedef enum{
	PRN_MODE_ALL_DOUBLE = 0,			/**<In longitudinal and transverse magnification zoom in*/
	PRN_MODE_WIDTH_DOUBLE ,			/**<In longitudinal and transverse magnification is normal*/
	PRN_MODE_HEIGHT_DOUBLE,       /**<Transverse, longitudinal magnification normally*/
	PRN_MODE_NORMAL               /**<Transverse, longitudinal normal to normal*/
}EM_PRN_MODE;


/**
 *@brief Enumeration type value for underline function ON/OFF
*/
typedef enum{
	PRN_UNDERLINE_STATUS_OPEN = 0,			/**<underline function ON*/
	PRN_UNDERLINE_STATUS_CLOSE			   /**<underline function OFF*/
}EM_PRN_UNDERLINE_STATUS;

/**
 *@brief font library registration info
*/
typedef struct
{
	int nOffset;						/**<the offset of desired character in font library*/
	int nFontByte;					   /**<the number of bytes of desired character occupies in font library*/
}ST_PRN_RECMSG;


/**
 *@brief Enumeration type value for underline function ON/OFF
*/
typedef struct
{
	char *pszName;	    			/**<font library name or its path*/
	int  nNum;				    	/**<Register No, support 0~7 register No.*/
	int  nDirection;   				/**<0: horizontal font; 1: vertical font*/
	int  w;							/**<width of font displayed*/
	int  h;							/**<height of font displayed*/
	int  (*func)(char *, ST_PRN_RECMSG *);	/**<function that obtains offset address and number of bytes occupied*/
	int  nIsHZ;                     /**<is the font library registered a Chinese font lib or ASCII character lib. 1: HZ  0: ZM*/
}ST_PRN_FONTMSG;


/**
 *@brief 		  printer initialization
 *@details  	it includes clearing buffer, resetting print parameters (incl. font, margin, mode etc.)
 *@param      unPrnDirSwitch  to decide whether turn on feed & print function or call NDK_PrnStart (start printing switch).
              0-- Close to send while playing function (the default)
	              Under this mode, all NDK_PrnStr, NDK_PrnImage can complete conversion to matrix and save the dot matrix data to the buffer.
	              Start all printing associated work including feeding paper and printing, after NDK_PrnStart is called.
              1-- Open side to side play function
	              under this mode, once there is a full line of data, it will be sent to print; calling NDK_PrnStart will be of no avail and it will return directly.
	              Calling NDK_PrnFeedByPixel will immediate start paper feed and return. Under OFF mode, this operate will start after NDK_PrnStart.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_PrnInit(uint unPrnDirSwitch);
/**
 *@brief 		to print string
 *@details 		this function will convert all strings to be printed to matrix buffer; and sending data and printing will begin after Start is called. This function is a 100% software operation.
 *@param		pszBuf is a string ended with\0 with content of ASC code, Chinese character, or line feed\n or\r(indicating the end of line, directly feed paper for empty line).
 				if pszBuf contains mixed string of Chinese characters and ASCII, the letters and characters concerns only most recent setting. 
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_PrnStr(const char *pszBuf);
/**
 *@brief 		to start printing.
 *@details 	both NDK_PrnStr and NDK_PrnImage will complete data-to-dot matrix conversion and send it to the buffer; call these functions to start sending data and printing.
			 			when the printing initiated by calling NDK_PrnStart is ended, the system will determine if a return value of 0 is obtained. A return value of -1 indicates a failure in sending data to print. It shall return printer state value immediately and stop sending data.   
			 			NDK_PrnStart will stop and wait for return of printer state after printing is completed. Applications may use the value NDK_PrnStart returned to determine if the printer is in the right state. 
			 			(if what returned is not printer state value or NDK_OK, in other words, some other system error occurs, the application needs to obtain printer state. However, case like this rarely happens)
 *@return
 *@li	NDK_OK				end of printing and the printer is in good state
 *@li	}EM_NDK_ERR;		Other system errors (such as NDK_ERR_OPEN_DEV or NDK_ERR_MACLLOC)
*/
int NDK_PrnStart(void);
/**
 *@brief 		to print image (this function shall also convert bit matrix to be printed to the buffer and call NDK_PrnStart to start printing)
 *@details  	maximum width of thermal printing is 384 pixels. If the sum of xsize and xpos surpasses the limit above, the system will have return failure; as for horizontal enlargement mode, the value shall not exceed 384/2.
 *@param 		unXsize width of image (pixel)
 *@param 		unYsize height of image (pixel)
 *@param 		unXpos Graphic column in the top left hand corner position, and must meet xpos + xsize < = ndk_PR_MAXLINEWIDE (normal mode for 384, when the lateral magnification for 384/2, the parameters for the absolute coordinates is not affected by the left margin)
 *@param 		psImgBuf  dot matrix data for the image in horizontal arrangement, in the first 8 dot of line 1 of byte 1, D7 is the first dot
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_PrnImage(uint unXsize,uint unYsize,uint unXpos,const char *psImgBuf);
/**
 *@brief 		to obtain the type of this printer
 *@retval   pemType Used to store the version string
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_PrnGetVersion(char *pszVer);
/**
 *@brief 		to set print font
 *@details  setting ASCII print font and Chinese font. Related definitions in files about interface between bottom layer and application may be referred to for the application layer.
 *@param 	emHZFont	Set Chinese font format
 *@param    emZMFont	Set ASCII font format
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_PrnSetFont(EM_PRN_HZ_FONT emHZFont,EM_PRN_ZM_FONT emZMFont);
/**
 *@brief		to obtain state value of printer
 *@details		this function can be used to determine if printer is out of paper before printing starts.
 *@retval	    pemStatus is used to return state value of printer(error code contains two or more values in OR relationship)
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_PrnGetStatus(EM_PRN_STATUS *pemStatus);
/**
 *@brief: 	setting print mode.
 *@param 	emMode print mode (normal mode by default)
 *@param     unSigOrDou select uni- or bi-directional print 0-- unidirectional 1--bidirectional (only valid for dot matrix printer, not thermal printer)
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_PrnSetMode(EM_PRN_MODE emMode,uint unSigOrDou);
/**
 *@brief		Set the print grayscale
 *@details		Set print gray (heating time), so that for different printing paper printing effect fine-tuning. (only for thermal effective, the needle is invalid)
 *@param    unGrey Grey value, the range is 0 ~ 5; 0 as the light effect, 5 for the printing effect. The default gray level for 3 print driver.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_PrnSetGreyScale(uint unGrey);
/**
 *@brief  	set left margin, word spacing and line spacing for printing. The effectiveness of setting on printer will maintain until next time. 
 *@param  unBorder left margin range: 0-288 (0 by default)
 *@param    unColumn word spacing rang: 0-255(0 by default)
 *@param    unRow line spacing, range: 0-255 (0 by default)
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_PrnSetForm(uint unBorder,uint unColumn, uint unRow);
/**
 *@brief 	  feeding paper per pixel
 *@details	to make the printer feed paper; take pixel point as parameter; paper will not be fed immediately after the function is called. It will be saved in buffer and wait until Start is called. in order to be executed with printing action at the same time.  
 *@param    unPixel  pixel point for paper feed, range > 0
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_PrnFeedByPixel(uint unPixel);

/**
 *@brief	 ON/OFF underline function for the printing.
 *@param  emStatus 0: open the underline; 1: close the underline
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_PrnSetUnderLine(EM_PRN_UNDERLINE_STATUS emStatus);

/**
 *@brief	Set alignment method (not fulfilled yet)
 *@param  unType 0: left-aligned; 1center-aligned; 2 right-aligned; 3 close alignment
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_PrnFontRegister(ST_PRN_FONTMSG *pstMsg);
/**
 *@brief	 To select print font per register No.
 *@param  unFontId  the id of registered font(once set, it will override font set in NDK_PrnSetFont)
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_PrnSetUsrFont(uint unFontId);
/**
 *@brief	 obtaining number of lines of bitmap printed this time.
 *@retval  punLine returns number of lines
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_PrnGetDotLine(uint *punLine);
/**
 *@brief	 printing images in bmp, png or other format
 *@details  this function will decode image stored in pos and save it to dot matrix buffer, however image decoding takes time and may cause a certain length of latency if necessary.
 *@param  pszPath path of image
 *@param  unXpos is the row position of upper-left corner of image and  xpos+xsize (width value of image after decoding) must <=ndk_PR_MAXLINEWIDE￡¨384 for normal mode and 384/2 for horizontal enlargement￡?
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_PrnPicture(uint unXpos,const char *pszPath);

/**
 *@brief	Set to print pages long (applies only to needle play)
 *@details   To set printer to print pages long, the API for needles and only take effect
 *@param  len	Page length range (0 < = len < = 792)
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_PrnSetPageLen(uint len);
/**
 *@brief	Load BDF Font
 *@detail  Use this function to load BDF font into memory, the larger fonts can take some time.
 *@param  pszPath BDF's path
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/

int NDK_PrnLoadBDFFont(const char *pszPath);
/**
 *@brief	The contents of the print BDF font
 *@param  pusText unsigned short Types of data.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/

int NDK_PrnBDFStr(ushort *pusText);

/**
 *@brief	Set the BDF font attributes
 *@param  unXpos  Left offset domain is: 0-288 (the default is zero)
 *@param  unLineSpace  Line spacing range: 0-255 (the default is zero)
 *@param  unWordSpace  Space domain is: 0-255 (the default is zero)
 *@param  unXmode  Lateral magnification (note that the font of the MaxWidth * unXmode must not exceed 384, otherwise failure)
 *@param  unYmode  Longitudinal magnification (note that the font MaxHeight * unYmode must not more than 48, otherwise failure)
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/

int NDK_PrnSetBDF(uint unXpos,uint unLineSpace,uint unWordSpace,uint unXmode,uint unYmode);

/** @} */ // Print module end


/** @addtogroup FileSystem
* @{
*/

/**
 *@brief 		open file.
 *@details
 *@param    pszName file name
 *@param    pszMode open mode "r" (open as read only, if file does not exist then fail) or "w"(open as write, if file does not exist, then create it).
 *@return
 *@li	 fd				If operation succeeded, return file descriptor 
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_FsOpen(const char *pszName,const char *pszMode);


/**
 *@brief 		to close file 
 *@details
 *@param    nHandle file handle
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_FsClose(int nHandle);

/**
 *@brief 		to read unLength of characters from nHandle file opened, starting from current pointer, to psBuffer.  
 *@details
 *@param    nHandle file handle
 *@param    unLength	length of characters that needs to be read
 *@retval    psBuffer	the buffer to read to; it is important to read enough length of bytes
 *@return
 *@li	length				actual length of file read
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_FsRead(int nHandle, char *psBuffer, uint unLength );

/**
 *@brief 		writing unLength of bytes into nHandle file that already opened.
 *@details
 *@param    nHandle file handle
 *@param    psBuffer	the buffer where file content is written to
 *@param    unLength	the length that writing requires
 *@return
 *@li	length				returns actual length written into file  
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_FsWrite(int nHandle, const char *psBuffer, uint unLength );

/**
 *@brief 		to move file pointer to a position ulDistance away from unPosition.
 *@details
 *@param    nHandle file handle
 *@param    ulDistance is the number of displacement of read/write position per paramter of unPostion.
 @param    unPosition is the length of characters that needs to be read
 						SEEK_SET the parameter of offset is new read/write postion.
						SEEK_CUR is to increase ?°offset?± units of displacement started from current read/write position.
						SEEK_END is to let read/write position point to end of file and increase "offset?± units of displacement.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_FsSeek(int nHandle, ulong ulDistance, uint unPosition );

/**
 *@brief 		cancel specified file
 *@details
 *@param    pszName name of file to be deleted
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_FsDel(const char *pszName);

/**
 *@brief 		file length
 *@details
 *@param    pszName file name
 *@retval   punSize return value of file size
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_FsFileSize(const char *pszName,uint *punSize);

/**
 *@brief 		file rename
 *@details
 *@param    pszsSrcname original file name
 *@param    pszDstname target file name
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_FsRename(const char *pszsSrcname, const char *pszDstname );

/**
 *@brief 		test if file exists
 *@details
 *@param    pszName file name
 *@return
 *@li	NDK_OK				operation succeeded (file exists)
 *@li	other EM_NDK_ERR		operation failed
*/

int NDK_FsExist(const char *pszName);

/**
 *@brief 		file truncation 
 *@details   NDK_FsTruncate() will change file length specified by parameter ofpszPath to size specified by parameter of unLen. If previous file size is larger than parameter of unLen specifies, the excess part will be deleted.
 		   			if previous file size is smaller than unLen specifies, the deficient part will be supplemented with 0xff
 *@param    pszPath file path
 *@param    unLen is the length to truncate
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_FsTruncate(const char *pszPath ,uint unLen );

/**
 *@brief 	  	reading position of file stream 
 *@details   is used to obtain current read & write postion of file stream
 *@param    nHandle file handle
 *@retval    pulRet position of file stream
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_FsTell(int nHandle,ulong *pulRet);

/**
 *@brief 	  	to get the space usage of file system disk 
 *@details
 *@param    	unWhich :0-- disk space used 1-- free disk space
 *@retval     pulSpace returns amount of disk space used or amount of free space 
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_FsGetDiskSpace(uint unWhich,ulong *pulSpace);
/**
 *@brief 		directory creation
 *@details
 *@param    pszName directory name
 *@return
 *@li	 NDK_OK				returns if operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/

int NDK_FsCreateDirectory(const char *pszName);


/**
 *@brief 		to delete directory.
 *@details
 *@param    pszName directory name
 *@return
 *@li	 NDK_OK				returns if operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/

int NDK_FsRemoveDirectory(const char *pszName);
/**
 *@brief 		file system formatting
 *@details	this function only works on traditional pos, for pos with gp platform, it will return -1 directly 
 *@return
 *@li	 NDK_OK				returns if operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/

int NDK_FsFormat(void);


/**
 *@brief 		to list all files under specified directory
 *@details	the size sent to psBuf must be large enough to avoid overflow; pbuf will have 20 bytes to store one file name
 						filename shall be stored in the first 19 bytes, the excess part (if any) will be truncated automatically. 1 in 20th byte indicates this file is a folder while 0 is an ordinary file 
 *@param       pPath specifies the directory to read
 *@retval        psBuf stores file name to pbuf and returns
 *@retval        punNum returns total number of files under this directory
 *@return
 *@li	 NDK_OK				returns if operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_FsDir(const char *pPath,char *psBuf,uint *punNum);

/** @} */ // end of file system module


/** @addtogroup ApplicationManagement
* @{
*/

#define NDK_APP_NAME_MAX_LEN		32	/**< max. length of application name*/
#define NDK_APP_VER_MAX_LEN			16	/**<maximum length of version*/
#define NDK_APP_BUILD_TIME_LEN		32	/**<maximum length of creation time*/

/**
 *@brief application info. This structure is used in NLD structure, involving complementing. no change is allowed to definition of structure, or it will be inconsistent with info packed by download tool. 
*/
typedef struct APPINFO{
    uchar 	szAppName[NDK_APP_NAME_MAX_LEN + 1];		/**<user program name*/
    uchar	szVerBuf[NDK_APP_VER_MAX_LEN + 1];			/**<user program version info*/
    int		nSeriNo;									/**<Serial No. V2 reserves it, but the meaning differs	*/
    uchar	szBuildTime[NDK_APP_BUILD_TIME_LEN + 1];	/**<when file is compiled*/
    int		nIsMaster;									/**<master control symbol*/
    uint	sunReverse[3];
}ST_APPINFO;

typedef int (*CallbackMock)(int, void *,int,void **,int *);

/**
 *@brief	Set the callback function pointer
 *@param	NDK_EventMain	Function's address
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_AppSetEventCallBack(CallbackMock NDK_EventMain);

/**
 *@brief	运行应用程序
 *@param	pszAppName	应用名称。
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_AppRun(const uchar *pszAppName);

/**
 *@brief	To execute event operation
 *@param	pszFilename		application name
  *@param	nModuleId		ExecEvent ID
 *@param	psInEventMsg	input event message
 *@param	nInlen			length of input event
 *@param	nMaxOutLen		length of output event allowed
 *@retval	psOutEventMsg	application message obtained
 *@retval	pnOutLen		length of data actually input
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_AppDoEvent(const uchar *pszFileName,int nModuleId,const void *pvInEventMsg, int nInlen, void *pvOutEventMsg, int nMaxOutLen, int *pnOutLen);

/**
 *@brief	Get installed a sign of whether to need to restart the application
 *@param	pnRebootFlag		Output parameters 1 is installed applications require a restart to take effect, 0 don't need to restart
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_AppGetReboot(int *pnRebootFlag);
/**
 *@brief	Load application
 *@param	pszFilename		application name
 *@param	nRebootFlag		reboot flag, this parameter is only valid for traditional POS terminal
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_AppLoad(const uchar *pszFilename, int nRebootFlag);

/**
 *@brief	 to obtain application info
 *@param	pszAppName	Application name, can input is NULL.
 *@param	nPos		offset; this offset is info table offset in system, and is download-order concerned.
 *@param	nSizeofInfo	maximum length of output application info
 *@retval	pstAppInfo	application info obtained
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_AppGetInfo(const uchar *pszAppName, int nPos, ST_APPINFO *pstAppInfo, int nSizeofInfo);

/**
 *@brief	 to remove application program
 *@param	pszAppName	application name
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_AppDel(const char *pszAppName);

/**
 *@brief	Run background services program
 *@param	pszAppName	Application name.
 *@param	argv Application of operating parameters
 *@param	block:  1 Block until the backend application exit
                    0 parallel running

 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_AppEXECV(const uchar *pszAppName, char * const argv[],char block);
/** @} */ // Many application modules

/** @addtogroup algorithm
* @{
*/
#define MAX_RSA_MODULUS_LEN		512				/**< Maximum modulus length */
#define MAX_RSA_PRIME_LEN		256				/**< Maximum modulus prime length */

/**
 *@brief symmetric key algorithm
*/
typedef enum{
	ALG_TDS_MODE_ENC = 0,		/**< DES encryption*/
	ALG_TDS_MODE_DEC = 1,		/**< DES decryption*/
}EM_ALG_TDS_MODE;

/**
 *@brief length of key for RSA algorithm 
*/
typedef enum{
	RSA_KEY_LEN_512  = 512,
	RSA_KEY_LEN_1024 = 1024,
	RSA_KEY_LEN_2048 = 2048,
}EM_RSA_KEY_LEN;

/**
 *@brief exponents for RSA algorithm 
*/
typedef enum{
	RSA_EXP_3 = 0x03,
	RSA_EXP_10001 = 0x10001,
}EM_RSA_EXP;

/**
 *@brief RSA public key
*/
typedef struct {
    ushort bits;       							/**< modulus in bits */
    uchar modulus[MAX_RSA_MODULUS_LEN+1];      	/**<modulus length */
	uchar publicExponent[MAX_RSA_MODULUS_LEN+1]; 	/**< public key exponent */
    uchar exponent[MAX_RSA_MODULUS_LEN+1];     	/**< private key exponent */
    uchar prime[2][MAX_RSA_PRIME_LEN+1];      	/**< pq prime number */
    uchar primeExponent[2][MAX_RSA_PRIME_LEN+1]; 	/**< division value of prime number and exponent */
    uchar coefficient[MAX_RSA_PRIME_LEN+1];  	 	/**< division value of prime number and prime number */
}ST_RSA_PRIVATE_KEY;

/**
 *@brief RSA private key
*/
typedef struct {
    ushort bits;                    			/**< modulus in bits */
    uchar modulus[MAX_RSA_MODULUS_LEN+1];  		/**< modulus length */
    uchar exponent[MAX_RSA_MODULUS_LEN+1];		/**< exponent */
}ST_RSA_PUBLIC_KEY;

/**
 *@brief 	Des calculation
 *@param	psDataIn	buffer for data to encrypt 
 *@param	psKey		key buffer of a length 8, 16 or 24
 *@param    nKeyLen     key length,,is of a value 8, 16 or 24 only
 *@param	nMode		encryption mode
 *@retval	psDataOut	output data
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_AlgTDes(uchar *psDataIn, uchar *psDataOut, uchar *psKey, int nKeyLen, int nMode);

/**
 *@brief	sha1 calculation
 *@param	psDataIn	input data
 *@param	nInlen		data length 
 *@retval	psDataOut	output data (calculation result of sha1 is of a length of 20 bytes)
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_AlgSHA1(uchar *psDataIn, int nInlen, uchar *psDataOut);

/**
 *@brief		sha256 calculation
 *@param	psDataIn	input number
 *@param	nInlen		data length
 *@retval	psDataOut	output data (calculation result of sha256 is of a length of  bytes)
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_AlgSHA256(uchar *psDataIn, int nInlen, uchar *psDataOut);

/**
 *@brief		sha512 calculation
 *@param	psDataIn	input number
 *@param	nInlen		encryption mode
 *@retval	psDataOut	output data (calculation result of sha512 is of a length of  bytes)
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_AlgSHA512(uchar *psDataIn, int nInlen, uchar *psDataOut);

/**
 *@brief	RSA key pair generation
 *@param	nProtoKeyBit		key length; now supports 512, 1024 and 2048 bits; refer to \ref EM_RSA_KEY_LEN "EM_RSA_KEY_LEN"
 *@param	nPubEType			exponent types, refer to \ref EM_RSA_EXP "EM_RSA_EXP"
 *@retval	pstPublicKeyOut		public key
 *@retval	pstPrivateKeyOut	private key
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_AlgRSAKeyPairGen( int nProtoKeyBit, int nPubEType, ST_RSA_PUBLIC_KEY *pstPublicKeyOut, ST_RSA_PRIVATE_KEY *pstPrivateKeyOut);

/**
 *@brief	RSA key pair encryption or decryption
 *@details	this function execute RSA encryption or decryption computation; encryption or decryption are fulfilled by adopting different keys; if (Modul,Exp) adopts private key, then encryption is executed; if public key, then decryption.
 			1st byte of psDataIn must be less than 1st byte of psModule. This function can achieve RSA computation of length equals or less than 2048 bits.
 *@param	psModule		module buffer
 *@param	nModuleLen		module length
 *@param	psExp			pointer of buffer that stores exponents for RSA algorithm, namely e; big-endian
 *@param	psDataIn		data buffer
 *@retval	psDataOut		output data
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_AlgRSARecover(uchar *psModule, int nModuleLen, uchar *psExp, uchar *psDataIn, uchar *psDataOut);

/**
 *@brief	RSA key pair check
 *@param	pstPublicKey		public key
 *@param	pstPrivateKey		private key
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_AlgRSAKeyPairVerify(ST_RSA_PUBLIC_KEY *pstPublicKey, ST_RSA_PRIVATE_KEY *pstPrivateKey);


/** @} */ // end of algorithm 


/** @addtogroup Security
* @{
*/

/**
 *@brief terminal key type
*/
typedef enum{
	SEC_KEY_TYPE_TLK=0,	/**<terminal loaded key*/
	SEC_KEY_TYPE_TMK,	/**<terminal MAC key*/
	SEC_KEY_TYPE_TPK,	/**<terminal PIN key*/
	SEC_KEY_TYPE_TAK,	/**<terminal MAC key*/
	SEC_KEY_TYPE_TDK,	/**<terminal data encryption & decryption key*/
}EM_SEC_KEY_TYPE;

/**
 *@brief key check mode
*/
typedef enum{
	SEC_KCV_NONE=0,		/**<no check*/
	SEC_KCV_ZERO,		/**<run DES/TDES encryption algorithm with 0x00 of 8 bytes, and first 4 bytes of ciphertext is obtained, which is KCV*/
	SEC_KCV_VAL,		/**<first, run odd parity with plaintext of key, then run DES/TDES algorithem with "\x12\x34x56\x78\x90\x12\x34\x56", first 4 bytes of ciphertext is obtained, which is KCV*/
	SEC_KCV_DATA,		/**<send in a string of data KcvData, run specific mode of MAC algorithm to [aucDstKeyValue(ciphertext) + KcvData] with source key pair, MAC of 8 bytes is obtained, which is KCV */
}EM_SEC_KCV;

/**
 *@brief MAC algorithm
*/
typedef enum{
	SEC_MAC_X99=0,      /**< X99 algorithm:o data is divided into blocks of 8 bytes, supplement with 0 if there is vacancy; exclusive or (XOR) of each encrypted block with next block, and then encrypt the result per key length*/
	SEC_MAC_X919,       /**< X99 algorithm: data is divided into blocks of 8 bytes, suppliment with 0 if vacancy, exclusive or (XOR) of each encrypted block with next block, and then encrypt the result per key DES,
                            last frame, if key is of length 16 bytes, then per 3DES; 8 bytes per DES*/
	SEC_MAC_ECB,        /**< after running exclusive or (XOR) operation on all data, proceed DES conversion with data, refer to UnionPay regulations on ECB algorithm*/
	SEC_MAC_9606,       /**< after exclusive or (XOR) of all data, run des algorithnon with data*/
}EM_SEC_MAC;
/**
 * varaible to fulfill overtime control during PIN input
 */
typedef enum {
	SEC_PIN_ISO9564_0=3,    /**<Lack of encryption, using master account password number fill 'F'*/
	SEC_PIN_ISO9564_1=4,    /**<Do not use the master account encryption, code digits for the random number*/
	SEC_PIN_ISO9564_2=5,    /**< do not encrypt with master account, fill in with ??F?ˉ to complete the length if password is too short*/
	SEC_PIN_ISO9564_3=6     /**<encrypt with master account, fill in with random numbers to complete the length if password is too short */
}EM_SEC_PIN;

/**
 *@brief DES algorithm type; it can run OR operation with different bits,
        e.g.: SEC_DES_ENCRYPT|SEC_DES_KEYLEN_8|SEC_DES_ECBMODE
            means to run encryption in ECB mode with key of length 8 bytes.  
*/
typedef enum{
	SEC_DES_ENCRYPT=0,                  /**<DES encription*/
	SEC_DES_DECRYPT=1,                  /**<DES decryption*/
	SEC_DES_KEYLEN_DEFAULT=(0<<1),      /**<encrypt with key of installation length*/
    SEC_DES_KEYLEN_8=(1<<1),            /**<to encrypt with key of 8 bytes*/
    SEC_DES_KEYLEN_16=(2<<1),           /**<to encrypt with key of 16 bytes*/
    SEC_DES_KEYLEN_24=(3<<1),           /**<to encrypt with key of 24 bytes*/
}EM_SEC_DES;

/**
 *@brief VPP The service returns the key values of definition
*/
typedef enum{
    SEC_VPP_KEY_PIN,					/**< Have PIN key and press, the application should show '*'*/
    SEC_VPP_KEY_BACKSPACE,				/**< Backspace key press*/
    SEC_VPP_KEY_CLEAR,					/**< Clear key press*/
    SEC_VPP_KEY_ENTER,					/**< Confirm key press*/
    SEC_VPP_KEY_ESC,					/**< pin enter cancel*/
    SEC_VPP_KEY_NULL					/**< pin no event occurs*/
}EM_SEC_VPP_KEY;

/**
 *@brief Offline check terminal mode
 */
typedef enum{
	SEC_OFFLINE_PIN_MODE_EMV=0,
}ST_SEC_OFFLINE_PIN_MODE;

/**
 *@brief State of terminal security attacks
 */
typedef enum{
	SEC_TAMPER_STATUS_NONE,					/**< No security against*/
	SEC_TAMPER_STATUS_HW,					/**< Hardware security attacks*/
	SEC_TAMPER_STATUS_CHECKFILE,			/**< File validation error*/
	SEC_TAMPER_STATUS_SEC_CONFIG,			/**< Security error register values*/
}EM_SEC_TAMPER_STATUS;

#define SEC_KEYBLOCK_FMT_TR31		(0x54523331)	/**<Extension of TR - 31 Key block Key installation package format, 0 x54523331 "TR31" */
/**
 *@brief Extended key installation package information, used to implement the TR - 31 and extended key installation package format
 *		  When the user wants to use TR - 31 encapsulated package to install key, will need to key the data encapsulated into ST_EXTEND_KEYBLOCK structure,
 *		  And stored in the structure of ST_SEC_KEY_INFO sDstKeyValue [24] members, passed to key installation interface, the system will try to use the format parses the installation key.
*/
typedef struct {
	unsigned int format;		/**< Extend key installation package format, currently only support SEC_KEYBLOCK_FMT_TR31 TR - 31 format*/
	unsigned int len;			/**< Key installation package data (pblock) length*/
	char *pblock;				/**< The key data pointer*/
}ST_EXTEND_KEYBLOCK;

/**
 *@brief KeyInfo 
*/
typedef struct{
    uchar 	ucScrKeyType; 		/**< type of source key that diffused this key, refer to KEY_TYPE, it shall not be lower than key level ucDstKeyType is at*/
    uchar 	ucDstKeyType; 		/**< type of destination key, refer to KEY_TYPE */
    uchar 	ucScrKeyIdx;		/**< index of source key that diffused this key; typically index starts from 1; if this variable equals 0, then this key is written in plaintext */
    uchar 	ucDstKeyIdx;		/**< index of destination key */
    int 	nDstKeyLen;			/**< length of destination key:8, 16, 24 */
    uchar 	sDstKeyValue[24];	/**< content to write to key */
}ST_SEC_KEY_INFO;

/**
 *@brief check info
*/
typedef struct{
    int 	nCheckMode; 		/**< check mode */
    int 	nLen;				/**< check data area length */
    uchar 	sCheckBuf[128];		/**< check data buffer */
}ST_SEC_KCV_INFO;

/**
 *@brief cyphortext offline PIN key
*/
typedef struct
{
	uint	unModlen;					/**< length of modulus for public encrytion key  */
	uchar	sMod[MAX_RSA_MODULUS_LEN];  /**< modulus for public key for encryption; big-endian, fill in with 0 if vacancy*/
	uchar	sExp[4];       				/**< modulus for public key for encryption; big-endian, fill in with 0 if vacancy*/
	uchar	ucIccRandomLen;   			/**< length of random number obtained from card  */
	uchar	sIccRandom[8];   			/**< random number obtained from card  */
}ST_SEC_RSA_PINKEY;

/**
 *@brief RSA key infor
*/
typedef struct {
    ushort usBits;                    		/**< RSA key, number of bits */
    uchar sModulus[MAX_RSA_MODULUS_LEN+1];  	/**< modulus */
    uchar sExponent[MAX_RSA_MODULUS_LEN+1]; 	/**< exponent */
    uchar reverse[4];							/**< Swallow the 4 bytes, used in the key store*/
}ST_SEC_RSA_KEY;

/**
 *@brief	to read security interface version
 *@retval	pszVerInfoOut	Version info (less than 16 bytes)
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecGetVer(uchar * pszVerInfoOut);

/**
 *@brief	to obtain random number
 *@param	nRandLen		length need to obtain
 *@retval	pvRandom		random number buffer
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other\ref EM_NDK_ERR "EM_NDK_ERR"		operation failed
*/
int NDK_SecGetRandom(int nRandLen , void *pvRandom);

/**
 *@brief	 To set security configuration
 *@details	1. subsequent operations will proceed control per security configuration info set by user with this function. 
 			If this function is not called to set security configuration, subsequent operations will proceed per minimum security configuration by default.
 			2. typically, security configuration info is only allowed to rise than fall in level (if any parameter in configuration info parameter table falls from 1 to 0, it will be considered as security level reduced).  
 *@param	unCfgInfo		configuration info
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecSetCfg(uint unCfgInfo);

/**
 *@brief	 to read security configuration
 *@retval	punCfgInfo		configuration info
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecGetCfg(uint *punCfgInfo);

/**
 *@brief	read kcv value of key
 *@details	To obtain KCV value of key for both parties of session to execute key check; encrypt a section of data with specified key and algorithm and return some
 *@param	ucKeyType		Key type
 *@param	ucKeyIdx		Key Serial No.
 *@param	pstKcvInfoOut	KCVencryption mode
 *@retval	pstKcvInfoOut	KCV value
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecGetKcv(uchar ucKeyType, uchar ucKeyIdx, ST_SEC_KCV_INFO *pstKcvInfoOut);

/**
 *@brief	 to erase all keys 
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecKeyErase(void);

/**
 *@brief	to write a key, incl. writing and diffusing TLK, TMK and TWK; also choose to check correctness of key with KCV. 
 *@details
 	PED adopts 3-layer key system, and layers from top down are:
	TLK-Terminal Key Loading Key
    	private key held by acquiring bank or POS operator which is directly written by its holder under secured conditions.
    	each PED terminal has only one such key, so the index No. of key is from 1 to 1.  

	TMK-Terminal Master Key=Acquirer Master Key
		is master key for terminal or called master key for acquiring bank   keys of this type can amount to 100 in number, so the index no. is from 1 to 100. 
		TMK can be directly written under secured conditions; write TMK directly, and make it consistent with MK/SK key system by diffusing TWK.
	TWK-Transaction working key = Transaction Pin Key + Transaction MAC Key + Terminal DES Enc Key + Terminal DES DEC/ENC Key
		Terminal working key for PIN ciphertext, MAC and other operations. keys of this type can amount to 100 in number, so the index no. is from 1 to 100. 
		TPK: is to calculate PIN Block after application inputs PIN.
		TAK: is to calculate MAC for message communication in the application.
		TEK: is to provide DES/TDES encrypted transmission or storage for sensitive data in the application.
		TEK: is to provide DES/TDES encryption or decryption for sensitive data in the application.
	TWK can be written under secured conditions; TWK directly written is consistent with Fixed Key system. Each key has its index No., length, usage and tag. 
	wherein key tag is set via API before key is written, in order to authorize this key for use and ensure it won't be misused. 

	DUKPT key mechanism:
	DUKPT[Derived Unique Key Per Transaction]key management system is designed for providing one unique key for one transaction, and the working key [PIN、MAC] for each transaction differs.
	It has introduced KSN [Key Serial Number] concept; KSN is the essential factor to achieve one transaction one key. Each KSN corresponds to a key; different keys can be generated per usage.
 	10 groups of such keys are allowed; user has to select index No. of group when writing TIK and select proper group index when DUKPT key is used 
 *@param	pstKeyInfoIn		key info
 *@param	pstKcvInfoIn		key check info
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecLoadKey(ST_SEC_KEY_INFO * pstKeyInfoIn, ST_SEC_KCV_INFO * pstKcvInfoIn);

/**
 *@brief	 setting the minimum time interval between two PINBlock or MAC calculations.
 *@details 	method of calculating PINBLOCK time interval: 
 			defaulted as 120s, so it can only be called for 4 times, in other words, TPKIntervalTimeMs is 30s by default; call this function to reset, and allows for 4 times of calling within a period of 4*TPKIntervalTimeMs
 			e.g. incoming TPKIntervalTimeMs is 20000(ms), only 4 times of calling is allowed in 80s
 *@param	unTPKIntervalTimeMs	PIN key calculation time interval  0 ¨C adopt default value, 0xFFFFFFFF, no change made
 *@param	unTAKIntervalTimeMs	MAC key calculation time interval  0 ¨C adopt defaulted value, 0xFFFFFFFF, no change made
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecSetIntervaltime(uint unTPKIntervalTimeMs, uint unTAKIntervalTimeMs);

/**
 *@brief	 Set the function key function 
 *@details 	 to define usage of function keys during password input
 *@param	ucType	to define usage type of function key 
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecSetFunctionKey(uchar ucType);

/**
 *@brief	MAC calculation 
 *@param	ucKeyIdx		key serial No.
 *@param	psDataIn		input data
 *@param	nDataInLen		input data length
 *@param	ucMod			MAC calculation mode, refer to /ref EM_SEC_MAC "EM_SEC_MAC"
 *@retval	psMacOut		MAC value, 8 bytes in length
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecGetMac(uchar ucKeyIdx, uchar *psDataIn, int nDataInLen, uchar *psMacOut, uchar ucMod);

/**
 *@brief	obtain PIN Block
 *@param	ucKeyIdx		key serial No.
 *@param	pszExpPinLenIn	 Password length, can be used for segmentation e.g. 0, 4, 6
 *@param	pszDataIn		input PIN BLOCK per ISO9564
 *@param	ucMode			calculation mode, refer to /ref EM_SEC_PIN "EM_SEC_PIN"
 *@param	nTimeOutMs		timeout (Don't allow more than 120 seconds)uint: ms
 *@retval	psPinBlockOut	    PIN Block output
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecGetPin(uchar ucKeyIdx, uchar *pszExpPinLenIn,const uchar * pszDataIn, uchar *psPinBlockOut, uchar ucMode, uint nTimeOutMs);

/**
 *@brief	 DES calculation
 *@details 	 to execute des calculation with specified key: note: to encrypt and decrypt with serial no. 1~100 
 *@param	ucKeyType		DES key type
 *@param	ucKeyIdx		DESkey serial No.
 *@param	psDataIn		data info
 *@param	nDataInLen		data length 
 *@param	ucMode			encryption mode, refer to /ref EM_SEC_DES "EM_SEC_DES"
 *@retval	psDataOut		data output info
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecCalcDes(uchar ucKeyType, uchar ucKeyIdx, uchar * psDataIn, int nDataInLen, uchar *psDataOut, uchar ucMode);

/**
 *@brief to check plaintext offline PIN
 *@details 	 Obtain plaintext PIN, send plaintext PIN BlOCK directly to card per card command and card channel no. provided by application (PIN BLOCK format is described in usage section). 
 *@param	ucIccSlot		IC card No.

 *@param	pszExpPinLenIn	Password length, can be used to break up, e.g. 0, 4, 6
 *@param	ucMode			IC card calculation mode (support EMV only)
 *@param	unTimeoutMs		timeout
 *@retval	psIccRespOut	answer-back code for card
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecVerifyPlainPin(uchar ucIccSlot, uchar *pszExpPinLenIn, uchar *psIccRespOut, uchar ucMode,  uint unTimeoutMs);

/**
 *@brief	 to check plaintext PIN offline
 *@details 	 Obtain plaintext PIN, encrypt plaintext PIN with RsaPinKey provided by application per EMV regulations, and then send ciphertext PIN directly to card per card command and card channel no. provided by application
 *@param	ucIccSlot		IC card No.
 *@param	pszExpPinLenIn	Password length, can be used to break up, e.g. 0, 4, 6
 *@param	pstRsaPinKeyIn	RSA key data
 *@param	ucMode			IC card calculation mode (support EMV only)
 *@param	unTimeoutMs		timeout
 *@retval	psIccRespOut	answer-back code for the card
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecVerifyCipherPin(uchar ucIccSlot, uchar *pszExpPinLenIn, ST_SEC_RSA_KEY *pstRsaPinKeyIn, uchar *psIccRespOut, uchar ucMode, uint unTimeoutMs);

/**
 *@brief	to install DUKPT key
 *@param	ucGroupIdx		key group ID
 *@param	ucSrcKeyIdx		old key ID (key ID that is used to encrypt initial key value)
 *@param	ucKeyLen		key length
 *@param	psKeyValueIn	initial key value
 *@param	psKsnIn		    KSN value
 *@param	pstKcvInfoIn	Kcv info
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecLoadTIK(uchar ucGroupIdx, uchar ucSrcKeyIdx, uchar ucKeyLen, uchar * psKeyValueIn, uchar * psKsnIn, ST_SEC_KCV_INFO * pstKcvInfoIn);

/**
 *@brief	 to obtain DUKPT value
 *@param	ucGroupIdx		DUKPT key group ID
 *@retval	psKsnOut		current KSN No.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecGetDukptKsn(uchar ucGroupIdx, uchar * psKsnOut);

/**
 *@brief	 to increase KSN No.
 *@param	ucGroupIdx		DUKPT key group ID
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecIncreaseDukptKsn(uchar ucGroupIdx);

/**
 *@brief	 Obtain the DUKPT key PIN Block
 *@param	ucGroupIdx		key serial No.
 *@param	pszExpPinLenIn	Password length, can be used to break up, e.g. 0, 4, 6
 *@param	psDataIn		PIN BLOCK input per ISO9564
 *@param	ucMode			calculation mode
 *@param	unTimeoutMs		timeout
 *@retval	psKsnOut		current KSN No.
 *@retval	psPinBlockOut	PIN Block output
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecGetPinDukpt(uchar ucGroupIdx, uchar *pszExpPinLenIn, uchar * psDataIn, uchar* psKsnOut, uchar *psPinBlockOut, uchar ucMode, uint unTimeoutMs);

/**
 *@brief	 to calculate DUKPT key MAC
 *@param	ucGroupIdx		key group No.
 *@param	psDataIn		input number
 *@param	nDataInLen		input number length
 *@param	ucMode			MAC calculation mode
 *@retval	psMacOut		MAC value, 8 bytes in length 
 *@retval	psKsnOut		current KSN No.
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecGetMacDukpt(uchar ucGroupIdx, uchar *psDataIn, int nDataInLen, uchar *psMacOut, uchar *psKsnOut, uchar ucMode);

/**
 *@brief	 to calculate DES
 *@details 	to calculate des with specified key
 *@param	ucGroupIdx		DUKPT key group No.
 *@param	ucKeyVarType	key type
 *@param	psIV			initialization vector
 *@param	psDataIn		data info
 *@param	usDataInLen		data length
 *@param	ucMode			encryption mode
 *@retval	psDataOut		data output info
 *@retval	psKsnOut		current KSN No.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecCalcDesDukpt(uchar ucGroupIdx, uchar ucKeyVarType, uchar *psIV, ushort usDataInLen, uchar *psDataIn,uchar *psDataOut,uchar *psKsnOut ,uchar ucMode);

/**
 *@brief	to install RSA key
 *@param	ucRSAKeyIndex	Key serial No.
 *@param 	pstRsakeyIn		RSA Key info
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecLoadRsaKey(uchar ucRSAKeyIndex, ST_SEC_RSA_KEY *pstRsakeyIn);

/**
 *@brief	to install RSA key
 *@param	ucRSAKeyIndex	Key Serial No.
 *@param 	psDataIn		data to be encrypted, must not exceed key modulus
 *@param	nDataInLen		data length 
 *@retval	psDataOut		output data of length equals with modulus  
 *@retval	psKeyInfoOut	key info
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SecRecover(uchar ucRSAKeyIndex, const uchar *psDataIn, int nDataInLen, uchar *psDataOut, uchar *psKeyInfoOut);

/**
 *@brief	Access to keyboard input
 *@retval	psPinBlock		pinblock data
 *@retval 	nStatus			status value
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	其它EM_NDK_ERR		operation failed
*/
int NDK_SecGetPinResult(uchar *psPinBlock, int *nStatus);

/**
 *@brief	Set the key owner application name
 *@details 	Only for the use of system application (Keyloader), through the interface specifies the subsequent installation key name of the owner.
 *			When install the key, the system security services will determine the caller identity, and then make a decision whether to adopt this function sets the key owner name:
 *			-For normal user program:
 *				This setting is invalid, system security services can specify installation key owner directly for the current user program
 *			-Application of the system:
 *				Determine if Keyloader system program, the security services using NDK_SecSetKeyOwner () sets the application owner called the currently installed keys, * if Keyloader key owner is not set, the default key owner appointed Keyloader itself
 *				Without Keyloader system procedures, directly to the current system applied to the key owner
 *@param	pszName			Key application owner name (length is less than 256), if the transfer is an empty string, would be empty before setting the key owner
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_SecSetKeyOwner(char *pszName);

/**
 *@brief	Access to security attacks
 *@retval	status			State security attacks reference/ref EM_SEC_TAMPER_STATUS EM_SEC_TAMPER_STATUS ""
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_SecGetTamperStatus(int *status);

/** @} */ // End of the Security Module



/** @addtogroup SerialCommunication 
* @{
*/


/**
 *@brief  A serial port choice
*/
typedef enum {
    PORT_NUM_COM1 = 0,	/**<serial port 1*/
    PORT_NUM_COM2 = 1,	/**<serial port 2*/
    PORT_NUM_WIRELESS = 2,	/**<wireless module*/
    PORT_NUM_MUX1 = 3,	/**<Multiplexing 1*/
    PORT_NUM_MUX2 = 4,	/**<Multiplexing 2*/
    PORT_NUM_MUX3 = 5,	/**<Multiplexing 3*/
    PORT_NUM_MODEM = 6,	/**<The cable module*/
    PORT_NUM_WIFI = 7,	/**<Wifi module*/
    PORT_NUM_USB = 8	/**<USB module*/
} EM_PORT_NUM;


/**
 *@brief   initialize serial port, and to set baud rate,data bit, parity bit and stop bit and etc.; 
 	recommend to call this initialization function every time before using serial port
 *@details Support baud rate {300,1200,2400,4800,9600,19200,38400,57600,115200}\n 
 			Support data bit {8,7,6,5}\n
 			Parity Check mode {N(n):no parity; O(o):odd; E(e):even}\n
			Support stop bit {1,2}
 *@param	emPort	designated serial port
 *@param	Pszattr	communication rate and format string ,e.g. "115200,8,N,1",If only write baud rate, default is "8,N,1"
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_PortOpen(EM_PORT_NUM emPort, const char *pszAttr);

/**
 *@brief	Close serial 
 *@param	emPort	The specified serial port
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_PortClose(EM_PORT_NUM emPort);

/**
 *@brief	 to read a specified length of data from specified serial port before timeout, and save it to pszOutbuf
 *@param	emPort	designated serial port
 *@param	unLen	indicates the length of data to read; >0  
 *@param	nTimeoutMs	latency; unit: millisecond
 *@retval	pszOutbuf	Head pointer of data receiving buffer
 *@retval	pnReadlen	to return actual length read
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_PortRead(EM_PORT_NUM emPort, uint unLen, char *pszOutbuf,int nTimeoutMs, int *pnReadlen);

/**
 *@brief	 to send a specified length of data to specified serial port, and save it in pszInbuf
 *@param	emPort	designated serial port
 *@param	unLen	indicates the length of data to read
 *@param	pszInbuf	data sending buffer
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_PortWrite(EM_PORT_NUM emPort, uint unLen,const char *pszInbuf);

/**
 *@brief	 to determine if the sending buffer of specified serial port is empty
 *@param	emPort	designated serial port
 *@return
 *@li	NDK_OK	no data in buffer
 *@li	NDK_ERR	data in buffer
*/
int NDK_PortTxSendOver(EM_PORT_NUM emPort);

/**
 *@brief	 to clear receiving buffer for specified serial port
 *@param	emPort	designated serial port
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_PortClrBuf(EM_PORT_NUM emPort);

/**
 *@brief to define number of bytes in buffer that needs to be read 
 *@param	emPort	designated serial port
 *@retval	pnReadlen	return length of buffer read
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_PortReadLen(EM_PORT_NUM emPort,int *pnReadlen);

/** @} */ // end of serial port communication module


/** @addtogroup Modem
* @{
*/

/**
*@brief  modem connection state definition
*/
typedef enum MDM_STATUS
{
	MDMSTATUS_NORETURN_AFTERPREDIAL=0,
	MDMSTATUS_OK_AFTERPREDIAL=1,
	MDMSTATUS_CONNECT_AFTERPREDIAL=2,
	MDMSTATUS_MS_NODIALTONE = -2,
	MDMSTATUS_MS_NOCARRIER =	-3,
	MDMSTATUS_MS_BUSY = -4,
	MDMSTATUS_MS_ERROR = -5,
	MDMSTATUS_NOPREDIAL = -11,
}EM_MDMSTATUS;
/**
*@brief  modem initializaiton function?ˉs patch parameter type definition
*/
typedef enum MDM_Patchtype
{
	MDM_PatchType5=5,// patch package method by default
	MDM_PatchType4=4,
	MDM_PatchType3=3,//fast link to patch package
	MDM_PatchType2=2,
	MDM_PatchType1=1,
	MDM_PatchType0=0,
}EM_MDM_PatchType;

/**
 *@brief	sync dial initialization function 
 *@param	nType		patch parameter available to use per different lines setting.
 *@return	NILL
  *@li	NDK_OK				operation succeeded
 *@li	???üNDK_ERR_MODEM_COUNTRYFAIL	failed to patch
                 NDK_ERR_MODEM_SDLCINITFAIL    failed to initialize
*/
int NDK_MdmSdlcInit(EM_MDM_PatchType nType);

/**
 *@brief	 async modem initialization 
 *@param	nType 	patch parameter available to use per different lines setting
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	NDK_ERR_MODEM_ASYNINITFAIL	Initialization failed
*/
int NDK_MdmAsynInit(EM_MDM_PatchType nType);

/**
 *@brief	modem function Dial.
 *@param	pszDailNum 	dial number
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other NDK_ERR_MODEM_SDLCDIALFAIL		failed to sync dial
                 NDK_ERR_MODEM_INIT_NOT         not initialized before dial
*/
int NDK_MdmDial(const char * pszDailNum);

/**
 *@brief	 to detect modem state.
 *@param	*pemStatus 	actual return value of modem state
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_MdmCheck(EM_MDMSTATUS  *pemStatus);

/**
 *@brief	modem data sending.
 *@param	pszData 	data sent 
 *@param	unDatalen 	length of data sent 
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other \ref NDK_ERR_MODEM_SDLCWRITEFAIL	"NDK_ERR_MODEM_SDLCWRITEFAIL"	failed to sync send
				 \ref NDK_ERR_MODEM_ASYNWRITEFAIL  "NDK_ERR_MODEM_ASYNWRITEFAIL"    failed to async send
				 \ref NDK_ERR_MODEM_INIT_NOT   "NDK_ERR_MODEM_INIT_NOT"              not initialized 
*/
int NDK_MdmWrite(const char *pszData,uint unDatalen);

/**
 *@brief	modem data receiving.
 *@param	*pszData 	data received
 *@param	*punDatalen 	length of data received
  *@param	unSenconds	timeout in seconds
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other	NDK_ERR_MODEM_SDLCREADFAIL	sync receive operation failed
					NDK_ERR_MODEM_ASYNREADFAIL   async receive failed
					NDK_ERR_MODEM_INIT_NOT                 not initialized
*/
int NDK_MdmRead(char  *pszData,uint *punDatalen,uint unSenconds);

/**
 *@brief	modem function HangUp.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_MdmHangup(void);

/**
 *@brief	 clearing modem buffer.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_MdmClrbuf(void);

/**
 *@brief	To read length of modem.
 *@param	*punReadlen 	length value returned
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_MdmGetreadlen(uint *punReadlen);

/**
 *@brief	modem function Reset.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_MdmReset(void);

/**
 *@brief	AT command interaction function.
 *@param	pucCmdstr 	command sequence input
 *@param	pszRespData 	response data returned 
 *@param	punLen 	length of data returned
 *@param	unTimeout 	timout
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_MdmExCommand(uchar *pucCmdstr,uchar *pszRespData,uint *punLen,uint unTimeout);

/** @} */ // Modem ends

/** @addtogroup Wirelessmodem 
* @{
*/

/**
 *@brief  definitions of commands frequently used in wireless module
*/
typedef enum {
    WLM_CMD_E0=0,					/**<echo off*/
    WLM_CMD_CSQ=1,				/**<to get signal value*/
    WLM_CMD_CREG=2,				/**<network registration state*/
    WLM_CMD_CPIN=3,				/**<card PIN query */
    WLM_CMD_CPIN0=4,			/**<set PIN code*/
    WLM_CMD_CGATT0=5,			/**<logoff GPRS network*/
    WLM_CMD_CGATT1=6,			/**<register GPRS network*/
    WLM_CMD_DIAL=7,				/**<dial*/
    WLM_CMD_D2=8,					/**<hardwire hangup function ON*/
    WLM_CMD_COPS=9,				/**<register network*/
    WLM_CMD_CGMR=10,			/**<to get module version*/
    WLM_CMD_CGSN,         /**<<to obtain GSN No. (imei or meid)*/
    WLM_CMD_END,          /**<end of command, additional new commands shall be placed before it*/
    WLM_CMD_UNDEFINE=1024,		/**<undefined in list*/
    WLM_CMD_PUBLIC=255
} EM_WLM_CMD;

/**
 *@brief  AT command package
*/
typedef struct NDK_WL_ATCMD{
		EM_WLM_CMD AtCmdNo;	/**<command No.*/
		char *pcAtCmd;			/**<command string*/
		char *pcAddParam;		/**<additional parameters*/
}ST_ATCMD_PACK;

/**
 *@brief  definition of return status in wireless module
*/
typedef enum{
    WLM_STATUS_UNTYPED=4,	/**<return not defined*/
    WLM_STATUS_NO_CARRIER=3,/**<no carrier*/
    WLM_STATUS_RING=2,		/**<RING string*/
    WLM_STATUS_CONNECT=1,	/**<connection string*/
    WLM_STATUS_OK=0,				/**<succeeded*/
    WLM_STATUS_ERROR=-1,			/**<error*/
    WLM_STATUS_RET_ERROR=-114,	/**<error in return*/
}EM_WLM_STATUS;


/**
 *@brief	 wireless MODEM hardware reset
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_WlModemReset(void);

/**
 *@brief	wireless MODEM module OFF
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_WlModemClose(void);

/**
 *@brief 	wirelss MODEM initialization, switch from serial port to wireless and determine if module?ˉs AT command can be correctly responded, check SIM card.
 *@param	nTimeout	timeout, unit: MS
 *@param	pszPINPassWord	PIN code
 *@retval	pemStatus	if succeeded return wireless status; if failed, return NDK_FAIL	failed
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_WlInit(int nTimeout,const char *pszPINPassWord,EM_WLM_STATUS *pemStatus);


/**
 *@brief	 to obtain intensity of wireless MODEM signal
 *@retval	pnSq	signal intensity obtained, value of 	0-31 indicates successful,99	Unknown, -1 failed
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_WlModemGetSQ(int *pnSq);


/**
 *@brief	Send wireless module AT commands and receive returns a response
 *@param	pstATCmdPack	The AT command packet
 *@param	unMaxlen	Maximum length buffer (pszOutput buffer length) (= 0 1024) using the default length
 *@param	unTimeout	Command timeout, unit: MS
 *@retval	pszOutput	The output string
 *@retval	pemStatus	Returns wireless status on success, failure return WLM_STATUS_ERROR failure
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_WlSendATCmd(const ST_ATCMD_PACK *pstATCmdPack,char *pszOutput,uint unMaxlen,uint unTimeout,EM_WLM_STATUS *pemStatus);

/**
 *@brief	 To close RF
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_WlCloseRF(void);

/**
 *@brief	 to select SIM card
 *@param	ucSimNo	card No.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_WlSelSIM(uchar ucSimNo);


/** @} */ // end of wireless module


/** @addtogroup Socket 
* @{
*/


/**
 *@brief	 Open TCP communication channel
 *@retval	pnFd	return TCP channel handle
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_TcpOpen(uint *punFd);

/**
 *@brief	close TCP communication channel
 *@param	unFd	handle of TCP channel to be closed
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_TcpClose(uint unFd);

/**
 *@brief	 to wait for TCP successfully closed; timely exit if closed; after NDK_TcpClose() is called, must call this function again to ensure TCP link is closed completely
 *@param	unFd	TCPchannel handle
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_TcpWait(uint unFd);

/**
 *@brief	To bind this port's IP address and port No. 
 *@param	unFd		TCP channel handle
 *@param	pszMyIp	source address
 *@param	usMyPort	source port
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_TcpBind(uint unFd, const char *pszMyIp, ushort usMyPort);

/**
 *@brief	to connect server 
 *@param	unFd	TCP channel handle
 *@param	pszRemoteIp	remote address
 *@param	usRemotePort	remote port
 *@param	unTimeout	remote connection timeout in seconds
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_TcpConnect(uint unFd, const char *pszRemoteIp, ushort usRemotePort, uint unTimeout);

/**
 *@brief	 listening the connection requested
 *@param	unFd	TCP channel handle
 *@param	nBacklog	maximum length of queue waiting for connection
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_TcpListen(uint unFd, int nBacklog);

/**
 *@brief	 receiving connection request
 *@param	unFd	TCP channel handle
 *@param	pszPeerIp	address to receive connection entity
 *@param	usPeerPort	port to receive connection entity
 *@retval	punNewFd	returns TCP channel handle
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_TcpAccept(uint unFd, const char *pszPeerIp, ushort usPeerPort, uint *punNewFd);

/**
 *@brief	 to send data
 *@param	unFd	TCP channel handle
 *@param	pInbuf	address of send buffer 
 *@param	unLen	length of data sent 
 *@param	unTimeout	timeout in seconds
 *@retval	punWriteLen	To receive actual length sent, if NULL, do not receive.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_TcpWrite(uint unFd, const void *pInbuf, uint unLen, uint unTimeout, uint *punWriteLen);

/**
 *@brief	 to receive data
 *@param	unFd	TCP channel handle
 *@param	unLen	length of data received
 *@param	unTimeout	timeout in seconds
 *@retval	pOutbuf	to receive address of buffer
 *@retval	punReadlen	 to return actual length sent
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_TcpRead(uint unFd, void *pOutbuf, uint unLen, uint unTimeout, uint *punReadlen);



/** @} */ // Socket end of communication module


/** @addtogroup PPPCommunication
* @{
*/

/**
 *@brief  Long connection identifier of a macro definition
*/
#define STATUS_OPEN			0x03
#define STATUS_CLOSE		0x02
#define LCP_ECHO_OPEN  STATUS_OPEN  /**<According to the ECHO callback detection switch state*/
#define LCP_ECHO_CLOSE  STATUS_CLOSE
#define LCP_DCD_OPEN  (STATUS_OPEN<<2)/**<According to DCD switch state*/
#define LCP_DCD_CLOSE  (STATUS_CLOSE<<2)
#define LCP_PPP_KEEP  (STATUS_OPEN<<4)/**<Long said the PPP link maintaining switch state*/
#define LCP_PPP_UNKEEPED  (STATUS_CLOSE<<4)

/**
 *@brief  PPP Connection state is defined
*/
typedef enum {
    PPP_STATUS_DISCONNECT=0,		/**<PPP not connected*/
    PPP_STATUS_CONNECTING=2,		/**<PPP connecting*/
    PPP_STATUS_CONNECTED=5,			/**<PPP connected*/
    PPP_STATUS_DISCONNECTING=6		/**<hanging up*/
} EM_PPP_STATUS;

/**
 *@brief  PPP configuration parameter
*/
typedef struct {
    int nDevType;			/**<type, to tell if it is a wireless MODEM or wired MODEM￡?0 ¨C wireless, 1 - wired*/
    unsigned int nPPPFlag;	/**<flag that indicates if long-polling maintenance is supported; assign proper macro definition if necessary */
    char szApn[64];			/**<APN setting*/
    char szDailNum[32];		/**<dial number*/
    int (*ModemDial)(void);/**<fucntion Dial*/
    unsigned int PPPIntervalTimeOut; /**<time interval of sending data package of long-polling maintenance, <if it is 30S, no maintenance will be done to long-polling*/
    unsigned char nMinSQVal;	/**<minimum signal value allowed during initialization*/
    char szPin[31];				/**<SIM card PIN code*/
    char nPPPHostIP[20];		/**<host IP that long-polling requires to PIN*/
} ST_PPP_CFG;

/**
 *@brief	 PPP parameter configuration
 *@param	pstPPPCfg	ppp parameter structure (device type is set as wireless by default)
 *@param	nuValidLen	valid length of parameter
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_PppSetCfg(ST_PPP_CFG *pstPPPCfg, uint nuValidLen);

/**
 *@brief	 PPP dail
 *@param	pszUsername	username
 *@param	pszPassword	password
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_PppDial(const char *pszUsername,const char *pszPassword);

/**
 *@brief	 PPP hangup
 *@param	nHangupType	hangup type 0 non-blocking hangup 1 blocking hangup
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_PppHangup(int nHangupType);

/**
 *@brief	 to obtain PPP status
 *@retval	pemStatus	returns PPP status; if NULL, do not execute this operation 
 *@retval	pnErrCode	returns PPP status error; if NULL, do not execute this operation 
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_PppCheck(EM_PPP_STATUS *pemStatus, int *pnErrCode);

/**
 *@brief	to obtain local address and host address
 *@retval	punLocalAddr	returns local address; if NULL, do not receive 
 *@retval	punHostAddr	returns host address; if NULL, do not receive 
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_PppGetAddr(ulong *pulLocalAddr, ulong *pulHostAddr);

/**
 *@brief	 to convert an IP in dotted decimal format into a long integer number
 *@param	pszIp	IP address string
 *@retval	pulIpAddr	return long integer number converted to
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_PppAddrChange(register const char *pszIp, ulong *pulIpAddr);

/** @} */ // end of PPP communication module

/** @addtogroup Ethernet 
* @{
*/


/**
 *@brief 	to set network address (dynamically allocated address will also be changed after setting)
 *@param	pszIp	the head pointer of local IP address string; must not be NULL pointer; support IPV4 protocol only
 *@param	pszMask  the head pointer of local subnet mask code string; must not be NULL pointer; support IPV4 protocol only
 *@param	pszGateway	 the head pointer of local gateway address string; must not be NULL pointer; support IPV4 protocol only
 *@param 	pszDns	is the address of DNS server, if NULL, do not set DNS address
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_EthSetAddress(const char *pszIp, const char *pszMask, const char *pszGateway, const char *pszDns);


/**
 *@brief	 to obtain network MAC address
 *@retval	pszMacAddr	return MAC address
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_EthGetMacAddr(char *pszMacAddr);


/**
 *@brief	 to obtain network address
 *@retval	pszIp	to return IP address
 *@retval	pszGateway	to return gateway address
 *@retval	pszMask	to return subnet mask
 *@retval	pszDns	IP address of DNS; if NULL, do not get DNS address
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_EthGetNetAddr(char *pszIp, char *pszMask, char *pszGateway, char *pszDns);


/**
 *@brief	 setting Ethernet working mode
 *@param	nMode	woking mode
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_NetDHCP(void);


/**
 *@brief	network PING function
 *@param	pszIp	Local IP address, the first of the string pointer, pointer to null. Only supports IPV4
 *@param	nTimeout	Timeout, the unit is in seconds
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_NetPing(char *pszIp, uint nTimeout);


/**
 *@brief	DNS(domain name resolution)
 *@param	pszDnsIp	The IP address of the parsed
 *@param	pszDnsName	realm name
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_GetDnsIp(char *pszDnsIp,const char *pszDnsName);


/** @} */ // end of ethernet communication module


/** @addtogroup Magneticcard
* @{
*/

/**
 *@brief	to open magnetic card device
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR			operation failed
*/
int NDK_MagOpen(void);

/**
 *@brief to close magnetic card device
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR			operation failed
*/
int NDK_MagClose(void);


/**
 *@brief	 to reset magnetic head
 *@details	 to reset magnetic head and clear magnetic card buffer data
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR			operation failed
*/
int NDK_MagReset(void);


/**
 *@brief	 Determining if card swiped 
 *@retval	pcSwiped	1----swiped    0-----not swiped
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR			operation failed
*/
int NDK_MagSwiped(uchar * pcSwiped);


/**
 *@brief	 reading data from track 1, 2, 3 of magnetic card buffer
 *@details	this operation is to be used together with function MagSwiped; set the pointer of track that you don’t need data from as NULL，then such data won't be output
 *@retval	pszTk1	track 1
 *@retval	pszTk2	track 2
 *@retval	pszTk3	track 3
 *@retval	pnErrorCode	magnetic card error code
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR			operation failed
*/
int NDK_MagReadNormal(char *pszTk1, char *pszTk2, char *pszTk3, int *pnErrorCode);


/**
 *@brief	 reading raw data from track 1, 2, 3 of magnetic card buffer
 *@details	to be used together with function MagSwiped; set the pointer of track that you don’t need data from as NULL，then such data won't be output
 *@retval	pszTk1	track 1
 *@retval	punTk1Len	track 1 data length
 *@retval	pszTk2	track 2
 *@retval	punTk2Len	track 2 data length
 *@retval	pszTk3	track 3
 *@retval	punTk3Len	track 3 data length

 *@return:
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR			operation failed
*/
int NDK_MagReadRaw(uchar *pszTk1, ushort* punTk1Len, uchar *pszTk2, ushort* punTk2Len,uchar *pszTk3, ushort* punTk3Len );

/** @} */ // end of magnetic card module

/** @addtogroup IC 
* @{
*/

typedef enum{
  ICTYPE_IC,  /**<contact IC card*/
  ICTYPE_SAM1, /**<SAM1 card*/
  ICTYPE_SAM2, /**<SAM2 card*/
  ICTYPE_SAM3, /**<SAM3 card*/
  ICTYPE_SAM4, /**<SAM4 card*/
  ICTYPE_M_1, /**<at24c01 at24c02 at24c04 at24c08 at24c16 at24c32 at24c64 */
  ICTYPE_M_2, /**<sle44x2*/
  ICTYPE_M_3, /**<sle44x8*/
  ICTYPE_M_4, /**<at88sc102*/
  ICTYPE_M_5, /**<at88sc1604*/
  ICTYPE_M_6, /**<at88sc1608*/
}EM_ICTYPE;

/**
 *@brief	 to obtain ver. No. of driver
 *@retval 	pszVersion   　　version No. of driver; require buffer size no less than 16 bytes 
 *　
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR			operation failed
*/
int  NDK_IccGetVersion(char *pszVersion);

/**
 *@brief	 to set card type
 *@param	emIctype　  card type　
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR			operation failed
*/
int NDK_IccSetType(EM_ICTYPE emIctype);

/**
 *@brief	 to obtain card type
 *@retval 	pemIctype card tpype　
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR			operation failed
*/
int NDK_IccGetType(EM_ICTYPE *pemIctype);

/**
 *@brief	to obtain card status 
 *@retval 	pnSta   bit0：IC card 1 inserted - “1”; if not, “0”
 *					bit1: IC card 1 powered up - “1”; if not, “0”
 *					bit2：reserved, return “0”
 *					Bit3：reserved, return “0”
 *					bit4: SAM card 1 powered up - “1”; if not, “0”
 *					Bit5: SAM card 2 powered up - “1”; if not, “0”
 *					bit6: SAM card 3 powered up - “1”; if not, “0”
 *					bit7: SAM card 4 powered up - “1”; if not, “0”

 *　
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR			operation failed
*/
int NDK_IccDetect(int *pnSta);


/**
 *@brief 	powered up
 *@param	emIctype　 ICC_IC contact IC card,　
 *                    ICC_SAM1　ＳＡＭ１card,
 *					  ICC_SAM2　ＳＡＭ２card,
 *					  ICC_SAM3　ＳＡＭ３card,
 *					  ICC_SAM4　ＳＡＭ４card,
 *@retval 　　psAtrbuf indicates ATR data
 *@retval     pnAtrlen indicates length of ATR data
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR			operation failed
*/
int NDK_IccPowerUp (EM_ICTYPE emIctype, uchar *psAtrbuf,int *pnAtrlen);

/**
 *@brief	powered down
 *@param	emIctype　 ICC_IC contact IC card,	
 *                    ICC_SAM1　ＳＡＭ１card,
 *					  ICC_SAM2　ＳＡＭ２card,
 *					  ICC_SAM3　ＳＡＭ３card,
 *					  ICC_SAM4　ＳＡＭ４card,
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR			operation failed
*/
int NDK_IccPowerDown(EM_ICTYPE emIctype);

/**
 *@brief	IC card operations
 *@param	emIctype　 ICC_IC contact IC card,	
 *                    ICC_SAM1　ＳＡＭ１card,
 *					  ICC_SAM2　ＳＡＭ２card,
 *					  ICC_SAM3　ＳＡＭ３card,
 *					  ICC_SAM4　ＳＡＭ４card,
 *@param	nSendlen	length of data sent
 *@param	psSendbuf	data sent
 *@retval 	pnRecvlen    length of data received
 *@retval 	psRecebuf    data received
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR			operation failed
*/
int NDK_Iccrw(EM_ICTYPE emIctype, int nSendlen,  uchar *psSendbuf, int *pnRecvlen,  uchar *psRecebuf);

/** @} */ // end of IC card module

/** @addtogroup RF 
* @{
*/
typedef enum {
	RFID_Autoscan=		0x00,
	RFID_RC531=			0x01,
	RFID_PN512=			0x02,
	RFID_No=			0xFF,
}EM_RFID;

/**
 *@brief	 to obtain Version No of RF driver 
 *@param	pszVersion	Version No. string returned
 *@return
 *@li	NDK_OK			operation succeeded
 *@li	EM_NDK_ERR		operation failed
*/
int  NDK_RfidVersion(uchar *pszVersion);


/**
 *@brief	 RF interface item initialization; this can be used to determine if item is installed or operable
 *@retval 	psStatus  extension for backup
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_RfidInit(uchar *psStatus);


/**
 *@brief	ON RF output
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_RfidOpenRf(void);


/**
 *@brief	OFF RF output; this can reduce consumption and protect RF item.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_RfidCloseRf(void);


/**
 *@brief	to obtain card status (to tell if seek card operation executed; can be used to determine if Standby is available)
 *@return
 *@li	NDK_OK		seek card operation succeeded (status: busy)
 *@li	NDK_ERR_RFID_NOTACTIV		seek card operation failed  (status: idle)
*/
int NDK_RfidPiccState(void);


/**
 *@brief	 device enters Standby status by force
 *@return
 *@li	NDK_OK		execution succeeded
 *@li	NDK_ERR		execution failed
*/
int NDK_RfidSuspend(void);


/**
 *@brief	resume device  
 *@return
 *@li	NDK_OK		execution succeeded
 *@li	NDK_ERR		execution failed
*/
int NDK_RfidResume(void);


/**
 *@brief	To set strategy for card seeking (it's OK to deliver one setting before seek card operation executed; as for M1 card operation, set it as TYPE-A card mode)
 *@param	ucPicctype = 0xc, indicates seek card operation targets TYPE-A cards only
 *			   0xcb, indicates seek card operation targets TYPE-B cards only
 *			   0xcd, indicates seek card operation targets Type-A and TYPE-B cards.
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_RfidPiccType(uchar ucPicctype);


/**
 *@brief	 seek RF card (to detect if there is any card in swiping area)
 *@retval 	psPicctype	Type of card activated 0xcc=TYPE-A card, 0xcb=TYPE-B card
 *@return
 *@li	NDK_OK				seek card operation succeeded; card type is in picctype
 *@li	other EM_NDK_ERR		seek card operation failed 
*/
int NDK_RfidPiccDetect(uchar *psPicctype);


/**
 *@brief	 RF card activation (w/card), equalizing powerup.
 *@retval 	psPicctype	Type of card activated 0xcc=TYPE-A card, 0xcb=TYPE-B card
 *@retval	pnDatalen	 data length
 *@retval	psDatabuf	data buffer (A card is  UID; B card databuf[1]~[4] is UID，others are application and protocol info)
 *@return
 *@li	NDK_OK				activation succeeded
 *@li	other EM_NDK_ERR		activation failed
*/
int NDK_RfidPiccActivate(uchar *psPicctype, int *pnDatalen,  uchar *psDatabuf);


/**
 *@brief	Invalidate card by turning off RF read/write operation shall be followed by this operation, equalizing power down.
 *@param	ucDelayms	= 0, always OFF RF; ≠0，shut down for ucDelayms milliseconds and turn on RF again.
 *                      a 6～10ms shutdown will invalidate card. If not followed by consecutive read card operations, it shall be set as 0 to turn off RF. 
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_RfidPiccDeactivate(uchar ucDelayms);


/**
 *@brief	RF card APDU interaction, viz. read/write card process (activated))
 *@param	nSendlen		length of command sent
 *@param	psSendbuf		command sending buffer 
 *@retval 	pnRecvlen	length of data received
 *@retval	psRecebuf	data receiving buffer
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_RfidPiccApdu(int nSendlen, uchar *psSendbuf, int *pnRecvlen,  uchar *psRecebuf);


/**
 *@brief	M1 card seek (must set to seek card of TYPE-A)
 *@param	ucReqcode		0: request REQA; ≠0: wake WUPA, typically WUPA will be used 
 *@retval 	pnDatalen	 Length of data received (2 bytes)
 *@retval	psDatabuf		data receiving buffer
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_M1Request(uchar ucReqcode, int *pnDatalen, uchar *psDatabuf);


/**
 *@brief	M1 card anti-collision (when NDK_RfidPiccDetect has detected card)
 *@retval 	pnDatalen	length of date received(UID length)
 *@retval	psDatabuf	data receiving buffer(UID)
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_M1Anti(int *pnDatalen, uchar *psDatabuf);


/**
*@brief		M1 card selection (when NDK_M1Anti is successful)
*@param		nUidlen			uid length
*@param		pnUidbuf	     uid data buffer
*@retval 	psSakbuf	    return data for select card operation (1 byte SAK)
*@return
*@li	NDK_OK				operation succeeded
*@li	other EM_NDK_ERR		operation failed
*/
int NDK_M1Select(int nUidlen, uchar *pnUidbuf, uchar *psSakbuf);


/**
 *@brief	M1 card authentication key storage (one key only has to be stored once)
 *@param	ucKeytype		authentication key type A=0x00 ；B=0x01
 *@param	ucKeynum	 key serial No. (0~15)
 *@param	psKeydata		key, 6 bytes
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_M1KeyStore(uchar ucKeytype,  uchar ucKeynum, uchar *psKeydata);


/**
 *@brief	M1 card loads stored key (one key only has to be loaded once)
 *@param	ucKeytype	authentication key type A=0x00 ；B=0x01
 *@param    ucKeynum	 key serial No.(0~15，A/B each has 16 keys)
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_M1KeyLoad(uchar ucKeytype,  uchar ucKeynum);


/**
 *@brief	authenticate M1 card with key loaded
 *@param	nUidlen	uid length
 *@param	psUidbuf	uid data (obtained by NDK_M1Anti)
 *@param	ucKeytype	authentication key type A=0x00 ；B=0x01
 *@param    ucBlocknum	block No. to be authenticated (note: not sector No.!)
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_M1InternalAuthen(int nUidlen, uchar *psUidbuf, uchar ucKeytype, uchar ucBlocknum);


/**
 *@brief	M1 card with external KEY authentication 
 *@param	nUidlen	uid length
 *@param	psUidbuf	uid data (obtained by NDK_M1Anti)
 *@param	ucKeytype	authentication key type A=0x00 ；B=0x01
 *@param	psKeydata	key(6 bytes)
 *@param    ucBlocknum	block No. to be authenticated (note: it's not sector No.!)

 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_M1ExternalAuthen(int nUidlen, uchar *psUidbuf, uchar ucKeytype, uchar *psKeydata, uchar ucBlocknum);


/**
 *@brief	M1 card 'block’ read operation
 *@param	ucBlocknum	block No. to read
 *@retval	pnDatalen	length of block data read 
 *@retval	psBlockdata	block data
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_M1Read(uchar ucBlocknum, int *pnDatalen, uchar *psBlockdata);


/**
 *@brief	M1 card 'block' write operation
 *@param	ucBlocknum	No. of block to write
 *@param	pnDatalen	length of block data read
 *@param	psBlockdata	block data
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_M1Write(uchar ucBlocknum, int *pnDatalen, uchar *psBlockdata);


/**
 *@brief	 M1card ‘block’increment operation
 *@param	ucBlocknum	No. of block to execute increment operation. Note: increment operation targets only register, no actual writing into block data area; besides, the block data of card must meet increment/decrement format.
 *@param	nDatalen	incremental data length (4 bytes)
 *@param	psDatabuf	incremental data
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_M1Increment(uchar ucBlocknum, int nDatalen, uchar *psDatabuf);


/**
 *@brief	M1card ‘block’decrement operation
 *@param	ucBlocknum	No. of block that will execute decrement operation. Note: increment operation targets only register, no actual writing into block data area. besides, the block data of card must meet increment/decrement format.
 *@param	nDanalen	incremental data length (4 bytes)
 *@param	psDatabuf	incremental data
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_M1Decrement(uchar ucBlocknum, int nDanalen, uchar *psDatabuf);


/**
 *@brief	transmission operation after M1 card increment/decrement operation (actually writing register value to block data area of card)
 *@param	ucBlocknum	No. of block to execute increment operation
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_M1Transfer(uchar ucBlocknum);


/**
 *@brief	 M1card register value restoration (restore initial register value in order to invalidate increment/decrement operation previously done)
 *@param	ucBlocknum:   No. of block that will execute decrement operation 
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_M1Restore(uchar ucBlocknum);


/**
*@brief	easy & quick card seeking (is used to expedite test and other operations)
*@param	nModecode	  =0 normal card seeking; ≠0 rapid card seeking
*@return
*@li	NDK_OK				operation succeeded
*@li	other EM_NDK_ERR		operation failed
*/
int NDK_PiccQuickRequest(int nModecode);


/**
 *@brief	to shield the judgment that supports ISO1443-4 protocol
 *@param	nModecode	≠0, execute shield operation
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SetIgnoreProtocol(int nModecode);


/**
*@brief	read the setting that shield support of ISO1443-4 protocol  
*@retval	pnModecode	if ≠0, execute shielding
*@return
*@li	NDK_OK				operation succeeded
*@li	other EM_NDK_ERR		operation failed
*/
int NDK_GetIgnoreProtocol(int *pnModecode);


/**
 *@brief	to read RF interface chip type
 *@retval	pnRfidtype	see/ref EM_RFID "EM_RFID"
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int  NDK_GetRfidType(int *pnRfidtype);

/** @} */ // end of RF card module

/** @addtogroup System Interface
* @{
*/

/**
 *@brief  to get POS version and hardware info index No.
	      Note: notations on info returned by SYS_HWINFO_GET_HARDWARE_INFO are as follows:
				 to obtain POS hardware info, each byte represents a different module
				 different value in the same byte presents different chip type in the same module 
				 supports at least 63 external devices, parameter array sent by application no less than 64
				 the array returned ends with Ox00 which represents device type; each byte before 0x00 represents a module
		pinfo[0]: wireless module
			0xFF    :no wireless module
			0x01    :SIM300
			0x02    :M72
			0x03    :DTGS800
			0x04    :SM700
			0x05    :MC39I
			0x06    :DTM228C
			0x07    :MC8331
			0x08    :EM200
		pinfo[1]: RF module
			0xFF     :no RF module
			0x01     :RC531
			0x02     :PN512
		pinfo[2]: magnetic card module
			0xFF     : no magnetic card module
			0x01     :
			0x02     :
		pinfo[3]: scanning head module
			0xFF     : no magnetic card module
			0x01     :EM1300
			0x02     :EM3000
			0x03     :SE955
		pinfo[4]: support external passport keyboard?
			0xFF     : No
			0x01     : Yes
		pinfo[5]: number of serial ports
			0xFF     :NILL
			0x01     :1 
			0x02     :2
		pinfo[6]:suport USB?
			0xFF     : No
			0x01     : Yes
		pinfo[7]:MODEM module
			0xFF     : No
			0x01     : Yes
		pinfo[8]:wifi Module
			0xFF     : No wifi module
			0x01     : is "USI WM-G-MR-09" module
		pinfo[9]: print module
			0xFF     : no print module
    		0x01     :Yes	\n\n
  			pinfo[10]:Print module	\n
    		0xFF     :No print module	\n
    		0x01~0x7F     :hermosensitive	\n
    		0x82~0x7E     :Needle to play	\n\n
   			pinfo[11]:Whether to support touch screen	\n
    		0xFF     :No	\n
    		0x01     :Yes	\n\n
   			pinfo[12]:If there is a radio frequency (rf) LED lights	\n
    		0xFF     :No	\n
			0x01     : Yes  \n
*/
typedef enum {
	SYS_HWINFO_GET_POS_TYPE=0,      		/**<to get model of pos machine   			*/
	SYS_HWINFO_GET_HARDWARE_INFO,       /**<to obtain all types of hardware the POS machine that supports, detailed return values are as above*/
	SYS_HWINFO_GET_BIOS_VER,        		/**<to obtain bios version info 			 */
	SYS_HWINFO_GET_POS_USN,        		/**<to get machine serial No.    		*/
	SYS_HWINFO_GET_POS_PSN,        		/**<to get machine No.    		*/
	SYS_HWINFO_GET_BOARD_VER,       		/**<to get mainboard No.        			*/
	SYS_HWINFO_GET_CREDITCARD_COUNT,		/**<to get total number of card swiping of the pos					*/
	SYS_HWINFO_GET_PRN_LEN,				/**<to get total print length of the pos    		*/
	SYS_HWINFO_GET_POS_RUNTIME,          /**<to get pos' power up and operation time  */
	SYS_HWINFO_GET_KEY_COUNT,            /**<to get times of keypress of the pos  */
	SYS_HWINFO_GET_CPU_TYPE,           /**<get pos cpu type  */
} EM_SYS_HWINFO;

/**
 *@brief  Read the index number of system configuration information
*/
typedef enum {
	SYS_CONFIG_SLEEP_ENABLE,	    /**<Dormancy can make 0: banned 1: enabled */
	SYS_CONFIG_SLEEP_TIME,      	/**<Before entering the sleep time of standby time*/
	SYS_CONFIG_SLEEP_MODE,      	/**<Sleep mode 1: shallow sleep 2: deep dormancy*/
	SYS_CONFIG_LANGUAGE,			/**<Language acquisition system 0:1: Chinese English */
	SYS_CONFIG_APP_AUTORUN,      	/**<Boot automatically run MCP 0: disable 1: enabled*/
} EM_SYS_CONFIG;

/**
 *@brief  Hardware device information types
*/
typedef enum {
	SYS_HWTYPE_WIRELESS_MODEM=0,	/**<wirelessmodem */
	SYS_HWTYPE_RFID,				/**< radio frequency card*/
	SYS_HWTYPE_MAG_CARD,			/**< magcard*/
	SYS_HWTYPE_SCANNER,				/**< scan head*/
	SYS_HWTYPE_PINPAD,				/**< code keyboard*/
	SYS_HWTYPE_AUX,					/**< serial port*/
	SYS_HWTYPE_USB,					/**< USB*/
	SYS_HWTYPE_MODEM,				/**< modem*/
	SYS_HWTYPE_WIFI,				/**< wifi*/
	SYS_HWTYPE_ETHERNET,			/**< Ethernet*/
	SYS_HWTYPE_PRINTER,				/**< printer*/
	SYS_HWTYPE_TOUCHSCREEN,			/**< touch screen*/
	SYS_HWTYPE_RFIDLED,				/**< rf LED*/
	SYS_HWTYPE_MAX					/**< The maximum, only allowed in the end*/
} EM_SYS_HWTYPE;

/**
 *@brief Control the POS destroy all the LED light on the condition variable
*/
typedef enum {
	LED_RFID_RED_ON = 0x01,      		/**<   Control of radio frequency (rf) red lights			*/
	LED_RFID_RED_OFF = 0x02,       	/**<   Control of radio frequency (rf) red lights went out			*/
	LED_RFID_RED_FLICK = 0x03,        	/**<   Control of radio frequency flashing red lights			*/
	LED_RFID_YELLOW_ON = 0x04,      		/**<   Control of radio frequency (rf) yellow light			*/
	LED_RFID_YELLOW_OFF = 0x08,       	/**<   Control of radio frequency (rf) yellow lights went out			*/
	LED_RFID_YELLOW_FLICK = 0x0c,        	/**<   Control of radio frequency flashing yellow lights			*/
	LED_RFID_GREEN_ON = 0x10,      		/**<   Control of radio frequency (rf) green lights			*/
	LED_RFID_GREEN_OFF = 0x20,       	/**<   Control of radio frequency (rf) green lights went out			*/
	LED_RFID_GREEN_FLICK = 0x30,        	/**<   Control the rf green light flash			*/
	LED_RFID_BLUE_ON = 0x40,      		/**<   Control the rf blue light			*/
	LED_RFID_BLUE_OFF = 0x80,       	/**<   Control of radio frequency (rf) blue lights went out			*/
	LED_RFID_BLUE_FLICK = 0xc0,        	/**<   Control the rf blue lights flash			*/
	LED_COM_ON = 0x100,      		/**<   The light control communication			*/
	LED_COM_OFF = 0x200,       	/**<   Control communication lights went out			*/
	LED_COM_FLICK = 0x300,        	/**<   Lights flash control communication			*/
	LED_ONL_ON = 0x400,      		/**<   Control online lights			*/
	LED_ONL_OFF = 0x800,       	/**<   Control online lights went out			*/
	LED_ONL_FLICK = 0xc00       	/**<   Control online flash lamp			*/

} EM_LED;
/*major device number */
typedef enum {
    KEYBOARD,		/**<keypad */
    PRINTER,		/**<printer*/
    MAG,			/**<magcard*/
    ICCARD,			/**<IC card */
    RFID,			/**<RF card */
    MODEM_ID,		/**<MODEM*/
    WLS,			/**<wireless*/
    WIFI,			/**<WIFI*/
    POWER,			/**<ON OFF*/
    DEV_MAIN_NUM	/**<The main equipment*/
} EM_SS_DEVMAINID;

/**
 *@brief Statistics of the equipment ID
*/
typedef enum{
	SS_KEY_0_ID = (KEYBOARD<<16|0),
	SS_KEY_1_ID = (KEYBOARD<<16|1),
	SS_KEY_2_ID = (KEYBOARD<<16|2),
	SS_KEY_3_ID = (KEYBOARD<<16|3),
	SS_KEY_4_ID = (KEYBOARD<<16|4),
	SS_KEY_5_ID = (KEYBOARD<<16|5),
	SS_KEY_6_ID = (KEYBOARD<<16|6),
	SS_KEY_7_ID = (KEYBOARD<<16|7),
	SS_KEY_8_ID = (KEYBOARD<<16|8),
	SS_KEY_9_ID = (KEYBOARD<<16|9),
	SS_KEY_10_ID = (KEYBOARD<<16|10),
	SS_KEY_11_ID = (KEYBOARD<<16|11),
	SS_KEY_12_ID = (KEYBOARD<<16|12),
	SS_KEY_13_ID = (KEYBOARD<<16|13),
	SS_KEY_14_ID = (KEYBOARD<<16|14),
	SS_KEY_15_ID = (KEYBOARD<<16|15),
	SS_KEY_16_ID = (KEYBOARD<<16|16),
	SS_KEY_17_ID = (KEYBOARD<<16|17),
	SS_KEY_18_ID = (KEYBOARD<<16|18),
	SS_KEY_19_ID = (KEYBOARD<<16|19),
	SS_KEY_20_ID = (KEYBOARD<<16|20),
	SS_KEY_21_ID = (KEYBOARD<<16|21),
	SS_KEY_22_ID = (KEYBOARD<<16|22),
	SS_KEY_23_ID = (KEYBOARD<<16|23),
	SS_KEY_24_ID = (KEYBOARD<<16|24),
	SS_KEY_25_ID = (KEYBOARD<<16|25),
	SS_KEY_26_ID = (KEYBOARD<<16|26),
	SS_KEY_27_ID = (KEYBOARD<<16|27),
	SS_KEY_28_ID = (KEYBOARD<<16|28),
	SS_KEY_29_ID = (KEYBOARD<<16|29),
	SS_KEY_30_ID = (KEYBOARD<<16|30),
	SS_KEY_31_ID = (KEYBOARD<<16|31),
	SS_KEY_TOTAL_ID = (KEYBOARD<<16|33),

	SS_PRT_PAPER_ID = (PRINTER<<16|0),    	/**<Print in meters*/
	SS_PRT_HEADER_ID = (PRINTER<<16|1),		/**<Needle with the total*/
	SS_PRT_HEAT_ID = (PRINTER<<16|2),		/**<The thermal head heating time*/

	SS_MAG_TIMES_ID = (MAG<<16|0),			/**<Credit card number*/

	SS_ICCARD_BASE_ID = (ICCARD<<16|0),		/**<Card number*/

	SS_RFID_TIMES_ID = (RFID<<16|0),		/**<For card number*/

	SS_MODEM_TIMES_ID = (MODEM_ID<<16|0),	/**<MODEM number of connections*/
	SS_MODEM_FAILTIMES_ID = (MODEM_ID<<16|1),/**<MODEM number of connection*/
	SS_MODEM_SDLCTIME_ID = (MODEM_ID<<16|2),/**<MODEM duration(SDLC)*/
	SS_MODEM_ASYNTIME_ID = (MODEM_ID<<16|3),/**<MODEM duration(asynchronous)*/

	SS_WLS_TIMES_ID = (WLS<<16|0),			/**<Wireless connection times*/
	SS_WLS_FAILTIMES_ID = (WLS<<16|1),		/**<Wireless connection*/
	SS_WLS_PPPTIME_ID = (WLS<<16|2),		/**<The wireless connection time(PPP)*/

	SS_WIFI_TIMES_ID = (WIFI<<16|0),		/**<WIFI number of connections*/
	SS_WIFI_TIME_ID = (WIFI<<16|1),			/**<WIFI The connection time*/

	SS_POWER_TIMES_ID = (POWER<<16|0),		/**<Switch machine number*/
	SS_POWERUP_TIME_ID = (POWER<<16|1)		/**<available machine time*/
}EM_SS_DEVID;

/**
 *@brief The firmware version type
*/
typedef enum {
	SYS_FWINFO_PRO,      		/**<RELEASE   			*/
	SYS_FWINFO_DEV				/**<Development Version   			*/
} EM_SYS_FWINFO;

/**
 *@brief Statistical structure of the device ID corresponds to the primary ID, ID, and the corresponding statistics
*/
typedef struct st_ss_output
{
	int nDevMainID;      /**<Equipment main ID*/
	int nDevMinorID;    /**<Device time ID*/
	int nValue;			/**<statistic*/
}ST_SS_OUTPUT;
/**
 *@brief	Obtain the NDK library version number
 *@retval   pszVer	Version number string, buffer size is not less than 16 bytes
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_Getlibver(char *pszVer);

/**
 *@brief 		system initialization (not used yet)
 *@details
 *@return
 *@li	 fd				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_SysInit(void);
/**
 *@brief 		SYSEXIT 
 *@details
 *@return
 *@li	 fd				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_SysExit(int nErrcode);
/**
 *@brief 		POS restart
 *@details
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SysReboot(void);
/**
 *@brief 		POS shutoff
 *@details
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SysShutDown(void);
/**
 *@brief 		Beep only sounds once, if consecutive beeps are need, time delay can be added in between
 *@details
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SysBeep(void);
/**
 *@brief 		set volume of beep
 *@details
 *@param    unVolumn    parameter of volume to set, range of value; 0~5; defaulted as 5 if not set
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SysSetBeepVol(uint unVolumn);
/**
 *@brief 		to get volume of beep
 *@details
 *@retval    punVolumn    parameter for volume to set
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SysGetBeepVol(uint *punVolumn);
/**
 *@brief 		sound for a certain period of time at certain frequency 
 *@details
 *@param    unFrequency  frequency of sound, unit: Hz    ，range: 0 < unFrequency <=4000
 *@param    unSeconds duration of sound, unit: ms, range: unSeconds > 0
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SysTimeBeep(uint unFrequency,uint unSeconds);
/**
 *@brief 		to set if auto standby is allowed 
 *@param    unFlag  0: auto standby not allowed, 1: auto standby allowed, parameter of other values is illegal
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SysSetSuspend(uint unFlag);
/**
 *@brief 		to set if immediate standby 
 *@details  the if auto standby setting has no effect on this fuction; once this function is called, the machine will enter standby mode immediately
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SysGoSuspend(void);
/**
 *@brief 		to get power level
 *@retval   punVol  if it is plugged in, 0, or less return battery level
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SysGetPowerVol(uint *punVol);
/**
 *@brief 		unit delay (time unit: 0.1s)
 *@details
 *@param    unDelayTime delaytime, range: unDelayTime > 0
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SysDelay(uint unDelayTime);
/**
 *@brief 		unit delay (time unit: 0.1s)
 *@details
 *@param    unDelayTime is delay time, range: unDelayTime > 0
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SysMsDelay(uint unDelayTime);
/**
 *@brief 		obtaining the current time of POS 
 *@details
 *@param     pstTime assigns tm structure typed pointer to it and returns current time of POS
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SysGetPosTime(struct tm *pstTime);

/**
 *@brief 		setting current time of POS
 *@details
 *@param     stTime assigns tm structure typed pointer to it and sets the variable of time as time of POS
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SysSetPosTime(struct tm stTime);

/**
 *@brief 		  to read specified library (provisional interface, not fulfilled)
 *@details    obtain n bytes of content of specified library per offset
 *@param      pPath path of library
 *@param      unOffset offset of library
 *@param      unLen bytes of library to obtain
 *@retval     psBuf is used to store font library content info retrieved
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SysReadFont(const char * pPath,uint unOffset,char *psBuf,uint unLen);
/**
 *@brief 		setting ON/OFF status of 4 RF LEDs of POS
 *@details
 *@param      nLed    the lower 4 bits of nLed represents 4 LEDs; from right to left are LEDs 1, 2, 3, 4; e.g. (nLed&(1 << 0)) !=0 indicates the operation on LED 1
 *@param      nStatus  the lower 8 bits of nStatus reprensents the status of 4 LEDs, each 2 bits for 1 LED, from right to left are LEDs 1, 2, 3, 4.
 		     e.g. (nStatus&3) indicates status of LED 1 for control. ((nStatus>>2)&3) indicates LED 2。
 		     0 means “maintain status”, 1ON，2 OFF，3 flash。
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_LedStatus(EM_LED emStatus);
/**
 *@brief 		starting the watch and beginning to time
 *@details  this is to be used together with NDK_SysStartWatch() and NDK_SysStopWatch(); accuracy: ≤ 1 ms.
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SysStartWatch(void);
/**
 *@brief 		stopping the watch and save the count value
 *@details
 *@retval   punTime the count value when watch ends
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SysStopWatch(uint *punTime);
/**
 *@brief 		to read hardware info interface of the pos
 *@details	if the hardware info index emFlag passed is out of range, it will return parameter error; if no version info is obtained, return NDK_ERR
 						size of the incoming parameter array can be set as 100 provisionaly, api only returns info in first the 100 bytes
 *@param    emFlag the index No. of device info to read
 *@retval   punLen returns length of buf info sent back
 *@retval   psBuf is to store info returned
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SysGetPosInfo(EM_SYS_HWINFO emFlag,uint *punLen,char *psBuf);
/**
 *@brief    Read the system configuration information
 *@param    emConfig To read configuration information index number
 *@retval   pnvalue Returns the configuration of the value
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed

*/
int NDK_SysGetConfigInfo(EM_SYS_CONFIG emConfig,int *pnvalue);
/**
 *@brief    To get the firmware types
 *@retval  	emFWinfo 	Return type of firmware and reference\ref EM_SYS_FWINFO "EM_SYS_FWINFO".
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SysGetFirmwareInfo(EM_SYS_FWINFO *emFWinfo);

/** @} */ // System interface end

/** @addtogroup Tool
* @{
*/

/**
 *@brief	 addition of 2 unsigned numeric strings of size up 12 bits 
 *@details	add 2 numeric strings bit by bit and over and over, the result of addition must not surpass 12 bits 
 *@param	pszDigStr1		numeric string 1
 *@param	pszDigStr2		numeric string 2
 *@param	pnResultLen		size of result buffer pszResult
 *@retval	pszResult		numeric string of the sum of addition
 *@retval	pnResultLen		number of bits of the sum
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_AddDigitStr(const uchar *pszDigStr1, const uchar *pszDigStr2, uchar* pszResult, int *pnResultLen );

/**
 *@brief	 adding 1 to the 6-bit numeric string of pcStrNum and insert it back
 *@param	pszStrNum		numeric string that needs adding; length of buffer at least 7
 *@retval	pszStrNum		resultant string of adding operation
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_IncNum (uchar * pszStrNum );

/**
 *@brief	to convert amount string with decimal point to string without
 *@param	pszSource		amount string to convert
 *@param	pnTargetLen		size of destination buffer
 *@retval	pszTarget		string converted
 *@retval	pnTargetLen		Length of string converted
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_FmtAmtStr (const uchar* pszSource, uchar* pszTarget, int* pnTargetLen );

/**
 *@brief	 compressing ASCII string to HEX
 *@details	if the length of strinig is not even, use “0”as a fill character to the left and “F” to the right per alignment method
 *@param	pszAsciiBuf		ASCII string to convert
 *@param	nLen			length of input data (length of ASCII string)
 *@param	ucType			alignment: 0 – left aligned  1 – right aligned
 *@retval	psBcdBuf		HEX data output from conversion
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_AscToHex (const uchar* pszAsciiBuf, int nLen, uchar ucType, uchar* psBcdBuf);

/**
 *@brief	 converting HEX code data to ASCII code string
 *@param	psBcdBuf		Hex data to convert
 *@param	nLen			length of data converted to (length of ASCII string)
 *@param	ucType			alignment  1 － left aligned  0 － right aligned
 *@retval	pszAsciiBuf		ASCII data output from conversion
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_HexToAsc (const uchar* psBcdBuf, int nLen, uchar ucType, uchar* pszAsciiBuf);

/**
 *@brief 	converting an integer to 4-byte character array (high first) 
 *@param	unNum		integer to convert
 *@retval	psBuf		string output from conversion
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_IntToC4 (uchar* psBuf, uint unNum );

/**
 *@brief	 converting an integer to 2-byte character array (high first)
 *@param	unNum		integer to convert
 *@retval	psBuf		string output from conversion
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_IntToC2(uchar* psBuf, uint unNum );

/**
 *@brief	 converting 4-byte character array to an integer (high first)
 *@param	psBuf		string to convert
 *@retval	unNum		integer output from conversion
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_C4ToInt(uint* unNum, uchar* psBuf );

/**
 *@brief	to converting 2-byte character array to an integer (high first) 
 *@details	length of psBuf >=2
 *@param	psBuf		string to convert
 *@retval	unNum		integer output from conversion
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_C2ToInt(uint *unNum, uchar *psBuf);

/**
 *@brief	 converting an integer (0-99) to 1-byte BCD
 *@param	nNum		integer (0-99) to convert 
 *@retval	ch			1-byte BCD character output from conversion 
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ByteToBcd(int nNum, uchar *ch);

/**
 *@brief	 converting 1-byte BCD to an integer (0-99)
 *@param	ch		BCD character to convert
 *@retval	pnNum	integer value (0-99) output from conversion 
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_BcdToByte(uchar ch, int *pnNum);

/**
 *@brief	 integer (0-9999)  integer (0-9999) to convert 
 *@param	nNum		numeric string 1
 *@param	pnBcdLen	size of output buffer
 *@retval	pnBcdLen	length of BCD converted; if succeeded, a fixed value of 2 will be returned 
 *@retval	psBcd		2-byte BCD output from conversion
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_IntToBcd(uchar *psBcd, int *pnBcdLen, int nNum);

/**
 *@brief	to converting 2-byte BCD to an integer (0-9999)
 *@details	length of psBcd = 2
 *@param	psBcd		2-byte BCD to convert
 *@retval	nNum		integer (0-9999) converted to 
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_BcdToInt(const uchar * psBcd, int *nNum);

/**
 *@brief 	LRC calculation
 *@details	length of buffer psbuf >nLen
 *@param	psBuf		string that requires LRC calculation
 *@param	nLen		length of string that requires LRC calculation
 *@retval	ucLRC		LRC from calculation
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_CalcLRC(const uchar *psBuf, int nLen, uchar *ucLRC);

/**
 *@brief to	trimming whitespace from left end of string
 *@param	pszBuf		buffer to store string
 *@retval	pszBuf		string with left-end whitespace trimmed
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_LeftTrim(uchar *pszBuf);

/**
 *@brief	 trimming whitespace from right end of string
 *@param	pszBuf		buffer to store string
 *@retval	pszBuf		string with right-end whitespace trimmed
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_RightTrim(uchar *pszBuf);

/**
 *@brief	trim whitespace from left & right ends of string
 *@param	pszBuf			buffer to store string
 *@retval	pszBuf			string with left- and right-end whitespace trimmed
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_AllTrim(uchar *pszBuf);

/**
 *@brief	 adding a character to a given string to make it of a length nLen
 *@details	pszString buffer is of a length > nlen；length of string must ＜ nlen
 *@param	pszString		buffer to store string
 *@param    nLen			length of string
 *@param	ch				character to add
 *@param	nOption			operation types
                          	0    add character to the head of string
                          	1    add character to the end of string
                          	2    add character both to the head and end of string
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_AddSymbolToStr(uchar *pszString, int nLen, uchar ch, int nOption);

/**
 *@brief	to intercepting substring
 *@details	substring with '\0' end
 *@param	pszSouStr		string to intercept
 *@param	nStartPos		starting position to intercept substring from; the position of string starts with 1 
 *@param	nNum			number of characters to intercept 
 *@retval	pszObjStr		buffer to store destination string
 *@retval	pnObjStrLen		length of substring
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SubStr(const uchar *pszSouStr, int nStartPos, int nNum, uchar *pszObjStr, int *pnObjStrLen);

/**
 *@brief	 determining if a given character is a numeric character
 *@param	ch		character to determine 
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_IsDigitChar(uchar ch);

/**
 *@brief 	determining if a given string a pure numeric one  
 *@param	pszString		string to be determined 
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_IsDigitStr(const uchar *pszString);

/**
 *@brief	to determine a given year a leap year
 *@param	nYear		year
 *@return
 *@li	NDK_OK				operation succeeded(leap year)
 *@li	other EM_NDK_ERR		operation failed (non-leap year)
*/
int NDK_IsLeapYear(int nYear);

/**
 *@brief	 to find maximum number of days in a given month of a given year
 *@param	nYear		year
 *@param	nMon		month
 *@retval	pnDays		maximum number of days in that month of that year
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_MonthDays(int nYear, int nMon, int *pnDays);

/**
 *@brief	 determining if a given string is a valid date format string
 *@param	pszDate		string of date format  format: YYYYMMDD
 *@return
 *@li	NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_IsValidDate(const uchar *pszDate);

/** @} */ // end of tool module


/** @addtogroup SSLSockets
* @{
*/

typedef enum
{
	NDK_NOWAIT = 0,				       ///< non-blocking
	NDK_SUSPEND = 0xFFFFFFFF,		 ///< blocking
}EM_BLOCK_OPT;
typedef struct st_socket_addr
{
	uint  unAddrType;	///< address type
	char *psAddr;					      ///< IP address（ASCIIz）.
	ushort usPort;					      ///< IP port.
}ST_SOCKET_ADDR;

typedef enum
{
    HANDSHAKE_SSLv2,	//!< SSLv2 only
    HANDSHAKE_SSLv23, 	//!< SSLv3 with fallback to SSLv2
    HANDSHAKE_SSLv3,	//!< SSLv3 only
    HANDSHAKE_TLSv1,	//!< TLSv1
}EM_SSL_HANDSHAKE_OPT;

typedef enum
{
    SSL_AUTH_NONE,			///< Server mode: the server will not send a client certificate request to the client, 
							///< so the client will not send a certificate.
							///< Client mode: if not using an anonymous cipher (by default disabled), 
							///< the server will send a certificate which will be checked.
	SSL_AUTH_CLIENT,		///< Server mode: the server sends a client certificate request to the client.
							///< The certificate returned (if any) is checked.
}EM_SSL_AUTH_OPT;

typedef enum
{
        SSL3_CIPHER_RSA_NULL_MD5 = 1,			///< SSL3_CIPHER_RSA_NULL_MD5
        SSL3_CIPHER_RSA_NULL_SHA,				///< SSL3_CIPHER_RSA_NULL_SHA
        SSL3_CIPHER_RSA_RC4_40_MD5,				///< SSL3_CIPHER_RSA_RC4_40_MD5
        SSL3_CIPHER_RSA_RC4_128_MD5,			///< SSL3_CIPHER_RSA_RC4_128_MD5
        SSL3_CIPHER_RSA_RC4_128_SHA,			///< SSL3_CIPHER_RSA_RC4_128_SHA
        SSL3_CIPHER_RSA_RC2_40_MD5,				///< SSL3_CIPHER_RSA_RC2_40_MD5
        SSL3_CIPHER_RSA_IDEA_128_SHA,			///< SSL3_CIPHER_IDEA_128_SHA
        SSL3_CIPHER_RSA_DES_40_CBC_SHA,			///< SSL3_CIPHER_DES_40_CBC_SHA
        SSL3_CIPHER_RSA_DES_64_CBC_SHA,			///< SSL3_CIPHER_DES_64_CBC_SHA
        SSL3_CIPHER_RSA_DES_192_CBC3_SHA,		///< SSL3_CIPHER_DES_192_CBC3_SHA
        SSL3_CIPHER_DH_RSA_DES_192_CBC3_SHA,	///< SSL3_CIPHER_DH_DSS_DES_192_CBC3_SHA
        SSL3_CIPHER_DH_DSS_DES_40_CBC_SHA,		///< SSL3_CIPHER_DH_DSS_DES_40_CBC_SHA
        SSL3_CIPHER_DH_DSS_DES_64_CBC_SHA,		///< SSL3_CIPHER_DH_DSS_DES_64_CBC_SHA
        SSL3_CIPHER_DH_DSS_DES_192_CBC3_SHA,	///< SSL3_CIPHER_DH_DSS_DES_192_CBC3_SHA
        SSL3_CIPHER_DH_RSA_DES_40_CBC_SHA,		///< SSL3_CIPHER_DH_RSA_DES_40_CBC_SHA
        SSL3_CIPHER_DH_RSA_DES_64_CBC_SHA,		///< SSL3_CIPHER_DH_RSA_DES_64_CBC_SHA
        SSL3_CIPHER_EDH_DSS_DES_40_CBC_SHA,		///< SSL3_CIPHER_EDH_DSS_DES_40_CBC_SHA
        SSL3_CIPHER_EDH_DSS_DES_64_CBC_SHA,		///< SSL3_CIPHER_EDH_DSS_DES_64_CBC_SHA
        SSL3_CIPHER_EDH_DSS_DES_192_CBC3_SHA,	///< SSL3_CIPHER_EDH_DSS_DES_192_CBC3_SHA
        SSL3_CIPHER_EDH_RSA_DES_40_CBC_SHA,		///< SSL3_CIPHER_EDH_RSA_DES_40_CBC_SHA
        SSL3_CIPHER_EDH_RSA_DES_64_CBC_SHA,		///< SSL3_CIPHER_EDH_RSA_DES_64_CBC_SHA
        SSL3_CIPHER_EDH_RSA_DES_192_CBC3_SHA,	///< SSL3_CIPHER_EDH_RSA_DES_192_CBC3_SHA
        SSL3_CIPHER_ADH_RC4_40_MD5,				///< SSL3_CIPHER_ADH_RC4_40_MD5
        SSL3_CIPHER_ADH_RC4_128_MD5,			///< SSL3_CIPHER_ADH_RC4_128_MD5
        SSL3_CIPHER_ADH_DES_40_CBC_SHA,			///< SSL3_CIPHER_ADH_DES_40_CBC_SHA
        SSL3_CIPHER_FZA_DMS_NULL_SHA,			///< SSL3_CIPHER_FZA_DMS_NULL_SHA
        SSL3_CIPHER_CK_FZA_DMS_FZA_SHA,			///< SSL3_CIPHER_CK_FZA_DMS_FZA_SHA
        SSL3_CIPHER_CK_FZA_DMS_RC4_SHA,			///< SSL3_CIPHER_CK_FZA_DMS_RC4_SHA
        SSL3_CIPHER_CK_ADH_DES_64_CBC_SHA,		///< SSL3_CIPHER_CK_ADH_DES_64_CBC_SHA
        SSL3_CIPHER_CK_ADH_DES_192_CBC_SHA,		///< SSL3_CIPHER_CK_ADH_DES_192_CBC_SHA
}EM_SSL_CIPHER_OPT;

typedef enum
{
    SSL_IS_DISCONNECTED,			///< Disconnected state
    SSL_CONNECTION_IN_PROGRESS,		///< Connection has been requested
    SSL_IS_CONNECTED				///< Connected state
}EM_SSL_CONNECTION_STATE;

typedef enum
{
    SSL_FILE_DER,		///<  DER(ASN1) file format
    SSL_FILE_PEM,		//!<  PEM (BASE64) file format
}EM_SSL_FILE_FORMAT;

typedef enum
{
	SSL_ADDR_IPV4,		/**<IP v4*/
    SSL_ADDR_IPV6,		/**<IP v6*/
}EM_ADDR_TYPE;

/**
 *@brief This function will load a client certificate file into the SSL context.  
 *@param 	handle     	SSL Socket handle
 *@param  filename   	Certificate file to load
 *@param  format		File format, \see SSL_FILE_FORMAT 
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_LoadClientCertificate(NDK_HANDLE handle, const char *filename, int format);
/**
 *@brief This function will load a private key file into the SSL context.   
 *@param 	handle     	SSL Socket handle
 *@param  filename   	Private Key file to load
 *@param  format		File format, \see SSL_FILE_FORMAT 
 *@param  password	password
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_LoadClientPrivateKey(NDK_HANDLE handle, const char *filename, int format,char *password);
/**
 *@brief This function will load a CA certificate chain into the SSL context.  
 *@param 	handle     	SSL Socket handle
 *@param  filename   	Certificate(s) file to load
 *@param  format		File format, \see SSL_FILE_FORMAT 
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_LoadServerCertificate(NDK_HANDLE handle, const char *filename, int format);

/**
 *@brief Creates an SSL socket.
 *@param type    		Session type, \see SSL_HANDSHAKE_OPT 
 *@param auth_opt    	Peer authentication mode, \see SSL_AUTH_OPT
 *@param cipher    	Pointer to list of supported ciphers. \see SSL_CIPHER_OPT						
 *@return
 *@liSSL Socket handle        operation succeeded	
 *@li	NULL                   operation failed
*/
NDK_HANDLE NDK_OpenSSLSocket(int type,int auth_opt,int* cipher);
/**
 *@brief	Disconnect and close an SSL socket
 *@param  handle  Socket handle
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_CloseSSLSocket(NDK_HANDLE handle);
/**
 *@brief  Sends an SSL disconnect to the peer.
 *@param  handle  Socket handle	
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SSLDisconnect(NDK_HANDLE handle);
/**
 *@brief  	Connect to a remote server
 *@param 		handle     	SSL Socket handle
 *@param 		pServer     Server IP address
 *@param 	    timeout     Connection timeout, in ms. 
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SSLConnect(NDK_HANDLE handle, ST_SOCKET_ADDR *pServer, int timeout);
/**
 *@brief	Returns current socket mode
 *@param 	handle     	SSL socket handle
 *@return
 *@li	NDK_NOWAIT(non-blocking)		NDK_SUSPEND(blocking)		operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_GetSSLBlockingMode(NDK_HANDLE handle);
/**
 *@brief Switches socket mode (blocking/non-blocking)
 *@param 	handle     	SSL socket handle
 *@param	mode	Blocking mode (SDK_NOWAIT or SDK_SUSPEND)
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SetSSLBlockingMode(NDK_HANDLE handle,int mode);
/**
 *@brief 	Sends data to an SSL socket. 
 *@param 	pvHandle     		SSL socket handle
 *@param 	psBuffer			Data to send
 *@param  	unBufferLen    Number of data bytes
 *@param  	punSendLen		Number of bytes sent
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SSLSend(NDK_HANDLE pvHandle, const char *psBuffer, uint unBufferLen, uint *punSendLen);
/**
 *@brief 	Receives data from the TCP (Stream) socket (blocking or not depends on socket mode).
 *@param 	pvHandle     		SSL socket handle
 *@param	pvBuffer  		Caller's data buffer
 *@param	unBufferLen    Size of caller's buffer
 *@param  	punRecvLen       Number of bytes actually received
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SSLReceive(NDK_HANDLE pvHandle, void *pvBuffer, const uint unBufferLen, uint *punRecvLen);
/**
 *@brief 	Assign an address to a server socket (this operation is also called socket naming)
 *@param 	pvHandle     	SSL socket handle
 *@param 	pstAddr   	IP address of a server socket
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SSLBind(NDK_HANDLE pvHandle, ST_SOCKET_ADDR *pstAddr);
/**
 *@brief 	Returns SSL socket's connection state
 *@param 	handle     	SSL Socket handle
 *@param  state		Connection state as follows:
						SSL_IS_DISCONNECTED
						SSL_CONNECTION_IN_PROGRESS
						SSL_IS_CONNECTED
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_GetSSLConnectStatus(NDK_HANDLE handle, int *state);
/**
 *@brief 	Allows check for data to read on the SSL socket until the timeout expired.
 *@param 	pvHandle    SSL socket handle
 *@param  	unTimeOut   Timeout to wait for data 
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SSLDataAvailable(NDK_HANDLE pvHandle, uint unTimeOut);


/** @} */ // SslSocket modle end

/** @addtogroup Timer
* @{
*/

#define ONEMILLISECOND 1     					/**<A millisecond*/
#define ONESECOND ( 100 * ONEMILLISECOND )  		/**<one second */
#define ONEMINUTE ( 60 * ONESECOND )	/**<one minute*/
typedef void        ( *pvFUNC )( void );
typedef const pvFUNC       pcFUNC;

/**
 *@brief	Wait for some period of time
 *@param  	unWaitDuration  timeout value in ticks
 *@return none
*/
void NDK_Wait(uint  unWaitDuration);
/**
 *@brief	Starts a timer and sets a flag when the timer expires.
 *@param  	unWaitDuration   time to wait in units of OS_TIMES
 *@param  	punFlag          pointer to the flag that is set when the time expires
 *@return
 *@li	Timer handle				  operation succeeded
 *@li	NULL 	            operation failed
*/
NDK_HANDLE NDK_WaitAndFlag(uint unWaitDuration,uint *punFlag);
/**
 *@brief	Cancels a timer previously initiated by NDK_WaitAndFlag().
 *@param  handle   Timer handle
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
void NDK_CancelTimer(NDK_HANDLE  handle);

/**
 *@brief	Register a routine to be called at a specified time interval.
 *@param  	unTimeInterval   allowable register time increments in units of OS_TIMES
 *@param  	pRoutine    address of routine which can be called 
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_RegisterTimerRoutine (uint unTimeInterval, pvFUNC pRoutine);


/** @} */ // Timer end

/** @addtogroup Thread
* @{
*/

typedef enum ndk_thread_state
{
	NDK_THREAD_STOPPED,		///< Thread is stopped
	NDK_THREAD_RUNNING,		///< Thread is running
	NDK_THREAD_SUSPEND,		///< Thread is suspended
} EM_THREAD_STATE;
/**
 *@brief    			Creates a thread 
	
 *@param 	ppvHandle  	Pointer to the storage for the thread handle
 *@param 	psName  		Thread name
 *@param	unStackSize  	Thread stack size
 *@param	pvEntryPoint Thread entry point
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_CreateThread( NDK_HANDLE *ppvHandle, const char* psName, uint unStackSize,
								void (*pvEntryPoint)( void ) );
/**
 *@brief    			Resumes execution of a previously stopped thread
 *@param 	handle  	Thread handle
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ResumeThread( NDK_HANDLE handle );
/**
 *@brief    			Stops execution of a running thread
 *@param 	handle  	Thread handle
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_SuspendThread( NDK_HANDLE handle );
/**
 *@brief    			Terminate a thread
 *@param 	handle  	Thread handle
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_TerminateThread( NDK_HANDLE handle );
/**
 *@brief	Force OS scheduling, allowing other threads to run
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_Relinquish( void );
/**
 *@brief 		Gets current status of the task
 *@param 	pvHandle  	Thread handle
 *@param 	pemState  		Container to return the state
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_GetThreadState( NDK_HANDLE pvHandle, EM_THREAD_STATE *pemState );
/**
 *@brief     		Suspends execution for the specified time.

 *@param	ms_wait Number of milliseconds to wait
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ThreadSleep( int ms_wait );
/**
 *@brief 				Create a semaphore
 *@param 	handle  	Pointer to store the semaphore handle
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_CreateSemaphore( NDK_HANDLE *handle );
/**
 *@brief 				Acquire a semaphore
 *@param 	handle  	Semaphore handle
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_LockSemaphore( NDK_HANDLE handle );
/**
 *@brief 				Acquire a semaphore
 *@param 	handle  	Semaphore handle
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_ReleaseSemaphore( NDK_HANDLE handle );
/**
 *@brief Destroy the semaphore object.
 *@param handle Pointer to the semaphore object to be released.
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_DestroySemaphore( NDK_HANDLE handle );


/** @} */ // Thread end

/** @addtogroup U Disk and SD Card
* @{
*/

typedef enum{
	UDISK = 0,    /**<Select U Disk*/
	SDDISK =1     /**<Select SD Card*/
}EM_DISKTYPE;

typedef enum
{
	DISKMOUNTSUCC=1,         /**<U disk or Sd card is available*/
	DISKNOTOPEN=2,           /**<U disk or Sd card is not open*/
	DISKDRIVERLOADFAIL=3,    /**<U disk or SD card drive load failure*/
	DISKMOUNTING=4,          /**<U disk or Sd card is being loaded*/
	DISKNOEXIT=5,	         /**<SD card not detected*/
	DISKTIMEOUT=6            /**<Detection of SD card timeout*/
}EM_DISKSTATE;

typedef struct{
	uint unFreeSpace;	/**<Can use the space size*/
	uint unTotalSpace;	/**<The total size*/
}ST_DISK_INFO;

/**
 *@brief	Open the U disk or SD card (note: the usb stick in use process, if the pos have big slot is selected gulp)
 *@param	emType	Type (UDISK: U disk, SDDISK: SD card. \ref EM_DISKTYPE "EM_DISKTYPE")
 *@param	nTimeOut Set the timeout (units of seconds, 0 means obstruction, non-zero said within the specified timeout does not return DISKMOUNTSUCC that state, at this time access to the state should be DISKTIMEOUT)
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_DiskOpen(EM_DISKTYPE emType,int nTimeOut);
/**
 *@brief	For information on usb stick or SD card
 *@param	pszDiskDir	U disk or SD card catalog
 *@param	pstInfo   Disk information structure（\ref ST_DISK_INFO "ST_DISK_INFO"
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_DiskGetInfo(char *pszDiskDir,ST_DISK_INFO  *pstInfo);
/**
 *@brief	To obtain U disk or SD card state
 *@param	emType	Type (UDISK: U disk, SDDISK: SD card. \ref EM_DISKTYPE "EM_DISKTYPE")
 *@retval	pnDiskState   state（\ref EM_DISKSTATE "EM_DISKSTATE"）
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_DiskGetState(EM_DISKTYPE emType,int *pnDiskState);
/**
 *@brief	Close the U disk or SD card
 *@param	emType	Type (UDISK: U disk, SDDISK: SD card. \ref EM_DISKTYPE "EM_DISKTYPE")
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_DiskClose(EM_DISKTYPE emType);
/**
 *@brief	To obtain U disk or SD Root directory
 *@param	emType	Type (UDISK: U disk, SDDISK: SD card. \ref EM_DISKTYPE "EM_DISKTYPE")
 *@retval	pszRdir  root directory
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_DiskGetRootDirName(EM_DISKTYPE emType,char **pszRdir);

/** @} */ // End of the usb and SD card module

/** @addtogroup WIFI
* @{
*/

typedef enum
{
    WIFI_NET_SEC_NONE,          /**<The router does not use the security encryption mode*/
    WIFI_NET_SEC_WEP_OPEN,      /**<Routers use keys to open WEP mode*/
    WIFI_NET_SEC_WEP_SHARED,    /**<Routers use the Shared secret WEP mode*/
    WIFI_NET_SEC_WPA,           /**<Routers use WPA mode*/
    WIFI_NET_SEC_WPA2           /**<Routers use WPA2 mode*/
} EM_WIFI_NET_SEC;

typedef enum {
    WIFI_KEY_TYPE_NOKEY,        /**<The router does not use the password*/
    WIFI_KEY_TYPE_HEX,          /**<Routers use hexadecimal code format*/
	WIFI_KEY_TYPE_ASCII         /**<Routers use ASCII code format*/
}EM_WIFI_KEY_TYPE;

typedef struct
{
    uchar ucIfDHCP;             /**<enable DHCP or not*/
    EM_WIFI_KEY_TYPE emKeyType; /**<The router's password format*/
    EM_WIFI_NET_SEC emSecMode;  /**<The router's security encryption mode*/
    char *pszKey;               /**<The router's password*/
    char *psEthIp;              /**<The terminal IP address*/
    char *psEthNetmask;         /**<Netmask address*/
    char *psEthGateway;         /**<Network gateway address*/
    char *psEthDnsPrimary;      /**<Network first DNS address*/
    char *psEthDnsSecondary;    /**<Network times DNS address*/
} ST_WIFI_PARAM;

typedef enum
{
    WIFI_WPA_CONSTATE_LINKING,      /**<Attempting to connect to the specified AP*/
    WIFI_WPA_CONSTATE_LINKED,       /**<Connection has been AP response*/
    WIFI_WPA_CONSTATE_AUTHENTICATED,/**<Connection has been AP validation*/
    WIFI_WPA_CONSTATE_CONTEXT       /**<Connected to the specified AP has been successful*/
} EM_WPA_CONSTATE;

#define WIFI_IW_ESSID_MAX_SIZE	128     /**<The router name allows the maximum length*/
#define WIFI_IW_ENCODING_TOKEN_MAX	128 /**<The router allows the maximum length of the password*/
typedef struct {
	char sEssid[WIFI_IW_ESSID_MAX_SIZE + 1];    /**<Router Name */
	char sKeyModeStr[128];                      /**<The router's security encryption mode*/
	int nFrequency;                             /**<The frequency of the router*/
	char sKey[WIFI_IW_ENCODING_TOKEN_MAX + 1];  /**<The router's password*/
	char sSignal[16];                           /**<The router signal values*/
}ST_WIFI_APINFO;

/**
 *@brief	Mode Init
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_WiFiInit(void);
/**
 *@brief	For scanning to AP SSID information
 *@retval	ppszESSIDlist	Save scan to AP SSID information of two dimensional array
 *@retval	pnNumList   Save the number of scans to AP
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_WiFiGetNetList(char **ppszESSIDlist, int *pnNumList);
/**
 *@brief	Access to AP signal value specified
 *@param	pszNetName	AP SSID
 *@retval	pnSignal   Save the AP signal values
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_WiFiSignalCover(const char *pszNetName, int *pnSignal);
/**
 *@brief	Access to specified AP safe mode
 *@param	pszESSIDName	AP SSID
 *@retval	pemSec	Save the AP security mode
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_GetWiFiSec(const char *pszESSIDName, EM_WIFI_NET_SEC *pemSec);
/**
 *@brief	Connect to the specified AP
 *@param	pszESSIDName	AP SSID
 *@param	pstParam	connection parameters
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_WiFiConnect(const char *pszESSIDName, const ST_WIFI_PARAM *pstParam);
/**
 *@brief	Get the connection status information
 *@retval	pemState	connection status
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_WiFiConnectState(EM_WPA_CONSTATE *pemState);
/**
 *@brief	Judgment is connected to the AP
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_WiFiIsConnected(void);
/**
 *@brief	unload WIFI mode
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_WiFiShutdown(void);
/**
 *@brief	Access to scan all of the information to AP
 *@retval	pstList	Save the scan to the AP information structure array
 *@param	nMaxNum	Hope to get to the largest number of AP
 *@retval	pnNumList   Save the number of scans to AP
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_WiFiGetNetInfo(ST_WIFI_APINFO *pstList, unsigned int unMaxNum, int *pnNumList);
/**
 *@brief	get WIFI MAC address
 *@retval	pszMac	save MAC address
 *@return
 *@li	 NDK_OK				operation succeeded
 *@li	other EM_NDK_ERR		operation failed
*/
int NDK_WiFiGetMac(char *pszMac);

/** @} */ // WIFI End of the module

#endif
/* End of this file */

