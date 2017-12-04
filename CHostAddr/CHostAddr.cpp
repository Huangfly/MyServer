#include "./CHostAddr.h"

//默认构造函数，只初始化
CHostAddr::CHostAddr()
{
	iLen = sizeof(struct sockaddr);
	memset(&addr, 0, iLen);
}

CHostAddr::CHostAddr(const CHostAddr &other)
{
	iLen = sizeof(struct sockaddr);
	memset(&addr, 0, iLen);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(other.getIP());
	addr.sin_port = htons(other.getPort());
}

//传参构造函数，
CHostAddr::CHostAddr(char *ip, int port)
{
	iLen = sizeof(struct sockaddr);
	memset(&addr, 0, iLen);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);
}

CHostAddr::~CHostAddr()
{

}

//设置IP
void CHostAddr::setIP(char *ip)
{
	addr.sin_addr.s_addr = inet_addr(ip);
}

//设置端口号
void CHostAddr::setPort(int port)
{
	addr.sin_port = htons(port);
}

//获取IP
char* CHostAddr::getIP() const
{
	return inet_ntoa(addr.sin_addr);
}

//获取端口号
int CHostAddr::getPort() const
{
	return ntohs(addr.sin_port);
}

//获取地址长度
socklen_t CHostAddr::getSize() const
{
	return iLen;
}

//获取地址长度地址
socklen_t* CHostAddr::getSizePtr() const
{
	return (socklen_t*)&iLen;
}

struct sockaddr* CHostAddr::getAddr()
{
	return (struct sockaddr*)&addr;
}

struct sockaddr_in* CHostAddr::getInAddr()
{
	return &(this->addr);
}

CHostAddr& CHostAddr::operator =(const CHostAddr& other)
{
	iLen = sizeof(struct sockaddr);
	memset(&addr, 0, iLen);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(other.getIP());
	addr.sin_port = htons(other.getPort());

	return *this;
}