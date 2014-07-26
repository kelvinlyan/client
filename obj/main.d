obj/main.d : src/main.cpp include/client.h include/tcp_connector.h \
 include/logger.h include/noncopyable.h include/code_breaker.h \
 include/msg_json.h include/tools.h include/protocol_system.h \
 include/singleton.h include/xml_parser.h include/config.h \
 include/config.h include/protocol_system.h
obj/main.o : src/main.cpp include/client.h include/tcp_connector.h \
 include/logger.h include/noncopyable.h include/code_breaker.h \
 include/msg_json.h include/tools.h include/protocol_system.h \
 include/singleton.h include/xml_parser.h include/config.h \
 include/config.h include/protocol_system.h
	g++ -c src/main.cpp -g -o obj/main.o -Iinclude -lboost_system -lboost_thread -ljsoncpp -ltinyxml
