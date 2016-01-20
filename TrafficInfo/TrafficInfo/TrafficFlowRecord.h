#ifndef _TRAFFICFLOWRECORD_H__
#define _TRAFFICFLOWRECORD_H__

class TrafficFlowRecord
{
	string SimIndex;
	string DetectorId;
	string LaneInfo;
	int TimeGap;
	string StartTime;
	int CarFlow;
	int Velocity;
	int Occupancy;
	string EndTime;

public:
	TrafficFlowRecord();
	TrafficFlowRecord(string sim_index, string detector_id, string lane_info, int time_gap, string start_time, int car_flow, int velocity, int occupancy, string end_time);
	~TrafficFlowRecord();

	int writeDataToSql(VspdCToMySQL* mysql);
};



#endif // !_TRAFFICFLOWRECORD_H__
