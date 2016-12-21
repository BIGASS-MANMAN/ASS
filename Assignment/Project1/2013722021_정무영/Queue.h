#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "WordNode.h"
using namespace std;
class Queue
{
public:
	WordNode * pHead;
	WordNode * pTail;
	int numOfWords;
	ofstream logfile;

public:
	Queue();
	~Queue();

	void		Push(WordNode * node);				// LOAD, ADD
	WordNode *	Pop();						// MOVE
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	bool		Print();							// PRINT
	bool		Save();								// SAVE
	int			GetNum();
};

#endif
