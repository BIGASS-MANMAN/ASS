#!/bin/bash

ASS=$1
TEST=$2
STUDENT=$3

python /usr/local/Auto_Scoring_System/src/MakeDeathMake.py $ASS $STUDENT
python /usr/local/Auto_Scoring_System/src/MakeDeathTest.py $ASS $STUDENT
cd /usr/local/Auto_Scoring_System/Assignment/$ASS/$STUDENT
make
./Death_$TEST --gtest_output="xml:Death_test.xml"
python /usr/local/Auto_Scoring_System/src/Report_Death_Test.py
python /usr/local/Auto_Scoring_System/src/MakeMake.py $ASS $STUDENT
python /usr/local/Auto_Scoring_System/src/MakeUnitTest.py $ASS $STUDENT
make
./$TEST --gtest_output="xml:Unit_Result.xml"
