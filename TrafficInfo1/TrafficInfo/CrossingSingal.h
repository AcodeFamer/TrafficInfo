#ifndef __CROSSINGSINGAL_H__
#define __CROSSINGSINGAL_H__
/**************************************·���ź�************************/
#include <vector>
#include "VspdCToMySQL.h"
using namespace std;


struct SingalInfo
{
	//��·�ڵ�ǰִ�еĿ��Ʒ�����ţ�·���źŻ�ʱ��Ч��
	int planIndex;
	//��·�ڵ�ǰִ�еĿ��Ʒ�������������·���źŻ�ʱ��Ч��
	int phaseNum;
	//��·�ڵ�ǰִ�еĿ��Ʒ�������������·���źŻ�ʱ��Ч��
	int peroid;
	//��λ�·���źŻ�ʱ��Ч��
	int phaseOffset;
	//��·�ڵ�ǰִ�п��Ʒ���ÿ����λ���̵�ʱ��(��������ĻƵ�ʱ��)��·���źŻ�ʱ��Ч��
	vector<int> greenTime;
	//��·�ڵ�ǰִ�п��Ʒ���ÿ����λ�ĺ��ʱ��(��������ĻƵ�ʱ��)��·���źŻ�ʱ��Ч��
	vector<int> redTime;
};

class CrossingSingal
{
public:
	//��·�ڽڵ�id
	string crossingId;
	//��·���Ƿ��źŻ�
	int isSingal;
	//·�ڵķ������
	static int IsStart;

private:
	//��ǰ����ִ�е��źſ��Ʒ�����Ϣ
	SingalInfo singal_info;
	//�¸�����ִ�е��źſ��Ʒ�����Ϣ
	SingalInfo singal_info_next;
	//��·�ڵ�ǰִ�п��Ʒ�����ǰִ�е��ĸ���λ����������ʱ��
	int phaseIndex;
	//��·�ڵ�ǰ��λִ�е��ڼ��루��������ʱ��
	int second;
	//�Ƿ��ǵ�һ������
	int isFirstPeroid;
	//����LINK id(���������,���±�1��ʼ)
	vector<string> linkInId;
	vector<string> linkOutId;

	//��·������ִ�еĿ��Ʒ���������λ�ĳ���Ȩ��(0�±겻��)��ÿ���л���һ������ʱ�����ݿ��ȡ��;
	vector<vector<string>> phaseStreamPri;
	//��·�ڵ�ǰ������Ȩ��
	vector<string> curStreamPri;
private:
	 VspdCToMySQL* mysql;
public:
	CrossingSingal(string crossing_id, VspdCToMySQL* my_sql, vector<string> stream_pri,vector<string> link_in_id, vector<string> link_out_id);
	~CrossingSingal();

	//��nodeinfo���л�ȡ��·��id��Ӧ�Ƿ��źŻ�(û�в鵽����-1)
	int isCrossingSinglised();

	//��controlplan�л�ȡActive�Ŀ��Ʒ�����Ϣ�������ÿ��·�ڽڵ���һ��plan��active�ģ�
	vector<string> getActivePlanInfo();

	//����λ���л�ȡ��·�ڵ���λ��Ϣ
	void getPhaseInfo(vector<int>& all_green_time, vector<int>& all_red_time);

	//���ø�·�ڵĵ�ǰִ�еĿ��Ʒ�����Ϣ
	void setSingalInfo(SingalInfo s);

	//���ø�·�ڵ���һ������ִ�еĿ��Ʒ�����Ϣ
	void setSingalInfoNext(SingalInfo s_next);
	
	//��ȡ��·�ڵ�ǰ���Ʒ������
	int getPlanIndex();
	//ִ�е���ǰ���Ʒ���
	void execute_singal_control();
	
	void setStreamPriority(int stream_index, string pri);


private:
    //��phasestream���л�ȡ������λ�����г���Ȩ�����(��ѯ��������ǰ���Ʒ�����ţ���·�ڣ�
	void getPhaseStreamPri();
	//������״̬�仯ʱ,���¿���״̬
	void  updateControlState(int stream_index,string pri);

	//���IsUpdate��־
	void clearIsUpdate();
};


#endif