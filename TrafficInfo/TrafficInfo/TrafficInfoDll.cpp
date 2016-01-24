// TrafficInfo.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"


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

//数据库信息
VspdCToMySQL* mysql = new VspdCToMySQL;
#define STATISTIC_STEP 5
int statistic_count = 0;


int sim_state = 0;  //仿真状态 0：未开始 1：运行  2：暂停  3：结束

//声明定时器1的回调函数
void CALLBACK TimerProc(HWND   hWnd, UINT   nMsg, UINT   nTimerid, DWORD   dwTime);
//声明定时器2的回调函数
void CALLBACK TimerProc2(HWND   hWnd, UINT   nMsg, UINT   nTimerid, DWORD   dwTime);



struct SIGPRI_s
{
	char* inlink;
	char* outlink;
	int	  priority;
};



/*********************************************路网打开前**********************************************/
void qpx_NET_preOpen()
{
	char* host="localhost";
	char* user="root";
	char* port ="3306";
	char* passwd="root";
	char* dbname="traffic_info"; 
	char* charset = "GBK";
	string Msg ;

	//连接数据库
	if(mysql->ConnMySQL(host,port,dbname,user,passwd,charset,Msg) != 0)
	{
		qps_GUI_printf("database connect fail");
	}
	else
	{
		qps_GUI_printf("database connect success");
	}
}
/*********************************************路网开启后**********************************************/
void qpx_NET_postOpen()
{

	TrafficInfo::simu_time = "00:00:00";
	//路网名称
	char* net_file_path=qpg_NET_dataPath();

	//从路径中取得名字(即为路网Id)
	string netName=getFileName(net_file_path);

	
	qps_GUI_printf("road net name: %s",netName.c_str());

	//获取节点，路段，子区，检测器数量信息
	//node数
	RoadNetInfo::nodeNum = qpg_NET_nodes();
	//link数
	RoadNetInfo::linkNum = qpg_NET_links();
	//zone数
	RoadNetInfo::zoneNum = qpg_NET_zones();
	//detector数
	RoadNetInfo::detectorNum = qpg_NET_detectors();

	
	qps_GUI_printf("nodeNum=%d,linkNum=%d,zoneNum=%d,detectorNum=%d", RoadNetInfo::nodeNum, RoadNetInfo::linkNum, RoadNetInfo::zoneNum, RoadNetInfo::detectorNum);

	
	//获取检测器指针和检测器id
	RoadNetInfo::getAllDetectorPointer(RoadNetInfo::detectorNum);
	RoadNetInfo::getAllDetectorId(RoadNetInfo::detectorNum);

	/***********************************判断是否为新路网****************************************/
	//若为新路网
	if(RoadNetInfo::isNewRoadNet(mysql,netName))
	{
		MessageBox(NULL, "New RoadNet", "告知4", MB_OK);
		//路网信息表中新增一条路网
		RoadNetInfo road_net_info(netName.c_str(), "", RoadNetInfo::nodeNum, RoadNetInfo::linkNum, RoadNetInfo::zoneNum, 0);
		road_net_info.writeDataToSql(mysql);
	    //清空相应数据表
		RoadNetInfo::clearTable(mysql);

		//更新相关表数据
		RoadNetInfo::updateRoadInfo(mysql);
	}
	//不是新路网
	else
	{
		
		if (RoadNetInfo::IsRoadNetModified(mysql, netName) == 1)
		{
			qps_GUI_printf("road net has modified");
			//更新roadnetinfo表
			RoadNetInfo::updateRoadNetInfoTable(mysql, netName);
			//清除相关数据表
			RoadNetInfo::clearTable(mysql);
			//更新相关表数据
			RoadNetInfo::updateRoadInfo(mysql);
		}
		
	}

	//*******************************************获取所有线圈指针**************************************************
	for (int i = 0; i < RoadNetInfo::detectorNum; i++)
	{
		int startLane = qpg_DTC_lane(RoadNetInfo::allDetectorPointer[i]);
		int endLane = qpg_DTC_end_lane(RoadNetInfo::allDetectorPointer[i]);
		RoadNetInfo::loopNumArray.push_back(endLane - startLane + 1);
		vector<LOOP*> temp;
		temp.clear();
		for (int j = 0; j < RoadNetInfo::loopNumArray[i]; j++)
		{
			LOOP* pLOOP = qpg_DTC_multipleLoop(RoadNetInfo::allDetectorPointer[i], j + 1);	
			temp.push_back(pLOOP);
		}
		RoadNetInfo::netLoop.push_back(temp);
	}



	RoadNetInfo::initCountLoop();
	RoadNetInfo::initCountDetector();

	//清空实时交通信息表
	string Msg;
	mysql->ClearTable("trafficinfo", Msg);
	
	qps_GUI_printf("wait for simulation start");

	//开启路网后新增一条仿真记录
	//SimRecord sm(netName,"", 1.00, STATISTIC_STEP,0,0,"","","",0,"","","" );
	//sm.writeDataToSql(mysql);


	//初始化OD矩阵
	RoadNetInfo::initDemandMatrix();

	//开启1s的定时器
	SetTimer(NULL, 1, 1000, TimerProc);

}

int restart_flag = 0;

//定时器的回调函数，用于实现定时查看仿真是否开启，暂停，停止，以及配置是否修改
void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	//查看仿真记录表，仿真是否暂停或者运行
	if (sim_state == 0 && SimRecord::isSimStart(mysql) > 0)  //仿真第一次开始
	{
		TrafficInfo::simu_time = "00:00:00";
		sim_state = 1;
		/*获取当前系统时间
		CTime time = CTime::GetCurrentTime(); //构造CTime对象  
		string current_datetime = datetime2str(time);//CTime对象转换为字符串
		MessageBox(NULL, current_datetime.c_str(), "", MB_OK);
		*/

		//从仿真记录表中读取最后一条记录中的仿真编号
		TrafficInfo::SimIndex = SimRecord::isSimStart(mysql);
		qps_GUI_printf("running,sim_state=%d\n", sim_state);
		qps_GUI_simRunning(PTRUE);

		

	}
	else if (sim_state == 1 && SimRecord::isSimPause(mysql) == true)  //仿真暂停
	{
		sim_state = 2;
		qps_GUI_printf("paused,sim_state=%d\n", sim_state);
		qps_GUI_simRunning(PFALSE);

		
	}
	else if (sim_state == 2 && SimRecord::isSimStart(mysql) > 0)  //暂停->继续运行
	{
		sim_state = 1;
		qps_GUI_simRunning(PTRUE);

		qps_GUI_printf("running,sim_state=%d\n", sim_state);
	}
	
	else if (SimRecord::isSimStop(mysql) == 1 && sim_state == 1 )// 运行时结束仿真
	{
		sim_state = 3;  //标志位为3结束仿真
		qps_NET_clearVehicles();//清除路面所有车辆
		qps_GUI_simRestart();//仿真重启
		qps_GUI_printf("running stop sim,sim_state=%d\n", sim_state);
		restart_flag = 1;//仿真重启完成后，设置重启标志位为1
	}
	//暂停时结束仿真（需要先将程序启动然后restart）
	else if (SimRecord::isSimStop(mysql) == 1 && sim_state == 2)  
	{
		sim_state = 1;
		qps_GUI_printf("pause stop sim,sim_state=%d\n", sim_state);
		qps_GUI_simRunning(PTRUE);
	}


	//*****************查看仿真记录表的OD值是否改变****************************************

	float od_value=(float)(SimRecord::getODvalue(mysql));  //从数据库获取ODvalue
	
	if (od_value != RoadNetInfo::ODvalue)   //ODvalue更新
	{
		qps_GUI_printf("od_value=%f", od_value);
		RoadNetInfo::setDemandMatrix(od_value);  //按照新的ODvalue值设置demand
		RoadNetInfo::ODvalue = od_value;          //保存新的ODvalue
	}

	//if (sim_state == 1)
	//{
		//查看控制方案表是否有控制方案更新，若有，从相位表中查询对应更新的红绿灯时间进更改设置
		vector<vector<string>> update_plan_info = ControlPlan::getPlanUpdateIndex(mysql);

		for (size_t plan_i = 0; plan_i < update_plan_info.size(); plan_i++)
		{
			//从获取控制方案信息中提取方案编号 周期 路口id

			int plan_index = str2int(update_plan_info[plan_i][0]);
			string crossing_id = update_plan_info[plan_i][1];
		    float period = atof(update_plan_info[plan_i][2].c_str());

			//对每一个控制方案编号，获取对应所有相位的信号灯时间
			vector<vector<string>> update_phase_info = Phase::getSingalTimeByIndex(mysql,plan_index);
			float time_sum=0.0;
			qps_GUI_printf("plan_index=%d", plan_index);
			for (size_t phase_i = 0; phase_i < update_phase_info.size(); phase_i++)
			{
				//累加所有时间，如果和period相同，则更新时间设置
				time_sum += atof(update_phase_info[phase_i][0].c_str()) + atof(update_phase_info[phase_i][1].c_str()) + atof(update_phase_info[phase_i][2].c_str());
				qps_GUI_printf("green=%f amber=%f red=%f", atof(update_phase_info[phase_i][0].c_str()), atof(update_phase_info[phase_i][1].c_str()), atof(update_phase_info[phase_i][2].c_str()));
			}

			qps_GUI_printf("crossing_id=%s", crossing_id.c_str());

			if (time_sum == period)
			{
				for (size_t phase_i = 0; phase_i < update_phase_info.size(); phase_i++)
				{
					//由于设置的绿灯时间对应黄灯和绿灯的总时间，所以在设置时要加上系统的黄灯时间
					qps_SIG_action(RoadNetInfo::AllSignalisedNode[crossing_id], phase_i + 1, 0, API_ACTION_STORED_GREEN, API_ACTIONMODE_SET, atof(update_phase_info[phase_i][0].c_str())+3);
					qps_SIG_action(RoadNetInfo::AllSignalisedNode[crossing_id], phase_i + 1, 0, API_ACTION_STORED_RED, API_ACTIONMODE_SET, atof(update_phase_info[phase_i][2].c_str()));
				}
			}

		}
	
	//}
}

//**************************************每一个仿真步开始调用
void qpx_NET_timeStep(void)
{
	if (restart_flag == 1)        //检测到重启标志位为1 表明restart完成
	{
		qps_GUI_printf("restart_flag=%d\n", restart_flag);
		sim_state = 0;
		restart_flag = 0;
		qps_GUI_simRunning(PFALSE);       //暂停仿真，表示仿真停止
	}
}


/*********************************************当有车经过检测器时******************************************/
/*当有车经过检测器时，必然有一个检测器线圈记录的通过车辆数会变化，寻找这个变换也就找到了哪个检测器线圈有车辆通过
**此时该车道线圈开始被占用，将标志位置1，此后每隔一秒查询该线圈占有时间是否更新，若更新，判断是在当前统计时间段内更新的
**直接累加到累计occ，若未更新，若车道被占用，手动增加累计occ一秒，并把标志位置为2，表示线圈被占用横跨多个统计时间段*/
void qpx_VHC_detector(VEHICLE* vehicle, LINK* link, DETECTOR* detector)
{
	//存储一份车辆通过数的副本
	vector<vector<int>> countEveryLoop_pre = RoadNetInfo::countEveryLoop;

	//查找是哪个线圈检测到车辆
	for (int i = 0; i < RoadNetInfo::detectorNum; i++)
	{
		for (int j = 0; j < RoadNetInfo::loopNumArray[i]; j++)
		{
			int count = qpg_DTL_count(RoadNetInfo::netLoop[i][j], 0);
			//更新累计量
			RoadNetInfo::countEveryLoop[i][j] = count;
			//查找是哪个线圈检测到车辆
			if (count != countEveryLoop_pre[i][j] && RoadNetInfo::isOccupiedEveryLoop[i][j] == 0)
			{
				//该线圈被占用标志位置1
				RoadNetInfo::isOccupiedEveryLoop[i][j] = 1;

				RoadNetInfo::velocityEveryLoopDuration[i][j] += qpg_DTL_speed(RoadNetInfo::netLoop[i][j], APILOOP_COMPLETE);
			}		
		}
	}
}

int a = 32;
/***********************************************模拟每执行一秒时调用*****************************************************/
void qpx_NET_second(void)
{
	//每隔1秒检测线圈被占用标志位为1的线圈，对应的占用时间是否更新，更新则写入变量
	for (int i = 0; i < RoadNetInfo::detectorNum; i++)
	{
		for (int j = 0; j < RoadNetInfo::loopNumArray[i]; j++)
		{
			//标志位大于0（包括1和2，统计时间段）
			if (RoadNetInfo::isOccupiedEveryLoop[i][j] > 0)
			{
				float occ = qpg_DTL_occupancy(RoadNetInfo::netLoop[i][j], APILOOP_COMPLETE);
				if (occ != RoadNetInfo::occupancyEveryLoop[i][j])//占用时间更新
				{   
					//累加该检测器的占用时间（仅限于在同一个统计时段内车辆通过检测器）
					if (RoadNetInfo::isOccupiedEveryLoop[i][j] == 1)
					{
						RoadNetInfo::occupancyEveryLoopDuration[i][j] += occ;
					}
						

					RoadNetInfo::occupancyEveryLoop[i][j] = occ; //占用时间写入
					RoadNetInfo::isOccupiedEveryLoop[i][j] = 0; //清标志位
				}
				else
				{
					RoadNetInfo::occupancyEveryLoopDuration[i][j] += 1;
				}
			}
		}
	}




    //每次到达设定时间间隔时
	statistic_count++;
	if (statistic_count == STATISTIC_STEP)
	{
		statistic_count = 0;
		int date = qpg_CLK_date();
		string simu_date = num2date(date);

		TrafficInfo::simu_time = updateTime(TrafficInfo::simu_time, STATISTIC_STEP);

		//获取占有率
		float occupancy = RoadNetInfo::occupancyEveryLoopDuration[89][1];

		for (int i = 0; i < RoadNetInfo::detectorNum; i++)
		{
			int sum = 0;
			for (int j = 0; j < RoadNetInfo::loopNumArray[i]; j++)
			{
				int count = qpg_DTL_count(RoadNetInfo::netLoop[i][j], 0);
				//计算差分量（即该仿真时间段内的车辆通过数）
				RoadNetInfo::countEveryLoopDiff[i][j] = count - RoadNetInfo::countEveryLoopDuration[i][j];


				
				if (RoadNetInfo::countEveryLoopDiff[i][j] == 0)
				{
					RoadNetInfo::velocityEveryLoopDuration[i][j] = 0.00;
				}
				else
				{
					RoadNetInfo::velocityEveryLoopDuration[i][j] = RoadNetInfo::velocityEveryLoopDuration[i][j] / RoadNetInfo::countEveryLoopDiff[i][j];
				}
				
				
				//更新累计量
				RoadNetInfo::countEveryLoopDuration[i][j] = count;
				//计算每一个加测器的车辆通过数(即该车道)
				sum = sum + RoadNetInfo::countEveryLoopDiff[i][j];

				//将还没有更新occ的检测器标志位由1置为2，表示这个线圈上有车占用横跨多个统计时间间隔
				if (RoadNetInfo::isOccupiedEveryLoop[i][j] == 1)
				{
					RoadNetInfo::isOccupiedEveryLoop[i][j] = 2;
				}

			}

			RoadNetInfo::countEveryDetector[i] = sum;
		}

		//该时间段内通过的车辆数
		int count = RoadNetInfo::countEveryLoopDiff[89][1];
		//获取平均速度
		float speed_smooth = RoadNetInfo::velocityEveryLoopDuration[89][1];
		
		int flag = RoadNetInfo::isOccupiedEveryLoop[89][1];
		
		CString mes;
		mes.Format("count=%d,occ=%f,speed=%f,flag=%d",count, occupancy,speed_smooth,flag);
		//MessageBox(NULL, mes, "", MB_OK);
		
        //写数据库

		//统计时间间隔内的数据写入数据库
		TrafficInfo::writeAllDataToSql(mysql);
			
		for (int i = 0; i < RoadNetInfo::detectorNum; i++)
		{
			for (int j = 0; j < RoadNetInfo::loopNumArray[i]; j++)
			{
				
				//清空occ的累计值
				RoadNetInfo::occupancyEveryLoopDuration[i][j] = 0;
				//清空velocity累计值
				RoadNetInfo::velocityEveryLoopDuration[i][j] = 0;
				//RoadNetInfo::isOccupiedEveryLoop[i][j] = 0; //清标志位
			}
		}
	
	}
}





/*************************************************当路网关闭时*********************************************************/
void qpx_NET_close(void)
{
	//关闭数据库
	mysql->CloseMySQLConn();
	//删除数据库对象
	delete mysql;
	//关闭定时器
	KillTimer(NULL, 1);
}