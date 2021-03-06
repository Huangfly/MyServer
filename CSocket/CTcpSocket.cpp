#include "./CTcpSocket.h"

//TCP套接字的默认构造函数
CTcpSocket::CTcpSocket()
:CSocket(true, AF_INET, 0)
{
	m_remote_addr = NULL;
}

//TCP套接字的拷贝构造函数
CTcpSocket::CTcpSocket(const CTcpSocket &other)
:CSocket(true, AF_INET, 0)
{
	this->m_fd = other.getFd();
	this->m_stream.setFd(this->m_fd);
	this->m_remote_addr = other.getRemoteAddr();
}

//TCP套接字的析构函数
CTcpSocket::~CTcpSocket()
{
	
}

//重载赋值运算符
CTcpSocket& CTcpSocket::operator =(const CTcpSocket &other)
{
	this->m_fd = other.getFd();
	this->m_stream.setFd(m_fd);
	m_remote_addr = other.getRemoteAddr();
	return *this;
}

CHostAddr* CTcpSocket::getRemoteAddr() const
{
	return m_remote_addr;
}

void CTcpSocket::setRemoteAddr(CHostAddr *remote_addr)
{
	m_remote_addr = remote_addr;
}

int CTcpSocket::Read(char *buf, const int buf_len)
{
	return m_stream.Read(buf, buf_len);
}

int CTcpSocket::Read(char *buf, const int buf_len, int timeout)
{
	return m_stream.Read(buf, buf_len, timeout);
}

int CTcpSocket::Write(char *buf, const int buf_len)
{
	return m_stream.Write(buf, buf_len);
}
