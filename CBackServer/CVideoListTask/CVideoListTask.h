#ifndef _CVIDEOLISTTASK_H_
#define _CVIDEOLISTTASK_H_

#include "../../CShareMem/CShareMem.h"
#include "../../CThread/CThreadPool.h"
#include "../../CPacket/packet.h"
#include "../../DbCon/DbCon.h"
#include "../../CLog/CLog.h"

class CVideoListTask:public CTask
{
public:
	CVideoListTask(char bus_buf[], int Len, int fd, P_HEAD *bus_head);
	void doAction();
private:
	int fd;
	P_VIDEO pack_video;
	P_HEAD bus_head;
};


#endif