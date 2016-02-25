#ifndef __DBOPERATION_H__
#define __DBOPERATION_H__

#include "VspdCToMySQL.h"
#include <set>
#include <map>

//****************************************���ݿ������*****************************************
class DBoperation
{
private:
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


	//��ѯ������ϸ������������·��Ϊ��·��id������link�ĳ���
	vector<vector<string>> getLinkDistance(string link_id);
	//��ȡphase����ָ����λ���PhaseIndex�Ŀ��Ʒ������(��������ֵ����Ϊ0��ʾ��ȡʧ��)����λ��ţ�����·����Ϣ
	int getPhaseInfo(int PhaseIndex, string& phase_id, string& crossing_id);

	//��������·�ڲ�ѯ·�ڳ������������·����Ϣ����������·��id������·��id,���ض�Ӧ��·�ڳ������StreamIndex����ȡʧ�ܷ���0
	vector<vector<string>> getCrossStreamInfo(string crossing_id);

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
	template<class T> void dataWriteToDatabase(string table_name, vector<T>& data);


};

//ģ�庯����ʵ�ֲ��ܷ���cpp�ļ��У��������ֱ������
template<class T>
void DBoperation::dataWriteToDatabase(string table_name,  vector<T>& data)
{
	/**************************************��������ͷ�� insert into table_name(�ֶ�1���ֶ�2����������)*/
	//��ȡ�ñ������ֶ���Ϣ
	vector<string> name = table[table_name];
	string SQL_insert = "insert into " + table_name + "(";
	for (size_t j = 0; j < name.size() - 1; j++)
	{
		SQL_insert = SQL_insert + name[j] + ",";
	}
	SQL_insert = SQL_insert + name[name.size() - 1] + ") values ";

	int count_db_write = 0;//ÿ�β���������������
	string SQL;
	//����ڵ���Ϣ��
	for (size_t i = 0; i < data.size(); i++)
	{
		//һ�β����������
		SQL = SQL + data[i].getDataString() + ",";
		//������������
		count_db_write++;
		//�ۼƵ�30������
		if (count_db_write == 30)
		{
			//ȥ�����һ������
			SQL.erase(SQL_insert.end());
			//������SQL�������
			SQL_insert = SQL_insert + SQL;
			//�������
			string Msg;
			mysql->InsertData(SQL_insert.c_str(), Msg);
			//count_db_write��0
			count_db_write = 0;
		}
	}
	//*********************************************���ʣ����30�����ݲ���
	if (count_db_write != 0)
	{
		//ȥ�����һ������
		SQL.erase(SQL_insert.end());
		//������SQL�������
		SQL_insert = SQL_insert + SQL;
		//�������
		string Msg;
		mysql->InsertData(SQL_insert.c_str(), Msg);
		//count_db_write��0
		count_db_write = 0;
	}

}

#endif