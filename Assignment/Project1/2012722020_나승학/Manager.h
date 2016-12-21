#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "CircularLinkedList.h"
#include "AlphabetBST.h"
#include "Queue.h"
#include <utility>

class Manager
{
private:
	CircularLinkedList * cll;	// MEMORIZED Circular Linked List
	AlphabetBST	* bst;			// MEMORIZING BST
	Queue * queue;				// TO_MEMORIZE Queue
	char m_Word[50];			// Word to UPDATE or TEST or SEARCH
	char m_Mean[50];			// Mean to UPDATE or TEST
	char m_search[50];			// Mean to search
	char m_Print[13];			// Way to PRINT
	char m_Print2[8];			// Way to PRINT
	int m_Move;					// The number of MOVE

public:
	Manager();					// Constructor
	~Manager();					// Destructor

	void run(const char * command);	// ifstream fin; fin.open(command); // and read all line
	
	bool LOAD();							// Load to_memorize.txt / memorizing.txt / memorized.txt
	bool ADD();								// Load word.txt
	bool MOVE();							// Move words to MEMORIZING frotm TO_MEMORIZE
	bool SAVE();							// Save words to text file
	bool TEST();							// Test word in MEMORIZING then move that word to MEMORIZED If pass
	bool SEARCH();							// Search word in word book
	bool PRINT();							// Print words of TO_MEMORIZE or MEMORIZING or MEMORIZED
	bool UPDATE();							// Update word in word book
	void LOG(const int, const bool);		// Record log about using word book program to log.txt
};

#endif
