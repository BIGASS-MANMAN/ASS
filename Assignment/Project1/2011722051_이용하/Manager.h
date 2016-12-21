#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "CircularLinkedList.h"
#include "AlphabetBST.h"
#include "Queue.h"
#include <fstream>

class Manager
{
public:
	CircularLinkedList * cll;	// MEMORIZED Circular Linked List
	AlphabetBST	* bst;			// MEMORIZING BST
	Queue * queue;				// TO_MEMORIZE Queue
	int sig;

public:
	Manager();
	~Manager();

	void run(const char * command);	// ifstream fin; fin.open(command); // and read all line
	
	bool LOAD();
	bool ADD();
	bool MOVE(int num);
	bool SAVE();
	bool TEST(char * arg1, char * arg2);
	bool SEARCH(char * arg);
	bool PRINT(char * arg1, char * arg2);
	bool UPDATE(char * arg1, char * arg2);
};

#endif
