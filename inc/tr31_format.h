#ifndef _TR31_FORMAT_H_
#define _TR31_FORMAT_H_

#include <stdint.h>

/*
 * TR-31 CBC MAC Key Block
 * ----------24-----------------------24----------------------------4-----
 * | header | header opt | length | Key | KSN(Condition) |Padding | MAC |
 * -----------------------------------------------------------------------
 */

#define XORDATA(j, data1, data2, datalen, outdata) {\
        for( j=0 ; j<(datalen) ; j++ ) \
                (outdata)[j] = (data1)[j]^(data2)[j]; \
}

#ifndef NULL
#define NULL 	(0)
#endif

#ifndef DES3_KEY_LEN
#define DES3_KEY_LEN 16
#endif

#define USE_CMAC_TDEA
//#define DEBUG_TR31_DATA

#define TR31_HEAD_LEN			(16 + 8 )
#define TR31_HEAD_OPT2_LEN		(2 + 2 + 20)
#ifdef USE_CMAC_TDEA
#define KBH_VERID               0x42
#define MAC_LEN                 8
#else
#define KBH_VERID               0x41
#define MAC_LEN 				4
#endif
#define DUKPT_KSN_LEN			10

#define TR31RSA_KEY_LEN					256
#define TR31_DATA_BCD_MAX 				(2 + TR31RSA_KEY_LEN + 6)	/*2[length] + [data] + 6[padding]*/
#define TR31_ENCRYPTED_BLOCK_BCD_MAX 	(TR31_HEAD_LEN + TR31_HEAD_OPT2_LEN + TR31_DATA_BCD_MAX + MAC_LEN)


/*	key usage (support only as below )*/
#define KEY_USAGE(usage)        (((usage)[0] << 8) | (usage)[1])

#define KEY_USAGE_BDK           	"B1"          /* B0:KT_BDK BASE Derivation Key */
#define KEY_USAGE_PRI          		"D0"          /* D0:KT_PRI  */
#define KEY_USAGE_MST           	"K0"          /* K0:KT_MST */
#define KEY_USAGE_TR31           	"K1"          /* K1:KT_TR31 */
#define KEY_USAGE_MAC      			"M0"          /* M0:KT_MAC*/
#define KEY_USAGE_PIN            	"P0"          /* P0:KT_PIN  */
#define KEY_USAGE_MAG            	"D0"          /* D0:KT_MAG, DATA Enc */

/*	key algorithm (support only as below )*/
#define KEY_ALGORITHM_RSA       	0x52            /* 'R':RSA */
#define KEY_ALGORITHM_TDEA      	0x54            /* 'T':Triple DEA */

/*	key mode of use  (support only as below )*/
#define KEY_USEMODE_MAC        		0x43            /* 'C':MAC Calculate (Generate or Verify) */
#define KEY_USEMODE_MST     		0x44            /* 'D':KT_MST */
#define KEY_USEMODE_ENCRYPT     	0x45            /* 'E':KT_PIN, KT_BDK */
#define KEY_USEMODE_SIG         	0x53            /* 'S': KT_PRI */

#define KEY_EXPORT					'E'
#define OPT_ID						"KS"
#define OPT_NR						"01"
#define OPT_LEN						"08"
#define OPT2_ID						"01"
#define OPT2_NR						"02"
#define OPT2_LEN					"18"

/*      Required Key Type (Usage + Algorithm + Mode)    */
#define KT_MST_TYPE             "K0TD"
#define KT_MST_TR31_TYPE        "K1TD"
#define KT_PIN_TYPE             "P0TE"
#define KT_MAC_TYPE             "M0TG"
#define KT_PRI_TYPE             "D0RS"
#define KT_MAG_TYPE             "D0TB"

#define KT_BDK_TYPE             "B1TE"

//	-----key filed ID ----
#define KEYFD_MT					0x00
#define KEYFD_FIX					0x01
#define KEYFD_DUKPT					0x02

typedef struct {
        uint8_t ver_id;         /* Key Block Version ID --- 'A'(0x41) */
        uint8_t length[4];      /* Key Block Length, including Header + DATA + MAC */
        uint8_t usage[2];       /* Key Usage */
        uint8_t algorithm;      /* The approved algorithm to be used by the protected key */
        uint8_t mode;           /* the operation the protected key can perform */
        uint8_t ver_num[2];     /* Key Version Number */
        uint8_t export;         /* Defines the protected key's exportablility */
        uint8_t option_nr[2];   /* Numbers of optional blocks */
        uint8_t reserv[2];      /* Reserved for future use */

		uint8_t opt_id[2];      /* The first optional block, for key index information*/
		uint8_t opt_len[2];		/*optional block length*/
		uint8_t fid;			/*key field*/
		uint8_t gid[3];			/*Group ID, ASCII Numeric Digits*/

		uint8_t opt2_id[2];		/* The second optional block, for DUKPT KSN value*/
		uint8_t opt2_len[2];	/*optional block length*/
		uint8_t ksn[20];		/*ASCII-encoded KSN for dukpt*/
}tr31_kbh_t;

typedef struct{
	uint8_t *key;			/*  key pointer */
	uint16_t keylen;			/* keylen*/
	uint8_t fid;				/* filed ID*/
	uint8_t gid;				/* group ID*/
	uint8_t usage[2];       	/* Key Usage */
    uint8_t algorithm;      	/* The approved algorithm to be used by the protected key */
    uint8_t mode;           	/* the operation the protected key can perform */
    uint8_t ver_num[2];     	/* Key Version Number */
    uint8_t export;         	/* Defines the protected key's exportablility */
	uint8_t ksn[10];			/* Key Serial Number */
	uint8_t reserv[3];      	/* Reserved for future use */
}tr31_key_t;


/* Return Value of tr31block_decode Fuction*/
#define TR31BLK_HERR_VER         -1             /*block header version error*/
#define TR31BLK_HERR_EXP         -2             /*block header Exportability error*/
#define TR31BLK_HERR_USG         -3             /*block header usage error*/
#define TR31BLK_HERR_LEN         -4             /*block header length byte error*/
#define TR31BLK_HERR_OPT         -5             /*block header option error*/

#define TR31BLK_ERR_LEN          -10            /*the Decoded block length error*/
#define TR31BLK_ERR_MAC          -11            /*block MAC error*/
#define TR31BLK_ERR_KLEN         -12            /*block KEY length error*/
#define TR31BLK_ERR_NULL         -13            /*Pointer NULL*/
#define TR31BLK_ERR_KSN         -14            /*KSN error*/


extern int tr31block_format(uint8_t * out, uint32_t *outlen,
                uint8_t * kek, int keklen, tr31_key_t * keyst );

#endif /*_TR31_FORMAT_H_*/
