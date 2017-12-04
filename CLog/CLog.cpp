#include "./CLog.h"

CLog::CLog(int sem_key)
:CStreamBase()
{
	write_sem = new CSem(1, sem_key);
}

CLog::~CLog()
{

}

void CLog::Create()
{
	char log_name[20] = {0};
	time_t now;
	struct tm *timenow;
	time(&now);
	timenow = localtime(&now);
	sprintf(log_name,"%d-%d-%d.log", timenow->tm_year + 1900, timenow->tm_mon, timenow->tm_mday);
	m_fd = open(log_name, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU | S_IRWXG | S_IRWXO);
	if (m_fd < 0)
	{
		perror("open log fail.");
		exit(1);
	}
	write_sem->Create();
	char buf[100] = {0};
	sprintf(buf, "\r\nʱ�䣺%04d-%02d-%02d %02d:%02d:%02d\r\n���ܣ�����������\r\n"
		, timenow->tm_year + 1900
		, timenow->tm_mon
		, timenow->tm_mday
		, timenow->tm_hour
		, timenow->tm_min
		, timenow->tm_sec);
	Write(buf, strlen(buf));
}

void CLog::Write_Log(int funcId,char *buf, int Len, char *type, int Id)
{
	char write_buf[2048] = {0};
	char fun_name[20] = {0};
	//�ȴ���һ��д��,��ȡ��Դ
	write_sem->SemOp(-1);
	//д��ʱ��͹���
	time_t now;
	struct tm *timenow;
	time(&now);
	timenow = localtime(&now);
	switch(funcId)
	{
	case PACK_LOGIN:
		strcpy(fun_name, "��¼");
		break;
	case PACK_CHANNEL:
		strcpy(fun_name, "��ȡƵ����Ϣ");
		break;
	case PACK_TYPE:
		strcpy(fun_name, "��ȡ������Ϣ");
		break;
	case PACK_REGION:
		strcpy(fun_name, "��ȡ������Ϣ");
		break;
	case PACK_VIDEO:
		strcpy(fun_name, "��ȡ��Ƶ��Ϣ");
		break;
	case PACK_VPLAY:
		strcpy(fun_name, "�ϴ����ż�¼");
		break;
	case PACK_VTIME:
		strcpy(fun_name, "�ϴ�����ʱ��");
		break;
	default:
		break;
	}
	sprintf(write_buf, "\r\nʱ�䣺%04d-%02d-%02d %02d:%02d:%02d\r\n���ܣ�%s\r\n"
		, timenow->tm_year + 1900
		, timenow->tm_mon
		, timenow->tm_mday
		, timenow->tm_hour
		, timenow->tm_min
		, timenow->tm_sec
		, fun_name);
	//д�����ͺ��û�ID
	sprintf(write_buf, "%s���ͣ�%s\r\n�û�Id��%04d\r\n", write_buf, type, Id);
	//д�����ݰ�
	for (int i = 1; i <= Len; i++)
	{
		
		if (i%16 == 0)
		{
			sprintf(write_buf, "%s %02x\r\n", write_buf, (unsigned char)(*buf));
		}
		else
		{
			sprintf(write_buf, "%s %02x", write_buf, (unsigned char)(*buf));
		}
		buf++;
	}
	sprintf(write_buf, "%s\r\n", write_buf);
	//д������
	Write(write_buf, strlen(write_buf));
	//�ͷ���Դ
	write_sem->SemOp(+1);
}