#include "stdafx.h"
#include "DBoperation.h"

DBoperation::DBoperation()
{	
	//**************************************初始化表名字和表字段

	//节点信息表
	string node[] = { "NodeId", "NodeName", "IsSubzone", "IsCrossing", "ConNodeNum", "IsSingal", "IsOneWay", "LinkId" };
	vector<string> nodeinfo(node, node + sizeof(node) / sizeof(string));
	table["nodeinfo"] = nodeinfo;


	//路段信息表
	string road[] = { "RoadId", "RoadName", "StartNode", "EndNode", "Distance" };
	vector<string> roadinfo(road, road + sizeof(road) / sizeof(string));
	table["roadinfo"] = roadinfo;

	//连接明细表
	string link[] = { "StartNode", "EndNode", "RoadId", "Distance" };
	vector<string> linkinfo(link, link + sizeof(link) / sizeof(string));
	table["linkinfo"] = linkinfo;

	//**********************路口车流表
	string cs[] = { "CrossingId", "LinkInId", "LinkOutId", "RoadInId", "RoadOutId", "Priority" };
	vector<string> crossingstream(cs, cs + sizeof(cs) / sizeof(string));
	table["crossingstream"] = crossingstream;

	//**********************检测器表
	string det[] = { "DetectorId", "DetectorName", "LinkId", "Flag", "DownStreamIndex", "CrossingId", "LaneNum" };
	vector<string> detector(det, det + sizeof(det) / sizeof(string));
	table["detector"] = detector;

	//***********************断面表
	string sec[] = { "SectionName", "IsTwoWay", "LinkId1", "DetectorId1", "LinkId2", "DetectorId2" };
	vector<string> section(sec, sec+sizeof(sec) / sizeof(string));
	table["section"] = section;
	
	//控制方案表
	string cp[] = { "CrossingId", "PhaseNum", "IsPeriodFixed" , "IsActuatedControl", "Period", "PhaseOffset", "IsUpdate" };
	vector<string> controlplan(cp, cp + sizeof(cp) / sizeof(string));
	table["controlplan"] = controlplan;

	//相位表
	string p[] = { "PlanIndex", "PhaseId", "CrossingId", "GreenTime", "AmberTime", "RedTime", "IsUpdate" };
	vector<string> phase(p, p + sizeof(p) / sizeof(string));
	table["phase"] = phase;

	//相位车流明细表
	string ps[] = { "PhaseIndex", "StreamIndex", "DirectionFlag", "PhaseId", "PlanIndex", "CrossingId", "LinkInId" ,"LinkOutId" };
	vector<string> phasestream(ps, p + sizeof(ps) / sizeof(string));
	table["phasestream"] = phasestream;

}

DBoperation::~DBoperation()
{

}

VspdCToMySQL* DBoperation::getMySql()
{
	return mysql;
}

void DBoperation::updateDataTable()
{

}

int DBoperation::getLinkInfo(int flag, LINK* pLink, string& road_id)
{
	//获取该LINK的两个NODE指针
	NODE* nodeA = qpg_LNK_nodeStart(pLink);
	NODE* nodeB = qpg_LNK_nodeEnd(pLink);
	//获取对应id
	string nodeA_id = qpg_NDE_name(nodeA);
	string nodeB_id = qpg_NDE_name(nodeB);

	string start_node, end_node;
	if (flag == 1)   //进  5位路口节点id是end_node
	{
		if (nodeA_id.size() == 5)
		{
			end_node = nodeA_id;
			start_node = nodeB_id;
		}
		else
		{
			start_node = nodeA_id;
			end_node = nodeB_id;
		}

	}
	else      //出   5位路口节点id是start_node
	{
		if (nodeA_id.size() == 5)
		{

			start_node = nodeA_id;
			end_node = nodeB_id;
		}
		else
		{
			start_node = nodeB_id;
			end_node = nodeA_id;
		}
	}
	//根据起始节点和结束节点,查询数据库
	string SQL = "select LinkIndex,RoadId from linkinfo where StartNode=";
	SQL = SQL + "'" + start_node + "' and EndNode='" + end_node + "'";
	string Msg;
	vector<vector<string>>  res = mysql->SelectData(SQL.c_str(), 2, Msg);
	if (res.size() != 0)
	{
		road_id = res[0][1];
		return str2int(res[0][0]);
	}
	else
	{
		qps_GUI_printf("start:%s,end:end:%s", start_node.c_str(), end_node.c_str());
	}
	return 0;
}

set<string> DBoperation::getLinkIdWhenFlagEqualsTwo()
{
	char * SQL = "SELECT LinkId FROM detector WHERE  Flag=2";
	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL, 1, Msg);

	set<string> allDetectorId;
	for (size_t i = 0; i < res.size(); i++)
		allDetectorId.insert(res[i][0]);
	return allDetectorId;
}

vector<string> DBoperation::getAllNetId()
{
	char* SQL = "SELECT RoadNetId FROM roadnetinfo";
	string Msg;
	vector<vector<string>> res;
	res = mysql->SelectData(SQL, 1, Msg);
	vector<string> allName;
	for (size_t i = 0; i < res.size(); i++)
	{
		allName.push_back(res[i][0]);
	}
	return allName;
}

void DBoperation::addNewRoadNet(RoadNetInfo road_net_info)
{
	vector<string> key;
	key.push_back("RoadNetId");
	key.push_back("RoadNetName");
	key.push_back("NodeNum");
	key.push_back("LinkNum");
	key.push_back("SubzoneNum");
	key.push_back("IsSimRunning");

	vector<string> values;
	values.push_back(road_net_info.RoadNetId);
	values.push_back(road_net_info.RoadNetName);
	values.push_back(int2str(road_net_info.NodeNum));
	values.push_back(int2str(road_net_info.LinkNum));
	values.push_back(int2str(road_net_info.SubzoneNum));
	values.push_back(int2str(road_net_info.IsSimRunning));

	mysql->add_data("roadnetinfo", key, values);
}

void DBoperation::clearTable()
{
	string Msg;
	//清空数据库表
	mysql->ClearTable("detector", Msg);
	mysql->ClearTable("roadinfo", Msg);
	mysql->ClearTable("nodeinfo", Msg);
	mysql->ClearTable("section", Msg);
	mysql->ClearTable("linkinfo", Msg);
	mysql->ClearTable("controlplan", Msg);
	mysql->ClearTable("phase", Msg);
	mysql->ClearTable("crossingstream", Msg);
	mysql->ClearTable("phasestream", Msg);
}

bool DBoperation::IsRoadNetModified(string net_name, int nodeNum, int linkNum, int zoneNum)
{
	//查询已知路网的节点数，子区数，检测器数
	string SQL = "SELECT * FROM  roadnetinfo WHERE  RoadNetId= ";
	SQL = SQL + "'" + net_name + "'";
	string Msg;
	vector<vector<string>>  res = mysql->SelectData(SQL.c_str(), 7, Msg);
	int node_num = str2int(res[0][3]);
	int link_num = str2int(res[0][4]);
	int subzone_num = str2int(res[0][5]);
	if (node_num != nodeNum || link_num != linkNum || subzone_num != zoneNum) //路网修改过
	{
		return 1;
	}
	return 0;
}

void DBoperation::updateRoadNetInfoTable(string net_name,int nodeNum,int linkNum,int zoneNum)
{
	string SQL = "UPDATE roadnetinfo SET ";
	SQL = SQL + " NodeNum= " + "'" + int2str(nodeNum) + "'";
	SQL = SQL + ", LinkNum= " + "'" + int2str(linkNum) + "'";
	SQL = SQL + ", SubzoneNum= " + "'" + int2str(zoneNum) + "'";
	SQL = SQL + " WHERE " + " RoadNetId= " + "'" + net_name + "'";
	string Msg;
	mysql->UpdateData(SQL.c_str(), Msg);
}

int DBoperation::isSimStart()
{
	char* SQL = "select * from simrecord where SimIndex=(select max(SimIndex) from simrecord);";
	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL, 15, Msg);
	if (res.size() != 0)
	{
		int is_start = str2int(res[0][6]);
		if (is_start == 1)//若仿真启动，返回仿真编号
			return str2int(res[0][0]);
		else
			return 0;
	}
	else return 0;
}

bool DBoperation::isSimPause()
{
	char* SQL = "select * from simrecord where SimIndex=(select max(SimIndex) from simrecord);";
	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL, 15, Msg);
	if (res.size() != 0)
	{
		int is_pause = str2int(res[0][7]);
		if (is_pause == 1)
			return true;
		else
			return false;
	}
	return false;
}

bool DBoperation::isSimStop()
{
	char* SQL = "select * from simrecord where SimIndex=(select max(SimIndex) from simrecord);";
	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL, 15, Msg);
	if (res.size() != 0)
	{
		int is_stop = str2int(res[0][11]);
		if (is_stop == 1)
			return true;
		else
			return false;
	}
	return false;
}

double DBoperation::getODvalue()
{
	char* SQL = "select * from simrecord where SimIndex=(select max(SimIndex) from simrecord);";
	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL, 15, Msg);
	double od = 0.0;
	if (res.size() != 0)
	{
		od = atof(res[0][4].c_str());
	}
	return od;
}


vector<vector<string>> DBoperation::getSingalTimeByIndex(int plan_index)
{
	string SQL = "select GreenTime,AmberTime,RedTime,IsUpdate from phase where PlanIndex=" + int2str(plan_index);

	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL.c_str(), 4, Msg);

	//读取完成后清除标志位
	string SQL_clear = "update phase set IsUpdate='0' where IsUpdate='1'";
	mysql->UpdateData(SQL_clear.c_str(), Msg);
	return res;
}

template<class T>void DBoperation::roadNetDataWriteToDatabase(string table_name, vector<T> data)
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
			SQL.erase(SQL_insert_nodeinfo.end());
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
		SQL.erase(SQL_insert_nodeinfo.end());
		//完整的SQL插入语句
		SQL_insert = SQL_insert + SQL;
		//插入操作
		string Msg;
		mysql->InsertData(SQL_insert.c_str(), Msg);
		//count_db_write清0
		count_db_write = 0;
	}
	
}

vector<vector<string>> DBoperation::getPlanUpdateIndex()
{
	//查询控制方案表,出现更新的控制方案编号
	char* SQL = "select PlanIndex,CrossingId,Period,PhaseOffset from controlplan where IsUpdate='1';";
	string msg;
	vector<vector<string>> res = mysql->SelectData(SQL, 4, msg);


	//读取完成后清除标志位
	SQL = "update controlplan set IsUpdate='0' where IsUpdate='1'";
	mysql->UpdateData(SQL, msg);
	return res;
}