# -*- coding: utf-8 -*-
import sys
import json
from xml.etree.ElementTree import parse

Ass_name = sys.argv[1]
Student = sys.argv[2]

root = parse("/usr/local/Auto_Scoring_System/Assignment/"+Ass_name+"/"+Student+"/Result/Unit_Result.xml")
output = open("/usr/local/Auto_Scoring_System/Assignment/"+Ass_name+"/"+Student+"/Result/Report.txt", 'a')

###############################################
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
            if testcase.findtext("failure"):
                for fail in testcase:
                    infolist = testcase.items()[2][1].split('_')
                    infolist.append("invalid value")
                    infolist.append(GetScore(infolist[0], infolist[1]))
                    s = str(infolist[0]) + "\t" + str(infolist[1]) + "\t" + str(infolist[2]) + "\t" + str(infolist[3]+"\n")
                    output.write(s)



output.close()
fscore.close()
