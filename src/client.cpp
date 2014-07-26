#include "client.h"

client::client(boost::asio::io_service& io_service, const string& ip, const string& port)
	: _connector(tcp_connector::create(io_service)), _player_id(0), _net_id(0)
{
	_connector->connect(ip, port);
	_connector->set_handler(boost::bind(&client::handle_msg, this, _1));
}

void client::login(const string& id, const string& passwd)
{
	Json::Value val;
	val["msg"] = Json::arrayValue;
	val["msg"].append(id);
	val["msg"].append(passwd);

	write(client::login_req, val);
}

void client::register_account(const string& id, const string& passwd)
{
	Json::Value val;
	val["msg"] = Json::arrayValue;
	val["msg"].append(id);
	val["msg"].append(passwd);

	write(client::register_req, val);
}

void client::write(int type, Json::Value& data)
{
	protocol* ptr = protocol_system::shared()->get_protocol_by_index(type);
	if(!ptr)
	{
		Log("type(%d) not found\n", type);
		return;
	}
	
	string str = data.toStyledString();
	str = tools::tighten(str);
	std::cout << str << std::endl;

	if(ptr->_sample == "")
		protocol_system::shared()->update_sample(ptr, str);

	msg_json msg;
	msg._player_id = _player_id;
	msg._net_id = _net_id;
	msg._type = type;
	msg._json_str_utf8 = str.data();
	msg._total_len = str.size() + msg_json::_header_size;
	
	string content;
	code_breaker::encode_msg_json(msg, content);


	_connector->write(content);


}

void client::handle_msg(string& str)
{
	msg_json m;

	code_breaker::decode_msg_json_helper helper(str);

	while(helper.decode_msg_json(m))
	{
		if(m._type == client::login_resp)
		{
			_player_id = m._player_id;
			_net_id = m._net_id;
		}

		Log("type: %d\ns2c: %s\n", m._type, m._json_str_utf8);
	}
}



