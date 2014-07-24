#ifndef _ENCODER_H
#define _ENCODER_H

#include <string>
#include "msg_json.h"
#include "tools.h"

using namespace std;

namespace encoder
{
	inline void encode_msg(msg_json& msg, string& result)
	{
		result += string((const char*)&msg, msg_json::_header_size);
		tools::convert_binary((char*)msg._json_str_utf8, msg._total_len - msg_json::_header_size);
		result += string(msg._json_str_utf8, msg._total_len - msg_json::_header_size);
	}
}

#endif
