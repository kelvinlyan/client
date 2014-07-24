#ifndef _TCP_CONNECTOR_H
#define _TCP_CONNECTOR_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <deque>
#include <string>
#include "logger.h"

using boost::asio::ip::tcp;
using namespace std;


class tcp_connector : public boost::enable_shared_from_this<tcp_connector>
{
	public:
		static const std::size_t _max_buff_size = 1024;
		typedef boost::function<void(string&)> Msg_Handler;
		typedef boost::shared_ptr<tcp_connector> Tcp_Pointer;

	public:
		~tcp_connector(){}
		static Tcp_Pointer create(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator);
		void set_handler(Msg_Handler handler);
		void write(const string& msg);
		void close();

	private:
		tcp_connector(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator);

		void handle_connect(const boost::system::error_code& error);
		void handle_read(const boost::system::error_code& error, std::size_t bytes_transferred);
		void handle_write(const boost::system::error_code& error); 

		void post_read0();
		void do_write(const string& msg);
		void do_close();

	private:
		Msg_Handler _handler;
		boost::asio::io_service& _io_service;
		tcp::socket _socket;
		char _read_buff[_max_buff_size];
		typedef std::deque<string> msg_queue;
		msg_queue _write_queue;
		//pthread_mutex_t _write_mutex;
};


#endif
