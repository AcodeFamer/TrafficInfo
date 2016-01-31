#include "stdafx.h"
#include "RoadAnalysis.h"

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

				int is_singal;
				if (qpg_NDE_signalised(allNodePointer[i]) == TRUE)  //��·���źŻ���д���Ʒ�����
				{
					is_singal = 1;

					//���źŻ��Ľڵ����map
					//AllSignalisedNode[allNodeId[i]] = allNodePointer[i];
					//���ø�·��Ϊ�ɱ�����
					qps_SIG_action(allNodePointer[i], 1, 0, API_ACTION_VARIABLE, API_ACTIONMODE_SET, 1);

					//**********************************************·�ڳ�����**************************************************
					//ÿ��·�ڵĽ���link���ͳ�link��
					int entry_links = qpg_NDE_entryLinks(allNodePointer[i]);
					int exit_links = qpg_NDE_exitLinks(allNodePointer[i]);
					qps_GUI_printf("in=%d,out=%d", entry_links, exit_links);
					for (int in = 0; in < entry_links; in++)
					{
						for (int out = 0; out < exit_links; out++)
						{
							//��Ӧ�Ľ���linkָ��
							LINK* link_in = qpg_NDE_linkEntry(allNodePointer[i], in + 1);
							LINK* link_out = qpg_NDE_link(allNodePointer[i], out + 1);
							//��ȡpriority
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

							int link_in_index = db_oper.getLinkInfo(1, link_in, road_id_in);

							int link_out_index = db_oper.getLinkInfo(2, link_out, road_id_out);

							CrossingStream cs(allNodeId[i], int2str(link_in_index), int2str(link_out_index), road_id_in, road_id_out, priority );
							allCrossingStream.push_back(cs);
						}
					}

					//**********************************************���Ʒ�����**************************************************
					//ÿ��·�ڶ�Ӧһ�����Ʒ���
					int phase_num = qpg_NDE_phases(allNodePointer[i]);//��λ��
					float period;//����
					qpg_SIG_inquiry(allNodePointer[i], 1, API_INQUIRY_CYCLE_TIME, &period);
					int is_period_fixed;  //�Ƿ�̶�����
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
					ControlPlan cp (allNodeId[i], phase_num, is_period_fixed, 1 - is_period_fixed, period, offset_time, 0 );
					allControlPlan.push_back(cp);

					//**********************************************��λ��**************************************************
					//�Ըÿ��Ʒ�����ÿһ����λ�����һ�����ݵ���λ��,��ѯcontrolplan�����һ���ı��

					char* SQL = "select PlanIndex from controlplan where PlanIndex=(select max(PlanIndex) from controlplan);";
					string Msg;
					vector<vector<string>> res = db_oper.getMySql()->SelectData(SQL, 1, Msg);
					int plan_index;
					if (res.size() != 0)
					{
						plan_index = str2int(res[0][0]);
					}

					//����������λ����ѯ��Ӧ���̵ƣ���ơ��Ƶ�ʱ��
					for (int phase_i = 0; phase_i < phase_num; phase_i++)
					{
						float green_time, red_time, amber_time;
						qpg_SIG_inquiry(allNodePointer[i], phase_i + 1, API_INQUIRY_STORED_GREEN, &green_time);
						qpg_SIG_inquiry(allNodePointer[i], phase_i + 1, API_INQUIRY_STORED_RED, &red_time);
						amber_time = qpg_CFG_amberTime();
						green_time = green_time - amber_time; //��ȡ�����̵�ʱ���а����Ƶ�ʱ��

					    Phase p (plan_index, phase_i + 1, allNodeId[i], green_time, amber_time, red_time, 0 );
						allPhase.push_back(p);
					}
				}
				else
				{
					is_singal = 0;
				}
				//·������д�����ݿ�
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
			//����·�γ���(��ѯ������ϸ������������·����ϢΪ��·��id������link���ۼ����ǵľ���)
			string SQL = "select Distance from linkinfo where RoadId=";
			SQL = SQL + "'" + node1 + node2 + "'";
			string Msg;
			float road_dis = 0;
			vector<vector<string>> res = db_oper.getMySql()->SelectData(SQL.c_str(), 1, Msg);
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



	//****************************************��λ������ϸ��**************************************************
	//��ѯ��λ���м�¼������
	char* SQL = "select PhaseIndex from phase where PhaseIndex=(select max(PhaseIndex) from phase);";
	string Msg;
	vector<vector<string>> res = db_oper.getMySql()->SelectData(SQL, 1, Msg);
	int phaseSum = str2int(res[0][0]);

	//����ÿһ����λ,����λ���л�ȡ���Ʒ�������λ��ţ�����·����Ϣ
	for (int phase_i = 0; phase_i < phaseSum; phase_i++)
	{
		string SQL_phase = "select PlanIndex,PhaseId,CrossingId from phase where PhaseIndex=";
		SQL_phase = SQL_phase + int2str(phase_i + 1);
		vector<vector<string>> res_phase = db_oper.getMySql()->SelectData(SQL_phase.c_str(), 3, Msg);

		string plan_index = res_phase[0][0];
		string phase_id = res_phase[0][1];
		string crossing_id = res_phase[0][2];

		/*
		CString mes;
		mes.Format("phase_i=%d,size=%d", phase_i,res_phase.size());
		MessageBox(NULL, mes, "", MB_OK);
		*/
		//��������·�ڲ�ѯ·�ڳ������������·����Ϣ����������·��id������·��id
		string SQL_crossingstream = "select StreamIndex,RoadInId,RoadOutId from crossingstream where CrossingId=";
		SQL_crossingstream = SQL_crossingstream + "'" + crossing_id + "'";
		vector<vector<string>> res_crossingstream = db_oper.getMySql()->SelectData(SQL_crossingstream.c_str(), 3, Msg);
		for (size_t crossingstream_i = 0; crossingstream_i < res_crossingstream.size(); crossingstream_i++)
		{
			string stream_index = res_crossingstream[crossingstream_i][0];
			string link_in_id = res_crossingstream[crossingstream_i][1];
			string link_out_id = res_crossingstream[crossingstream_i][2];

			PhaseStream ps ( int2str(phase_i), stream_index, "", phase_id, plan_index, crossing_id, link_in_id, link_out_id );
			allPhaseStream.push_back(ps);
		}
	}
}



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

		if (allDetectorId[i].size() != 12)
		{
			CString message5(allDetectorId[i].c_str());

			MessageBox(NULL, message5, "��������", MB_OK);
			continue;
		}


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
	set<string> link_id = db_oper.getLinkIdWhenFlagEqualsTwo();
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
}

RoadAnalysis::RoadAnalysis()
{

}

RoadAnalysis::~RoadAnalysis()
{

}

DBoperation RoadAnalysis::getDBoperation()
{
	return db_oper;
}

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
		//��ȡ��Ӧid

		string start_node = qpg_NDE_name(nodeA);
		string end_node = qpg_NDE_name(nodeB);
		float dis = qpg_LNK_length(allLinkPointer[i]);   //·�γ���
		string road_id;  //����·��id
		//��ȡlink��Ӧ·��id�����ã�·����·�ڼ�ڵ㰴��·��id��С�������α�ţ�·����С����ڵ㰴�մ�С����·�ڷ����ţ�

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

		if (road_id.size() > 0)
		{
			LinkInfo link_info (start_node, end_node, road_id, dis);
			allLink.push_back(link_info);
		}

	}
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
	vector<string> allNetName = db_oper.getAllNetId();

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
	analyseLink();
	analyseNode();
	analyseDetector();
}
