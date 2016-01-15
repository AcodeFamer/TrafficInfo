#ifndef __SECTION_H__
#define __SECTION_H__

#include "VspdCToMySQL.h"
#include "utility.h"
#include <string>
using namespace std;

class Section
{
	//断面名称
	string SectionName;
	//是否双向
	int IsTwoWay;
	//方向1路段ID
	string LinkId1;
	//方向1检测器ID
	string DetectorId1;
	//方向2路段ID
	string LinkId2;
	//方向2检测器ID
	string DetectorId2;
public:
	Section();
	Section(string name, int is_two_way, string link_id_1, string detector_id_1, string link_id_2, string detector_id_2);
	~Section();


	int writeDataToSql(VspdCToMySQL* mysql);

};



#endif