#include "./CShareMem.h"

//信号量的构造函数
CSem::CSem(int val, key_t sem_key)
{
	this->val = val;
	this->sem_key = sem_key;
}
//信号量的析构函数
CSem::~CSem()
{
	union semun value = {0};
	semctl(sem_id, 0, IPC_RMID, value);
}
//信号量的初始化
void CSem::Create()
{
	sem_id = semget(sem_key,0,0);
	if (sem_id == -1)
	{
		perror("semget not create.");
		sem_id = semget(sem_key, 1, IPC_CREAT | 0766);
	}
	
	union semun value = {0};
	value.val = val;
	semctl(sem_id, 0, SETVAL, value);
}
//信号量的PV操作
void CSem::SemOp(int op)
{
	struct sembuf sem_buf = {0};
	sem_buf.sem_num = 0;
	sem_buf.sem_op = op;
	sem_buf.sem_flg = 0;
	semop(sem_id, &sem_buf, 1);
//	union semun value = {0};
//	semctl(sem_id, 0, GETALL, value);
//	printf("id:%d  val:%d\n",sem_id, value.);
}

CShareMem::CShareMem(int shm_key, int sem_key, int nBlockCount /* = 10 */, int BlockSize /* = 200 */)
{
	this->shm_key = shm_key;
	this->nBlockCount = nBlockCount;
	this->BlockSize = BlockSize;
	this->shm_id = -1;
	this->sem_key = sem_key;
	this->empty_sem = new CSem(nBlockCount, sem_key);//空闲资源为nBlockCount
	this->full_sem = new CSem(0, sem_key+1);//可读资源为0
}

CShareMem::~CShareMem()
{
	shmdt(pBase);
	delete empty_sem;
	delete full_sem;
}


void CShareMem::Create()
{
	//开辟共享内存
	shm_id = shmget(shm_key, 0, 0);
	if (shm_id >= 0)
	{
		shmctl(shm_id, IPC_RMID, NULL);
	}
	shm_id = shmget(shm_key, nBlockCount * BlockSize, IPC_CREAT | 0766);
	pBase = (char*)shmat(shm_id, NULL, 0);
	///////////////////////////
	//SYSTEM V信号量,进程间同步
	//初始化信号量
	empty_sem->Create();
	full_sem->Create();
}

//将数据写入数据块
void CShareMem::Write(char *buf, int Len, int fd)
{
	if (Len > BlockSize)
	{
		printf("Len:%d\n",Len);
		perror("Len more Big with BlockSize.");
		exit(1);
	}

	//等待空闲资源,P操作-1
	empty_sem->SemOp(-1);

	//获取空闲的数据块位置，0空闲 -1正在写入 1资源存在
	int pos = 0;
	while (pos < (nBlockCount * BlockSize) && *(pBase + pos) != 0)//遍历找到空闲数据块
	{
		pos += BlockSize;
	}
	*(pBase + pos) = -1;//标志数据块
	//将数据写进数据块
	memcpy(pBase + pos + 1, &fd, sizeof(int));
	memcpy(pBase + pos + 1 + sizeof(int), &Len, sizeof(int));
	memcpy(pBase + pos + 1 + sizeof(int) * 2, buf, Len);

	//资源写入完毕
	*(pBase + pos) = 1;
	//可读资源+1
	full_sem->SemOp(+1);
}

//读取有资源的数据块
void CShareMem::Read(char *buf, int *Len, int *fd, P_HEAD *head)
{
	int val;
	//等待可读资源-1
	full_sem->SemOp(-1);
	//查找有资源的数据块
	int pos = 0;
	while (pos < (nBlockCount * BlockSize) && *(pBase + pos) != 1)
	{
		pos += BlockSize;
	}
	if (pos >= (nBlockCount * BlockSize))
	{
		return;
	}
	//获取数据
	memcpy(fd, pBase + pos + 1, sizeof(int));
	memcpy(Len, pBase + pos + sizeof(int) + 1, sizeof(int));
	memcpy(buf, pBase + pos + sizeof(int) * 2 + 1, *Len);
	if (head != NULL)
	{
		memcpy(head, buf + H_E_LEN, sizeof(P_HEAD));
	}
	
	//读取完毕,清空数据块
	memset(pBase + pos, 0, sizeof(int) * 2 + 1 + *Len);
	//释放一个空闲资源,V操作 +1
	empty_sem->SemOp(+1);
}