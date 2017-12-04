#ifndef _CPLAYTASK_H_
#define _CPLAYTASK_H_

#include "../../CShareMem/CShareMem.h"
#include "../../CThread/CThreadPool.h"
#include "../../CPacket/packet.h"
#include "../../DbCon/DbCon.h"
#include "../../CLog/CLog.h"
#include <list>


class CPlayTask:public CTask
{
public:
	CPlayTask(int fd, P_HEAD *bus_head, char *buf, int Len);
	void doAction();
private:
	int fd;
	P_HEAD bus_head;
	P_PLAY bus_pack;
};

#endif