#ifndef __SIMRECORD_H__
#define __SIMRECORD_H__

class SimRecord
{
	string RoadNetId;
	string RoadName;
	float ODvalue;
	int StatisticInterval;
	int IsStart;
	int IsPause;
	string SimuStartTime;
	string SimuStartClock;
	string Duration;
	int IsFinished;
	string SimuStopTime;
	string SimuStopClock;
	string UpdateTime;
public:
	SimRecord();
	SimRecord(string road_net_id,string road_name,float OD_value,
		      int statistic_interval,int is_start,int is_pause,string simu_start_time,string simu_start_clock,
			  string duration,int is_finished,string simu_stop_time,string simu_stop_clock,string update_time);

	~SimRecord();

	int writeDataToSql(VspdCToMySQL* mysql);
	//���������ֶ��Ƿ�Ϊ1
	static int isSimStart(VspdCToMySQL* mysql);
	//������ͣ�ֶ��Ƿ�Ϊ1
	static bool isSimPause(VspdCToMySQL* mysql);
	//����ֹͣ�ֶ��Ƿ�Ϊ1
	static bool isSimStop(VspdCToMySQL* mysql);

	//get ODֵ 
	static double getODvalue(VspdCToMySQL* mysql);
};

#endif