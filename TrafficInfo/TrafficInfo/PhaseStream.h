/*********相位车流*************/
#ifndef __PHASESTREAM_H__
#define __PHASESTREAM_H__

class PhaseStream
{
	string PhaseIndex;
	string StreamIndex;
	string Priority;
	string DirectionFlag;
	string PhaseId;
	string PlanIndex;
	string CrossingId;
	string LinkInId;
	string LinkOutId;
public:
	PhaseStream();
	PhaseStream(string phase_index, string stream_index, string priority, string dir_flag, string phase_id, string plan_index, string crossing_index, string link_in_id, string link_out_id);
	~PhaseStream();

	int writeDataToSql(VspdCToMySQL* mysql);

	static vector<PhaseStream> allPhaseStream;

};

#endif