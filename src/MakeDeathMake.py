import sys

Ass_name = sys.argv[1]
Student = sys.argv[2]

print("Make Death test Makefile......\n")
#Open assignment information file
#If use database, replace code form
rf = open("/usr/local/Auto_Scoring_System/info/"+Ass_name+"/"+Ass_name+"_info.txt")
lines = rf.readlines()
lines = list(map(lambda s: s.strip('\n'), lines))

Class = []

i = 0
for line in lines:
    s = line.split('\t')
    if 'Title' in line:
	Title = s[2]
    elif 'Test' in line:
	Test = s[2]
    elif 'Class' in line:
	for ClassNum in range(2, len(s)):
	    Class.append(s[ClassNum])
	break

#Make Death test C++ file
wf = open("/usr/local/Auto_Scoring_System/Assignment/"+Ass_name+"/"+Student+"/Makefile",'w')

wf.write("GTEST_DIR = /usr/local/Auto_Scoring_System/gtest-1.7.0\nUSER_DIR = ./\nSIG_DIR = ../../../src\nCPPFLAGS += -isystem $(GTEST_DIR)/include\nCXXFLAGS += -g -Wall -Wextra -pthread\nTESTS = Death_"+Test+"\nGTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \\\n\t\t$(GTEST_DIR)/include/gtest/internal/*.h\nall : $(TESTS)\nclean :\n\t\trm -f $(TESTS) gtest_main.a *.o \n")

for i in range(0, len(Class)):
    wf.write(Class[i]+".o : $(USER_DIR)/"+Class[i]+".cc $(USER_DIR)/"+Class[i]+".h $(GTEST_HEADERS)\n\t$(CXX) $(CPPFALGS) $(CXXFLAGS) -c $(USER_DIR)/"+Class[i]+".cc\n")

wf.write("Death_"+Test+".o : "+"$(USER_DIR)/Death_"+Test+".cc ")
for i in range(0, len(Class)):
    wf.write("$(USER_DIR)/"+Class[i]+".h ")
wf.write("$(GTEST_HEADERS)\n\t$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Death_"+Test+".cc\n")
wf.write("Death_"+Test+" : ")
for i in range(0, len(Class)):
    wf.write(Class[i]+".o ")
wf.write("Death_"+Test+".o ../../../gtest-1.7.0/gtest_main.a\n\t$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@ $(SIG_DIR)/signal.h $(SIG_DIR)/signal.cc")

rf.close()
wf.close()
