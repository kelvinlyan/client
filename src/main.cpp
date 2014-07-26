#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "json/json.h"
#include "client.h"
#include "config.h"
#include "protocol_system.h"

using boost::asio::ip::tcp;

int main()
{
	protocol_system::shared();
	boost::asio::io_service ios;
	client c(ios, config::shared()->get_ip(), config::shared()->get_port());
	boost::thread thread(boost::bind(&boost::asio::io_service::run, &ios));
	c.login(config::shared()->get_id(), config::shared()->get_passwd());
	

	while(1)
	{
		string s1, s2;
		cin >> s1 >> s2;
		Json::Value msg;
		if(s2 != "null")
		{
			msg["msg"] = Json::arrayValue;
			Json::Value& ref = msg["msg"];
			int begin = 0;
			while(true)
			{
			 	int pos = s2.find(',', begin);
				if(pos != string::npos)
				{
					ref.append(atoi(s2.substr(begin, pos - begin).c_str()));
					begin = pos + 1;
				}
				else
				{
					ref.append(atoi(s2.substr(begin).c_str()));
					break;
				}
			}
		}
		c.write(atoi(s1.c_str()), msg);
			
	}
}



