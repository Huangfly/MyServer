#include "./CPlayTimeTask.h"

extern CShareMem shm_ack;
extern CLog server_log;

int GetOneRecord_callback(void *pData,int col,char **val,char **colname)
{
	A_PLAY *addPlay = (A_PLAY*)pData;
	
	addPlay->user_id = atoi(val[0]);
	addPlay->video_id = atoi(val[1]);
	strcpy(addPlay->time, val[2]);
	addPlay->play_times = atoi(val[3]);
	
	CDbCon *iDb;
	char sql[256] = {0};
	iDb = CDbCon::getInstance();
	
	sprintf(sql,"select video_name from Tbl_video_info where video_id=%d;",addPlay->video_id);
	iDb->Get_Data(sql, GetData_callback, addPlay->video_name);
	
	return 0;
}

CPlayTimeTask::CPlayTimeTask(int fd, P_HEAD *bus_head, char *buf, int Len)
:CTask()
{
	this->fd = fd;
	memcpy(&(this->bus_head), bus_head, sizeof(P_HEAD));
	if (Len == sizeof(P_PTIME))
	{
		memcpy(&(this->bus_pack), buf, Len);
	}
}

void CPlayTimeTask::doAction()
{
	char ack_buf[400] = {0};
	int Size = 0;
	CPacketStream packet;
	if (bus_head.msg_code == 0)
	{
		packet.Packet(ack_buf, &Size, PACK_VTIME, NULL, 0, 0, 0);
		shm_ack.Write(ack_buf, Size, fd);
		return;
	}
	CDbCon *iDb;
	char sql[256] = {0};
	iDb = CDbCon::getInstance();

	sprintf(sql,"update Tbl_record set play_times=%d where record_id=%d;"
		, bus_pack.end_time
		, bus_pack.record_id);
	iDb->Get_Data(sql, NULL, NULL);

	A_PLAY pPlay = {0};
	sprintf(sql,"select user_id,video_id,end_time,play_times from Tbl_record where record_id=%d;", bus_pack.record_id);
	iDb->Get_Data(sql, GetOneRecord_callback, &pPlay);
	packet.Packet(ack_buf, &Size, PACK_VTIME, &pPlay, sizeof(A_PLAY), bus_head.trans_id, bus_head.msg_code);
	shm_ack.Write(ack_buf, Size, fd);
	server_log.Write_Log(PACK_VTIME, ack_buf, Size, (char*)"·¢ËÍ", pPlay.user_id);
}
