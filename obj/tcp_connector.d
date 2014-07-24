obj/tcp_connector.d : src/tcp_connector.cpp include/tcp_connector.h \
 include/logger.h
obj/tcp_connector.o : src/tcp_connector.cpp include/tcp_connector.h \
 include/logger.h
	g++ -c src/tcp_connector.cpp -o obj/tcp_connector.o -Iinclude -lboost_system -lboost_thread -ljsoncpp -ltinyxml
