#include "./CHostAddr/CHostAddr.h"
#include "./CThread/CThreadBase.h"
#include "./CPreServer/CPreServer.h"
#include "./CShareMem/CShareMem.h"
#include "./CBackServer/CBackServer.h"
#include <map>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include "./CLog/CLog.h"
/////////
//共享内存
#define SHMBUS_KEY 1110 //业务共享内存
#define SHMACK_KEY 1111 //应答共享内存
#define SEMBUS_KEY 2220
#define SEMACK_KEY 2222
#define SEMLOG_KEY 3333
//////////
//函数声明
void PreProcess();//前置服务器
void BackProcess();//后置服务器
//////////
//变量定义
CShareMem shm_bus(SHMBUS_KEY, SEMBUS_KEY, 50, 80);
CShareMem shm_ack(SHMACK_KEY, SEMACK_KEY, 50, 600);
CLog server_log(SEMLOG_KEY);
map<int,int> user_list;
map<int,int> connect_list;

int connect_Count = 0;
int rcv_Count = 0;
int ack_Count = 0;

int user_Count = 0;
int video_channel = 0;
int video_type = 0;
int video_region = 0;
int video_list = 0;
int play_data = 0;
int play_time = 0;

int log_fd;

void Catch_signal(int no)
{
}

int main()
{
	shm_bus.Create();
	shm_ack.Create();
	signal(SIGPIPE, Catch_signal);
	server_log.Create();

//	printf("%d\n",sizeof(P_VIDEO));

	pid_t pid;
	pid = fork();

	if (pid < 0)
	{
		perror("fork fail.");
	}
	else if(pid == 0)//子进程
	{
		PreProcess();
	}
	else
	{
		BackProcess();
	}

	return 0;
}


void PreProcess()
{
	CPreServer pre_server;
	pre_server.Exec();
}

void BackProcess()
{
	CBackServer back_server;
	back_server.Exec();
}