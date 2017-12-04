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
	int val;//�ź����ĳ�ʼֵ
	int sem_id;
	key_t sem_key;
};

class CShareMem
{
public:
	CShareMem(int shm_key, int sem_key, int nBlockCount = 10, int BlockSize = 200);
	~CShareMem();
	void Create();
	//int GetEmpty();//��ȡ���е����ݿ�
	void Write(char *buf, int Len, int fd);//�����ݿ�д������
	void Read(char *buf, int *Len, int *fd, P_HEAD *head);
private:
	int shm_id;
	int shm_key;
	int size;
	char *pBase;//����ַ
	int BlockSize;//һ�����ݿ�Ĵ�С
	int nBlockCount;//���ݿ������
	//////////////
	//��Ϣ���У�������ݺ������һ�����̻�ȡ
	//int msg_id;
	//int msg_key;
	/////////////////
	//�ź���,��Դ����Ϊ���ݿ�����
	int sem_id;
	int sem_key;
	CSem *empty_sem;//������Դ�ź���
	CSem *full_sem;//�ɶ���Դ�ź���
};

#endif