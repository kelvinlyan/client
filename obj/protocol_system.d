obj/protocol_system.d : src/protocol_system.cpp include/protocol_system.h \
 include/singleton.h include/xml_parser.h include/config.h \
 include/logger.h
obj/protocol_system.o : src/protocol_system.cpp include/protocol_system.h \
 include/singleton.h include/xml_parser.h include/config.h \
 include/logger.h
	g++ -c src/protocol_system.cpp -o obj/protocol_system.o -Iinclude -lboost_system -lboost_thread -ljsoncpp -ltinyxml
