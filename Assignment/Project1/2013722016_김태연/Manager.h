#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "CircularLinkedList.h"
#include "AlphabetBST.h"
#include "Queue.h"
#include <utility>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;

class Manager
{
public:
	CircularLinkedList * cll;	// MEMORIZED Circular Linked List
	AlphabetBST	* bst;			// MEMORIZING BST
	Queue * queue;				// TO_MEMORIZE Queue
	char *arg1, *arg2;

public:
	Manager();
	~Manager();

	void run(const char * command);	// ifstream fin; fin.open(command); // and read all line

	bool LOAD();
	bool ADD();
	bool MOVE();
	bool TEST();
	bool SEARCH();
	bool PRINT();
	bool UPDATE();
	bool SAVE();
	void Set(char* string);

};

#endif

