obj/xml_parser.d : src/xml_parser.cpp include/xml_parser.h
obj/xml_parser.o : src/xml_parser.cpp include/xml_parser.h
	g++ -c src/xml_parser.cpp -o obj/xml_parser.o -Iinclude -lboost_system -lboost_thread -ljsoncpp -ltinyxml
