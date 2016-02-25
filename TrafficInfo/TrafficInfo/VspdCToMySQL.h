/*

	mysql数据库中增删查改的操作的实现
*/

#ifndef __VSPDCTOMYSQL_H__
#define __VSPDCTOMYSQL_H__
#include <winsock2.h>
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
    //解析的mysql的函数原型；
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
	   //构造函数和析构函数
       VspdCToMySQL();
       ~VspdCToMySQL();
 
	   //开启事务：插入数据前，先开启事务，提高效率（用于innodb引擎）
	   void StartTransition();

	   //提交事务：插入完成后提交事务（用于innodb引擎）
	   void CommitTransition();
       /*
	     连接数据库（host：主机名 port:端口 Db:数据库名称 ，user:用户，charset:字符集 Msg:返回信息）
	     返回值：0 连接成功  1 失败
	   */
	   int ConnMySQL(string host, int port, string Db, string user, string passwd, string charset, string& Msg);
 
	   /*
	     数据库查询
	     参数：SQL：SQL语言,Cnum：查询的列字段数 ,Msg：返回的信息
	     返回值：0 连接成功  1 失败
	   */
       vector<vector<string>> SelectData(const char * SQL,int Cnum ,string& Msg);
      
       /*
	     数据库插入SQL实现（）
	     返回值:0  插入成功  1 插入失败
	   */
       int InsertData(const char * SQL,string& Msg);
	   /*
	     数据库更新SQL实现（）
	     返回值:0  更新成功  1 更新失败
	   */
       int UpdateData(const char * SQL,string& Msg);
	   /*
	     数据库删除SQL实现（）
	     返回值:0  删除成功  1 删除失败
	   */
       int DeleteData(const char * SQL,string& Msg);
	   /*
		   关闭数据库连接
	   */
       void CloseMySQLConn();
	   /*
	       给一个表添加数据（多条同时添加）
		   返回值:0  添加成功  1添加失败
	   */
	   int add_data(const string tableName,vector<string> key,vector<string> values);
	   /*
	       清空一个数据表
		   返回值:0  成功  1 失败
	   */
	   int ClearTable(string tableName,string& Msg);

};

#endif