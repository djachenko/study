SRC = equations.cpp

BIN = $(SRC:.cpp=.out)

all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm *.out
