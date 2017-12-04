#include "./CStreamBase.h"

//默认构造函数
CStreamBase::CStreamBase()
{
	m_fd = -1;
}

//传参初始化
CStreamBase::CStreamBase(int fd)
{
	m_fd = fd;
}

//读写流析构函数
CStreamBase::~CStreamBase()
{

}

//设置文件描述符
void CStreamBase::setFd(int fd)
{
	m_fd = fd;
}

//获取文件描述符
int CStreamBase::getFd() const
{
	return m_fd;
}

//读文件，堵塞模式
int CStreamBase::Read(char *buf, const int buf_len)
{
	int nCount;
	nCount = read(m_fd, buf, buf_len);
	if (nCount == -1)
	{
		perror("read fail.");
//		exit(1);
	}

	return nCount;
}

//读文件，带时间
int CStreamBase::Read(char *buf, const int buf_len, int timeout)
{
	fd_set readset;
	struct timeval iTime = {0};
	int nEvent;
	FD_ZERO(&readset);
	FD_SET(m_fd, &readset);

	iTime.tv_sec = timeout;
	iTime.tv_usec = 0;
	nEvent = select(m_fd + 1, &readset, NULL, NULL, &iTime);

	switch(nEvent)
	{
	case -1:
		{
			perror("select fail");
			exit(1);
			return -1;
		}
		break;
	case 0:
		{
			printf("time out.\n");
			return 0;
		}
		break;
	default:
		{
			return read(m_fd, buf, buf_len);
		}
		break;
	}
}

//读文件，带地址
int CStreamBase::Read(char *buf, const int buf_len, CHostAddr &remote_addr)
{
	int nCount;
	nCount = recvfrom(m_fd, buf, buf_len, 0, remote_addr.getAddr(), remote_addr.getSizePtr());
	if (nCount == -1)
	{
		perror("read fail.");
		exit(1);
	}
	
	return nCount;
}

//读文件，带地址，带时间
int CStreamBase::Read(char *buf, const int buf_len, CHostAddr &remote_addr, int timeout)
{
	fd_set readset;
	struct timeval iTime = {0};
	int nEvent;
	FD_ZERO(&readset);
	FD_SET(m_fd, &readset);
	
	iTime.tv_sec = timeout;
	iTime.tv_usec = 0;
	nEvent = select(m_fd + 1, &readset, NULL, NULL, &iTime);
	
	switch(nEvent)
	{
	case -1:
		{
			perror("select fail");
			exit(1);
			return -1;
		}
		break;
	case 0:
		{
			printf("time out.\n");
			return 0;
		}
		break;
	default:
		{
			return recvfrom(m_fd, buf, buf_len, 0, remote_addr.getAddr(), remote_addr.getSizePtr());
		}
		break;
	}
}

//写文件，堵塞模式
int CStreamBase::Write(const char *buf, const int buf_len)
{
	int nCount;
	nCount = write(m_fd, buf, buf_len);
	if (nCount == -1)
	{
//		perror("write fail.");
	}
	
	return nCount;
}

//写文件，带地址
int CStreamBase::Write(const char *buf, const int buf_len, CHostAddr remote_addr)
{
	int nCount;
	nCount = sendto(m_fd, buf, buf_len, 0, remote_addr.getAddr(), remote_addr.getSize());
	if (nCount == -1)
	{
//		perror("write fail.");
	}
	
	return nCount;
}
