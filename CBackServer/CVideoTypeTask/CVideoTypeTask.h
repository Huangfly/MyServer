#ifndef _CVIDEOTYPETASK_H_
#define _CVIDEOTYPETASK_H_

#include "../../CShareMem/CShareMem.h"
#include "../../CThread/CThreadPool.h"
#include "../../CPacket/packet.h"
#include "../../DbCon/DbCon.h"
#include "../../CLog/CLog.h"
#include <list>

class CVideoTypeTask:public CTask
{
public:
	CVideoTypeTask(int fd, P_HEAD *bus_head);
	void doAction();
private:
	int fd;
	P_HEAD bus_head;
};


#endif