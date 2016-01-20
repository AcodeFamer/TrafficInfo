#include "stdafx.h"
#include "TrafficFlowRecord.h"


TrafficFlowRecord::TrafficFlowRecord()
{

}

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

TrafficFlowRecord::~TrafficFlowRecord()
{

}

int TrafficFlowRecord::writeDataToSql(VspdCToMySQL* mysql)
{
	vector<string> key;
	key.push_back("SimIndex");
	key.push_back("DetectorId");
	key.push_back("LaneInfo");
	key.push_back("TimeGap");
	key.push_back("StartTime");
	key.push_back("CarFlow");
	key.push_back("Velocity");
	key.push_back("Occupancy");
	key.push_back("EndTime");

	vector<string> values;
	values.push_back(SimIndex);
	values.push_back(DetectorId);
	values.push_back(LaneInfo);
	values.push_back(int2str(TimeGap));
	values.push_back(StartTime);
	values.push_back(int2str(CarFlow));
	values.push_back(int2str(Velocity));
	values.push_back(int2str(Occupancy));
	values.push_back(EndTime);


	if (mysql->add_data("trafficflowrecord", key, values) == 0)
	{
		return 0;
	}

	else
		return 1;
}

