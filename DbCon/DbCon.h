/****************************************************************************************************
*版权所有 Copyleft(C)2015    卓跃计算机职业培训学校
*文件名称： DbCon.h
*
*内容摘要：
*	本文件存放数据库基类的声明
*历史记录：
*	创建时间：2015-01-25
*	日期：2015-01-25 		修改人：黄飞华
*	描述：
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
	CDbCon();//构造函数私有，防止实例化
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