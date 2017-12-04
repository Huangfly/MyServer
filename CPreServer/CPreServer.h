#ifndef _CPRESERVER_H_
#define _CPRESERVER_H_

#include "../CShareMem/CShareMem.h"
#include "../CThread/CThreadBase.h"
#include "../CEpoll/CServerEpoll.h"
#include "../CEpoll/CClientEpoll.h"

class CPrintThread:public CThreadBase
{
public:
	CPrintThread(CClientEpoll *client_epoll);
	void Run();
private:
	CClientEpoll *client_epoll;
};

class CRcvAckThread:public CThreadBase
{
public:
	CRcvAckThread();
	void Run();
private:
	CThreadPool *sendack_poll;
};


class CClientEpollThread:public CThreadBase
{
public:
	CClientEpollThread(CClientEpoll *client_epoll);
	void Run();
private:
	CClientEpoll *client_epoll;
};

class CSendPackTask:public CTask
{
public:
	CSendPackTask(char *buf, int Len, int fd, P_HEAD *ack_head);
	~CSendPackTask();
	void doAction();
private:
	char *buf;
	int Len;
	int fd;
	P_HEAD ack_head;
};

class CPreServer
{
public:
	CPreServer();
	~CPreServer();
	void Exec();
private:

};

#endif