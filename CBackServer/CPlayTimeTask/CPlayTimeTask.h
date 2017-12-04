#ifndef _CPLAYTIMRTASK_H_
#define _CPLAYTIMRTASK_H_

#include "../../CShareMem/CShareMem.h"
#include "../../CThread/CThreadPool.h"
#include "../../CPacket/packet.h"
#include "../../DbCon/DbCon.h"
#include "../../CLog/CLog.h"
#include <list>

class CPlayTimeTask:public CTask
{
public:
	CPlayTimeTask(int fd, P_HEAD *bus_head, char *buf, int Len);
	void doAction();
private:
	int fd;
	P_HEAD bus_head;
	P_PTIME bus_pack;
};


#endif