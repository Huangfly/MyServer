#include "./CVideoListTask.h"

extern CShareMem shm_ack;
extern CLog server_log;

int GetVideo_callback(void *pData,int col,char **val,char **colname)
{
	list<A_VIDEO*> *video = (list<A_VIDEO*>*)pData;
	A_VIDEO *addVideo = new A_VIDEO;
	
	addVideo->video_id = atoi(val[0]);
	addVideo->channel_id = atoi(val[1]);
	addVideo->type_id = atoi(val[2]);
	addVideo->region_id = atoi(val[3]);
	strcpy(addVideo->name, val[4]);
	addVideo->playtimes = atoi(val[5]);
	if(strcmp(val[6],"Y") == 0)
	{
		addVideo->is_new = 1;
	}
	else
	{
		addVideo->is_new = 0;
	}
	
	video->push_front(addVideo);
	
	return 0;
}

CVideoListTask::CVideoListTask(char bus_buf[], int Len, int fd, P_HEAD *bus_head)
:CTask()
{
	memcpy(&(this->bus_head), bus_head, sizeof(P_HEAD));
	this->fd = fd;
	if (Len == sizeof(P_VIDEO))
	{
		memcpy(&pack_video, bus_buf, sizeof(P_VIDEO));
	}
	
}

void CVideoListTask::doAction()
{
	CPacketStream packet;
	int Size = 0;
	char ack_buf[800] = {0};
	if (bus_head.msg_code == 0)//给压测发送应答
	{
		packet.Packet(ack_buf, &Size, PACK_VIDEO, NULL, 0, bus_head.trans_id, bus_head.msg_code);
		shm_ack.Write(ack_buf, Size, fd);
		return;
	}

	//处理客户端的业务
	char pack[800] = {0};
	list<A_VIDEO*> video;
	A_VIDEO *pVideo;
	int count = 0;
	int Len = 0;
	
	char sql[256] = {0};
	char sql1[20] = {0};
	char sql2[20] = {0};
	char sql3[20] = {0};
	CDbCon *iDb;
	iDb = CDbCon::getInstance();

	video.clear();
	
	if (pack_video.channel_id != 0)
	{
		sprintf(sql1, "channel_id=%d and ", pack_video.channel_id);
	}
	if (pack_video.type_id != 0)
	{
		sprintf(sql2, "type_id=%d and ", pack_video.type_id);
	}
	if (pack_video.region_id != 0)
	{
		sprintf(sql3, "region_id=%d and", pack_video.region_id);
	}

	sprintf(sql,"select video_id,channel_id,type_id,region_id,video_name,play_times,online from Tbl_video_info where %s%s%s online='Y' limit 10 offset %d;"
		, sql1
		, sql2
		, sql3
		, pack_video.page * 10);
	iDb->Get_Data(sql, GetVideo_callback, &video);
	sprintf(sql,"select COUNT(*) from Tbl_video_info where %s%s%s online='Y';"
		, sql1
		, sql2
		, sql3);
	iDb->Get_Data(sql, GetCount_callback, &count);

	for (; video.empty() != true;)
	{
		pVideo = video.front();
		pVideo->count = count;
		memcpy(pack + Len, pVideo, sizeof(A_VIDEO));
		Len += sizeof(A_VIDEO);
		video.pop_front();
		delete pVideo;
	}

	packet.Packet(ack_buf, &Size, PACK_VIDEO, pack, Len, 0, 0);
	shm_ack.Write(ack_buf, Size, fd);
	server_log.Write_Log(PACK_VIDEO, ack_buf, Size, (char*)"发送", 1);
}
