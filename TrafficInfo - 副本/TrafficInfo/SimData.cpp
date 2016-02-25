#include "stdafx.h"
#include "SimData.h"

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
//³õÊ¼»¯countEveryDetector
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
