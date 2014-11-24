#ifndef _POSDEF_H_
#define _POSDEF_H_

#include   "NDK.h"

/*             �������Ա                */
#define		ADM	    1
#define 	OPER	2

#ifdef USE_POS_INSIDE_PINPAD
#define PubPOSInitKey PubInitEsamKey
#else
#define PubPOSInitKey initkey
#endif

#define PubSelectList(pstr, pstitle, nselect, pnselect) \
	PubSelectListItem( pstr, pstitle, NULL, nselect, pnselect)


/*  ע�⣺Ŀǰ���ÿռ�Ϊ2k��������滮���ڶ���ʱ��Ҫ�������Ʒ�Χ������չ*/
/*ĸpos��������*/
#define	dNvrAdder_Start	 0

#define	dInited_off	dNvrAdder_Start
#define	dInited_len	1

#define	dTermtype_off	dInited_off + dInited_len
#define	dTermtype_len	1

#define	dTek1_off	dTermtype_off + dTermtype_len
#define	dTek1_len	24

#define	dTek2_off	dTek1_off + dTek1_len
#define	dTek2_len	24

#define 	dTekflag_off 	dTek2_off + dTek2_len
#define 	dTekflag_len 1

#define	dRecNum_off	dTekflag_off+dTekflag_len
#define	dRecNum_len	4

#define	dKekGroupNo_off   dRecNum_off+dRecNum_len
#define	dKekGroupNo_len   4
#define	dKekSerialNo_off   dKekGroupNo_off+dKekGroupNo_len
#define	dKekSerialNo_len   4

//#define	dNvrAdder_End   dRecNum_off+dRecNum_len
#define	dNvrAdder_End   dKekSerialNo_off+dKekSerialNo_len

#define fMAX_FRAM_SIZE 	2000

#if dNvrAdder_End > (dNvrAdder_Start+fMAX_FRAM_SIZE)
#error Define NVR Err!
#endif


#define APP_NAME			 "MPOS" 		/**<Ӧ������:�й�����*/

#define APP_NAMEDESC		"MPOS"

#define VERSTR_GZYL 		"V0903001" 	/**<�й����̰汾*/

#define APP_VERSION			"2009032001"	/**<�汾���壬���й����̵�TMS��԰汾�Ķ���yyyymmdd+2λ���*/

#define APP_SERIAL			0x11

#if defined(POS8510)
#define POS_MODEL			"\x85\x10"
#define SUPPORT_PINPAD 1
#endif
#if defined(POS8200)
#define POS_MODEL			"\x82\x00"
#define SUPPORT_PINPAD 1
#endif
#if defined(POS8300)
#define POS_MODEL			"\x83\x00"
#endif

//#if defined(POS8510) || defined(POS8080)
//#define AUX2 AUX_PINPAD/*������̽ӿ�NL8510ר�Ŷ����˽�������̵Ĵ��ڶ����������ϱ���Ӵ���2*/
//#endif

#endif

