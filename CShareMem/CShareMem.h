#ifndef _CSHAREMEM_H_
#define _CSHAREMEM_H_

#include "../CPacket/packet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include <semaphore.h>
using namespace std;

union semun {
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
							 (Linux-specific) */
};

class CSem
{
public:
	CSem(int val, key_t sem_key);
	~CSem();
	void Create();
	void SemOp(int op);
private:
	int val;//信号量的初始值
	int sem_id;
	key_t sem_key;
};

class CShareMem
{
public:
	CShareMem(int shm_key, int sem_key, int nBlockCount = 10, int BlockSize = 200);
	~CShareMem();
	void Create();
	//int GetEmpty();//获取空闲的数据块
	void Write(char *buf, int Len, int fd);//往数据块写入数据
	void Read(char *buf, int *Len, int *fd, P_HEAD *head);
private:
	int shm_id;
	int shm_key;
	int size;
	char *pBase;//基地址
	int BlockSize;//一个数据块的大小
	int nBlockCount;//数据块的总数
	//////////////
	//消息队列，存放数据后告诉另一个进程获取
	//int msg_id;
	//int msg_key;
	/////////////////
	//信号量,资源个数为数据块总数
	int sem_id;
	int sem_key;
	CSem *empty_sem;//空闲资源信号量
	CSem *full_sem;//可读资源信号量
};

#endif