#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "WordNode.h"
#include <fstream>

using namespace std;

class Queue
{
public:
	WordNode * pHead;

public:
	Queue();
	~Queue();

	void		Push(WordNode * node);				// LOAD, ADD
	WordNode *	Pop();						// MOVE
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	bool		Print(ofstream& logfile);							// PRINT
	bool		Save();								// SAVE
	bool		Empty();
	WordNode *	Front();
};

#endif
