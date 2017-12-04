#include "./CThreadPool.h"

CTask::CTask()
{

}

CTask::~CTask()
{

}

void CTask::doAction()
{

}

//创建线程池
CThreadPool::CThreadPool(int maxCount /* = 10 */)
{
	this->m_maxCount = maxCount;
	this->m_nowCount = 0;
	this->m_waitCount = 0;
	this->threadlist.clear();
	this->isQuit = false;

	pthread_mutex_init(&m_mutex, NULL);
	pthread_cond_init(&m_cond, NULL);
	pthread_cond_init(&end_cond, NULL);
}

//销毁线程池
CThreadPool::~CThreadPool()
{
	//退出线程
	this->isQuit = true;
	//清空任务列表
	pthread_mutex_lock(&m_mutex);
	threadlist.clear();
	//唤醒所有的线程
	pthread_cond_broadcast(&m_cond);
	//等待所有线程结束
	pthread_cond_wait(&m_cond, &m_mutex);
	//销毁
	pthread_mutex_destroy(&m_mutex);
	pthread_cond_destroy(&m_cond);

	printf("delete.\n");
}

//添加任务
void CThreadPool::addTask(CTask *Task)
{
	int rlt;
	//锁住任务列表资源，等待其他线程操作完任务列表再添加任务
	pthread_mutex_lock(&m_mutex);
	threadlist.push_back(Task);
	pthread_mutex_unlock(&m_mutex);

	//判断是否有等待线程
	if (m_waitCount > 0)//有等待线程
	{
		//唤醒等待的某一个
		pthread_mutex_lock(&m_mutex);
		pthread_cond_signal(&m_cond);
		pthread_mutex_unlock(&m_mutex);
	}
	else
	{
		//判断是否可以添加
		//正在执行的线程小于最大线程数时，才可以创建新的线程
		if (m_nowCount < m_maxCount)
		{
			rlt = pthread_create(&tid, NULL, runtine, this);
			if (rlt != 0)
			{
				printf("thread count:%d\n",this->m_nowCount);
				perror("pthread_create fail");
				exit(1);
			}
			m_nowCount++;
		}
	}
}

//
void* CThreadPool::runtine(void *pSelf)
{
	CTask *pTask;
	CThreadPool *threadpool;
	threadpool = (CThreadPool*)pSelf;

	pthread_detach(pthread_self());

	while (threadpool->isQuit != true)
	{
		//////////////////////////////
		//锁住任务列表，如果其他线程在占用锁，则堵塞，等待其他线程释放锁
		//
		//无任务时，将该线程挂起，并释放锁，等待唤醒
		//有任务时，将任务取出来，然后解锁，最后再执行任务
		pthread_mutex_lock(&(threadpool->m_mutex));
		if (threadpool->threadlist.empty())//链表为空，无任务
		{
			//释放锁，进入等待，等待唤醒，直到任务列表有任务添加时才唤醒（在addTask中判断）
			threadpool->m_waitCount++;
			pthread_cond_wait(&(threadpool->m_cond), &(threadpool->m_mutex));
			pthread_mutex_unlock(&(threadpool->m_mutex));//wait会将互斥锁返回回去，所以需要将锁解掉
			threadpool->m_waitCount--;
		}
		else
		{
			//任务队列相当于共享的资源，所以对它的操作要在解锁之前
			//将先进的任务取出来，并从任务列表删除
			pTask = threadpool->threadlist.front();
			threadpool->threadlist.pop_front();
			//执行任务之前，将锁释放掉，以执行任务队列里另外的任务
			pthread_mutex_unlock(&(threadpool->m_mutex));
			//执行任务
			pTask->doAction();
			delete pTask;
		}
	}
	//线程结束
	threadpool->m_nowCount--;//正在执行的线程-1
	printf("task quit.\n");

	if (threadpool->m_nowCount <= 0)//全部线程结束
	{
		pthread_cond_signal(&(threadpool->m_cond));
	}
		
	pthread_exit(NULL);
}