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

//�����̳߳�
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

//�����̳߳�
CThreadPool::~CThreadPool()
{
	//�˳��߳�
	this->isQuit = true;
	//��������б�
	pthread_mutex_lock(&m_mutex);
	threadlist.clear();
	//�������е��߳�
	pthread_cond_broadcast(&m_cond);
	//�ȴ������߳̽���
	pthread_cond_wait(&m_cond, &m_mutex);
	//����
	pthread_mutex_destroy(&m_mutex);
	pthread_cond_destroy(&m_cond);

	printf("delete.\n");
}

//�������
void CThreadPool::addTask(CTask *Task)
{
	int rlt;
	//��ס�����б���Դ���ȴ������̲߳����������б����������
	pthread_mutex_lock(&m_mutex);
	threadlist.push_back(Task);
	pthread_mutex_unlock(&m_mutex);

	//�ж��Ƿ��еȴ��߳�
	if (m_waitCount > 0)//�еȴ��߳�
	{
		//���ѵȴ���ĳһ��
		pthread_mutex_lock(&m_mutex);
		pthread_cond_signal(&m_cond);
		pthread_mutex_unlock(&m_mutex);
	}
	else
	{
		//�ж��Ƿ�������
		//����ִ�е��߳�С������߳���ʱ���ſ��Դ����µ��߳�
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
		//��ס�����б���������߳���ռ��������������ȴ������߳��ͷ���
		//
		//������ʱ�������̹߳��𣬲��ͷ������ȴ�����
		//������ʱ��������ȡ������Ȼ������������ִ������
		pthread_mutex_lock(&(threadpool->m_mutex));
		if (threadpool->threadlist.empty())//����Ϊ�գ�������
		{
			//�ͷ���������ȴ����ȴ����ѣ�ֱ�������б����������ʱ�Ż��ѣ���addTask���жϣ�
			threadpool->m_waitCount++;
			pthread_cond_wait(&(threadpool->m_cond), &(threadpool->m_mutex));
			pthread_mutex_unlock(&(threadpool->m_mutex));//wait�Ὣ���������ػ�ȥ��������Ҫ�������
			threadpool->m_waitCount--;
		}
		else
		{
			//��������൱�ڹ������Դ�����Զ����Ĳ���Ҫ�ڽ���֮ǰ
			//���Ƚ�������ȡ���������������б�ɾ��
			pTask = threadpool->threadlist.front();
			threadpool->threadlist.pop_front();
			//ִ������֮ǰ�������ͷŵ�����ִ��������������������
			pthread_mutex_unlock(&(threadpool->m_mutex));
			//ִ������
			pTask->doAction();
			delete pTask;
		}
	}
	//�߳̽���
	threadpool->m_nowCount--;//����ִ�е��߳�-1
	printf("task quit.\n");

	if (threadpool->m_nowCount <= 0)//ȫ���߳̽���
	{
		pthread_cond_signal(&(threadpool->m_cond));
	}
		
	pthread_exit(NULL);
}