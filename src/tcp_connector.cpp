#include "tcp_connector.h"


tcp_connector::Tcp_Pointer tcp_connector::create(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator)
{
	return tcp_connector::Tcp_Pointer(new tcp_connector(io_service, endpoint_iterator));
}

tcp_connector::tcp_connector(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator)
	: _io_service(io_service), _socket(io_service)
{
	boost::asio::async_connect(_socket, endpoint_iterator, 
		boost::bind(&tcp_connector::handle_connect, shared_from_this(), boost::asio::placeholders::error));
}

void tcp_connector::set_handler(Msg_Handler handler)
{
	_handler = handler;
}

void tcp_connector::write(const string& msg)
{
	_io_service.post(boost::bind(&tcp_connector::do_write, shared_from_this(), msg));
}

void tcp_connector::close()
{
	_io_service.post(boost::bind(&tcp_connector::do_close, shared_from_this()));
}

void tcp_connector::handle_connect(const boost::system::error_code& error)
{
	if(!error)
	{
		Log("connect success\n");
		post_read0();
	}
	else
	{
		Log("connect error: %s\n", error.message().c_str());
	}
}

void tcp_connector::post_read0()
{
	_socket.async_read_some(boost::asio::null_buffers(), 
		boost::bind(&tcp_connector::handle_read, shared_from_this(), boost::asio::placeholders::error, 
		boost::asio::placeholders::bytes_transferred));
}

void tcp_connector::handle_read(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	if(!error)
	{
		std::size_t len = _socket.read_some(boost::asio::buffer(_read_buff, _max_buff_size));

		Log("read %d bytes\n", len);
		if(_handler)
		{
			string msg(_read_buff, len);
			_handler(msg);
		}
		post_read0();
	}
	else
	{
		Log("read error: %s\n", error.message().c_str());
		do_close();
	}
}

void tcp_connector::do_write(const string& str)
{
	bool write_in_progress = !_write_queue.empty();
	_write_queue.push_back(str);
	if(!write_in_progress)
	{
		boost::asio::async_write(_socket, boost::asio::buffer(_write_queue.front().c_str(), _write_queue.front().size()),
			boost::bind(&tcp_connector::handle_write, shared_from_this(), boost::asio::placeholders::error));
	}
}

void tcp_connector::handle_write(const boost::system::error_code& error)
{
	if(!error)
	{
		Log("write %d bytes\n", _write_queue.front().size());
		_write_queue.pop_front();
		if(!_write_queue.empty())
		{
			boost::asio::async_write(_socket, boost::asio::buffer(_write_queue.front().c_str(), _write_queue.front().size()),
				boost::bind(&tcp_connector::handle_write, shared_from_this(), boost::asio::placeholders::error));
		}
	}
	else
	{
		Log("write error: %s\n", error.message().c_str());
		do_close();
	}
}

void tcp_connector::do_close()
{
	_socket.close();
	Log("close\n");
}


