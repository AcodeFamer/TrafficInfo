#include "stdafx.h"
#include "RoadAnalysis.h"

/****************************************解析所有link*****************************************************/
void RoadAnalysis::analyseLink()
{
	//获取所有的link指针
	vector<LINK*> allLinkPointer = getAllLinkPointer(LinkNum);

	set<string> allstring;
	//遍历所有link(两个node相连，获取到的是两个link )
	for (int i = 0; i < LinkNum; i++)
	{
		//获取该LINK的两个NODE指针
		NODE* nodeA = qpg_LNK_nodeStart(allLinkPointer[i]);
		NODE* nodeB = qpg_LNK_nodeEnd(allLinkPointer[i]);

		//获取StartNode和EndNode对应的id
		string start_node = qpg_NDE_name(nodeA);
		string end_node = qpg_NDE_name(nodeB);
		//获取该link的长度
		float dis = qpg_LNK_length(allLinkPointer[i]);
		string road_id;  //所属路段id
		//获取link对应路段id
		if (start_node.size() == 12 && end_node.size() == 12)  //两个都是路口间节点或是路口小区间节点
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
		//若找到一条link，则存入allLink中
		if (road_id.size() > 0)
		{
			LinkInfo link_info(start_node, end_node, road_id, dis);
			allLink.push_back(link_info);
		}
	}
	
	//数据写入数据库
	db_oper->dataWriteToDatabase("linkinfo", allLink);
}

/****************************************解析所有节点***************************************************************/
void RoadAnalysis::analyseNode()
{
	/*****************************节点信息表更新**************************************/
	//获取所有节点指针
	vector<NODE*> allNodePointer = getAllNodePointer(NodeNum);
	//获取所有节点Id
	vector<string> allNodeId = getAllNodeId(NodeNum);

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
				//路口初始化未被信号化
				int is_singal = 0;
				//**********************************************路口车流表  控制状态查询表**************************************************
				//每个路口的入link数和出link数
				int entry_links = qpg_NDE_entryLinks(allNodePointer[i]);
				int exit_links = qpg_NDE_exitLinks(allNodePointer[i]);
				qps_GUI_printf("in=%d,out=%d", entry_links, exit_links);
				int stream_count = 0;//车流编号
				//将该路口的入link和出link两两配对组成路口车流信息
				for (int in_index = 0; in_index < entry_links; in_index++)
				{
					for (int out_index = 0; out_index < exit_links; out_index++)
					{
						//相应的进出link指针
						LINK* link_in = qpg_NDE_linkEntry(allNodePointer[i], in_index + 1);
						LINK* link_out = qpg_NDE_link(allNodePointer[i], out_index + 1);
						//初始化所有的车流权限为BARRED
						qps_LNK_priority(link_in, link_out, APIPRI_MAJOR);
						string priority="BARRED";
						//入link、出link所属的路段id
					    string road_id_in, road_id_out;
						//获取入link、出link对应的LinkIndex  和  所属的路段id(road_id_in,road_id_out)
						int link_in_index = db_oper->getLinkInfo(1, link_in, road_id_in);
						int link_out_index = db_oper->getLinkInfo(2, link_out, road_id_out);
						//获取成功，数据加入allCrossingStream
						if (link_in_index > 0 && link_out_index > 0)
						{
							//路口车流数据添加
							CrossingStream cs(allNodeId[i], int2str(link_in_index), int2str(link_out_index), road_id_in, road_id_out, priority);
							allCrossingStream.push_back(cs);
							//控制状态数据
							stream_count++;//计算车流编号
							ControlState constat(allNodeId[i], int2str(stream_count), road_id_in, road_id_out, priority);
							allControlState.push_back(constat);
						}
					}
				}

				//路口数据添加
				NodeInfo node ( allNodeId[i], "", 0, 1, con_num, is_singal, 0, "" );
				allNode.push_back(node);

			}
			//Id末两位不全为0 小区节点
			else
			{
				//判断是否单向 0 双向  1单向
				if (allNodeId[i][3] == '0')      //双向
				{
					NodeInfo node (allNodeId[i], "", 1, 0, 1, 0, 0, "" );
					allNode.push_back(node);
				}
				else                         //单向
				{
					NodeInfo node (allNodeId[i], "", 1, 0, 1, 0, 1, "" );
					allNode.push_back(node);
				}
			}
		}
		//路口间节点(12位的路口间节点一定对应一条路段，取前10位作为路段id)
		else if (allNodeId[i].size() == 12)
		{
			//路口间节点数据写入数据库
			NodeInfo node (allNodeId[i], "", 0, 0, 0, 0, 0, "" );
			allNode.push_back(node);

			/*******************************路段信息表更新******************************************/
			string node1 = allNodeId[i].substr(0, 5);
			string node2 = allNodeId[i].substr(5, 5);

			
			//查询连接明细表中所有所属路段为该路段id的所有link的长度
			vector<vector<string>> res = db_oper->getLinkDistance(node1+node2);
			//计算路段长度(累加它们的距离)
			float road_dis = 0;
			for (size_t res_i = 0; res_i < res.size(); res_i++)
			{
				road_dis += (float)atof(res[res_i][0].c_str());
			}

			if (allNodeId[i][10] == '1')//单向路段 
			{
				string road_link_id = node1 + node2;
				//判断该id是否已经存入数据库，若没有，写入数据库
				if (RoadAnalysis::IsRoadLinkIdExist(road_link_id) == 0)
				{
					string start_node = node1;
					string end_node = node2;
					float dis = road_dis;
					RoadInfo road (road_link_id, "", start_node, end_node, dis );
					allRoad.push_back(road);
				}
			}
			else    //双向路段
			{

				string road_link_id_1 = node1 + node2;
				if (RoadAnalysis::IsRoadLinkIdExist(road_link_id_1) == 0)
				{
					string start_node_1 = node1;
					string end_node_1 = node2;
					float dis_1 = road_dis;
					RoadInfo road_1 ( road_link_id_1, "", start_node_1, end_node_1, dis_1 );
					allRoad.push_back(road_1);
				}
				string road_link_id_2 = node2 + node1;
				if (RoadAnalysis::IsRoadLinkIdExist(road_link_id_2) == 0)
				{
					string start_node_2 = node2;
					string end_node_2 = node1;
					float dis_2 = road_dis;
					RoadInfo road_2( road_link_id_2, "", start_node_2, end_node_2, dis_2 );
					allRoad.push_back(road_2);
				}

			}

		}
	}
	

	//相关数据写入数据库
	db_oper->dataWriteToDatabase("nodeinfo", allNode);
	db_oper->dataWriteToDatabase("roadinfo", allRoad);
	db_oper->dataWriteToDatabase("crossingstream", allCrossingStream);
	db_oper->dataWriteToDatabase("controlstate", allControlState);
	//db_oper.dataWriteToDatabase("controlplan",allControlPlan);
	//db_oper.dataWriteToDatabase("phase", allPhase);
}


/****************************************解析所有相位***************************************************************/
void RoadAnalysis::analysePhase()
{
	//****************************************相位车流明细表**************************************************
	//相位表中记录的条数
	int phaseSum = allPhase.size();

	//对于每一个相位,从相位表中获取控制方案编号，相位序号，所属路口信息
	for (int phase_i = 0; phase_i < phaseSum; phase_i++)
	{
		int plan_index;
		string phase_id, crossing_id;
		//获取phase表中指定相位编号PhaseIndex的控制方案编号(函数返回值，若为0表示获取失败)，相位序号，所属路口信息
		plan_index = db_oper->getPhaseInfo(phase_i + 1, phase_id, crossing_id);

		//根据所属路口查询路口车流表中满足该路口id的所有流入路段id和流出路段id,以及权限情况
		vector<vector<string>> res_crossingstream = db_oper->getCrossStreamInfo(crossing_id);
		for (size_t crossingstream_i = 0; crossingstream_i < res_crossingstream.size(); crossingstream_i++)
		{
			string stream_index = res_crossingstream[crossingstream_i][0];
			string link_in_id = res_crossingstream[crossingstream_i][1];
			string link_out_id = res_crossingstream[crossingstream_i][2];
			string priority = res_crossingstream[crossingstream_i][3];
			//相位车流数据保存
			PhaseStream ps(int2str(phase_i), stream_index, priority, "", phase_id, int2str(plan_index), crossing_id, link_in_id, link_out_id);
			allPhaseStream.push_back(ps);
		}
	}
	
	//相关数据写入数据库
	db_oper->dataWriteToDatabase("phasestream", allPhaseStream);
}

/****************************************解析所有检测器***************************************************************/
void RoadAnalysis::analyseDetector()
{
	/*****************************************检测器表更新***************************************************/
	// 获取所有检测器指针
	//	vector<DETECTOR*> allDetectorPointer = RoadNetInfo::getAllDetectorPointer(detectorNum);
	//获取所有节点Id
	//	vector<string> allDetectorId = RoadNetInfo::getAllDetectorId(detectorNum);

	//遍历所有的检测器(检测器id一定是12位的)
	for (size_t i = 0; i < allDetectorId.size(); i++)
	{
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
		Detector detector ( allDetectorId[i], "", road_link_id, flag, down_stream_index, crossing, lane_num );
		allDetector.push_back(detector);
	}
	qps_GUI_printf("detector success");

	/**************************检测断面表更新******************************/
	//获取所有中游标识检测器对应的路段id
	set<string> link_id = db_oper->getLinkIdWhenFlagEqualsTwo();
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
		Section section ( "", is_two_way, link_id_1, detector_id_1, link_id_2, detector_id_2 );
		allSection.push_back(section);
	}

	//数据写入数据库
	db_oper->dataWriteToDatabase("detector", allDetector);
	
}

/****************************************解析所有断面***************************************************************/
void RoadAnalysis::analyseSection()
{
	/**************************检测断面表更新******************************/
	//获取所有中游标识检测器对应的路段id
	set<string> link_id = db_oper->getLinkIdWhenFlagEqualsTwo();
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
		//section加入allSection中
		Section section("", is_two_way, link_id_1, detector_id_1, link_id_2, detector_id_2);
		allSection.push_back(section);
	}
	//更新数据库
	db_oper->dataWriteToDatabase("section", allSection);
}

RoadAnalysis::RoadAnalysis()
{
	db_oper = new DBoperation();
}

RoadAnalysis::~RoadAnalysis()
{
	delete db_oper;
}

DBoperation* RoadAnalysis::getDBoperation()
{
	return db_oper;
}





vector<LINK*> RoadAnalysis::getAllLinkPointer(int LinkNum)
{
	vector<LINK*> allLinkPointer;
	for (int i = 0; i < LinkNum; i++)
	{
		LINK* pLink = qpg_NET_linkByIndex(i + 1);
		allLinkPointer.push_back(pLink);
	}
	return allLinkPointer;
}

vector<NODE*> RoadAnalysis::getAllNodePointer(int nodeNum)
{
	vector<NODE*> allNodePointer;
	for (int i = 0; i < nodeNum; i++)
	{
		NODE* pNode = qpg_NET_nodeByIndex(i + 1);
		allNodePointer.push_back(pNode);
	}
	return allNodePointer;
}

vector<string> RoadAnalysis::getAllNodeId(int nodeNum)
{
	vector<string> allNodeId;
	//获取所有节点指针
	vector<NODE*> allNodePointer = getAllNodePointer(nodeNum);
	for (size_t i = 0; i < allNodePointer.size(); i++)
	{
		char* name = qpg_NDE_name(allNodePointer[i]);
		string node_name(name);
		allNodeId.push_back(node_name);
	}
	return allNodeId;
}

int RoadAnalysis::IsRoadLinkIdExist(string road_link_id)
{
	for (size_t i = 0; i < allRoad.size(); i++)
	{
		if (allRoad[i].RoadId == road_link_id)
		{
			return 1;
		}
	}
	return 0;
}


void RoadAnalysis::getAllDetectorPointer(int detectorNum)
{
	allDetectorPointer.clear();
	for (int i = 0; i < detectorNum; i++)
	{
		DETECTOR* pDetector = qpg_NET_detectorByIndex(i + 1);
		allDetectorPointer.push_back(pDetector);
	}
}

void RoadAnalysis::getAllDetectorId(int detectorNum)
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

bool RoadAnalysis::isNewRoadNet(string road_name)
{
	//从数据库中取出所有路网名称
	vector<string> allNetName = db_oper->getAllNetId();

	for (size_t i = 0; i < allNetName.size(); i++)
	{
		if (road_name == allNetName[i])
		{
			return false;
		}
	}
	return true;
}

void RoadAnalysis::updateRoadNetData()
{
	//解析link
	analyseLink();
	//解析node
	analyseNode();
	//解析相位
	//analysePhase();
	//解析detector
	analyseDetector();
	//解析section
	analyseSection();
}

