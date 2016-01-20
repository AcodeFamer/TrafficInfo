#ifndef __LINKINFO_H__
#define __LINKINFO_H__

#include "utility.h"
#include "VspdCToMySQL.h"
#include <string>

class LinkInfo
{
	string StartNode;

	string EndNode;

	string RoadId;

	float Distance;

public:
	LinkInfo();
	LinkInfo(string, string, string, float);
	~LinkInfo();

	int writeDataToSql(VspdCToMySQL* mysql);

	//根据LINK指针在数据库中查询对应的编号和所属路段信息,返回对应编号
	static int getLinkInfo(VspdCToMySQL* msql, int flag, LINK* pLink, string& road_id);
};



#endif