#include "./packet.h"

void CPacketStream::Packet(char buf[1024], int *Size, int funcId, void *pData, int Len, int trans_id, int msg_code /* = 0 */)
{
	char head_str[2] = {HEAD_CHR, HEAD_CHR};
	char end_str[2] = {END_CHR, END_CHR};
	P_HEAD packet_head = {0};

	packet_head.funcId = funcId;
	packet_head.size = H_E_LEN + sizeof(P_HEAD) + Len + H_E_LEN;
	*Size = packet_head.size;
	packet_head.trans_id = trans_id;
	packet_head.msg_code = msg_code;

	//memset(buf, 0, packet_head.size);
	memcpy(buf, head_str, H_E_LEN);
	memcpy(buf + H_E_LEN, &packet_head, sizeof(P_HEAD));
	if (pData != NULL && Len > 0)
	{
		memcpy(buf + H_E_LEN + sizeof(P_HEAD), pData, Len);
		memcpy(buf + H_E_LEN + sizeof(P_HEAD) + Len, end_str, H_E_LEN);
	}
	else
	{
		memcpy(buf + H_E_LEN + sizeof(P_HEAD), end_str, H_E_LEN);
	}
}

int CPacketStream::GetPack(char *buf, int nRead, char *pack, int *Len, int *funcId)
{
	int i = 0;
	P_HEAD head = {0};
	char head_str[2] = {HEAD_CHR, HEAD_CHR};
	char end_str[2] = {END_CHR, END_CHR};

	for (i = 0; i < nRead; i++)
	{
		if (*(buf + i) == HEAD_CHR)
		{
			if (*(buf + i + 1) == HEAD_CHR)
			{
				//获取head，取出size
				memcpy(&head, buf + i + H_E_LEN, sizeof(P_HEAD));
				if (head.size > nRead - i || head.size < 0 || head.funcId == 0)
				{
					continue;
				}
				//偏移size，判断是否有包尾
				if (memcmp(buf + i + head.size - H_E_LEN, end_str, H_E_LEN) == 0)//获取到完整的包
				{
					memcpy(pack, buf + i, head.size);
					*Len = head.size;
					*funcId = head.funcId;
					return i;
				}
				else//半包
				{
					continue;
				}
			}
		}
	}


/*	//先遍历找到包头
	for (i = 0; i < nRead; i++)
	{
		if(memcmp(buf + i, head_str, H_E_LEN) == 0)
		{
			//获取head，取出size
			memcpy(&head, buf + i + H_E_LEN, sizeof(P_HEAD));
			if (head.size > nRead - i || head.size < 0 || head.funcId == 0)
			{
				continue;
			}
			//偏移size，判断是否有包尾
			if (memcmp(buf + i + head.size - H_E_LEN, end_str, H_E_LEN) == 0)//获取到完整的包
			{
				memcpy(pack, buf + i, head.size);
				*Len = head.size;
				*funcId = head.funcId;
				return i;
			}
			else//半包
			{
				continue;
			}
		}
	}*/
	*Len = 0;
	return i;
}