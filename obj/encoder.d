obj/encoder.d : src/encoder.cpp include/encoder.h include/msg_json.h \
 include/tools.h
obj/encoder.o : src/encoder.cpp include/encoder.h include/msg_json.h \
 include/tools.h
	g++ -c src/encoder.cpp -o obj/encoder.o -Iinclude -lboost_system -lboost_thread -ljsoncpp -ltinyxml
