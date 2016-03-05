#include "stdafx.h"
#include "RoadAnalysis.h"

/****************************************��������link*****************************************************/
void RoadAnalysis::analyseLink()
{
	//��ȡ���е�linkָ��
	vector<LINK*> allLinkPointer = getAllLinkPointer(LinkNum);

	set<string> allstring;
	//��������link(����node��������ȡ����������link )
	for (int i = 0; i < LinkNum; i++)
	{
		//��ȡ��LINK������NODEָ��
		NODE* nodeA = qpg_LNK_nodeStart(allLinkPointer[i]);
		NODE* nodeB = qpg_LNK_nodeEnd(allLinkPointer[i]);

		//��ȡStartNode��EndNode��Ӧ��id
		string start_node = qpg_NDE_name(nodeA);
		string end_node = qpg_NDE_name(nodeB);
		//��ȡ��link�ĳ���
		float dis = qpg_LNK_length(allLinkPointer[i]);
		string road_id;  //����·��id
		//��ȡlink��Ӧ·��id
		if (start_node.size() == 12 && end_node.size() == 12)  //��������·�ڼ�ڵ����·��С����ڵ�
		{
			//����·��ʱ��·�ڼ�ڵ�ǰʮλֱ�ӱ�ʾ·��
			if (start_node[10] == '1')
			{
				//���ڵ�������ʱ����·�η���һ��
				if (start_node[11] < end_node[11])
				{
					road_id = start_node.substr(0, 10);
				}
			}
			//˫��·��ʱ��·�ڼ�ڵ�ǰʮλ��С·�ڽڵ�id��ǰ����·�ڽڵ�id�ں�
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
				//����·��ʱ��·�ڼ�ڵ�ǰʮλֱ�ӱ�ʾ·��
				if (start_node[10] == '1')
				{
					//·�κ���λ��end_node������һ��
					if (start_node.substr(5, 5) == end_node)
					{
						road_id = start_node.substr(0, 10);
					}
				}
				else
				{
					//˫��·��ʱ��·�ڼ�ڵ�ǰʮλ��С����
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
		//���ҵ�һ��link�������allLink��
		if (road_id.size() > 0)
		{
			LinkInfo link_info(start_node, end_node, road_id, dis);
			allLink.push_back(link_info);
		}
	}
	
	//����д�����ݿ�
	db_oper->dataWriteToDatabase("linkinfo", allLink);
}

/****************************************�������нڵ�***************************************************************/
void RoadAnalysis::analyseNode()
{
	/*****************************�ڵ���Ϣ�����**************************************/
	//��ȡ���нڵ�ָ��
	vector<NODE*> allNodePointer = getAllNodePointer(NodeNum);
	//��ȡ���нڵ�Id
	vector<string> allNodeId = getAllNodeId(NodeNum);

	//��������·���ڵ�Id
	for (size_t i = 0; i<allNodeId.size(); i++)
	{
		//·�ڽڵ��С���ڵ�
		if (allNodeId[i].size() == 5)
		{
			//Idĩ��λΪ0 ·�ڽڵ�
			if (allNodeId[i][3] == '0' && allNodeId[i][4] == '0')
			{
				//get��ýڵ������ڵ���Ŀ
				int con_num = qpg_NDE_links(allNodePointer[i]);
				//·�ڳ�ʼ��δ���źŻ�
				int is_singal = 0;
				//**********************************************·�ڳ�����  ����״̬��ѯ��**************************************************
				//ÿ��·�ڵ���link���ͳ�link��
				int entry_links = qpg_NDE_entryLinks(allNodePointer[i]);
				int exit_links = qpg_NDE_exitLinks(allNodePointer[i]);
				qps_GUI_printf("in=%d,out=%d", entry_links, exit_links);
				int stream_count = 0;//�������
				//����·�ڵ���link�ͳ�link����������·�ڳ�����Ϣ
				for (int in_index = 0; in_index < entry_links; in_index++)
				{
					for (int out_index = 0; out_index < exit_links; out_index++)
					{
						//��Ӧ�Ľ���linkָ��
						LINK* link_in = qpg_NDE_linkEntry(allNodePointer[i], in_index + 1);
						LINK* link_out = qpg_NDE_link(allNodePointer[i], out_index + 1);
						//��ʼ�����еĳ���Ȩ��ΪBARRED
						qps_LNK_priority(link_in, link_out, APIPRI_MAJOR);
						string priority="BARRED";
						//��link����link������·��id
					    string road_id_in, road_id_out;
						//��ȡ��link����link��Ӧ��LinkIndex  ��  ������·��id(road_id_in,road_id_out)
						int link_in_index = db_oper->getLinkInfo(1, link_in, road_id_in);
						int link_out_index = db_oper->getLinkInfo(2, link_out, road_id_out);
						//��ȡ�ɹ������ݼ���allCrossingStream
						if (link_in_index > 0 && link_out_index > 0)
						{
							//·�ڳ����������
							CrossingStream cs(allNodeId[i], int2str(link_in_index), int2str(link_out_index), road_id_in, road_id_out, priority);
							allCrossingStream.push_back(cs);
							//����״̬����
							stream_count++;//���㳵�����
							ControlState constat(allNodeId[i], int2str(stream_count), road_id_in, road_id_out, priority);
							allControlState.push_back(constat);
						}
					}
				}

				//·���������
				NodeInfo node ( allNodeId[i], "", 0, 1, con_num, is_singal, 0, "" );
				allNode.push_back(node);

			}
			//Idĩ��λ��ȫΪ0 С���ڵ�
			else
			{
				//�ж��Ƿ��� 0 ˫��  1����
				if (allNodeId[i][3] == '0')      //˫��
				{
					NodeInfo node (allNodeId[i], "", 1, 0, 1, 0, 0, "" );
					allNode.push_back(node);
				}
				else                         //����
				{
					NodeInfo node (allNodeId[i], "", 1, 0, 1, 0, 1, "" );
					allNode.push_back(node);
				}
			}
		}
		//·�ڼ�ڵ�(12λ��·�ڼ�ڵ�һ����Ӧһ��·�Σ�ȡǰ10λ��Ϊ·��id)
		else if (allNodeId[i].size() == 12)
		{
			//·�ڼ�ڵ�����д�����ݿ�
			NodeInfo node (allNodeId[i], "", 0, 0, 0, 0, 0, "" );
			allNode.push_back(node);

			/*******************************·����Ϣ�����******************************************/
			string node1 = allNodeId[i].substr(0, 5);
			string node2 = allNodeId[i].substr(5, 5);

			
			//��ѯ������ϸ������������·��Ϊ��·��id������link�ĳ���
			vector<vector<string>> res = db_oper->getLinkDistance(node1+node2);
			//����·�γ���(�ۼ����ǵľ���)
			float road_dis = 0;
			for (size_t res_i = 0; res_i < res.size(); res_i++)
			{
				road_dis += (float)atof(res[res_i][0].c_str());
			}

			if (allNodeId[i][10] == '1')//����·�� 
			{
				string road_link_id = node1 + node2;
				//�жϸ�id�Ƿ��Ѿ��������ݿ⣬��û�У�д�����ݿ�
				if (RoadAnalysis::IsRoadLinkIdExist(road_link_id) == 0)
				{
					string start_node = node1;
					string end_node = node2;
					float dis = road_dis;
					RoadInfo road (road_link_id, "", start_node, end_node, dis );
					allRoad.push_back(road);
				}
			}
			else    //˫��·��
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
	

	//�������д�����ݿ�
	db_oper->dataWriteToDatabase("nodeinfo", allNode);
	db_oper->dataWriteToDatabase("roadinfo", allRoad);
	db_oper->dataWriteToDatabase("crossingstream", allCrossingStream);
	db_oper->dataWriteToDatabase("controlstate", allControlState);
	//db_oper.dataWriteToDatabase("controlplan",allControlPlan);
	//db_oper.dataWriteToDatabase("phase", allPhase);
}


/****************************************����������λ***************************************************************/
void RoadAnalysis::analysePhase()
{
	//****************************************��λ������ϸ��**************************************************
	//��λ���м�¼������
	int phaseSum = allPhase.size();

	//����ÿһ����λ,����λ���л�ȡ���Ʒ�����ţ���λ��ţ�����·����Ϣ
	for (int phase_i = 0; phase_i < phaseSum; phase_i++)
	{
		int plan_index;
		string phase_id, crossing_id;
		//��ȡphase����ָ����λ���PhaseIndex�Ŀ��Ʒ������(��������ֵ����Ϊ0��ʾ��ȡʧ��)����λ��ţ�����·����Ϣ
		plan_index = db_oper->getPhaseInfo(phase_i + 1, phase_id, crossing_id);

		//��������·�ڲ�ѯ·�ڳ������������·��id����������·��id������·��id,�Լ�Ȩ�����
		vector<vector<string>> res_crossingstream = db_oper->getCrossStreamInfo(crossing_id);
		for (size_t crossingstream_i = 0; crossingstream_i < res_crossingstream.size(); crossingstream_i++)
		{
			string stream_index = res_crossingstream[crossingstream_i][0];
			string link_in_id = res_crossingstream[crossingstream_i][1];
			string link_out_id = res_crossingstream[crossingstream_i][2];
			string priority = res_crossingstream[crossingstream_i][3];
			//��λ�������ݱ���
			PhaseStream ps(int2str(phase_i), stream_index, priority, "", phase_id, int2str(plan_index), crossing_id, link_in_id, link_out_id);
			allPhaseStream.push_back(ps);
		}
	}
	
	//�������д�����ݿ�
	db_oper->dataWriteToDatabase("phasestream", allPhaseStream);
}

/****************************************�������м����***************************************************************/
void RoadAnalysis::analyseDetector()
{
	/*****************************************����������***************************************************/
	// ��ȡ���м����ָ��
	//	vector<DETECTOR*> allDetectorPointer = RoadNetInfo::getAllDetectorPointer(detectorNum);
	//��ȡ���нڵ�Id
	//	vector<string> allDetectorId = RoadNetInfo::getAllDetectorId(detectorNum);

	//�������еļ����(�����idһ����12λ��)
	for (size_t i = 0; i < allDetectorId.size(); i++)
	{
		//�����idǰ10λΪ����·�α��
		string road_link_id = allDetectorId[i].substr(0, 10);
		//��11λΪ�������α�ʶ
		int flag = allDetectorId[i][10] - 0x30;
		//��⳵����
		int startLane = qpg_DTC_lane(allDetectorPointer[i]);
		int endLane = qpg_DTC_end_lane(allDetectorPointer[i]);
		int lane_num = endLane - startLane + 1;
		//����·��(���μ����)
		string crossing;
		if (flag == 3)
			crossing = allDetectorId[i].substr(5, 5);
		//���μ�������
		int down_stream_index = allDetectorId[i][11] - 0x30;
		Detector detector ( allDetectorId[i], "", road_link_id, flag, down_stream_index, crossing, lane_num );
		allDetector.push_back(detector);
	}
	qps_GUI_printf("detector success");

	/**************************����������******************************/
	//��ȡ�������α�ʶ�������Ӧ��·��id
	set<string> link_id = db_oper->getLinkIdWhenFlagEqualsTwo();
	//����·��id����
	for (set<string>::iterator it = link_id.begin(); it != link_id.end();)
	{
		string id = *it;
		//����·������յ�id���õ�����·��id
		string node1 = id.substr(0, 5);
		string node2 = id.substr(5, 5);
		string id2 = node2 + node1;
		//���ҷ����Ƿ��ڼ�����
		set<string>::iterator it2 = link_id.find(id2);

		int is_two_way;
		string link_id_1, detector_id_1, link_id_2, detector_id_2;

		if (it2 != link_id.end())  //˫�� 
		{
			//˫��·�Σ�����������������·��id�ͼ����id
			is_two_way = 1;
			link_id_1 = *it;
			detector_id_1 = *it + "2" + "1";
			link_id_2 = *it2;
			detector_id_2 = *it2 + "2" + "1";
			//�Ӽ�����ɾ��������id
			link_id.erase(it2);
			it = link_id.erase(it);
		}

		else   //����
		{
			//����·��ֻ���һ�������·��id�ͼ����id
			is_two_way = 0;
			link_id_1 = *it;
			detector_id_1 = *it + "2" + "1";
			link_id_2 = "";
			detector_id_2 = "";
			//ɾ�����id
			it = link_id.erase(it);
		}
		//д���ݿ�
		Section section ( "", is_two_way, link_id_1, detector_id_1, link_id_2, detector_id_2 );
		allSection.push_back(section);
	}

	//����д�����ݿ�
	db_oper->dataWriteToDatabase("detector", allDetector);
	
}

/****************************************�������ж���***************************************************************/
void RoadAnalysis::analyseSection()
{
	/**************************����������******************************/
	//��ȡ�������α�ʶ�������Ӧ��·��id
	set<string> link_id = db_oper->getLinkIdWhenFlagEqualsTwo();
	//����·��id����
	for (set<string>::iterator it = link_id.begin(); it != link_id.end();)
	{
		string id = *it;
		//����·������յ�id���õ�����·��id
		string node1 = id.substr(0, 5);
		string node2 = id.substr(5, 5);
		string id2 = node2 + node1;
		//���ҷ����Ƿ��ڼ�����
		set<string>::iterator it2 = link_id.find(id2);

		int is_two_way;
		string link_id_1, detector_id_1, link_id_2, detector_id_2;

		if (it2 != link_id.end())  //˫�� 
		{
			//˫��·�Σ�����������������·��id�ͼ����id
			is_two_way = 1;
			link_id_1 = *it;
			detector_id_1 = *it + "2" + "1";
			link_id_2 = *it2;
			detector_id_2 = *it2 + "2" + "1";
			//�Ӽ�����ɾ��������id
			link_id.erase(it2);
			it = link_id.erase(it);
		}

		else   //����
		{
			//����·��ֻ���һ�������·��id�ͼ����id
			is_two_way = 0;
			link_id_1 = *it;
			detector_id_1 = *it + "2" + "1";
			link_id_2 = "";
			detector_id_2 = "";
			//ɾ�����id
			it = link_id.erase(it);
		}
		//section����allSection��
		Section section("", is_two_way, link_id_1, detector_id_1, link_id_2, detector_id_2);
		allSection.push_back(section);
	}
	//�������ݿ�
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
	//��ȡ���нڵ�ָ��
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
		//allDetectorIdByPointer����Ԫ��
		allDetectorIdByPointer[allDetectorPointer[i]] = detector_name;
	}
}

bool RoadAnalysis::isNewRoadNet(string road_name)
{
	//�����ݿ���ȡ������·������
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
	//����link
	analyseLink();
	//����node
	analyseNode();
	//������λ
	//analysePhase();
	//����detector
	analyseDetector();
	//����section
	analyseSection();
}

