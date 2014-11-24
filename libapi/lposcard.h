/*
* �´�½���Թ�˾ ��Ȩ����(c) 2012-2016
*
* POSͳһ�濨��
* (���������Ӵ�ʽIC�����ǽ���Ƶ��)ͷ�ļ�  --- lposcard.h
* ��    �ߣ�    �λ���
* ��    �ڣ�    2012-12-10
* ����޸��ˣ�  �λ���
* ����޸����ڣ�2012-12-10
*/
#ifndef _LPOSCARD_H
#define _LPOSCARD_H

#define IC1_EXIST		0x01
#define IC1_POWERON	0x02
#define SIM1_POWERON	0x04
#define SIM2_POWERON	0x08
#define SIM3_POWERON	0x10
#define SIM4_POWERON	0x20

#define CARD_FUNCQUIT (-4)  		/**<���ܼ��˳�*/

typedef enum{
	RFIDREADER_POS=1,			/**<���ö�����*/
	RFIDREADER_ZX,	 		 	/**<���˶�����*/
	RFIDREADER_SH,	 		 	/**<ʢ��(ֱͨ)������*/
	RFIDREADER_829			/**<��˾829*/
}ENM_RFREADERTYPE;			/**<�ǽӶ���������*/

typedef enum{
	EM_RF_INSIDE  = 0x01,		/**<POS������Ƶ����ģ��*/
	EM_RF_OUTSIDE = 0x02		/**<POS�����Ƶ����ģ��*/
}ENM_INOROUTFLAG;			/**<POS���������û���ӱ��*/

typedef enum {
	EM_CARD_RF_M1  = 0x01,		/**<mifare one*/
	EM_CARD_RF_CPU = 0x02		/**<cpu*/
}ENM_CARDTYPE;				/**<POS���������û���ӱ��*/

typedef enum{
	RFCARDTYPE_CPU_INSIDE=0,	/**<����CPU��*/
	RFCARDTYPE_M1_INSIDE,		/**<����M1��*/
	RFCARDTYPE_CPU_OUTSIDE,	/**<����CPU��*/
	RFCARDTYPE_M1_OUTSIDE	/**<����M1��*/
}ENM_RFIDCARDTYPE;			/**<�ǽӿ����ͱ��*/

typedef enum{
	EM_RF_AKEY  = 0x00,        	/**<A Key*/
	EM_RF_BKEY = 0x01			/**<B Key*/
}ENM_RFIDM1KEYMODE;		/**<M1�� Key����*/

typedef enum 
{
	RD_SHOWBALANCE = 0x00,			/**< ��ʾ�������*/
	RD_SHOWSUCC = 0x01,				/**< ��ʾ���׳ɹ�*/
	RD_SHOWFAIL =0x02,					/**< ��ʾ����ʧ��*/
	RD_SHOWLITTEBALANCE= 0x03,		/**< ��ʾ����*/
	RD_SHOWEXCEPTION =0x04,			/**< ��ʾ�����쳣*/
	RD_SHOWSWIPCARD =0x05,			/**< ��ʾ����ˢ��*/
	RD_SHOWEMPTY = 0x06				/**< ��ʾ����״̬*/
}ENM_READERSHOW;


typedef struct{
	char cOperFlag;        		/**<EM_RF_INSIDE��ʾʹ�����ã�EM_RF_OUTSIDE��ʾʹ������,EM_RF_INSIDE|EM_RF_OUTSIDE��ʾʹ��������*/
	char cAux; 		       	/**<��Ӷ��������Ӵ���(���ò���)*/
	char cDefaultType;     	/**<Ĭ����Ӷ���������(˫Ƶ:RFIDREADER_ZX,RFIDREADER_SH,��Ƶ:ENM_RFREADERTYPE,RFIDREADER_ZX�ݲ�֧��2.4G M1����)*/
	char cUsedDoubleRF;    	/**<�Ƿ�ʹ�ö�������˫ƵѰ��ģʽ0:��1��(��Ӷ�����ר��)	(��ע����������֧��)*/		
	char cCardType;			/**<��Ҫ��ȡ�Ŀ�Ƭ����ENM_CARDTYPE*/
	char cIs829SupportM1;	/**<829ģ���Ƿ�֧��M1��0:��֧�֣�����:֧��*/
	char *pszM1AID;			/**<��2.4G��ͷ��Чm1����Ӧ��AID,��ֵΪNULLʱ���õ��ż���Ĭ��AID*/
	char cFirst;				/**<2.4G������ѯ��0:M1�����ȣ�����:CPU������*/
}STRFIDCARDPARAM;

enum EM_CARDINPUTMODE
{
	CARD_STRIPE = (1<<0),		/**<ˢ�ſ�*/
	CARD_KEYIN = (1<<1),		/**<���俨��*/
	CARD_INSERTIC = (1<<2),		/**<����IC��*/
	CARD_RFCARD = (1<<3),		/**<�ӷǽӿ�*/
	CARD_STRIPE_KEYIN = CARD_STRIPE|CARD_KEYIN,
	CARD_STRIPE_INSERTIC = CARD_STRIPE|CARD_INSERTIC,
	CARD_STRIPE_RFCARD = CARD_RFCARD|CARD_STRIPE,
	CARD_STRIPE_KEYIN_INSERTIC = CARD_STRIPE_KEYIN|CARD_INSERTIC,
	CARD_STRIPE_KEYIN_RFCARD = CARD_STRIPE_KEYIN|CARD_RFCARD,
	CARD_STRIPE_KEYIN_INSERTIC_RFCARD = CARD_STRIPE_KEYIN_INSERTIC|CARD_RFCARD,
	CARD_STRIPE_INSERTIC_RFCARD = CARD_STRIPE_INSERTIC |CARD_RFCARD,
	CARD_KEYIN_INSERIC = CARD_KEYIN|CARD_INSERTIC,
	CARD_KEYIN_RFCARD = CARD_KEYIN|CARD_RFCARD,
	CARD_KEYIN_INSERIC_RFCARD = CARD_KEYIN_INSERIC|CARD_RFCARD,
	CARD_INSERTIC_RFCARD = CARD_INSERTIC|CARD_RFCARD
};

enum EM_MAINTK
{
	NOMAINTK = 0x00,							/**<û�����ȵ���ֻҪ��1���ŵ��� 	*/
	MAINTK1  = (1<<0),  			  				/**<һ�ŵ�Ϊ���ȵ�              	*/
	MAINTK2  = (1<<1),  			   				/**<���ŵ�Ϊ���ȵ�              	*/
	MAINTK3  = (1<<2),  			   				/**<���ŵ�Ϊ���ȵ�              	*/
	MAINTK1_2 =   (MAINTK1 | MAINTK2),			/**<һ�����ŵ�Ϊ���ȵ�          	*/
	MAINTK1_3 =   (MAINTK1 | MAINTK3),			/**<һ�����ŵ�Ϊ���ȵ�          	*/
	MAINTK2_3 =   (MAINTK2 | MAINTK3), 			/**<�������ŵ�Ϊ���ȵ�          	*/
	MAINTK1_2_3 = (MAINTK1 | MAINTK2 | MAINTK3)	/**<һ���������ŵ�Ϊ���ȵ�      	*/
};

typedef struct
{
    uint    unFlag; 	         		/**<ˢ�����뷽ʽ EM_CARDINPUTMODE */
    uint    unMaintk;			/**<���ȴŵ� EM_MAINTK */
    uint    unInputMinLen;		/**<�ֹ�������С����*/
	uint    unInputMaxLen;	/**<�ֹ�������󳤶�*/
    uint    unTimeout;			/**<ˢ����ʱ,��λs*/
    uint    unSleepTime;		/**<��Ҫ���ߵ�ʱ��,��λs,Ϊ0�ı�ʾ������*/
	uint    unFunctionKeyFlag;	/**<�Ƿ�֧�ֹ��ܼ�,1֧�֣�0��֧��*/
}STREADCARDPARAM;

/**
* @brief ˢ��
* @detail ͬʱ֧�ִſ��Ķ��������俨�š�IC���忨��⡢��Ƶ�����
* @detail ��Ҫ�����Ƶ����ʱ����ȷ���Ѿ�ִ��PubInitRFCardParam
* @param [in] pstReadCardParm  ˢ������
* @param [out] pszTk1  һ�ŵ�����
* @param [out] pszTk2  ���ŵ�����
* @param [out] pszTk3  ���ŵ�����
* @param [out] pnCardType  �������� CARD_STRIPE,CARD_KEYIN,CARD_INSERTIC,CARD_RFCARD,CARD_FUNCQUIT
               CARD_KEYIN    --- pszTk2 ��ʾ���������
               CARD_FUNCQUIT --- pszTk2[0] ��ʾ���ܼ���ֵ
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @author �λ���
* @date 2012-10-24
*/
int PubPosReadCard(const STREADCARDPARAM *pstReadCardParm,char *pszTk1, char *pszTk2, char *pszTk3, int *pnCardType);


/**
* @brief IC���ϵ磬����IC�����͡�
* @param [in] nCardPort IC���˿ں�
* @param [in] nCardType IC������
* @param [out] psAtr  �ϵ緵����Ϣ
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @li APP_QUIT �˳�
* @author�λ���
* @date 2012-6-1
*/
int PubICPowerUp (const int nCardPort,const int nCardType,char *psAtr);

/**
* @brief ��ȡIC��״̬
* @param [out] pszStatus  IC��״̬
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @author �λ���
* @date 2012-6-1
*/
int PubGetICStatus(char *pszStatus);

/**
* @brief ��ȡIC��״̬
* @param [in] nCardPort  IC���˿ں�
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @author �λ���
* @date 2012-6-1
*/
int PubICPowerDown(const int nCardPort);

/**
* @brief IC/SIM����׼�������������
* @param [in] nCardPort IC���˿ں�
* @param [in] cCLA �������
* @param [in] cINS ָ�����
* @param [in] cP1 ���Ӳ���1
* @param [in] cP2 ���Ӳ���2
* @param [in] ucInLen �������ݳ���
* @param [in] psInData ��������
* @param [in] nLe �ڴ���Ӧ���ݳ���
* @param [out] pucOutLen  �������ݳ���
* @param [out] psOutData  ��������
* @param [out] pszSW1  ����״̬1
* @param [out] pszSW2  ����״̬2
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @author �λ���
* @date 2012-6-1
*/
int PubICComm (const int nCardPort, const char cCLA, const char cINS,
			   const char cP1, const char cP2, const uchar ucInLen,
			   const char *psInData, int nLe, uchar *pucOutLen, 
			  char *psOutData, char *pszSW1, char *pszSW2);

/**
* @brief ��ʼ����Ƶ������ģ�飬����Ӧ���������á�
* @param [in] pstRFIDCardParam ģ�����,��ο�STRFIDCARDPARAM�ṹ�嶨��
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @author �λ���
* @date 2012-6-1
*/
int PubInitRFCardParam (const STRFIDCARDPARAM * pstRFIDCardParam);

/**
* @brief �ǽӿ�(CPU��)�ϵ�
* @param [out] psUID  �����к�,��һ���ֽ�Ϊ���кų���
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @li APP_QUIT �˳�
* @author �λ���
* @date 2012-6-1
*/
int PubRFCPUPowerUp (char *psUID);

/**
* @brief �ǽӿ�(CPU��)�µ�
* @param ��
* @return 
* @li APP_FAIL ʧ��
* @li APP_SUCC �ɹ�
* @author �λ���
* @date 2012-6-1
*/
int PubRFCPUPowerDown (void);

/**
* @brief ��ǽӿ�(CPU��)����ͨѶ��ʹ��APDU��
* @param [in] psSend  ���͵����ݻ�����
* @param [in] nSendLen  �������ݳ���
* @param [out] psRecv  �������ݻ�����
* @param [out]  pnRecvLen  �������ݵĳ���
* @return 
* @li <0 ʧ��
* @li APP_SUCC �ɹ�
* @author �λ���
* @date 2012-6-1
*/
int PubRFCPUComm(char *psSend, int nSendLen,char *psRecv, int *pnRecvLen);

/**
* @brief Ѱ��(�ǽ���Ƶ�����ҵ���Ƭ���ϵ�)���˴�Ѱ���ڳ�ʼ�������趨�еĿ����࣬�ο�PubInitRFCardParam��
* @param [out] psUid  ��ȡ�Ŀ����к�
* @param [out]  pnType  Ѱ�ҵ��ķǽӿ����ͱ�� ---ENM_RFIDCARDTYPE
* @return 
* @li <0 ʧ��
* @li APP_SUCC �ɹ�
* @author �λ���
* @date 2012-6-1
*/
int PubRFSeekCard(char* psUid,ENM_RFIDCARDTYPE *pnType);

/**
* @brief �ͷſ�(M1��ר��)��
* @param ��
* @return 
* @li <0 ʧ��
* @li APP_SUCC �ɹ�
* @author �λ���
* @date 2012-6-1
*/
int PubRFFreeCard(void);

/**
* @brief �洢������Կ(M1��ר��)��
* @param [in] ucKeySector  ������,1K M1��������[0-15],4K M1��������[0-40],������δ�����ơ�					
* @param [in]  psAKey  A��Կ(6���ֽ�)
* @param [in]  psBKey  B��Կ(6���ֽ�)
* @return 
* @li <0 ʧ��
* @li APP_SUCC �ɹ�
* @author �λ���
* @date 2012-6-1
*/
int PubRFStoreKey(uchar ucKeySector,const char * psAKey,const char * psBKey);

/**
* @brief ��Ƭ������֤,��PubRFStoreKey����ʹ��,(M1��ר��)��
* @param [in] ucKeySector  ������,1K M1��������[0-15],4K M1��������[0-40],������δ�����ơ�					
* @param [in]  ucKeyMode  ��Կģʽ---ENM_RFIDM1KEYMODE
* @return 
* @li <0 ʧ��
* @li APP_SUCC �ɹ�
* @author �λ���
* @date 2012-6-1
*/
int PubRFAuthCard(uchar ucKeySector,uchar ucKeyMode);

/**
* @brief ��Ƭ������֤(�Դ���֤��Կ),(M1��ר��)��
* @param [in] ucKeySector  ������,1K M1��������[0-15],4K M1��������[0-40],������δ�����ơ�					
* @param [in]  ucKeyMode  ��Կģʽ---ENM_RFIDM1KEYMODE
* @param [in]  psKey  ��Կ(6���ֽ�)
* @return 
* @li <0 ʧ��
* @li APP_SUCC �ɹ�
* @author �λ���
* @date 2012-6-1
*/
int PubRFAuthByKey(uchar ucKeySector,uchar ucKeyMode,const char * psKey);

/**
* @brief ��Ƭ���д����,(M1��ר��)��
* @param [in] ucBlockNo  ���,1K M1��������[0-3],4K M1��������[0-15],������δ�����ơ�					
* @param [in]  psData  ��д����(16���ֽ�)
* @return 
* @li <0 ʧ��
* @li APP_SUCC �ɹ�
* @author �λ���
* @date 2012-6-1
*/
int PubRFWrite(uchar ucBlockNo,const char *psData);

/**
* @brief ��Ƭ��Ŷ�����,(M1��ר��)��
* @param [in] ucBlockNo  ���,1K M1��������[0-3],4K M1��������[0-15],������δ�����ơ�					
* @param [in]  psData  ��������(16���ֽ�)
* @return 
* @li <0 ʧ��
* @li APP_SUCC �ɹ�
* @author �λ���
* @date 2012-6-1
*/
int PubRFRead(uchar ucBlockNo,char *psData);

/**
* @brief ��Ƭ�����������,(M1��ר��)��
* @param [in] ucBlockNo  ���,1K M1��������[0-3],4K M1��������[0-15],������δ�����ơ�					
* @param [in]  psData  ������������(4���ֽ�)
* @return 
* @li <0 ʧ��
* @li APP_SUCC �ɹ�
* @author �λ���
* @date 2012-6-1
*/
int PubRFInc(uchar ucBlockNo,const char *psData);

/**
* @brief ��Ƭ��ż�������,(M1��ר��)��
* @param [in] ucBlockNo  ���,1K M1��������[0-3],4K M1��������[0-15],������δ�����ơ�					
* @param [in]  psData  ������������(4���ֽ�)
* @return 
* @li <0 ʧ��
* @li APP_SUCC �ɹ�
* @author �λ���
* @date 2012-6-1
*/
int PubRFDec(uchar ucBlockNo,const char *psData);

/**
* @brief ��Ƭ��Ŵ��Ͳ���,(M1��ר��)��
* @param [in] ucBlockNo  ���,1K M1��������[0-3],4K M1��������[0-15],������δ�����ơ�					
* @return 
* @li <0 ʧ��
* @li APP_SUCC �ɹ�
* @author �λ���
* @date 2012-6-1
*/
int PubRFTransfer(uchar ucBlockNo);

/**
* @brief ��Ƭ��Ÿ���(�ָ�)����,(M1��ר��)��
* @param [in] ucBlockNo  ���,1K M1��������[0-3],4K M1��������[0-15],������δ�����ơ�					
* @return 
* @li <0 ʧ��
* @li APP_SUCC �ɹ�
* @author �λ���
* @date 2012-6-1
*/
int PubRFReStore(uchar ucBlockNo);

/**
* @brief ȡ������롣
* @param ��					
* @return 
* @li �������
* @author �λ���
* @date 2012-6-1
*/
int PubGetCardErrorCode(void);

/**
* @brief ȡ��Ӷ������汾,30+30:ǰ30�ֽ�Ϊ829�汾,��30ΪĬ�϶������汾��
* @param [out] pszVer  �汾�ţ��������������60��					
* @return 
* @li ��
* @author �λ���
* @date 2012-6-1
*/
void PubGetReaderVer(char *pszVer);

/**
* @brief ѡ��ֻ��CPU����M1������������֧�֡�
* @param [in] eCardType  ������---ENM_CARDTYPE��					
* @return 
* @li ��
* @author �λ���
* @date 2012-6-1
*/
void PubSelectCardType(ENM_CARDTYPE eCardType);

/**
* @brief 2.4G������ѯ��
* @param [in] cRf24First  2.4G������ѯ,0:M1�����ȣ�����:CPU�����ȡ�					
* @return 
* @li ��
* @author �λ���
* @date 2012-6-1
*/
void PubRf24First(char cRf24First);

/**
* @brief �ǽӴ�ʽ��������ʾ������
* @param [in] cFlag  ��ʾ����---ENM_READERSHOW
* @param [in] pszAmount  ��ʾ��� 12�ֽ�
* @param [in] pszBalance  ��ʾ��� 12�ֽ�				
* @return 
* @li <0 ʧ��
* @li APP_SUCC �ɹ�
* @author �λ���
* @date 2012-6-1
*/
int PubReadCardDisp(char cFlag,const char* pszAmount,const char* pszBalance );

/**
* @brief ��ȡѰ���Ŀ�ƬƵ�����ͣ�13.56��2.4G��
* @param ��				
* @return 
* @li APP_FAIL  ʧ��
* @li 0  13.56M
* @li 1  2.4G
* @author �λ���
* @date 2012-6-1
*/
int PubGetRfCardType(void);

/**
* @brief ȡ��汾��
* @param [out] 	psVer �汾��(12���ֽ�)		
* @return 
* @li ��
* @author �λ���
* @date 2012-6-1
*/
int PubGetCardLibVer(char* psVer);

/**
* @brief �ϵ�(����Ѱ������)
* @param [out] 	pszRes 
* @return 
* @li ��
* @author �λ���
* @date 2012-6-1
*/
int PubCardPowerUp(char *pszRes);

/**
* @brief �µ�(����Ѱ������)
* @return 
* @li ��
* @author �λ���
* @date 2012-6-1
*/
int PubCardPowerDown();

/**
* @brief �շ�ָ��(����Ѱ�����ͣ�ָ���ѷ�װ��)
* @return 
* @li ��
* @author �λ���
* @date 2012-6-1
*/
int PubCardrw(const int nCommandLen, const char *pszCommand, int *pnLen, char *pszResponse);

/**
* @brief ��״̬(����Ѱ������)
* @return 
* @li APP_FAIL �޿�
* @li APP_SUCC �п�
* @author �λ���
* @date 2012-10-31
*/
int PubGetCardStatus();

/**
* @brief �շ�ָ��(IC����ָ���ѷ�װ��)
* @return 
* @li ��
* @author �λ���
* @date 2012-6-1
*/
int PubICrw(const int nCardPort, const int nCommandLen, const char *pszCommand, int *pnLen, char *pszResponse);

/**
* @brief �ǽӴ�ʽ��beep����
* @param [in]  nDelayTime --- ����������ʱ������λms 
* @param [in]  nTimes --- ���д���
* @param [in]  nInterval --- �������λms
* @return 
* @li ��
* @author �λ���
* @date 2012-6-1
*/
int PubRfReaderBeep(int nDelayTime, int nTimes,int nInterval);

#endif
/* End of lposcard.h*/
