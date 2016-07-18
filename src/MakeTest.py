#Open assignmnet information file
import sys

Ass_name = sys.argv[1]
Student = sys.argv[2]

rf = open("/usr/local/Auto_Scoring_System/info/"+Ass_name+"/"+Ass_name+"_info.txt")
lines = rf.readlines()
lines = list(map(lambda s: s.strip(), lines))

TestMatrix = [[0 for col in range(10)] for row in range(30)]

i = 0
for line in lines:
    s = line.split('\t')
    TestMatrix[i] = s
    if 'Title' in TestMatrix[i]:
	Title = TestMatrix[i][2]
    elif 'Test' in TestMatrix[i]:
	Test = TestMatrix[i][2]
    elif 'Header' in TestMatrix[i]:
	Header = TestMatrix[i][2]
    elif 'Source' in TestMatrix[i]:
	Source = TestMatrix[i][2]
    elif '-Requirements' in TestMatrix[i]:
	req = TestMatrix[i][2]
	end = req.find('>')
	req = req[1:end]
	req = req.split(':')
	var_type = req[0]
	var_name = req[1]
	var_size = req[2]
	var_input = req[3]	

    elif 'Function' in TestMatrix[i]:
	k = i+1
    else:
	pass

    i = i + 1


Function = []
for j in range(0,len(lines)-k):
    Parameter = TestMatrix[k][2].translate(None, "<>").split('},{')
    Output = Parameter[0].translate(None,"{}")
    Input = Parameter[1].translate(None,"{}")
    Function.append({'Category' : 'Fucntion', 'Name' : TestMatrix[k][0], 'Output' : Output, 'Input' : Input})

    k = k+1

print(Title)
print(Test)
print(Header)
print(var_type)
print(var_name)
print(var_size)
print(var_input)
for i in range(0, len(Function)):
    print(Function[i])

wf = open("/usr/local/Auto_Scoring_System/info/"+Ass_name+"/"+Test+".cc",'w')
wf.write("#include \"/usr/local/Auto_Scoring_System/Assignment/"+Ass_name+"/"+Student+"/"+Header+"\"\n")
wf.write("#include \"gtest/gtest.h\"\n\n")
wf.write("class "+Test+" : public testing::Test{\n\tprotected:\n\t\tvirtual void SetUp(){}\n\t\tvirtual void TearDown(){}\n};\n")
wf.write(var_type +" " +  var_name + "[" + var_size + "] = " + var_input + ";" +"\n\n")

for i in range(0, len(Function)):
    wf.write("TEST_F(" +Test+","+Function[i]['Name']+"){EXPECT_EQ("+Function[i]['Output']+","+Function[i]['Name']+"("+Function[i]['Input']+'));}\n')


rf.close()
wf.close()
