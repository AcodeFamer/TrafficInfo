#include "stdafx.h"
#include "CrossingSingal.h"

//初始化路口仿真没有开启
int CrossingSingal::IsStart = 0;
VspdCToMySQL* CrossingSingal::mysql = 0;
CrossingSingal::CrossingSingal(string crossing_id, vector<string> stream_pri, vector<string> link_in_id, vector<string> link_out_id)
{

	//路口id
	crossingId = crossing_id;
	//初始化没有信号化
	isSingal = 0;
	//初始化当前相位经过0秒
	second = 0;
	//初始化为第一个相位
	isFirstPhase = 1;
	//初始化当前第0相位
	phaseIndex = 0;

	//初始化当前控制方案相位数为-1（在执行第0相位时直接进行相位切换跳转到第一相位）
	singal_info.phaseNum = 0;
	//初始化流入流出link id
	linkInId = link_in_id;
	linkOutId = link_out_id;
	
	//初始化控制方案类型
	planType = -1;
	//初始化所有车流为MAJOR
	curStreamPri = vector<string>(link_in_id.size()+1, "MAJOR");
	//controlstate IsUpdate标记  0 1变化
	controlStateIsUpdateFlag = 0;
}

CrossingSingal::~CrossingSingal()
{

}

SingalInfo CrossingSingal::getSingalInfo()
{
	return singal_info;
}

int CrossingSingal::isCrossingSinglised()
{
	string SQL = "select IsSingal from nodeinfo where NodeId=";
	SQL = SQL + "'" + crossingId + "'";
	string Msg;
	vector<vector<string>> res=mysql->SelectData(SQL.c_str(), 1, Msg);
	if (res.size() > 0)
	{
		if (res[0][0] == "1")
		{
			return 1;
		}
		else
		{
			return 0;
		}
		
	}
	return -1;
}

void CrossingSingal::setPlanIndex(int plan_index)
{
	singal_info.planIndex = plan_index;
}

void CrossingSingal::setCrossingSingalised(int is_singlised)
{
	isSingal = is_singlised;
}

vector<vector<string>> CrossingSingal::getCrossingstreamInfo()
{
	string SQL = "select Priority,IsUpdate from crossingstream where CrossingId=";
	SQL = SQL + "'" + crossingId+"'";
	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL.c_str(), 2, Msg);
	return res;
}

vector<string> CrossingSingal::getActivePlanInfo()
{
	string SQL = "select PlanIndex,PhaseNum,Period,PhaseOffset,PlanType,IsUpdate from controlplan where CrossingId=";
	SQL = SQL + "'" + crossingId + "' AND IsActive='1'";
	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL.c_str(), 6, Msg);

	vector<string> res_final;
	if (res.size() > 0)
	{
		res_final=res[0];
	}
	return res_final;
}

void CrossingSingal::getPhaseInfo(vector<int>& all_green_time,vector<int>& all_red_time)
{
	string SQL = "select GreenTime,AmberTime,RedTime from phase where CrossingId=";
	SQL = SQL + "'" + crossingId + "' ORDER BY PhaseId";
	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL.c_str(), 3, Msg);
	
	//获取所有相位的绿灯红灯时间
	all_red_time.push_back(0);  //默认第0个相位时间为0
	all_green_time.push_back(0);
	for (size_t phase_i = 0; phase_i < res.size(); phase_i++)
	{
		int green_time = str2int(res[phase_i][0]);
		int amber_time = str2int(res[phase_i][1]);
		int red_time = str2int(res[phase_i][2]);
		//按相位顺序存储绿灯时间，红灯时间
		all_green_time.push_back(green_time + amber_time);
		all_red_time.push_back(red_time);
	}
}


void CrossingSingal::setSingalInfo(SingalInfo s)
{
	singal_info = s;
}

void CrossingSingal::setSingalInfoNext(SingalInfo s_next)
{
	singal_info_next = s_next;
}

int CrossingSingal::getPlanIndex()
{
	return singal_info.planIndex;
}
//根据控制方案类型执行控制方案
void CrossingSingal::execute_singal_control()
{
	int stream_num = linkInId.size() - 1;//该路口车流 数量
	//全部红灯
	if (planType == PLANTYPE_RED)
	{
		isFirstPhase = 1;//设置在切换固定周期时，从第一个相位开始执行
		int is_pri_update = 0;  //是否有pri变化
		for (int index = 1; index <= stream_num; index++)
		{
			if (curStreamPri[index] != "BARRED")
			{
				setStreamPriority(index, "BARRED");
				curStreamPri[index] = "BARRED";
				updateControlState(index, "BARRED");
				is_pri_update = 1;
			}
		}
		if (is_pri_update == 1)
		{
			changeIsUpdate();
		}
	}
	//全部黄灯闪烁
	else if (planType == PLANTYPE_YELLOW)
	{
		isFirstPhase = 1; //设置在切换固定周期时，从第一个相位开始执行
		int is_pri_update = 0;  //是否有pri变化
		for (int index = 1; index <= stream_num; index++)
		{
			if (curStreamPri[index] != "MINOR")
			{
				setStreamPriority(index, "MINOR");
				curStreamPri[index] = "MINOR";
				updateControlState(index, "MINOR");
				is_pri_update = 1;
			}
		}
		if (is_pri_update == 1)
		{
			changeIsUpdate();
		}
	}
	//在线控制，读取到权限就改
	else if (planType == PLANTYPE_ONLINE_CONTROL)  
	{
		isFirstPhase = 1;//设置在切换固定周期时，从一个相位开始执行
		int stream_num = linkInId.size() - 1;//该路口车流 数量
		getPhaseStreamPri();//获取车流权限情况
		int is_pri_update = 0;  //是否有pri变化
		for (int index = 1; index <= stream_num; index++)
		{
			if (curStreamPri[index] != phaseStreamPri[1][index])   //此时只读取第一个周期
			{
				setStreamPriority(index, phaseStreamPri[1][index]);
				curStreamPri[index] = phaseStreamPri[1][index];
				updateControlState(index, phaseStreamPri[1][index]);
				is_pri_update = 1;
			}
		}
		if (is_pri_update == 1)
		{
			changeIsUpdate();
		}
	}
	//固定周期
	else if (planType == PLANTYPE_FIX_PEROID)
	{
		if (isFirstPhase == 0)
		{
			CString mes;
			//mes.Format("second=%d,phaseIndex=%d,greenTime=%d,redTime=%d", second, phaseIndex, singal_info.greenTime[phaseIndex], singal_info.redTime[phaseIndex]);
			//mes.Format("second=%d,phaseIndex=%d,greenTime.size=%d,redTime.size=%d", second, phaseIndex, singal_info.greenTime.size(), singal_info.redTime.size());
			//MessageBox(NULL, mes, "", MB_OK);
			
		}

		int stream_num = linkInId.size() - 1;//该路口车流 数量
		//仿真开始第一个周期
		if (isFirstPhase == 1)
		{
			isFirstPhase = 0;
			singal_info = singal_info_next;//加载控制方案到当前
			getPhaseStreamPri();   //获取路口车流权限
			phaseIndex = 1;  //当前执行第一个相位
			second = 0;   //第一个相位已经执行0秒
			curStreamPri = phaseStreamPri[1];  //当前控制车流权限
			for (int index = 1; index <= stream_num; index++)
			{
				setStreamPriority(index, phaseStreamPri[1][index]); //设置车流权限
				updateControlState(index, phaseStreamPri[1][index]);//更新控制状态
			}
			changeIsUpdate();
		}

		else
		{
			/********************判断是否需要开启黄灯****************/
			if (second == singal_info.greenTime[phaseIndex] - 3) //判断是否需要开启黄灯
			{
				//clearIsUpdate();
				//遍历车流
				int is_pri_update = 0;  //是否有pri变化
				for (int index = 1; index <= stream_num; index++)
				{
					if (phaseIndex < singal_info.phaseNum)
					{
						if (curStreamPri[index] == "MAJOR" && phaseStreamPri[phaseIndex + 1][index] == "BARRED")
						{
							//需要开启黄灯
							setStreamPriority(index, "MINOR");
							curStreamPri[index] = "MINOR";
							updateControlState(index, "MINOR");
							is_pri_update = 1;
						}
						if (is_pri_update == 1)
						{
							changeIsUpdate();
						}
					}
					else
					{
						singal_info.planIndex = singal_info_next.planIndex;  //这里只修改控制方案编号，没有修改正在执行的方案相位时间配置
						getPhaseStreamPri();//获取到的是下一个周期的权限
						if (curStreamPri[index] == "MAJOR" && phaseStreamPri[1][index] == "BARRED")
						{
							//需要开启黄灯
							setStreamPriority(index, "MINOR");
							curStreamPri[index] = "MINOR";
							updateControlState(index, "MINOR");
							is_pri_update = 1;
						}
					}
				}
				if (is_pri_update == 1)
				{
					changeIsUpdate();
				}
			}
			//切换下一个相位
			if (second == singal_info.greenTime[phaseIndex])
			{
				second = 0;
				phaseIndex++;
				clearIsUpdate();
				//还在当前周期
				if (phaseIndex <= singal_info.phaseNum)
				{
					if (singal_info.greenTime[phaseIndex] == 0)   //下一个相位全是红灯
					{
						int is_pri_update = 0;  //是否有pri变化
						for (int index = 1; index <= stream_num; index++)
						{
							if (curStreamPri[index] != "BARRED")
							{
								setStreamPriority(index, "BARRED");
								curStreamPri[index] = "BARRED";
								updateControlState(index, "BARRED");
								is_pri_update = 0;
							}
						}
						if (is_pri_update == 1)
						{
							changeIsUpdate();
						}
					}
					else
					{
						int is_pri_update = 0;  //是否有pri变化
						for (int index = 1; index <= stream_num; index++)
						{
							if (curStreamPri[index] != phaseStreamPri[phaseIndex][index])	
							{
								setStreamPriority(index, phaseStreamPri[phaseIndex][index]);
								curStreamPri[index] = phaseStreamPri[phaseIndex][index];
								updateControlState(index, phaseStreamPri[phaseIndex][index]);
								is_pri_update = 1;
							}
							if (is_pri_update == 1)
							{
								changeIsUpdate();
							}
						}
					}
				}
				//需要切换下一个周期
				else
				{
					second = 0;
					phaseIndex = 1;
					singal_info = singal_info_next;
					getPhaseStreamPri();
					int is_pri_update = 0;  //是否有pri变化
					for (int index = 1; index <= stream_num; index++)
					{
						if (curStreamPri[index] != phaseStreamPri[phaseIndex][index])
						{
							setStreamPriority(index, phaseStreamPri[phaseIndex][index]);
							curStreamPri[index] = phaseStreamPri[phaseIndex][index];
							updateControlState(index, phaseStreamPri[phaseIndex][index]);
							is_pri_update = 1;
						}
					}
					if (is_pri_update == 1)
					{
						changeIsUpdate();
					}
					return;
				}
			}
		}
		//执行秒数加1
		second++;
	}
	//不是上述定义的控制方案类型（该信号化路口没有定义的IsActive=1的控制方案），按照crossingstream中设置车流权限crossingstream
	else
	{
		vector<vector<string>> res=getCrossingstreamInfo();
		CString mes;
		for (size_t i = 0; i < res.size(); i++)
		{
			string pri = res[i][0];
			setStreamPriority(i + 1, pri);
		}
	}
}

void CrossingSingal::setStreamPriority(int stream_index, string pri)
{
	//调试显示获取的车流权限信息
	CString mes;
	/*
	mes.Format("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s", 
		phaseStreamPri[phaseIndex][1].c_str(), phaseStreamPri[phaseIndex][2].c_str(), phaseStreamPri[phaseIndex][3].c_str(), phaseStreamPri[phaseIndex][4].c_str(),
		phaseStreamPri[phaseIndex][5].c_str(), phaseStreamPri[phaseIndex][6].c_str(), phaseStreamPri[phaseIndex][7].c_str(), phaseStreamPri[phaseIndex][8].c_str(),
		phaseStreamPri[phaseIndex][9].c_str(), phaseStreamPri[phaseIndex][10].c_str(), phaseStreamPri[phaseIndex][11].c_str(), phaseStreamPri[phaseIndex][12].c_str(),
		phaseStreamPri[phaseIndex][13].c_str(), phaseStreamPri[phaseIndex][14].c_str(), phaseStreamPri[phaseIndex][15].c_str(), phaseStreamPri[phaseIndex][16].c_str()
		                                                          );
	MessageBox(NULL, mes, "", MB_OK);*/
	

	
	char* link_in = const_cast<char*>(linkInId[stream_index].c_str());
	char* link_out = const_cast<char*>(linkOutId[stream_index].c_str());
		
	int pri_set;
	if (pri == "MAJOR")
		pri_set = APIPRI_MAJOR;
	else if (pri == "MEDIUM")
		pri_set = APIPRI_MEDIUM;
	else if (pri == "MINOR")
		pri_set = APIPRI_MINOR;
	else 
		pri_set = APIPRI_BARRED;

	qps_LNK_priority(qpg_NET_link(link_in), qpg_NET_link(link_out), pri_set);
}



void CrossingSingal::getPhaseStreamPri()
{
	//获取该路口 当前执行方案的 每一个相位车流权限
	string SQL = "select StreamState from phasestream where ";
	SQL = SQL  + "PlanIndex='" + int2str(singal_info.planIndex) + "' AND CrossingId='" + crossingId + "' ORDER BY PhaseId,StreamIndex";
	qps_GUI_printf("%s", SQL.c_str());

	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL.c_str(), 1, Msg);


	phaseStreamPri.clear();
	vector<string> row(linkInId.size(), "0");
	phaseStreamPri.push_back(row);
	//按相位存储每个车流的权限
	if (res.size() > 0)
	{
		int index = 0;
		for (size_t phase_i = 0; phase_i < res.size()/(linkInId.size()-1); phase_i++)
		{
			vector<string> row;
			row.push_back("0");
			for (size_t stream_i = 0; stream_i < linkInId.size()-1; stream_i++)
			{
				row.push_back(res[index][0]);
				index++;
			}
			phaseStreamPri.push_back(row);
		}
	}
	else
	{
		MessageBox(NULL, "getPhaseStreamPri fail", "error", MB_OK);
	}
	/*
	CString mes;
	mes.Format("singal_info.planIndex=%d,size1=%d,size2=%d", singal_info.planIndex,phaseStreamPri.size(), phaseStreamPri[1].size());
	MessageBox(NULL, mes, "", MB_OK);
*/

}

void CrossingSingal::updateControlState(int stream_index,string pri)
{
	//原先的方法，更新pri是更新对应的IsUpdate
	//string SQL = "update controlstate set Priority='" + pri + "',IsUpdate=1 where CrossingId='";
	//SQL = SQL + crossingId + "' AND StreamIndex='" + int2str(stream_index) + "'";
	
	//现在统一更新IsUpdate
	string SQL = "update controlstate set Priority='" + pri + "' where CrossingId='";
	SQL = SQL + crossingId + "' AND StreamIndex='" + int2str(stream_index) + "'";
	string Msg;
	mysql->UpdateData(SQL.c_str(), Msg);
}

void CrossingSingal::changeIsUpdate()
{
	//变化IsUpdate值
	controlStateIsUpdateFlag = 1 - controlStateIsUpdateFlag;

	string SQL = "update controlstate set IsUpdate='" + int2str(controlStateIsUpdateFlag) + "' where CrossingId='";
	SQL = SQL + crossingId + "'";
	string Msg;
	mysql->UpdateData(SQL.c_str(), Msg);

}

void CrossingSingal::clearIsUpdate()
{
	string SQL = "update controlstate set IsUpdate=0";
	
	string Msg;
	mysql->UpdateData(SQL.c_str(), Msg);

}

void CrossingSingal::clearIsUpdate(string tablename)
{
	string SQL = "update " + tablename + " set IsUpdate=0";
	string Msg;
	mysql->UpdateData(SQL.c_str(), Msg);
}

void CrossingSingal::setPlanType(int type)
{
	planType = type;
}

void CrossingSingal::initControlState()
{
	string SQL = "update controlstate set Priority='MAJOR',IsUpdate='0'";

	string Msg;
	mysql->UpdateData(SQL.c_str(), Msg);
}

void CrossingSingal::setMysql(VspdCToMySQL* my_sql)
{
	mysql = my_sql;
}

