obj/client.d : src/client.cpp include/client.h include/tcp_connector.h \
 include/logger.h include/noncopyable.h include/code_breaker.h \
 include/msg_json.h include/tools.h include/protocol_system.h \
 include/singleton.h include/xml_parser.h include/config.h
obj/client.o : src/client.cpp include/client.h include/tcp_connector.h \
 include/logger.h include/noncopyable.h include/code_breaker.h \
 include/msg_json.h include/tools.h include/protocol_system.h \
 include/singleton.h include/xml_parser.h include/config.h
	g++ -c src/client.cpp -g -o obj/client.o -Iinclude -lboost_system -lboost_thread -ljsoncpp -ltinyxml
