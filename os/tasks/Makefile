SRC = 22.cpp

BIN = $(SRC:.cpp=.out)

CXX = g++
CXXFLAGS += -pthreads
LDFLAGS += -lrt

all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm *.out
