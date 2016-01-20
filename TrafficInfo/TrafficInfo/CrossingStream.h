#ifndef __CROSSINGSTREAM_H__
#define __CROSSINGSTREAM_H__

#include "VspdCToMySQL.h"
#include "utility.h"
#include <string>
using namespace std;


class CrossingStream
{
	string CrossingId;
	string LinkInId;
	string LinkOutId;
	string RoadInId;
	string RoadOutId;
	string Priority;

public:
	CrossingStream();
	CrossingStream(string, string, string, string, string, string);
	~CrossingStream();

	int writeDataToSql(VspdCToMySQL* mysql);
};


#endif