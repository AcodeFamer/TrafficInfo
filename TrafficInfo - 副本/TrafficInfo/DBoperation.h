#ifndef __DBOPERATION_H__
#define __DBOPERATION_H__

#include "VspdCToMySQL.h"
#include <set>
#include <map>

//****************************************���ݿ������*****************************************
class DBoperation
{
	VspdCToMySQL* mysql;
	//�����ֺͱ��ֶ���Ϣ
	map<string, vector<string>> table;
public:
	DBoperation();
	~DBoperation();
	VspdCToMySQL* getMySql();
	//������Ӧ�����ݿ��
	void updateDataTable();
	//���ݸ���LINKָ���ȡ��Ӧ������·��id
	int getLinkInfo(int flag, LINK* pLink, string& road_id);
	set<string> getLinkIdWhenFlagEqualsTwo();
	vector<string> getAllNetId();
	//����µ�·����Ϣ
	void addNewRoadNet(RoadNetInfo road_net_info);
	//�����ر���Ϣ
	void clearTable();
	//�ж�·���Ƿ��޸�
	bool IsRoadNetModified(string net_name, int nodeNum, int linkNum, int zoneNum);
	//����·����Ϣ��·���޸�ʱ���ã�
	void updateRoadNetInfoTable(string net_name, int nodeNum, int linkNum, int zoneNum);
	//�жϷ����Ƿ�����
	int  isSimStart();
	//�жϷ����Ƕ���ͣ
	bool isSimPause();
	bool isSimStop();
	//�����ݿ��л�ȡOD_valueֵ
	double getODvalue();
	//�鿴���Ʒ��������Ϣ���Ƿ���£�·��id��planIndex��
	vector<vector<string>> getPlanUpdateIndex();
	//�鿴��λ����ָ��planIndex��������λ��Ϣ
	vector<vector<string>> getSingalTimeByIndex(int plan_index);
	//�������֣���Ӧ���ݣ�д�����ݿ��
	template<class T> void roadNetDataWriteToDatabase(string table_name,vector<T> data);
};
#endif