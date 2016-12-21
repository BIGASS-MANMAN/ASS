#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "CircularLinkedList.h"
#include "AlphabetBST.h"
#include "Queue.h"
#include <utility>
#pragma warning(disable:4996) 

class Manager
{
public:
	CircularLinkedList* cll;	// MEMORIZED Circular Linked List
	AlphabetBST* bst;			// MEMORIZING BST
	Queue* queue;				// TO_MEMORIZE Queue

public:
	Manager();
	~Manager();
	char* tok1;
	char* tok2;
	char* tok3;


	void run(const char* command);	// ifstream fin; fin.open(command); // and read all line
	bool LOAD(); //load
	bool ADD(); //add
	bool MOVE(); //move
	bool SAVE(); //save
	bool TEST(); // if test passes the input then put it into CLL
	bool SEARCH(); //search
	bool PRINT(); //print
	bool UPDATE(); //update
	void ComImple(char* tok1, char* tok2, char* tok3);
	void ChoosePrint(char* a2, char* a3);
	char* up(char* word);

};

#endif
