#ifndef _CIRCULARLINKEDLIST_H_
#define _CIRCULARLINKEDLIST_H_

#include "WordNode.h"

/* MEMORIZED */
class CircularLinkedList
{
public:
	WordNode* pHead;	// Circular Linked List Head Pointer

	CircularLinkedList();
	~CircularLinkedList();

	void		Insert(WordNode* node);			// LOAD, TEST
	WordNode *	Search(char* word);				// SEARCH, UPDATE
	bool		Print();						// PRINT
	bool		Save();							// SAVE
	char* up(char* word);
	
};

#endif
