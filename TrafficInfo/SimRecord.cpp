#include "stdafx.h"
#include "SimRecord.h"

SimRecord::SimRecord(string road_net_id, string road_name, float OD_value,
	int statistic_interval, int is_start, int is_pause, string simu_start_time, string simu_start_clock,
	string duration, int is_finished, string simu_stop_time, string simu_stop_clock,string update_time)
{
	RoadNetId = road_net_id;
	RoadName = road_name;
	ODvalue = OD_value;
	StatisticInterval = statistic_interval;
	IsStart = is_start;
	IsPause = is_pause;
	SimuStartTime = simu_start_time;
	SimuStartClock = simu_stop_clock;
	Duration = duration;
	IsFinished = is_finished;
	SimuStopTime = simu_start_time;
	SimuStopClock = simu_start_clock;
	UpdateTime = update_time;
}

SimRecord::SimRecord()
{

}

SimRecord::~SimRecord()
{
}

int SimRecord::writeDataToSql(VspdCToMySQL* mysql)
{
	vector<string> key;
	key.push_back("RoadNetId");
	key.push_back("RoadName");
	key.push_back("ODvalue");
	key.push_back("StatisticInterval");
	key.push_back("IsStart");
	key.push_back("IsPause");
	key.push_back("SimuStartTime");
	key.push_back("SimuStartClock");
	key.push_back("Duration");
	key.push_back("IsFinished");
	key.push_back("SimuStopTime");
	key.push_back("SimuStopClock");
	key.push_back("UpdateTime");

	vector<string> values;
	values.push_back(RoadNetId);
	values.push_back(RoadName);
	values.push_back(float2str(ODvalue));    //ODvalue
	values.push_back(int2str(StatisticInterval));
	values.push_back(int2str(IsStart));
	values.push_back(int2str(IsPause));
	values.push_back(SimuStartTime);
	values.push_back(SimuStartClock);
	values.push_back(Duration);
	values.push_back(int2str(IsFinished));
	values.push_back(SimuStopTime);
	values.push_back(SimuStopClock);
	values.push_back(UpdateTime);

	
	if (mysql->add_data("simrecord", key, values) == 0)
	{
		return 0;
	}

	else
		return 1;
}

int SimRecord::isSimStart(VspdCToMySQL* mysql)
{
	char* SQL = "select * from simrecord where SimIndex=(select max(SimIndex) from simrecord);";
	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL,15,Msg);
	if (res.size() != 0)
	{
		int is_start = str2int(res[0][6]);
		if (is_start == 1)
			return str2int(res[0][0]);
		else
			return 0;
	}
	else return 0;
}

bool SimRecord::isSimPause(VspdCToMySQL* mysql)
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

bool SimRecord::isSimStop(VspdCToMySQL* mysql)
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

double SimRecord::getODvalue(VspdCToMySQL* mysql)
{
	char* SQL = "select * from simrecord where SimIndex=(select max(SimIndex) from simrecord);";
	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL, 15, Msg);
	double od = 0.0;
	if (res.size() != 0)
	{
		od= atof(res[0][4].c_str());
	}
	return od;
}
