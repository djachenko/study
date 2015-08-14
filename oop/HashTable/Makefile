GTEST_DIR = gtest
USER_DIR = .

CPPFLAGS += -I$(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra

PROJECT = HashTable
TESTS = $(PROJECT)Tests

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h

all : $(TESTS)

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^
	
$(PROJECT).o : $(USER_DIR)/$(PROJECT).h $(USER_DIR)/$(PROJECT).cpp
	$(CXX) $(CXXFLAGS) -c $(USER_DIR)/$(PROJECT).cpp 

$(TESTS).o : $(USER_DIR)/$(TESTS).cpp $(USER_DIR)/$(PROJECT).h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/$(TESTS).cpp

$(TESTS) : $(PROJECT).o $(TESTS).o gtest_main.a 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -lpthread -o $@

clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o
