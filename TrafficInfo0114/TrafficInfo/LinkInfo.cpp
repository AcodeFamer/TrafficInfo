#include "stdafx.h"
#include "LinkInfo.h"


vector<string> LinkInfo::allRoadLinkId;

LinkInfo::LinkInfo()
{

}

LinkInfo::LinkInfo(string id,string name,string start_node,string end_node,int dis)
{
	
	LinkId=id;
	
	LinkName=name;

	StartNode=start_node;

	EndNode=end_node;

	Distance=dis;


}

LinkInfo::~LinkInfo()
{

}

int LinkInfo::writeDataToSql( VspdCToMySQL* mysql )
{
	vector<string> key;
	key.push_back("LinkId");
	key.push_back("LinkName");
	key.push_back("StartNode");
	key.push_back("EndNode");
	key.push_back("Distance");


	vector<string> values;
	values.push_back(LinkId);
	values.push_back(LinkName);
	values.push_back(StartNode);
	values.push_back(EndNode);
	values.push_back(int2str(Distance));


	if (mysql->add_data("linkinfo", key, values)==0)
	{
		//路段Id成功写入数据库时，同时添加到allRoadLinkId
		allRoadLinkId.push_back(LinkId);
		return 0;
	}
		
	else 
		return 1;
}

int LinkInfo::IsRoadLinkIdExist(string road_link_id)
{
	for (size_t i = 0; i < allRoadLinkId.size(); i++)
	{
		if (allRoadLinkId[i] == road_link_id)
		{
			return 1;
		}
	}
	return 0;
}
