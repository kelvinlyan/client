obj/tcp_connector.d : src/tcp_connector.cpp include/tcp_connector.h \
 include/logger.h include/color.hpp
obj/tcp_connector.o : src/tcp_connector.cpp include/tcp_connector.h \
 include/logger.h include/color.hpp
	g++ -c src/tcp_connector.cpp -g -o obj/tcp_connector.o -Iinclude -lboost_system -lboost_thread -ljsoncpp -ltinyxml
