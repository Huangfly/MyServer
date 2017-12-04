#include "./CLoginTask.h"

extern CShareMem shm_ack;
extern CLog server_log;
std::map<string, T_USER> user_buf;

int GetUser_callback(void *pData,int col,char **val,char **colname)
{
	T_USER user = {0};

	user.psw = (string)val[1];
	user.user_id = atoi(val[2]);

	user_buf.insert(pair<string, T_USER>((string)val[0],user));
	return 0;
}

CLoginTask::CLoginTask(char *login, int Len, int fd, P_HEAD *bus_head)
:CTask()
{
	if(Len == sizeof(P_LOGIN))
	{
		memcpy(&(this->login), login, Len);
	}
	memcpy(&(this->bus_head), bus_head, sizeof(P_HEAD));
	this->Len = Len;
	this->fd = fd;
}

CLoginTask::~CLoginTask()
{

}

void CLoginTask::doAction()
{
	CPacketStream packet;
	char buf[800] = {0};
	A_LOGIN login_ack = {0};
	int Size;
	string name;
	string psw;
	char id[10] = {""};
	map<string, T_USER>::iterator it;

	name = (string)login.name;
	psw = (string)login.pwd;

	if (Len != sizeof(P_LOGIN))
	{
		printf("name:%s\n",login.name);
		perror("Not P_LOGIN Pack.");
		return;
	}

	if (user_buf.empty() == true || bus_head.msg_code != 0)
	{
		char sql[256] = {0};
		CDbCon *iDb;
		iDb = CDbCon::getInstance();
		
		sprintf(sql,"select client_name,client_password,client_id from Tbl_client where client_stu='Y';");
		iDb->Get_Data(sql, GetUser_callback, NULL);
	}

	if ( (it = user_buf.find(name)) != user_buf.end())
	{
		if (it->second.psw == psw)
		{
			login_ack.user_id = it->second.user_id;
			login_ack.login_ret = 1;
			packet.Packet(buf, &Size, PACK_LOGIN, &login_ack, sizeof(A_LOGIN), bus_head.trans_id, bus_head.msg_code);
			shm_ack.Write(buf, Size, fd);
			if (bus_head.msg_code != 0)
			{
				server_log.Write_Log(PACK_LOGIN, buf, Size, (char*)"·¢ËÍ", 1);
			}
			return;
		}
	}		
	login_ack.login_ret = 0;
	packet.Packet(buf, &Size, PACK_LOGIN, &login_ack, sizeof(A_LOGIN), bus_head.trans_id, bus_head.msg_code);
	shm_ack.Write(buf, Size, fd);
	if (bus_head.msg_code != 0)
	{
		server_log.Write_Log(PACK_LOGIN, buf, Size, (char*)"·¢ËÍ", 1);
	}
}