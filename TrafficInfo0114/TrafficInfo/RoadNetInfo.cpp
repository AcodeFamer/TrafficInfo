#include "stdafx.h"
#include "RoadNetInfo.h"


//路网中所有检测器指针和检测器id
vector<DETECTOR*> RoadNetInfo::allDetectorPointer;

vector<string> RoadNetInfo::allDetectorId;

map<DETECTOR*, string> RoadNetInfo::allDetectorIdByPointer;


//node数
int RoadNetInfo::nodeNum=0;
//link数
int RoadNetInfo::linkNum = 0;
//zone数
int RoadNetInfo::zoneNum=0;
//detector数
int RoadNetInfo::detectorNum=0;

//所有线圈的指针
vector<vector<LOOP*>> RoadNetInfo::netLoop;
//每个检测器对应有几个线圈
vector<int> RoadNetInfo::loopNumArray;


//路网中每一个detector的每一个loop通过的车辆数(累积量)(有车通过时就刷新)
vector<vector<int>> RoadNetInfo::countEveryLoop;
//路网中每一个detector的每一个loop通过的车辆数(累积量)(到达间隔时间时才刷新)
vector<vector<int>> RoadNetInfo::countEveryLoopDuration;
//路网中每一个detector的每一个loop通过的车辆数(差分量)
vector<vector<int>> RoadNetInfo::countEveryLoopDiff;
//路网中每一个detector所有线圈通过的车辆数
vector<int> RoadNetInfo::countEveryDetector;


//每一个线圈上一辆车的占有时间
vector<vector<float>> RoadNetInfo::occupancyEveryLoop;
//统计时段内，占有时间的累加
vector<vector<float>> RoadNetInfo::occupancyEveryLoopDuration;
//线圈是否被车占用
vector<vector<int>> RoadNetInfo::isOccupiedEveryLoop;


//线圈所属车道平均车速（截止当前时刻）
vector<vector<float>> RoadNetInfo::velocityEveryLoop;
//统计时段内平均车速
vector<vector<float>> RoadNetInfo::velocityEveryLoopDuration;


//OD矩阵
vector<vector<float>> RoadNetInfo::demandMatrix;

float RoadNetInfo::ODvalue = 1.0;
RoadNetInfo::RoadNetInfo()
{
  //  mysql = new VspdCToMySQL;
}

RoadNetInfo::RoadNetInfo(string Id,string name,int nodeNum,int linkNum,int subzoneNum,int isSimRunning)
{
    this->RoadNetId=Id;
    
    this->RoadNetName=name;
    
    this->NodeNum=nodeNum;
    
    this->LinkNum=linkNum;
    
    this->SubzoneNum=subzoneNum;
    
    this->IsSimRunning=isSimRunning;
}

RoadNetInfo::~RoadNetInfo()
{
   // delete mysql;
}


int RoadNetInfo::writeDataToSql(VspdCToMySQL *mysql)
{
	vector<string> key;
	key.push_back("RoadNetId");
	key.push_back("RoadNetName");
	key.push_back("NodeNum");
	key.push_back("LinkNum");
	key.push_back("SubzoneNum");
	key.push_back("IsSimRunning");

	vector<string> values;
	values.push_back(RoadNetId);
	values.push_back(RoadNetName);
	values.push_back(int2str(NodeNum));
	values.push_back(int2str(LinkNum));
	values.push_back(int2str(SubzoneNum));
	values.push_back(int2str(IsSimRunning));

    if(mysql->add_data("roadnetinfo",key,values)==0)
		return 0;
	else 
		return 1;
}

vector<string> RoadNetInfo::getAllNetId( VspdCToMySQL *mysql )
{

	char* SQL="SELECT RoadNetId FROM roadnetinfo";
	string Msg;
	vector<vector<string>> res;
	res=mysql->SelectData(SQL,1,Msg);
	vector<string> allName;
	for(size_t i=0;i<res.size();i++)
	{
		allName.push_back(res[i][0]);
	}
	return allName;
}

bool RoadNetInfo::isNewRoadNet(VspdCToMySQL *mysql ,string road_name )
{
	//从数据库中取出所有路网名称
	vector<string> allNetName=getAllNetId(mysql);

	for(size_t i=0;i<allNetName.size();i++)
	{
		if(road_name==allNetName[i])
		{
			return false;
		}
	}
	return true;
}

vector<string> RoadNetInfo::getAllNodeId(int nodeNum)
{
	vector<string> allNodeId;
	//获取所有节点指针
	vector<NODE*> allNodePointer=getAllNodePointer(nodeNum);
	for(size_t i=0;i<allNodePointer.size();i++)
	{
		char* name=qpg_NDE_name(allNodePointer[i]);
		string node_name(name);
		allNodeId.push_back(node_name);
	}
	return allNodeId;
}

vector<NODE*> RoadNetInfo::getAllNodePointer(int nodeNum)
{
	vector<NODE*> allNodePointer;
	for (int i = 0; i < nodeNum; i++)
	{
		NODE* pNode = qpg_NET_nodeByIndex(i + 1);
		allNodePointer.push_back(pNode);
	}
	return allNodePointer;
}

void RoadNetInfo::getAllDetectorPointer(int detectorNum)
{
	allDetectorPointer.clear();
	for (int i = 0; i < detectorNum; i++)
	{
		DETECTOR* pDetector = qpg_NET_detectorByIndex(i + 1);
		allDetectorPointer.push_back(pDetector);
	}
}

void RoadNetInfo::getAllDetectorId(int detectorNum)
{
	//vector<string> allDetectorId;
	//vector<DETECTOR*> allDetectorPointer = getAllDetectorPointer(detectorNum);
	allDetectorId.clear();
	allDetectorIdByPointer.clear();
	for (int i = 0; i < detectorNum; i++)
	{
		string name = qpg_DTC_name(allDetectorPointer[i]);
		string detector_name(name);
		allDetectorId.push_back(detector_name);
		//allDetectorIdByPointer插入元素
		allDetectorIdByPointer[allDetectorPointer[i]] = detector_name;
	}
}

bool RoadNetInfo::IsRoadNetModified(VspdCToMySQL* mysql,string net_name)
{
	//查询已知路网的节点数，子区数，检测器数
	string SQL = "SELECT * FROM  roadnetinfo WHERE  RoadNetId= ";
	SQL = SQL + "'" + net_name + "'";
	string Msg;
	vector<vector<string>>  res = mysql->SelectData(SQL.c_str(), 7, Msg);
	int node_num = str2int(res[0][3]);
	int link_num = str2int(res[0][4]);
	int subzone_num = str2int(res[0][5]);
	if (node_num != nodeNum || link_num != linkNum || subzone_num != zoneNum) //路网修改过
	{
		return 1;
	}
	return 0;
	
}

void RoadNetInfo::updateRoadNetInfoTable(VspdCToMySQL* mysql,string net_name)
{
	string SQL = "UPDATE roadnetinfo SET ";
	SQL = SQL + " NodeNum= " + "'" + int2str(nodeNum) + "'";
	SQL = SQL + ", LinkNum= " + "'" + int2str(linkNum) + "'";
	SQL = SQL + ", SubzoneNum= " + "'" + int2str(zoneNum) + "'";
	SQL = SQL + " WHERE " + " RoadNetId= " + "'" + net_name + "'";
	string Msg;
	mysql->UpdateData(SQL.c_str(), Msg);
}

void RoadNetInfo::updateRoadInfo(VspdCToMySQL* mysql)
{
	/*****************************节点信息表更新**************************************/
	//获取所有节点指针
	vector<NODE*> allNodePointer = RoadNetInfo::getAllNodePointer(nodeNum);
	//获取所有节点Id
	vector<string> allNodeId = RoadNetInfo::getAllNodeId(nodeNum);


	//解析所有路网节点Id
	for (size_t i = 0; i<allNodeId.size(); i++)
	{
		//调试信息
		if (allNodeId[i].size() != 5 && allNodeId[i].size() != 12)
		{
			CString message_temp(allNodeId[i].c_str());

			MessageBox(NULL, message_temp, "告知", MB_OK);
			continue;
		}
		//路口节点或小区节点
		if (allNodeId[i].size() == 5)
		{
			//Id末两位为0 路口节点
			if (allNodeId[i][3] == '0' && allNodeId[i][4] == '0')
			{
				//get与该节点相连节点数目
				int con_num = qpg_NDE_links(allNodePointer[i]);

				//路口数据写入数据库
				NodeInfo node(allNodeId[i], "", 0, 1, con_num, 1, 0, "");
				node.writeDataToSql(mysql);
			}
			//Id末两位不全为0 小区节点
			else
			{
				//判断是否单向 0 双向  1单向
				if (allNodeId[i][3] == '0')      //双向
				{
					NodeInfo node(allNodeId[i], "", 1, 0, 1, 0, 0, "");
					node.writeDataToSql(mysql);
				}
				else                         //单向
				{
					NodeInfo node(allNodeId[i], "", 1, 0, 1, 0, 1, "");
					node.writeDataToSql(mysql);
				}
			}
		}
		//路口间节点(12位的路口间节点一定对应一条路段，取前10位作为路段id)
		else if (allNodeId[i].size() == 12)
		{
			/*
			//获取对应的两个路口id
			string node1=allNodeId[i].substr(0,5);
			string node2=allNodeId[i].substr(5,5);
			//路段id（小的节点编号在前，大的节点编号在后）
			string road_link_id;
			if(node1<node2)
			{
			road_link_id=node1+node2;
			}
			else
			{
			road_link_id=node2+node1;
			}
			*/
			//路口间节点数据写入数据库
			NodeInfo node(allNodeId[i], "", 0, 0, 0, 0, 0, "");
			node.writeDataToSql(mysql);

			/*******************************路段信息表更新******************************************/
			string node1 = allNodeId[i].substr(0, 5);
			string node2 = allNodeId[i].substr(5, 5);
			if (allNodeId[i][10] == '1')//单向路段 
			{
				string road_link_id = node1 + node2;
				//判断该id是否已经存入数据库，若没有，写入数据库
				if (LinkInfo::IsRoadLinkIdExist(road_link_id) == 0)
				{
					string start_node = node1;
					string end_node = node2;
					int dis = 0;
					LinkInfo link(road_link_id, "", start_node, end_node, dis);
					link.writeDataToSql(mysql);
				}

			}
			else    //双向路段
			{

				string road_link_id_1 = node1 + node2;
				if (LinkInfo::IsRoadLinkIdExist(road_link_id_1) == 0)
				{
					string start_node_1 = node1;
					string end_node_1 = node2;
					int dis_1 = 0;
					LinkInfo link_1(road_link_id_1, "", start_node_1, end_node_1, dis_1);
					link_1.writeDataToSql(mysql);
				}

				string road_link_id_2 = node2 + node1;
				if (LinkInfo::IsRoadLinkIdExist(road_link_id_2) == 0)
				{
					string start_node_2 = node2;
					string end_node_2 = node1;
					int dis_2 = 0;
					LinkInfo link_2(road_link_id_2, "", start_node_2, end_node_2, dis_2);
					link_2.writeDataToSql(mysql);
				}

			}

		}
	}

	MessageBox(NULL, "节点信息表、路段信息表数据库成功", "告知5", MB_OK);

	/*****************************************检测器表更新***************************************************/
	// 获取所有检测器指针
//	vector<DETECTOR*> allDetectorPointer = RoadNetInfo::getAllDetectorPointer(detectorNum);
	//获取所有节点Id
//	vector<string> allDetectorId = RoadNetInfo::getAllDetectorId(detectorNum);

	//遍历所有的检测器(检测器id一定是12位的)
	for (size_t i = 0; i < allDetectorId.size(); i++)
	{

		if (allDetectorId[i].size() != 12)
		{
			CString message5(allDetectorId[i].c_str());

			MessageBox(NULL, message5, "检测器编号", MB_OK);
			continue;
		}


		//检测器id前10位为所属路段编号
		string road_link_id = allDetectorId[i].substr(0, 10);
		//第11位为上中下游标识
		int flag = allDetectorId[i][10] - 0x30;
		//检测车道数
		int startLane = qpg_DTC_lane(allDetectorPointer[i]);
		int endLane = qpg_DTC_end_lane(allDetectorPointer[i]);
		int lane_num = endLane - startLane + 1;
		//所属路口(下游检测器)
		string crossing;
		if (flag == 3)
			crossing = allDetectorId[i].substr(5, 5);
		//下游检测器编号
		int down_stream_index = allDetectorId[i][11] - 0x30;
		Detector detector(allDetectorId[i], "", road_link_id, flag, down_stream_index, crossing, lane_num);
		detector.writeDataToSql(mysql);
	}
	MessageBox(NULL, "检测器表写入成功", "告知6", MB_OK);

	/**************************检测断面表更新******************************/
	//获取所有中游标识检测器对应的路段id
	set<string> link_id = Detector::getLinkIdWhenFlagEqualsTwo(mysql);
	//遍历路段id集合
	for (set<string>::iterator it = link_id.begin(); it != link_id.end();)
	{
		string id = *it;
		//交换路段起点终点id，得到反向路段id
		string node1 = id.substr(0, 5);
		string node2 = id.substr(5, 5);
		string id2 = node2 + node1;
		//查找反向是否在集合中
		set<string>::iterator it2 = link_id.find(id2);

		int is_two_way;
		string link_id_1, detector_id_1, link_id_2, detector_id_2;

		if (it2 != link_id.end())  //双向 
		{
			//双向路段，添加正反两个方向的路段id和检测器id
			is_two_way = 1;
			link_id_1 = *it;
			detector_id_1 = *it + "2" + "1";
			link_id_2 = *it2;
			detector_id_2 = *it2 + "2" + "1";
			//从集合中删除这两个id
			link_id.erase(it2);
			it = link_id.erase(it);
		}

		else   //单向
		{
			//单向路段只添加一个方向的路段id和检测器id
			is_two_way = 0;
			link_id_1 = *it;
			detector_id_1 = *it + "2" + "1";
			link_id_2 = "";
			detector_id_2 = "";
			//删除这个id
			it = link_id.erase(it);
		}
		//写数据库
		Section section("", is_two_way, link_id_1, detector_id_1, link_id_2, detector_id_2);
		section.writeDataToSql(mysql);

	}
	MessageBox(NULL, "检测断面表写入成功", "告知6", MB_OK);
}

void RoadNetInfo::clearTable(VspdCToMySQL* mysql)
{
	string Msg;
	//清空数据库表
	mysql->ClearTable("detector", Msg);
	mysql->ClearTable("linkinfo", Msg);
	mysql->ClearTable("nodeinfo", Msg);
	mysql->ClearTable("section", Msg);
}



//初始化countEveryLoop，countEveryLoopDiff occupancyEveryLoop isOccupiedEveryLoop occupancyEveryLoopDuration velocityEveryLoopDuration

void RoadNetInfo::initCountLoop()
{
	countEveryLoop.clear();
	countEveryLoopDuration.clear();
	countEveryLoopDiff.clear();
	occupancyEveryLoop.clear();
	isOccupiedEveryLoop.clear();
	occupancyEveryLoopDuration.clear();
	velocityEveryLoop.clear();
	velocityEveryLoopDuration.clear();

	vector<int> everyDetectorCount;
	vector<float> everyDetectorOccupancy;
	for (int i = 0; i < detectorNum; i++)
	{
		everyDetectorCount.clear();
		everyDetectorOccupancy.clear();
		for (int j = 0; j < loopNumArray[i]; j++)
		{
			//int count = qpg_DTL_count(netLoops[i][j],0);
			everyDetectorCount.push_back(0);
			everyDetectorOccupancy.push_back(0.0);
		}
		countEveryLoop.push_back(everyDetectorCount);
		countEveryLoopDuration.push_back(everyDetectorCount);
		countEveryLoopDiff.push_back(everyDetectorCount);
		occupancyEveryLoop.push_back(everyDetectorOccupancy);
		occupancyEveryLoopDuration.push_back(everyDetectorOccupancy);
		isOccupiedEveryLoop.push_back(everyDetectorCount);
		velocityEveryLoop.push_back(everyDetectorOccupancy);
		velocityEveryLoopDuration.push_back(everyDetectorOccupancy);
	}

}
//初始化countEveryDetector
void RoadNetInfo::initCountDetector()
{
	countEveryDetector.resize(detectorNum);
}

void RoadNetInfo::initDemandMatrix()
{
	vector<float> row;
	row.resize(zoneNum);
	for (int i = 0; i < zoneNum; i++)
	{
		demandMatrix.push_back(row);
	}

	for (int i = 0; i < zoneNum; i++)
	{
		for (int j = 0; j < zoneNum; j++)
		{
			if (i != j)
			{
				demandMatrix[i][j] = qpg_DMD_demand(1, i + 1, j + 1);
			}
		}
	}
}

void RoadNetInfo::setDemandMatrix(float od_value)
{
	for (int i = 0; i < zoneNum; i++)
	{
		for (int j = 0; j < zoneNum; j++)
		{
			if (i != j)
			{
				demandMatrix[i][j] = od_value*demandMatrix[i][j];

				qps_DMD_demand(1, i+1, j+1, demandMatrix[i][j]);
			}
		}
	}
}
