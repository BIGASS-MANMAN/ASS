# -*- coding: utf-8 -*-
import sys
from xml.etree.ElementTree import parse

Ass_name = sys.argv[1]
Student = sys.argv[2]

root = parse("/usr/local/Auto_Scoring_System/Assignment/"+Ass_name+"/"+Student+"/Result/Death_test.xml")
output = open("/usr/local/Auto_Scoring_System/info/"+Ass_name+"/"+Ass_name+"_Death_Function.txt", 'w')
output2 = open("/usr/local/Auto_Scoring_System/Assignment/"+Ass_name+"/"+Student+"/Result/Report.txt", 'w')

########################################################################
fscore = open("/usr/local/Auto_Scoring_System/info/"+Ass_name+"/"+Ass_name+"_info.txt", 'r')

temp_list = fscore.readlines()

score_list = []

result_score_list = []
temp_score_list = []
temp_string = ""

find = False

for i in range(0, len(temp_list)):
    if temp_list[i] == "Function	=	\n":
        find = True
        continue
    if find:
        score_list.append(temp_list[i])

braceStart = False

for i in range(0, len(score_list)):
    for j in range(0, len(score_list[i])):
        if score_list[i][j] == '{':
            braceStart = True
        elif score_list[i][j] == '}':
            braceStart = False
            temp_score_list.append(temp_string)
            temp_string = ""
        elif braceStart:
            temp_string = temp_string + score_list[i][j]
    result_score_list.append(temp_score_list)
    temp_score_list = []

def GetScore(suite, case):
    for i in range(0, len(result_score_list)):
        for j in range(0, len(result_score_list[i])):
            if len(result_score_list[i]) == 0: continue
            if suite == result_score_list[i][0] and case == result_score_list[i][6]:
                return result_score_list[i][8]
    return 0
for testsuites in root.getiterator():
    for testsuite in testsuites:
        for testcase in testsuite:
            if testcase.keys()[0] == 'message': continue # only for test case
            if len(testcase.getchildren()) == 0: # There is no "failed to die"
                a = testcase.items()[2][1].split('_')
                print a[0] + "\t" + a[3] + "failed to die"
                s = a[0] + "\t" + a[3] + "\t" + "failed to die" + "\n"
                output.write(s)
                output2.write(s)
                continue
            else:
                if testcase.getchildren()[0].items()[0][1].find('failed to die') != -1:
                    continue # failed to die
                elif testcase.getchildren()[0].items()[0][1].find('infinite loop') != -1:
                    b = testcase.items()[2][1].split('_')
                    print b[0] + "\t" + b[3] + "\t" + "infinite loop" + "\t" + GetScore(b[0], b[3])
                    s = b[0] + "\t" + b[3] + "\t" + "infinite loop" + "\t" + GetScore(b[0], b[3]) + "\n"
                    output.write(s)
                    output2.write(s)
                    continue
                elif testcase.getchildren()[0].items()[0][1].find('segmentation fault') != -1:
					b = testcase.items()[2][1].split('_')
					print b[0] + "\t" + b[3] + "\t" + "segmentation fault" + "\t" + GetScore(b[0], b[3])
					s = b[0] + "\t" + b[3] + "\t" + "segmentation fault" + "\t" + GetScore(b[0], b[3]) + "\n"
					output.write(s)
					output2.write(s)
					continue
                else:
                    print "Unexpected case"

fscore.close()
output.close()
output2.close()
