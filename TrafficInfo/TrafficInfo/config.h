#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "tinyxml/tinyxml.h"
#include <string>
#include <map>
using namespace std;

//获取数据库连接配置
map<string, string> getDatabaseConfig();

#endif