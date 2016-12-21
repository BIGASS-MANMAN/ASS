#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "WordNode.h"

class Queue
{
public:
	WordNode * pHead;

public:
	Queue();
	~Queue();

	void		Push(WordNode * node);
	void        Push(const char*word,const char*mean);  			// LOAD, ADD
	WordNode *	Pop();						// MOVE
	WordNode *	Search(const char * word);				// SEARCH, UPDATE
	bool		Print();							// PRINT
	bool		Save();								// SAVE
};

#endif
