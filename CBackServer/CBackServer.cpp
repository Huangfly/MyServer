#include "./CBackServer.h"

extern CShareMem shm_bus;

CBackServer::CBackServer()
{
	busctl_pool = new CThreadPool(10);
}

CBackServer::~CBackServer()
{

}

void CBackServer::Exec()
{
	char bus_pack[200] = {0};
	P_HEAD head = {0};
	int Len = 0;
	int fd;
	while (1)
	{
		shm_bus.Read(bus_pack, &Len, &fd, NULL);
		
		if (Len > 0)//读取到资源
		{
			busctl_pool->addTask(new CUnpackTask(bus_pack, Len, fd, busctl_pool));
			memset(bus_pack, 0, Len);
		}
	}
}