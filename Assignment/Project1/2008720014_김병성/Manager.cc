#include "/usr/local/Auto_Scoring_System/src/signal.h"
#include "Manager.h"
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
#define MAX_SIZE 100

Manager::Manager()
{
	cll = new CircularLinkedList;
	bst = new AlphabetBST;
	queue = new Queue;
}


Manager::~Manager()
{ return;

	delete cll;
	delete bst;
	delete queue;
}

void Manager::run(const char * command)
{
	struct sigaction sa;
	set_sigaction(sa);
	alarm(3);

	char inputString[MAX_SIZE];					// For reading text file by line
	ifstream fin;
	
	char alphabet[26] = { 'p','h','x','d','l',
		't','z','b','f','j',
		'n','r','v','y','a',
		'c','e','g','i','k',
		'm','o','q','s','u','w' };

	// Make up AlphabetBST
	AlphabetNode *alpha_node = new AlphabetNode[26];
	for (int i = 0;i<26;i++) {							
		alpha_node[i].SetAlphabet(alphabet[i]);
		bst->Insert(&alpha_node[i]);
	}
	
	fin.open(command);
	while (!fin.eof()) {
		fin.getline(inputString, MAX_SIZE - 1);
		//cout << inputString << endl;	//program checking tool
		Recognize_the_instruction(inputString);
	}

	fin.close();
}

void Manager::Recognize_the_instruction(char * text_line)	// Recognize the instruction lines in "log.txt"
{								
	ofstream FILEOUT;
	FILEOUT.open("log.txt", ios::app);
	instruction = strtok(text_line, " ");			// get the [instruction] from text_line
	int i=0;										// while statement variable
	while (parameter[i] = strtok(NULL, " ")) {		
		i++;
	}

	// According to [instruction], call the Command fuction.
	// if an error occur, print error_code
	if (!strcmp(instruction,"LOAD")) {
		if(!LOAD()) {
			Print_Error(100);
		}
	}
	else if (!strcmp(instruction, "ADD")) {
		if(!ADD()) {
			Print_Error(200);
		}
	}
	else if (!strcmp(instruction, "MOVE")) {
		if(!MOVE()) {
			Print_Error(300);
		}
	}
	else if (!strcmp(instruction, "SAVE")) {
		if(!SAVE()) {
			Print_Error(400);
		}
	}
	else if (!strcmp(instruction, "TEST")) {
		if(!TEST()) {
			Print_Error(500);
		}
	}
	else if (!strcmp(instruction, "SEARCH")) {
		if(!SEARCH()) {
			Print_Error(600);
		}
	}
	else if (!strcmp(instruction, "PRINT")) {
		if(!PRINT()) {
			Print_Error(700);
		}
	}
	else if (!strcmp(instruction, "UPDATE")) {
		if(!UPDATE()) {
			Print_Error(800);
		}
	}
	else if (!strcmp(instruction, "EXIT")) EXIT();

	FILEOUT.close();
}

void Manager::Print_Error(int error_code)				// Print error_code 
{
	ofstream FILEOUT("log.txt", ios::app);
	FILEOUT << "======== ERROR ========" << endl;
	FILEOUT << error_code << endl;
	FILEOUT << "=======================" << endl << endl;

	FILEOUT.close();
}


bool Manager::LOAD()
{
	ifstream fin01, fin02, fin03;
	ofstream FILEOUT;

	char inputString[MAX_SIZE];			
	char *word_token;

	if (parameter[0]) return false;									// ERROR CASE; LOAD command needs no parameter

	if (cll->GetpHead() || bst->GetWordCnt() || queue->GetpHead())	// ERROR CASE; When already data exist in Data Structure
		return false;
	
	
	fin01.open("to_memorize.txt");
	fin02.open("memorizing_word.txt");
	fin03.open("memorized_word.txt");
	FILEOUT.open("log.txt");

	// ERROR CASE; when "to_memorize.txt" OR "memorizing_word.txt" OR "memorized_word.txt" do not exist
	if(!fin01.is_open() || !fin02.is_open() || !fin03.is_open()) {
		if(!fin01.is_open()) ofstream FILE01("to_memorize_word.txt"); // create "to_memorize.txt" FILE
		if(!fin02.is_open()) ofstream FILE02("memorizing_word.txt"); // create "memorizing_word.txt" FILE
		if(!fin03.is_open()) ofstream FILE03("memorized_word.txt"); // create "memorized_word.txt" FILE
		return false;
	}

	// push "to_memorize_word.txt" into queue
	while(!fin01.eof()) {						 
		WordNode * NewNode = new WordNode;
		fin01.getline(inputString, MAX_SIZE-1);
		word_token = strtok(inputString, "\t");
		NewNode->SetWord(word_token);
		word_token = strtok(NULL, "\t");
		NewNode->SetMean(word_token);
		queue->Push(NewNode);
	}
	
	// push "memorizing_word.txt" into BST
	while(!fin02.eof()) {
		WordNode * NewNode = new WordNode;
		char ch;
		fin02.getline(inputString, MAX_SIZE - 1);
		word_token = strtok(inputString, "\t");
		ch = word_token[0];						// the first letter of a word
		NewNode->SetWord(word_token);
		word_token = strtok(NULL, "\t");
		NewNode->SetMean(word_token);
		
		AlphabetNode *an = bst->Getroot();	
		while(ch != an->GetAlphabet()) {
			if (ch < an->GetAlphabet())
				an = an->GetLeft();
			else if (ch > an->GetAlphabet())
				an = an->GetRight();
		}
		an->GetBST()->Insert(NewNode);
	}

	// push "memorized_word.txt" into Circular linked list
	while(!fin03.eof()) {
		WordNode * NewNode = new WordNode;
		fin03.getline(inputString, MAX_SIZE - 1);
		word_token = strtok(inputString, "\t");
		NewNode->SetWord(word_token);
		word_token = strtok(NULL, "\t");
		NewNode->SetMean(word_token);
		cll->Insert(NewNode);
	}

	FILEOUT << "======== LOAD ========" << endl;
	FILEOUT << "Success" << endl;
	FILEOUT << "======================" << endl << endl;

	fin01.close();
	fin02.close();
	fin03.close();
	FILEOUT.close();
	return true;
}

bool Manager::ADD()
{
	ifstream fin;
	ofstream FILEOUT;
	char* ppStr = NULL;
	char inputString[MAX_SIZE];
	char *word_token;
	char ch;
	fin.open("word.txt");
	FILEOUT.open("log.txt", ios::app);

	// ERROR CASE; ADD command needs no parameter
	if (parameter[0]) return false;

	// ERROR CASE; The "word.txt" file does not exist.
	if(!fin.is_open()) 
		return false;

	// ERROR CASE; when The "word.txt" file is empty
	if(!fin.get(ch)) return false;

	while(!fin.eof()) {
		WordNode *NewNode = new WordNode;
		fin.getline(inputString, MAX_SIZE-1);
		word_token = strtok_s(inputString, "\t",&ppStr);
		NewNode->SetWord(word_token);
		word_token = strtok_s(NULL, "\t",&ppStr);
		NewNode->SetMean(word_token);
		queue->Push(NewNode);
	}

	FILEOUT << "======== ADD ========" << endl;
	FILEOUT << "Success" << endl;
	FILEOUT << "======================" << endl << endl;

	fin.close();
	FILEOUT.close();
	return true;
}

bool Manager::MOVE()
{
	ofstream FILEOUT("log.txt");

	// ERROR CASE; MOVE command needs 1 parameter
	if (!parameter[0] || parameter[1]) return false;




	FILEOUT << "======== MOVE ========" << endl;
	FILEOUT << "Success" << endl;
	FILEOUT << "======================" << endl << endl;

	FILEOUT.close();
	return true;
}

bool Manager::SAVE()
{
	ofstream FILEOUT("log.txt");
	

	FILEOUT << "======== SAVE ========" << endl;
	FILEOUT << "Success" << endl;
	FILEOUT << "======================" << endl << endl;

	FILEOUT.close();
	return true;
}

bool Manager::TEST()
{
	ofstream FILEOUT("log.txt");




	FILEOUT << "======== LOAD ========" << endl;
	FILEOUT << "Pass" << endl;
	FILEOUT << "======================" << endl << endl;

	FILEOUT.close();
	return true;
}

bool Manager::SEARCH()
{
	cout << "SEARCH Execute complete" << endl;
	return false;
}

bool Manager::PRINT()
{
	ofstream FILEOUT;
	FILEOUT.open("log.txt", ios::app);

	if (!parameter[0]) return false;				// ERROR CASE; it needs at least one parameter

	if (!strcmp(parameter[0],"TO_MEMORIZE")) {		// the first parameter : TO_MEMORIZE

		if(parameter[1]) return false;				// ERROR CASE; It needs no parameter after "TO_MEMORIZE" 

		if(!queue->Print()) return false;
	}

	else if (!strcmp(parameter[0], "MEMORIZING")) {			// the first parameter : MEMORIZING

		if(!parameter[1] || parameter[2])					// ERROR CASE; It needs only 1 parameter after "MEMORIZING"
			return false;									// {"R_PRE","I_PRE","R_IN","I_IN","R_POST","I_POST","I_LEVEL"}

		if(!bst->Print(parameter[1])) return false;

	}

	else if (!strcmp(parameter[0], "MEMORIZED")) {			// the first parameter : MEMORIZED

		if (parameter[1]) return false;				// ERROR CASE; It needs no parameter after "MEMORIZED"

		WordNode *TempNode =cll->GetpHead();
		if (!TempNode) return false;				// ERROR CASE; "MEMORIZED" word list does not exist

		FILEOUT << "======== PRINT ========" << endl;
		FILEOUT << TempNode->GetWord() << " " << TempNode->GetMean() << endl;
		while (TempNode->GetNext() != cll->GetpHead()) {
			TempNode = TempNode->GetNext();
			FILEOUT << TempNode->GetWord() << " " << TempNode->GetMean() << endl;
		}
		FILEOUT << "=======================" << endl << endl;
	}	

	FILEOUT.close();
	return true;
}

bool Manager::UPDATE()
{
	cout << "UPDATE Execute complete" << endl;
	return true;
}

void Manager::EXIT()
{
}
