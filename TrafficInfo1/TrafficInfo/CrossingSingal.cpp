#include "stdafx.h"
#include "CrossingSingal.h"

//��ʼ��·�ڷ���û�п���
int CrossingSingal::IsStart = 0;

CrossingSingal::CrossingSingal(string crossing_id, VspdCToMySQL* my_sql, vector<string> stream_pri, vector<string> link_in_id, vector<string> link_out_id)
{
	//��ʼ�����ݿ����
	mysql = my_sql;
	//·��id
	crossingId = crossing_id;
	//��ʼ��û���źŻ�
	isSingal = 0;
	//��ʼ����ǰ��λ����0��
	second = 0;
	//��ʼ��Ϊ��һ������
	isFirstPeroid = 1;
	//��ʼ����ǰ��0��λ
	phaseIndex = 0;

	//��ʼ����ǰ���Ʒ�����λ��Ϊ-1����ִ�е�0��λʱֱ�ӽ�����λ�л���ת����һ��λ��
	singal_info.phaseNum = 0;
	//��ʼ����������link id
	linkInId = link_in_id;
	linkOutId = link_out_id;
}

CrossingSingal::~CrossingSingal()
{

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

vector<string> CrossingSingal::getActivePlanInfo()
{
	string SQL = "select PlanIndex,PhaseNum,Period,PhaseOffset from controlplan where CrossingId=";
	SQL = SQL + "'" + crossingId + "' AND IsActive='1'";
	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL.c_str(), 4, Msg);

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

void CrossingSingal::execute_singal_control()
{
	if (isFirstPeroid == 0)
	{
		CString mes;
		mes.Format("second=%d,phaseIndex=%d,greenTime=%d,redTime=%d", second, phaseIndex, singal_info.greenTime[phaseIndex], singal_info.redTime[phaseIndex]);
		MessageBox(NULL, mes, "", MB_OK);
	}

	int stream_num = linkInId.size() - 1;//��·�ڳ��� ����
	//���濪ʼ��һ������
	if (isFirstPeroid == 1)
	{
		isFirstPeroid = 0;
		singal_info = singal_info_next;
		getPhaseStreamPri();
		phaseIndex=1;
		curStreamPri = phaseStreamPri[1];
		for (int index = 1; index <= stream_num; index++)
		{
			setStreamPriority(index, phaseStreamPri[1][index]);
			updateControlState(index, phaseStreamPri[1][index]);
		}
		MessageBox(NULL, "first peroid", "", MB_OK);
	}
	
	else
	{
		/********************�ж��Ƿ���Ҫ�����Ƶ�****************/
		if (second == singal_info.greenTime[phaseIndex] - 3) //�ж��Ƿ���Ҫ�����Ƶ�
		{
			clearIsUpdate();
			//��������
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
						MessageBox(NULL, "set yellow 1", "", MB_OK);
					}
				}
				else
				{
					singal_info.planIndex = singal_info_next.planIndex;  //����ֻ�޸Ŀ��Ʒ�����ţ�û���޸�����ִ�еķ�����λʱ������
					getPhaseStreamPri();//��ȡ��������һ�����ڵ�Ȩ�ޣ�
					if (curStreamPri[index] == "MAJOR" && phaseStreamPri[1][index] == "BARRED")
					{
						//��Ҫ�����Ƶ�
						setStreamPriority(index, "MINOR");
						curStreamPri[index] = "MINOR";
						updateControlState(index, "MINOR");
						MessageBox(NULL, "set yellow 2", "", MB_OK);
					}
				}
				
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
					for (int index = 1; index <= stream_num; index++)
					{
						if (curStreamPri[index] != "BARRED")
						{
							setStreamPriority(index, "BARRED");
							curStreamPri[index] = "BARRED";
							updateControlState(index, "BARRED");
						}
					}
				}
				else
				{
					for (int index = 1; index <= stream_num; index++)
					{
						if (curStreamPri[index] != phaseStreamPri[phaseIndex][index])
						{
							setStreamPriority(index, phaseStreamPri[phaseIndex][index]);
							curStreamPri[index] = phaseStreamPri[phaseIndex][index];
							updateControlState(index, phaseStreamPri[phaseIndex][index]);
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
				for (int index = 1; index <= stream_num; index++)
				{
					if (curStreamPri[index] != phaseStreamPri[phaseIndex][index])
					{
						setStreamPriority(index, phaseStreamPri[phaseIndex][index]);
						curStreamPri[index] = phaseStreamPri[phaseIndex][index];
						updateControlState(index, phaseStreamPri[phaseIndex][index]);
					}
				}
				return ;
			}
		}
	}
	//ִ��������1
	second++;
}

void CrossingSingal::setStreamPriority(int stream_index, string pri)
{
	//������ʾ��ȡ�ĳ���Ȩ����Ϣ
	CString mes;
	mes.Format("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s", 
		phaseStreamPri[phaseIndex][1].c_str(), phaseStreamPri[phaseIndex][2].c_str(), phaseStreamPri[phaseIndex][3].c_str(), phaseStreamPri[phaseIndex][4].c_str(),
		phaseStreamPri[phaseIndex][5].c_str(), phaseStreamPri[phaseIndex][6].c_str(), phaseStreamPri[phaseIndex][7].c_str(), phaseStreamPri[phaseIndex][8].c_str(),
		phaseStreamPri[phaseIndex][9].c_str(), phaseStreamPri[phaseIndex][10].c_str(), phaseStreamPri[phaseIndex][11].c_str(), phaseStreamPri[phaseIndex][12].c_str(),
		phaseStreamPri[phaseIndex][13].c_str(), phaseStreamPri[phaseIndex][14].c_str(), phaseStreamPri[phaseIndex][15].c_str(), phaseStreamPri[phaseIndex][16].c_str()
		                                                          );
	//MessageBox(NULL, mes, "", MB_OK);
	

	
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
	SQL = SQL  + "PlanIndex='" + int2str(singal_info.planIndex) + "' AND CrossingId='" + crossingId + "'";
	/*
	CString mes1;
	mes1.Format("%s", SQL.c_str());
	MessageBox(NULL, mes1, "", MB_OK);
*/
	string Msg;
	vector<vector<string>> res = mysql->SelectData(SQL.c_str(), 1, Msg);

	phaseStreamPri.clear();
	vector<string> row(res.size() / singal_info.phaseNum + 1, "0");
	phaseStreamPri.push_back(row);
	//����λ�洢ÿ��������Ȩ��
	if (res.size() > 0)
	{
		int index = 0;
		for (int phase_i = 0; phase_i < singal_info.phaseNum; phase_i++)
		{
			vector<string> row;
			row.push_back("0");
			for (size_t stream_i = 0; stream_i < res.size() / singal_info.phaseNum; stream_i++)
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
	//
	

	string SQL = "update controlstate set Priority='" + pri + "',IsUpdate=1 where CrossingId='";
	SQL = SQL + crossingId + "' AND StreamIndex='" + int2str(stream_index) + "'";
	
	string Msg;
	mysql->UpdateData(SQL.c_str(), Msg);
	
}

void CrossingSingal::clearIsUpdate()
{
	string SQL = "update controlstate set IsUpdate=0";
	
	string Msg;
	mysql->UpdateData(SQL.c_str(), Msg);

}



