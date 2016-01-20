/**********节点信息************/
#ifndef __NODEINFO_H__
#define __NODEINFO_H__

#include  "VspdCToMySQL.h"
#include "utility.h"
#include <string>
using namespace std;

class NodeInfo
{
    //节点ID
    string NodeId;
    //节点名称
    string NodeName;
    //是否小区
    int IsSubzone;
    //是否路口
    int IsCrossing;
    //连接节点�?
    int ConNodeNum;
    //是否信号�?
    int IsSingal;

	int IsOneWay;

	string LinkId;
public:
    NodeInfo();
    NodeInfo(string,string,int,int,int,int,int,string);
    ~NodeInfo();
	int writeDataToSql(VspdCToMySQL *mysql);
};

#endif