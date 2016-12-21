#!/bin/bash

ASS=$1
TEST=$2
STUDENT=$3

tar -C /usr/local/Auto_Scoring_System/Assignment/$ASS/$STUDENT -xvf /usr/local/Auto_Scoring_System/Assignment/$ASS/$STUDENT/$STUDENT.tar.gz
chmod 777 /usr/local/Auto_Scoring_System/Assignment/$ASS/$STUDENT/*
rm /usr/local/Auto_Scoring_System/Assignment/$ASS/$STUDENT/*.txt
sed -i 's/^\xef\xbb\xbf//g' /usr/local/Auto_Scoring_System/Assignment/$ASS/$STUDENT/*.cc /usr/local/Auto_Scoring_System/Assignment/$ASS/$STUDENT/*.h
cp /usr/local/Auto_Scoring_System/info/$ASS/word.txt /usr/local/Auto_Scoring_System/Assignment/$ASS/$STUDENT
python /usr/local/Auto_Scoring_System/src/MakeDeathMake.py $ASS $STUDENT
python /usr/local/Auto_Scoring_System/src/MakeDeathTest.py $ASS $STUDENT
python /usr/local/Auto_Scoring_System/src/InsertSigHandler.py $ASS $STUDENT
cd /usr/local/Auto_Scoring_System/Assignment/$ASS/$STUDENT
make
./Death_$TEST --gtest_output="xml:./Result/Death_test.xml"
python /usr/local/Auto_Scoring_System/src/Report_Death_Test.py $ASS $STUDENT
python /usr/local/Auto_Scoring_System/src/MakeMake.py $ASS $STUDENT
python /usr/local/Auto_Scoring_System/src/MakeUnitTest.py $ASS $STUDENT
make
./$TEST --gtest_output="xml:./Result/Unit_Result.xml"
python /usr/local/Auto_Scoring_System/src/Report.py $ASS $STUDENT
python /usr/local/Auto_Scoring_System/src/Xml2Json.py $ASS $STUDENT
python /usr/local/Auto_Scoring_System/src/DB_Scoring.py $ASS $STUDENT
