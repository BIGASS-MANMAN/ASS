#ifndef _CIRCULARLINKEDLIST_H_
#define _CIRCULARLINKEDLIST_H_
/************************************************************/
/*This is CircularLinkedList.cc that structred CLL			*/
/*Also, It is definition about CircularLinkedList Class	*/
/************************************************************/
#define MEMORIZED_FILENAME "memorized_word.txt" 
#include "WordNode.h"

class CircularLinkedList
{
public:
	/*MEMBER VARIABLE*/
	WordNode * pHead;	// Circular Linked List Head Pointer
	WordNode * pTail;

public:
	/*CONSTRUCTOR, DESTRUCTOR*/
	CircularLinkedList();
	~CircularLinkedList();

	/*MEMBER FUNCTION*/
	void		Insert(WordNode * node);			// LOAD, TEST
	WordNode *	Search(char * word);				// SEARCH, UPDATE
	bool		Print();							// PRINT
	bool		Save();
	bool		isEmpty();
};

#endif
