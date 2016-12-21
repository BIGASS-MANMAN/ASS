#ifndef _CIRCULARLINKEDLIST_H_
#define _CIRCULARLINKEDLIST_H_

#include "WordNode.h"
#include <iostream>

using namespace std;

class CircularLinkedList
{
public:
	WordNode * pHead;	// Circular Linked List Head Pointer

public:
	CircularLinkedList();
	~CircularLinkedList();

	void		Insert(WordNode * node);			// LOAD, TEST
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	bool		Print();							// PRINT
	bool		Save();								// SAVE
	WordNode*	GetHead(){return pHead;}			// get pHead
};

#endif