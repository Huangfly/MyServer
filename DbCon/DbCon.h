/****************************************************************************************************
*��Ȩ���� Copyleft(C)2015    ׿Ծ�����ְҵ��ѵѧУ
*�ļ����ƣ� DbCon.h
*
*����ժҪ��
*	���ļ�������ݿ���������
*��ʷ��¼��
*	����ʱ�䣺2015-01-25
*	���ڣ�2015-01-25 		�޸��ˣ��Ʒɻ�
*	������
******************************************************************************************************/
#ifndef _DBCON_H_
#define _DBCON_H_

#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

class CDbCon
{
public:
	static CDbCon* getInstance()
	{
		if (mInstance == NULL)
		{
			mInstance=new CDbCon();
		}
		return mInstance;
	}

	int Get_Data(char *sql,sqlite3_callback Callback,void *pData);
protected:
	CDbCon();//���캯��˽�У���ֹʵ����
	~CDbCon();

	sqlite3 *mydb;

	static CDbCon *mInstance;
	class CGarbo
    {
    public:
        ~CGarbo()
        {
            if(CDbCon::mInstance!=NULL)
                delete CDbCon::mInstance;
        }
    };
    static CGarbo Garbo;
};

int GetData_callback(void *pData,int col,char **val,char **colname);
int GetCount_callback(void *pData,int col,char **val,char **colname);

#endif