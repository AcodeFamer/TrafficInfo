/****************ʵʱ��ͨ��Ϣ��************************/
#ifndef __TRAFFICINFO_H__
#define __TRAFFICINFO_H__

class TrafficInfo
{
	//������
	int SimuIndex;
	//�����Id
	string DetectorId;
	//�������
	string LaneId;
	//��¼ʱ��
	string RecordTime;
	//������
	int CarFlow;
	//ƽ���ٶ�
	float AvgVelocity;
	//ռ��ʱ��
	float OccupancyTime;
public:
	TrafficInfo();
	TrafficInfo(int simu_index, string detector_id, string lane_id, string record_time, int car_flow, float velocity_ave, float occupancy_time);
	~TrafficInfo();

	static void writeAllDataToSql(VspdCToMySQL* mysql);

	static string simu_time;
	//������
	static int SimIndex;
};


#endif