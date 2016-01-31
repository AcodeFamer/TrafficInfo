/*********************相位表*****************************/
#ifndef __PHASE_H__
#define __PHASE_H__

class Phase
{
	int PlanIndex;
	int PhaseId;
	string CrossingId;
	float GreenTime;
	float AmberTime;
	float RedTime;
	int IsUpdate;
public:
	Phase();
	Phase(int plan_index, int phase_id, string crossing_id, float green_time, float amber_time, float red_time, int is_update);
	~Phase();

	int writeDataToSql(VspdCToMySQL* mysql);

	//根据制定的控制方案，获取每一个相位的绿灯，红灯时间
	static vector<vector<string>>  getSingalTimeByIndex(VspdCToMySQL* mysql, int plan_index);

	static vector<Phase> allPhase;
};

#endif