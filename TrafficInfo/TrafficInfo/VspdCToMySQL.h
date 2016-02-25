/*

	mysql���ݿ�����ɾ��ĵĲ�����ʵ��
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
    //������mysql�ĺ���ԭ�ͣ�
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
	   //���캯������������
       VspdCToMySQL();
       ~VspdCToMySQL();
 
	   //�������񣺲�������ǰ���ȿ����������Ч�ʣ�����innodb���棩
	   void StartTransition();

	   //�ύ���񣺲�����ɺ��ύ��������innodb���棩
	   void CommitTransition();
       /*
	     �������ݿ⣨host�������� port:�˿� Db:���ݿ����� ��user:�û���charset:�ַ��� Msg:������Ϣ��
	     ����ֵ��0 ���ӳɹ�  1 ʧ��
	   */
	   int ConnMySQL(string host, int port, string Db, string user, string passwd, string charset, string& Msg);
 
	   /*
	     ���ݿ��ѯ
	     ������SQL��SQL����,Cnum����ѯ�����ֶ��� ,Msg�����ص���Ϣ
	     ����ֵ��0 ���ӳɹ�  1 ʧ��
	   */
       vector<vector<string>> SelectData(const char * SQL,int Cnum ,string& Msg);
      
       /*
	     ���ݿ����SQLʵ�֣���
	     ����ֵ:0  ����ɹ�  1 ����ʧ��
	   */
       int InsertData(const char * SQL,string& Msg);
	   /*
	     ���ݿ����SQLʵ�֣���
	     ����ֵ:0  ���³ɹ�  1 ����ʧ��
	   */
       int UpdateData(const char * SQL,string& Msg);
	   /*
	     ���ݿ�ɾ��SQLʵ�֣���
	     ����ֵ:0  ɾ���ɹ�  1 ɾ��ʧ��
	   */
       int DeleteData(const char * SQL,string& Msg);
	   /*
		   �ر����ݿ�����
	   */
       void CloseMySQLConn();
	   /*
	       ��һ����������ݣ�����ͬʱ��ӣ�
		   ����ֵ:0  ��ӳɹ�  1���ʧ��
	   */
	   int add_data(const string tableName,vector<string> key,vector<string> values);
	   /*
	       ���һ�����ݱ�
		   ����ֵ:0  �ɹ�  1 ʧ��
	   */
	   int ClearTable(string tableName,string& Msg);

};

#endif