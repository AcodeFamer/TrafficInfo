#include "stdafx.h"
#include "RoadNetInfo.h"
#include <set>

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


map<string, NODE*> RoadNetInfo::AllSignalisedNode;


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

vector<LINK*> RoadNetInfo::getAllLinkPointer(int LinkNum)
{
	vector<LINK*> allLinkPointer;
	for (int i = 0; i < LinkNum; i++)
	{
		LINK* pLink = qpg_NET_linkByIndex(i + 1);
		allLinkPointer.push_back(pLink);
	}
	return allLinkPointer;
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
	/*****************************************连接明细表更新***************************************************/
	//获取所有的link指针
	vector<LINK*> allLinkPointer = getAllLinkPointer(linkNum);

	set<string> allstring;
	//遍历所有link(两个node相连，获取到的是两个link )
	for (int i = 0; i < linkNum; i++)
	{
		//获取该LINK的两个NODE指针
		NODE* nodeA = qpg_LNK_nodeStart(allLinkPointer[i]);
		NODE* nodeB = qpg_LNK_nodeEnd(allLinkPointer[i]);
		//获取对应id

		string start_node = qpg_NDE_name(nodeA);
		string end_node = qpg_NDE_name(nodeB);
		float dis = qpg_LNK_length(allLinkPointer[i]);   //路段长度
		string road_id;  //所属路段id
		//获取link对应路段id（适用：路口与路口间节点按照路口id从小到大依次编号，路口与小区间节点按照从小区到路口方向编号）
		
		if (start_node.size() == 12 && end_node.size()==12)  //两个都是路口间节点或是路口小区间节点
		{
			//单向路段时，路口间节点前十位直接表示路段
			if (start_node[10] == '1')  
			{
				//当节点编号增大时，与路段方向一致
				if (start_node[11] < end_node[11])
				{
					road_id = start_node.substr(0, 10);
				}
			}
			//双向路段时，路口间节点前十位由小路口节点id在前，大路口节点id在后
			else
			{
				if (start_node[11] < end_node[11])
				{
					road_id = start_node.substr(0, 10);
				}
				else
				{
					road_id = start_node.substr(5, 5) + start_node.substr(0, 5);
				}
			}
		}

		else
		{
			if (start_node.size() == 12 && end_node.size() == 5)
			{
				//单向路段时，路口间节点前十位直接表示路段
				if (start_node[10] == '1')
				{
					//路段后五位是end_node，方向一致
					if (start_node.substr(5, 5) == end_node)
					{
						road_id = start_node.substr(0, 10);
					}
				}
				else
				{
					//双向路段时，路口间节点前十位从小到大
					if (start_node.substr(5, 5) == end_node)
					{
						road_id = start_node.substr(0, 10);
					}
					else
					{
						road_id = start_node.substr(5, 5) + start_node.substr(0, 5);
					}
				}
			}
			else
			{
				if (end_node[10] == '1')
				{
					if (end_node.substr(0, 5) == start_node)
					{
						road_id = end_node.substr(0, 10);
					}
				}
				else
				{
					if (end_node.substr(0, 5) == start_node)
					{
						road_id = end_node.substr(0, 10);
					}
					else
					{
						road_id = end_node.substr(5, 5) + end_node.substr(0, 5);
					}
				}
			}
		}

		if (road_id.size() > 0)
		{
			LinkInfo link_info(start_node, end_node, road_id, dis);
			link_info.writeDataToSql(mysql);
		}
		
	}

	qps_GUI_printf("linkinfo success");

	qps_GUI_printf("linkNum=%d,allstring=%d",linkNum,allstring.size());
	/*****************************节点信息表更新**************************************/
	//获取所有节点指针
	vector<NODE*> allNodePointer = RoadNetInfo::getAllNodePointer(nodeNum);
	//获取所有节点Id
	vector<string> allNodeId = RoadNetInfo::getAllNodeId(nodeNum);


	//解析所有路网节点Id
	for (size_t i = 0; i<allNodeId.size(); i++)
	{
		//路口节点或小区节点
		if (allNodeId[i].size() == 5)
		{
			//Id末两位为0 路口节点
			if (allNodeId[i][3] == '0' && allNodeId[i][4] == '0')
			{
				//get与该节点相连节点数目
				int con_num = qpg_NDE_links(allNodePointer[i]);

				int is_singal;
				if (qpg_NDE_signalised(allNodePointer[i]) == TRUE)  //该路口信号化，写控制方案表
				{
					is_singal = 1;
					
					//该信号化的节点加入map
					AllSignalisedNode[allNodeId[i]] = allNodePointer[i];
					//设置该路口为可变周期
					qps_SIG_action(allNodePointer[i], 1, 0, API_ACTION_VARIABLE, API_ACTIONMODE_SET, 1);

					//**********************************************路口车流表**************************************************
					//每个路口的进入link数和出link数
					int entry_links = qpg_NDE_entryLinks(allNodePointer[i]);
					int exit_links = qpg_NDE_exitLinks(allNodePointer[i]);
					qps_GUI_printf("in=%d,out=%d",entry_links,exit_links);
					for (int in = 0; in < entry_links; in++)
					{
						for (int out = 0; out < exit_links; out++)
						{
							//相应的进出link指针
							LINK* link_in = qpg_NDE_linkEntry(allNodePointer[i], in + 1);
							LINK* link_out = qpg_NDE_link(allNodePointer[i], out + 1);
							//获取priority
							int pri = qpg_LNK_priority(link_in, link_out);
							string priority;
							switch (pri)
							{
							case APIPRI_MAJOR:
								priority = "MAJOR";
								break;
							case APIPRI_MEDIUM:
								priority = "MEDIUM";
								break;
							case APIPRI_MINOR:
								priority = "MINOR";
								break;
							case APIPRI_BARRED:
								priority = "BARRED";
								break;
							default:
								;
							}
							string road_id_in, road_id_out;

							int link_in_index = LinkInfo::getLinkInfo(mysql, 1, link_in, road_id_in);
				
							int link_out_index = LinkInfo::getLinkInfo(mysql, 2, link_out, road_id_out);

							CrossingStream cs(allNodeId[i], int2str(link_in_index), int2str(link_out_index), road_id_in, road_id_out, priority);
							cs.writeDataToSql(mysql);
						}
					}

					//**********************************************控制方案表**************************************************
					//每个路口对应一个控制方案
					int phase_num = qpg_NDE_phases(allNodePointer[i]);//相位数
					float period;//周期
					qpg_SIG_inquiry(allNodePointer[i], 1, API_INQUIRY_CYCLE_TIME, &period);
					int is_period_fixed;  //是否固定周期
					if (qpg_NDE_variable(allNodePointer[i]))
					{
						is_period_fixed = 0;
					}
					else
					{
						is_period_fixed = 1;
					}
					float offset_time;
					qpg_SIG_inquiry(allNodePointer[i], 1, API_INQUIRY_OFFSET, &offset_time);
					ControlPlan cp(allNodeId[i], phase_num, is_period_fixed, 1 - is_period_fixed, period, offset_time, 0);
					cp.writeDataToSql(mysql);

					//**********************************************相位表**************************************************
					//对该控制方案的每一个相位，添加一条数据到相位表,查询controlplan中最后一条的编号
					
					char* SQL = "select PlanIndex from controlplan where PlanIndex=(select max(PlanIndex) from controlplan);";
					string Msg;
					vector<vector<string>> res = mysql->SelectData(SQL, 1, Msg);
					int plan_index;
					if (res.size() != 0)
					{
						plan_index = str2int(res[0][0]);
					}
				
					//遍历所有相位，查询对应的绿灯，红灯、黄灯时间
					for (int phase_i = 0; phase_i < phase_num; phase_i++)
					{
						float green_time,red_time,amber_time;
						qpg_SIG_inquiry(allNodePointer[i], phase_i + 1, API_INQUIRY_STORED_GREEN, &green_time);
						qpg_SIG_inquiry(allNodePointer[i], phase_i + 1, API_INQUIRY_STORED_RED, &red_time);
						amber_time = qpg_CFG_amberTime();
						green_time = green_time - amber_time; //获取到的绿灯时间中包含黄灯时间
						
						Phase p(plan_index, phase_i + 1, allNodeId[i], green_time, amber_time, red_time, 0);
						p.writeDataToSql(mysql);
					}
				}
				else
				{
					is_singal = 0;
				}
				//路口数据写入数据库
				NodeInfo node(allNodeId[i], "", 0, 1, con_num, is_singal, 0, "");
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
			//路口间节点数据写入数据库
			NodeInfo node(allNodeId[i], "", 0, 0, 0, 0, 0, "");
			node.writeDataToSql(mysql);

			/*******************************路段信息表更新******************************************/
			string node1 = allNodeId[i].substr(0, 5);
			string node2 = allNodeId[i].substr(5, 5);
			//计算路段长度(查询连接明细表中所有所属路段信息为该路段id的所有link，累加它们的距离)
			string SQL = "select Distance from linkinfo where RoadId=";
			SQL = SQL + "'" + node1+node2 + "'";
			string Msg;
			float road_dis = 0;
			vector<vector<string>> res = mysql->SelectData(SQL.c_str(), 1, Msg);
			for (size_t res_i = 0; res_i < res.size(); res_i++)
			{
				road_dis += (float)atof(res[res_i][0].c_str());
			}

			if (allNodeId[i][10] == '1')//单向路段 
			{
				string road_link_id = node1 + node2;
				//判断该id是否已经存入数据库，若没有，写入数据库
				if (RoadInfo::IsRoadLinkIdExist(road_link_id) == 0)
				{
					string start_node = node1;
					string end_node = node2;
					float dis = road_dis;
					RoadInfo link(road_link_id, "", start_node, end_node, dis);
					link.writeDataToSql(mysql);
				}
			}
			else    //双向路段
			{

				string road_link_id_1 = node1 + node2;
				if (RoadInfo::IsRoadLinkIdExist(road_link_id_1) == 0)
				{
					string start_node_1 = node1;
					string end_node_1 = node2;
					float dis_1 = road_dis;
					RoadInfo link_1(road_link_id_1, "", start_node_1, end_node_1, dis_1);
					link_1.writeDataToSql(mysql);
				}
				string road_link_id_2 = node2 + node1;
				if (RoadInfo::IsRoadLinkIdExist(road_link_id_2) == 0)
				{
					string start_node_2 = node2;
					string end_node_2 = node1;
					float dis_2 = road_dis;
					RoadInfo link_2(road_link_id_2, "", start_node_2, end_node_2, dis_2);
					link_2.writeDataToSql(mysql);
				}

			}

		}
	}

	
	//****************************************相位车流明细表**************************************************
	//查询相位表中记录的条数
	char* SQL = "select PhaseIndex from phase where PhaseIndex=(select max(PhaseIndex) from phase);";
	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL, 1, Msg);
	int phaseSum = str2int(res[0][0]);
	
	//对于每一个相位,从相位表中获取控制方案，相位序号，所属路口信息
	for (int phase_i = 0; phase_i < phaseSum; phase_i++)
	{
		string SQL_phase = "select PlanIndex,PhaseId,CrossingId from phase where PhaseIndex=";
		SQL_phase = SQL_phase + int2str(phase_i+1);
		vector<vector<string>> res_phase= mysql->SelectData(SQL_phase.c_str(), 3, Msg);

		string plan_index = res_phase[0][0];
		string phase_id = res_phase[0][1];
		string crossing_id = res_phase[0][2];

		/*
		CString mes;
		mes.Format("phase_i=%d,size=%d", phase_i,res_phase.size());
		MessageBox(NULL, mes, "", MB_OK);
		*/
		//根据所属路口查询路口车流表中满足该路口信息的所有流入路段id和流出路段id
		string SQL_crossingstream = "select StreamIndex,RoadInId,RoadOutId from crossingstream where CrossingId=";
		SQL_crossingstream = SQL_crossingstream + "'" + crossing_id + "'";
		vector<vector<string>> res_crossingstream = mysql->SelectData(SQL_crossingstream.c_str(), 3, Msg);
		for (size_t crossingstream_i = 0; crossingstream_i < res_crossingstream.size(); crossingstream_i++)
		{
			string stream_index = res_crossingstream[crossingstream_i][0];
			string link_in_id = res_crossingstream[crossingstream_i][1];
			string link_out_id = res_crossingstream[crossingstream_i][2];

			PhaseStream ps(int2str(phase_i), stream_index, "", phase_id, plan_index, crossing_id, link_in_id, link_out_id);
			ps.writeDataToSql(mysql);
		}
	}

	qps_GUI_printf("phaseSum=%d",phaseSum);
	
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
	qps_GUI_printf("detector success");

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
	qps_GUI_printf("section success");



}

void RoadNetInfo::clearTable(VspdCToMySQL* mysql)
{
	string Msg;

	

	//清空数据库表
	mysql->ClearTable("detector", Msg);
	mysql->ClearTable("roadinfo", Msg);
	mysql->ClearTable("nodeinfo", Msg);
	mysql->ClearTable("section", Msg);
	mysql->ClearTable("linkinfo", Msg);
	mysql->ClearTable("controlplan",Msg);
	mysql->ClearTable("phase", Msg);
	mysql->ClearTable("crossingstream", Msg);
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
