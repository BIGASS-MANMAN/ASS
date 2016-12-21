#ifndef _QUEUE_H_
#define _QUEUE_H_
/************************************************************/
/*This is Queue.h that structred Queue						*/
/*Also, It is definition about Queue Class					*/
/************************************************************/
#define TO_MEMORIZE_FILENAME "to_memorize_word.txt"
#include "WordNode.h"

class Queue
{
public:
	/*MEMBER VARIABLE*/
	WordNode * pHead;
	WordNode * pTail;
	
public:
	/*CONSTRUCTOR, DESTRUCTOR*/
	Queue();
	~Queue();

	/*MEMBER FUNCTION*/
	void		Push(WordNode * node);				// LOAD, ADD
	WordNode *  Pop_back();
	WordNode *	Pop();								// MOVE
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	WordNode *  top();
	bool		Print();							// PRINT
	bool		Save();	
	bool		isEmpty();
};

#endif
