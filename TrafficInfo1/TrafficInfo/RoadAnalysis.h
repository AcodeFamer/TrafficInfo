#ifndef __ROADANALYSIS_H__
#define __ROADANALYSIS_H__

#include "stdafx.h"
#include <vector>
#include <map>
#include "DBoperation.h"

//路网解析类
class RoadAnalysis
{
private:
	//数据库操作类对象
	DBoperation* db_oper;
public:
	RoadAnalysis();
	~RoadAnalysis();
	DBoperation* getDBoperation();
public:
	 vector<NodeInfo> allNode;
	 vector<RoadInfo> allRoad;
	 vector<LinkInfo> allLink;
	 vector<CrossingStream> allCrossingStream;
	 vector<ControlState> allControlState;
	 vector<Detector> allDetector;
	 vector<Section> allSection;
	 vector<ControlPlan> allControlPlan;
	 vector<Phase> allPhase;
	 vector<PhaseStream> allPhaseStream;
	 
public:
	int LinkNum;
	int NodeNum;
	int ZoneNum;
	int DetectorNum;

public:
	//解析Link，生成连接明细
	void analyseLink();
	//解析节点Id，生成路网的所有节点，连接，路段，控制方案，相位信息
	void analyseNode();
	//解析相位，生成相位车流明细表
	void analysePhase();
	//解析检测器
	void analyseDetector();
	//解析断面
	void analyseSection();

public:
	vector<DETECTOR*> allDetectorPointer;

	vector<string>  allDetectorId;
	
	map<DETECTOR*, string> allDetectorIdByPointer;
	//所有信号化路口的id和指针
	map<string, NODE*> AllSignalisedNode;

	void getAllDetectorPointer(int detectorNum);
	void getAllDetectorId(int detectorNum);

	bool isNewRoadNet(string road_name);

	void updateRoadNetData();
	
private:
	vector<LINK*> getAllLinkPointer(int LinkNum);

	//获取路网中所有的节点指针
	vector<NODE*> getAllNodePointer(int nodeNum);
	//获取路网中所有的节点Id
	vector<string> getAllNodeId(int nodeNum);
	//判断路段是否存在
	int IsRoadLinkIdExist(string road_link_id);

};


#endif