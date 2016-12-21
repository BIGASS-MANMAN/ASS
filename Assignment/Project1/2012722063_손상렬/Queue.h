#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "WordNode.h"
#include "fstream"
#include <string.h>
#pragma warning(disable:4996)
#pragma execution_character_set("utf-8")

class Queue
{
public:
	WordNode * pHead;
	WordNode * pTail;

public:
	Queue();
	~Queue();

	void		Push(WordNode * node);	
	WordNode *	Pop();	
	WordNode *	Search(char * word);	
	bool		Print();
	bool		Save();	
	bool		empty();
	void		Display();
};

#endif
