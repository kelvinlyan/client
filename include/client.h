#ifndef _CLIENT_H
#define _CLIENT_H

#include <boost/asio.hpp>
#include "tcp_connector.h"
#include "noncopyable.h"
#include "encoder.h"
#include "json/json.h"

using boost::asio::ip::tcp;


class client : public noncopyable
{
	public:
		enum
		{
			account_begin = 10,
			register_req,
			login_req,
			logout_req,
		};

	public:
		client(boost::asio::io_service& io_service, const string& ip, const string& port);
		~client(){}
		void set_handler(tcp_connector::Msg_Handler& msg);
		void login(const string& id, const string& passwd);
		void register_account(const string& id, const string& passwd);
		void write(int type, Json::Value& msg);
		void handle_msg(string& msg);

	private:
		static tcp::resolver::iterator get_resolver_iterator(boost::asio::io_service& io_service, const string& ip, const string& port);
		tcp_connector::Tcp_Pointer _connector;

		int _player_id;
		int _net_id;
};

#endif
