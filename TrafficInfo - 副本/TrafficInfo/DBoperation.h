#ifndef __DBOPERATION_H__
#define __DBOPERATION_H__

#include "VspdCToMySQL.h"
#include <set>
#include <map>

//****************************************数据库操作类*****************************************
class DBoperation
{
private:
	VspdCToMySQL* mysql;
	//表名字和表字段信息
	map<string, vector<string>> table;
public:
	DBoperation();
	~DBoperation();
	VspdCToMySQL* getMySql();
	//更新相应的数据库表
	void updateDataTable();
	//根据给定LINK指针获取对应的所属路段id
	int getLinkInfo(int flag, LINK* pLink, string& road_id);
	set<string> getLinkIdWhenFlagEqualsTwo();
	vector<string> getAllNetId();
	//添加新的路网信息
	void addNewRoadNet(RoadNetInfo road_net_info);
	//清空相关表信息
	void clearTable();
	//判断路网是否修改
	bool IsRoadNetModified(string net_name, int nodeNum, int linkNum, int zoneNum);
	//更新路网信息表（路网修改时调用）
	void updateRoadNetInfoTable(string net_name, int nodeNum, int linkNum, int zoneNum);


	//查询连接明细表中所有所属路段为该路段id的所有link的长度
	vector<vector<string>> getLinkDistance(string link_id);
	//获取phase表中指定相位编号PhaseIndex的控制方案编号(函数返回值，若为0表示获取失败)，相位序号，所属路口信息
	int getPhaseInfo(int PhaseIndex, string& phase_id, string& crossing_id);

	//根据所属路口查询路口车流表中满足该路口信息的所有流入路段id和流出路段id,返回对应的路口车流编号StreamIndex，获取失败返回0
	vector<vector<string>> getCrossStreamInfo(string crossing_id);

	//判断仿真是否启动
	int  isSimStart();
	//判断仿真是都暂停
	bool isSimPause();
	bool isSimStop();
	//从数据库中获取OD_value值
	double getODvalue();
	//查看控制方案表的信息（是否更新，路口id，planIndex）
	vector<vector<string>> getPlanUpdateIndex();
	//查看相位表中指定planIndex的所有相位信息
	vector<vector<string>> getSingalTimeByIndex(int plan_index);
	//按表名字，相应数据，写入数据库表
	template<class T> void dataWriteToDatabase(string table_name, vector<T>& data);


};

//模板函数的实现不能放在cpp文件中，否则会出现编译错误
template<class T>
void DBoperation::dataWriteToDatabase(string table_name,  vector<T>& data)
{
	/**************************************插入语句的头部 insert into table_name(字段1，字段2，、、、、)*/
	//获取该表所有字段信息
	vector<string> name = table[table_name];
	string SQL_insert = "insert into " + table_name + "(";
	for (size_t j = 0; j < name.size() - 1; j++)
	{
		SQL_insert = SQL_insert + name[j] + ",";
	}
	SQL_insert = SQL_insert + name[name.size() - 1] + ") values ";

	int count_db_write = 0;//每次插入数据条数计数
	string SQL;
	//插入节点信息表
	for (size_t i = 0; i < data.size(); i++)
	{
		//一次插入多条数据
		SQL = SQL + data[i].getDataString() + ",";
		//插入条数计数
		count_db_write++;
		//累计到30条数据
		if (count_db_write == 30)
		{
			//去掉最后一个逗号
			SQL.erase(SQL_insert.end());
			//完整的SQL插入语句
			SQL_insert = SQL_insert + SQL;
			//插入操作
			string Msg;
			mysql->InsertData(SQL_insert.c_str(), Msg);
			//count_db_write清0
			count_db_write = 0;
		}
	}
	//*********************************************最后还剩不足30条数据插入
	if (count_db_write != 0)
	{
		//去掉最后一个逗号
		SQL.erase(SQL_insert.end());
		//完整的SQL插入语句
		SQL_insert = SQL_insert + SQL;
		//插入操作
		string Msg;
		mysql->InsertData(SQL_insert.c_str(), Msg);
		//count_db_write清0
		count_db_write = 0;
	}

}

#endif