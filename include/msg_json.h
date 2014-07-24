#ifndef _MSG_JSON_H
#define _MSG_JSON_H

struct msg_json
{
	public:
		enum{
			_header_size = 12
		};
		

		msg_json()
			:_net_id(0), _player_id(0), _json_str_utf8(NULL){}
		short _total_len;
		short _type;
		int _net_id;
		int _player_id;
		const char* _json_str_utf8;
};

#endif
