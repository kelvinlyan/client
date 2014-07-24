#ifndef _PROTOCOL_SYSTEM_H
#define _PROTOCOL_SYSTEM_H

#include <string>
#include <map>
#include "singleton.h"
#include "xml_parser.h"
#include "config.h"

using namespace std;

struct protocol
{
	public:
		int _index;
		string _name;
		string _sample;
};


class protocol_system : public singleton<protocol_system>
{
	public:
		protocol_system();
		virtual ~protocol_system(){}
		void load_file();
		protocol* get_protocol_by_index(int index);
		protocol* get_protocol_by_name(const string& name);
		void update_sample(protocol* ptr, const string& sample);
		
	private:
		typedef map<int, protocol*> Index2Protocol;
		typedef map<string, protocol*> Name2Protocol;
		Index2Protocol _index_to_protocol_map;
		Name2Protocol _name_to_protocol_map;
		xml_parser _xml_parser;
};


#endif
