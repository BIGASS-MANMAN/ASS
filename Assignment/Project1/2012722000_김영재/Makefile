GTEST_DIR = /usr/local/Auto_Scoring_System/gtest-1.7.0
USER_DIR = ./
SIG_DIR = ../../../src
CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread
TESTS = Project1Test main
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
		$(GTEST_DIR)/include/gtest/internal/*.h
all : $(TESTS)
clean :
		rm -f $(TESTS) gtest_main.a *.o
AlphabetBST.o : $(USER_DIR)/AlphabetBST.cc $(USER_DIR)/AlphabetBST.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/AlphabetBST.cc
AlphabetNode.o : $(USER_DIR)/AlphabetNode.cc $(USER_DIR)/AlphabetNode.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/AlphabetNode.cc
CircularLinkedList.o : $(USER_DIR)/CircularLinkedList.cc $(USER_DIR)/CircularLinkedList.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/CircularLinkedList.cc
Manager.o : $(USER_DIR)/Manager.cc $(USER_DIR)/Manager.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/Manager.cc
Queue.o : $(USER_DIR)/Queue.cc $(USER_DIR)/Queue.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/Queue.cc
WordBST.o : $(USER_DIR)/WordBST.cc $(USER_DIR)/WordBST.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/WordBST.cc
WordNode.o : $(USER_DIR)/WordNode.cc $(USER_DIR)/WordNode.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/WordNode.cc
Project1Test.o : $(USER_DIR)/Project1Test.cc $(USER_DIR)/AlphabetBST.h $(USER_DIR)/AlphabetNode.h $(USER_DIR)/CircularLinkedList.h $(USER_DIR)/Manager.h $(USER_DIR)/Queue.h $(USER_DIR)/WordBST.h $(USER_DIR)/WordNode.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Project1Test.cc
Project1Test : AlphabetBST.o AlphabetNode.o CircularLinkedList.o Manager.o Queue.o WordBST.o WordNode.o Project1Test.o ../../../gtest-1.7.0/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@ $(SIG_DIR)/signal.h $(SIG_DIR)/signal.cc
main : AlphabetBST.o AlphabetNode.o CircularLinkedList.o Manager.o Queue.o WordBST.o WordNode.o main.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@ $(SIG_DIR)/signal.h $(SIG_DIR)/signal.cc
