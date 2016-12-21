#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "WordNode.h"
#include <fstream>

class Queue
{
public:
	WordNode * pHead;
	WordNode * pTail;
	WordNode * pPop;
	WordNode * pSearch;
	WordNode * pPrint;
	WordNode * pSave;


public:
	Queue();
	~Queue();

	void		Push(WordNode * node);				// LOAD, ADD
	WordNode *	Pop();								// MOVE
	bool		IsEmpty();
	WordNode *	Front();
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	bool		Print();							// PRINT
	bool		Save();								// SAVE
	int			count();
};

#endif
