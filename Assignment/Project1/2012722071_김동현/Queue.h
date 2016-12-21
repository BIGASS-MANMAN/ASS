#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "WordNode.h"
#include <iostream>
#include <fstream>

class Queue
{
public:
	WordNode * pHead;
public:
	Queue();
	~Queue();

	void      Push(WordNode * node);            // LOAD, ADD
	WordNode *   Pop();                  // MOVE
	WordNode *   Search(char * word);            // SEARCH, UPDATE
	bool      Print();                     // PRINT
	bool      Save();                        // SAVE
	bool      IsEmpty();
	int         cnt();
};

#endif
