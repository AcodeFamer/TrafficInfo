#include "stdafx.h"
#include "config.h"

//获取数据库连接配置 返回配置参数db_config
//db_config中SuccessFlag标志表示是否成功获取配置数据，成功为success 失败为fail
map<string, string> getDatabaseConfig()
{
	map<string, string> db_config;
	TiXmlDocument doc;
	//读取配置文件失败
	if (!doc.LoadFile("config.xml"))
	{
		//cerr << doc.ErrorDesc();
		doc.Clear();
		db_config["SuccessFlag"] = "fail";
		return db_config;
	}
	//查找每一个元素
	for (TiXmlElement* root = doc.FirstChildElement(); root != NULL; root = doc.NextSiblingElement())
	{
		if (root != NULL)
		{
			string root_name = root->Value();
			//conf_db的元素为配置数据
			if (root_name == "conf_db")
			{
				//获取对应标签指针
				TiXmlElement* elem1 = root->FirstChildElement("host");
                TiXmlElement* elem2 = root->FirstChildElement("user");
				TiXmlElement* elem3 = root->FirstChildElement("port");
				TiXmlElement* elem4 = root->FirstChildElement("passwd");
				TiXmlElement* elem5 = root->FirstChildElement("dbname");
				TiXmlElement* elem6 = root->FirstChildElement("charset");
				//若其中有一个指针为空则读取失败
				if (elem1 == NULL || elem2 == NULL || elem3 == NULL || elem4 == NULL || elem5 == NULL || elem6 == NULL)
				{
					doc.Clear();
					db_config["SuccessFlag"] = "fail";
					return db_config;
				}
				//获取配置数据
				db_config["host"] = elem1->GetText();
				db_config["user"] = elem2->GetText();
				db_config["port"] = elem3->GetText();
				db_config["passwd"] = elem4->GetText();
				db_config["dbname"] = elem5->GetText();
				db_config["charset"] = elem6->GetText();
				//返回配置数据
				doc.Clear();
				db_config["SuccessFlag"] = "success";
				return db_config;

				
			}
		}
	}
	//遍历完所有的元素没有conf_db的元素，失败
	doc.Clear();
	db_config["SuccessFlag"] = "fail";
	return db_config;
}
