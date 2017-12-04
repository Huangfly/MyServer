#include "./CPlayTask.h"

extern CShareMem shm_ack;
extern CLog server_log;

int GetRecord_callback(void *pData,int col,char **val,char **colname)
{
	list<A_PLAY*> *play = (list<A_PLAY*>*)pData;
	A_PLAY *addPlay = new A_PLAY;

	addPlay->user_id = atoi(val[0]);
	addPlay->video_id = atoi(val[1]);
	strcpy(addPlay->time, val[2]);
	addPlay->play_times = atoi(val[3]);

	CDbCon *iDb;
	char sql[256] = {0};
	iDb = CDbCon::getInstance();

	sprintf(sql,"select video_name from Tbl_video_info where video_id=%d;",addPlay->video_id);
	iDb->Get_Data(sql, GetData_callback, addPlay->video_name);

	play->push_back(addPlay);
	
	return 0;
}

CPlayTask::CPlayTask(int fd, P_HEAD *bus_head, char *buf, int Len)
:CTask()
{
	this->fd = fd;
	memcpy(&(this->bus_head), bus_head, sizeof(P_HEAD));
	if (Len == sizeof(P_PLAY))
	{
		memcpy(&(this->bus_pack), buf, Len);
	}
}

void CPlayTask::doAction()
{
	char ack_buf[800] = {0};
	int Size = 0;
	CPacketStream packet;

	//处理压测的请求包
	if (bus_head.msg_code == 0)
	{
		packet.Packet(ack_buf, &Size, PACK_VPLAY, NULL, 0, 0, 0);
		shm_ack.Write(ack_buf, Size, fd);
		return;
	}
	
	CDbCon *iDb;
	char sql[256] = {0};
	iDb = CDbCon::getInstance();

	//处理客户端的历史播放记录请求
	if (bus_pack.video_id == -1)
	{
		list<A_PLAY*> play;
		A_PLAY *pPlay;
		char pack_buf[200] = {0};
		int play_Len = 0;
		play.clear();
		sprintf(sql,"select user_id,video_id,end_time,play_times from Tbl_record where user_id=%d order by record_id desc limit 3;"
			, bus_pack.user_id);
		iDb->Get_Data(sql, GetRecord_callback, &play);

		for (; play.empty() != true;)
		{
			pPlay = play.front();
			memcpy(pack_buf + play_Len, pPlay, sizeof(A_PLAY));
			play_Len += sizeof(A_PLAY);
			play.pop_front();
			delete pPlay;
		}
		packet.Packet(ack_buf, &Size, PACK_VPLAY, pack_buf, play_Len, bus_head.trans_id, bus_head.msg_code);
		shm_ack.Write(ack_buf, Size, fd);
		return;
	}

	time_t now;
	struct tm *timenow;
	char time_buf[23] = {0};
	time(&now);
	timenow = localtime(&now);
	sprintf(time_buf, "%04d-%02d-%02d %02d:%02d:%02d"
		, timenow->tm_year + 1900
		, timenow->tm_mon
		, timenow->tm_mday
		, timenow->tm_hour
		, timenow->tm_min
		, timenow->tm_sec);

	int record_id = 0;
	int play_times = 0;
	

	//获取播放次数
	sprintf(sql,"select play_times from Tbl_video_info where video_id=%d;", bus_pack.video_id);
	iDb->Get_Data(sql, GetCount_callback, &play_times);
	//播放次数+1
	play_times++;
	//修改视频表的播放次数
	sprintf(sql,"update Tbl_video_info set play_times=%d where video_id=%d;"
		, play_times
		, bus_pack.video_id);
	iDb->Get_Data(sql, NULL, NULL);
	//如果客户端没有登录，仅修改视频列表的播放次数，然后应答空包
	if (bus_pack.user_id == 0)
	{
		packet.Packet(ack_buf, &Size, PACK_VPLAY, NULL, 0, bus_head.trans_id, bus_head.msg_code);
		shm_ack.Write(ack_buf, Size, fd);
		return;
	}

	sprintf(sql,"select COUNT(*) from Tbl_record;");
	iDb->Get_Data(sql, GetCount_callback, &record_id);
	if (record_id == 0)
	{
		sprintf(sql,"INSERT INTO Tbl_record VALUES(1,%d,%d,0,'%s');"
			, bus_pack.user_id
			, bus_pack.video_id
			, time_buf);
	}
	else
	{
		sprintf(sql,"INSERT INTO Tbl_record VALUES(null,%d,%d,0,'%s');"
			, bus_pack.user_id
			, bus_pack.video_id
			, time_buf);
	}

	iDb->Get_Data(sql, NULL, NULL);
	
	//获取视频名称
	char video_name[20] = {0};
	sprintf(sql,"select video_name from Tbl_video_info where video_id=%d;", bus_pack.video_id);
	iDb->Get_Data(sql, GetData_callback, video_name);
	//压包
	A_PLAY pack_play = {0};
	pack_play.record_id = record_id;
	pack_play.user_id = bus_pack.user_id;
	pack_play.video_id = bus_pack.video_id;
	strcpy(pack_play.time, time_buf);
	strcpy(pack_play.video_name, video_name);
	packet.Packet(ack_buf, &Size, PACK_VPLAY, &pack_play, sizeof(A_PLAY), bus_head.trans_id, bus_head.msg_code);
	shm_ack.Write(ack_buf, Size, fd);
	//写日志
	server_log.Write_Log(PACK_VPLAY, ack_buf, Size, (char*)"发送", bus_pack.user_id);
}