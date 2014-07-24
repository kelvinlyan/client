#include "client.h"

client::client(boost::asio::io_service& io_service, const string& ip, const string& port)
	: _connector(tcp_connector::create(io_service, get_resolver_iterator(io_service, ip, port))), _player_id(0), _net_id(0)
{
}

void client::set_handler(tcp_connector::Msg_Handler& handler)
{
	_connector->set_handler(handler);
}

tcp::resolver::iterator client::get_resolver_iterator(boost::asio::io_service& io_service, const string& ip, const string& port)
{
	tcp::resolver resolver(io_service);
	tcp::resolver::query query(ip, port);
	return resolver.resolve(query);
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
	msg_json msg;
	msg._player_id = _player_id;
	msg._net_id = _net_id;
	msg._type = type;
	string str = data.toStyledString();
	str = tools::tighten(str);
	msg._json_str_utf8 = str.data();
	msg._total_len = str.size() + msg_json::_header_size;
	
	string content;
	encoder::encode_msg(msg, content);

	_connector->write(content);
}

void client::handle_msg(string& msg)
{
	msg_json m;
	//msg_json* ptr = 
}



