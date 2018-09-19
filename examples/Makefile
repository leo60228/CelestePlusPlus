SRC_FILES := $(wildcard ./*.cpp)
BIN_FILES := $(patsubst ./%.cpp,./%,$(SRC_FILES))

CXXFLAGS := -I../include -MMD

all: $(BIN_FILES)

$(BIN_FILES):
	g++ $(CXXFLAGS) -o $@ $@.cpp

-include $(SRC_FILES:.cpp=.d)
