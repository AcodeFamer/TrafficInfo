/*****************璺淇℃伅绫?***************/

#ifndef __RoadInfo_H__
#define __RoadInfo_H__

#include "VspdCToMySQL.h"
#include "utility.h"
#include <string>
using namespace std;

class RoadInfo
{
    //璺ID
	string RoadId;
    //璺鍚嶇О
	string RoadName;
    //璧峰鑺傜偣
    string StartNode;
    //缁撴潫鑺傜偣
    string EndNode;
    //璺濈
    int Distance;
    

public:
	RoadInfo();
	RoadInfo(string, string, string, string, int);
	~RoadInfo();

	int writeDataToSql(VspdCToMySQL* mysql);

	//存储路网中所有的路段Id
	static vector<string> allRoadLinkId;
	//判断新加入的路段id是否已经存在
	static int IsRoadLinkIdExist(string road_link_id);
};



#endif