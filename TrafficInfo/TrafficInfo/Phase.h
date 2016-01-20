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
};

#endif