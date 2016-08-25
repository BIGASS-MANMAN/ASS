GTEST_DIR = /usr/local/Auto_Scoring_System/gtest-1.7.0
USER_DIR = ./
CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread
TESTS = BSTTest
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
		$(GTEST_DIR)/include/gtest/internal/*.h
all : $(TESTS)
clean :
		rm -f $(TESTS) gtest_main.a *.o
Node.o : $(USER_DIR)/Node.cc $(USER_DIR)/Node.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/Node.cc
BST.o : $(USER_DIR)/BST.cc $(USER_DIR)/BST.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/BST.cc
BSTTest.o : $(USER_DIR)/BSTTest.cc $(USER_DIR)/Node.h $(USER_DIR)/BST.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/BSTTest.cc
BSTTest : Node.o BST.o BSTTest.o ../../../gtest-1.7.0/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@