a_file = 'com1.txt'
s_file = 'com2.txt'
score_file = 'score.txt'

assistant = open(a_file, 'r')
student = open(s_file, 'r')
score = open(score_file, 'r')

a_data_t = assistant.read()
s_data_t = student.read()

a_data = a_data_t.split('\n')
s_data = s_data_t.split('\n')

score_data = score.readlines()
score_list = []

total_score = 0
student_score = 0
unexpected_case_score = 5

def isSpecial(word):
    special = "=-*!@#$%^&()+/."
    for i in range(0, len(special)):
        if word == special[i]:
            return True
    return False
    
def isSTART(string):
    if not len(string) > 0:
        return False
    else:
        if isSpecial(string[0]):
            for i in range(0, len(string)):
                if not isSpecial(string[i]):
                    for j in range(i+1, len(string)):
                        if isSpecial(string[j]):
                            return string[i:j].strip()
        else:
            return False

def isEND(string):
    if not len(string) > 0:
        return False
    else:
        for i in range(0, len(string)):
            if not isSpecial(string[i]):
                return False
        return True

def isSame(list1, list2):
    if len(list1) != len(list2): # length is equal
        return False
    else:
        for i in range(0, len(list1)): # all elements are equal
            if len(list1[i]) != len(list2[i]):
                return False
            element1 = list1[i].strip()
            element1 = element1.split(' ')
            element2 = list2[i].strip()
            element2 = element2.split(' ')
            for j in range(0, len(element1)):
                if element1[j] != element2[j]:
                    return False
    return True

def isCorrect(data): # correct data form
    correct = True
    for i in range(0, len(data)):
        if data[i].find('START') != -1:
            if correct:
                correct = False
                continue
            else:
                return False
        if data[i].find('END') != -1:
            if not correct:
                correct = True
                continue
            else:
                return False
    return correct

def getScore(case_name):
    for i in range(0, len(score_data)):
        if score_data[i].split(' ')[0] == case_name:
            return int(score_data[i].split(' ')[1])
    return 0 # 0 points per unexpected case of the student

# get Total Score
for i in range(0, len(score_data)):
    temp = score_data[i].strip()
    score_list.append(temp.split(' '))
    total_score = total_score + int(score_list[i][1])

student_score = total_score

a_temp = []
s_temp = []

a_i = 0
s_i = 0

isFound = False # not correct output is detected
isDetected = False
isUnexpected = False

casename = ""

if not isCorrect(a_data) or not isCorrect(s_data):
    print "Error: Not correct form"
    exit()

print ""
print "================================ Result ================================"
while a_i != len(a_data):
    if a_data[a_i] == '': # new line is ignored
        a_i = a_i + 1
        continue
    if isSTART(a_data[a_i]):
        casename = isSTART(a_data[a_i])
        a_i = a_i + 1
        a_temp = []
        while not isEND(a_data[a_i]):
            a_temp.append(a_data[a_i].upper())
            a_i = a_i + 1
    else:
        a_i = a_i + 1
        continue
    for i in range(0, len(s_data)):
        if isSTART(s_data[i]) == casename:
            isDetected = True
            s_data[i] = ''
            s_i = i + 1
            s_temp = []
            while True:
                if isEND(s_data[s_i]):
                    s_data[s_i] = ''
                    break
                s_temp.append(s_data[s_i].upper())
                s_data[s_i] = ''
                s_i = s_i + 1
            if not isSame(a_temp, s_temp):
                if not isFound: isFound = True
                print "Not Correct: " + casename + " ( -" + str(getScore(casename)) + " ) "
                student_score = student_score - getScore(casename)
                break
            else:
                break
    if not isDetected:
        if not isFound: isFound = True
        print "No Case: " + casename
        isDetected = False
    isDetected = False

if not isFound: print "Not found"

for i in range(0, len(s_data)):
    if s_data[i] == '': continue
    if isSTART(s_data[i]):
        if not isUnexpected:
            isUnexpected = True
            print "------------------------------------------------------------------------"
        print "Unexpected Case: " + isSTART(s_data[i]) + " ( -" + str(unexpected_case_score) + " ) "
        student_score = student_score - unexpected_case_score

print "------------------------------------------------------------------------"
print " Score: " + str(student_score) + " / " + str(total_score) + " (student_score/total_score)"
print "========================================================================"
print ""

assistant.close()
student.close()
score.close()
