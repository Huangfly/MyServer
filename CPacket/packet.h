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
//���ܺź궨��
#define PACK_HEARD		0 //������
#define PACK_LOGIN		1 //��¼��
#define PACK_CHANNEL	2 //Ƶ����
#define PACK_TYPE		3 //�����
#define PACK_REGION		4 //������
#define PACK_VIDEO		5 //��Ƶ��
#define PACK_VPLAY		6 //���Ű�
#define PACK_VTIME		7 //����ʱ����

//����ͷ
typedef struct packet_head 
{
	int size;
	int funcId;
	int trans_id;
	int msg_code;//��Ϣ���룺0-֪ͨ������������ѹ�ⷢ�İ�   1-�ͻ��˷��İ�
}P_HEAD;
/*
//����ͷ
typedef struct HeadData_t
{
	int funcId;
	bool isdeal;
	int size;
}P_HEAD;*/

//��¼�����, C >> S
typedef struct packet_login 
{
	char name[20];
	char pwd[10];
}P_LOGIN;

//��¼Ӧ�����S >> C
typedef struct ack_login
{
	int user_id;
	int login_ret;//0ʧ��   1�ɹ�
}A_LOGIN;

//��ƵƵ��Ӧ���
typedef struct ack_channel
{
	int t_count;
	int channel_id;
	char name[20];
}A_CHANNEL;

//��Ƶ����Ӧ���
typedef struct ack_type
{
	int t_count;
	int channel_id;
	int type_id;
	char name[20];
}A_TYPE;

//��Ƶ����Ӧ���
typedef struct ack_region
{
	int t_count;
	int channel_id;
	int region_id;
	char name[20];
}A_REGION;

//��Ƶ�б������
typedef struct pack_videolist 
{
	int page;//ҳ��
	int channel_id;//Ƶ��ID
	int type_id;//����ID
	int region_id;//����ID
}P_VIDEO;

//��Ƶ�б�Ӧ���
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

//���ż�¼����
typedef struct packet_play
{
	int user_id;
	int video_id;
}P_PLAY;
//���ż�¼Ӧ��
typedef struct ack_play
{
	int record_id;
	int user_id;
	int video_id;
	int play_times;
	char video_name[20];
	char time[24];
}A_PLAY;

//����ʱ�������
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