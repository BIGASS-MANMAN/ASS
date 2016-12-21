#ifndef _CIRCULARLINKEDLIST_H_
#define _CIRCULARLINKEDLIST_H_

#include "WordNode.h"

class CircularLinkedList
{
private:
	WordNode * pHead;	// Circular Linked List Head Pointer
	WordNode * pTail;	// Circular Linked List Tail Pointer
public:
	CircularLinkedList();							// Constructor
	~CircularLinkedList();							// Destructor

	void		Insert(WordNode * node);			// LOAD, TEST
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	bool		Print();							// PRINT
	bool		Save();								// SAVE
	WordNode *	Delete(WordNode * node);			// Delete
	bool		IsEmpty();							// Check the number of node of CircularLinkedList

};

#endif
