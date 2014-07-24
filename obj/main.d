obj/main.d : src/main.cpp include/client.h include/tcp_connector.h \
 include/logger.h include/noncopyable.h include/encoder.h \
 include/msg_json.h include/tools.h include/config.h include/singleton.h \
 include/xml_parser.h include/protocol_system.h include/config.h
obj/main.o : src/main.cpp include/client.h include/tcp_connector.h \
 include/logger.h include/noncopyable.h include/encoder.h \
 include/msg_json.h include/tools.h include/config.h include/singleton.h \
 include/xml_parser.h include/protocol_system.h include/config.h
	g++ -c src/main.cpp -o obj/main.o -Iinclude -lboost_system -lboost_thread -ljsoncpp -ltinyxml
