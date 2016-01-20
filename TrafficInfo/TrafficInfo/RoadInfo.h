/*****************路段信息�?***************/

#ifndef __RoadInfo_H__
#define __RoadInfo_H__

#include "VspdCToMySQL.h"
#include "utility.h"
#include <string>
using namespace std;

class RoadInfo
{
    //路段ID
	string RoadId;
    //路段名称
	string RoadName;
    //起始节点
    string StartNode;
    //结束节点
    string EndNode;
    //距离
    int Distance;
    

public:
	RoadInfo();
	RoadInfo(string, string, string, string, int);
	~RoadInfo();

	int writeDataToSql(VspdCToMySQL* mysql);

	//�洢·�������е�·��Id
	static vector<string> allRoadLinkId;
	//�ж��¼����·��id�Ƿ��Ѿ�����
	static int IsRoadLinkIdExist(string road_link_id);
};



#endif