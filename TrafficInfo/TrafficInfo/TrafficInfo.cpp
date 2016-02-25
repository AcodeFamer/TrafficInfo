#include "stdafx.h"
#include "TrafficInfo.h"


string TrafficInfo::simu_time="";
int TrafficInfo::SimIndex;

TrafficInfo::TrafficInfo()
{

}

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

TrafficInfo::~TrafficInfo()
{

}

void TrafficInfo::writeAllDataToSql(VspdCToMySQL* mysql)
{
	int count_db_write = 0;//ÿ�β���������������
	mysql->StartTransition();//����������߲���Ч��

	string Msg;
	string SQL_insert_laneflow("INSERT DELAYED INTO trafficinfo(SimIndex,DetectorId,LaneId,RecordTime,CarFlow,AvgVelocity,OccupancyTime) VALUES ");

	for (int i = 0; i < RoadNetInfo::detectorNum; i++)
	{
		for (int j = 0; j < RoadNetInfo::loopNumArray[i]; j++)
		{
			if (count_db_write == 0)
			{
				SQL_insert_laneflow = SQL_insert_laneflow + "(" +
					"'" + int2str(SimIndex) + "'" + "," +
					"'" + RoadNetInfo::allDetectorId[i] + "'" + "," +
					"'" + int2str(j + 1) + "'" + "," +
					"'" + simu_time + "'" + "," +
					"'" + int2str(RoadNetInfo::countEveryLoopDiff[i][j]) + "'" + "," +
					"'" + float2str(RoadNetInfo::velocityEveryLoopDuration[i][j]) + "'" + "," +
					"'" + float2str(RoadNetInfo::occupancyEveryLoopDuration[i][j]) + "'" +
					")";

			}

			else
			{
				SQL_insert_laneflow = SQL_insert_laneflow + "," + "(" +
					"'" + int2str(SimIndex) + "'" + "," +
					"'" + RoadNetInfo::allDetectorId[i] + "'" + "," +
					"'" + int2str(j + 1) + "'" + "," +
					"'" + TrafficInfo::simu_time + "'" + "," +
					"'" + int2str(RoadNetInfo::countEveryLoopDiff[i][j]) + "'" + "," +
					"'" + float2str(RoadNetInfo::velocityEveryLoopDuration[i][j]) + "'" + "," +
					"'" + float2str(RoadNetInfo::occupancyEveryLoopDuration[i][j]) + "'" +
					")";


			}
			count_db_write++;
			if (count_db_write == 30)  //ÿ�β�30������ ��40��ʱ��������
			{
				mysql->InsertData(SQL_insert_laneflow.c_str(), Msg);
				count_db_write = 0;
				SQL_insert_laneflow = "INSERT DELAYED INTO trafficinfo(SimIndex,DetectorId,LaneId,RecordTime,CarFlow,AvgVelocity,OccupancyTime) VALUES ";
			}
		}
	}
	mysql->InsertData(SQL_insert_laneflow.c_str(), Msg); //�����30�����ݲ���
	mysql->CommitTransition();  //�ύ����
}