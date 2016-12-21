#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "WordNode.h"
#include <iostream>
#include <fstream>
using namespace std;
class Queue
{
public:	// Queue Head Pointer
	WordNode * pHead;
	WordNode * pTail;
public:	//the member function of Queue
	Queue();
	~Queue();
	void setHead(WordNode * node);    //setHead
	void setTail(WordNode * node);    //setTail
	WordNode * getHead();            //Get Head Pointer
	WordNode * getTail();           //Get Tail Pointer
	void		Push(WordNode * node);				// LOAD, ADD
	WordNode *	Pop();						// MOVE
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	bool		Print();							// PRINT
	bool		Save();								// SAVE
	bool        IsEmpty();
};

#endif
