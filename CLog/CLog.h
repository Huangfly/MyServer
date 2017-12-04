#ifndef _CLOG_H_
#define _CLOG_H_

#include "../CStreamBase/CStreamBase.h"
#include "../CShareMem/CShareMem.h"
#include "../CPacket/packet.h"
#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

class CLog:public CStreamBase
{
public:
	CLog(int sem_key);
	~CLog();
	void Create();
	void Write_Log(int funcId,char *buf, int Len, char *type, int Id);
private:
	CSem *write_sem;
};

#endif