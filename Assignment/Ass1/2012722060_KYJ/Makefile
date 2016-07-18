GTEST_DIR = /usr/local/Auto_Scoring_System/gtest-1.7.0

USER_DIR = ./

CPPFLAGS += -isystem $(GTEST_DIR)/include

CXXFLAGS += -g -Wall -Wextra -pthread

TESTS = unittest4

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

all : $(TESTS)

clean :
	rm -f $(TESTS) gtest_main.a *.o

4.o : $(USER_DIR)/4.cc $(USER_DIR)/4.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/4.cc

UnitTest4.o : /usr/local/Auto_Scoring_System/info/Ass1/UnitTest4.cc $(USER_DIR)/4.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c /usr/local/Auto_Scoring_System/info/Ass1/UnitTest4.cc

unittest4 : 4.o UnitTest4.o ../../../gtest-1.7.0/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
