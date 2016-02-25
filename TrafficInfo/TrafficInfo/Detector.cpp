#include "stdafx.h"
#include "Detector.h"


vector<Detector> Detector::allDetector;

Detector::Detector()
{

}

Detector::Detector(string detector_id, string detector_name, string link_id, int flag, int down_stream_index, string crossing_id,int lane_num)
{

	DetectorId=detector_id;

	DetectorName = detector_name;
	
	LinkId = link_id;
	
	Flag = flag;

	DownStreamIndex = down_stream_index;

	CrossingId = crossing_id;

	LaneNum = lane_num;

}

Detector::~Detector()
{

}

int Detector::writeDataToSql(VspdCToMySQL* mysql)
{
	vector<string> key;
	key.push_back("DetectorId");
	key.push_back("DetectorName");
	key.push_back("LinkId");
	key.push_back("Flag");
	key.push_back("DownStreamIndex");
	key.push_back("CrossingId");
	key.push_back("LaneNum");

	vector<string> values;
	values.push_back(DetectorId);
	values.push_back(DetectorName);
	values.push_back(LinkId);
	values.push_back(int2str(Flag));
	values.push_back(int2str(DownStreamIndex));
	values.push_back(CrossingId);
	values.push_back(int2str(LaneNum));

	if(mysql->add_data("detector",key,values)==0)
		return 0;
	else 
		return 1;
}

set<string> Detector::getLinkIdWhenFlagEqualsTwo(VspdCToMySQL *mysql)
{
	char * SQL = "SELECT LinkId FROM detector WHERE  Flag=2";
	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL, 1, Msg);

	set<string> allDetectorId;
	for (size_t i = 0; i < res.size(); i++)
		allDetectorId.insert(res[i][0]);
	return allDetectorId;
}
