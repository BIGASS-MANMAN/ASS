#ifndef _CIRCULARLINKEDLIST_H_
#define _CIRCULARLINKEDLIST_H_

#include "WordNode.h"
#include <fstream>
#pragma execution_character_set("utf-8")
#include <string.h>

class CircularLinkedList
{
public:
	WordNode * pHead;
	WordNode * pTail;
	bool writable;

public:
	CircularLinkedList();
	~CircularLinkedList();

	void		Insert(WordNode * node);
	WordNode *	Search(char * word);
	bool		Print();
	bool		Save();
	void		SaveWord(WordNode * start, WordNode * pointer, int count);
	WordNode *	getHead();
	void		setHead(WordNode * node);
	WordNode *	getTail();
	void		setTail(WordNode * node);
};

#endif
