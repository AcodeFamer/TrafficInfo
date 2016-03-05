#include "stdafx.h"
#include "SimData.h"

SimData::SimData()
{

}

SimData::~SimData()
{

}

void SimData::initCountLoop(int detectorNum)
{
	countEveryLoop.clear();
	countEveryLoopDuration.clear();
	countEveryLoopDiff.clear();
	occupancyEveryLoop.clear();
	isOccupiedEveryLoop.clear();
	occupancyEveryLoopDuration.clear();
	velocityEveryLoop.clear();
	velocityEveryLoopDuration.clear();

	vector<int> everyDetectorCount;
	vector<float> everyDetectorOccupancy;
	for (int i = 0; i < detectorNum; i++)
	{
		everyDetectorCount.clear();
		everyDetectorOccupancy.clear();
		for (int j = 0; j < loopNumArray[i]; j++)
		{
			//int count = qpg_DTL_count(netLoops[i][j],0);
			everyDetectorCount.push_back(0);
			everyDetectorOccupancy.push_back(0.0);
		}
		countEveryLoop.push_back(everyDetectorCount);
		countEveryLoopDuration.push_back(everyDetectorCount);
		countEveryLoopDiff.push_back(everyDetectorCount);
		occupancyEveryLoop.push_back(everyDetectorOccupancy);
		occupancyEveryLoopDuration.push_back(everyDetectorOccupancy);
		isOccupiedEveryLoop.push_back(everyDetectorCount);
		velocityEveryLoop.push_back(everyDetectorOccupancy);
		velocityEveryLoopDuration.push_back(everyDetectorOccupancy);
	}

}
//初始化countEveryDetector
void SimData::initCountDetector(int detectorNum)
{
	countEveryDetector.resize(detectorNum);
}


void SimData::initDemandMatrix(int zoneNum)
{
	vector<float> row;
	row.resize(zoneNum);
	for (int i = 0; i < zoneNum; i++)
	{
		demandMatrix.push_back(row);
	}

	for (int i = 0; i < zoneNum; i++)
	{
		for (int j = 0; j < zoneNum; j++)
		{
			if (i != j)
			{
				demandMatrix[i][j] = qpg_DMD_demand(1, i + 1, j + 1);
			}
		}
	}
}

void SimData::setDemandMatrix(int zoneNum,float od_value)
{
	for (int i = 0; i < zoneNum; i++)
	{
		for (int j = 0; j < zoneNum; j++)
		{
			if (i != j)
			{
				demandMatrix[i][j] = od_value*demandMatrix[i][j];

				qps_DMD_demand(1, i + 1, j + 1, demandMatrix[i][j]);
			}
		}
	}
}

void SimData::writeAllDataToSql(VspdCToMySQL* mysql,int detectorNum)
{
	int count_db_write = 0;//每次插入数据条数计数
	mysql->StartTransition();//开启事务，提高插入效率

	string Msg;
	string SQL_insert_laneflow("INSERT DELAYED INTO trafficinfo(SimIndex,DetectorId,LaneId,RecordTime,CarFlow,AvgVelocity,OccupancyTime) VALUES ");

	for (int i = 0; i < detectorNum; i++)
	{
		for (int j = 0; j < loopNumArray[i]; j++)
		{
			if (count_db_write == 0)
			{
				SQL_insert_laneflow = SQL_insert_laneflow + "(" +
					"'" + int2str(simIndex) + "'" + "," +
					"'" + allDetectorId[i] + "'" + "," +
					"'" + int2str(j + 1) + "'" + "," +
					"'" + simuTime + "'" + "," +
					"'" + int2str(countEveryLoopDiff[i][j]) + "'" + "," +
					"'" + float2str(velocityEveryLoopDuration[i][j]) + "'" + "," +
					"'" + float2str(occupancyEveryLoopDuration[i][j]) + "'" +
					")";

			}

			else
			{
				SQL_insert_laneflow = SQL_insert_laneflow + "," + "(" +
					"'" + int2str(simIndex) + "'" + "," +
					"'" + allDetectorId[i] + "'" + "," +
					"'" + int2str(j + 1) + "'" + "," +
					"'" + simuTime + "'" + "," +
					"'" + int2str(countEveryLoopDiff[i][j]) + "'" + "," +
					"'" + float2str(velocityEveryLoopDuration[i][j]) + "'" + "," +
					"'" + float2str(occupancyEveryLoopDuration[i][j]) + "'" +
					")";


			}
			count_db_write++;
			if (count_db_write == 30)  //每次插30条数据 插40条时程序会崩溃
			{
				mysql->InsertData(SQL_insert_laneflow.c_str(), Msg);
				count_db_write = 0;
				SQL_insert_laneflow = "INSERT DELAYED INTO trafficinfo(SimIndex,DetectorId,LaneId,RecordTime,CarFlow,AvgVelocity,OccupancyTime) VALUES ";
			}
		}
	}
	mysql->InsertData(SQL_insert_laneflow.c_str(), Msg); //最后不足30条数据插入
	mysql->CommitTransition();  //提交事务
}
