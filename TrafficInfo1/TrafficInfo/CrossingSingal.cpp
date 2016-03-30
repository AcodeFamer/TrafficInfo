#include "stdafx.h"
#include "CrossingSingal.h"

//��ʼ��·�ڷ���û�п���
int CrossingSingal::IsStart = 0;
VspdCToMySQL* CrossingSingal::mysql = 0;
CrossingSingal::CrossingSingal(string crossing_id, vector<string> stream_pri, vector<string> link_in_id, vector<string> link_out_id)
{

	//·��id
	crossingId = crossing_id;
	//��ʼ��û���źŻ�
	isSingal = 0;
	//��ʼ����ǰ��λ����0��
	second = 0;
	//��ʼ��Ϊ��һ����λ
	isFirstPhase = 1;
	//��ʼ����ǰ��0��λ
	phaseIndex = 0;

	//��ʼ����ǰ���Ʒ�����λ��Ϊ-1����ִ�е�0��λʱֱ�ӽ�����λ�л���ת����һ��λ��
	singal_info.phaseNum = 0;
	//��ʼ����������link id
	linkInId = link_in_id;
	linkOutId = link_out_id;
	
	//��ʼ�����Ʒ�������
	planType = -1;
	//��ʼ�����г���ΪMAJOR
	curStreamPri = vector<string>(link_in_id.size()+1, "MAJOR");
	//controlstate IsUpdate���  0 1�仯
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
	
	//��ȡ������λ���̵ƺ��ʱ��
	all_red_time.push_back(0);  //Ĭ�ϵ�0����λʱ��Ϊ0
	all_green_time.push_back(0);
	for (size_t phase_i = 0; phase_i < res.size(); phase_i++)
	{
		int green_time = str2int(res[phase_i][0]);
		int amber_time = str2int(res[phase_i][1]);
		int red_time = str2int(res[phase_i][2]);
		//����λ˳��洢�̵�ʱ�䣬���ʱ��
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
//���ݿ��Ʒ�������ִ�п��Ʒ���
void CrossingSingal::execute_singal_control()
{
	int stream_num = linkInId.size() - 1;//��·�ڳ��� ����
	//ȫ�����
	if (planType == PLANTYPE_RED)
	{
		isFirstPhase = 1;//�������л��̶�����ʱ���ӵ�һ����λ��ʼִ��
		int is_pri_update = 0;  //�Ƿ���pri�仯
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
	//ȫ���Ƶ���˸
	else if (planType == PLANTYPE_YELLOW)
	{
		isFirstPhase = 1; //�������л��̶�����ʱ���ӵ�һ����λ��ʼִ��
		int is_pri_update = 0;  //�Ƿ���pri�仯
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
	//���߿��ƣ���ȡ��Ȩ�޾͸�
	else if (planType == PLANTYPE_ONLINE_CONTROL)  
	{
		isFirstPhase = 1;//�������л��̶�����ʱ����һ����λ��ʼִ��
		int stream_num = linkInId.size() - 1;//��·�ڳ��� ����
		getPhaseStreamPri();//��ȡ����Ȩ�����
		int is_pri_update = 0;  //�Ƿ���pri�仯
		for (int index = 1; index <= stream_num; index++)
		{
			if (curStreamPri[index] != phaseStreamPri[1][index])   //��ʱֻ��ȡ��һ������
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
	//�̶�����
	else if (planType == PLANTYPE_FIX_PEROID)
	{
		if (isFirstPhase == 0)
		{
			CString mes;
			//mes.Format("second=%d,phaseIndex=%d,greenTime=%d,redTime=%d", second, phaseIndex, singal_info.greenTime[phaseIndex], singal_info.redTime[phaseIndex]);
			//mes.Format("second=%d,phaseIndex=%d,greenTime.size=%d,redTime.size=%d", second, phaseIndex, singal_info.greenTime.size(), singal_info.redTime.size());
			//MessageBox(NULL, mes, "", MB_OK);
			
		}

		int stream_num = linkInId.size() - 1;//��·�ڳ��� ����
		//���濪ʼ��һ������
		if (isFirstPhase == 1)
		{
			isFirstPhase = 0;
			singal_info = singal_info_next;//���ؿ��Ʒ�������ǰ
			getPhaseStreamPri();   //��ȡ·�ڳ���Ȩ��
			phaseIndex = 1;  //��ǰִ�е�һ����λ
			second = 0;   //��һ����λ�Ѿ�ִ��0��
			curStreamPri = phaseStreamPri[1];  //��ǰ���Ƴ���Ȩ��
			for (int index = 1; index <= stream_num; index++)
			{
				setStreamPriority(index, phaseStreamPri[1][index]); //���ó���Ȩ��
				updateControlState(index, phaseStreamPri[1][index]);//���¿���״̬
			}
			changeIsUpdate();
		}

		else
		{
			/********************�ж��Ƿ���Ҫ�����Ƶ�****************/
			if (second == singal_info.greenTime[phaseIndex] - 3) //�ж��Ƿ���Ҫ�����Ƶ�
			{
				//clearIsUpdate();
				//��������
				int is_pri_update = 0;  //�Ƿ���pri�仯
				for (int index = 1; index <= stream_num; index++)
				{
					if (phaseIndex < singal_info.phaseNum)
					{
						if (curStreamPri[index] == "MAJOR" && phaseStreamPri[phaseIndex + 1][index] == "BARRED")
						{
							//��Ҫ�����Ƶ�
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
						singal_info.planIndex = singal_info_next.planIndex;  //����ֻ�޸Ŀ��Ʒ�����ţ�û���޸�����ִ�еķ�����λʱ������
						getPhaseStreamPri();//��ȡ��������һ�����ڵ�Ȩ��
						if (curStreamPri[index] == "MAJOR" && phaseStreamPri[1][index] == "BARRED")
						{
							//��Ҫ�����Ƶ�
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
			//�л���һ����λ
			if (second == singal_info.greenTime[phaseIndex])
			{
				second = 0;
				phaseIndex++;
				clearIsUpdate();
				//���ڵ�ǰ����
				if (phaseIndex <= singal_info.phaseNum)
				{
					if (singal_info.greenTime[phaseIndex] == 0)   //��һ����λȫ�Ǻ��
					{
						int is_pri_update = 0;  //�Ƿ���pri�仯
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
						int is_pri_update = 0;  //�Ƿ���pri�仯
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
				//��Ҫ�л���һ������
				else
				{
					second = 0;
					phaseIndex = 1;
					singal_info = singal_info_next;
					getPhaseStreamPri();
					int is_pri_update = 0;  //�Ƿ���pri�仯
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
		//ִ��������1
		second++;
	}
	//������������Ŀ��Ʒ������ͣ����źŻ�·��û�ж����IsActive=1�Ŀ��Ʒ�����������crossingstream�����ó���Ȩ��crossingstream
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
	//������ʾ��ȡ�ĳ���Ȩ����Ϣ
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
	//��ȡ��·�� ��ǰִ�з����� ÿһ����λ����Ȩ��
	string SQL = "select StreamState from phasestream where ";
	SQL = SQL  + "PlanIndex='" + int2str(singal_info.planIndex) + "' AND CrossingId='" + crossingId + "' ORDER BY PhaseId,StreamIndex";
	qps_GUI_printf("%s", SQL.c_str());

	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL.c_str(), 1, Msg);


	phaseStreamPri.clear();
	vector<string> row(linkInId.size(), "0");
	phaseStreamPri.push_back(row);
	//����λ�洢ÿ��������Ȩ��
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
	//ԭ�ȵķ���������pri�Ǹ��¶�Ӧ��IsUpdate
	//string SQL = "update controlstate set Priority='" + pri + "',IsUpdate=1 where CrossingId='";
	//SQL = SQL + crossingId + "' AND StreamIndex='" + int2str(stream_index) + "'";
	
	//����ͳһ����IsUpdate
	string SQL = "update controlstate set Priority='" + pri + "' where CrossingId='";
	SQL = SQL + crossingId + "' AND StreamIndex='" + int2str(stream_index) + "'";
	string Msg;
	mysql->UpdateData(SQL.c_str(), Msg);
}

void CrossingSingal::changeIsUpdate()
{
	//�仯IsUpdateֵ
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

