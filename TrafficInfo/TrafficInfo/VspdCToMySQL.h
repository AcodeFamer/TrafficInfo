#ifndef __VSPDCTOMYSQL_H__
#define __VSPDCTOMYSQL_H__
#include<winsock2.h>
#include <iostream>
#include <string>
#include <mysql.h>
#include <tchar.h>
#include <vector>
using namespace std;

typedef MYSQL*(__stdcall * MYSQL_INIT)(MYSQL*);

typedef MYSQL*(__stdcall * MYSQL_REAL_CONNECT)(MYSQL*, const char*, const char*, const char*, const char*, unsigned int, const char*, unsigned long);

typedef int(__stdcall * MYSQL_SET_CHARACTER_SET)(MYSQL*, const char*);

typedef int(__stdcall * MYSQL_QUERY)(MYSQL*, const char*);

typedef MYSQL_RES*(__stdcall * MYSQL_STORE_RESULT)(MYSQL*);

typedef MYSQL_ROW(__stdcall * MYSQL_FETCH_ROW)(MYSQL_RES *);

typedef void(__stdcall * MYSQL_FREE_RESULT)(MYSQL_RES *);

typedef void(__stdcall * MYSQL_CLOSE)(MYSQL*);

class VspdCToMySQL 
{
    
	HINSTANCE hInst;

	MYSQL_INIT mysql_init;

	MYSQL_REAL_CONNECT mysql_real_connect;

	MYSQL_SET_CHARACTER_SET mysql_set_character_set;

	MYSQL_QUERY mysql_query;

	MYSQL_STORE_RESULT mysql_store_result;

	MYSQL_FETCH_ROW mysql_fetch_row;

	MYSQL_FREE_RESULT mysql_free_result;

	MYSQL_CLOSE mysql_close;
public:
      
       MYSQL mysql;
 
       /*构造和析构函数*/
       VspdCToMySQL();
       ~VspdCToMySQL();
 
	   //�������񣺲�������ǰ���ȿ����������Ч��
	   void StartTransition();

	   //�ύ���񣺲�����ɺ��ύ����
	   void CommitTransition();
       /*
       主要的功能：
       初始化数据库
       连接数据�?
       设置字符�?
       
       
       入口参数
       host:服务器IP
       Db：数据库名称
       user：数据库用户
       passwd：数据库用户的密�?
       charset：希望使用的字符�?
       Msg：返回的消息（包括错误消息）
       
       
       出口参数�?
       int �? 表示成功  1表示失败
       */
       
       
       int ConnMySQL(char *host,char * port,char * Db,char * user,char* passwd,char * charset,string& Msg);
 
       /*
       主要功能�?
       插入数据
       
       入口参数�?
       SQL:查询SQL语句
       
       Cnum：查询的列数
       Msg：返回的消息（包括错误消息）
       
       出口参数：string 准备放置返回的数据，多条记录则用0x06展开，多个栏位用0x05隔开
       如果范围的长度为0 ，则表示无结�?

      */
       vector<vector<string>> SelectData(const char * SQL,int Cnum ,string& Msg);
      
       /*
     
       */
       int InsertData(const char * SQL,string& Msg);
       
       /*
       主要功能�?
       修改数据
       
       入口参数�?
       SQL：查询的SQL语句
       Msg：返回的消息（包括错误消息）
       
       出口参数�?
       int�? 表示成功�?表示失败
       */
       int UpdateData(const char * SQL,string& Msg);
       
       
       /*
       主要功能�?
       删除数据
       
       入口参数�?
       SQL：查询的SQL语句
       Msg：返回的消息（包括错误消息）
       
       出口参数�?
       int�? 表示成功�?表示失败
       */
       int DeleteData(const char * SQL,string& Msg);
       /*
       主要功能�?
       关闭数据库连�?
       */
       void CloseMySQLConn();


	   int add_data(const string tableName,vector<string> key,vector<string> values);


	   int ClearTable(string tableName,string& Msg);

	  
 
};

#endif