#include <string>
using namespace std;

class AbstractDataType
{
public:
	virtual string getDataString() = 0;
};


//***************************路网信息表
class RoadNetInfo : public AbstractDataType
{
public:
	//路网ID
	string RoadNetId;
	//路网名称
	string RoadNetName;
	//节点数
	int NodeNum;
	//连接数
	int LinkNum;
	//小区数
	int SubzoneNum;
	//是否仿真运行
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
//***********************节点信息表
class NodeInfo : public AbstractDataType
{
public:
	//节点ID
	string NodeId;
	//节点名称
	string NodeName;
	//是否小区
	int IsSubzone;
	//是否路口
	int IsCrossing;
	//连接节点数（路口）
	int ConNodeNum;
	//是否信号化（路口）
	int IsSingal;
    //是否单向（小区）
	int IsOneWay;
	//所属路段ID（路段节点）
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

//********************路段信息表（单向）
class RoadInfo : public AbstractDataType
{
public:
	//路段ID、、、、、
	string RoadId;
	//路段名称
	string RoadName;
	//起始节点
	string StartNode;
	//结束节点
	string EndNode;
	//距离
	float Distance;
	//是否存在断面检测器

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

//********************连接明细表
class LinkInfo : public AbstractDataType
{
public:
	//起始节点
	string StartNode;
	//结束节点
	string EndNode;
	//所属路段编号
	string RoadId;
	//距离
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

//**********************路口车流表
class CrossingStream : public AbstractDataType
{
public:
	//路口ID
	string CrossingId;
	//流入连接ID
	string LinkInId;
	//流出连接ID
	string LinkOutId;
	//流入路段ID
	string RoadInId;
	//流出路段ID
	string RoadOutId;
	//权限情况
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

//******************检测器表
class Detector : public AbstractDataType
{
public:
	//检测器ID
	string DetectorId;
	//
	string DetectorName;
	//所属路段ID
	string LinkId;
	//上中下游标识
	int Flag;
	//下游检测器序号（下游检测器）
	int DownStreamIndex;
	//所属路口（下游检测器）
	string CrossingId;
    //所属检测断面（中游检测器）

	//检测车道数
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

//****************************检测断面表
class  Section : public AbstractDataType
{
public:
	//断面名称
	string SectionName;
	//是否双向
	int IsTwoWay;
	//方向1路段ID
	string LinkId1;
	//方向1检测器ID
	string DetectorId1;
	//方向2路段ID
	string LinkId2;
	//方向2检测器ID
	string DetectorId2;

	Section::Section(string name, int is_two_way, string link_id_1, string detector_id_1, string link_id_2, string detector_id_2)
	{
		//断面名称
		SectionName = name;
		//是否双向
		IsTwoWay = is_two_way;
		//方向1路段ID
		LinkId1 = link_id_1;
		//方向1检测器ID
		DetectorId1 = detector_id_1;
		//方向2路段ID
		LinkId2 = link_id_2;
		//方向2检测器ID
		DetectorId2 = detector_id_2;
	}


	string getDataString()
	{
		return "('" + SectionName + "','" + int2str(IsTwoWay) + "','" + LinkId1 + "','" + DetectorId1 + "','" + LinkId2 + "','" + DetectorId2 + "')";
	}
};

//**************************实时交通信息表
class TrafficInfo : public AbstractDataType
{
public:
	//仿真编号
	int SimuIndex;
	//检测器Id
	string DetectorId;
	//车道编号
	string LaneId;
	//记录时间
	string RecordTime;
	//车流量
	int CarFlow;
	//平均速度
	float AvgVelocity;
	//占有时间
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

//***************************交通流统计表

class TrafficFlowRecord : public AbstractDataType
{
public:
	//仿真编号、、、、、、、、
	string SimIndex;
	//检测器ID
	string DetectorId;
	//车道信息（0表示所有车道，1、2、3表示序号）
	string LaneInfo;
	//统计间隔
	int TimeGap;
	//起始时间
	string StartTime;
	//流量
	int CarFlow;
	//速度
	int Velocity;
	//占有率
	int Occupancy;
	//截止时间
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

//*************************控制方案表
class ControlPlan : public AbstractDataType
{
public:
	//所属路口
	string CrossingId;
	//相位数
	int PhaseNum;
	//是否固定周期
	int IsPeriodFixed;
	//是否感应控制
	int IsActuatedControl;
	//周期
	float Period;
	//相位差
	float PhaseOffset;
	//是否更新
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

//相位表
class Phase : public AbstractDataType
{
public:
	//所属方案
	int PlanIndex;
	//相位序号
	int PhaseId;
	//所属路口
	string CrossingId;
	//绿灯时间
	float GreenTime;
	//黄灯时间
	float AmberTime;
	//红灯时间
	float RedTime;
	//是否更新
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

//相位车流明细表
class PhaseStream : public AbstractDataType
{
public:
	//所属相位编号
	string PhaseIndex;
	//车流编号
	string StreamIndex;
	//左直右掉标识
	string DirectionFlag;
	//所属相位序号
	string PhaseId;
	//所属方案
	string PlanIndex;
	//所属路口
	string CrossingId;
	//进口路段
	string LinkInId;
	//出口路段
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


