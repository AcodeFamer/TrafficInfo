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
 
      
       VspdCToMySQL();
       ~VspdCToMySQL();
 
	   //�������񣺲�������ǰ���ȿ����������Ч��
	   void StartTransition();

	   //�ύ���񣺲�����ɺ��ύ����
	   void CommitTransition();
  
       
       
       int ConnMySQL(char *host,char * port,char * Db,char * user,char* passwd,char * charset,string& Msg);
 
     
       vector<vector<string>> SelectData(const char * SQL,int Cnum ,string& Msg);
      
       /*
     
       */
       int InsertData(const char * SQL,string& Msg);
       
      
       int UpdateData(const char * SQL,string& Msg);
       
       
       
       int DeleteData(const char * SQL,string& Msg);
       
       void CloseMySQLConn();


	   int add_data(const string tableName,vector<string> key,vector<string> values);


	   int ClearTable(string tableName,string& Msg);

	  
 
};

#endif