// TrafficInfo.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include "CrossingSingal.h"
#include <vector>
#include "tinyXML/tinyxml.h"



#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

//路网解析对象，负责路网数据解析
RoadAnalysis RA;
//一个仿真数据对象 记录仿真数据
SimData simData;

//保存每个路口的控制信号信息
vector<CrossingSingal> allCrossingSingal;

#define STATISTIC_STEP 5
int statistic_count = 0;

//多少个仿真步长为1s
int STEP_NUM = (int)(1 / qpg_CFG_timeStep());
int step_count = 0;

//声明定时器1的回调函数
void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime);


/*********************************************路网打开前**********************************************/
void qpx_NET_preOpen()
{
	//连接数据库
	//if(RA.getDBoperation()->getMySql()->ConnMySQL(host,str2int(port),dbname,user,passwd,charset,Msg) != 0)
	if (RA.getDBoperation()->getMySql()->ConnMySQL() != 0)
	{
		MessageBox(NULL, "数据库连接失败，请修改配置文件config.xml", "错误", MB_OK);
	}
	else
	{
		MessageBox(NULL, "数据库连接成功", "通知", MB_OK);
	}
}
/*********************************************路网开启后**********************************************/
void qpx_NET_postOpen()
{
	simData.simuTime = "00:00:00";
	//获取路网路径
	char* net_file_path=qpg_NET_dataPath();
	//从路径中取得名字(即为路网Id)
	string netName=getFileName(net_file_path);

	qps_GUI_printf("road net name: %s",netName.c_str());

	//获取节点，路段，子区，检测器数量信息
	//node数
	RA.NodeNum = qpg_NET_nodes();
	//link数
	RA.LinkNum= qpg_NET_links();
	//zone数
	RA.ZoneNum = qpg_NET_zones();
	//detector数
	RA.DetectorNum = qpg_NET_detectors();

	
	qps_GUI_printf("nodeNum=%d,linkNum=%d,zoneNum=%d,detectorNum=%d", RA.NodeNum, RA.LinkNum, RA.ZoneNum, RA.DetectorNum);

	
	//获取检测器指针和检测器id
	RA.getAllDetectorPointer(RA.DetectorNum);
	RA.getAllDetectorId(RA.DetectorNum);
	//初始化仿真数据中所有检测器Id
	simData.allDetectorId = RA.allDetectorId;

	/***********************************判断是否为新路网****************************************/
	//若为新路网
	if(RA.isNewRoadNet(netName))
	{
		MessageBox(NULL, "新路网", "通知", MB_OK);
		//路网信息表中新增一条路网
		RoadNetInfo road_net_info(netName.c_str(), "", RA.NodeNum, RA.LinkNum, RA.ZoneNum, 0);
		RA.getDBoperation()->addNewRoadNet(road_net_info);
		//清空相应数据表
		RA.getDBoperation()->clearTable();
		//解析路网生成相关表数据
		RA.updateRoadNetData();
	}
	//不是新路网
	else
	{
		if (RA.getDBoperation()->IsRoadNetModified(netName,RA.NodeNum,RA.LinkNum,RA.ZoneNum) == 1)
		{
			qps_GUI_printf("road net has modified");
			//更新roadnetinfo表
			RA.getDBoperation()->updateRoadNetInfoTable(netName,RA.NodeNum,RA.LinkNum,RA.ZoneNum);

			//清空相应数据表
			RA.getDBoperation()->clearTable();
			//解析路网生成相关表数据
			RA.updateRoadNetData();
		}
	}

	//*******************************************获取所有线圈指针**************************************************
	for (int i = 0; i < RA.DetectorNum; i++)
	{
		int startLane = qpg_DTC_lane(RA.allDetectorPointer[i]);
		int endLane = qpg_DTC_end_lane(RA.allDetectorPointer[i]);
		simData.loopNumArray.push_back(endLane - startLane + 1);
		vector<LOOP*> temp;
		temp.clear();
		for (int j = 0; j < simData.loopNumArray[i]; j++)
		{
			LOOP* pLOOP = qpg_DTC_multipleLoop(RA.allDetectorPointer[i], j + 1);	
			temp.push_back(pLOOP);
		}
		simData.netLoop.push_back(temp);
	}

	//初始化仿真数据
	simData.initCountLoop(RA.DetectorNum);
	simData.initCountDetector(RA.DetectorNum);

	//清空实时交通信息表
	string Msg;
    RA.getDBoperation()->getMySql()->ClearTable("trafficinfo", Msg);
	RA.getDBoperation()->getMySql()->ClearTable("roadrecord", Msg);


	/*************************设置所有的路口信号为外部控制,设置每个路口的控制方案**********************************************/
	for (int node_i = 0; node_i < RA.NodeNum; node_i++)
	{
		NODE* pNode = qpg_NET_nodeByIndex(node_i + 1);
		string node_id = qpg_NDE_name(pNode);
		//若是路口
		if (node_id.size() == 5 && node_id[3] == '0' && node_id[4] == '0')
		{
			//初始化每个路口的外部信号控制为FALSE
			qps_NDE_externalController(pNode, Bool::PFALSE);
			
			int entry_links = qpg_NDE_entryLinks(pNode);
			int exit_links = qpg_NDE_exitLinks(pNode);
			//将该路口的入link和出link两两配对组成路口车流信息
			vector<string> link_in_id, link_out_id;
			link_in_id.push_back("");
			link_out_id.push_back("");
			for (int in_index = 0; in_index < entry_links; in_index++)
			{
				for (int out_index = 0; out_index < exit_links; out_index++)
				{
					//相应的进出link指针
					LINK* link_in = qpg_NDE_linkEntry(pNode, in_index + 1);
					LINK* link_out = qpg_NDE_link(pNode, out_index + 1);
					//link name
					string in_id = qpg_LNK_name(link_in);
					string out_id = qpg_LNK_name(link_out);
					//按车流编号顺序添加
					link_in_id.push_back(in_id);
					link_out_id.push_back(out_id);
				}
			}
			//初始化路口的当前权限pri为MAJOR
			vector<string> stream_pri(link_in_id.size(), "MAJOR");
			//创建一个路口信号对象，加入所有路口信号中
			CrossingSingal::setMysql(RA.getDBoperation()->getMySql()); //设置数据库对象
			CrossingSingal cs(node_id, stream_pri, link_in_id, link_out_id);
			allCrossingSingal.push_back(cs);
		}
	}
	//初始化controlstate为MAJOR
	CrossingSingal::initControlState();

	//初始化OD矩阵
	simData.initDemandMatrix(RA.ZoneNum);

	simData.initRoadInfo(RA.getDBoperation()->getMySql());

	//开启1s的定时器
	SetTimer(NULL, 1, 1000, TimerProc);
	//初始化仿真编号为0
	simData.simState = 0;

	qps_GUI_printf("STEP_NUM=%d", STEP_NUM);

	qps_GUI_printf("wait for simulation start");
}

int restart_flag = 0;

int seq = 0;
//定时器的回调函数，用于实现仿真控制、信号控制、配置修改
void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{

	/*********************************仿真控制**************************************************/
	//从仿真记录表中读取最后一条仿真记录
	SimState sm = RA.getDBoperation()->getSimRecordInfo();
	//查看仿真记录表，仿真是否暂停或者运行
	if (sm.is_start == 1 && simData.simState == 0)  //仿真第一次开始
	{
		simData.simuTime = "00:00:00";
		simData.simState = 1;
		//设置仿真编号
		simData.simIndex = sm.sim_index;
		//开启仿真
		qps_GUI_simRunning(PTRUE);
	}
	else if (sm.is_pause == 1 && simData.simState == 1)  //仿真暂停
	{
		simData.simState = 2;
		//qps_GUI_printf("paused,sim_state=%d\n", sim_state);
		qps_GUI_simRunning(PFALSE);	
	}
	else if (sm.is_start == 1 && simData.simState == 2)  //暂停->继续运行
	{
		simData.simState = 1;
		qps_GUI_simRunning(PTRUE);
	//	qps_GUI_printf("running,sim_state=%d\n", sim_state);
	}
	else if (sm.is_finished == 1 &&  simData.simState == 1)// 运行时结束仿真
	{
		simData.simState = 3;  //标志位为3结束仿真
		qps_NET_clearVehicles();//清除路面所有车辆
		qps_GUI_simRestart();//仿真重启
		//qps_GUI_printf("running stop sim,sim_state=%d\n", sim_state);
		restart_flag = 1;//仿真重启完成后，设置重启标志位为1
	}
	//暂停时结束仿真（需要先将程序启动然后restart）
	else if (sm.is_finished == 1 && simData.simState == 2)
	{
		simData.simState = 3;
		//qps_GUI_printf("pause stop sim,sim_state=%d\n", sim_state);
		qps_GUI_simRunning(PTRUE);
	}
	qps_GUI_printf("size=%d,seq=%d", allCrossingSingal.size(), ++seq);
	/************************查看仿真记录表的OD值是否改变****************************************/

	float od_value=(float)(RA.getDBoperation()->getODvalue());  //从数据库获取ODvalue
	
	if (od_value != simData.odValue)   //ODvalue更新
	{
		qps_GUI_printf("od_value=%f", od_value);
		simData.setDemandMatrix(RA.ZoneNum,od_value);  //按照新的ODvalue值设置demand
		simData.odValue = od_value;          //保存新的ODvalue
	}

	//qps_GUI_printf("size=%d,seq=%d", allCrossingSingal.size(), ++seq);
	/*******************************路口信号控制****************************************/

	for (size_t cross_i = 0; cross_i < allCrossingSingal.size(); cross_i++)
	{
		//qps_GUI_printf("IsSingal=%d,seq=%d", allCrossingSingal[0].isCrossingSinglised(),++seq);
		//若该路口信号化
		if (allCrossingSingal[cross_i].isCrossingSinglised() == 1 )
		{
			if (allCrossingSingal[cross_i].isSingal == 0)
			{
				allCrossingSingal[cross_i].setCrossingSingalised(1); //设该路口信号化
				NODE* pNode = qpg_NET_node(const_cast<char*>(allCrossingSingal[cross_i].crossingId.c_str()));
				qps_NDE_externalController(pNode, PTRUE);//外部控制设置为TRUE，信号化路口
			}

			vector<string> res_plan = allCrossingSingal[cross_i].getActivePlanInfo();//获取控制方案表中该路口active为1的方案信息（PlanIndex,PhaseNum,Period,PhaseOffset）
			//qps_GUI_printf("res_plan.size=%d plan_type=%d,seq=%d", res_plan.size(), str2int(res_plan[4]),seq++);
			//存在active为1的控制方案
			if (res_plan.size() > 0)
			{
				int plan_index = str2int(res_plan[0]);//控制方案编号
				int phase_num = str2int(res_plan[1]);  //相位数
				int period = str2int(res_plan[2]);    //周期长
				int phase_offset = str2int(res_plan[3]); //相位差
				int plan_type = str2int(res_plan[4]);  //获取控制方案类型

				vector<int> all_green_time, all_red_time;//路口红绿灯配时
				int is_update = str2int(res_plan[5]);   //phase表是否更新
				//下面三种情况，需要读取phase表的配时信息
				//固定周期的控制方案变化变为另一个编号的固定周期控制方案
				if ((plan_type == PLANTYPE_FIX_PEROID && allCrossingSingal[cross_i].planType == PLANTYPE_FIX_PEROID && allCrossingSingal[cross_i].getSingalInfo().planIndex != plan_index) ||
					(allCrossingSingal[cross_i].planType != PLANTYPE_FIX_PEROID && plan_type == PLANTYPE_FIX_PEROID) ||    //路口控制方案类型由固定其他类型转为固定周期类型
					is_update == 1  )   //is_update=1  表示phase表发生更改
				{
					allCrossingSingal[cross_i].getPhaseInfo(all_green_time, all_red_time);//获取配时方案
					SingalInfo s = { plan_index, phase_num, period, phase_offset, all_green_time, all_red_time };
					allCrossingSingal[cross_i].setSingalInfoNext(s);
				}
				/*
				if (plan_type != PLANTYPE_FIX_PEROID)
				{
					SingalInfo s = { plan_index, phase_num, period, phase_offset, all_green_time, all_red_time };
					allCrossingSingal[cross_i].setSingalInfo(s);
				}*/
				allCrossingSingal[cross_i].setPlanType(plan_type); //设置路口的控制方案类型
				allCrossingSingal[cross_i].setPlanIndex(plan_index);//设置控制方案编号
			}
			//该信号化路口没有IsActive=1的控制方案
			else
			{
				//设控制方案编号为-1
				allCrossingSingal[cross_i].setPlanIndex(-1);
				//MessageBox(NULL, "no active plan", "", MB_OK);
			}
		}
		else  //该路口没有信号化
		{
			if (allCrossingSingal[cross_i].isSingal == 1) //本来是信号化的路口，现在取消信号化
			{
				allCrossingSingal[cross_i].setCrossingSingalised(0); //设该路口未信号化
				NODE* pNode = qpg_NET_node(const_cast<char*>(allCrossingSingal[cross_i].crossingId.c_str()));
				qps_NDE_externalController(pNode, PFALSE);//外部控制设置为FALSE，取消信号化
			}

			//查询crossingstream表  设置车流权限，
			vector<vector<string>> crossingstream_info=allCrossingSingal[cross_i].getCrossingstreamInfo();
			for (size_t i = 0; i < crossingstream_info.size(); i++)
			{
				string pri = crossingstream_info[i][0];  //权限
				int is_update = str2int(crossingstream_info[i][1]);  //IsUpdate标志位
				if (is_update == 1)
				{
					allCrossingSingal[cross_i].setStreamPriority(i+1, pri);  //更新权限
					//这里不更新控制状态查询表
					//allCrossingSingal[cross_i].updateControlState(i, pri); //更新控制状态
				}
			}
		}
	}
	CrossingSingal::clearIsUpdate("controlplan");
	CrossingSingal::clearIsUpdate("crossingstream");
}


//**************************************每一个仿真步开始调用*********************
void qpx_NET_timeStep(void)
{
	if (restart_flag == 1)        //检测到重启标志位为1 表明restart完成
	{
		qps_GUI_printf("restart_flag=%d\n", restart_flag);
		simData.simState = 0;
		restart_flag = 0;
		qps_GUI_simRunning(PFALSE);       //暂停仿真，表示仿真停止
	}
}


/*********************************************当有车经过检测器时******************************************/
/*当有车经过检测器时，必然有一个检测器线圈记录的通过车辆数会变化，寻找这个变换也就找到了哪个检测器线圈有车辆通过
**此时该车道线圈开始被占用，将标志位置1，此后每隔一秒查询该线圈占有时间是否更新，若更新，判断是在当前统计时间段内更新的
**直接累加到累计occ，若未更新，若车道被占用，增加累计occ一秒，并把标志位置为2，表示线圈被占用横跨多个统计时间段*/
void qpx_VHC_detector(VEHICLE* vehicle, LINK* link, DETECTOR* detector)
{
	//存储一份车辆通过数的副本
	vector<vector<int>> countEveryLoop_pre = simData.countEveryLoop;

	//查找是哪个线圈检测到车辆
	for (int i = 0; i < RA.DetectorNum; i++)
	{
		for (int j = 0; j < simData.loopNumArray[i]; j++)
		{
			int count = qpg_DTL_count(simData.netLoop[i][j], 0);
			//更新累计量
			simData.countEveryLoop[i][j] = count;
			//查找是哪个线圈检测到车辆
			if (count != countEveryLoop_pre[i][j] && simData.isOccupiedEveryLoop[i][j] == 0)
			{
				//该线圈被占用标志位置1
				simData.isOccupiedEveryLoop[i][j] = 1;

				simData.velocityEveryLoopDuration[i][j] += qpg_DTL_speed(simData.netLoop[i][j], APILOOP_COMPLETE);
			}		
		}
	}
}


/***********************************************模拟每执行一秒时调用*****************************************************/
void qpx_NET_second(void)
{
	//信号化的节点执行控制方案
	for (size_t i = 0; i < allCrossingSingal.size(); i++)
	{
		if (allCrossingSingal[i].isSingal == 1)
		{
			CString mes;
			mes.Format("i=%d", i);
			//MessageBox(NULL, mes, "", MB_OK);
			allCrossingSingal[i].execute_singal_control();
		}
	}


	//每隔1秒检测线圈被占用标志位为1的线圈，对应的占用时间是否更新，更新则写入变量
	for (int i = 0; i < RA.DetectorNum; i++)
	{
		for (int j = 0; j < simData.loopNumArray[i]; j++)
		{
			//标志位大于0（包括1和2，统计时间段）
			if (simData.isOccupiedEveryLoop[i][j] > 0)
			{
				float occ = qpg_DTL_occupancy(simData.netLoop[i][j], APILOOP_COMPLETE);
				if (occ != simData.occupancyEveryLoop[i][j])//占用时间更新
				{   
					//累加该检测器的占用时间（仅限于在同一个统计时段内车辆通过检测器）
					if (simData.isOccupiedEveryLoop[i][j] == 1)
					{
						simData.occupancyEveryLoopDuration[i][j] += occ;
					}
					simData.occupancyEveryLoop[i][j] = occ; //占用时间写入
					simData.isOccupiedEveryLoop[i][j] = 0; //清标志位
				}
				else
				{
					simData.occupancyEveryLoopDuration[i][j] += 1;
				}
			}
		}
	}


	/********************更新路段统计信息******************/
	//统计每条Road上所有link的数据
	for (size_t i = 0; i < simData.allRoadId.size(); i++)
	{	
		//以该路段中入路口的那个link的车道数作为整个road的车道数
		for (int m = 0; m < simData.laneNum[i][0]; m++)
		{
			size_t lane_0 = simData.laneNum[i][0] - m;
			simData.RoadLength[i][lane_0 - 1] = 0.0;
			float road_count = 0;
			//遍历该road所有link
			for (size_t j = 0; j < simData.linkPointerInRoad[i].size(); j++)
			{
				int lane_index = simData.laneNum[i][j] - m;
				if (lane_index > 0)  //该条link存在
				{
					road_count += qpg_STA_count(simData.linkPointerInRoad[i][j], lane_index);//该road上车辆数
					simData.RoadDelay[i][lane_0 - 1] += qpg_STA_delay(simData.linkPointerInRoad[i][j], lane_index);//延时累加
					simData.RoadDensity[i][lane_0 - 1] += qpg_STA_density(simData.linkPointerInRoad[i][j], lane_index)*qpg_LNK_length(simData.linkPointerInRoad[i][j]);//密度乘以该link长度后累加
					simData.RoadLength[i][lane_0 - 1] += qpg_LNK_length(simData.linkPointerInRoad[i][j]); //每条车道长度
					simData.RoadFlow[i][lane_0 - 1] += qpg_STA_flow(simData.linkPointerInRoad[i][j], lane_index);   //flow累加
					simData.RoadQueueCount[i][lane_0 - 1] += qpg_STA_stoplineQueueCount(simData.linkPointerInRoad[i][j], lane_index); //queueCount累加
					simData.RoadQueuePCU[i][lane_0 - 1] += qpg_STA_stoplineQueuePCUs(simData.linkPointerInRoad[i][j], lane_index);//PCU累加
					simData.RoadQueueLength[i][lane_0 - 1] += qpg_STA_stoplineQueueLength(simData.linkPointerInRoad[i][j], lane_index);//queueLength累加
					if (qpg_STA_speed(simData.linkPointerInRoad[i][j], lane_index) > 0.0 && qpg_STA_count(simData.linkPointerInRoad[i][j], lane_index) > 0 )
						simData.RoadSpeed[i][lane_0 - 1] += qpg_STA_speed(simData.linkPointerInRoad[i][j], lane_index) * qpg_STA_count(simData.linkPointerInRoad[i][j], lane_index);//speed乘以count后累加
				}
			}
			//
			if (road_count > simData.Roadcount[i][lane_0-1])    //保存最大的count
			{
				simData.Roadcount[i][lane_0 - 1] = road_count;
			}
			if (simData.RoadQueueCount[i][lane_0 - 1] > simData.RoadMaxQueueCount[i][lane_0 - 1])   //保存最大的QueueCount
			{
				simData.RoadMaxQueueCount[i][lane_0 - 1] = simData.RoadQueueCount[i][lane_0 - 1];
			}
			if (simData.RoadQueueLength[i][lane_0 - 1] > simData.RoadMaxQueueLength[i][lane_0 - 1])  //保存最大的QueueLength
			{
				simData.RoadMaxQueueLength[i][lane_0 - 1] = simData.RoadQueueLength[i][lane_0 - 1];
			}
		}
	}

	statistic_count++;
	//每次到达设定时间间隔时
	if (statistic_count == STATISTIC_STEP)
	{
		/*************************更新实时交通流信息*****************************/
		statistic_count = 0; //重新计数
		int date = qpg_CLK_date();
		string simu_date = num2date(date);
		//计算当前仿真时间
		simData.simuTime = updateTime(simData.simuTime, STATISTIC_STEP);
		//计算该时间段内数据文件
		for (int i = 0; i < RA.DetectorNum; i++)
		{
			int sum = 0;
			for (int j = 0; j < simData.loopNumArray[i]; j++)
			{
				int count = qpg_DTL_count(simData.netLoop[i][j], 0);
				//计算差分量（即该仿真时间段内的车辆通过数）
				simData.countEveryLoopDiff[i][j] = count - simData.countEveryLoopDuration[i][j];

				if (simData.countEveryLoopDiff[i][j] == 0)
				{
					simData.velocityEveryLoopDuration[i][j] = 0.00;
				}
				else
				{
					simData.velocityEveryLoopDuration[i][j] = simData.velocityEveryLoopDuration[i][j] / simData.countEveryLoopDiff[i][j];
				}
				
				
				//更新累计量
				simData.countEveryLoopDuration[i][j] = count;
				//计算每一个加测器的车辆通过数(即该车道)
				sum = sum + simData.countEveryLoopDiff[i][j];

				//将还没有更新occ的检测器标志位由1置为2，表示这个线圈上有车占用横跨多个统计时间间隔
				if (simData.isOccupiedEveryLoop[i][j] == 1)
				{
					simData.isOccupiedEveryLoop[i][j] = 2;
				}

			}
			simData.countEveryDetector[i] = sum;
		}

		//统计时间间隔内的数据写入数据库
		simData.writeDetectorDataToSql(RA.getDBoperation()->getMySql(), RA.DetectorNum);

		for (int i = 0; i < RA.DetectorNum; i++)
		{
			for (int j = 0; j < simData.loopNumArray[i]; j++)
			{
				
				//清空occ的累计值
				simData.occupancyEveryLoopDuration[i][j] = 0;
				//清空velocity累计值
				simData.velocityEveryLoopDuration[i][j] = 0;
				//RoadNetInfo::isOccupiedEveryLoop[i][j] = 0; //清标志位
			}
		}

		//计算平均信息
		for (size_t i = 0; i < simData.allRoadId.size(); i++)
		{
			for (int j = 0; j < simData.laneNum[i][0]; j++)
			{
				//simData.Roadcount[i][j] /= STATISTIC_STEP;
				simData.RoadDelay[i][j] /= STATISTIC_STEP;
				simData.RoadDensity[i][j] /= (STATISTIC_STEP*simData.RoadLength[i][j]);
				simData.RoadFlow[i][j] /= STATISTIC_STEP;
				simData.RoadQueueCount[i][j] /= STATISTIC_STEP;
				simData.RoadQueuePCU[i][j] /= STATISTIC_STEP;
				simData.RoadQueueLength[i][j] /= STATISTIC_STEP;
				if (simData.Roadcount[i][j] <= 0.1)
					simData.RoadSpeed[i][j] = 0.0;
				else
					simData.RoadSpeed[i][j] /= (STATISTIC_STEP*simData.Roadcount[i][j]);
			}
		}

		//数据写入数据库
		CString mes;
		mes.Format("lane1=%.2f,lane2=%.2f,lane3=%.2f", simData.Roadcount[0][0], simData.RoadQueueCount[0][1], simData.RoadQueueCount[0][2]);
		//MessageBox(NULL, mes, "", MB_OK);
		simData.writeRoadDataToSql(RA.getDBoperation()->getMySql());

		//数据请0
		for (size_t i = 0; i < simData.allRoadId.size(); i++)
		{
			for (int j = 0; j < simData.laneNum[i][0]; j++)
			{
				simData.Roadcount[i][j] = 0;
				simData.RoadDelay[i][j] = 0;
				simData.RoadDensity[i][j] = 0;
				simData.RoadFlow[i][j] = 0;
				simData.RoadQueueCount[i][j] = 0;
				simData.RoadQueueLength[i][j] = 0;
				simData.RoadSpeed[i][j] = 0;
				simData.RoadMaxQueueCount[i][j] = 0;
				simData.RoadMaxQueueLength[i][j] = 0;
			}
		}
	}
}


/*************************************************当路网关闭时*********************************************************/
void qpx_NET_close(void)
{
	//关闭数据库
	RA.getDBoperation()->getMySql()->CloseMySQLConn();
	//关闭定时器
	KillTimer(NULL, 1);
}