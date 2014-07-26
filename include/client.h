#ifndef _CLIENT_H
#define _CLIENT_H

#include <boost/asio.hpp>
#include "tcp_connector.h"
#include "noncopyable.h"
#include "code_breaker.h"
#include "json/json.h"
#include "protocol_system.h"

using boost::asio::ip::tcp;


class client : public noncopyable
{
	public:
		enum
		{
			account_req_begin = 10,
			register_req,
			login_req,
			logout_req,

			acount_resp_begin = 110,
			register_resp,
			login_resp,
			logout_resp,
			
		};

	public:
		client(boost::asio::io_service& io_service, const string& ip, const string& port);
		~client(){}
		void login(const string& id, const string& passwd);
		void register_account(const string& id, const string& passwd);
		void write(int type, Json::Value& msg);
		void handle_msg(string& str);

	private:
		tcp_connector::Tcp_Pointer _connector;
		map<int, time_t> _time_checker;

		int _player_id;
		int _net_id;
};

#endif
