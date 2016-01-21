CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -Wpedantic -I./include/
LFLAGS = -lboost_system -lpthread

CMD   = $(CXX) $(CXXFLAGS) $(LFLAGS) $^ -o $@
CMD_D = $(CMD)_d

CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

opt: CXXFLAGS += -O3
opt: all

all: main

debug: CXXFLAGS += -DDEBUG -ggdb3
debug: all

main: $(OBJ_FILES)
	$(CMD)

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o
	rm -f main

.PHONY: all clean
