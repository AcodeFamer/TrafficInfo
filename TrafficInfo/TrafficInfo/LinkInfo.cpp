#include "stdafx.h"
#include "LinkInfo.h"


vector<LinkInfo> LinkInfo::allLinkInfo;

LinkInfo::LinkInfo()
{

}

LinkInfo::LinkInfo(string start_node, string end_node, string road_id, float dis)
{
	StartNode = start_node;
	EndNode = end_node;
	RoadId = road_id;
	Distance = dis;
}

LinkInfo::~LinkInfo()
{

}

int LinkInfo::writeDataToSql(VspdCToMySQL* mysql)
{
	vector<string> key;
	key.push_back("StartNode");
	key.push_back("EndNode");
	key.push_back("RoadId");
	key.push_back("Distance");


	vector<string> values;
	values.push_back(StartNode);
	values.push_back(EndNode);
	values.push_back(RoadId);
	values.push_back(float2str(Distance));


	if (mysql->add_data("linkinfo", key, values) == 0)
	{
		return 0;
	}

	else
		return 1;
}

int LinkInfo::getLinkInfo(VspdCToMySQL* mysql, int flag, LINK* pLink, string& road_id)
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
		qps_GUI_printf("start:%s,end:end:%s",start_node.c_str(),end_node.c_str());
	}
	return 0;
}

