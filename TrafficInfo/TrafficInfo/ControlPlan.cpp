#include "stdafx.h"
#include "ControlPlan.h"


ControlPlan::ControlPlan()
{

}

ControlPlan::ControlPlan(string crossing_id, int phase_num, int is_period_fixed, int is_actuated_control, float period, float offset, int is_update)
{
	CrossingId = crossing_id;
	PhaseNum = phase_num;
	IsPeriodFixed = is_period_fixed;
	IsActuatedControl = is_actuated_control;
	Period = period;
	PhaseOffset = offset;
	IsUpdate = is_update;
}

ControlPlan::~ControlPlan()
{

}

int ControlPlan::writeDataToSql(VspdCToMySQL *mysql)
{
	vector<string> key;
	key.push_back("CrossingId");
	key.push_back("PhaseNum");
	key.push_back("IsPeriodFixed");
	key.push_back("IsActuatedControl");
	key.push_back("Period");
	key.push_back("PhaseOffset");
	key.push_back("IsUpdate");


	vector<string> values;
	values.push_back(CrossingId);
	values.push_back(int2str(PhaseNum));
	values.push_back(int2str(IsPeriodFixed));
	values.push_back(int2str(IsActuatedControl));
	values.push_back(float2str(Period));
	values.push_back(float2str(PhaseOffset));
	values.push_back(int2str(IsUpdate));

	if (mysql->add_data("controlplan", key, values) == 0)
	{
		return 0;
	}

	else
		return 1;
}

vector<vector<string>> ControlPlan::getPlanUpdateIndex(VspdCToMySQL* mysql)
{
	//查询控制方案表,出现更新的控制方案编号
	char* SQL = "select PlanIndex,CrossingId,Period from controlplan where IsUpdate='1';";
	string msg;
	vector<vector<string>> res=mysql->SelectData(SQL, 3,msg);

	
	//读取完成后清除标志位
	SQL = "update controlplan set IsUpdate='0' where IsUpdate='1'";
	mysql->UpdateData(SQL, msg);
	return res;
}

