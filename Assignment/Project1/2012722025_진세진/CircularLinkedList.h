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

	void		Insert(WordNode * node);			// LOAD, TEST
	void		Insert(const char* word, const char* mean);

	WordNode *	Search(const char * word);			// SEARCH, UPDATE
	bool		Print();							// PRINT
	bool		Save();								// SAVE
};

#endif
