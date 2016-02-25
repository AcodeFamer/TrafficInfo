/*****************·����Ϣ��***************/

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

	//�洢·�������е�·��Id
	static vector<string> allRoadLinkId;
	//�ж��¼����·��id�Ƿ��Ѿ�����
	static int IsRoadLinkIdExist(string road_link_id);

	static vector<RoadInfo> allRoadInfo;
};



#endif