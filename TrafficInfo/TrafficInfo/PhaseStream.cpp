#include "stdafx.h"
#include "PhaseStream.h"

PhaseStream::PhaseStream()
{

}

PhaseStream::PhaseStream(string phase_index, string stream_index, string dir_flag, string phase_id, string plan_index, string crossing_index, string link_in_id, string link_out_id)
{
	PhaseIndex = phase_index;
	StreamIndex = stream_index;
	DirectionFlag = dir_flag;
	PhaseId = phase_id;
	PlanIndex = plan_index;
	CrossingId = crossing_index;
	LinkInId = link_in_id;
	LinkOutId = link_out_id;
}

PhaseStream::~PhaseStream()
{

}

int PhaseStream::writeDataToSql(VspdCToMySQL* mysql)
{
	vector<string> key;
	key.push_back("PhaseIndex");
	key.push_back("StreamIndex");
	key.push_back("DirectionFlag");
	key.push_back("PhaseId");
	key.push_back("PlanIndex");
	key.push_back("CrossingId");
	key.push_back("LinkInId");
	key.push_back("LinkOutId");

	vector<string> values;
	values.push_back(PhaseIndex);
	values.push_back(StreamIndex);
	values.push_back(DirectionFlag);
	values.push_back(PhaseId);
	values.push_back(PlanIndex);
	values.push_back(CrossingId);
	values.push_back(LinkInId);
	values.push_back(LinkOutId);

	if (mysql->add_data("phasestream", key, values) == 0)
	{
		return 0;
	}

	else
		return 1;
}
