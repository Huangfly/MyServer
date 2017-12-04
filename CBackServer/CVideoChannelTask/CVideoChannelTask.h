#ifndef _CVIDEOCHANNELTASK_H_
#define _CVIDEOCHANNELTASK_H_

#include "../../CShareMem/CShareMem.h"
#include "../../CThread/CThreadPool.h"
#include "../../CPacket/packet.h"
#include "../../DbCon/DbCon.h"
#include "../../CLog/CLog.h"
#include <list>

class CVideoChannelTask:public CTask
{
public:
	CVideoChannelTask(int fd, P_HEAD *bus_head);
	void doAction();
private:
	int fd;
	P_HEAD bus_head;
};


#endif