#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "CircularLinkedList.h"
#include "AlphabetBST.h"
#include "Queue.h"

class Manager
{
public:
	CircularLinkedList * cll;	// MEMORIZED Circular Linked List
	AlphabetBST	* bst;			// MEMORIZING BST
	Queue * queue;				// TO_MEMORIZE Queue
	char *arg1, *arg2;			// variables for SEARCH,UPDATE function

public:
	Manager();
	~Manager();

	void run(const char * command);	// ifstream fin; fin.open(command); // and read all line
	
	bool LOAD();
	bool ADD();
	bool MOVE();
	bool SAVE();
	bool TEST();
	bool SEARCH();
	bool PRINT();
	bool UPDATE();
	void Error(const int number);	// Print error message to "log.txt" file
	void Success(const char *name);		// Print success message to "log.txt" file
};

#endif
