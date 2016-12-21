#ifndef _CIRCULARLINKEDLIST_H_
#define _CIRCULARLINKEDLIST_H_

#include "WordNode.h"
class WordNode;
class CircularLinkedList
{
public:
	WordNode * pHead;	// Circular Linked List Head Pointer

public:
	CircularLinkedList();
	~CircularLinkedList();

	WordNode*	Get_Head();
	void		Insert(WordNode * node);			// LOAD, TEST
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	bool		Print();							// PRINT
	bool		Save();								// SAVE
};

#endif
