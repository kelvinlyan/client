obj/client.d : src/client.cpp include/client.h include/tcp_connector.h \
 include/logger.h include/noncopyable.h include/encoder.h \
 include/msg_json.h include/tools.h
obj/client.o : src/client.cpp include/client.h include/tcp_connector.h \
 include/logger.h include/noncopyable.h include/encoder.h \
 include/msg_json.h include/tools.h
	g++ -c src/client.cpp -g -o obj/client.o -Iinclude -lboost_system -lboost_thread -ljsoncpp -ltinyxml
