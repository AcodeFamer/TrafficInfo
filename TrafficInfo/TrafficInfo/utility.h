#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <sstream>
#include <string>
#include <atltime.h>

using namespace std;

//int杞瑂tring***********************
string int2str(int num);


//****************date鐨刬nt杞瑂tring*************
string num2date(int date);
string num2time(int time);


/******************鏇存柊鏃堕棿***************
time:褰撳墠鏃堕棿
gap锛氭椂闂撮棿闅?
杩斿洖鏇存柊鍚庣殑鏃堕棿
*/
string updateTime(string time,int gap);
/***********string杞琲nt******************
*/
int str2int(string s);


string getFileName(char* fullpathname);

string float2str(float num);

string datetime2str(CTime time);


#endif