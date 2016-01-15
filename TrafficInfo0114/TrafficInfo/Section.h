#ifndef __SECTION_H__
#define __SECTION_H__

#include "VspdCToMySQL.h"
#include "utility.h"
#include <string>
using namespace std;

class Section
{
	//��������
	string SectionName;
	//�Ƿ�˫��
	int IsTwoWay;
	//����1·��ID
	string LinkId1;
	//����1�����ID
	string DetectorId1;
	//����2·��ID
	string LinkId2;
	//����2�����ID
	string DetectorId2;
public:
	Section();
	Section(string name, int is_two_way, string link_id_1, string detector_id_1, string link_id_2, string detector_id_2);
	~Section();


	int writeDataToSql(VspdCToMySQL* mysql);

};



#endif