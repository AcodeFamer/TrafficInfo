#ifndef __DBOPERATION_H__
#define __DBOPERATION_H__

#include "VspdCToMySQL.h"
#include <set>
#include <map>

//****************************************数据库操作类*****************************************
class DBoperation
{
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
	template<class T> void roadNetDataWriteToDatabase(string table_name,vector<T> data);
};
#endif