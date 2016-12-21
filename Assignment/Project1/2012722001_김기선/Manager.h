#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "CircularLinkedList.h"
#include "AlphabetBST.h"
#include "Queue.h"
#include <utility>

class Manager
{
public:
	CircularLinkedList * cll;	// MEMORIZED Circular Linked List
	AlphabetBST	* bst;			// MEMORIZING BST
	Queue * queue;				// TO_MEMORIZE Queue
	char* file_word1;			// command file variable
	char* file_word2;			// command file variable
	int file_wordcnt;			// command file variable for BST

public:
	Manager();
	~Manager();

	void run(const char * command);	// ifstream fin; fin.open(command); // and read all line

	bool LOAD();			//LOAD function
	bool ADD();			//ADD function
	bool MOVE();			//MOVE function
	bool SAVE();			//SAVE function
	bool TEST();			//TEST function
	bool SEARCH();			//SEARCH function
	bool PRINT();			//PRINT function
	bool UPDATE();			//UPDATE function

	void Conversion(char* input);	//CONVERSION function
};

#endif
