#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "CircularLinkedList.h"
#include "AlphabetBST.h"
#include "Queue.h"
#include <fstream>
#include <iostream>

using namespace std;

class Manager
{
public:
	CircularLinkedList * cll;	// MEMORIZED Circular Linked List
	AlphabetBST	* bst;			// MEMORIZING BST
	Queue * queue;				// TO_MEMORIZE Queue

	char* arg1;					// command parameter1
	char* arg2;					// command parameter2

public:
	Manager();
	~Manager();

	void run(const char * command);	// and read all line
	
	bool LOAD();
	bool ADD();		
	bool MOVE();
	bool SAVE();
	bool TEST();
	bool SEARCH();
	bool PRINT();
	bool UPDATE();
	void EXIT();

	void getins(char* command);		// execute menu
};

#endif
