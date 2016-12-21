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
	int			count();							//for counting word
	void		Push(WordNode * node);				// LOAD, ADD
	WordNode *	Pop();						// MOVE
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	bool		Print();							// PRINT
	bool		Save();								//SAVE
	char* 		GetBigWord(char * word);			// change small word to big word
};

#endif
