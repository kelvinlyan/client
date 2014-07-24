#ifndef _MESSAGE_HANDLER_H
#define _MESSAGE_HANDLER_H

#include <string>
#include "tcp_connector.h"

using namespace std;

class message_handler : public iMessage_handler
{
	public:
		virtual void handle(string& msg);
};

#endif
