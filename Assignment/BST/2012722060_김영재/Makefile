GTEST_DIR = /usr/local/Auto_Scoring_System/gtest-1.7.0

USER_DIR = ./

CPPFLAGS += -isystem $(GTEST_DIR)/include

CXXFLAGS += -g -Wall -Wextra -pthread

TESTS = BST_unittest

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

all : $(TESTS)

clean :
	rm -f $(TESTS) gtest_main.a *.o
Node.o : $(USER_DIR)/Node.cc $(USER_DIR)Node.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/Node.cc

BST.o : $(USER_DIR)/BST.cc $(USER_DIR)/BST.h $(USER_DIR)/Node.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/BST.cc

BST_unittest.o : $(USER_DIR)/BST_unittest.cc $(USER_DIR)/BST.h $(USER_DIR)/Node.h  $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/BST_unittest.cc

BST_unittest : Node.o BST.o BST_unittest.o ../../../gtest-1.7.0/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
