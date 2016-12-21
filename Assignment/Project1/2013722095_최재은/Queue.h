#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "WordNode.h"
/* TO MEMORIZE */
class Queue
{
public:
	WordNode* pHead;
	WordNode* pTail;
	Queue();
	~Queue();

	void		Push(WordNode* node);		// LOAD, ADD
	WordNode*	Pop();						// MOVE
	WordNode*	Search(char* word);			// SEARCH, UPDATE
	bool		Print();					// PRINT
	bool		Save();						// SAVE
	int Cntqueue();
	char* up(char* word);

};

#endif
