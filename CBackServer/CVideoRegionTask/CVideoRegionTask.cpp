#include "./CVideoRegionTask.h"

extern CShareMem shm_ack;
extern CLog server_log;

int GetRegion_callback(void *pData,int col,char **val,char **colname)
{
	list<A_REGION*> *region = (list<A_REGION*>*)pData;
	A_REGION *addRegion = new A_REGION;
	
	addRegion->channel_id = atoi(val[0]);
	addRegion->region_id = atoi(val[1]);
	strcpy(addRegion->name,val[2]);
	
	
	region->push_front(addRegion);
	return 0;
}

CVideoRegionTask::CVideoRegionTask(int fd, P_HEAD *bus_head)
{
	memcpy(&(this->bus_head), bus_head, sizeof(P_HEAD));
	this->fd = fd;
}

void CVideoRegionTask::doAction()
{
	CPacketStream packet;
	int Size = 0;
	char ack_buf[800] = {0};
	if (bus_head.msg_code == 0)//给压测发送应答
	{
		packet.Packet(ack_buf, &Size, PACK_REGION, NULL, 0, bus_head.trans_id, bus_head.msg_code);
		shm_ack.Write(ack_buf, Size, fd);
		return;
	}

	//处理客户端的业务
	char region_pack[800] = {0};
	int region_Len = 0;
	list<A_REGION*> region;
	A_REGION *pRegion;
	int count;
	
	region.clear();
	
	char sql[256] = {0};
	CDbCon *iDb;
	iDb = CDbCon::getInstance();
	
	sprintf(sql,"select channel_id,region_id,region_name from Tbl_video_region;");
	iDb->Get_Data(sql, GetRegion_callback, &region);
	sprintf(sql,"select COUNT(*) from Tbl_video_region;");
	iDb->Get_Data(sql, GetCount_callback, &count);
	
	for (; region.empty() != true;)
	{
		pRegion = region.front();
		pRegion->t_count = count;	
		memcpy(region_pack + region_Len, pRegion, sizeof(A_REGION));
		region_Len += sizeof(A_REGION);
		region.pop_front();
		delete pRegion;
	}

	packet.Packet(ack_buf, &Size, PACK_REGION, region_pack, region_Len, bus_head.trans_id, bus_head.msg_code);
	shm_ack.Write(ack_buf, Size, fd);
	server_log.Write_Log(PACK_REGION, ack_buf, Size, (char*)"发送", 1);
}