#include "protocol_system.h"

protocol_system::protocol_system()
	: _xml_parser(config::shared()->get_sample_file())
{
	load_file();
}

void protocol_system::load_file()
{
	vector<TiXmlElement*> pNodeVec;
	_xml_parser.get_all_node("DataFormat", pNodeVec);
	for(vector<TiXmlElement*>::iterator iter = pNodeVec.begin(); iter != pNodeVec.end(); ++iter)
	{
		TiXmlElement* pNode = *iter;
		protocol* ptr = new protocol;
		for(TiXmlAttribute* pAttr = pNode->FirstAttribute(); pAttr; pAttr = pAttr->Next())
		{
			if(pAttr->Name() == string("Protocol"))
				ptr->_name = pAttr->Value();
			else if(pAttr->Name() == string("Index"))
				ptr->_index = atoi(pAttr->Value());
			else if(pAttr->Name() == string("sample"))
				ptr->_sample = pAttr->Value();
		}
		_index_to_protocol_map.insert(make_pair(ptr->_index, ptr));
		_name_to_protocol_map.insert(make_pair(ptr->_name, ptr));
	}

	/*for(Index2Protocol::iterator iter = _index_to_protocol_map.begin(); iter != _index_to_protocol_map.end(); ++iter)
	{
		cout << iter->second->_name << " " << iter->second->_index << " " << iter->second->_sample << endl;
	}*/
}

protocol* protocol_system::get_protocol_by_index(int index)
{
	Index2Protocol::iterator iter = _index_to_protocol_map.find(index);
	if(iter != _index_to_protocol_map.end())
	{
		return iter->second;
	}
	return NULL;
}

protocol* protocol_system::get_protocol_by_name(const string& name)
{
	Name2Protocol::iterator iter = _name_to_protocol_map.find(name);
	if(iter != _name_to_protocol_map.end())
	{
		return iter->second;
	}
	return NULL;
}

void protocol_system::update_sample(protocol* ptr, const string& sample)
{
	ptr->_sample = sample;
	map<string, string> condition;
	condition.insert(make_pair("Protocol", ptr->_name));
	map<string, string> target;
	target.insert(make_pair("Sample", sample));
	_xml_parser.modify_first_attribute_by_condition("DataFormat", condition, target);
}




