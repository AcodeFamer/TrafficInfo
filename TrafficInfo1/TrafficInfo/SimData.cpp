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

void SimData::writeDetectorDataToSql(VspdCToMySQL* mysql, int detectorNum)
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

void SimData::initRoadInfo(VspdCToMySQL* mysql)
{
	//路网节点数
	int net_node_num = qpg_NET_nodes();

	int usefulRoadCount = 0;
	for (int node_i = 0; node_i < net_node_num; node_i++)
	{
		//node指针
		NODE* pNode = qpg_NET_nodeByIndex(node_i + 1);
		//node id
		string node_id = qpg_NDE_name(pNode);
		//若是路口
		if (node_id.size() == 5 && node_id[3] == '0' && node_id[4] == '0')
		{
			//entyy link 数目
			int entry_links = qpg_NDE_entryLinks(pNode);

			usefulRoadCount += entry_links;

		    //遍历该路口的link_in
			for (int in_index = 0; in_index < entry_links; in_index++)
			{
				//link指针
				LINK* link_in = qpg_NDE_linkEntry(pNode, in_index + 1);
				//车道数
				int lane_num = qpg_LNK_lanes(link_in);

				//路口link 找出五位的id，为该路段的endNodeId
				NODE* sNode=qpg_LNK_nodeEnd(link_in);
				NODE* eNode = qpg_LNK_nodeStart(link_in);
				string start_id = qpg_NDE_name(sNode);
				string end_id=qpg_NDE_name(eNode);

				string road_id_end;
				if (end_id.size() == 5)
				{
					road_id_end = end_id;
				}
				else
				{
					road_id_end = start_id;
				}

				vector<LINK*> array_link;    //数组此路段所有link*
				vector<int> array_lane_num;  //数组保存此路段对应link的车道数
				array_link.push_back(link_in);
				array_lane_num.push_back(lane_num);
				while (qpg_LNK_entryLinks(link_in) == 1)  //继续查找该link的进入link数
				{
					link_in = qpg_LNK_entry(link_in, 1); 
					lane_num = qpg_LNK_lanes(link_in);
					array_link.push_back(link_in);
					array_lane_num.push_back(lane_num);
				}

				//路口link 找出五位的id，为该路段的startNodeId
				sNode = qpg_LNK_nodeEnd(link_in);
				eNode = qpg_LNK_nodeStart(link_in);
				start_id = qpg_NDE_name(sNode);
				end_id = qpg_NDE_name(eNode);

				string road_id_start;
				if (end_id.size() == 5)
				{
					road_id_start = end_id;
				}
				else
				{
					road_id_start = start_id;
				}

				//得到路段Id
				string road_id = road_id_start + road_id_end;
				allRoadId.push_back(road_id);
				//MessageBox(NULL, road_id.c_str(), "", MB_OK);
				//该路段信息存储
				linkPointerInRoad.push_back(array_link);
				laneNum.push_back(array_lane_num);
					
			}

		}
	}

	//MessageBox(NULL, int2str(usefulRoadCount).c_str(), "", MB_OK);
	for (int i = 0; i < usefulRoadCount; i++)
	{
		vector<float> row(laneNum[i][0], 0.0);  //每个road的车道数定义为进入路口的那个link的车道数
		Roadcount.push_back(row);
		RoadDelay.push_back(row);
		RoadDensity.push_back(row);
		RoadFlow.push_back(row);
		RoadQueueCount.push_back(row);
		RoadQueuePCU.push_back(row);
		RoadQueueLength.push_back(row);
		RoadSpeed.push_back(row);
		RoadLength.push_back(row);
		RoadMaxQueueCount.push_back(row);
		RoadMaxQueueLength.push_back(row);
	}
}

void SimData::writeRoadDataToSql(VspdCToMySQL* mysql)
{
	int count_db_write = 0;//每次插入数据条数计数
	mysql->StartTransition();//开启事务，提高插入效率

	string Msg;
	string SQL_insert_laneflow("INSERT DELAYED INTO roadrecord(SimIndex,RecordTime,RoadId,LaneId,CrossingId,Count,Delay,Density,Flow,QueueCount,QueueMaxCount,QueuePCU,QueueLength,QueueMaxLength,Speed) VALUES ");

	for (size_t i = 0; i < allRoadId.size(); i++)
	{
		for (size_t j = 0; j < Roadcount[i].size(); j++)
		{
			if (count_db_write == 0)
			{
				SQL_insert_laneflow = SQL_insert_laneflow + "(" +
					"'" + int2str(simIndex) + "'" + "," +
					"'" + simuTime + "'" + "," +
					"'" + allRoadId[i] + "'" + "," +
					"'" + int2str(j+1) + "'" + "," +
					"'" + allRoadId[i].substr(5,5) + "'" + "," +
					"'" + float2str(Roadcount[i][j]) + "'" + "," +
					"'" + float2str(RoadDelay[i][j]) + "'" + "," +
					"'" + float2str(RoadDensity[i][j]) + "'" + "," +
					"'" + float2str(RoadFlow[i][j]) + "'" + "," +
					"'" + float2str(RoadQueueCount[i][j]) + "'" + "," +
					"'" + float2str(RoadMaxQueueCount[i][j]) + "'" + "," +
					"'" + float2str(RoadQueuePCU[i][j]) + "'" + "," +
					"'" + float2str(RoadQueueLength[i][j]) + "'" + "," +
					"'" + float2str(RoadMaxQueueLength[i][j]) + "'" + "," +
					"'" + float2str(RoadSpeed[i][j]) + "'" +
					")";

			}

			else
			{
				SQL_insert_laneflow = SQL_insert_laneflow + "," + "(" +
					"'" + int2str(simIndex) + "'" + "," +
					"'" + simuTime + "'" + "," +
					"'" + allRoadId[i] + "'" + "," +
					"'" + int2str(j + 1) + "'" + "," +
					"'" + allRoadId[i].substr(5, 5) + "'" + "," +
					"'" + float2str(Roadcount[i][j]) + "'" + "," +
					"'" + float2str(RoadDelay[i][j]) + "'" + "," +
					"'" + float2str(RoadDensity[i][j]) + "'" + "," +
					"'" + float2str(RoadFlow[i][j]) + "'" + "," +
					"'" + float2str(RoadQueueCount[i][j]) + "'" + "," +
					"'" + float2str(RoadMaxQueueCount[i][j]) + "'" + "," +
					"'" + float2str(RoadQueuePCU[i][j]) + "'" + "," +
					"'" + float2str(RoadQueueLength[i][j]) + "'" + "," +
					"'" + float2str(RoadMaxQueueLength[i][j]) + "'" + "," +
					"'" + float2str(RoadSpeed[i][j]) + "'" +
					")";


			}
			count_db_write++;
			if (count_db_write == 10)  //每次插20条数据 
			{
				mysql->InsertData(SQL_insert_laneflow.c_str(), Msg);
				count_db_write = 0;
				SQL_insert_laneflow = "INSERT DELAYED INTO roadrecord(SimIndex,RecordTime,RoadId,LaneId,CrossingId,Count,Delay,Density,Flow,QueueCount,QueueMaxCount,QueuePCU,QueueLength,QueueMaxLength,Speed) VALUES ";
			}
		}
	}
	mysql->InsertData(SQL_insert_laneflow.c_str(), Msg); //最后不足30条数据插入
	mysql->CommitTransition();  //提交事务
}
