obj/tools.d : src/tools.cpp include/tools.h
obj/tools.o : src/tools.cpp include/tools.h
	g++ -c src/tools.cpp -o obj/tools.o -Iinclude -lboost_system -lboost_thread -ljsoncpp -ltinyxml
