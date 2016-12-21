#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "WordNode.h"

class Queue
{	

public:
	WordNode * pHead;
	Queue();
	~Queue();

	void		Push(WordNode * node);				// LOAD, ADD
	WordNode *	Pop();						// MOVE
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	bool		Print();					// PRINT
	bool		Save();						// SAVE
	WordNode*	GetQueueHead();
};

#endif
