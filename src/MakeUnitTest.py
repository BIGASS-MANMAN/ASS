#Open assignmnet information file
import sys

#Decide current function didn't occur error(segmentation fault, infinite loop...)
def IsFail(Func, FL):
    for i in range(0, len(FL)):
	if Func['Fname'] == FL[i][0] and Func['InputGRP'] == FL[i][1]:
	   return 1
	else:
	   continue
    return 0


Ass_name = sys.argv[1]
Student = sys.argv[2]


print("Make Unittest Code......\n")
rf = open("/usr/local/Auto_Scoring_System/info/"+Ass_name+"/"+Ass_name+"_info.txt")
fl = open("/usr/local/Auto_Scoring_System/Assignment/"+Ass_name+"/"+Student+"/Result/Report.txt")

#Call up Failed function list from "ASS_name"_Death_Function.txt
Fails = fl.readlines()
Fails = list(map(lambda s: s.strip('\n'), Fails))

#Fail[0] : Function name    /	Fail[1] : Function test input group
FailList = []
for Fail in Fails:
    f = Fail.split('\t')
    FailList.append(f)


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

SetUp = []
for j in range(i,len(lines)):
    if 'Function' in lines[j]:
	j = j + 1
	break	   
    SetUp.append(lines[j])

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

    Output = temp[4].split(',')
    TestEx = temp[5]
    InputGRP = temp[6].translate(None,"}")
    Function.append({'Fname' : Fname, 'Objname' : Objname, 'Helper' : Helper, 'Output' : Output, 'TestEx' : TestEx, 'Input' : Input[InputRow], 'InputGRP' : InputGRP})
    InputRow = InputRow + 1



wf = open("/usr/local/Auto_Scoring_System/Assignment/"+Ass_name+"/"+Student+"/"+Test+".cc",'w')
for i in range(0, len(Class)):
    wf.write("#include \"/usr/local/Auto_Scoring_System/Assignment/"+Ass_name+"/"+Student+"/"+Class[i]+".h\"\n")
wf.write("#include \"../../src/signal.h\"\n");
wf.write("#include \"gtest/gtest.h\"\n\n")
for i in range(0, len(SetUp)):
   wf.write(SetUp[i]+"\n")

flag = 0
FunctionNum = 0

FFlag = 0
for i in range(0, len(Function)):
    if len(Function[i]) == 0:
	if FFlag == 1:
	    wf.write("}\n")
            FFlag = 0
	flag = 0
	continue

    if IsFail(Function[i],FailList) == 1:
	continue

    FFlag = 1
    if flag == 0:
	wf.write("TEST_F("+Test+","+Function[i]['Fname']+"_"+Function[i]['InputGRP']+"){\n")

    flag = 1

    if Function[i]['TestEx'] == 'X':
	wf.write("\t"+Function[i]['Objname']+"->"+Function[i]['Fname']+"(")
	for j in range(0, len(Function[i]['Input'])):
	    wf.write(Function[i]['Input'][j].split(',')[1])
	    if j == len(Function[i]['Input'])-1:
		wf.write(");\n")
		break
	    wf.write(",")

    else:
	if Function[i]['Helper'] == 'X':
	    if Function[i]['Output'][0] == number:
		wf.write("\tEXPECT_EQ("+Fucntion[i]['Objname']+"->"+Function[i]['Fname']+"(")
	    else:
		wf.write("\tEXPECT_STREQ("+Fucntion[i]['Objname']+"->"+Function[i]['Fname']+"(")

	else:
	    if Function[i]['Output'][0] == "number":
		wf.write("\tEXPECT_EQ("+Function[i]['Helper']+"(")
	    else:
		wf.write("\tEXPECT_STREQ("+Function[i]['Helper']+"(")

	for j in range(0, len(Function[i]['Input'])):
	    wf.write(Function[i]['Input'][j].split(',')[1])
	    if j == len(Function[i]['Input'])-1:
	        wf.write("),")
	        break
	    wf.write(",")
	wf.write(Function[i]['Output'][1]+");\n")
if FFlag == 1:
    wf.write("}")


rf.close()
wf.close()
