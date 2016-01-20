#include "stdafx.h"
#include "VspdCTOMySQL.h"
 
VspdCToMySQL::VspdCToMySQL()
{
	hInst=LoadLibrary(_T("D:\\wamp\\bin\\mysql\\mysql5.5.20\\lib\\libmysql.dll"));

	mysql_init = (MYSQL_INIT)GetProcAddress(hInst, "mysql_init");

	mysql_real_connect = (MYSQL_REAL_CONNECT)GetProcAddress(hInst, "mysql_real_connect");

	mysql_set_character_set = (MYSQL_SET_CHARACTER_SET)GetProcAddress(hInst, "mysql_set_character_set");

	mysql_query = (MYSQL_QUERY)GetProcAddress(hInst, "mysql_query");

	mysql_store_result = (MYSQL_STORE_RESULT)GetProcAddress(hInst, "mysql_store_result");

	mysql_fetch_row = (MYSQL_FETCH_ROW)GetProcAddress(hInst, "mysql_fetch_row");

	mysql_free_result = (MYSQL_FREE_RESULT)GetProcAddress(hInst, "mysql_free_result");

	mysql_close = (MYSQL_CLOSE)GetProcAddress(hInst, "mysql_close");
}
 
VspdCToMySQL::~VspdCToMySQL()
{
}
 
void VspdCToMySQL::StartTransition()
{
	

	mysql_query(&mysql, "START TRANSACTION");
}

void VspdCToMySQL::CommitTransition()
{
	

	mysql_query(&mysql, "COMMIT");
}

//初始化数据库
int VspdCToMySQL::ConnMySQL(char *host,char * port ,char * Db,char * user,char* passwd,char * charset,string& Msg)
{

       if( mysql_init(&mysql) == NULL )
       {
              Msg = "inital mysql handle error";
              return 1;
       }    
 
       if (mysql_real_connect(&mysql,host,user,passwd,Db,0,NULL,0) == NULL)
       {
              Msg = "Failed to connect to database: Error";
              return 1;
       }    
 
       if(mysql_set_character_set(&mysql,"GBK") != 0)
       {
              Msg = "mysql_set_character_set Error";
              return 1;
       }
       return 0;
}
 
//查询数据
vector<vector<string>> VspdCToMySQL::SelectData(const char * SQL,int Cnum,string& Msg)
{
   vector<vector<string>> query_res;


	MYSQL_ROW m_row;
    MYSQL_RES *m_res;
    char sql[2048];
    sprintf(sql,SQL);
    int rnum = 0;
    char rg = 0x06;//行隔开
    char cg = {0x05};//字段隔开
 
    if(mysql_query(&mysql,sql) != 0)
    {
        Msg = "select ps_info Error";
        return query_res;
    }
    
    m_res = mysql_store_result(&mysql);
 
    if(m_res==NULL)
    {
        Msg = "select username Error";
        return query_res;
    }

    //string str("");
    
 
    while(m_row = mysql_fetch_row(m_res))
    {
        vector<string> row_res;
        for(int i = 0;i < Cnum;i++)
        {
           row_res.push_back(m_row[i]);
        }
        query_res.push_back(row_res);
     }
 
     mysql_free_result(m_res);
 
     return query_res;
}



//插入数据
int VspdCToMySQL::InsertData(const char * SQL,string& Msg)
{

  
   char sql[2048];
   sprintf(sql,SQL);
   if(mysql_query(&mysql,sql) != 0)
   {
       Msg = "Insert Data Error";
       return 1;
   }
   return 0;
}
 
//更新数据
int VspdCToMySQL::UpdateData(const char * SQL,string& Msg)
{
   
    char sql[2048];
    sprintf(sql,SQL);
    if(mysql_query(&mysql,sql) != 0)
    {
        Msg = "Update Data Error";
        return 1;
    }
    return 0;
}
 
//删除数据
int VspdCToMySQL::DeleteData(const char * SQL,string& Msg)
{

 

   char sql[2048];
   sprintf(sql,SQL);
   if(mysql_query(&mysql,sql) != 0)
   {
      Msg = "Delete Data error";
      return 1;
   }
   return 0;
}
 
//关闭数据库连��?
void VspdCToMySQL::CloseMySQLConn()
{
   
   mysql_close(&mysql);
}

int VspdCToMySQL::add_data( string tableName,vector<string> key,vector<string> value)
{
	string SQL="INSERT INTO "+tableName+ "(";
	for(size_t i=0;i<key.size()-1;i++)
	{
		SQL=SQL+key[i]+",";
	}
	SQL=SQL+key[key.size()-1]+")";

	SQL=SQL+" VALUES (";

	for(size_t i=0;i<value.size()-1;i++)
	{
		SQL=SQL+"'"+value[i]+"'"+",";
	}
	SQL = SQL + "'" + value[key.size() - 1] + "'" + ")";

	cout<<SQL<<endl;
	string Msg;
	if(InsertData(SQL.c_str(),Msg)!=0)
	{
		cout<<Msg<<endl;
		return 1;
	}

	return 0;
}

int VspdCToMySQL::ClearTable( string tableName ,string& Msg)
{
	string SQL("truncate table ");
	SQL=SQL+tableName+";";
	char sql[2048];
	sprintf(sql,SQL.c_str());

	if(mysql_query(&mysql,sql) != 0)
	{
		Msg = "clear table Error";
		return 1;
	}
	return 0;
}
/*
#include "stdafx.h"
#include "VspdCTOMySQL.h"
 
int main(int argc, char* argv[])
{
    char* host="MYSQL服务器IP";
    char* user="root";
    char* port ="3306";
    char* passwd="用户密码";
    char* dbname="数据库名��?; 
    char* charset = "GBK";//支持中文
    char* Msg = "";//消息变量
    //初始��?
    VspdCToMySQL * vspdctomysql = new VspdCToMySQL;
    if(vspdctomysql->ConnMySQL(host,port,dbname,user,passwd,charset,Msg) == 0)
           printf("连接成功/r/n");
    else
           printf(Msg);
   
    //查询
    char * SQL = "SELECT ids,username,passwd,address FROM vcaccesstest";
    string str = vspdctomysql->SelectData(SQL,4,Msg);
    if( str.length() > 0 )
    {
           printf("查询成功/r/n");
           printf(str.data());
           printf("/r/n");
    }
    else
    {
           printf(Msg);
    }
    //插入
    SQL = "insert into vcaccesstest(ids,username,passwd,address) values(4,'我的','123210','测试地址')";
    if(vspdctomysql->InsertData(SQL,Msg) == 0)
           printf("插入成功/r/n");
    //更新
    SQL = "update vcaccesstest set username = '修改��?,passwd='2345' where ids = 3 ";
    if(vspdctomysql->UpdateData(SQL,Msg) == 0)
           printf("更新成功/r/n");
    //删除
    SQL = "delete from vcaccesstest where ids = 3 ";
    if(vspdctomysql->DeleteData(SQL,Msg) == 0)
           printf("删除成功/r/n");
 
    vspdctomysql->CloseMySQLConn();
 
    return 0;
}
*/