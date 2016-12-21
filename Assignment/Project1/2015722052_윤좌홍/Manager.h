#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "CircularLinkedList.h"
#include "AlphabetBST.h"
#include "Queue.h"
#include <utility>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
using namespace std;

class Manager
{
public:
	CircularLinkedList * cll;	// MEMORIZED Circular Linked List
	AlphabetBST	* bst;			// MEMORIZING BST
	Queue * queue;				// TO_MEMORIZE Queue

	char * order;				//excute order
	char * option_1;			//Text word file name, move word conunt, print struct, Updata word, Test word
	char * option_2;			//print option, Updata mean, Test mean
	ofstream fout_log;
	pair<char *, char *> wordmean;
public:
	Manager();
	~Manager();

	void run(const char * command);	// ifstream fin; fin.open(command); // and read all line
	char *  strlwr(char * str);
	bool LOAD();
	bool ADD();
	bool MOVE();
	bool SAVE();
	bool TEST();
	bool SEARCH();
	bool PRINT();
	bool UPDATE();
};

#endif
