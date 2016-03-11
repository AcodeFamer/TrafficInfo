#ifndef __CROSSINGSINGAL_H__
#define __CROSSINGSINGAL_H__
/**************************************路口信号************************/
#include <vector>
#include "VspdCToMySQL.h"
using namespace std;

//控制方案类型
enum
{
	PLANTYPE_RED = 0,               //红灯
	PLANTYPE_YELLOW,                //黄灯
	PLANTYPE_FIX_PEROID,            //固定周期
	PLANTYPE_ACTUAL_CONTROL,        //感应控制
	PLANTYPE_ONLINE_CONTROL,        //在线控制
};

struct SingalInfo
{
	//该路口当前执行的控制方案编号（路口信号化时有效）
	int planIndex;
	//该路口当前执行的控制方案总周期数（路口信号化时有效）
	int phaseNum;
	//该路口当前执行的控制方案总周期数（路口信号化时有效）
	int peroid;
	//相位差（路口信号化时有效）
	int phaseOffset;
	//该路口当前执行控制方案每个相位的绿灯时间(包含三秒的黄灯时间)（路口信号化时有效）
	vector<int> greenTime;
	//该路口当前执行控制方案每个相位的红灯时间(包含三秒的黄灯时间)（路口信号化时有效）
	vector<int> redTime;
};

class CrossingSingal
{
public:
	//该路口节点id
	string crossingId;
	//该路口是否信号化
	int isSingal;
	//路口的仿真否开启
	static int IsStart;
	//该路口控制方案的类型
	int planType;
private:
	//当前正在执行的信号控制方案信息
	SingalInfo singal_info;
	//下个周期执行的信号控制方案信息
	SingalInfo singal_info_next;
	//该路口当前执行控制方案当前执行到哪个相位（仿真运行时）
	int phaseIndex;
	//该路口当前相位执行到第几秒（仿真运行时）
	int second;
	//是否是第一个相位(固定周期的控制方案)
	int isFirstPhase;
	//流入LINK id(按车流编号,从下标1开始)
	vector<string> linkInId;
	vector<string> linkOutId;

	//该路口正在执行的控制方案各个相位的车流权限(0下标不用)（每次切换下一个周期时从数据库获取）;
	vector<vector<string>> phaseStreamPri;
	//该路口当前车流的权限
	vector<string> curStreamPri;
private:
	static VspdCToMySQL* mysql;
public:
	CrossingSingal(string crossing_id, vector<string> stream_pri,vector<string> link_in_id, vector<string> link_out_id);
	~CrossingSingal();

	//获取当前正在执行的信号信息
	SingalInfo getSingalInfo();
	//从nodeinfo表中获取该路口id对应是否信号化(没有查到返回-1)
	int isCrossingSinglised();
	//设置当前控制方案编号
	void setPlanIndex(int plan_index);
	//设置路口是否信号化
	void setCrossingSingalised(int is_singlised);

	//从crossingstream中查询priority
	vector<vector<string>> getCrossingstreamInfo();

	//从controlplan中获取Active的控制方案信息（最多是每个路口节点有一个plan是active的）
	vector<string> getActivePlanInfo();

	//从相位表中获取该路口的相位信息
	void getPhaseInfo(vector<int>& all_green_time, vector<int>& all_red_time);

	//设置该路口的当前执行的控制方案信息
	void setSingalInfo(SingalInfo s);

	//设置该路口的下一个周期执行的控制方案信息
	void setSingalInfoNext(SingalInfo s_next);
	
	//获取该路口当前控制方案编号
	int getPlanIndex();
	//执行当期前控制方案
	void execute_singal_control();
	//设置该路口的某条车流编号权限车流权限
	void setStreamPriority(int stream_index, string pri);

	//设置控制方案类型
	void setPlanType(int type);
	//初始化controlstate所有车流权限为Major
	static void initControlState();
	//初始化设置mysql指针
	static void setMysql(VspdCToMySQL* my_sql);
	//当控制状态变化时,更新控制状态
	void  updateControlState(int stream_index, string pri);

	//清空IsUpdate标志位
	static void clearIsUpdate(string tablename);
private:
    //从phasestream表中获取所有相位的所有车流权限情况(查询条件：当前控制方案编号，该路口）
	void getPhaseStreamPri();

	//清空IsUpdate标志
	void clearIsUpdate();

	
};


#endif