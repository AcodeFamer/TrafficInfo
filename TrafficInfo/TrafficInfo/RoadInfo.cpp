#include "stdafx.h"
#include "RoadInfo.h"


vector<string> RoadInfo::allRoadLinkId;
RoadInfo::RoadInfo()
{

}

RoadInfo::RoadInfo(string id, string name, string start_node, string end_node, float dis)
{
	
	RoadId=id;
	
	RoadName=name;

	StartNode=start_node;

	EndNode=end_node;

	Distance=dis;


}

RoadInfo::~RoadInfo()
{

}

int RoadInfo::writeDataToSql(VspdCToMySQL* mysql)
{
	vector<string> key;
	key.push_back("RoadId");
	key.push_back("RoadName");
	key.push_back("StartNode");
	key.push_back("EndNode");
	key.push_back("Distance");


	vector<string> values;
	values.push_back(RoadId);
	values.push_back(RoadName);
	values.push_back(StartNode);
	values.push_back(EndNode);
	values.push_back(float2str(Distance));


	if (mysql->add_data("roadinfo", key, values)==0)
	{
		//路段Id成功写入数据库时，同时添加到allRoadLinkId
		allRoadLinkId.push_back(RoadId);
		return 0;
	}
		
	else 
		return 1;
}

int RoadInfo::IsRoadLinkIdExist(string road_link_id)
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
