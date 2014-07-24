obj/config.d : src/config.cpp include/config.h include/singleton.h \
 include/xml_parser.h include/logger.h
obj/config.o : src/config.cpp include/config.h include/singleton.h \
 include/xml_parser.h include/logger.h
	g++ -c src/config.cpp -g -o obj/config.o -Iinclude -lboost_system -lboost_thread -ljsoncpp -ltinyxml
