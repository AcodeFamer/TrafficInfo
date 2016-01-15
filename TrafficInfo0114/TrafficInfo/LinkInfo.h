/*****************路段信息�?***************/

#ifndef __LINKINFO_H__
#define __LINKINFO_H__

#include "VspdCToMySQL.h"
#include "utility.h"
#include <string>
using namespace std;

class LinkInfo
{
    //路段ID
    string LinkId;
    //路段名称
    string LinkName;
    //起始节点
    string StartNode;
    //结束节点
    string EndNode;
    //距离
    int Distance;
    

public:
    LinkInfo();
    LinkInfo(string,string,string,string,int);
    ~LinkInfo();

	int writeDataToSql(VspdCToMySQL* mysql);

	//�洢·�������е�·��Id
	static vector<string> allRoadLinkId;
	//�ж��¼����·��id�Ƿ��Ѿ�����
	static int IsRoadLinkIdExist(string road_link_id);
};



#endif