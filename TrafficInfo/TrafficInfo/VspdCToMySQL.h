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
 
       /*鏋勯�犲拰鏋愭瀯鍑芥暟*/
       VspdCToMySQL();
       ~VspdCToMySQL();
 
	   //开启事务：插入数据前，先开启事务，提高效率
	   void StartTransition();

	   //提交事务：插入完成后提交事务
	   void CommitTransition();
       /*
       涓昏鐨勫姛鑳斤細
       鍒濆鍖栨暟鎹簱
       杩炴帴鏁版嵁搴?
       璁剧疆瀛楃闆?
       
       
       鍏ュ彛鍙傛暟
       host:鏈嶅姟鍣↖P
       Db锛氭暟鎹簱鍚嶇О
       user锛氭暟鎹簱鐢ㄦ埛
       passwd锛氭暟鎹簱鐢ㄦ埛鐨勫瘑鐮?
       charset锛氬笇鏈涗娇鐢ㄧ殑瀛楃闆?
       Msg锛氳繑鍥炵殑娑堟伅锛堝寘鎷敊璇秷鎭級
       
       
       鍑哄彛鍙傛暟锛?
       int 锛? 琛ㄧず鎴愬姛  1琛ㄧず澶辫触
       */
       
       
       int ConnMySQL(char *host,char * port,char * Db,char * user,char* passwd,char * charset,string& Msg);
 
       /*
       涓昏鍔熻兘锛?
       鎻掑叆鏁版嵁
       
       鍏ュ彛鍙傛暟锛?
       SQL:鏌ヨSQL璇彞
       
       Cnum锛氭煡璇㈢殑鍒楁暟
       Msg锛氳繑鍥炵殑娑堟伅锛堝寘鎷敊璇秷鎭級
       
       鍑哄彛鍙傛暟锛歴tring 鍑嗗鏀剧疆杩斿洖鐨勬暟鎹紝澶氭潯璁板綍鍒欑敤0x06灞曞紑锛屽涓爮浣嶇敤0x05闅斿紑
       濡傛灉鑼冨洿鐨勯暱搴︿负0 锛屽垯琛ㄧず鏃犵粨鏋?

      */
       vector<vector<string>> SelectData(const char * SQL,int Cnum ,string& Msg);
      
       /*
     
       */
       int InsertData(const char * SQL,string& Msg);
       
       /*
       涓昏鍔熻兘锛?
       淇敼鏁版嵁
       
       鍏ュ彛鍙傛暟锛?
       SQL锛氭煡璇㈢殑SQL璇彞
       Msg锛氳繑鍥炵殑娑堟伅锛堝寘鎷敊璇秷鎭級
       
       鍑哄彛鍙傛暟锛?
       int锛? 琛ㄧず鎴愬姛锛?琛ㄧず澶辫触
       */
       int UpdateData(const char * SQL,string& Msg);
       
       
       /*
       涓昏鍔熻兘锛?
       鍒犻櫎鏁版嵁
       
       鍏ュ彛鍙傛暟锛?
       SQL锛氭煡璇㈢殑SQL璇彞
       Msg锛氳繑鍥炵殑娑堟伅锛堝寘鎷敊璇秷鎭級
       
       鍑哄彛鍙傛暟锛?
       int锛? 琛ㄧず鎴愬姛锛?琛ㄧず澶辫触
       */
       int DeleteData(const char * SQL,string& Msg);
       /*
       涓昏鍔熻兘锛?
       鍏抽棴鏁版嵁搴撹繛鎺?
       */
       void CloseMySQLConn();


	   int add_data(const string tableName,vector<string> key,vector<string> values);


	   int ClearTable(string tableName,string& Msg);

	  
 
};

#endif