#include "./CVideoChannelTask.h"

extern CShareMem shm_ack;
extern CLog server_log;

int GetChannel_callback(void *pData,int col,char **val,char **colname)
{
	list<A_CHANNEL*> *channel = (list<A_CHANNEL*>*)pData;
	A_CHANNEL *addChannel = new A_CHANNEL;

	addChannel->channel_id = atoi(val[0]);
	strcpy(addChannel->name,val[1]);

	channel->push_front(addChannel);

	return 0;
}

CVideoChannelTask::CVideoChannelTask(int fd, P_HEAD *bus_head)
:CTask()
{
	memcpy(&(this->bus_head), bus_head, sizeof(P_HEAD));
	this->fd = fd;
}

void CVideoChannelTask::doAction()
{
	CPacketStream packet;
	int Size = 0;
	char ack_buf[800] = {0};

	if (bus_head.msg_code == 0)//给压测发送应答
	{
		packet.Packet(ack_buf, &Size, PACK_CHANNEL, NULL, 0, bus_head.trans_id, bus_head.msg_code);
		shm_ack.Write(ack_buf, Size, fd);
		return;
	}

	//处理客户端的业务
	char channel_pack[400] = {0};
	int Len = 0;
	list<A_CHANNEL*> channel;
	A_CHANNEL *pChannel;
	int count;
	channel.clear();
	
	char sql[256] = {0};
	CDbCon *iDb;
	iDb = CDbCon::getInstance();
	
	sprintf(sql,"select channel_id,channel_name from Tbl_video_channel;");
	iDb->Get_Data(sql, GetChannel_callback, &channel);
	sprintf(sql,"select COUNT(*) from Tbl_video_channel;");
	iDb->Get_Data(sql, GetCount_callback, &count);
	
	for (; channel.empty() != true;)
	{
		pChannel = channel.front();
		pChannel->t_count = count;
		printf("name:%s\n",pChannel->name);
		memcpy(channel_pack + Len, pChannel, sizeof(A_CHANNEL));
		Len += sizeof(A_CHANNEL);
		channel.pop_front();
		delete pChannel;
	}
		
	packet.Packet(ack_buf, &Size, PACK_CHANNEL, channel_pack, Len, bus_head.trans_id, bus_head.msg_code);
	shm_ack.Write(ack_buf, Size, fd);
	server_log.Write_Log(PACK_CHANNEL, ack_buf, Size, (char*)"发送", 1);
}