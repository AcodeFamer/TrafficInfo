#include "stdafx.h"
#include "Phase.h"


vector<Phase> Phase::allPhase;


Phase::Phase()
{

}

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

Phase::~Phase()
{

}

int Phase::writeDataToSql(VspdCToMySQL* mysql)
{
	vector<string> key;
	key.push_back("PlanIndex");
	key.push_back("PhaseId");
	key.push_back("CrossingId");
	key.push_back("GreenTime");
	key.push_back("AmberTime");
	key.push_back("RedTime");
	key.push_back("IsUpdate");

	vector<string> values;
	values.push_back(int2str(PlanIndex));
	values.push_back(int2str(PhaseId));
	values.push_back(CrossingId);
	values.push_back(float2str(GreenTime));
	values.push_back(float2str(AmberTime));
	values.push_back(float2str(RedTime));
	values.push_back(int2str(IsUpdate));

	if (mysql->add_data("phase", key, values) == 0)
	{
		return 0;
	}

	else
		return 1;
}

vector<vector<string>> Phase::getSingalTimeByIndex(VspdCToMySQL* mysql, int plan_index)
{
	string SQL = "select GreenTime,AmberTime,RedTime,IsUpdate from phase where PlanIndex=" + int2str(plan_index);

	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL.c_str(),4, Msg);

	//读取完成后清除标志位
	string SQL_clear = "update phase set IsUpdate='0' where IsUpdate='1'";
	mysql->UpdateData(SQL_clear.c_str(), Msg);
	return res;
}

