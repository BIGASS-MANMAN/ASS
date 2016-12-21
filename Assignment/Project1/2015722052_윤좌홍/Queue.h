#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "WordNode.h"
#include <fstream>
using namespace std;
class Queue
{
public:
	WordNode * pHead;
	int WordCnt;
	ofstream fout_word;
public:
	Queue();
	~Queue();

	void		Push(WordNode * node);				// LOAD, ADD
	WordNode *	Pop();						// MOVE
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	bool		Print();							// PRINT
	bool		Save();								// SAVE
	int			GetWordCnt();
	void		SetWordCnt(int count);
};

#endif
