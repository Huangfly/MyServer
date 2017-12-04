#include "./CPreServer.h"

extern CShareMem shm_bus;
extern CShareMem shm_ack;
extern map<int,int> user_list;
extern map<int,int> connect_list;

extern int connect_Count;
extern int rcv_Count;
extern int ack_Count;

extern int user_Count;
extern int video_channel;
extern int video_type;
extern int video_region;
extern int video_list;
extern int play_data;
extern int play_time;

CClientEpollThread::CClientEpollThread(CClientEpoll *client_epoll)
:CThreadBase()
{
	this->client_epoll = client_epoll;
}

//客户端监听线程
CPrintThread::CPrintThread(CClientEpoll *client_epoll)
{
		this->client_epoll = client_epoll;
}

//打印信息线程
void CPrintThread::Run()
{
	map<int,int>::iterator it;
	int time = 0;
	int connect_time = 0;
	while (1)
	{
		sleep(1);
		printf("=============================================================================\n");
		printf("有效连接数: %d\n", connect_Count);
		printf("接收数据包: %d\t\t发送数据包:%d\n", rcv_Count, ack_Count);
		printf("\n用户登录数: %d\n", user_Count);
		printf("获取视频频道: %d \t获取视频分类: %d \t获取视频地区: %d\n", video_channel, video_type,video_region);
		printf("获取视频列表: %d \t上传播放数据: %d \t上传播放时长: %d\n", video_list, play_data,play_time);
		printf("=============================================================================\n");
		
		//每隔1秒，每个登录的用户的值减1
		for (it = user_list.begin(); it != user_list.end(); it++)
		{
			it->second--;
		}
		for (it = connect_list.begin(); it != connect_list.end(); it++)
		{
			it->second--;
		}
		//每隔5秒，检测每个用户的值是否为5，不为5说明用户5秒内没收到心脏包
		if (time > 5)
		{
			for (it = user_list.begin(); it != user_list.end(); it++)
			{
				if (it->second <= 0)
				{
					client_epoll->DelEvent(it->first, EPOLLOUT);
					close(it->first);
					user_list.erase(it->first);
					connect_Count--;
					user_Count--;
				}
			}
			time = 0;
		}
		//每隔2分钟，未登陆的
		if (connect_time > 10)
		{
			for (it = connect_list.begin(); it != connect_list.end(); it++)
			{
				if (it->second <= 0)
				{
					client_epoll->DelEvent(it->first, EPOLLOUT);
					close(it->first);
					connect_list.erase(it->first);
					connect_Count--;
				}
			}
			connect_time = 0;
		}
		connect_time++;
		time++;
	}
}

//客户端监听线程
void CClientEpollThread::Run()
{
	client_epoll->Start(-1);
}

//发送应答包
CSendPackTask::CSendPackTask(char *buf, int Len, int fd, P_HEAD *ack_head)
:CTask()
{
	this->buf = new char[Len];
	memcpy(this->buf,buf,Len);
	this->Len = Len;
	this->fd = fd;
	memcpy(&(this->ack_head), ack_head, sizeof(P_HEAD));
}

CSendPackTask::~CSendPackTask()
{
	delete []buf;
}

void CSendPackTask::doAction()
{
	CStreamBase write_ack;
	map<int,int>::iterator it;
	int ctl = 0;
	write_ack.setFd(fd);
	ctl = write_ack.Write(buf, Len);
	ack_Count++;
	if(ctl > 0)
	{
		
		switch(ack_head.funcId)
		{
		case PACK_LOGIN:
			{
				A_LOGIN login_ret = {0};
				memcpy(&login_ret, buf + H_E_LEN + sizeof(P_HEAD), sizeof(A_LOGIN));
				if (login_ret.login_ret == 1 && user_list.find(fd) == user_list.end() && connect_list.find(fd) != connect_list.end())
				{
					connect_list.erase(fd);
					user_list.insert(pair<int, int>(fd, 5));
					user_Count++;
				}
			}
			break;
		case PACK_CHANNEL:
			video_channel++;
			break;
		case PACK_TYPE:
			video_type++;
			break;
		case PACK_REGION:
			video_region++;
			break;
		case PACK_VIDEO:
			video_list++;
			break;
		case PACK_VPLAY:
			play_data++;
			break;
		case PACK_VTIME:
			play_time++;
			break;
		default:
			break;
		}
	}
}

CRcvAckThread::CRcvAckThread()
{
	this->sendack_poll = new CThreadPool(20);
}

void CRcvAckThread::Run()
{
	char ack_buf[1200] = {0};
	int Len;
	int fd;
	
	P_HEAD head = {0};
	
	
	while (1)
	{
		shm_ack.Read(ack_buf, &Len, &fd, &head);
		if (Len > 10)
		{
			this->sendack_poll->addTask(new CSendPackTask(ack_buf, Len, fd, &head));
			Len = 0;
		}
	}
}

//前置服务器的构造函数
CPreServer::CPreServer()
{
	
}


CPreServer::~CPreServer()
{

}

void CPreServer::Exec()
{
	CHostAddr Server_addr((char*)"192.168.233.222", 8888);
	//创建一个CClientEpoll监听客户端的请求事件
	CClientEpoll client_epoll(10001);//最大监听1000哥客户端
	//创建一个CServerEpoll监听客户端的连接事件，将CClientEpoll传进去
	CServerEpoll server_epoll(&Server_addr, 1000, &client_epoll);

	char ip[20] = {0};
	int port = 0;
	bool ret;
	while (1)
	{
		printf("请输入IP地址：");
		scanf("%s", ip);
		int i = 0;
		char *pos = ip;
		while ((pos = strchr(pos, '.')) != NULL)
		{
			i++;
			pos++;
		}
		if (i != 3)
		{
			printf("IP格式错误，请重新输入！\n");
			continue;
		}
		printf("请输入端口号：");
		scanf("%d", &port);
		Server_addr.setIP(ip);
		Server_addr.setPort(port);
		ret = server_epoll.Connect();
		if (ret == true)
		{
			break;
		}
		else
		{
			printf("请重新输入！\n");
		}
	}
	//开一个线程用于CClientEpoll监听
	CClientEpollThread client_thread(&client_epoll);
	client_thread.Create();
	//打印线程
	CPrintThread printf_thread(&client_epoll);
	printf_thread.Create();
	//打开应答包监听线程
	CRcvAckThread rcvAck_Thread;
	rcvAck_Thread.Create();
	////////////////////////////////////
	//主线程
	//开始监听客户端的连接事件
	server_epoll.Start(-1);
}
