#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "errno.h"
#include <unistd.h>
#include <ctype.h>
#include "NDK.h"
#include "Pri_DownloadApi.h"
#include "Pri_DownloadTool.h"
#include "PriKeyDownload.h"
#include "PriKey_Deal.h"
#include "emvrsa.h"
#include "PSam.h"
#include "debug.h"


#define DOWNLOAD_DIR    "/appfs/download/temp"              /*下载程序的工作目录，也是NLD程序包的下载目录*/
#define KEY_FILE_LEN 512

struct stat {
	unsigned long	st_dev;		/* Device.  */
	unsigned long	st_ino;		/* File serial number.  */
	unsigned int	st_mode;	/* File mode.  */
	unsigned int	st_nlink;	/* Link count.  */
	unsigned int	st_uid;		/* User ID of the file's owner.  */
	unsigned int	st_gid;		/* Group ID of the file's group. */
	unsigned long	st_rdev;	/* Device number, if device.  */
	unsigned long	__pad1;
	long		st_size;	/* Size of file, in bytes.  */
	int		st_blksize;	/* Optimal block size for I/O.  */
	int		__pad2;
	long		st_blocks;	/* Number 512-byte blocks allocated. */
	long		st_atime;	/* Time of last access.  */
	unsigned long	st_atime_nsec;
	long		st_mtime;	/* Time of last modification.  */
	unsigned long	st_mtime_nsec;
	long		st_ctime;	/* Time of last status change.  */
	unsigned long	st_ctime_nsec;
	unsigned int	__unused4;
	unsigned int	__unused5;
};

int DetectedPortType = PORT_NONE;   //检测到的当前通讯口类型:PORT_AUX / PORT_USB
int Auxautodetect = 1;  //正常下载时候的自动检测串口
unsigned int PortEnableCtrl = (1<<PORT_AUX) | (1<<PORT_USB);        // 默认RS232/USB串口均可用
uchar g_passBuf[8];
char g_rdir[3][16]= {{0},{0},{0}};
int g_TypeSam=0,g_TypeIC=0;
EM_ICTYPE g_Sam=ICTYPE_SAM1;

void MessagePrint(char *szChinese, char *szEnglish,int time)
{
	NDK_ScrClrs();
	if (g_Language == 0)
		NDK_ScrPrintf(szChinese);
	else
		NDK_ScrPrintf(szEnglish);
	NDK_KbGetCode(time,NULL);
}

int init(void)
{
	int iRet;
	int nKey;
	iRet = NDK_ScrInitGui ();
	if(NDK_OK !=iRet ) {
		NDK_ScrPrintf("NDK_ScrInitGui fail");
		NDK_KbGetCode(0,&nKey);
		return FAIL;
	}
	NDK_ScrAutoUpdate(1,&iRet);//设置自动刷新界面
	iRet = NDK_SysGetConfigInfo(SYS_CONFIG_LANGUAGE,&g_Language);//读取语言配置
	if (iRet < 0) {
		g_Language = 0;     //取语言失败则默认为中文提示
	}
	return SUCC;
}

int HandShake()
{
	NDK_ScrClrs();
	if (g_Language == 0)
		NDK_ScrPrintf("正在与PC进行连接..\n");
	else
		NDK_ScrPrintf("Connecting PC now..\n");
	WriteDownloadCommand(0x05);//发送下载请求
	NDK_SysMsDelay(100);
	return SUCC;
}

int Trim(char* lpStr)
{
	if(lpStr == NULL)
		return FAIL;
	char tmp[256] = {0};
	char* ptr = lpStr;
	int i=0;

	while(*ptr) {
		if(!isspace(*ptr)) {
			tmp[i]=*ptr;
			i++;
		}
		ptr++;
	}
	if(strlen(tmp)==0)
		return FAIL;
	strcpy(lpStr,tmp);
	return SUCC;
}

int sys_initconfig(char *path,config_t *cfg_file)
{
	if(access(path, F_OK) < 0)
		return FAIL;
	config_init(cfg_file);
	if (config_read_file(cfg_file, path) == CONFIG_FALSE) {
		config_destroy(cfg_file);
		return FAIL;
	}
	return SUCC;
}

int PriKeyConfDeal(unsigned char *owner,unsigned char *ver,char *filenamebuf)
{
	config_t  sys_cfg;
	config_t  cfg_pos;
	FILE *fp;
	config_setting_t *root_class;
	config_setting_t * sys_root_setting;
	config_setting_t * child_root_setting;
	config_setting_t * new_root_setting;
	config_setting_t * root_root_setting;
	int k=0,key_count;
	char buff[256];


	fp = fopen("PriKey.conf", "r");
	if (fp == NULL) {
		fp = fopen("PriKey.conf", "w");
		if (fp == NULL) {
			return FAIL;
		} else {
			config_init(&cfg_pos);
			if (config_read_file(&cfg_pos, "PriKey.conf") == CONFIG_FALSE) {
				config_destroy(&cfg_pos);
				return FAIL;
			}
			root_class = config_root_setting(&cfg_pos);
			if(root_class==NULL) {
				config_destroy(&cfg_pos);
				return FAIL;
			}
			if(NULL==config_setting_add(root_class, "prikey", CONFIG_TYPE_GROUP)) {
				config_destroy(&cfg_pos);
				return FAIL;
			}
			if (! config_write_file(&cfg_pos, "PriKey.conf")) {
				config_destroy(&cfg_pos);
				return FAIL;
			}
			config_destroy(&cfg_pos);
		}
	}
	fclose(fp);
	if(sys_initconfig("PriKey.conf",&sys_cfg)==FAIL) {
		MessagePrint("初始化私钥配置文件失败\n","config file init fail\n",0);
		return FAIL;
	}
	sys_root_setting=config_lookup(&sys_cfg,"prikey");
	if(NULL==sys_root_setting) {
		PDEBUG("%s,%d,-----------------\n",__FUNCTION__,__LINE__);
		config_destroy(&sys_cfg);
		return FAIL;
	}
	key_count=config_setting_length(sys_root_setting);
	for(k=0; k<key_count; k++) {
		char * child_name=NULL;
		char * child_string=NULL;
		char * key_owner=NULL;
		char * key_ver=NULL;
		config_setting_t * ele_root_setting;
		config_setting_t * member_root_setting;
		config_setting_t *parent_root_setting;

		child_root_setting=config_setting_get_elem(sys_root_setting,k);
		if(child_root_setting==NULL) {
			PDEBUG("%s,%d,-----------------\n",__FUNCTION__,__LINE__);
			config_destroy(&sys_cfg);
			return FAIL;
		}
		child_name=config_setting_name(child_root_setting);
		if(child_name==NULL) {
			PDEBUG("%s,%d,-----------------\n",__FUNCTION__,__LINE__);
			config_destroy(&sys_cfg);
			return FAIL;
		}
		ele_root_setting=config_lookup(&sys_cfg,child_name);
		if(ele_root_setting==NULL) {
			PDEBUG("%s,%d,-----------------\n",__FUNCTION__,__LINE__);
			config_destroy(&sys_cfg);
			return FAIL;
		}
		member_root_setting=config_setting_get_member(ele_root_setting,"owner");
		if(member_root_setting==NULL) {
			PDEBUG("%s,%d,-----------------\n",__FUNCTION__,__LINE__);
			config_destroy(&sys_cfg);
			return FAIL;
		}
		key_owner=config_setting_get_string(member_root_setting);
		if(key_owner==NULL) {
			PDEBUG("%s,%d,-----------------\n",__FUNCTION__,__LINE__);
			config_destroy(&sys_cfg);
			return FAIL;
		}
		member_root_setting=config_setting_get_member(ele_root_setting,"ver");
		if(member_root_setting==NULL) {
			PDEBUG("%s,%d,-----------------\n",__FUNCTION__,__LINE__);
			config_destroy(&sys_cfg);
			return FAIL;
		}
		key_ver=config_setting_get_string(member_root_setting);
		if(key_ver==NULL) {
			PDEBUG("%s,%d,-----------------\n",__FUNCTION__,__LINE__);
			config_destroy(&sys_cfg);
			return FAIL;
		}
		if(strcmp((char *)owner,key_owner)==0&&strcmp((char *)ver,key_ver)==0) {
			child_string=config_setting_get_string(child_root_setting);
			if(child_string==NULL) {
				PDEBUG("%s,%d,-----------------\n",__FUNCTION__,__LINE__);
				config_destroy(&sys_cfg);
				return FAIL;
			}
			remove(child_string);
			if(CONFIG_FALSE==config_setting_remove(sys_root_setting,child_name)) {
				PDEBUG("%s,%d Delete key item %s fail\n",__FUNCTION__,__LINE__,child_name);
				config_destroy(&sys_cfg);
				return FAIL;
			}
			parent_root_setting=config_setting_parent(ele_root_setting);
			if(NULL==parent_root_setting) {
				PDEBUG("%s,%d---------------This is the root setting\n",__FUNCTION__,__LINE__);
				config_destroy(&sys_cfg);
				return FAIL;
			}
			child_name=config_setting_name(ele_root_setting);
			if(CONFIG_FALSE==config_setting_remove(parent_root_setting,child_name)) {
				PDEBUG("%s,%d Delete key item %s fail\n",__FUNCTION__,__LINE__,child_name);
				config_destroy(&sys_cfg);
				return FAIL;
			}
			break;
		}
	}
	k=1;
	memset(buff,0x00,sizeof(buff));
	sprintf(buff,"key_%d",k);
	while((new_root_setting=config_setting_add(sys_root_setting,buff,CONFIG_TYPE_STRING))==NULL) {
		k++;
		if(k<256)
			sprintf(buff,"key_%d",k);
		else {
			config_destroy(&sys_cfg);
			return FAIL;
		}
	}
	config_setting_set_string(new_root_setting,filenamebuf);
	root_root_setting=config_root_setting(&sys_cfg);
	if(root_root_setting==NULL) {
		PDEBUG("%s,%d,-----------------\n",__FUNCTION__,__LINE__);
		config_destroy(&sys_cfg);
		return FAIL;
	}
	new_root_setting=config_setting_add(root_root_setting,buff,CONFIG_TYPE_GROUP);
	if(NULL==new_root_setting) {
		PDEBUG("%s,%d,-----------------\n",__FUNCTION__,__LINE__);
		config_destroy(&sys_cfg);
		return FAIL;
	}
	child_root_setting=config_setting_add(new_root_setting,"owner",CONFIG_TYPE_STRING);
	if(child_root_setting==NULL) {
		PDEBUG("%s,%d,-----------------\n",__FUNCTION__,__LINE__);
		config_destroy(&sys_cfg);
		return FAIL;
	}
	config_setting_set_string(child_root_setting,(char *)owner);
	child_root_setting=config_setting_add(new_root_setting,"ver",CONFIG_TYPE_STRING);
	if(child_root_setting==NULL) {
		PDEBUG("%s,%d,-----------------\n",__FUNCTION__,__LINE__);
		config_destroy(&sys_cfg);
		return FAIL;
	}
	config_setting_set_string(child_root_setting,(char *)ver);
	config_write_file(&sys_cfg,"PriKey.conf");
	config_destroy(&sys_cfg);
	return SUCC;
}

int strtobcd(char *pFilename,R_RSA_PRIVATE_KEY *prikey)
{
	struct stat stat_buf,stat_pub;
	int count=0,num=1,nOutFileHandle;
	int hFileIn,iret;
	char ch,buf[256],psam_buf[584];
	unsigned char *ptmp_mod=NULL,p_mod[KEY_FILE_LEN];
	int i, j,temp, ch1;
	unsigned char *pub_buf=NULL,sum;
	union {
		char c[4];
		int i;
	} tmp;
	char len_buf[7];

	memset(p_mod,0x00,sizeof(p_mod));
	if(stat(pFilename, &stat_buf) == FAIL) {
		PDEBUG("%s,%d,Get the size of file '%s' error.\n",__FUNCTION__,__LINE__, pFilename);
		return FAIL;
	}
	hFileIn = open(pFilename,O_RDONLY);

	ptmp_mod=malloc(stat_buf.st_size);
	if(ptmp_mod==NULL) {
		PDEBUG("%s,%d,malloc for private mod error!\n",__FUNCTION__,__LINE__);
		close(hFileIn);
		return FAIL;
	}

	//读取私钥文件中的模
	if(read(hFileIn,ptmp_mod,stat_buf.st_size)!=stat_buf.st_size) {
		PDEBUG("%s,%d,read private mod error!\n",__FUNCTION__,__LINE__);
		close(hFileIn);
		free(ptmp_mod);
		return FAIL;
	}
	close(hFileIn);
	for(i=0,j=0; (i<stat_buf.st_size)&&(j<(stat_buf.st_size+1)/2); i++,j++) {
		if((i==0)&&(stat_buf.st_size%2 != 0)) { //密钥文件中含奇数个字符
			//第一次只算一个字符
			if('A' <= ptmp_mod[i]) { /* A~F, a~f */
				if('a' <= ptmp_mod[i]) { /*小写字母转换为大写字母*/
					ptmp_mod[i]-=32;
				}
				temp=ptmp_mod[i]-65+10;
				p_mod[j]=(0<<4)+((temp%16)&0x0F);
			} else {
				temp=ptmp_mod[i]-48;
				p_mod[j]=(0<<4)+((temp%10)&0x0F);
			}
		} else { /*每次由2个字符算出一个BCD码*/
			if('A' <= ptmp_mod[i]) { /* A~F, a~f */
				if('a' <= ptmp_mod[i]) { /*小写字母转换为大写字母*/
					ptmp_mod[i]-=32;
				}
				temp=ptmp_mod[i]-65+10;
				ch1=((temp%16)&0x0F)<<4;
			} else {
				temp=ptmp_mod[i]-48;
				ch1=((temp%10)&0x0F)<<4;
			}

			if('A' <= ptmp_mod[i+1]) { /* A~F, a~f */
				if('a' <= ptmp_mod[i+1]) { /*小写字母转换为大写字母*/
					ptmp_mod[i+1]-=32;
				}
				temp=ptmp_mod[i+1]-65+10;
				p_mod[j]=ch1+((temp%16)&0x0F);
			} else {
				temp=ptmp_mod[i+1]-48;
				p_mod[j]=ch1+((temp%10)&0x0F);
			}
			i++;/*add 2*/
		}
	}
	(*prikey).mod_bits=8*KEY_FILE_LEN/2;
	(*prikey).exp_bits=8*KEY_FILE_LEN/2;
	memcpy((*prikey).modulus,p_mod,KEY_FILE_LEN/2);
	memcpy((*prikey).exponent,p_mod+KEY_FILE_LEN/2,KEY_FILE_LEN/2);
	iret=system("openssl rsa -in key.pem -pubout -out pubkey.pem");
	if(iret!=0) {
		PDEBUG("openssl rsa -in key.pem -pubout -out pubkey.pem fail\n");
		return FAIL;
	}
	stat("pubkey.pem",&stat_pub);
	PDEBUG("%s,%d,size=%d-------------\n",__FUNCTION__,__LINE__,stat_pub.st_size);
	pub_buf=(unsigned char *)malloc(stat_pub.st_size+4);
	pub_buf[0]='O';
	pub_buf[1]='K';
	pub_buf[stat_pub.st_size+2]=ETX;
	hFileIn = open("pubkey.pem",O_RDONLY);
	if(read(hFileIn,pub_buf+2,stat_pub.st_size)!=stat_pub.st_size) {
		PDEBUG("%s,%d,read pubkey.pem error!\n",__FUNCTION__,__LINE__);
		close(hFileIn);
		free(pub_buf);
		return FAIL;
	}
	sum = 0;
	for (i=2; i<stat_pub.st_size+2; i++) {
		sum += (unsigned char)pub_buf[i];
	}
	pub_buf[stat_pub.st_size+3]=sum;
	sum=0;
	tmp.i=stat_pub.st_size;
	len_buf[0]='O';
	len_buf[1]='K';
	len_buf[2]=tmp.c[0];
	len_buf[3]=tmp.c[1];
	len_buf[4]=tmp.c[2];
	len_buf[5]=ETX;
	sum=len_buf[2]+len_buf[3]+len_buf[4];
	len_buf[6]=sum;
	dl_clrportbuf(1);
	do {
		WriteDownloadCommand(DL_PROC_PUBKEY);
		count++;
		if(count>5) {
			close(hFileIn);
			free(pub_buf);
			PDEBUG("%s,%d,-------------\n",__FUNCTION__,__LINE__);
			return FAIL;
		}
		iret=dl_portread(1, &ch, 3000);
		PDEBUG("%s,%d,%c,%d-------------\n",__FUNCTION__,__LINE__,ch,iret);
	} while(ch!=0x52);

	count=0;
	do {
		dl_portwrite(7,(char *)len_buf);
		count++;
		if(count>5) {
			close(hFileIn);
			free(pub_buf);
			return FAIL;
		}
		iret=dl_portread(1, &ch, 3000);
		PDEBUG("%s,%d,%c,%d-------------\n",__FUNCTION__,__LINE__,ch,iret);
	} while(ch!='S');
	count=0;
	do {
		dl_portwrite(stat_pub.st_size+4,(char *)pub_buf);
		count++;
		if(count>5) {
			close(hFileIn);
			free(pub_buf);
			return FAIL;
		}
		iret=dl_portread(1, &ch, 3000);
		PDEBUG("%s,%d,%c,%d-------------\n",__FUNCTION__,__LINE__,ch,iret);
	} while(ch=='C');
	close(hFileIn);
	free(pub_buf);
	memset(buf,0x00,sizeof(buf));
	sprintf(buf,"%d_prikey",num);
	while(0==access(buf,F_OK)) {
		num++;
		if(num<256)
			sprintf(buf,"%d_prikey",num);
		else
			return FAIL;
	}
	NDK_ScrClrs();
	if (g_Language == 0)
		NDK_ScrPrintf("正在加密和备份私钥..\n");
	else
		NDK_ScrPrintf("Doing Encryption and Backup Prikey..\n");

	iret=PriKey_Deal(prikey,buf,"prikey_11.nk",0);
	if(iret==FAIL) {
		return FAIL;
	}
	if ((nOutFileHandle = open("prikey_11.nk",O_RDWR)) < 0) {
		PDEBUG("%s,%d,open prikey_11.nk fail,iret=%d\n",__FUNCTION__,__LINE__,nOutFileHandle);
		return FAIL;
	}
	memset(psam_buf,0x00,sizeof(psam_buf));
	count=read(nOutFileHandle,psam_buf,584);
	if(count!=584) {
		close(nOutFileHandle);
		return FAIL;
	}
	if(BakPsam_UpdateParam(psam_buf,sizeof(psam_buf))<0) {
		PDEBUG("%s,%d,BakPsam_UpdateParam err!!\n",__FUNCTION__,__LINE__);
		return -1;
	}
	remove("prikey_11.nk");
	iret=PriKeyConfDeal((*prikey).owner,(*prikey).ver,buf);
	if(iret==FAIL) {
		PDEBUG("%s,%d,File compared fail\n",__FUNCTION__,__LINE__);
		return FAIL;
	}
	return SUCC;
}

int PriFile_Creat(R_RSA_PRIVATE_KEY *prikey)
{
	FILE *fpin=NULL,*fpout=NULL;
	char buff[256];
	int iret,first_flag=1,second_flag=0;

	fpin=fopen("1.txt","r");
	if(fpin==NULL) {
		PDEBUG("%s,%d,open 1.txt fail!\n",__FUNCTION__,__LINE__);
		return FAIL;
	}
	fpout=fopen("moudle.txt","w+");
	if(fpout==NULL) {
		PDEBUG("%s,%d,open module.txt fail!\n",__FUNCTION__,__LINE__);
		fclose(fpin);
		return FAIL;
	}
	memset(buff,0x00,sizeof(buff));
	fgets(buff,256,fpin);
	fgets(buff,256,fpin);
	while(1) {
		char *str=NULL;
		memset(buff,0x00,sizeof(buff));
		if(NULL==fgets(buff,256,fpin)) {
			PDEBUG("%s,%d,fgets str fail!\n",__FUNCTION__,__LINE__);
			fclose(fpin);
			fclose(fpout);
			return FAIL;
		}
		if(strstr(buff,"prime1")!=NULL) {
			break;
		}
		if(strstr(buff,"publicExponent")!=NULL) {
			second_flag=1;
			fgets(buff,256,fpin);
			continue;
		}
		while((str=strchr(buff,':'))!=NULL) {
			*str=0x20;
		}
		iret=Trim(buff);
		if(FAIL==iret) {
			continue;
		}
		if(first_flag==1) {
			fputs(buff+2,fpout);
			first_flag=0;
		} else if(second_flag==1) {
			if(buff[0]=='0'&&buff[1]=='0') {
				fputs(buff+2,fpout);
				second_flag=0;
			} else {
				fputs(buff,fpout);
				second_flag=0;
			}
		} else {
			fputs(buff,fpout);
		}
	}
	fclose(fpin);
	fclose(fpout);
	iret=strtobcd("moudle.txt",prikey);
	if(iret==FAIL) {
		remove("1.txt");
		remove("moudle.txt");
		remove("key.pem");
		remove("pubkey.pem");
		return FAIL;
	}
	remove("moudle.txt");
	remove("key.pem");
	remove("pubkey.pem");
	remove("1.txt");
	return SUCC;
}

int GetNum(char *filename)
{
	int num;
	char str[3];

	if(filename==NULL)
		return FAIL;
	memcpy(str,filename,3);
	num=atoi(str);
	return num;
}

int SumSignature(R_RSA_PRIVATE_KEY *prikey)
{
	int keycount,i,num;
	int nInFileHandle,iret,count;
	uchar udesout[8]= {0}, udesin[8]= {0};
	char *keyfilename=NULL;
	char *key_name=NULL;
	char *owner=NULL;
	char *ver=NULL;
	char *p;
	char buff[256];
	st_item_details prikeyitem[100];
	st_item_details *selitem=NULL;
	config_t sys_cfg;
	config_setting_t *sys_root_setting;

	memset(prikeyitem,0x00,sizeof(prikeyitem));
	if(sys_initconfig("PriKey.conf",&sys_cfg)==FAIL) {
		MessagePrint("conf 文件初始化失败\n","conf ini fail\n",0);
		return FAIL;
	}
	sys_root_setting=config_lookup(&sys_cfg,"prikey");
	if(sys_root_setting==NULL) {
		MessagePrint("配置文件格式有误\n","conf format error\n",0);
		config_destroy(&sys_cfg);
		return FAIL;
	}
	keycount=config_setting_length(sys_root_setting);
	if(0==keycount) {
		MessagePrint("没有私钥文件\n","No PriKey File\n",0);
		config_destroy(&sys_cfg);
		return FAIL;
	}
	NDK_ScrClrs();
	for(i=0; i<keycount; i++) {
		memset(buff,0x00,sizeof(buff));
		config_setting_t *ele_root_setting;
		config_setting_t *child_root_setting;

		ele_root_setting=config_setting_get_elem(sys_root_setting,i);
		key_name=config_setting_name(ele_root_setting);
		if(key_name==NULL) {
			config_destroy(&sys_cfg);
			return FAIL;
		}
		child_root_setting=config_lookup(&sys_cfg,key_name);
		if(child_root_setting==NULL) {
			config_destroy(&sys_cfg);
			return FAIL;
		}
		if(CONFIG_FALSE==config_setting_lookup_string(child_root_setting,"owner",&owner)) {
			config_destroy(&sys_cfg);
			return FAIL;
		}
		if(CONFIG_FALSE==config_setting_lookup_string(child_root_setting,"ver",&ver)) {
			config_destroy(&sys_cfg);
			return FAIL;
		}
		sprintf(buff,"%s_%s",owner,ver);
		strcpy(prikeyitem[i].name[0],buff);
		strcpy(prikeyitem[i].name[1],buff);
		prikeyitem[i].func=NULL;
	}
	strcpy(prikeyitem[i].name[0],"end");
	selitem=build_menu(prikeyitem);
	if(NULL==selitem) {
		config_destroy(&sys_cfg);
		return -2;
	}
	NDK_ScrClrs();
	if (g_Language == 0)
		NDK_ScrPrintf("正在解密私钥..\n");
	else
		NDK_ScrPrintf("Des PriKey now..\n");
	keyfilename=config_setting_get_string_elem(sys_root_setting,selitem-prikeyitem);
	PDEBUG("%s,%d,keyfilename=%s--------\n",__FUNCTION__,__LINE__,keyfilename);
	num=GetNum(keyfilename);
	if(num==FAIL) {
		config_destroy(&sys_cfg);
		return FAIL;
	}
	if ((nInFileHandle = open((const char *)keyfilename, O_RDWR)) < 0) {
		config_destroy(&sys_cfg);
		return FAIL;
	}
	p=(char *)prikey;
	for(i=0; i<sizeof(R_RSA_PRIVATE_KEY)/8; i++) {
		count=read(nInFileHandle,udesin,8);
		if(count!=8) {
			close(nInFileHandle);
			config_destroy(&sys_cfg);
			return FAIL;
		}
		iret=NDK_SecCalcDes(SEC_KEY_TYPE_TDK, num, udesin, 8, udesout, SEC_DES_DECRYPT|SEC_DES_KEYLEN_8);
		if(iret!=NDK_OK) {
			MessagePrint("解密失败\n","DECRYPT Fail\n",0);
			config_destroy(&sys_cfg);
			close(nInFileHandle);
			return FAIL;
		}
		memcpy(p,udesout,8);
		p+=8;
	}
	close(nInFileHandle);
	config_destroy(&sys_cfg);
	return SUCC;
}

int GetPriKeyFile()
{
	int hnd;
	int len,  j, rlen, lastframe;
	char buf[2048];
	union {
		char c[4];
		int i;
	} tmp;
	int nBytesRead, nBytesWrite;
	char *bp = NULL;
	char *pFilename=CSR_SIGN_FILE;
	int iret;

	MessagePrint("接收数据长度...\n","Receiving file\nlength...\n",1);
	WriteDownloadCommand(DL_CMD_FILEOWER);
	iret = RecOneFrameWithRepeat(7, buf, 2000) ;

	tmp.c[0] = buf[2];
	tmp.c[1] = buf[3];
	tmp.c[2] = buf[4];
	tmp.c[3] = 0;
	len = tmp.i;    //要下载的文件长度

	if ((hnd=open(pFilename,O_RDWR|O_CREAT|O_TRUNC,0666)) == FSFAIL) { // 4......打开文件.................................
		MessagePrint("创建文件prikey.bak失败\n","Cannot create\nfile prikey.bak",0);
		return FAIL;
	}
	if (g_Language !=0) {
		NDK_ScrPrintf("File length is:%d\n", len);
		NDK_ScrPrintf("\nReceiving...");
	} else {
		NDK_ScrPrintf("文件大小:%d\n", len);
	}
	MessagePrint("接收数据内容...\n","Receiving file data...\n",1);
	for (j=0; ; j++) { //接受数据并写到文件
		if (dl_portwrite(1, "S") == FAIL) {
			close(hnd);
			remove(pFilename);
			if (g_Language !=0)
				DispMsg_exit("RS232: \nWrite S Fail");
			else
				DispMsg_exit("串口写S失败");
		}
		if (len > FL) {
			rlen = FL;
			len -= FL;
			lastframe = FALSE;
		} else {
			rlen = len;
			lastframe = TRUE;
		}
		if (RecOneFrameWithRepeat(rlen+4, buf, 2000) == FAIL) { //接收数据
			close(hnd);
			remove(pFilename);
			MessagePrint("接收数据失败","Receive data \nfailed",0);
			return FAIL;
		}

		nBytesRead = rlen;
		bp = &buf[2];
		while (nBytesRead > 0) {
			while (((nBytesWrite=write(hnd,bp,nBytesRead))==FSFAIL)&&(errno == EINTR))  ;
			if (nBytesWrite < 0) {
				if (errno == ENOSPC) { //磁盘空间不足
					MessagePrint("磁盘空间不足\n\n写文件失败", "No enough flash space.\n\nWrite file \nfailed.",0);
				} else {
					MessagePrint("\n写文件失败","Write file \nfailed.",0);
				}
				close(hnd);
				remove(pFilename);
				return FAIL;
			}
			if (nBytesWrite == 0)
				break;
			nBytesRead -= nBytesWrite;
			bp += nBytesWrite;
		}
		if (nBytesRead != 0) {
			close(hnd);
			remove(pFilename);
			return FAIL;
		}
		if (lastframe == TRUE)
			break;
	}
	close(hnd);
	return SUCC;
}

int GetCSRFile()
{
	int hnd;
	int len,  j, rlen, lastframe;
	char buf[2048];
	union {
		char c[4];
		int i;
	} tmp;
	int nBytesRead, nBytesWrite;
	char *bp = NULL;
	char *pFilename=CSR_SIGN_FILE;
	int iret;

	MessagePrint("接收数据长度...\n","Receiving file\nlength...\n",1);
	WriteDownloadCommand(DL_CMD_FILEOWER);
	iret = RecOneFrameWithRepeat(7, buf, 2000) ;

	tmp.c[0] = buf[2];
	tmp.c[1] = buf[3];
	tmp.c[2] = buf[4];
	tmp.c[3] = 0;
	len = tmp.i;    //要下载的文件长度
	WDEBUG("recv file len:%d",len);

	if ((hnd=open(pFilename,O_RDWR|O_CREAT|O_TRUNC,0666)) == FSFAIL) { // 4......打开文件.................................
		MessagePrint("创建文件RecvCSR失败\n","Cannot create\nfile RecvCSR",0);
		return FAIL;
	}
	if (g_Language !=0) {
		NDK_ScrPrintf("File length is:%d\n", len);
		NDK_ScrPrintf("\nReceiving...");
	} else {
		NDK_ScrPrintf("文件大小:%d\n", len);
	}
	MessagePrint("接收数据内容...\n","Receiving file data...\n",1);
	for (j=0; ; j++) { //接受数据并写到文件
		if (dl_portwrite(1, "S") == FAIL) {
			close(hnd);
			remove(pFilename);
			if (g_Language !=0)
				DispMsg_exit("RS232: \nWrite S Fail");
			else
				DispMsg_exit("串口写S失败");
		}
		if (len > FL) {
			rlen = FL;
			len -= FL;
			lastframe = FALSE;
		} else {
			rlen = len;
			lastframe = TRUE;
		}
		if (RecOneFrameWithRepeat(rlen+4, buf, 2000) == FAIL) { //接收数据
			close(hnd);
			remove(pFilename);
			MessagePrint("接收数据失败","Receive data \nfailed",0);
			return FAIL;
		}

		nBytesRead = rlen;
		bp = &buf[2];
		while (nBytesRead > 0) {
			while (((nBytesWrite=write(hnd,bp,nBytesRead))==FSFAIL)&&(errno == EINTR))  ;
			if (nBytesWrite < 0) {
				if (errno == ENOSPC) { //磁盘空间不足
					MessagePrint("磁盘空间不足\n\n写文件失败", "No enough flash space.\n\nWrite file \nfailed.",0);
				} else {
					MessagePrint("\n写文件失败","Write file \nfailed.",0);
				}
				close(hnd);
				remove(pFilename);
				return FAIL;
			}
			if (nBytesWrite == 0)
				break;
			nBytesRead -= nBytesWrite;
			bp += nBytesWrite;
		}
		if (nBytesRead != 0) {
			close(hnd);
			remove(pFilename);
			return FAIL;
		}
		if (lastframe == TRUE)
			break;
	}
	close(hnd);
	return SUCC;
}

int EnterNewDownload(R_RSA_PRIVATE_KEY *prikey)
{
	char ch;
	int iret = 0;
	int num=1,i,count;
	unsigned char sum;
	char cmd[512],buff[512];
	char buf[68];
	unsigned char strDigest[24]= {0};
	unsigned char Digest[20]= {0};
	unsigned char *pOutput = NULL;
	unsigned int OutputLen = 0;
	unsigned char OutputBuf[KEY_FILE_LEN/2+4];
	char recFilename[30] = {0};

	memset(OutputBuf,0x00,sizeof(OutputBuf));
	NDK_PortClrBuf(PORT_NUM_USB);
	pOutput=(unsigned char*)malloc(KEY_FILE_LEN/2+4);
	WriteDownloadCommand(0x17);
	iret = dl_portread(1, &ch, 3000);
	WDEBUG("%d",iret);
	WDEBUG("%d",ch);
	switch(ch) {
		case 0x30: {
					   WDEBUG("run");
					   NDK_ScrClrs();
					   if (g_Language == 0)
						   NDK_ScrPrintf("正在生成公私钥..\n");
					   else
						   NDK_ScrPrintf("Generating Pub/PriKey..\n");
					   WriteDownloadCommand(DL_CMD_FILEOWER);
					   iret=RecOneFrameWithRepeat(68, buf, 2000);
					   if(iret==FAIL) {
						   PDEBUG("%s,%d,接收数据失败\n",__FUNCTION__,__LINE__);
						   return -1;
					   }
					   memcpy((*prikey).owner,buf+2,32);
					   memcpy((*prikey).ver,buf+34,16);
					   memcpy((*prikey).info_reserved,buf+50,16);
					   iret=system("openssl genrsa -out key.pem 2048");
					   if(0!=iret) {
						   PDEBUG("%s,%d,生成公私渴О躙n",__FUNCTION__,__LINE__);
						   return -1;
					   }
					   iret=system("openssl rsa -text -in key.pem  >1.txt");
					   if(iret!=0) {
						   PDEBUG("%s,%d,转换公私钥失败\n",__FUNCTION__,__LINE__);
						   return -1;
					   }
					   iret=PriFile_Creat(prikey);
					   if(iret==FAIL) {
						   PDEBUG("%s,%d,生成私钥文件失败\n",__FUNCTION__,__LINE__);
						   return -1;
					   }
					   iret=1;
				   }
				   break;
		case 0x32: {
					   WDEBUG("run");
					   NDK_ScrClrs();
					   if (g_Language == 0)
						   NDK_ScrPrintf("正在进行签名..\n");
					   else
						   NDK_ScrPrintf("Signature now..\n");
					   WriteDownloadCommand(DL_CMD_FILEOWER);
					   iret=RecOneFrameWithRepeat(24,(char *)strDigest, 2000);
					   if(iret==FAIL) {
						   return -2;
					   }
					   memcpy(Digest,strDigest+2,20);
					   OutputLen = xauth_private_encryption(PRI_KEY_FILE, 20, Digest, pOutput, 0);
					   /*iret=RSAPublicEncrypt(pOutput, &OutputLen, Digest, 20, prikey);*/
					   PDEBUG("%s,%d,len=%d-------------\n",__FUNCTION__,__LINE__,OutputLen);
					   if(OutputLen!=256) {
						   return -2;
					   }
					   OutputBuf[0]='O';
					   OutputBuf[1]='K';
					   memcpy(OutputBuf+2,pOutput,OutputLen);
					   OutputBuf[sizeof(OutputBuf)-2]=ETX;
					   sum = 0;
					   for (i=2; i<sizeof(OutputBuf)-2; i++) {
						   sum += (unsigned char)OutputBuf[i];
						   PDEBUG("%d-",sum);
					   }
					   OutputBuf[sizeof(OutputBuf)-1]=sum;
					   PDEBUG("%s,%d,sum=%d,out=%d-------------\n",__FUNCTION__,__LINE__,sum,OutputBuf[sizeof(OutputBuf)-1]);

					   count=0;
					   do {
						   if(FAIL==dl_portwrite(OutputLen+4,(char *)OutputBuf)) {
							   free(pOutput);
							   return -2;
						   }
						   count++;
						   if(count>5) {
							   free(pOutput);
							   return -2;
						   }
						   iret=dl_portread(1, &ch, 3000);
						   PDEBUG("%s,%d,%c,%d-------------\n",__FUNCTION__,__LINE__,ch,iret);
					   } while(ch=='C');
					   free(pOutput);
					   iret=2;
				   }
				   break;
		case 0x33: {
					   WDEBUG("run");
					   WriteDownloadCommand(DL_CMD_FILEOWER);
					   iret=GetPriKeyFile();
					   if(FAIL==iret) {
						   remove("prikey.bak");
						   return -3;
					   }

					   sprintf(cmd,"%d_prikey",num);
					   while(access(cmd,F_OK)==0) {
						   num++;
						   sprintf(cmd,"%d_prikey",num);
						   if(num>255) {
							   remove("prikey.bak");
							   return -3;
						   }
					   }
					   memset(buff,0x00,sizeof(buff));
					   sprintf(buff,"mv prikey.bak %d_prikey.bak",num);
					   system(buff);
					   memset(buff,0x00,sizeof(buff));
					   sprintf(buff,"%d_prikey.bak",num);
					   iret=PriKey_Deal(prikey,buff,cmd,2);
					   if(iret==FAIL) {
						   PDEBUG("%s,%d,PriKey_Deal Fail\n",__FUNCTION__,__LINE__);
						   remove(buff);
						   return -3;
					   }
					   iret=PriKeyConfDeal((*prikey).owner,(*prikey).ver,cmd);
					   if(iret==FAIL) {
						   PDEBUG("%s,%d,PriKeyConfDeal fail\n",__FUNCTION__,__LINE__);
						   remove(buff);
						   return -3;
					   }
					   iret=3;
					   remove(buff);
				   }
				   break;
		case 'A': {
					  WDEBUG("CSR File Download");
					  WriteDownloadCommand(DL_CMD_FILENAMELEN);
					  iret=RecieveCertFile(recFilename);
					  if(FAIL==iret) {
						  WDEBUG("error!");
						  remove(CSR_SIGN_FILE);
						  return -4;
					  }
					  if(show_csr() != SUCC){
						  WDEBUG("error!");
						  return -4;
					  }

					  iret = make_csr_sign();
					  fprintf(stderr, "return form make csr\n");
					  if(iret != SUCC){
						  WDEBUG("error");
						  EchoError("Sign Failed!");
						  return -4;
					  }
					  WDEBUG("Send signed file");
					  dl_clrportbuf(1);
					  iret = SendCertFile(NEW_CERT_FILE, CERT_FILE);
					  if(FAIL==iret) {
						  EchoError("Send Cert Failed!");
						  return -4;
					  }
					  iret=4;
				  }
				  break;
	}
	return iret;
}

int PriKeyDownload(R_RSA_PRIVATE_KEY *prikey)
{
	int iRet;
	WDEBUG("run");
	iRet = EnterNewDownload(prikey);
	if(iRet<0) {
		NDK_SysTimeBeep(2500, 250);
		NDK_SysMsDelay(100);
		NDK_SysTimeBeep(2500, 250);
		switch(iRet) {
			case -1:
				MessagePrint("公私钥生成失败", "Generate Pub/Pri Key fail!",0);
				break;
			case -2:
				MessagePrint("签名失败\n","Signature Fail\n",0);
				break;
			case -3:
				MessagePrint("获取私钥文件失败\n","Get Prikey File Fail\n",0);
				break;
			case -4:
				MessagePrint("签名证书请求文件失败\n","Get Prikey File Fail\n",0);
				break;
			default :
				break;
		}
		return FAIL;
	} else if(iRet>0) {
		NDK_SysTimeBeep(2500, 500);//playmusic("|+2.16|2.16|5.8|7.8|+7.8|5.4|");
		switch(iRet) {
			case 1:
				MessagePrint("公私钥生成成功", "Generate Pub/Pri Key succ!",0);
				break;
			case 2:
				MessagePrint("签名成功","Signature Succ",0);
				break;
			case 3:
				MessagePrint("获取私钥文件成功\n","Get Prikey File Succ\n",0);
				break;
			case 4:
				MessagePrint("签名证书请求文件成功\n","Get Prikey File Succ\n",0);
				break;
			default:
				break;
		}
		iRet=2;
	}
	return iRet;
}

int PriKeyInput()
{
	int iret,num=1,count,key;
	int nInFileHandle;
	char buf[256];
	char read[584];
	int filelen;
	R_RSA_PRIVATE_KEY prikey;
	st_item_details priitem[100];

	memset(priitem,0x00,sizeof(priitem));
	iret=IsSamICReady();
	if(iret==FAIL)
		return FAIL;
	iret=SetPassword(0);
	if(iret==FAIL) {
		MessagePrint("输入口令失败\n","Set Password Fail\n",0);
		return -2;
	}
	if(BakPsam_Read_Param(read,&filelen,sizeof(read))<0) {
		PDEBUG("%s,%d,BakPsam_UpdateParam err!!\n",__FUNCTION__,__LINE__);
		return -1;
	}
	if ((nInFileHandle = open("prikey_11.nk", O_RDWR|O_CREAT)) <0) {
		PDEBUG("%s,%d,open prikey_11.nk fail\n",__FUNCTION__,__LINE__);
		return FAIL;
	}
	count=write(nInFileHandle,read,584);
	if(count!=584) {
		close(nInFileHandle);
		return FAIL;
	}
	close(nInFileHandle);
	memset(buf,0x00,sizeof(buf));
	sprintf(buf,"%d_prikey",num);
	while(0==access(buf,F_OK)) {
		num++;
		if(num<256)
			sprintf(buf,"%d_prikey",num);
		else
			return FAIL;
	}
	NDK_ScrClrs();
	if (g_Language == 0)
		NDK_ScrPrintf("导入后原有的相同所有者和版本的私钥将被覆盖,任意键继续，取消键返回..\n");
	else
		NDK_ScrPrintf("The key with same owner and ver will be covered by new one，any key to continue,Esc to back..\n");
	NDK_KbGetCode(0,&key);
	if(key==ESC)
		return -2;
	NDK_ScrClrs();
	if (g_Language == 0)
		NDK_ScrPrintf("正在导入，请稍候..\n");
	else
		NDK_ScrPrintf("Inputing now,Pls wait..\n");
	iret=PriKey_Deal(&prikey,buf,"prikey_11.nk",1);
	if(iret==FAIL) {
		PDEBUG("%s,%d,PriKey_Deal fail\n",__FUNCTION__,__LINE__);
		return FAIL;
	}
	PDEBUG("%s,%d,rev=%s---\n",__FUNCTION__,__LINE__,prikey.info_reserved);
	if(memcmp(prikey.info_reserved,"newland",7)!=0) {
		MessagePrint("导入的私钥有误","Inputed key error",0);
		remove("prikey_11.nk");
		remove(buf);
		return FAIL;
	}
	iret=PriKeyConfDeal(prikey.owner,prikey.ver,buf);
	if(iret==FAIL) {
		PDEBUG("%s,%d,PriKeyConfDeal fail\n",__FUNCTION__,__LINE__);
		return FAIL;
	}
	remove("prikey_11.nk");
	return SUCC;
}

int KeyDesEnc(char *file_name,char *name)
{
	int nInFileHandle,nOutFileHandle;
	uchar udesout[8]= {0}, udesin[8]= {0},udataout[8]= {0};
	int num,count,iret,i;

	iret=SetPassword(1);
	if(iret==FAIL) {
		MessagePrint("设置口令失败\n","Set Password Fail\n",0);
		return FAIL;
	}
	NDK_ScrClrs();
	if (g_Language == 0)
		NDK_ScrPrintf("正在导出，请稍候..\n");
	else
		NDK_ScrPrintf("Outputing now,Pls wait..\n");
	num=GetNum(file_name);
	if(num==FAIL)
		return FAIL;
	PDEBUG("%s,%d------------num=%d\n",__FUNCTION__,__LINE__,num);
	if ((nInFileHandle = open((const char *)file_name, O_RDONLY)) <0) {
		return FAIL;
	}
	if ((nOutFileHandle = open(name, O_RDWR|O_CREAT|O_TRUNC, 0666)) < 0) {
		close(nInFileHandle);
		return FAIL;
	}
	for(i=0; i<FILELEN/8; i++) {
		count=read(nInFileHandle,udesin,8);
		if(count!=8) {
			close(nInFileHandle);
			close(nOutFileHandle);
			return FAIL;
		}
		iret=NDK_SecCalcDes(SEC_KEY_TYPE_TDK, num, udesin, 8, udesout, SEC_DES_DECRYPT|SEC_DES_KEYLEN_8);
		if(iret!=NDK_OK) {
			MessagePrint("解密失败\n","DECRYPT Fail\n",0);
			close(nInFileHandle);
			close(nOutFileHandle);
			return FAIL;
		}
		iret=NDK_AlgTDes(udesout,udataout,g_passBuf,8,ALG_TDS_MODE_ENC);
		if(iret!=NDK_OK) {
			MessagePrint("口令加密失败\n","Password ENC Fail\n",0);
			close(nInFileHandle);
			close(nOutFileHandle);
			return FAIL;
		}
		count=write(nOutFileHandle,udataout,8);
		if(count!=8) {
			close(nInFileHandle);
			close(nOutFileHandle);
			return FAIL;
		}
	}
	close(nInFileHandle);
	close(nOutFileHandle);
	return SUCC;
}

int IsSamICReady()
{
	int iRet,key;

	NDK_ScrClrs();
	if(g_TypeSam==1) {
		if (g_Language == 0)
			NDK_ScrPrintf("请确保SAM卡已插入,任意键继续,取消键退出\n");
		else
			NDK_ScrPrintf("Ensure SAM card is inserted,Any key to continue,Cancel to Esc\n");
	} else if(g_TypeIC==1) {
		if (g_Language == 0)
			NDK_ScrPrintf("请确保IC卡已插入,任意键继续,取消键退出\n");
		else
			NDK_ScrPrintf("Ensure IC card is inserted,Any key to continue,Cancel to Esc\n");
	}
	NDK_KbGetCode(0,&key);
	if(key==K_ESC)
		return FAIL;
	iRet=BakPsam_PowerUp();
	if(iRet==-1) {
		if(g_TypeSam==1)
			MessagePrint("SAM卡上电失败!","SAM card powerup  fail!",0);
		else if(g_TypeIC==1)
			MessagePrint("IC卡上电失败!","IC card powerup  fail!",0);
		return FAIL;
	}
	return 0;
}

int IsUdiskReady()
{
	int status,nState,iret;

	NDK_ScrClrs();
	if (g_Language == 0)
		NDK_ScrPrintf("请插入U盘,任意键继续\n");
	else
		NDK_ScrPrintf("Pls insert U disk ,Any key to continue\n");
	NDK_KbGetCode(0,NULL);
	NDK_ScrClrs();
	if (g_Language == 0)
		NDK_ScrPrintf("正在打开U盘,请稍候,取消键退出!\n");
	else
		NDK_ScrPrintf("Opening U Disk,pls wait,Cancel to Esc!\n");
	NDK_DiskOpen(UDISK,0);
	while(status!=0x1b) {
		iret=NDK_DiskGetState(UDISK,&nState);
		if(iret<0) {
			fprintf(stderr,"NDK_DiskGetState fail current state=[%d]\n",iret);
			break;
		}
		if(nState==DISKMOUNTSUCC) {
			break;
		} else {
			sleep(1);
		}
		NDK_KbGetCode(1,&status);
	}
	if((status==0x1b)||(iret<0)) {
		return FAIL;
	}
	return SUCC;
}

#define DEFAULT_PAGE_MAX 10
st_item_details * build_menu(st_item_details *list)
{
	int gview_w,gview_h;
	int gfonth,gfontw;
	int currentpage = 0;
	int currentitem = 0;
	int columcount = 0;
	int keynum,num=1;
	int keycode;
	int linespace,pagespace;
	int spacecount;
	char spacefill[32];
	int pagecount = DEFAULT_PAGE_MAX;
	char *count_perpage;
	st_item_details *p;


	count_perpage= calloc(1,sizeof(char)*pagecount);
	NDK_ScrGetLcdSize(&gview_w,&gview_h);
	NDK_ScrGetFontSize(&gfontw,&gfonth);
	do {
		linespace = gview_w;
		pagespace=gview_h;
		p = list+currentitem;
		keynum = 1;
		columcount = 0;
		NDK_ScrClrs();
		while(memcmp(p->name[0],"end",3)!=0) {
			if((strlen(p->name[g_Language])+2)*(gfontw/2)>gview_w||(keynum>10)) {
				if(linespace&&(linespace!=gview_w))
					NDK_ScrPrintf("\n");
				linespace = gview_w;
				columcount = 0;
				if(((strlen(p->name[g_Language])+2)*(gfontw/2))%gview_w==0) {
					num=((strlen(p->name[g_Language])+2)*(gfontw/2))/gview_w;
				} else {
					num=((strlen(p->name[g_Language])+2)*(gfontw/2))/gview_w+1;
				}
				PDEBUG("%s,%d,num=%d,keynum=%d,%d\n",__FUNCTION__,__LINE__,num,keynum,(pagespace-num*gfonth));
				if(((pagespace-num*gfonth)<0)||(keynum>10)) {
					*(count_perpage+currentpage) = (keynum-1);
					break;
				} else {
					pagespace =pagespace-num*gfonth;
				}
				NDK_ScrPrintf("%d.%s\n",(keynum++)%10,p->name[g_Language]);
				p++;
				continue;
			}
			if((linespace<(strlen(p->name[g_Language])+2)*(gfontw/2))||(columcount==2)||(keynum>10)) {
				if(linespace&&(linespace!=gview_w))
					NDK_ScrPrintf("\n");
				linespace = gview_w;
				columcount = 0;
				if(((pagespace-gfonth)<0)||(keynum>10)) {
					*(count_perpage+currentpage) = (keynum-1);
					break;
				} else {
					pagespace -=gfonth;

				}
			}

			if(columcount==1) {
				if(((strlen(p->name[g_Language])+2)*(gfontw/2)>(gview_w/2))||(linespace<(gview_w/2))) {
					spacecount = (linespace-(strlen(p->name[g_Language])+2)*(gfontw/2))/(gfontw/2);
				} else {
					spacecount = (gview_w/2-(gview_w-linespace))/(gfontw/2);
					if((linespace==(gview_w/2))&&((strlen(p->name[g_Language])+3)*(gfontw/2)<=(gview_w/2))) {
						spacecount++;
					}
				}
				if(spacecount) {
					memset(spacefill,0x20,spacecount);
					spacefill[spacecount] =0;
					NDK_ScrPrintf("%s",spacefill);
					linespace-=(spacecount*gfontw/2);
				}

			}
			if(columcount==0) {
				if((pagespace-gfonth)<0) {
					*(count_perpage+currentpage) = (keynum-1);
					break;
				}
			}
			NDK_ScrPrintf("%d.%s",(keynum++)%10,p->name[g_Language]);
			linespace-=((strlen(p->name[g_Language])+2)*(gfontw/2));
			columcount++;
			p++;
		}
		NDK_ScrRefresh();
		NDK_KbGetCode(0,&keycode);
		switch(keycode) {
			case DOWN:
			case RIGHT:
			case F2:
				if(memcmp((list+currentitem+(keynum-1))->name[0],"end",3)!=0) {
					currentitem+=(keynum-1);
					currentpage++;
					if(currentpage>=pagecount) {
						pagecount+=DEFAULT_PAGE_MAX;
						count_perpage = realloc(count_perpage,sizeof(char)*pagecount);
					}
				}
				break;
			case UP:
			case LEFT:
			case F1:
				if(currentpage>0) {
					currentpage--;
					currentitem -=*(count_perpage+currentpage);
				}
				break;
			case K_ESC:
				break;
			default: {
						 st_item_details *choose;
						 if((keycode=='0')&&((keynum-1)==10)) {
							 choose = list+currentitem+9;
							 free(count_perpage);
							 return choose;
							 //choose->func(choose->name[g_Language]);
						 } else if((keycode>='1')&&(keycode<=('0'+(keynum-1)))) {
							 choose = list+currentitem+(keycode-'0')-1;
							 free(count_perpage);
							 return choose;
							 //choose->func(choose->name[g_Language]);
						 }

						 break;
					 }
		}
	} while(keycode!=K_ESC);
	free(count_perpage);
	return NULL;
}

int PriKeyOutput()
{
	config_t sys_cfg;
	config_setting_t *sys_root_setting;
	config_setting_t *ele_root_setting;
	config_setting_t *child_root_setting;
	int key_count,i,iret,key;
	int nOutFileHandle,count;
	char *key_name=NULL;
	char *file_name=NULL;
	char *owner=NULL;
	char *ver=NULL;
	char ownerbuf[256]= {0},verbuf[256]= {0};
	char buff[256];
	char buf[584];
	char *p=NULL;
	st_item_details prikeyitem[100];
	st_item_details *selitem=NULL;
	memset(prikeyitem,0x00,sizeof(prikeyitem));

	iret=IsSamICReady();
	if(iret==FAIL)
		return FAIL;
	if(sys_initconfig("PriKey.conf",&sys_cfg)==FAIL) {
		MessagePrint("初始化PriKey.conf失败\n","Init PriKey.conf Fail\n",0);
		return FAIL;
	}
	sys_root_setting=config_lookup(&sys_cfg,"prikey");
	if(sys_root_setting==NULL) {
		MessagePrint("配置文件格式有误\n","Config file's format error\n",0);
		config_destroy(&sys_cfg);
		return FAIL;
	}
	key_count=config_setting_length(sys_root_setting);
	if(key_count==0) {
		MessagePrint("没有私钥文件\n","No PriKey File\n",0);
		config_destroy(&sys_cfg);
		return FAIL;
	}

	for(i=0; i<key_count; i++) {
		memset(buff,0x00,sizeof(buff));
		ele_root_setting=config_setting_get_elem(sys_root_setting,i);
		key_name=config_setting_name(ele_root_setting);
		if(key_name==NULL) {
			config_destroy(&sys_cfg);
			return FAIL;
		}
		child_root_setting=config_lookup(&sys_cfg,key_name);
		if(child_root_setting==NULL) {
			config_destroy(&sys_cfg);
			return FAIL;
		}
		if(CONFIG_FALSE==config_setting_lookup_string(child_root_setting,"owner",&owner)) {
			config_destroy(&sys_cfg);
			return FAIL;
		}
		if(CONFIG_FALSE==config_setting_lookup_string(child_root_setting,"ver",&ver)) {
			config_destroy(&sys_cfg);
			return FAIL;
		}
		sprintf(buff,"%s_%s",owner,ver);
		strcpy(prikeyitem[i].name[0],buff);
		strcpy(prikeyitem[i].name[1],buff);
		prikeyitem[i].func=NULL;
	}
	strcpy(prikeyitem[i].name[0],"end");
	selitem=build_menu(prikeyitem);
	if(NULL==selitem) {
		config_destroy(&sys_cfg);
		return -2;
	}
	p=strstr(selitem->name[0],"_");
	if(p==NULL) {
		config_destroy(&sys_cfg);
		return FAIL;
	}
	memcpy(ownerbuf,selitem->name[0],p-selitem->name[0]);
	strcpy(verbuf,p+1);
	for(i=0; i<key_count; i++) {
		ele_root_setting=config_setting_get_elem(sys_root_setting,i);
		key_name=config_setting_name(ele_root_setting);
		if(key_name==NULL) {
			config_destroy(&sys_cfg);
			return FAIL;
		}
		child_root_setting=config_lookup(&sys_cfg,key_name);
		if(child_root_setting==NULL) {
			config_destroy(&sys_cfg);
			return FAIL;
		}
		if(CONFIG_FALSE==config_setting_lookup_string(child_root_setting,"owner",&owner)) {
			config_destroy(&sys_cfg);
			return FAIL;
		}
		if(CONFIG_FALSE==config_setting_lookup_string(child_root_setting,"ver",&ver)) {
			config_destroy(&sys_cfg);
			return FAIL;
		}
		if(strcmp(owner,ownerbuf)==0&&strcmp(ver,verbuf)==0) {
			file_name=config_setting_get_string(ele_root_setting);
			if(file_name==NULL) {
				config_destroy(&sys_cfg);
				return FAIL;
			}
			break;
		}

	}
	NDK_ScrClrs();
	if (g_Language == 0)
		NDK_ScrPrintf("导出后原有的私钥将被覆盖,任意键继续，取消键返回..\n");
	else
		NDK_ScrPrintf("The key will be covered by new one，any key to continue,Cancel to Esc..\n");
	NDK_KbGetCode(0,&key);
	if(key==ESC) {
		config_destroy(&sys_cfg);
		return -2;
	}
	iret=KeyDesEnc(file_name,"prikey_11.nk");
	if(iret==FAIL) {
		PDEBUG("%s,%d,KeyDesEnc FAIL\n",__FUNCTION__,__LINE__);
		config_destroy(&sys_cfg);
		return FAIL;
	}
	if ((nOutFileHandle = open("prikey_11.nk",O_RDWR)) < 0) {
		PDEBUG("%s,%d,open prikey_11.nk fail,iret=%d\n",__FUNCTION__,__LINE__,nOutFileHandle);
		config_destroy(&sys_cfg);
		return FAIL;
	}
	count=read(nOutFileHandle,buf,584);
	if(count!=584) {
		close(nOutFileHandle);
		config_destroy(&sys_cfg);
		return FAIL;
	}
	if(BakPsam_UpdateParam(buf,sizeof(buf))<0) {
		PDEBUG("%s,%d,BakPsam_UpdateParam err!!\n",__FUNCTION__,__LINE__);
		config_destroy(&sys_cfg);
		return FAIL;
	}
	remove("prikey_11.nk");
	config_destroy(&sys_cfg);
	return SUCC;
}

int SelectFunc(void)
{
	int nKey;

	NDK_ScrClrs();
	if (g_Language == 0)
		NDK_ScrPrintf("请选择备份私钥的外部设备:\n1.IC 卡\n2.SAM卡\n");
	else
		NDK_ScrPrintf("Select external devices to save PriKey:\n1.IC Card\n2.SAM Card\n");
	NDK_KbGetCode(0,&nKey);
	while(1) {
		if(nKey==ONE) {
			g_TypeIC=1;
			g_TypeSam=0;
			g_Sam=ICTYPE_IC;
			return 0;
		} else if(nKey==TWO) {
			g_TypeSam=1;
			g_TypeIC=0;
			NDK_ScrClrs();
			if (g_Language == 0)
				NDK_ScrPrintf("请选择SAM卡:\n1.SAM1\n2.SAM2\n");
			else
				NDK_ScrPrintf("Select Sam Card:\n1.SAM1\n2.SAM2\n");
			NDK_KbGetCode(0,&nKey);
			while(1) {
				if(ONE==nKey) {
					g_Sam=ICTYPE_SAM1;
					return 0;
				} else if(TWO==nKey) {
					g_Sam=ICTYPE_SAM2 ;
					return 0;
				} else if(ESC==nKey) {
					g_TypeSam=0;
					return -1;
				}
				NDK_KbGetCode(0,&nKey);
			}
		}
		else if(nKey==ESC) {
			return -1;
		}
		NDK_KbGetCode(0,&nKey);
	}
}

#define PRIVATE_DEC_TMP_FILE_IN		"/tmp/private_dec_tmp_in"
#define PRIVATE_DEC_TMP_FILE_OUT	"/tmp/private_dec_tmp_out"
/**
* @brief	使用KLDSERV自身的私钥进行解密，openssl命令示例：
* 			openssl rsautl -in cipher.txt -out plain.txt -inkey private.key -decrypt
* @param[in]	keyfile	--	用于解密的私钥文件路径
* @param[in]	inlen	--	加密数据长度
* @param[in]	in	--	加密数据指针
* @param[out]	out	--	解密输出数据指针
* @retval	<=0	--	失败
* 			>0	--	返回解密结果长度
*/
int xauth_private_encryption(char *keyfile, int inlen, char *in, char *out, int mode)
{
#if 1	/*使用openssl命令行实现*/
	int tmp_fd;
	struct stat fbuf;
	int ret;
	char cmd[512];

	tmp_fd = open(PRIVATE_DEC_TMP_FILE_IN, O_RDWR|O_CREAT|O_TRUNC, 0666);
	write(tmp_fd, in, inlen);
	close(tmp_fd);
	remove(PRIVATE_DEC_TMP_FILE_OUT);
	if (mode)	/*私钥签名*/
		sprintf(cmd, "openssl rsautl -sign -in %s -out %s -inkey %s",
				PRIVATE_DEC_TMP_FILE_IN,
				PRIVATE_DEC_TMP_FILE_OUT,
				keyfile);
	else		/*私钥RSA解密*/
		sprintf(cmd, "openssl rsautl -in %s -out %s -inkey %s -decrypt",
				PRIVATE_DEC_TMP_FILE_IN,
				PRIVATE_DEC_TMP_FILE_OUT,
				keyfile);
	ret = system(cmd);
	if (ret != 0) {
		ret = -1;
		goto priv_dec_exit;
	}
	tmp_fd = open(PRIVATE_DEC_TMP_FILE_OUT, O_RDONLY);
	fstat(tmp_fd, &fbuf);
	ret = read(tmp_fd, out, fbuf.st_size);
	close(tmp_fd);

priv_dec_exit:
	remove(PRIVATE_DEC_TMP_FILE_IN);
	remove(PRIVATE_DEC_TMP_FILE_OUT);
	return ret;
#else	/*后期改用openssl加解密C库编码实现*/
	return 0;
#endif
}

int SetPassword(int flag)
{
	unsigned int len;

	while(1) {
		len=0;
		NDK_ScrClrs();
		if(flag==0) {
			if (g_Language == 0)
				NDK_ScrPrintf("请输入先前设置的8位数字口令:\n");
			else
				NDK_ScrPrintf("Pls Input 8 Num Password which you have setted:\n");
		} else {
			if (g_Language == 0)
				NDK_ScrPrintf("请设置8位数字口令:\n");
			else
				NDK_ScrPrintf("Pls Set 8 Num Password:\n");
		}
		NDK_KbGetInput((char *)g_passBuf,8,8,&len,INPUTDISP_NORMAL,0,INPUT_CONTRL_LIMIT_ERETURN);
		PDEBUG("%s,%d,len=%d--------\n",__FUNCTION__,__LINE__,len);
		if(len==0)
			return FAIL;
		else {
			if(strstr((char *)g_passBuf,".")!=NULL) {
				MessagePrint("口令必须为数字","Password must be num",0);
				continue;
			}
		}
		break;
	}
	return SUCC;
}

int tmp_entry(void)
{
	char ch=0;
	int iRet,nCount;
	int i=0;
	R_RSA_PRIVATE_KEY prikey;
	PDEBUG("read to go\n");
	int nKey;

	if(FAIL==init())
		return FAIL;
keynum:
	NDK_ScrClrs();
	if (g_Language == 0)
		NDK_ScrPrintf("1.签名\n2.生成公私钥\n3.私钥导入\n4.私钥导出\n5.下载私钥\n");
	else
		NDK_ScrPrintf("1.Hash Sign\n2.Cert Sign\n3.About Me\n4.PriKey Output\n5.CSR Sign\n");
		NDK_KbGetCode(0,&nKey);
	switch (nKey)
	{
		case TWO:
			if (-1 == SelectFunc())
				goto keynum;
			iRet = IsSamICReady();
			if (iRet == FAIL)
				goto keynum;
			iRet = SetPassword(1);
			if (iRet == SUCC) {
				MessagePrint("设置口令成功\n", "Set Password Succ\n", 0);
			} else {
				MessagePrint("设置口令失败\n", "Set Password Fail\n", 0);
				goto keynum;
			}
			break;
		case THREE:
			if (-1 == SelectFunc())
				goto keynum;
			iRet = PriKeyInput();
			if (iRet == FAIL || iRet == -2) {
				remove("prikey_11.nk");
				NDK_SysTimeBeep(2500, 250);
				NDK_SysMsDelay(100);
				NDK_SysTimeBeep(2500, 250);
				MessagePrint("私钥导入失败\n", "PriKey Input Fail\n", 0);
				goto keynum;
			} else {
				NDK_SysTimeBeep(2500, 500);
				MessagePrint("私钥导入成功\n", "PriKey Input Succ\n", 0);
				goto keynum;
			}
		case FOUR:
			if (-1 == SelectFunc())
				goto keynum;
			iRet = PriKeyOutput();
			if (iRet == FAIL || iRet == -2) {
				remove("prikey_11.nk");
				NDK_SysTimeBeep(2500, 250);
				NDK_SysMsDelay(100);
				NDK_SysTimeBeep(2500, 250);
				MessagePrint("私钥导出失败\n", "PriKey Output Fail\n", 0);
				goto keynum;
			} else {
				NDK_SysTimeBeep(2500, 500);
				MessagePrint("私钥导出成功\n", "PriKey Output Succ\n", 0);
				goto keynum;
			}
		case ONE:
			/*iRet = SumSignature(&prikey);*/
			/*if (FAIL == iRet || iRet == -2) {*/
				/*MessagePrint("签名失败\n", "Signature Fail\n", 0);*/
				/*goto keynum;*/
			/*} else {*/
				/*break;*/
			/*}*/
			break;
		case FIVE:
			break;
		case K_ESC:
			return SUCC;
		default:
			goto keynum;
			break;
	}

	DetectedPortType = PORT_NUM_COM2;
	SetDownloadPortType(DetectedPortType);//初始化通讯
	iRet = dl_initdownloadport();
	/*CommInitConfig();*/
	while(1) {
		iRet=TimeOutProcess();
		if(FAIL==iRet)
			return FAIL;
		else if(-2==iRet) {
			Auxautodetect=1;
			goto keynum;
		}
		HandShake();
		NDK_KbHit(&nKey);
		if ( nKey == ESC) {
			dl_portexit();
			return FAIL;
		}
		nCount = dl_portread(1, &ch, 100);
		if(nCount!=1) {
			i++;
			if(i>4) {
				if(FAIL==TimeOutProcess()) {
					dl_portexit();
					return FAIL;
				}
			}
		} else {
			i=0;
			if(0x07==ch) {
				iRet=PriKeyDownload(&prikey);
				if(iRet==2) {
					dl_portexit();
					Auxautodetect=1;
					goto keynum;
					/*return SUCC;*/
				} else if(FAIL==iRet) {
					dl_portexit();
					Auxautodetect=1;
					goto keynum;
					/*return FAIL;*/
				}
			}
		}
	}
}

