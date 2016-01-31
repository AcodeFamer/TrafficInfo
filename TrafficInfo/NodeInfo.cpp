#include "stdafx.h"
#include "NodeInfo.h"


vector<NodeInfo> NodeInfo::allNodeInfo;


NodeInfo::NodeInfo()
{

}

NodeInfo::NodeInfo(string id,string name,int is_sub_zone,int is_crossing,int con_node_num,int is_singal,int is_one_way,string link_id)
{

	NodeId=id;

	NodeName=name;

	IsSubzone=is_sub_zone;

	IsCrossing=is_crossing;

	ConNodeNum=con_node_num;

	IsSingal=is_singal;

	IsOneWay=is_one_way;

	LinkId=link_id;
}

NodeInfo::~NodeInfo()
{

}

int NodeInfo::writeDataToSql( VspdCToMySQL *mysql )
{
	/***************判断节点的类型写入数据库****************************/
	vector<string> key;
	vector<string> values;
	if(IsSubzone==1)//小区
	{
		
		key.push_back("NodeId");
		key.push_back("IsSubzone");
		key.push_back("IsCrossing");
		key.push_back("IsOneWay");

		
		values.push_back(NodeId);
		values.push_back(int2str(IsSubzone));
		values.push_back(int2str(IsCrossing));
		values.push_back(int2str(IsOneWay));		
	}

	else if (IsCrossing==1)//路口
	{

		
		key.push_back("NodeId");
		key.push_back("IsSubzone");
		key.push_back("IsCrossing");
		key.push_back("ConNodeNum");
		key.push_back("IsSingal");


		values.push_back(NodeId);
		values.push_back(int2str(IsSubzone));
		values.push_back(int2str(IsCrossing));
		values.push_back(int2str(ConNodeNum));
		values.push_back(int2str(IsSingal));
	}
	else       //路段节点
	{
		
		key.push_back("NodeId");
		key.push_back("IsSubzone");
		key.push_back("IsCrossing");
		key.push_back("LinkId");

		
		values.push_back(NodeId);
		values.push_back(int2str(IsSubzone));
		values.push_back(int2str(IsCrossing));
		values.push_back(LinkId);
	}
	
	if(mysql->add_data("nodeinfo",key,values)==0)
		return 0;
	else 
		return 1;
}