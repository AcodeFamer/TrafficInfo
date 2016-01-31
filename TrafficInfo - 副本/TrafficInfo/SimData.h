#ifndef __SIMDATA_H__
#define __SIMDATA_H__

#include <string>
using namespace std;
class SimData
{
public:
	//��ǰ����ʱ��
	string simuTime;
	//
	int simState;  //��ǰ����״̬ 0��δ��ʼ 1������  2����ͣ  3������

	int simIndex;//��ǰ������

	float odValue;  //����ʱ��ODֵ

	//ÿ���������Ӧ�м�����Ȧ
	vector<int> loopNumArray;
	//������Ȧ��ָ��
	vector<vector<LOOP*>> netLoop;


	//·����ÿһ��detector��ÿһ��loopͨ���ĳ�����(�ۻ���)(�г�ͨ��ʱ��ˢ��)
	vector<vector<int>> countEveryLoop;
	//·����ÿһ��detector��ÿһ��loopͨ���ĳ�����(�ۻ���)(������ʱ��ʱ��ˢ��)
	vector<vector<int>> countEveryLoopDuration;
	//·����ÿһ��detector��ÿһ��loopͨ���ĳ�����(�����)
	vector<vector<int>> countEveryLoopDiff;
	//·����ÿһ��detector������Ȧͨ���ĳ�����
	vector<int> countEveryDetector;

	//ÿһ����Ȧ��һ������ռ��ʱ��(�г�ͨ��ʱˢ��)
	vector<vector<float>> occupancyEveryLoop;
	//ͳ��ʱ���ڣ�ռ��ʱ����ۼ�
	vector<vector<float>> occupancyEveryLoopDuration;
	//��Ȧ�Ƿ񱻳�ռ��
	vector<vector<int>> isOccupiedEveryLoop;

	//��Ȧ��������ƽ�����٣���ֹ��ǰʱ�̣�
	vector<vector<float>> velocityEveryLoop;
	//ͳ��ʱ����ƽ������
	vector<vector<float>> velocityEveryLoopDuration;


	//·������ʱ��demand����
	vector<vector<float>> demandMatrix;
	

	//��ʼ����ر���
	void SimData::initCountLoop(int detectorNum);
	void SimData::initCountDetector(int detectorNum);

	//��ʼ��demand����
	void initDemandMatrix(int zoneNum);

	//���ݴ����ݿ��ȡ��ODvalue����demand����
	void setDemandMatrix(int zoneNum, float od_value);
};
#endif