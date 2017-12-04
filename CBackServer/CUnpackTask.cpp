#include "./CUnpackTask.h"

CUnpackTask::CUnpackTask(char *bus_buf, int Len, int fd, CThreadPool *busctl_pool)
:CTask()
{
	this->buf = new char[Len];
	this->Len = Len;
	memcpy(buf, bus_buf, Len);
	this->busctl_pool = busctl_pool;
	this->fd = fd;
}

CUnpackTask::~CUnpackTask()
{
	delete []buf;
}

void CUnpackTask::doAction()
{
	P_HEAD head = {0};

	memcpy(&head, buf, sizeof(P_HEAD));
	switch(head.funcId)
	{
	case PACK_LOGIN:
		{
			busctl_pool->addTask(new CLoginTask(buf + sizeof(P_HEAD), Len - sizeof(P_HEAD), fd, &head));
		}
		break;
	case PACK_CHANNEL:
		{
			busctl_pool->addTask(new CVideoChannelTask(fd, &head));
		}
		break;
	case PACK_TYPE:
		{
			busctl_pool->addTask(new CVideoTypeTask(fd, &head));
		}
		break;
	case PACK_REGION:
		{
			busctl_pool->addTask(new CVideoRegionTask(fd, &head));
		}
		break;
	case PACK_VIDEO:
		{
			busctl_pool->addTask(new CVideoListTask(buf + sizeof(P_HEAD), Len - sizeof(P_HEAD), fd, &head));
		}
		break;
	case PACK_VPLAY:
		{
			busctl_pool->addTask(new CPlayTask(fd, &head, buf + sizeof(P_HEAD), Len - sizeof(P_HEAD)));
		}
		break;
	case PACK_VTIME:
		{
			busctl_pool->addTask(new CPlayTimeTask(fd, &head, buf + sizeof(P_HEAD), Len - sizeof(P_HEAD)));
		}
		break;
	default:
		break;
	}
}