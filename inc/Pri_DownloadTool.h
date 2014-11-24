#ifndef __DownLoadWANG_H__
#define __DownLoadWANG_H__

int Prompt(char *s, int nAttr, int nSeconds);
void DispMsg_exit(char *s);
void WriteDownloadCommand(char cCmd);
int RecOneFrame(int len, char *buf, int time);
int RecOneFrameWithRepeat(int len, char *buf, int time);
int insertprotocol(unsigned char *pbuf, unsigned long len);
int SendFrameWithRepeat(char *sendbuf, int len);
int SetDownloadPortType(int porttype);
int GetDownloadPortType(void);
int dl_initdownloadport(void);
int dl_portread(int len,char *OutBuf,int seconds);
int dl_portwrite(int len,const char *InBuf);
int dl_clrportbuf(int rxtx);
void dl_portexit(void);
int SelectDownloadPort(int nSeconds) ;
void NormalShow(char *szChinese, char *szEnglish, int nSeconds);
#endif
