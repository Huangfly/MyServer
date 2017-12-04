#ifndef _CBACKSERVER_H_
#define _CBACKSERVER_H_

#include "../CShareMem/CShareMem.h"
#include "../CThread/CThreadPool.h"
#include "../CPacket/packet.h"
#include "./CUnpackTask.h"

class CBackServer
{
public:
	CBackServer();
	~CBackServer();
	void Exec();
private:
	CThreadPool *busctl_pool;
};

#endif