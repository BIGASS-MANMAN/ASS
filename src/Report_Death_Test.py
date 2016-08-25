# -*- coding: utf-8 -*-
from xml.etree.ElementTree import parse

root = parse("/usr/local/Auto_Scoring_System/Assignment/ASS1/2012722060_김영재/Death_test.xml")
output = open("/usr/local/Auto_Scoring_System/info/ASS1/ASS1_Death_Function.txt", 'w')

switched = False

i = 0

for testsuites in root.getiterator():
    for testsuite in testsuites:
        for testcase in testsuite:
            if testcase.keys()[0] == 'message': continue # only for test case
            if len(testcase.getchildren()) == 0: # There is no "failed to die"
                a = testcase.items()[2][1].split('_')
                print a[0] + "\t" + a[3] + "failed to die"
                s = a[0] + "\t" + a[3] + "\t" + "failed to die" + "\n"
                output.write(s)
                continue
            else:
                if testcase.getchildren()[0].items()[0][1].find('failed to die') != -1:
                    continue # failed to die
                elif testcase.getchildren()[0].items()[0][1].find('infinite loop') != -1:
                    b = testcase.items()[2][1].split('_')
                    print b[0] + "\t" + b[3] + "\t" + "infinite loop"
                    s = b[0] + "\t" + b[3] + "\t" + "infinite loop" + "\n"
                    output.write(s)
                    continue
                else:
                    print "Unexpected case"
output.close()

