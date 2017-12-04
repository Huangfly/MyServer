#ifndef _CVIDEOREGIONTASK_H_
#define _CVIDEOREGIONTASK_H_

#include "../../CShareMem/CShareMem.h"
#include "../../CThread/CThreadPool.h"
#include "../../CPacket/packet.h"
#include "../../DbCon/DbCon.h"
#include "../../CLog/CLog.h"
#include <list>


class CVideoRegionTask:public CTask
{
public:
	CVideoRegionTask(int fd, P_HEAD *bus_head);
	void doAction();
private:
	int fd;
	P_HEAD bus_head;
};


#endif