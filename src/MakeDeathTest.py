#Open assignmnet information file
import sys

Ass_name = sys.argv[1]
Student = sys.argv[2]

print("Make Death Test Code......\n")
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
    elif 'SetUp' in line:
	i = i + 1
	break

    i = i + 1

#Copy SetUp() code to List
SetUp = []
for j in range(i,len(lines)):
    if 'Function' in lines[j]:
	j = j + 1
	break	   
    SetUp.append(lines[j])

#Copy Function tested by unittest to list
InputRow = 0
Function = []
Input = [[0 for col in range(0)] for row in range(100)]
for k in range(j,len(lines)):
    temp = lines[k].translate(None, "[]").split('},{')
    if len(temp) == 1:
	Function.append("")
	continue
    Fname = temp[0].translate(None,"{")
    Objname = temp[1]
    Helper = temp[2]
    Input_temp = temp[3].split('>,<')
    for InputCol in range(0,len(Input_temp)):
	Input[InputRow].append(Input_temp[InputCol].translate(None,"<>"))

    Output = temp[4]
    TestEx = temp[5]
    InputGRP = temp[6].translate(None,"}")
#Show function's key values
    Function.append({'Fname' : Fname, 'Objname' : Objname, 'Helper' : Helper, 'Output' : Output, 'TestEx' : TestEx, 'Input' : Input[InputRow], 'InputGRP' : InputGRP})
    print(Fname+" "+Objname+" "+Helper+" "+Output+" "+TestEx+" "+" "+InputGRP)
    InputRow = InputRow + 1


wf = open("/usr/local/Auto_Scoring_System/Assignment/"+Ass_name+"/"+Student+"/Death_"+Test+".cc",'w')
for i in range(0, len(Class)):
    wf.write("#include \"/usr/local/Auto_Scoring_System/Assignment/"+Ass_name+"/"+Student+"/"+Class[i]+".h\"\n")
wf.write("#include \"../../src/signal.h\"\n");

wf.write("#include \"gtest/gtest.h\"\n\n")
for i in range(0, len(SetUp)):
   wf.write(SetUp[i]+"\n")

#If general termination, this test is failed (Because Not death, failed to die)
#If occur segmentation fault, comapare error MSG(segmentation fault)
#If error MSG matched with cerr MSG, test is succeed(Actually fail)
#If cerr MSG is infinite loop, this test fall in infinite loop. Then test is terminated by SIGALRM

FunctionNum = 0
GRPTEMP = 0
INSERTTEMP = 0
for i in range(0, len(Function)):
    if len(Function[i]) == 0:
	continue
	   
    if Function[i]['Helper'] == 'X':
	if GRPTEMP != Function[i]['InputGRP'] or INSERTTEMP != Function[i]['Fname']:
	    GRPTEMP = Function[i]['InputGRP']
	    INSERTTEMP = Function[i]['Fname']
	    FunctionNum = 0
	wf.write("TEST_F("+Test+","+Function[i]['Fname']+"_Death_test_"+Function[i]['InputGRP']+"_%d)\n{\n"%FunctionNum)
	wf.write("\tASSERT_DEATH("+Function[i]['Objname']+"->"+Function[i]['Fname']+ "(")
	for j in range(0, len(Function[i]['Input'])):
	    wf.write(Function[i]['Input'][j].split(',')[1])
	    if j == len(Function[i]['Input'])-1:
		break
	    wf.write(",")
	wf.write("),\"segmentation fault\");\n}\n")
	FunctionNum = FunctionNum + 1


rf.close()
wf.close()
