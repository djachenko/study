GTEST_DIR = gtest
USER_DIR = .

CPPFLAGS += -I$(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra

CELL_TESTS = CellTests
FIELD_TESTS = FieldTests
LIFE = Life

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h

all : $(LIFE)
tests : $(CELL_TESTS) $(FIELD_TESTS)

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)



gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^



Cell.o : $(USER_DIR)/Cell.cpp $(USER_DIR)/Cell.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Cell.cpp

CellTests.o : $(USER_DIR)/CellTests.cpp $(USER_DIR)/Cell.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/CellTests.cpp

CellTests : Cell.o CellTests.o gtest_main.a 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -lpthread -o $@



Field.o : $(USER_DIR)/Field.cpp $(USER_DIR)/Field.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Field.cpp

FieldTests.o : $(USER_DIR)/FieldTests.cpp $(USER_DIR)/Field.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/FieldTests.cpp

FieldTests : Field.o Cell.o FieldTests.o gtest_main.a 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -lpthread -o $@



Game.o : $(USER_DIR)/Game.cpp $(USER_DIR)/Game.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Game.cpp



Life.o : $(USER_DIR)/Life.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Life.cpp

Life : Life.o Game.o Field.o Cell.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -lpthread -o $@


clean :
	rm -f $(CELL_TESTS) $(FIELD_TESTS) Life gtest.a gtest_main.a *.o
