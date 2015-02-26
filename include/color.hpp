#ifndef _COMMON_COLOR_HPP
#define _COMMON_COLOR_HPP

#include <stdio.h>
#include <string>

namespace color
{
	enum{
		BLACK = 30,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		PURPLE,
		DARK_GREEN,
		WHITE
	};
	
#define CREATE(color) \
	static std::string m##color(const char* pstr) \
	{ \
		char buff[1024]; \
		sprintf(buff, "\033[%dm\033[1m%s\033[0m", color, pstr); \
		return string(buff); \
	} \
	static std::string m##color(int num) \
	{ \
		char buff[1024]; \
		sprintf(buff, "\033[%dm\033[1m%d\033[0m", color, num); \
		return string(buff); \
	} \
	static std::string m##color(unsigned int num) \
	{ \
		char buff[1024]; \
		sprintf(buff, "\033[%dm\033[1m%u\033[0m", color, num); \
		return string(buff); \
	} \
	static std::string m##color(double num) \
	{ \
		char buff[1024]; \
		sprintf(buff, "\033[%dm\033[1m%lf\033[0m", color, num); \
		return string(buff); \
	} \


	CREATE(BLACK);
	CREATE(RED);
	CREATE(GREEN);
	CREATE(YELLOW);
	CREATE(BLUE);
	CREATE(PURPLE);
	CREATE(DARK_GREEN);
	CREATE(WHITE);

};




#endif
