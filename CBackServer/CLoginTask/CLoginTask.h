#ifndef _CLOGINTASK_H_
#define _CLOGINTASK_H_

#include "../../CShareMem/CShareMem.h"
#include "../../CThread/CThreadPool.h"
#include "../../CPacket/packet.h"
#include "../../DbCon/DbCon.h"
#include "../../CLog/CLog.h"
#include <map>
#include <string>
#include <iostream>
using namespace std;

typedef map<string,int> MyType;
typedef struct t_user_list 
{
	int user_id;
	string psw;
}T_USER;

class CLoginTask:public CTask
{
public:
	CLoginTask(char *login, int Len, int fd, P_HEAD *bus_head);
	~CLoginTask();
	void doAction();
private:
	P_HEAD bus_head;
	P_LOGIN login;
	int Len;
	int fd;
};

#endif