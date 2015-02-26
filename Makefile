SRC := src
INC := include
BIN := bin
OBJ := obj

srcs = $(wildcard $(SRC)/*.cpp)
objs = $(patsubst %.cpp, $(OBJ)/%.o, $(notdir $(srcs)))
deps = $(objs:%.o=%.d)

TARGET := test

CC := g++
CCFLAGS := -I$(INC)
LDFLAGS := -lboost_system -lboost_thread -ljsoncpp -ltinyxml 
CCFLAGS += $(LDFLAGS)

vpath %.h $(INC)
vpath %.cpp $(SRC)

all : dep $(BIN)/$(TARGET)

dep :
$(OBJ)/%.d : $(SRC)/%.cpp
	@set -e;
	@rm -f $@;
	@$(CC) -MM $< $(CCFLAGS) > $@.temp;
	@sed 's,\($*\)\.o[ :]*,$(OBJ)/\1.d : ,g' < $@.temp >> $@;
	@sed 's,\($*\)\.o[ :]*,$(OBJ)/\1.o : ,g' < $@.temp >> $@;
	@echo -e "\t"$(CC) -c $< -g -o $(subst .d,.o,$@) $(CCFLAGS) >> $@;
	@rm -f $@.temp;

$(BIN)/$(TARGET) : $(objs)
	$(CC) -g -o $(BIN)/$(TARGET) $^ $(CCFLAGS);
	@echo Target: ./$(BIN)/$(TARGET) Done

include $(deps)

.PHONY : info
info :
	@echo $(srcs);
	@echo $(objs);
	@echo $(deps);
	@echo $(CCFLAGS);

.PHONY : clean
clean :
	-rm -rf $(OBJ)/* $(BIN)/$(TARGET);

	
