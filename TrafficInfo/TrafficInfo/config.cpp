#include "stdafx.h"
#include "config.h"

//��ȡ���ݿ��������� �������ò���db_config
//db_config��SuccessFlag��־��ʾ�Ƿ�ɹ���ȡ�������ݣ��ɹ�Ϊsuccess ʧ��Ϊfail
map<string, string> getDatabaseConfig()
{
	map<string, string> db_config;
	TiXmlDocument doc;
	//��ȡ�����ļ�ʧ��
	if (!doc.LoadFile("config.xml"))
	{
		//cerr << doc.ErrorDesc();
		doc.Clear();
		db_config["SuccessFlag"] = "fail";
		return db_config;
	}
	//����ÿһ��Ԫ��
	for (TiXmlElement* root = doc.FirstChildElement(); root != NULL; root = doc.NextSiblingElement())
	{
		if (root != NULL)
		{
			string root_name = root->Value();
			//conf_db��Ԫ��Ϊ��������
			if (root_name == "conf_db")
			{
				//��ȡ��Ӧ��ǩָ��
				TiXmlElement* elem1 = root->FirstChildElement("host");
                TiXmlElement* elem2 = root->FirstChildElement("user");
				TiXmlElement* elem3 = root->FirstChildElement("port");
				TiXmlElement* elem4 = root->FirstChildElement("passwd");
				TiXmlElement* elem5 = root->FirstChildElement("dbname");
				TiXmlElement* elem6 = root->FirstChildElement("charset");
				//��������һ��ָ��Ϊ�����ȡʧ��
				if (elem1 == NULL || elem2 == NULL || elem3 == NULL || elem4 == NULL || elem5 == NULL || elem6 == NULL)
				{
					doc.Clear();
					db_config["SuccessFlag"] = "fail";
					return db_config;
				}
				//��ȡ��������
				db_config["host"] = elem1->GetText();
				db_config["user"] = elem2->GetText();
				db_config["port"] = elem3->GetText();
				db_config["passwd"] = elem4->GetText();
				db_config["dbname"] = elem5->GetText();
				db_config["charset"] = elem6->GetText();
				//������������
				doc.Clear();
				db_config["SuccessFlag"] = "success";
				return db_config;

				
			}
		}
	}
	//���������е�Ԫ��û��conf_db��Ԫ�أ�ʧ��
	doc.Clear();
	db_config["SuccessFlag"] = "fail";
	return db_config;
}
