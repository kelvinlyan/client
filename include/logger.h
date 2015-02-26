#ifndef _LOGGER_H
#define _LOGGER_H

#include <stdio.h>
//#include <boost/log.hpp>

#define Log(...) \
	printf(__VA_ARGS__)

/*class logger : public singleton<logger>
{
	private:
		
};*/


#endif
