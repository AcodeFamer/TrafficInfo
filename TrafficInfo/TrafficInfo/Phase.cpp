#include "stdafx.h"
#include "Phase.h"

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

