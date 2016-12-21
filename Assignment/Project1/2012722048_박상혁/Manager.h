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
	AlphabetBST	* bst;		// MEMORIZING BST
	Queue * queue;			// TO_MEMORIZE Queue

public:
	Manager();
	~Manager();

	void run(const char * command);	// ifstream fin; fin.open(command); // and read all line
	
	bool LOAD();					// LOAD to Queue, BST, CLL from each text file
	bool ADD();					// ADD to Queue from word.txt
	bool MOVE(int num);				// MOVE Queue -> BST
	bool SAVE();					// SAVE to text file
	bool TEST(char * word, char * mean);		// TEST and move BST -> CLL
	bool SEARCH(char * word);			// SEARCH words
	bool PRINT(char * name, char * order);		// PRINT each structure's words
	bool UPDATE(char * word, char * mean);		// UPDATE word's mean
};

#endif
