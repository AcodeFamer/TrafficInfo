/*********路网信息，解析路网******/
#ifndef __ROADNETINFO_H__
#define __ROADNETINFO_H__

#include "VspdCTOMySQL.h"
#include <iostream>
#include <vector>
#include <map>
#include "utility.h"
using namespace std;

class RoadNetInfo
{
    //璺綉ID
    string RoadNetId;
    //璺綉鍚嶇О
    string RoadNetName;
    //鑺傜偣鏁?
    int NodeNum;
    //link鏁?
    int LinkNum;
    //灏忓尯鏁?
    int SubzoneNum;
    //鏄惁浠跨湡杩愯
    int IsSimRunning;

	
    
public:
	//VspdCToMySQL *mysql;
    //鏋勯€犲嚱鏁板拰鏋愭瀯鍑芥暟
    RoadNetInfo();
    RoadNetInfo(string,string,int,int,int,int);
    ~RoadNetInfo();
    //鏁版嵁鍐欏叆鏁版嵁搴?
    int writeDataToSql(VspdCToMySQL *mysql);

	//从数据库中获取所有的路网名字
	static vector<string> getAllNetId(VspdCToMySQL *mysql);
	//判断是否为新路网
	static bool isNewRoadNet(VspdCToMySQL *mysql,string road_name);
	
	//获取路网中所有的节点指针
	static vector<NODE*> getAllNodePointer(int nodeNum);
	//获取路网中所有的节点Id
	static vector<string> getAllNodeId(int nodeNum);

	static vector<LINK*> getAllLinkPointer(int LinkNum);

	//获取路网中所有检测器指针
	static void getAllDetectorPointer(int detectorNum);
	//获取路网中所有的检测器Id
	static void getAllDetectorId(int detectorNum);

	



	//判断路网是否修改
	static bool IsRoadNetModified(VspdCToMySQL* mysql, string net_name);

	//更新roadnetinfo表
	static void updateRoadNetInfoTable(VspdCToMySQL* mysql, string net_name);

	//当为新路网或者是路网修改过时，更新nodeinfo，roadInfo，section，detector表
	static void updateRoadInfo(VspdCToMySQL* mysql);

	static void clearTable(VspdCToMySQL* mysql);

	static vector<DETECTOR*> allDetectorPointer;
	static vector<string> allDetectorId;
	static map<DETECTOR*, string> allDetectorIdByPointer; //根据检测器指针查找id


	//初始化countEveryLoop，countEveryLoopDiff 
	static void initCountLoop();
	//初始化countEveryDetector
	static void initCountDetector();

	//node数
	static int nodeNum;
	//link数
	static int linkNum;
	//zone数
	static int zoneNum;
	//detector数
	static int detectorNum;

	//所有线圈的指针
	static vector<vector<LOOP*>> netLoop;
    //每个检测器对应有几个线圈
	static vector<int> loopNumArray;


	//路网中每一个detector的每一个loop通过的车辆数(累积量)(有车通过时就刷新)
	static vector<vector<int>> countEveryLoop;
	//路网中每一个detector的每一个loop通过的车辆数(累积量)(到达间隔时间时才刷新)
	static vector<vector<int>> countEveryLoopDuration;
	//路网中每一个detector的每一个loop通过的车辆数(差分量)
	static vector<vector<int>> countEveryLoopDiff;
	//路网中每一个detector所有线圈通过的车辆数
	static vector<int> countEveryDetector;

	//每一个线圈上一辆车的占有时间(有车通过时刷新)
	static vector<vector<float>> occupancyEveryLoop;
	//统计时段内，占有时间的累加
	static vector<vector<float>> occupancyEveryLoopDuration;
	//线圈是否被车占用
	static vector<vector<int>> isOccupiedEveryLoop;

	//线圈所属车道平均车速（截止当前时刻）
	static vector<vector<float>> velocityEveryLoop;
	//统计时段内平均车速
	static vector<vector<float>> velocityEveryLoopDuration;
	//路网仿真时的demand矩阵
	static vector<vector<float>> demandMatrix;
	//仿真路网时的OD比例值
	static float ODvalue;
	//初始化OD矩阵
	static void initDemandMatrix();

	static void setDemandMatrix(float od_value);


	//所有信号化路口的id和NODE*  map
	static map<string, NODE*> AllSignalisedNode;
};


#endif