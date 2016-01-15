/*****************璺淇℃伅琛?**************/

#ifndef __DETECTOR_H__
#define __DETECTOR_H__

#include "utility.h"
#include "VspdCToMySQL.h"
#include <string>
#include <set>
using namespace std;


class Detector
{
    //妫€娴嬪櫒ID
    string DetectorId;

	string DetectorName;


    //鎵€灞炶矾娈礗D
    string LinkId;
    //涓婁笅涓父鏍囪瘑
    int Flag;
    //涓嬫父妫€娴嬪櫒搴忓彿
	int DownStreamIndex;

	string CrossingId;

    //妫€娴嬭溅閬撴暟
    int LaneNum;
    
    
public:
    Detector();
	Detector::Detector(string detector_id, string detector_name, string link_id, int flag, int down_stream_index, string crossing_id, int lane_num);
    ~Detector();
    
    int writeDataToSql(VspdCToMySQL* mysql);

	//返回当上中下游标识为2的所有的检测器Id
	static set<string> getLinkIdWhenFlagEqualsTwo(VspdCToMySQL *mysql);
};


#endif