/**********节点信息表************/
#ifndef __NODEINFO_H__
#define __NODEINFO_H__

#include  "VspdCToMySQL.h"
#include "utility.h"
#include <string>
using namespace std;

class NodeInfo
{
    
    string NodeId;
    
    string NodeName;
    
    int IsSubzone;
    
    int IsCrossing;
    
    int ConNodeNum;
    
    int IsSingal;

	int IsOneWay;

	string LinkId;

public:
    NodeInfo();
    NodeInfo(string,string,int,int,int,int,int,string);
    ~NodeInfo();
	int writeDataToSql(VspdCToMySQL *mysql);

	static vector<NodeInfo> allNodeInfo;
};

#endif