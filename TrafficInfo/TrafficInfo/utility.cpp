#include "stdafx.h"
#include "utility.h"


string int2str(int num)   
{   
	string str = "";   
	if(num == 0)   
		return "0";   

	if(num < 0)   
		str = "-" ;   
	num = abs(num);  // num = num > 0 ? num : -1 * num;  
	while(num )   
	{   
		str = (char)(num % 10 + 48) + str ;   
		num /= 10;   
	}   
	return str;   
}  

std::string num2date( int date )
{
	int day=date%100;
	date=date/100;
	int month=date%100;
	date=date/100;
	int year=date;

	string d=int2str(year)+"-";
	if(month<10)
	{
		d=d+"0"+int2str(month)+"-";
	}
	else
	{
		d=d+int2str(month)+"-";
	}

	if(day<10)
	{
		d=d+"0"+int2str(day)+"-";
	}
	else
	{
		d=d+int2str(day);
	}
	return d;
}

std::string num2time(int time)
{
	int second = time % 100;
	time = time / 100;
	int minute = time % 100;
	time = time / 100;
	int hour = time;

	string t;
	if (hour < 10)
	{
		t = t + "0" + int2str(hour) + ":";
	}
	else
	{
		t = t  + int2str(hour) + ":";
	}

	if (minute < 10)
	{
		t = t + "0" + int2str(minute) + ":";
	}
	else
	{
		t = t + int2str(minute) + ":";
	}

	if (second < 10)
	{
		t = t + "0" + int2str(second) + ":";
	}
	else
	{
		t = t + int2str(second);
	}
	return t;
}


std::string updateTime(string time, int gap)
{
	string hour, minute, second;
	int h, m, s;
	hour.push_back(time[0]);
	hour.push_back(time[1]);
	h = str2int(hour);

	minute.push_back(time[3]);
	minute.push_back(time[4]);
	m = str2int(minute);

	second.push_back(time[6]);
	second.push_back(time[7]);
	s = str2int(second);

	s = s + gap;

	int m_add = s / 60;

	s = s % 60;

	m = m + m_add;

	int h_add = m / 60;

	m = m % 60;

	h = h + h_add;

	string res;
	if (h < 10)
	{
		res = res + "0" + int2str(h);
	}
	else
	{
		res = res + int2str(h);
	}
	res = res + ":";

	if (m < 10)
	{
		res = res + "0" + int2str(m);
	}
	else
	{
		res = res + int2str(m);
	}
	res = res + ":";

	if (s < 10)
	{
		res = res + "0" + int2str(s);
	}
	else
	{
		res = res + int2str(s);
	}

	return res;

}

int str2int(string s)
{
	int length = s.size();
	int index;
	bool flag = true;
	for (int i = 0; i < length; i++)
	{
		if (s[i] != '0')
		{
			flag = false;
			index = i;
			break;
		}
	}
	if (flag)
		return 0;

	int res = 0;
	for (int i = index; i <length; i++)
	{
		res = res * 10 + (s[i] - 0x30);
	}
	return res;
}



string getFileName(char* fullpathname)
{
	int name_len = strlen(fullpathname);
	int index1=-1;
	for (int i = name_len - 1; i >= 0; i--)
	{
		if (fullpathname[i] == '/')
		{
			index1 = i;
			break;
		}
	}
	string name;
	for (int i = index1 + 1; i < name_len; i++)
	{
		name.push_back(fullpathname[i]);
	}
	return name;
}



string float2str(float num)
{
	ostringstream buffer;

	buffer << num;
	string str = buffer.str();

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '.')
		{
			if (str.size() - i - 1 > 2)
			{
				str.erase(i + 3);
				break;
			}
		}
	}
	return str;
}

std::string datetime2str(CTime time)
{
	int Year = time.GetYear(); ///年  
	
	int Month = time.GetMonth(); ///月  
	
	int Day = time.GetDay(); ///日  
	
	int Hour = time.GetHour(); ///小时  

	int Minute = time.GetMinute(); ///分钟  

	int Second = time.GetSecond(); ///秒  

	string Date = num2date(Year * 10000 + Month * 100 + Day);

	string Time = num2time(Hour * 10000 + Minute * 100 + Second);

	string datetime = Date +" "+ Time;
	

	return datetime;



}

