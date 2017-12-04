/****************************************************************************************************
*��Ȩ���� (C)2015   ׿Ծ�����ְҵ��ѵѧУ
*�ļ����ƣ� DbCon.c
*
*����ժҪ��
*	���ļ�ʵ�����ݿ�Ĳ�����ʵ��
*��ʷ��¼��
*	����ʱ�䣺2015-03-05
*	���ڣ�2015-03-05		�޸��ˣ��Ʒɻ�
*	������
******************************************************************************************************/
#include "./DbCon.h"

CDbCon* CDbCon::mInstance=NULL;
CDbCon::CGarbo CDbCon::Garbo;

/*********************************************************
*	�������ƣ�CDbCon::CDbCon()
*	������
			���ݿ����Ĺ��캯���������ݿ�
*	������
			��
*	����ֵ��
			��
*	�޸�ʱ�䣺2015.03.05  15:34		�Ʒɻ�
*********************************************************/
CDbCon::CDbCon()
{
	if( sqlite3_open("./DB/myDB.db", &mydb) != SQLITE_OK)
	{
		cout << "open db error" << endl;
		exit(1);
	}
}

/*********************************************************
*	�������ƣ�int CDbCon::Get_Data(char *sql,sqlite3_callback Callback,void *pData)
*	������
			�����ݿ���в���������ȡ
*	������
			��sql��SQLite3���ݿ��SQLִ�����
			��Callback���ص�����
			��pData���ص������Ĵ������
*	����ֵ��
			��merrmsg��������Ϣ
*	�޸�ʱ�䣺2015.03.05  15:34		�Ʒɻ�
*********************************************************/
int CDbCon::Get_Data(char *sql,sqlite3_callback Callback,void *pData)
{
	char *errmsg;
	int iresult;
	
	iresult = sqlite3_exec(mydb,sql,Callback,pData,&errmsg);
	return iresult;
}

/*********************************************************
*	�������ƣ�CDbCon::~CDbCon()
*	������
			���ݿ����������������ر����ݿ�
*	������
			��
*	����ֵ��
			��
*	�޸�ʱ�䣺2015.03.05  15:34		�Ʒɻ�
*********************************************************/
CDbCon::~CDbCon()
{
	if( sqlite3_close(mydb) != SQLITE_OK)
	{
		cout << "close db error" << endl;
		exit(1);		
	}
}

/*********************************************************
*	�������ƣ�int GetData_callback(void *pData,int col,char **val,char **colname)
*	������
			�ص�����������ȡ�����еĵ�һ�����ݿ������������
*	������
			��pData���������
			��col���������
			��val���е�����
			��colname���е�����

*	����ֵ��
			����0�����������˳�����ִ�лص�����
*	�޸�ʱ�䣺2015.03.05  15:34		�Ʒɻ�
*********************************************************/
int GetData_callback(void *pData,int col,char **val,char **colname)
{
	strcpy((char*)pData,val[0]);
	return 0;
}

int GetCount_callback(void *pData,int col,char **val,char **colname)
{
	int *count = (int*)pData;
	*count = atoi(val[0]);
	return 0;
}