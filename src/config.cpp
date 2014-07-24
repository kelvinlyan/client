#include "config.h"

config::config()
	: _sample_file(""), _ip(""), _port("")
{
	load_file();
}

void config::load_file()
{
	xml_parser parser("../etc/config.xml");
	TiXmlElement* pNode;
	if(!parser.get_first_node("Connection", pNode))
	{
		Log("config error\n");
		exit(0);
	}

	for(TiXmlAttribute* pAttr = pNode->FirstAttribute(); pAttr; pAttr = pAttr->Next())
	{
		if(pAttr->Name() == string("Ip"))
			_ip = pAttr->Value();
		if(pAttr->Name() == string("Port"))
			_port = pAttr->Value();
	}
	
	if(!parser.get_first_node("Protocols", pNode))
	{
		Log("config error\n");
		exit(0);
	}

	for(TiXmlAttribute* pAttr = pNode->FirstAttribute(); pAttr; pAttr = pAttr->Next())
	{
		if(pAttr->Name() == string("File"))
			_sample_file = pAttr->Value();
	}

	if(!parser.get_first_node("Acount", pNode))
	{
		Log("config error\n");
		exit(0);
	}

	for(TiXmlAttribute* pAttr = pNode->FirstAttribute(); pAttr; pAttr = pAttr->Next())
	{
		if(pAttr->Name() == string("Id"))
			_id = pAttr->Value();
		if(pAttr->Name() == string("Passwd"))
			_passwd = pAttr->Value();
	}
	if(_ip == "" || _port == "" || _sample_file == "" || _id == "" || _passwd == "")
	{
		Log("config error\n");
		exit(0);
	}
	
	Log("Server: %s:%s\n", _ip.c_str(), _port.c_str());
	Log("Sample File: %s\n", _sample_file.c_str());
	Log("Id: %s\nPasswd: %s\n", _id.c_str(), _passwd.c_str());
}

string config::get_ip()
{
	return _ip;
}

string config::get_port()
{
	return _port;
}

string config::get_sample_file()
{
	return _sample_file;
}

string config::get_id()
{
	return _id;
}

string config::get_passwd()
{
	return _passwd;
}
