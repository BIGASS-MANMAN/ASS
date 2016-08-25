GTEST_DIR = /usr/local/Auto_Scoring_System/gtest-1.7.0
USER_DIR = ./
CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread
TESTS = GraphTest
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
		$(GTEST_DIR)/include/gtest/internal/*.h
all : $(TESTS)
clean :
		rm -f $(TESTS) gtest_main.a *.o
LeftistTree.o : $(USER_DIR)/LeftistTree.cc $(USER_DIR)/LeftistTree.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/LeftistTree.cc
Manager.o : $(USER_DIR)/Manager.cc $(USER_DIR)/Manager.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/Manager.cc
dijkstra.o : $(USER_DIR)/dijkstra.cc $(USER_DIR)/dijkstra.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/dijkstra.cc
edge.o : $(USER_DIR)/edge.cc $(USER_DIR)/edge.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/edge.cc
graph.o : $(USER_DIR)/graph.cc $(USER_DIR)/graph.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/graph.cc
node.o : $(USER_DIR)/node.cc $(USER_DIR)/node.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/node.cc
request.o : $(USER_DIR)/request.cc $(USER_DIR)/request.h $(GTEST_HEADERS)
	$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/request.cc
GraphTest.o : $(USER_DIR)/GraphTest.cc $(USER_DIR)/LeftistTree.h $(USER_DIR)/Manager.h $(USER_DIR)/dijkstra.h $(USER_DIR)/edge.h $(USER_DIR)/graph.h $(USER_DIR)/node.h $(USER_DIR)/request.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/GraphTest.cc
GraphTest : LeftistTree.o Manager.o dijkstra.o edge.o graph.o node.o request.o GraphTest.o ../../../gtest-1.7.0/gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@