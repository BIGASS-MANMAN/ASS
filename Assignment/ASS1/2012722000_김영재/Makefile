GTEST_DIR = /usr/local/Auto_Scoring_System/gtest-1.7.0
USER_DIR = ./
SIG_DIR = ../../../src
CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread
TESTS = ASS1Test
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
		$(GTEST_DIR)/include/gtest/internal/*.h
all : $(TESTS)
clean :
		rm -f $(TESTS) gtest_main.a *.o
ALP_BST.o : $(USER_DIR)/ALP_BST.cc $(USER_DIR)/ALP_BST.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/ALP_BST.cc
Alphabet.o : $(USER_DIR)/Alphabet.cc $(USER_DIR)/Alphabet.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/Alphabet.cc
CircularQueue.o : $(USER_DIR)/CircularQueue.cc $(USER_DIR)/CircularQueue.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/CircularQueue.cc
Manager.o : $(USER_DIR)/Manager.cc $(USER_DIR)/Manager.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/Manager.cc
Queue.o : $(USER_DIR)/Queue.cc $(USER_DIR)/Queue.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/Queue.cc
WORD_BST.o : $(USER_DIR)/WORD_BST.cc $(USER_DIR)/WORD_BST.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/WORD_BST.cc
Word.o : $(USER_DIR)/Word.cc $(USER_DIR)/Word.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/Word.cc
ASS1Test.o : $(USER_DIR)/ASS1Test.cc $(USER_DIR)/ALP_BST.h $(USER_DIR)/Alphabet.h $(USER_DIR)/CircularQueue.h $(USER_DIR)/Manager.h $(USER_DIR)/Queue.h $(USER_DIR)/WORD_BST.h $(USER_DIR)/Word.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/ASS1Test.cc
ASS1Test : ALP_BST.o Alphabet.o CircularQueue.o Manager.o Queue.o WORD_BST.o Word.o ASS1Test.o ../../../gtest-1.7.0/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@ $(SIG_DIR)/signal.h $(SIG_DIR)/signal.cc