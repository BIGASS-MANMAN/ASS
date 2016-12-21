#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "WordNode.h"

class Queue
{
public:
	WordNode * pHead;
	int WordCnt;

public:
	Queue(){pHead = '\0';WordCnt=0;}
	~Queue(){}

	void		Push(WordNode * node);	// LOAD, ADD
	WordNode *	Pop();					// MOVE
	WordNode *	Search(char * word);	// SEARCH, UPDATE
	bool		Print();				// PRINT
	bool		Save();					// SAVE

	WordNode* GetHead(){return pHead;}	// Get pHead

	int GetWordCnt(){return WordCnt;}	// Get WordCnt
	void SetWordCntup(){WordCnt++;}		// Set WordCnt
	void SetWordCntdown(){WordCnt--;}	// Set WordCnt
};

#endif
