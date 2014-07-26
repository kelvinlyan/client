#ifndef _CODE_BREAKER_H
#define _CODE_BREAKER_H

#include <string>
#include "msg_json.h"
#include "tools.h"

using namespace std;

namespace code_breaker
{
	inline void encode_msg_json(msg_json& msg, string& result)
	{
		result += string((const char*)&msg, msg_json::_header_size);
		tools::convert_binary((char*)msg._json_str_utf8, msg._total_len - msg_json::_header_size);
		result += string(msg._json_str_utf8, msg._total_len - msg_json::_header_size);
	}

	class decode_msg_json_helper
	{
		public:
			decode_msg_json_helper(string& msg)
				: _msg(msg), _offset(0){}

			~decode_msg_json_helper(){}	

			bool decode_msg_json(msg_json& result)
			{
				if(_offset >= _msg.size())
					return false;
				if(_msg.size() - _offset < msg_json::_header_size)
					return false;
				
				const msg_json* ptr = (const msg_json*)(_msg.c_str() + _offset);

				if(ptr->_total_len > _msg.size() - _offset)
					return false;

				result._type = ptr->_type;
				result._player_id = ptr->_player_id;
				result._net_id = ptr->_net_id;
				result._total_len = ptr->_total_len;
				char* pstr = (char*)malloc(ptr->_total_len - msg_json::_header_size + 1);
				memcpy(pstr, _msg.c_str() + _offset + msg_json::_header_size, ptr->_total_len - msg_json::_header_size);
				tools::convert_binary(pstr, ptr->_total_len - msg_json::_header_size);
				pstr[ptr->_total_len - msg_json::_header_size] = 0;
				result._json_str_utf8 = pstr;

				_offset += ptr->_total_len;

				return true;
			}

		private:
			string& _msg;
			int _offset;
	};
}

#endif
