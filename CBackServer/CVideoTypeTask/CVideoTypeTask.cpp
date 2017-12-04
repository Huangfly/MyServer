#include "./CVideoTypeTask.h"

extern CShareMem shm_ack;
extern CLog server_log;

int GetType_callback(void *pData,int col,char **val,char **colname)
{
	list<A_TYPE*> *type = (list<A_TYPE*>*)pData;
	A_TYPE *addType = new A_TYPE;
	
	addType->channel_id = atoi(val[0]);
	addType->type_id = atoi(val[1]);
	strcpy(addType->name,val[2]);
	
	type->push_front(addType);
	
	return 0;
}

CVideoTypeTask::CVideoTypeTask(int fd, P_HEAD *bus_head)
{
	memcpy(&(this->bus_head), bus_head, sizeof(P_HEAD));
	this->fd = fd;
}

void CVideoTypeTask::doAction()
{
	CPacketStream packet;
	int Size = 0;
	char ack_buf[1024] = {0};
	if (bus_head.msg_code == 0)//给压测发送应答
	{
		packet.Packet(ack_buf, &Size, PACK_TYPE, NULL, 0, bus_head.trans_id, bus_head.msg_code);
		shm_ack.Write(ack_buf, Size, fd);
		return;
	}

	//处理客户端的业务
	char type_pack[800] = {0};
	int type_Len = 0; 
	list<A_TYPE*> type;
	A_TYPE *pType;
	int count;
	
	type.clear();
	
	char sql[256] = {0};
	CDbCon *iDb;
	iDb = CDbCon::getInstance();
	
	sprintf(sql,"select channel_id,type_id,type_name from Tbl_video_type;");
	iDb->Get_Data(sql, GetType_callback, &type);
	sprintf(sql,"select COUNT(*) from Tbl_video_type;");
	iDb->Get_Data(sql, GetCount_callback, &count);
	
	for (; type.empty() != true;)
	{
		pType = type.front();
		pType->t_count = count;
		memcpy(type_pack + type_Len, pType, sizeof(A_TYPE));
		type_Len += sizeof(A_TYPE);
		type.pop_front();
		delete pType;
	}

	packet.Packet(ack_buf, &Size, PACK_TYPE, type_pack, type_Len, bus_head.trans_id, bus_head.msg_code);
	shm_ack.Write(ack_buf, Size, fd);
	server_log.Write_Log(PACK_TYPE, ack_buf, Size, (char*)"发送", 1);
}