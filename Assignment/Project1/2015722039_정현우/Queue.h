#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "WordNode.h"
using namespace std;

class Queue
{
public:
	WordNode * pHead;	//Queue's head
	ofstream Wmemory;	//Write in to_memorize.txt
	ofstream Log;		//Wirte Log
public:
	Queue();
	~Queue();
	void		Push(WordNode * node);				// LOAD, ADD
	WordNode *	Pop();								// MOVE
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	bool		Print();							// PRINT
	bool		Save();								// SAVE
	bool		Empty();							//Empty
	WordNode *	Front();							//Front
		
};

#endif
