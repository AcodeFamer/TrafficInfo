/****************实时交通信息表************************/
#ifndef __TRAFFICINFO_H__
#define __TRAFFICINFO_H__

class TrafficInfo
{
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
public:
	TrafficInfo();
	TrafficInfo(int simu_index, string detector_id, string lane_id, string record_time, int car_flow, float velocity_ave, float occupancy_time);
	~TrafficInfo();

	static void writeAllDataToSql(VspdCToMySQL* mysql);

	static string simu_time;
	//仿真编号
	static int SimIndex;
};


#endif