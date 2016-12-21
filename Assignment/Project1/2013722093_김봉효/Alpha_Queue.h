
#ifndef _ALPHA_QUEUE_H_
#define _ALPHA_QUEUE_H_

#include "WordNode.h"
#include"AlphabetNode.h"

class Alpha_Queue
{
public:
	AlphabetNode* pHead;

public:
	Alpha_Queue();
	~Alpha_Queue();

	void			Push(AlphabetNode * node);				// LOAD, ADD
	AlphabetNode *	Pop();						// MOVE
	bool			IsEmpty();
};

#endif
