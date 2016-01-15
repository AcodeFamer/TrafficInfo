#include "stdafx.h"
#include "Section.h"

Section::Section()
{
}

Section::Section(string name, int is_two_way, string link_id_1, string detector_id_1, string link_id_2, string detector_id_2)
{
	//��������
	SectionName=name;
	//�Ƿ�˫��
	IsTwoWay = is_two_way;
	//����1·��ID
	LinkId1 = link_id_1;
	//����1�����ID
	DetectorId1 = detector_id_1;
	//����2·��ID
	LinkId2 = link_id_2;
	//����2�����ID
	DetectorId2 = detector_id_2;
}

Section::~Section()
{

}

int Section::writeDataToSql(VspdCToMySQL* mysql)
{
	vector<string> key;
	key.push_back("SectionName");
	key.push_back("IsTwoWay");
	key.push_back("LinkId1");
	key.push_back("DetectorId1");
	key.push_back("LinkId2");
	key.push_back("DetectorId2");

	vector<string> values;
	values.push_back(SectionName);
	values.push_back(int2str(IsTwoWay));
	values.push_back(LinkId1);
	values.push_back(DetectorId1);
	values.push_back(LinkId2);
	values.push_back(DetectorId2);

	if (mysql->add_data("section", key, values) == 0)
	{
		return 0;
	}

	else
		return 1;
}
