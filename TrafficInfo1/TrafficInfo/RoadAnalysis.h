#ifndef __ROADANALYSIS_H__
#define __ROADANALYSIS_H__

#include "stdafx.h"
#include <vector>
#include <map>
#include "DBoperation.h"

//·��������
class RoadAnalysis
{
private:
	//���ݿ���������
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
	//����Link������������ϸ
	void analyseLink();
	//�����ڵ�Id������·�������нڵ㣬���ӣ�·�Σ����Ʒ�������λ��Ϣ
	void analyseNode();
	//������λ��������λ������ϸ��
	void analysePhase();
	//���������
	void analyseDetector();
	//��������
	void analyseSection();

public:
	vector<DETECTOR*> allDetectorPointer;

	vector<string>  allDetectorId;
	
	map<DETECTOR*, string> allDetectorIdByPointer;
	//�����źŻ�·�ڵ�id��ָ��
	map<string, NODE*> AllSignalisedNode;

	void getAllDetectorPointer(int detectorNum);
	void getAllDetectorId(int detectorNum);

	bool isNewRoadNet(string road_name);

	void updateRoadNetData();
	
private:
	vector<LINK*> getAllLinkPointer(int LinkNum);

	//��ȡ·�������еĽڵ�ָ��
	vector<NODE*> getAllNodePointer(int nodeNum);
	//��ȡ·�������еĽڵ�Id
	vector<string> getAllNodeId(int nodeNum);
	//�ж�·���Ƿ����
	int IsRoadLinkIdExist(string road_link_id);

};


#endif