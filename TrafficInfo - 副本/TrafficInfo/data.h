#include <string>
using namespace std;

class AbstractDataType
{
public:
	virtual string getDataString() = 0;
};


//***************************·����Ϣ��
class RoadNetInfo : public AbstractDataType
{
public:
	//·��ID
	string RoadNetId;
	//·������
	string RoadNetName;
	//�ڵ���
	int NodeNum;
	//������
	int LinkNum;
	//С����
	int SubzoneNum;
	//�Ƿ��������
	int IsSimRunning;

	RoadNetInfo::RoadNetInfo(string Id, string name, int nodeNum, int linkNum, int subzoneNum, int isSimRunning)
	{
		RoadNetId = Id;
		RoadNetName = name;
		NodeNum = nodeNum;
		LinkNum = linkNum;
		SubzoneNum = subzoneNum;
		IsSimRunning = isSimRunning;
	}

	string getDataString()
	{
		return "('" + RoadNetId + "','" + RoadNetName + "','" + int2str(NodeNum) + "','" + int2str(LinkNum) + "','" + int2str(SubzoneNum) + "','" + int2str(IsSimRunning) + "')";
	}
};
//***********************�ڵ���Ϣ��
class NodeInfo : public AbstractDataType
{
public:
	//�ڵ�ID
	string NodeId;
	//�ڵ�����
	string NodeName;
	//�Ƿ�С��
	int IsSubzone;
	//�Ƿ�·��
	int IsCrossing;
	//���ӽڵ�����·�ڣ�
	int ConNodeNum;
	//�Ƿ��źŻ���·�ڣ�
	int IsSingal;
    //�Ƿ���С����
	int IsOneWay;
	//����·��ID��·�νڵ㣩
	string LinkId;


	NodeInfo::NodeInfo(string id, string name, int is_sub_zone, int is_crossing, int con_node_num, int is_singal, int is_one_way, string link_id)
	{
		NodeId = id;
		NodeName = name;
		IsSubzone = is_sub_zone;
		IsCrossing = is_crossing;
		ConNodeNum = con_node_num;
		IsSingal = is_singal;
		IsOneWay = is_one_way;
		LinkId = link_id;
	}

	string getDataString()
	{
		return "('" + NodeId + "','" + NodeName + "','" + int2str(IsSubzone) + "','" + int2str(IsCrossing) + "','" + int2str(ConNodeNum) + "','" + int2str(IsSingal) + "','" + int2str(IsOneWay) + "','" + LinkId + "')";
	}
};

//********************·����Ϣ������
class RoadInfo : public AbstractDataType
{
public:
	//·��ID����������
	string RoadId;
	//·������
	string RoadName;
	//��ʼ�ڵ�
	string StartNode;
	//�����ڵ�
	string EndNode;
	//����
	float Distance;
	//�Ƿ���ڶ�������

	RoadInfo::RoadInfo(string id, string name, string start_node, string end_node, float dis)
	{
		RoadId = id;
		RoadName = name;
		StartNode = start_node;
		EndNode = end_node;
		Distance = dis;
	}

	string getDataString()
	{
		return "('" + RoadId + "','" + RoadName + "','" + StartNode + "','" + EndNode + "','" + float2str(Distance) + "')";
	}
};

//********************������ϸ��
class LinkInfo : public AbstractDataType
{
public:
	//��ʼ�ڵ�
	string StartNode;
	//�����ڵ�
	string EndNode;
	//����·�α��
	string RoadId;
	//����
	float Distance;

	LinkInfo::LinkInfo(string start_node, string end_node, string road_id, float dis)
	{
		StartNode = start_node;
		EndNode = end_node;
		RoadId = road_id;
		Distance = dis;
	}

	string getDataString()
	{
		return "('" + StartNode + "','" + EndNode + "','" + RoadId + "','" + float2str(Distance) +  "')";
	}
};

//**********************·�ڳ�����
class CrossingStream : public AbstractDataType
{
public:
	//·��ID
	string CrossingId;
	//��������ID
	string LinkInId;
	//��������ID
	string LinkOutId;
	//����·��ID
	string RoadInId;
	//����·��ID
	string RoadOutId;
	//Ȩ�����
	string Priority;

	CrossingStream::CrossingStream(string crossing_id, string link_in_id, string link_out_id, string road_in_id, string road_out_id, string pri)
	{
		CrossingId = crossing_id;
		LinkInId = link_in_id;
		LinkOutId = link_out_id;
		RoadInId = road_in_id;
		RoadOutId = road_out_id;
		Priority = pri;
	}

	string getDataString()
	{
		return "('" + CrossingId + "','" + LinkInId + "','" + LinkOutId + "','" + RoadInId + "','" + RoadOutId + "','" + Priority +  "')";
	}
};

//******************�������
class Detector : public AbstractDataType
{
public:
	//�����ID
	string DetectorId;
	//
	string DetectorName;
	//����·��ID
	string LinkId;
	//�������α�ʶ
	int Flag;
	//���μ������ţ����μ������
	int DownStreamIndex;
	//����·�ڣ����μ������
	string CrossingId;
    //���������棨���μ������

	//��⳵����
	int LaneNum;

	Detector::Detector(string detector_id, string detector_name, string link_id, int flag, int down_stream_index, string crossing_id, int lane_num)
	{
		DetectorId = detector_id;
		DetectorName = detector_name;
		LinkId = link_id;
		Flag = flag;
		DownStreamIndex = down_stream_index;
		CrossingId = crossing_id;
		LaneNum = lane_num;
	}

	string getDataString()
	{
		return "('" + DetectorId + "','" + DetectorName + "','" + LinkId + "','" + int2str(Flag) + "','" + int2str(DownStreamIndex) + "','" + CrossingId + "','" + int2str(LaneNum) +  "')";
	}
};

//****************************�������
class  Section : public AbstractDataType
{
public:
	//��������
	string SectionName;
	//�Ƿ�˫��
	int IsTwoWay;
	//����1·��ID
	string LinkId1;
	//����1�����ID
	string DetectorId1;
	//����2·��ID
	string LinkId2;
	//����2�����ID
	string DetectorId2;

	Section::Section(string name, int is_two_way, string link_id_1, string detector_id_1, string link_id_2, string detector_id_2)
	{
		//��������
		SectionName = name;
		//�Ƿ�˫��
		IsTwoWay = is_two_way;
		//����1·��ID
		LinkId1 = link_id_1;
		//����1�����ID
		DetectorId1 = detector_id_1;
		//����2·��ID
		LinkId2 = link_id_2;
		//����2�����ID
		DetectorId2 = detector_id_2;
	}


	string getDataString()
	{
		return "('" + SectionName + "','" + int2str(IsTwoWay) + "','" + LinkId1 + "','" + DetectorId1 + "','" + LinkId2 + "','" + DetectorId2 + "')";
	}
};

//**************************ʵʱ��ͨ��Ϣ��
class TrafficInfo : public AbstractDataType
{
public:
	//������
	int SimuIndex;
	//�����Id
	string DetectorId;
	//�������
	string LaneId;
	//��¼ʱ��
	string RecordTime;
	//������
	int CarFlow;
	//ƽ���ٶ�
	float AvgVelocity;
	//ռ��ʱ��
	float OccupancyTime;

	TrafficInfo::TrafficInfo(int simu_index, string detector_id, string lane_id, string record_time, int car_flow, float velocity_ave, float occupancy_time)
	{
		SimuIndex = simu_index;
		DetectorId = detector_id;
		LaneId = lane_id;
		RecordTime = record_time;
		CarFlow = car_flow;
		AvgVelocity = velocity_ave;
		OccupancyTime = occupancy_time;
	}

	string getDataString()
	{
		return "('" + int2str(SimuIndex) + "','" + DetectorId + "','" + LaneId + "','" + RecordTime + "','" + int2str(CarFlow) + "','" + float2str(AvgVelocity) + "','" + float2str(OccupancyTime) +"')";
	}
};

//***************************��ͨ��ͳ�Ʊ�

class TrafficFlowRecord : public AbstractDataType
{
public:
	//�����š���������������
	string SimIndex;
	//�����ID
	string DetectorId;
	//������Ϣ��0��ʾ���г�����1��2��3��ʾ��ţ�
	string LaneInfo;
	//ͳ�Ƽ��
	int TimeGap;
	//��ʼʱ��
	string StartTime;
	//����
	int CarFlow;
	//�ٶ�
	int Velocity;
	//ռ����
	int Occupancy;
	//��ֹʱ��
	string EndTime;

	TrafficFlowRecord::TrafficFlowRecord(string sim_index, string detector_id, string lane_info, int time_gap, string start_time, int car_flow, int velocity, int occupancy, string end_time)
	{
		SimIndex = sim_index;
		DetectorId = detector_id;
		LaneInfo = lane_info;
		TimeGap = time_gap;
		StartTime = start_time;
		CarFlow = car_flow;
		Velocity = velocity;
		Occupancy = occupancy;
		EndTime = end_time;
	}

};

//*************************���Ʒ�����
class ControlPlan : public AbstractDataType
{
public:
	//����·��
	string CrossingId;
	//��λ��
	int PhaseNum;
	//�Ƿ�̶�����
	int IsPeriodFixed;
	//�Ƿ��Ӧ����
	int IsActuatedControl;
	//����
	float Period;
	//��λ��
	float PhaseOffset;
	//�Ƿ����
	int IsUpdate;

	ControlPlan::ControlPlan(string crossing_id, int phase_num, int is_period_fixed, int is_actuated_control, float period, float offset, int is_update)
	{
		CrossingId = crossing_id;
		PhaseNum = phase_num;
		IsPeriodFixed = is_period_fixed;
		IsActuatedControl = is_actuated_control;
		Period = period;
		PhaseOffset = offset;
		IsUpdate = is_update;
	}

	string getDataString()
	{
		return "('" + CrossingId + "','" + int2str(PhaseNum) + "','" + int2str(IsPeriodFixed) + "','" + int2str(IsActuatedControl) + "','" + float2str(Period) + "','" + float2str(PhaseOffset) + "','" + int2str(IsUpdate) + "')";
	}
};

//��λ��
class Phase : public AbstractDataType
{
public:
	//��������
	int PlanIndex;
	//��λ���
	int PhaseId;
	//����·��
	string CrossingId;
	//�̵�ʱ��
	float GreenTime;
	//�Ƶ�ʱ��
	float AmberTime;
	//���ʱ��
	float RedTime;
	//�Ƿ����
	int IsUpdate;

	Phase::Phase(int plan_index, int phase_id, string crossing_id, float green_time, float amber_time, float red_time, int is_update)
	{
		PlanIndex = plan_index;
		PhaseId = phase_id;
		CrossingId = crossing_id;
		GreenTime = green_time;
		AmberTime = amber_time;
		RedTime = red_time;
		IsUpdate = is_update;
	}

	string getDataString()
	{
		return "('" + int2str(PlanIndex) + "','" + int2str(PhaseId) + "','" + CrossingId + "','" + float2str(GreenTime) + "','" + float2str(AmberTime) + "','" + float2str(RedTime) + "','" + int2str(IsUpdate) + "')";
	}
};

//��λ������ϸ��
class PhaseStream : public AbstractDataType
{
public:
	//������λ���
	string PhaseIndex;
	//�������
	string StreamIndex;
	//��ֱ�ҵ���ʶ
	string DirectionFlag;
	//������λ���
	string PhaseId;
	//��������
	string PlanIndex;
	//����·��
	string CrossingId;
	//����·��
	string LinkInId;
	//����·��
	string LinkOutId;

	PhaseStream::PhaseStream(string phase_index, string stream_index, string dir_flag, string phase_id, string plan_index, string crossing_index, string link_in_id, string link_out_id)
	{
		PhaseIndex = phase_index;
		StreamIndex = stream_index;
		DirectionFlag = dir_flag;
		PhaseId = phase_id;
		PlanIndex = plan_index;
		CrossingId = crossing_index;
		LinkInId = link_in_id;
		LinkOutId = link_out_id;
	}

	string getDataString()
	{
		return "('" + PhaseIndex + "','" + StreamIndex + "','" + DirectionFlag + "','" + PhaseId + "','" + PlanIndex + "','" + CrossingId + "','" + LinkInId + "','" + LinkOutId + "')";
	}
};


