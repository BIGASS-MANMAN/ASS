#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "WordNode.h"

class Queue
{
private:
	WordNode * pHead;								// Head pointer of Queue
	WordNode * pTail;								// Tail pointer of Queue
	int WordCnt;									// The number of nodes of Queue
public:
	Queue();										// Constructor
	~Queue();										// Destructor

	void		Push(WordNode * node);				// LOAD, ADD
	WordNode *	Pop();								// MOVE
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	bool		Print();							// PRINT
	bool		Save();								// SAVE
	bool		IsEmpty();							// Check the number of node of Queue
	int			WordNumber();						// return word number
};

#endif
