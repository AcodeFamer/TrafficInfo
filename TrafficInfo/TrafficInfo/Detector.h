/*****************检测器表**************/

#ifndef __DETECTOR_H__
#define __DETECTOR_H__

#include "utility.h"
#include "VspdCToMySQL.h"
#include <string>
#include <set>
using namespace std;


class Detector
{
    
    string DetectorId;

	string DetectorName;

    string LinkId;

    int Flag;

	int DownStreamIndex;

	string CrossingId;

    int LaneNum;
    
public:
    Detector();
	Detector::Detector(string detector_id, string detector_name, string link_id, int flag, int down_stream_index, string crossing_id, int lane_num);
    ~Detector();
    
    int writeDataToSql(VspdCToMySQL* mysql);

	//返回当上中下游标识为2的所有的检测器Id
	static set<string> getLinkIdWhenFlagEqualsTwo(VspdCToMySQL *mysql);
	
	static vector<Detector> allDetector;
};


#endif