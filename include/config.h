#ifndef _CONFIG_H
#define _CONFIG_H

#include <string>
#include "singleton.h"
#include "xml_parser.h"
#include "logger.h"

using namespace std;

class config : public singleton<config>
{
	public:
		config();
		virtual ~config(){}
		void load_file();
		string get_sample_file();
		string get_ip();
		string get_port();
		string get_id();
		string get_passwd();

	private:
		string _id;
		string _passwd;
	    string _sample_file;
		string _ip;
		string _port;
};

#endif
