#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "json/json.h"
#include "client.h"
#include "config.h"
#include "protocol_system.h"
//#include "test.h"

using boost::asio::ip::tcp;

void test()
{
	xml_parser parser("../etc/sample.xml");
	string version, stand, encoding;
	if(parser.get_declaration(version, stand, encoding))
		cout << version << ", " << stand << ", " << encoding << endl;
	
	TiXmlElement* pNode;
	string str("DataFormat");
	if(parser.get_first_node(str, pNode))
		cout << pNode->Value() << endl;


	pause();
}

int main()
{
	//test();

	protocol_system::shared();
	boost::asio::io_service ios;
	client c(ios, config::shared()->get_ip(), config::shared()->get_port());
	boost::thread thread(boost::bind(&boost::asio::io_service::run, &ios));
	c.login(config::shared()->get_id(), config::shared()->get_passwd());
	
	while(1)
	{
		//string cmd;
		//cin.getline(cmd);
		//cout << cmd << endl;
		string s1, s2, s3;
		cin >> s1 >> s2 >> s3;
		Json::Value msg;
		
		if(atoi(s1.c_str()) == 1401)
		{
			msg["msg"] = Json::arrayValue;
			Json::Value& ref = msg["msg"];
			ref.append(s2);
			ref.append(0);
			ref.append(false);
		}
		else if(s2 != "null")
		{
			msg["msg"] = Json::arrayValue;
			Json::Value& ref = msg["msg"];
			int begin = 0;
			while(true)
			{
			 	int pos = s2.find(',', begin);
				if(pos != string::npos)
				{
					string str = s2.substr(begin, pos - begin);
					if(str[0] == '\'')
					{
						str = str.substr(1, str.size() - 2);
						ref.append(str);
					}
					else if(str[0] == '\"')
					{
						str = str.substr(1, str.size() - 1);
						ref.append((bool)atoi(str.c_str()));
					}
					else
					{
						ref.append(atoi(str.c_str()));
					}
					begin = pos + 1;
				}
				else
				{
					string str = s2.substr(begin);
					if(str[0] == '\'')
					{
						str = str.substr(1, str.size() - 2);
						ref.append(str);
					}
					else if(str[0] == '\"')
					{
						str = str.substr(1, str.size() - 1);
						ref.append((bool)atoi(str.c_str()));
					}
					else
					{
						ref.append(atoi(str.c_str()));
					}
					break;
				}
			}
		}
		int num = atoi(s3.c_str());
		while(num--)
			c.write(atoi(s1.c_str()), msg);
	}
}



