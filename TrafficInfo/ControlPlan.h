/****************控制方案表******************/
#ifndef __CONTROLPLAN_H__
#define __CONTROLPLAN_H__

#include "utility.h"
#include "VspdCToMySQL.h"
#include <string>

class ControlPlan
{
	string CrossingId;
	int PhaseNum;
	int IsPeriodFixed;
	int IsActuatedControl;
	float Period;
	float PhaseOffset;
	int IsUpdate;
public:
	ControlPlan();
	ControlPlan(string crossing_id, int phase_num, int is_period_fixed, int is_actuated_control, float period, float offset, int is_update);
	~ControlPlan();
	int writeDataToSql(VspdCToMySQL *mysql);

	//查询控制方案修改的方案编号和周期
	static vector<vector<string>> getPlanUpdateIndex(VspdCToMySQL* mysql);

	static vector<ControlPlan> allControlPlan;
};


#endif // !__CONTROLPLAN_H__
