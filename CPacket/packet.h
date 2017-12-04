#ifndef _PACKET_H_
#define _PACKET_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEAD_CHR 0x04
#define END_CHR  0x05
#define H_E_LEN 2

// #define HEAD_CHR '$'
// #define END_CHR  '#'
// #define H_E_LEN 1

///////////////////////////////////////
//功能号宏定义
#define PACK_HEARD		0 //心跳包
#define PACK_LOGIN		1 //登录包
#define PACK_CHANNEL	2 //频道包
#define PACK_TYPE		3 //分类包
#define PACK_REGION		4 //地区包
#define PACK_VIDEO		5 //视频包
#define PACK_VPLAY		6 //播放包
#define PACK_VTIME		7 //播放时长包

//数据头
typedef struct packet_head 
{
	int size;
	int funcId;
	int trans_id;
	int msg_code;//信息代码：0-通知服务器不处理压测发的包   1-客户端发的包
}P_HEAD;
/*
//数据头
typedef struct HeadData_t
{
	int funcId;
	bool isdeal;
	int size;
}P_HEAD;*/

//登录请求包, C >> S
typedef struct packet_login 
{
	char name[20];
	char pwd[10];
}P_LOGIN;

//登录应答包，S >> C
typedef struct ack_login
{
	int user_id;
	int login_ret;//0失败   1成功
}A_LOGIN;

//视频频道应答包
typedef struct ack_channel
{
	int t_count;
	int channel_id;
	char name[20];
}A_CHANNEL;

//视频分类应答包
typedef struct ack_type
{
	int t_count;
	int channel_id;
	int type_id;
	char name[20];
}A_TYPE;

//视频地区应答包
typedef struct ack_region
{
	int t_count;
	int channel_id;
	int region_id;
	char name[20];
}A_REGION;

//视频列表请求包
typedef struct pack_videolist 
{
	int page;//页码
	int channel_id;//频道ID
	int type_id;//分类ID
	int region_id;//地区ID
}P_VIDEO;

//视频列表应答包
typedef struct ack_video
{
	int count;
	int video_id;
	int channel_id;
	int type_id;
	int region_id;
	char name[20];
	int playtimes;
	char is_new;
}A_VIDEO;

//播放记录请求
typedef struct packet_play
{
	int user_id;
	int video_id;
}P_PLAY;
//播放记录应答
typedef struct ack_play
{
	int record_id;
	int user_id;
	int video_id;
	int play_times;
	char video_name[20];
	char time[24];
}A_PLAY;

//播放时长请求包
typedef struct packet_playtime
{
	int record_id;
	int end_time;
}P_PTIME;

class CPacketStream
{
public:
	void Packet(char buf[1024], int *Size, int funcId, void *pData, int Len, int trans_id, int msg_code = 0);
	int GetPack(char *buf, int nRead, char *pack, int *Len, int *funcId);
private:
};

#endif