#ifndef _CIRCULARLINKEDLIST_H_
#define _CIRCULARLINKEDLIST_H_

#include "WordNode.h"

class CircularLinkedList
{
public:
	WordNode * pHead;	// Circular Linked List Head Pointer

public:
	CircularLinkedList();
	~CircularLinkedList();
	WordNode * 	GetHead();							// for pointing pHead
	void		Insert(WordNode * node);			// LOAD, TEST
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	bool		Print();							// PRINT
	bool		Save();								// SAVE
	char * 		GetBigWord(char*word);				//change small word to big word
};

#endif
