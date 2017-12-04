/****************************************************************************************************
*版权所有 (C)2015   卓跃计算机职业培训学校
*文件名称： DbCon.c
*
*内容摘要：
*	本文件实现数据库的操作的实现
*历史记录：
*	创建时间：2015-03-05
*	日期：2015-03-05		修改人：黄飞华
*	描述：
******************************************************************************************************/
#include "./DbCon.h"

CDbCon* CDbCon::mInstance=NULL;
CDbCon::CGarbo CDbCon::Garbo;

/*********************************************************
*	函数名称：CDbCon::CDbCon()
*	描述：
			数据库基类的构造函数，打开数据库
*	参数：
			无
*	返回值：
			无
*	修改时间：2015.03.05  15:34		黄飞华
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
*	函数名称：int CDbCon::Get_Data(char *sql,sqlite3_callback Callback,void *pData)
*	描述：
			对数据库进行操作，即存取
*	参数：
			【sql】SQLite3数据库的SQL执行语句
			【Callback】回调函数
			【pData】回调函数的传入参数
*	返回值：
			【merrmsg】错误信息
*	修改时间：2015.03.05  15:34		黄飞华
*********************************************************/
int CDbCon::Get_Data(char *sql,sqlite3_callback Callback,void *pData)
{
	char *errmsg;
	int iresult;
	
	iresult = sqlite3_exec(mydb,sql,Callback,pData,&errmsg);
	return iresult;
}

/*********************************************************
*	函数名称：CDbCon::~CDbCon()
*	描述：
			数据库基类的析构函数，关闭数据库
*	参数：
			无
*	返回值：
			无
*	修改时间：2015.03.05  15:34		黄飞华
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
*	函数名称：int GetData_callback(void *pData,int col,char **val,char **colname)
*	描述：
			回调函数，将读取到的行的第一个数据拷贝给传入参数
*	参数：
			【pData】传入参数
			【col】最大列数
			【val】列的数据
			【colname】列的名字

*	返回值：
			返回0继续，否则退出不再执行回调函数
*	修改时间：2015.03.05  15:34		黄飞华
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