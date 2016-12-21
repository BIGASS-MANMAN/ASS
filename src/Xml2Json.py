# -*- coding: utf-8 -*-
import json
import sys

Ass_name = sys.argv[1]
Student = sys.argv[2]


_input_report = open("/usr/local/Auto_Scoring_System/Assignment/" + Ass_name + "/" + Student+ "/Result/Report.txt", 'r')
output = open('/usr/local/Auto_Scoring_System/Assignment/' + Ass_name + "/" + Student+ '/Result/Result.json', 'w')

def isSame(data1, data2):
    if len(data1) != len(data2): return False
    for i in range(0, len(data1)):
        if data1[i] != data2[i]: return False;
    return True

# make data form
data = _input_report.read().strip().split('\n')

for i in range(0, len(data)):
    data[i] = data[i].split('\t')

# redundancy check
for i in range(0, len(data)):
    if data[i] == '':
        continue
    for j in range(i+1, len(data)):
        if isSame(data[i], data[j]):
            data[j] = ''

# ********** json file form **********
# {
#     {
#         "Testsuite":"data[i][0]"
#         "Testcase":"data[i][1]"
#         "Message":"data[i][2]"
#         "Score":""data[i][3]"
#     },
#     {
#         "Testsuite":"data[i+1][0]"
#         "Testcase":"data[i+1][1]"
#         "Message":"data[i+1][2]"
#         "Score":"data[i+1][3]"
#     }
# }

'''
isFirst = True # for comma

output.write('{\n')
for i in range(0, len(data)):
    if data[i] == '':
        continue
    else:
        if isFirst:
            isFirst = False
        else:
            output.write(',\n')
        output.write("\t{\n")
        a = '\t\t"Testsuite":' + '"' + data[i][0] + '"' + '\n'
        b = '\t\t"Testcase":' + '"' + data[i][1] + '"' + '\n'
        c = '\t\t"Message":' + '"' + data[i][2] + '"' + '\n'
        d = '\t\t"Score":' + '"' + data[i][3] + '"' + '\n'
        output.write(a)
        output.write(b)
        output.write(c)
        output.write(d)
        output.write("\t}")
        t = data[i][0] + "\t" + data[i][1] + "\t" + data[i][2] + "\t" + data[i][3] + "\n"
output.write('\n}')
'''

result = {}
result['assert'] = []

for i in range(0, len(data)):
    e = result['assert']
    e += {
        'Testsuite': data[i][0],
        'Testcase': data[i][1],
        'Message': data[i][2],
        'Score': data[i][3]
        },

print(result)

with output as f:
    json.dump(result, f, ensure_ascii=False, indent=4)

_input_report.close()
output.close()

