#include"stdafx.h"
#include "CrossingStream.h"


vector<CrossingStream> CrossingStream::allCrossingStream;

CrossingStream::CrossingStream()
{

}

CrossingStream::CrossingStream(string crossing_id, string link_in_id, string link_out_id, string road_in_id,string road_out_id, string pri)
{
	CrossingId = crossing_id;
	LinkInId = link_in_id;
	LinkOutId = link_out_id;
	RoadInId = road_in_id;
	RoadOutId = road_out_id;
	Priority = pri;
}

CrossingStream::~CrossingStream()
{

}

int CrossingStream::writeDataToSql(VspdCToMySQL* mysql)
{
	vector<string> key;
	key.push_back("CrossingId");
	key.push_back("LinkInId");
	key.push_back("LinkOutId");
	key.push_back("RoadInId");
	key.push_back("RoadOutId");
	key.push_back("Priority");

	vector<string> values;
	values.push_back(CrossingId);
	values.push_back(LinkInId);
	values.push_back(LinkOutId);
	values.push_back(RoadInId);
	values.push_back(RoadOutId);
	values.push_back(Priority);

	if (mysql->add_data("crossingstream", key, values) == 0)
	{
		return 0;
	}

	else
		return 1;
}
