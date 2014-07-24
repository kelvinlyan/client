#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "json/json.h"
#include "client.h"
#include "config.h"
#include "protocol_system.h"

using boost::asio::ip::tcp;

int main()
{
	protocol_system::shared();
	boost::asio::io_service ios;
	client c(ios, config::shared()->get_ip(), config::shared()->get_port());
	boost::thread thread(boost::bind(&boost::asio::io_service::run, &ios));
	c.login(config::shared()->get_id(), config::shared()->get_passwd());
	

	while(1)
		sleep(1);
}



