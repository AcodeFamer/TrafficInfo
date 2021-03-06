#include "stdafx.h"
#include "VspdCTOMySQL.h"
 
VspdCToMySQL::VspdCToMySQL()
{
	//hInst=LoadLibrary(_T("D:\\wamp\\bin\\mysql\\mysql5.5.20\\lib\\libmysql.dll"));
	//相对路径，libmysql.dll放在parmics安装目录下
	hInst = LoadLibrary(_T("libmysql.dll"));

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

//连接数据库
int VspdCToMySQL::ConnMySQL(string host, int port, string Db, string user, string passwd, string charset, string& Msg)
{

       if( mysql_init(&mysql) == NULL )
       {
              Msg = "inital mysql handle error";
              return 1;
       }    
 
       if (mysql_real_connect(&mysql,host.c_str(),user.c_str(),passwd.c_str(),Db.c_str(),port,NULL,0) == NULL)
       {
              Msg = "Failed to connect to database: Error";
              return 1;
       }    
 
       if(mysql_set_character_set(&mysql,charset.c_str()) != 0)
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
 
//关闭数据库连接
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

	string Msg;
	if(InsertData(SQL.c_str(),Msg)!=0)
	{
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
