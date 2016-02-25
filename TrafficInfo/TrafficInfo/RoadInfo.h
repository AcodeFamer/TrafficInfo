/*****************路段信息表***************/

#ifndef __RoadInfo_H__
#define __RoadInfo_H__

#include "VspdCToMySQL.h"
#include "utility.h"
#include <string>
using namespace std;

class RoadInfo
{
    
	string RoadId;
    
	string RoadName;
   
    string StartNode;
   
    string EndNode;
    
    float Distance;
    

public:
	RoadInfo();
	RoadInfo(string, string, string, string, float);
	~RoadInfo();

	int writeDataToSql(VspdCToMySQL* mysql);

	//存储路网中所有的路段Id
	static vector<string> allRoadLinkId;
	//判断新加入的路段id是否已经存在
	static int IsRoadLinkIdExist(string road_link_id);

	static vector<RoadInfo> allRoadInfo;
};



#endif