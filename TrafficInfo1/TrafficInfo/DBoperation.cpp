#include "stdafx.h"
#include "DBoperation.h"

DBoperation::DBoperation()
{	
	//��ʼ�����ݿ����
	mysql = new VspdCToMySQL();
	
	//**************************************��ʼ�������ֺͱ��ֶ�

	//�ڵ���Ϣ��
	string node[] = { "NodeId", "NodeName", "IsSubzone", "IsCrossing", "ConNodeNum", "IsSingal", "IsOneWay", "LinkId" };
	vector<string> nodeinfo(node, node + sizeof(node) / sizeof(string));
	table["nodeinfo"] = nodeinfo;


	//·����Ϣ��
	string road[] = { "RoadId", "RoadName", "StartNode", "EndNode", "Distance" };
	vector<string> roadinfo(road, road + sizeof(road) / sizeof(string));
	table["roadinfo"] = roadinfo;

	//������ϸ��
	string link[] = { "StartNode", "EndNode", "RoadId", "Distance" };
	vector<string> linkinfo(link, link + sizeof(link) / sizeof(string));
	table["linkinfo"] = linkinfo;

	//**********************·�ڳ�����
	string cs[] = { "CrossingId", "LinkInId", "LinkOutId", "RoadInId", "RoadOutId", "Priority" };
	vector<string> crossingstream(cs, cs + sizeof(cs) / sizeof(string));
	table["crossingstream"] = crossingstream;

	//**********************����״̬��ѯ
	string constat[] = { "CrossingId", "StreamIndex", "RoadInId", "RoadOutId", "Priority" };
	vector<string> controlstate(constat, constat + sizeof(constat) / sizeof(string));
	table["controlstate"] = controlstate;

	//**********************�������
	string det[] = { "DetectorId", "DetectorName", "LinkId", "Flag", "DownStreamIndex", "CrossingId", "LaneNum" };
	vector<string> detector(det, det + sizeof(det) / sizeof(string));
	table["detector"] = detector;

	//***********************�����
	string sec[] = { "SectionName", "IsTwoWay", "LinkId1", "DetectorId1", "LinkId2", "DetectorId2" };
	vector<string> section(sec, sec+sizeof(sec) / sizeof(string));
	table["section"] = section;
	
	//���Ʒ�����
	string cp[] = { "CrossingId", "PhaseNum", "IsPeriodFixed" , "IsActuatedControl", "Period", "PhaseOffset", "IsUpdate" };
	vector<string> controlplan(cp, cp + sizeof(cp) / sizeof(string));
	table["controlplan"] = controlplan;

	//��λ��
	string p[] = { "PlanIndex", "PhaseId", "CrossingId", "GreenTime", "AmberTime", "RedTime", "IsUpdate" };
	vector<string> phase(p, p + sizeof(p) / sizeof(string));
	table["phase"] = phase;

	//��λ������ϸ��
	string ps[] = { "PhaseIndex", "StreamIndex", "DirectionFlag", "PhaseId", "PlanIndex", "CrossingId", "LinkInId" ,"LinkOutId" };
	vector<string> phasestream(ps, ps + sizeof(ps) / sizeof(string));
	table["phasestream"] = phasestream;

	//ʵʱ��ͨ��Ϣ��
	string trainfo[] = { "SimuIndex", "DetectorId", "LaneId", "RecordTime", "CarFlow", "AvgVelocity", "OccupancyTime" };
	vector<string> trafficinfo(trainfo, trainfo + sizeof(trainfo) / sizeof(string));
	table["trafficinfo"] = trafficinfo;

}

DBoperation::~DBoperation()
{
	//ɾ�����ݿ����
	delete mysql;
}

VspdCToMySQL* DBoperation::getMySql()
{
	return mysql;
}

void DBoperation::updateDataTable()
{

}

//��ȡ��link����link������·��id  ���ɹ����������ض�Ӧ��LinkIndex����ʧ�ܣ���������0
int DBoperation::getLinkInfo(int flag, LINK* pLink, string& road_id)
{
	//��ȡ��LINK������NODEָ��
	NODE* nodeA = qpg_LNK_nodeStart(pLink);
	NODE* nodeB = qpg_LNK_nodeEnd(pLink);
	//��ȡ��Ӧid
	string nodeA_id = qpg_NDE_name(nodeA);
	string nodeB_id = qpg_NDE_name(nodeB);

	string start_node, end_node;
	if (flag == 1)   //��  5λ·�ڽڵ�id��end_node
	{
		if (nodeA_id.size() == 5)
		{
			end_node = nodeA_id;
			start_node = nodeB_id;
		}
		else
		{
			start_node = nodeA_id;
			end_node = nodeB_id;
		}

	}
	else      //��   5λ·�ڽڵ�id��start_node
	{
		if (nodeA_id.size() == 5)
		{

			start_node = nodeA_id;
			end_node = nodeB_id;
		}
		else
		{
			start_node = nodeB_id;
			end_node = nodeA_id;
		}
	}
	//������ʼ�ڵ�ͽ����ڵ�,��ѯ���ݿ⣨�ڴ�֮ǰ���뽫allLink����д�����ݿ⣩
	string SQL = "select LinkIndex,RoadId from linkinfo where StartNode=";
	SQL = SQL + "'" + start_node + "' and EndNode='" + end_node + "'";
	string Msg;
	vector<vector<string>>  res = mysql->SelectData(SQL.c_str(), 2, Msg);
	if (res.size() != 0)
	{
		road_id = res[0][1];
		return str2int(res[0][0]);
	}
	else
	{
		qps_GUI_printf("link not exists(start:%s,end:%s) ", start_node.c_str(), end_node.c_str());
	}
	return 0;
}

set<string> DBoperation::getLinkIdWhenFlagEqualsTwo()
{
	char * SQL = "SELECT LinkId FROM detector WHERE Flag=2";
	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL, 1, Msg);

	set<string> allDetectorId;
	for (size_t i = 0; i < res.size(); i++)
		allDetectorId.insert(res[i][0]);
	return allDetectorId;
}

vector<string> DBoperation::getAllNetId()
{
	char* SQL = "SELECT RoadNetId FROM roadnetinfo";
	string Msg;
	vector<vector<string>> res;
	res = mysql->SelectData(SQL, 1, Msg);
	vector<string> allName;
	for (size_t i = 0; i < res.size(); i++)
	{
		allName.push_back(res[i][0]);
	}
	return allName;
}

void DBoperation::addNewRoadNet(RoadNetInfo road_net_info)
{
	vector<string> key;
	key.push_back("RoadNetId");
	key.push_back("RoadNetName");
	key.push_back("NodeNum");
	key.push_back("LinkNum");
	key.push_back("SubzoneNum");
	key.push_back("IsSimRunning");

	vector<string> values;
	values.push_back(road_net_info.RoadNetId);
	values.push_back(road_net_info.RoadNetName);
	values.push_back(int2str(road_net_info.NodeNum));
	values.push_back(int2str(road_net_info.LinkNum));
	values.push_back(int2str(road_net_info.SubzoneNum));
	values.push_back(int2str(road_net_info.IsSimRunning));

	mysql->add_data("roadnetinfo", key, values);
}

void DBoperation::clearTable()
{
	string Msg;
	//������ݿ��
	mysql->ClearTable("detector", Msg);
	mysql->ClearTable("roadinfo", Msg);
	mysql->ClearTable("nodeinfo", Msg);
	mysql->ClearTable("section", Msg);
	mysql->ClearTable("linkinfo", Msg);
	//mysql->ClearTable("controlplan", Msg);
	//mysql->ClearTable("phase", Msg);
	mysql->ClearTable("crossingstream", Msg);
	mysql->ClearTable("controlstate", Msg);
	//mysql->ClearTable("phasestream", Msg);
}

bool DBoperation::IsRoadNetModified(string net_name, int nodeNum, int linkNum, int zoneNum)
{
	//��ѯ��֪·���Ľڵ��������������������
	string SQL = "SELECT * FROM  roadnetinfo WHERE  RoadNetId= ";
	SQL = SQL + "'" + net_name + "'";
	string Msg;
	vector<vector<string>>  res = mysql->SelectData(SQL.c_str(), 7, Msg);
	int node_num = str2int(res[0][3]);
	int link_num = str2int(res[0][4]);
	int subzone_num = str2int(res[0][5]);
	if (node_num != nodeNum || link_num != linkNum || subzone_num != zoneNum) //·���޸Ĺ�
	{
		return 1;
	}
	return 0;
}

void DBoperation::updateRoadNetInfoTable(string net_name,int nodeNum,int linkNum,int zoneNum)
{
	string SQL = "UPDATE roadnetinfo SET ";
	SQL = SQL + " NodeNum= " + "'" + int2str(nodeNum) + "'";
	SQL = SQL + ", LinkNum= " + "'" + int2str(linkNum) + "'";
	SQL = SQL + ", SubzoneNum= " + "'" + int2str(zoneNum) + "'";
	SQL = SQL + " WHERE " + " RoadNetId= " + "'" + net_name + "'";
	string Msg;
	mysql->UpdateData(SQL.c_str(), Msg);
}

vector<vector<string>> DBoperation::getLinkDistance(string link_id)
{
	string Msg;
	string SQL = "select Distance from linkinfo where RoadId=";
	SQL = SQL + "'" + link_id + "'";
	vector<vector<string>> res =mysql->SelectData(SQL.c_str(), 1, Msg);
	return res;
}

int DBoperation::getPhaseInfo(int phaseIndex, string& phase_id, string& crossing_id)
{
	string Msg;
	string SQL_phase = "select PlanIndex,PhaseId,CrossingId from phase where PhaseIndex=";
	SQL_phase = SQL_phase + int2str(phaseIndex);
	vector<vector<string>> res_phase = mysql->SelectData(SQL_phase.c_str(), 3, Msg);
	if (res_phase.size() > 0)
	{
		int plan_index = str2int(res_phase[0][0]);
		phase_id = res_phase[0][1];
		crossing_id = res_phase[0][2];
		return plan_index;
	}
	return 0;
	
}
//��������·�ڲ�ѯ·�ڳ������������·����Ϣ����������·��id������·��id
vector<vector<string>> DBoperation::getCrossStreamInfo(string crossing_id)
{
	string Msg;
	string SQL_crossingstream = "select StreamIndex,RoadInId,RoadOutId,Priority from crossingstream where CrossingId=";
	SQL_crossingstream = SQL_crossingstream + "'" + crossing_id + "'";
	vector<vector<string>> res_crossingstream = mysql->SelectData(SQL_crossingstream.c_str(), 4, Msg);
	return res_crossingstream;
}

int DBoperation::isSimStart()
{
	char* SQL = "select * from simrecord where SimIndex=(select max(SimIndex) from simrecord);";
	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL, 15, Msg);
	if (res.size() != 0)
	{
		int is_start = str2int(res[0][6]);
		if (is_start == 1)//���������������ط�����
			return str2int(res[0][0]);
		else
			return 0;
	}
	else return 0;
}

bool DBoperation::isSimPause()
{
	char* SQL = "select * from simrecord where SimIndex=(select max(SimIndex) from simrecord);";
	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL, 15, Msg);
	if (res.size() != 0)
	{
		int is_pause = str2int(res[0][7]);
		if (is_pause == 1)
			return true;
		else
			return false;
	}
	return false;
}

bool DBoperation::isSimStop()
{
	char* SQL = "select * from simrecord where SimIndex=(select max(SimIndex) from simrecord);";
	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL, 15, Msg);
	if (res.size() != 0)
	{
		int is_stop = str2int(res[0][11]);
		if (is_stop == 1)
			return true;
		else
			return false;
	}
	return false;
}

double DBoperation::getODvalue()
{
	char* SQL = "select * from simrecord where SimIndex=(select max(SimIndex) from simrecord);";
	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL, 15, Msg);
	double od = 0.0;
	if (res.size() != 0)
	{
		od = atof(res[0][4].c_str());
	}
	return od;
}


vector<vector<string>> DBoperation::getSingalTimeByIndex(int plan_index)
{
	string SQL = "select GreenTime,AmberTime,RedTime,IsUpdate from phase where PlanIndex=" + int2str(plan_index);

	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL.c_str(), 4, Msg);

	//��ȡ��ɺ������־λ
	string SQL_clear = "update phase set IsUpdate='0' where IsUpdate='1'";
	mysql->UpdateData(SQL_clear.c_str(), Msg);
	return res;
}



vector<vector<string>> DBoperation::getPlanUpdateIndex()
{
	//��ѯ���Ʒ�����,���ָ��µĿ��Ʒ������
	char* SQL = "select PlanIndex,CrossingId,Period,PhaseOffset from controlplan where IsUpdate='1';";
	string msg;
	vector<vector<string>> res = mysql->SelectData(SQL, 4, msg);


	//��ȡ��ɺ������־λ
	SQL = "update controlplan set IsUpdate='0' where IsUpdate='1'";
	mysql->UpdateData(SQL, msg);
	return res;
}