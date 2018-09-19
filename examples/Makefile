SRC_FILES := $(wildcard ./*.cpp)
BIN_FILES := $(patsubst ./%.cpp,./%,$(SRC_FILES))

CXXFLAGS := -I../include -MMD -std=c++17
LDFLAGS := -lstdc++fs

all: $(BIN_FILES)

$(BIN_FILES):
	$(CXX) $(CXXFLAGS) -o $@ $@.cpp $(LDFLAGS)

-include $(SRC_FILES:.cpp=.d)
