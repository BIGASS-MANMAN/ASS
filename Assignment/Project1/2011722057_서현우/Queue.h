#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "WordNode.h"
#include <cstring>
class Queue
{
public:
	WordNode * pHead;//Variable pHead declarations
public:
	Queue();//Constructor
	~Queue();//Destructor

	void		Push(WordNode * node);// Function Push declarations(Use LOAD, ADD)
	WordNode *	Pop();// Function Pop declarations (Use MOVE)
	WordNode *	Search(char * word);// Function Search declarations (Use SEARCH, UPDATE)
	bool		Print();// Function Print declarations (Use PRINT)
	bool		Save();// Function Save declarations (Use SAVE)
};

#endif
