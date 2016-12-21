#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "CircularLinkedList.h"
#include "AlphabetBST.h"
#include "Queue.h"
#include <utility>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cstring>
using namespace std;

class Manager
{
public:
	CircularLinkedList * cll;	// MEMORIZED Circular Linked List
	AlphabetBST	* bst;			// MEMORIZING BST
	Queue * queue;				// TO_MEMORIZE Queue
	char* word;					// Char* type variable declarations
	char* mean;					// Char* type variable declarations
	char* order;				// Char* type variable declarations
	char* select;				// Char* type variable declarations
public:
	Manager();//Constructor
	~Manager();//Destructor

	void run(const char * command);	// ifstream fin; fin.open(command); // and read all line
	
	bool LOAD();// Function LOAD declarations
	bool ADD();// Function ADD declarations
	bool MOVE();// Function MOVE declarations
	bool SAVE();// Function SAVE declarations
	bool TEST();// Function TEST declarations
	bool SEARCH();// Function SEARCH declarations
	bool PRINT();// Function PRINT declarations
	bool UPDATE();// Function UPDATE declarations
};

#endif
