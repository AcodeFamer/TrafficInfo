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

	//����LINKָ�������ݿ��в�ѯ��Ӧ�ı�ź�����·����Ϣ,���ض�Ӧ���
	static int getLinkInfo(VspdCToMySQL* msql, int flag, LINK* pLink, string& road_id);
};



#endif