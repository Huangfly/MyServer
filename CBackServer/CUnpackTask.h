#ifndef _CUNPACKTASK_H_
#define _CUNPACKTASK_H_

#include "../CShareMem/CShareMem.h"
#include "../CThread/CThreadPool.h"
#include "../CPacket/packet.h"
//////////////////////////////
//业务包处理头文件
#include "./CLoginTask/CLoginTask.h"
#include "./CVideoChannelTask/CVideoChannelTask.h"
#include "./CVideoRegionTask/CVideoRegionTask.h"
#include "./CVideoTypeTask/CVideoTypeTask.h"
#include "./CVideoListTask/CVideoListTask.h"
#include "./CPlayTask/CPlayTask.h"
#include "./CPlayTimeTask/CPlayTimeTask.h"

class CUnpackTask:public CTask
{
public:
	CUnpackTask(char *bus_buf, int Len, int fd, CThreadPool *busctl_pool);
	~CUnpackTask();
	void doAction();
private:
	char *buf;
	int Len;
	int fd;
	CThreadPool *busctl_pool;
};

#endif