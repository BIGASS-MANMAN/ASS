#ifndef _CIRCULARLINKEDLIST_H_
#define _CIRCULARLINKEDLIST_H_

#include "WordNode.h"
#include<fstream>

class CircularLinkedList
{
public:
	WordNode * pHead;	// Circular Linked List Head Pointer
	WordNode * pSearch;
	WordNode * pPrint;
	WordNode * pSave;

public:
	CircularLinkedList();
	~CircularLinkedList();

	void		Insert(WordNode * node);			// LOAD, TEST
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	bool		Print();							// PRINT
	bool		Save();								// SAVE
};

#endif
